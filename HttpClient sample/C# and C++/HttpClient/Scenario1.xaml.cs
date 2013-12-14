﻿//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

using SDKTemplate;
using System;
using System.Threading;
using System.Threading.Tasks;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Navigation;
using Windows.Web.Http;
using Windows.Web.Http.Filters;

namespace Microsoft.Samples.Networking.HttpClientSample
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class Scenario1 : SDKTemplate.Common.LayoutAwarePage, IDisposable
    {
        // A pointer back to the main page. This is needed if you want to call methods in MainPage such
        // as NotifyUser()
        MainPage rootPage = MainPage.Current;

        private HttpBaseProtocolFilter filter;
        private HttpClient httpClient;
        private CancellationTokenSource cts;

        public Scenario1()
        {
            this.InitializeComponent();
        }

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.  The Parameter
        /// property is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {    
            // In this scenario we just create an HttpClient instance with default settings. I.e. no custom filters. 
            // For examples on how to use custom filters see other scenarios.
            filter = new HttpBaseProtocolFilter();
            httpClient = new HttpClient(filter);
            cts = new CancellationTokenSource();
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            Dispose();
        }

        private async void Start_Click(object sender, RoutedEventArgs e)
        {
            // The value of 'AddressField' is set by the user and is therefore untrusted input. If we can't create a
            // valid, absolute URI, we'll notify the user about the incorrect input.
            // Note that this app has both "Internet (Client)" and "Home and Work Networking" capabilities set,
            // since the user may provide URIs for servers located on the intErnet or intrAnet. If apps only
            // communicate with servers on the intErnet, only the "Internet (Client)" capability should be set.
            // Similarly if an app is only intended to communicate on the intrAnet, only the "Home and Work
            // Networking" capability should be set.
            Uri resourceUri;
            if (!Uri.TryCreate(AddressField.Text.Trim(), UriKind.Absolute, out resourceUri))
            {
                rootPage.NotifyUser("Invalid URI.", NotifyType.ErrorMessage);
                return;
            }

            if (resourceUri.Scheme != "http" && resourceUri.Scheme != "https")
            {
                rootPage.NotifyUser("Only 'http' and 'https' schemes supported.", NotifyType.ErrorMessage);
                return;
            }

            Helpers.ScenarioStarted(StartButton, CancelButton, OutputField);
            rootPage.NotifyUser("In progress", NotifyType.StatusMessage);

            try
            {
                if (ReadDefaultRadio.IsChecked.Value)
                {
                    filter.CacheControl.ReadBehavior = HttpCacheReadBehavior.Default;
                }
                else if (ReadMostRecentRadio.IsChecked.Value)
                {
                    filter.CacheControl.ReadBehavior = HttpCacheReadBehavior.MostRecent;
                }
                else if (ReadOnlyFromCacheRadio.IsChecked.Value)
                {
                    filter.CacheControl.ReadBehavior = HttpCacheReadBehavior.OnlyFromCache;
                }

                if (WriteDefaultRadio.IsChecked.Value)
                {
                    filter.CacheControl.WriteBehavior = HttpCacheWriteBehavior.Default;
                }
                else if (WriteNoCacheRadio.IsChecked.Value)
                {
                    filter.CacheControl.WriteBehavior = HttpCacheWriteBehavior.NoCache;
                }

                HttpResponseMessage response = await httpClient.GetAsync(resourceUri).AsTask(cts.Token);

                await Helpers.DisplayTextResultAsync(response, OutputField, cts.Token);

                rootPage.NotifyUser(
                    "Completed. Response came from " + response.Source + ".",
                    NotifyType.StatusMessage);
            }
            catch (TaskCanceledException)
            {
                rootPage.NotifyUser("Request canceled.", NotifyType.ErrorMessage);
            }
            catch (Exception ex)
            {
                rootPage.NotifyUser("Error: " + ex.Message, NotifyType.ErrorMessage);
            }
            finally
            {
                Helpers.ScenarioCompleted(StartButton, CancelButton);
            }
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            cts.Cancel();
            cts.Dispose();

            // Re-create the CancellationTokenSource.
            cts = new CancellationTokenSource();
        }

        public void Dispose()
        {
            if (filter != null)
            {
                filter.Dispose();
                filter = null;
            }

            if (httpClient != null)
            {
                httpClient.Dispose();
                httpClient = null;
            }

            if (cts != null)
            {
                cts.Dispose();
                cts = null;
            }
        }
    }
}
