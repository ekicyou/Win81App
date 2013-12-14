﻿//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include "pch.h"
#include "App.h"
#include <Initguid.h>
#include <dxgi1_3.h>
#include <dxgidebug.h>

using namespace MarbleMaze;

using namespace concurrency;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Devices::Input;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;

// The main function is only used to initialize our IFrameworkView class.
// <snippet5>
[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
    auto directXApplicationSource = ref new DirectXApplicationSource();
    CoreApplication::Run(directXApplicationSource);
    return 0;
}
// </snippet5>

// <snippet2>
IFrameworkView^ DirectXApplicationSource::CreateView()
{
    return ref new App();
}
// </snippet2>

App::App() :
    m_windowClosed(false),
    m_windowVisible(true)
{
}

// The first method called when the IFrameworkView is being created.
// <snippet3>
void App::Initialize(CoreApplicationView^ applicationView)
{
    // Register event handlers for app lifecycle. This example includes Activated, so that we
    // can make the CoreWindow active and start rendering on the window.
    applicationView->Activated +=
        ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &App::OnActivated);

    CoreApplication::Suspending +=
        ref new EventHandler<SuspendingEventArgs^>(this, &App::OnSuspending);

    CoreApplication::Resuming +=
        ref new EventHandler<Platform::Object^>(this, &App::OnResuming);

    // At this point we have access to the device.
    // We can create the device-dependent resources.
    m_deviceResources = std::make_shared<DX::DeviceResources>();
}
// </snippet3>

// Called when the CoreWindow object is created (or re-created).
// <snippet4>
void App::SetWindow(CoreWindow^ window)
{
    window->PointerCursor = ref new CoreCursor(CoreCursorType::Arrow, 0);

    window->SizeChanged +=
        ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &App::OnWindowSizeChanged);

    window->VisibilityChanged +=
        ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &App::OnVisibilityChanged);

    window->Closed +=
        ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &App::OnWindowClosed);

    window->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &App::OnPointerPressed);

    window->PointerReleased += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &App::OnPointerReleased);

    window->PointerMoved += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &App::OnPointerMoved);

    window->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &App::OnKeyDown);

    window->KeyUp += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &App::OnKeyUp);

    DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();
    currentDisplayInformation->DpiChanged += ref new TypedEventHandler<DisplayInformation^, Platform::Object^>(this, &App::OnDpiChanged);
    currentDisplayInformation->OrientationChanged += ref new TypedEventHandler<DisplayInformation^, Platform::Object^>(this, &App::OnOrientationChanged);

    DisplayInformation::DisplayContentsInvalidated += ref new TypedEventHandler<DisplayInformation^, Object^>(this, &App::OnDisplayContentsInvalidated);

    // Disable all pointer visual feedback for better performance when touching.
    auto pointerVisualizationSettings = PointerVisualizationSettings::GetForCurrentView();
    pointerVisualizationSettings->IsContactFeedbackEnabled = false;
    pointerVisualizationSettings->IsBarrelButtonFeedbackEnabled = false;

    m_deviceResources->SetWindow(window);
    m_main = std::unique_ptr<MarbleMazeMain>(new MarbleMazeMain(m_deviceResources));
}
// </snippet4>

// Initializes scene resources, or loads a previously saved app state.
// <snippet112>
void App::Load(Platform::String^ entryPoint)
{
    task<void>([=]()
    {
        m_main->LoadDeferredResources(true, false);
    });
}
// </snippet112>

// This method is called after the window becomes active.
// <snippet6>
void App::Run()
{
    while (!m_windowClosed)
    {
        if (m_windowVisible)
        {
            CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

            m_main->Update();

            if (m_main->Render())
            {
                m_deviceResources->Present();
            }
        }
        else
        {
            CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
        }
    }

    // The app is exiting so do the same thing as would if app was being suspended.
    m_main->OnSuspending();

#ifdef _DEBUG
    // Dump debug info when exiting
    DumpD3DDebug();
#endif //_DEGBUG
}
// </snippet6>

// Required for IFrameworkView.
// Terminate events do not cause Uninitialize to be called. It will be called if your IFrameworkView
// class is torn down while the app is in the foreground.
void App::Uninitialize()
{
}

// Application lifecycle event handlers.

