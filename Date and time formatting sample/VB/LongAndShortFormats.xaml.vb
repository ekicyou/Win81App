﻿'*********************************************************
'
' Copyright (c) Microsoft. All rights reserved.
' THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
' IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
' PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
'
'*********************************************************

Imports System.Text
Imports Windows.Globalization
Imports Windows.Globalization.DateTimeFormatting

''' <summary>
''' An empty page that can be used on its own or navigated to within a Frame.
''' </summary>
Partial Public NotInheritable Class LongAndShortFormats
    Inherits Global.SDKTemplate.Common.LayoutAwarePage

    ' A pointer back to the main page.  This is needed if you want to call methods in MainPage such
    ' as NotifyUser()
    Private rootPage As MainPage = MainPage.Current

    Public Sub New()
        Me.InitializeComponent()
    End Sub

    ''' <summary>
    ''' Invoked when this page is about to be displayed in a Frame.
    ''' </summary>
    ''' <param name="e">Event data that describes how this page was reached.  The Parameter
    ''' property is typically used to configure the page.</param>
    Protected Overrides Sub OnNavigatedTo(ByVal e As NavigationEventArgs)
    End Sub


    ''' <summary>
    ''' This is the click handler for the 'Default' button.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    Private Sub Display_Click(ByVal sender As Object, ByVal e As RoutedEventArgs)
        ' This scenario uses the Windows.Globalization.DateTimeFormatting.DateTimeFormatter class
        ' in order to display dates and times using basic formatters.

        ' We keep results in this variable
        Dim results As New StringBuilder()
        results.AppendLine("Current application context language: " & ApplicationLanguages.Languages(0))
        results.AppendLine()

        ' Create basic date/time formatters.
        Dim basicFormatters() As DateTimeFormatter = { _
            New DateTimeFormatter("shortdate"), _
            New DateTimeFormatter("longdate"), _
            New DateTimeFormatter("shorttime"), _
            New DateTimeFormatter("longtime") _
        }

        ' Create date/time to format and display.
        Dim dateTime As Date = Date.Now

        ' Try to format and display date/time if calendar supports it.
        For Each formatter As DateTimeFormatter In basicFormatters
            Try
                ' Format and display date/time.
                results.AppendLine(formatter.Template & ": " & formatter.Format(dateTime))
            Catch e1 As ArgumentException
                ' Retrieve and display formatter properties. 
                results.AppendLine(String.Format("Unable to format Gregorian DateTime {0} using formatter with template {1} for languages [{2}], region {3}, calendar {4} and clock {5}", dateTime, formatter.Template, String.Join(",", formatter.Languages), formatter.GeographicRegion, formatter.Calendar, formatter.Clock))
            End Try
        Next formatter

        ' Display the results
        rootPage.NotifyUser(results.ToString(), NotifyType.StatusMessage)
    End Sub
End Class
