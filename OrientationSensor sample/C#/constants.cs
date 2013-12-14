﻿//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

using System.Collections.Generic;
using System;

namespace SDKTemplate
{
    public partial class MainPage : SDKTemplate.Common.LayoutAwarePage
    {
        public const string FEATURE_NAME = "Orientation Sensor Raw Data";

        List<Scenario> scenarios = new List<Scenario>
        {
            new Scenario() { Title = "Orientation sensor data events", ClassType = typeof(Microsoft.Samples.Devices.Sensors.OrientationSensorSample.Scenario1) },
            new Scenario() { Title = "Poll orientation sensor readings", ClassType = typeof(Microsoft.Samples.Devices.Sensors.OrientationSensorSample.Scenario2) },
            new Scenario() { Title = "Sensor calibration", ClassType = typeof(Microsoft.Samples.Devices.Sensors.OrientationSensorSample.Scenario3) }
        };
    }

    public class Scenario
    {
        public string Title { get; set; }

        public Type ClassType { get; set; }

        public override string ToString()
        {
            return Title;
        }
    }
}
