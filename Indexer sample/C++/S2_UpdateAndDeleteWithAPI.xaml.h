//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
//
//*********************************************************

//
// S2_UpdateAndDeleteWithAPI.xaml.h
// Declaration of the S2_UpdateAndDeleteWithAPI class
//

#pragma once
#include "S2_UpdateAndDeleteWithAPI.g.h"

namespace SDKSample
{
    namespace Indexer
    {
        public ref class S2_UpdateAndDeleteWithAPI sealed
        {
        public:
            S2_UpdateAndDeleteWithAPI();

        private:
            void AddToIndex_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
            void UpdatePropertyHelper(Platform::String^ itemKey, Platform::String^ propertyKey, Platform::String^ propertyName, Platform::Object^ newValue);
            void UpdateName_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
            void DeleteKeywords_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
            void DeleteItemsHelper(std::function<Windows::Foundation::IAsyncAction^(Windows::Storage::Search::ContentIndexer^)> deleteFunction);
            void DeleteSingleItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
            void DeleteMultipleItems_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
            void DeleteAllItems_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        };
    }
}
