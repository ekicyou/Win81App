﻿// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

//
// Scenario3Input.xaml.cpp
// Implementation of the Scenario3Input class.
//

#include "pch.h"
#include "ScenarioInput3.xaml.h"
#include "MainPage.xaml.h"

using namespace ToastsSampleCPP;

using namespace NotificationsExtensions::ToastContent;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Notifications;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

ScenarioInput3::ScenarioInput3()
{
	InitializeComponent();

	Scenario3DisplayToastImage01->Click += ref new RoutedEventHandler([this](Object^ sender, RoutedEventArgs^ e) {
		Scenario3DisplayToast(ToastTemplateType::ToastImageAndText01); 
	});

	Scenario3DisplayToastImage02->Click += ref new RoutedEventHandler([this](Object^ sender, RoutedEventArgs^ e) {
		Scenario3DisplayToast(ToastTemplateType::ToastImageAndText02); 
	});

	Scenario3DisplayToastImage03->Click += ref new RoutedEventHandler([this](Object^ sender, RoutedEventArgs^ e) {
		Scenario3DisplayToast(ToastTemplateType::ToastImageAndText03); 
	});

	Scenario3DisplayToastImage04->Click += ref new RoutedEventHandler([this](Object^ sender, RoutedEventArgs^ e) {
		Scenario3DisplayToast(ToastTemplateType::ToastImageAndText04); 
	});


	Scenario3DisplayToastImage01String->Click += ref new RoutedEventHandler([this](Object^ sender, RoutedEventArgs^ e) {
		Scenario3DisplayToastWithStringManipulation(ToastTemplateType::ToastImageAndText01); 
	});

	Scenario3DisplayToastImage02String->Click += ref new RoutedEventHandler([this](Object^ sender, RoutedEventArgs^ e) {
		Scenario3DisplayToastWithStringManipulation(ToastTemplateType::ToastImageAndText02); 
	});

	Scenario3DisplayToastImage03String->Click += ref new RoutedEventHandler([this](Object^ sender, RoutedEventArgs^ e) {
		Scenario3DisplayToastWithStringManipulation(ToastTemplateType::ToastImageAndText03); 
	});

	Scenario3DisplayToastImage04String->Click += ref new RoutedEventHandler([this](Object^ sender, RoutedEventArgs^ e) {
		Scenario3DisplayToastWithStringManipulation(ToastTemplateType::ToastImageAndText04); 
	});
}

ScenarioInput3::~ScenarioInput3()
{
}

#pragma region Template-Related Code - Do not remove
void ScenarioInput3::OnNavigatedTo(NavigationEventArgs^ e)
{
	// Get a pointer to our main page
	rootPage = dynamic_cast<MainPage^>(e->Parameter);
}

void ScenarioInput3::OnNavigatedFrom(NavigationEventArgs^ e)
{

}

#pragma endregion

void ScenarioInput3::OutputText(String^ text) {
	if (outputText == nullptr) 
	{
		// Get a pointer to the content within the OutputFrame.
		Page^ outputFrame = dynamic_cast<Page^>(rootPage->OutputFrame->Content);

		// Go find the elements that we need for this scenario
		outputText = dynamic_cast<TextBlock^>(outputFrame->FindName("Scenario3OutputText"));
	}

	outputText->Text = text;
}

