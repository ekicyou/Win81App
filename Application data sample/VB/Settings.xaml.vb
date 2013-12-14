'*********************************************************
'
' Copyright (c) Microsoft. All rights reserved.
' THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
' IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
' PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
'
'*********************************************************

Imports Windows.Storage

''' <summary>
''' An empty page that can be used on its own or navigated to within a Frame.
''' </summary>
Partial Public NotInheritable Class Settings
    Inherits Global.SDKTemplate.Common.LayoutAwarePage

    ' A pointer back to the main page.  This is needed if you want to call methods in MainPage such
    ' as NotifyUser()
    Private rootPage As MainPage = MainPage.Current
    Private roamingSettings As ApplicationDataContainer = Nothing

    Private Const SettingName As String = "exampleSetting"

    Public Sub New()
        Me.InitializeComponent()

        roamingSettings = ApplicationData.Current.RoamingSettings

        DisplayOutput()
    End Sub

    ' Guidance for Settings.
    '
    ' Settings are a convenient way of storing small pieces of configuration data
    ' for your application.
    '
    ' Settings can be either Local or Roaming.
    '
    ' Roaming settings will be synchronized across machines on which the user has
    ' signed in with a Microsoft Account.  Roaming of settings is not instant; the
    ' system weighs several factors when determining when to send the data.  Usage
    ' of roaming data should be kept below the quota (available via the 
    ' RoamingStorageQuota property), or else roaming of data will be suspended.
    '
    ' User preferences for your application are a great match for roaming settings.
    ' User preferences are usually fixed in number and small in size.  Users will
    ' appreciated that your application is customized the way they prefer across
    ' all of their machines.
    '
    ' Local settings are not synchronized and remain on the machine on which they
    ' were originally written.
    '
    ' Care should be taken to guard against an excessive volume of data being
    ' stored in settings.  Settings are not intended to be used as a database.
    ' Large data sets will take longer to load from disk during your application's
    ' launch.

    ' This sample illustrates reading and writing from a roaming setting, though a
    ' local setting could be used just as easily.

    Private Sub WriteSetting_Click(ByVal sender As Object, ByVal e As RoutedEventArgs)
        roamingSettings.Values(SettingName) = "Hello World" ' example value

        DisplayOutput()
    End Sub

    Private Sub DeleteSetting_Click(ByVal sender As Object, ByVal e As RoutedEventArgs)
        roamingSettings.Values.Remove(SettingName)

        DisplayOutput()
    End Sub

    Private Sub DisplayOutput()
        Dim value As Object = roamingSettings.Values(SettingName)

        OutputTextBlock.Text = String.Format("Setting: {0}", (If(value Is Nothing, "<empty>", ("""" & CStr(value) & """"))))
    End Sub

    ''' <summary>
    ''' Invoked when this page is about to be displayed in a Frame.
    ''' </summary>
    ''' <param name="e">Event data that describes how this page was reached.  The Parameter
    ''' property is typically used to configure the page.</param>
    Protected Overrides Sub OnNavigatedTo(ByVal e As NavigationEventArgs)
    End Sub
End Class

