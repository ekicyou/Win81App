//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
//
//*********************************************************

#pragma once

namespace SDKSample
{
    public value struct Scenario
    {
        Platform::String^ Title;
        Platform::String^ ClassName;
    };

    partial ref class MainPage
    {
    internal:
        static property Platform::String^ FEATURE_NAME 
        {
            Platform::String^ get() 
            {  
                return "Media Extensions"; 
            }
        }

        static property Platform::Array<Scenario>^ scenarios 
        {
            Platform::Array<Scenario>^ get() 
            { 
                return scenariosInner; 
            }
        }		

    private:
        static Platform::Array<Scenario>^ scenariosInner;
    };

    namespace MediaExtensions
    {
		ref class SampleUtilities sealed
		{
		public:
			static void PickSingleFileAndSet(Windows::Foundation::Collections::IVector<Platform::String^>^ fileTypeFilters, Windows::Foundation::Collections::IVector<Windows::UI::Xaml::Controls::MediaElement^>^ mediaElements);
		};
    }
}