void ScenarioInput3::Scenario3DisplayToast(ToastTemplateType templateType)
{
	IToastNotificationContent^ toastContent = nullptr;

	if (templateType == ToastTemplateType::ToastImageAndText01)
	{
		IToastImageAndText01^ specializedContent = ToastContentFactory::CreateToastImageAndText01();
		specializedContent->TextBodyWrap->Text = "Body text that wraps";
		specializedContent->Image->Src = Scenario3ImageUrl->Text;
		specializedContent->Image->Alt = "Web image";
		toastContent = specializedContent;
	}
	else if (templateType == ToastTemplateType::ToastImageAndText02)
	{
		IToastImageAndText02^ specializedContent = ToastContentFactory::CreateToastImageAndText02();
		specializedContent->TextHeading->Text = "Heading text";
		specializedContent->TextBodyWrap->Text = "Body text that wraps";
		specializedContent->Image->Src = Scenario3ImageUrl->Text;
		specializedContent->Image->Alt = "Web image";
		toastContent = specializedContent;
	}
	else if (templateType == ToastTemplateType::ToastImageAndText03)
	{
		IToastImageAndText03^ specializedContent = ToastContentFactory::CreateToastImageAndText03();
		specializedContent->TextHeadingWrap->Text = "Heading text that wraps";
		specializedContent->TextBody->Text = "Body text";
		specializedContent->Image->Src = Scenario3ImageUrl->Text;
		specializedContent->Image->Alt = "Web image";
		toastContent = specializedContent;
	}
	else if (templateType == ToastTemplateType::ToastImageAndText04)
	{
		IToastImageAndText04^ specializedContent = ToastContentFactory::CreateToastImageAndText04();
		specializedContent->TextHeading->Text = "Heading text that wraps";
		specializedContent->TextBody1->Text = "First body text";
		specializedContent->TextBody2->Text = "Second body text";
		specializedContent->Image->Src = Scenario3ImageUrl->Text;
		specializedContent->Image->Alt = "Web image";
		toastContent = specializedContent;
	}

    if (toastContent != nullptr)
    {
        OutputText(toastContent->GetContent());
        // Create a toast, then create a ToastNotifier object to show
        // the toast
        auto toast = toastContent->CreateNotification();
        // If you have other applications in your package, you can specify the AppId of
        // the app to create a ToastNotifier for that application
        ToastNotificationManager::CreateToastNotifier()->Show(toast);
    }
}

void ScenarioInput3::Scenario3DisplayToastWithStringManipulation(ToastTemplateType templateType)
{
	String^ toastXmlString = nullptr;

	if (templateType == ToastTemplateType::ToastImageAndText01)
	{
		toastXmlString = "<toast>"
			+ "<visual version='1'>"
			+ "<binding template='toastImageAndText01'>"
			+ "<text id='1'>Body text that wraps over three lines</text>"
			+ "<image id='1' src='" + Scenario3ImageUrl->Text + "' alt='Web image'/>"
			+ "</binding>"
			+ "</visual>"
			+ "</toast>";
	}
	else if (templateType == ToastTemplateType::ToastImageAndText02)
	{
		toastXmlString = "<toast>"
			+ "<visual version='1'>"
			+ "<binding template='toastImageAndText02'>"
			+ "<text id='1'>Heading text</text>"
			+ "<text id='2'>Body text that wraps over two lines</text>"
			+ "<image id='1' src='" + Scenario3ImageUrl->Text + "' alt='Web image'/>"
			+ "</binding>"
			+ "</visual>"
			+ "</toast>";
	}
	else if (templateType == ToastTemplateType::ToastImageAndText03)
	{
		toastXmlString = "<toast>"
			+ "<visual version='1'>"
			+ "<binding template='toastImageAndText03'>"
			+ "<text id='1'>Heading text that wraps over two lines</text>"
			+ "<text id='2'>Body text</text>"
			+ "<image id='1' src='" + Scenario3ImageUrl->Text + "' alt='Web image'/>"
			+ "</binding>"
			+ "</visual>"
			+ "</toast>";
	}
	else if (templateType == ToastTemplateType::ToastImageAndText04)
	{
		toastXmlString = "<toast>"
			+ "<visual version='1'>"
			+ "<binding template='toastImageAndText04'>"
			+ "<text id='1'>Heading text</text>"
			+ "<text id='2'>First body text</text>"
			+ "<text id='3'>Second body text</text>"
			+ "<image id='1' src='" + Scenario3ImageUrl->Text + "' alt='Web image'/>"
			+ "</binding>"
			+ "</visual>"
			+ "</toast>";
	}

	auto toastDOM = ref new Windows::Data::Xml::Dom::XmlDocument();
	try 
	{
		toastDOM->LoadXml(toastXmlString);

		OutputText(toastDOM->GetXml());

		// Create a toast, then create a ToastNotifier object to show
		// the toast
		auto toast = ref new ToastNotification(toastDOM);

		// If you have other applications in your package, you can specify the AppId of
		// the app to create a ToastNotifier for that application
		ToastNotificationManager::CreateToastNotifier()->Show(toast);
	}
	catch (Exception^ e)
	{
		rootPage->NotifyUser("Error loading the xml, check for invalid characters in the input", NotifyType::ErrorMessage);
	}
}