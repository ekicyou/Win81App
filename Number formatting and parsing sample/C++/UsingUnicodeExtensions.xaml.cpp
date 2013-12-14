﻿//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

//
// UsingUnicodeExtensions.xaml.cpp
// Implementation of the UsingUnicodeExtensions class
//

#include "pch.h"
#include "UsingUnicodeExtensions.xaml.h"

using namespace SDKSample::NumberFormatting;

using namespace Platform;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Globalization;
using namespace Windows::Globalization::NumberFormatting;

UsingUnicodeExtensions::UsingUnicodeExtensions()
{
    InitializeComponent();
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void UsingUnicodeExtensions::OnNavigatedTo(NavigationEventArgs^ e)
{
    // A pointer back to the main page.  This is needed if you want to call methods in MainPage such
    // as NotifyUser()
    rootPage = MainPage::Current;
}

/// <summary>
/// This is the click handler for the 'Display' button.
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void SDKSample::NumberFormatting::UsingUnicodeExtensions::Display_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{	
    // This scenario uses language tags with unicode extensions to construct and use the various 
    // formatters and NumeralSystemTranslator in Windows.Globalization.NumberFormatting to format numbers 

    // Variable where we keep results to display
    String^ results = "";

	// Create number to format.
    float randomNumber = (float)rand() / RAND_MAX * 100000.0f;
    results += "Random number used by formatters: " + randomNumber + "\n";
    // Create a string to translate
    String^ stringToTranslate = "These are the 10 digits of a numeral system: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9";
    results += "String used by NumeralSystemTranslater: " + stringToTranslate + "\n";
    // Create the rounder and set its increment to 0.01
    IncrementNumberRounder^ rounder = ref new IncrementNumberRounder();
    rounder->Increment = 0.001;
    results += "CurrencyFormatter will be using Euro symbol and all formatters rounding to 0.001 increments\n\n";
	
	// The list of language tags with unicode extensions we want to test
	auto languages = ref new Platform::Collections::Vector<String^>();
    languages->Append("de-DE-u-nu-telu-ca-buddist-co-phonebk-cu-usd");
    languages->Append("ja-jp-u-nu-arab");
    	
    // Create the various formatters, now using the language list with unicode extensions
	results += "Creating formatters using following languages in the language list: \n";
	for(unsigned int i =0; i<languages->Size; i++)
	{
		results += "\t" + languages->GetAt(i) + "\n";
	}
	results += "\n";

	// Create the various formatters.
    DecimalFormatter^ decimalFormatter = ref new DecimalFormatter(languages, "ZZ");
    decimalFormatter->NumberRounder = rounder; decimalFormatter->FractionDigits = 2;
    CurrencyFormatter^ currencyFormatter = ref new CurrencyFormatter(CurrencyIdentifiers::EUR, languages, "ZZ");
    currencyFormatter->NumberRounder = rounder; currencyFormatter->FractionDigits = 2;
    PercentFormatter^ percentFormatter = ref new PercentFormatter(languages, "ZZ");
    percentFormatter->NumberRounder = rounder; percentFormatter->FractionDigits = 2;
    PermilleFormatter^ permilleFormatter = ref new PermilleFormatter(languages, "ZZ");
    permilleFormatter->NumberRounder = rounder; permilleFormatter->FractionDigits = 2;
    NumeralSystemTranslator^ numeralTranslator = ref new NumeralSystemTranslator(languages);
	
    results += "Using resolved language  " + decimalFormatter->ResolvedLanguage + "  : (note that all extension tags other than nu are ignored)\n";          
    // Format using formatters and translate using NumeralSystemTranslator.
    results += "Decimal Formatter:   " + decimalFormatter->Format(randomNumber) + "\n";
    results += "Currency formatted:   " + currencyFormatter->Format(randomNumber) + "\n";
    results += "Percent formatted:   " + percentFormatter->Format(randomNumber) + "\n";
    results += "Permille formatted:   " + permilleFormatter->Format(randomNumber) + "\n";
    results += "NumeralTranslator translated:   " + numeralTranslator->TranslateNumerals(stringToTranslate) + "\n";
		
	// Display the results.
    rootPage->NotifyUser(results, NotifyType::StatusMessage);
}