void App::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
{
    CoreWindow::GetForCurrentThread()->Activated += ref new TypedEventHandler<CoreWindow^, WindowActivatedEventArgs^>(this, &App::OnWindowActivationChanged);

    // Run() won't start until the CoreWindow is activated.
    CoreWindow::GetForCurrentThread()->Activate();
    m_windowVisible = true;
}

// <snippet14>
void App::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
    // Save app state asynchronously after requesting a deferral. Holding a deferral
    // indicates that the application is busy performing suspending operations. Be
    // aware that a deferral may not be held indefinitely. After about five seconds,
    // the app will be forced to exit.
    SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

    create_task([this, deferral]()
    {
        m_deviceResources->Trim();
        m_main->OnSuspending();
        deferral->Complete();
    });
}
// </snippet14>

// <snippet15>
void App::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
    // Restore any data or state that was unloaded on suspend. By default, data
    // and state are persisted when resuming from suspend. Note that this event
    // does not occur if the app was previously terminated.

    m_main->OnResuming();
}
// </snippet15>

// Window event handlers.

// <snippet9>
void App::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
{
    m_deviceResources->SetLogicalSize(Size(sender->Bounds.Width, sender->Bounds.Height));
    m_main->CreateWindowSizeDependentResources();
}
// </snippet9>

// <snippet114>
void App::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
    m_windowVisible = args->Visible;
}
// </snippet114>

void App::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
    m_windowClosed = true;
}

// Display properties event handlers.

void App::OnDpiChanged(DisplayInformation^ sender, Platform::Object^ args)
{
    m_deviceResources->SetDpi(sender->LogicalDpi);
    m_main->CreateWindowSizeDependentResources();
}

void App::OnOrientationChanged(DisplayInformation^ sender, Platform::Object^ args)
{
    m_deviceResources->SetCurrentOrientation(sender->CurrentOrientation);
    m_main->CreateWindowSizeDependentResources();
}

void App::OnDisplayContentsInvalidated(DisplayInformation^ sender, Platform::Object^ args)
{
    m_deviceResources->ValidateDevice();
}

void App::OnWindowActivationChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowActivatedEventArgs^ args)
{
    if (args->WindowActivationState == CoreWindowActivationState::Deactivated)
    {
        m_main->OnFocusChange(false);
    }
    else if (args->WindowActivationState == CoreWindowActivationState::CodeActivated
        || args->WindowActivationState == CoreWindowActivationState::PointerActivated)
    {
        m_main->OnFocusChange(true);
    }
}

// <snippet68>
void App::OnPointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
    m_main->AddTouch(args->CurrentPoint->PointerId, args->CurrentPoint->Position);
}

void App::OnPointerReleased(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
    m_main->RemoveTouch(args->CurrentPoint->PointerId);
}

void App::OnPointerMoved(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
    m_main->UpdateTouch(args->CurrentPoint->PointerId, args->CurrentPoint->Position);
}
// </snippet68>

void App::OnKeyDown(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args)
{
    m_main->KeyDown(args->VirtualKey);
}


void App::OnKeyUp(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args)
{
    m_main->KeyUp(args->VirtualKey);
#ifdef _DEBUG
    // Pressing F4 cause the app to exit, so that DumpD3DDebug method gets called on exit
    if (args->VirtualKey == VirtualKey::F4)
    {
        m_windowClosed = true;
    }
#endif // _DEBUG
}

#ifdef _DEBUG
void App::DumpD3DDebug()
{
    // This is debug code to free up all allocated D3D resources, and generate debug output for leaked objects.
    // The way this works is that D3D keeps track of all objects. When we destroy the m_main and m_deviceResources classes, 
    // all D3D objects should be released. If any objects that D3D thinks are not released are being leaked and the code should be examined.

    // Get the debug interface for the device.
    Microsoft::WRL::ComPtr<IDXGIDebug1> debugInterface = nullptr;
    DX::ThrowIfFailed(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debugInterface)));

    // Free up all D3D resources.
    m_deviceResources->GetD3DDeviceContext()->ClearState();
    m_deviceResources->GetD3DDeviceContext()->Flush();

    UserInterface::GetInstance().Release();
    m_main = nullptr;
    m_deviceResources = nullptr;

    // Dump the list of leaked objects to the debugger output window.
    DX::ThrowIfFailed(debugInterface->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL));
}
#endif
