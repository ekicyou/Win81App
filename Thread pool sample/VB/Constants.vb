﻿'*********************************************************
'
' Copyright (c) Microsoft. All rights reserved.
' THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
' IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
' PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
'
'*********************************************************


Imports System
Imports Windows.System.Threading

Namespace Global.SDKTemplate
    Partial Public Class MainPage
        Inherits SDKTemplate.Common.LayoutAwarePage

        ' Change the string below to reflect the name of your sample.
        ' This is used on the main page as the title of the sample.
        Public Const FEATURE_NAME As String = "ThreadPool"

        ' Change the array below to reflect the name of your scenarios.
        ' This will be used to populate the list of scenarios on the main page with
        ' which the user will choose the specific scenario that they are interested in.
        ' These should be in the form: "Navigating to a web page".
        ' The code in MainPage will take care of turning this into: "1) Navigating to a web page"
        Private scenariosList As New List(Of Scenario)() From { _
            New Scenario() With {.Title = "Thread pool delay timer", .ClassType = GetType(ThreadPool.DelayTimer)}, _
            New Scenario() With {.Title = "Thread pool periodic timer", .ClassType = GetType(ThreadPool.PeriodicTimer)}, _
            New Scenario() With {.Title = "Thread pool work item", .ClassType = GetType(ThreadPool.WorkItem)} _
        }
    End Class

    Public Class Scenario
        Public Property Title() As String

        Public Property ClassType() As Type

        Public Overrides Function ToString() As String
            Return Title
        End Function
    End Class
End Namespace

Public Enum Status
    Unregistered = 0
    Started = 1
    Canceled = 2
    Completed = 3
End Enum

Friend Class ThreadPoolSample
    Public Shared DelayTimer As ThreadPoolTimer
    Public Shared DelayTimerScenario As DelayTimer
    Public Shared DelayTimerMilliseconds As Integer = 0
    Public Shared DelayTimerInfo As String = ""
    Public Shared DelayTimerStatus As Status = Status.Unregistered
    Public Shared DelayTimerSelectedIndex As Integer = 0

    Public Shared PeriodicTimer As ThreadPoolTimer
    Public Shared PeriodicTimerScenario As PeriodicTimer
    Public Shared PeriodicTimerCount As Long = 0
    Public Shared PeriodicTimerMilliseconds As Integer = 0
    Public Shared PeriodicTimerInfo As String = ""
    Public Shared PeriodicTimerStatus As Status = Status.Unregistered
    Public Shared PeriodicTimerSelectedIndex As Integer = 0

    Public Shared ThreadPoolWorkItem As IAsyncAction
    Public Shared WorkItemScenaioro As WorkItem
    Public Shared WorkItemPriority As WorkItemPriority = WorkItemPriority.Normal
    Public Shared WorkItemStatus As Status
    Public Shared WorkItemSelectedIndex As Integer = 1
End Class
