//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#include "pch.h"
#include "MainPage.xaml.h"
#include "Constants.h"

using namespace SDKSample;

Platform::Array<Scenario>^ MainPage::scenariosInner = ref new Platform::Array<Scenario>
{
    // The format here is the following:
    //     { "Description for the sample", "Fully quaified name for the class that implements the scenario" }
    { "Mobile Broadband Device", "SDKSample.MobileBroadband.BroadbandDevice" },
    { "Network Account Watcher", "SDKSample.MobileBroadband.AccountWatcher" },
    { "Operator Notification", "SDKSample.MobileBroadband.OperatorMessage" },
    { "Connection UI", "SDKSample.MobileBroadband.ShowConnection" },
    { "Get Connection Profiles", "SDKSample.MobileBroadband.GetConnectionProfiles" },
    { "Tethering", "SDKSample.MobileBroadband.StartStopTethering" }
};
