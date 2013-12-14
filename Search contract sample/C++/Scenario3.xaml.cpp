//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

//
// Scenario3.xaml.cpp
// Implementation of the Scenario3 class
//

#include "pch.h"
#include "Scenario3.xaml.h"

using namespace SDKSample::SearchContract;

using namespace std;
using namespace Platform;
using namespace Windows::ApplicationModel::Search;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

Scenario3::Scenario3()
{
    InitializeComponent();
    searchPane = SearchPane::GetForCurrentView();
}

void Scenario3::OnNavigatedTo(NavigationEventArgs^ e)
{
    MainPage::Current->NotifyUser("Use the search pane to submit a query", NotifyType::StatusMessage);
    // This event should be registered when your app first creates its main window in App::OnWindowCreated().
    token = searchPane->SuggestionsRequested += ref new TypedEventHandler<SearchPane^, SearchPaneSuggestionsRequestedEventArgs^>(this, &Scenario3::OnSearchPaneSuggestionsRequested);
}

void Scenario3::OnNavigatedFrom(NavigationEventArgs^ e)
{
    searchPane->SuggestionsRequested -= token;
}

void Scenario3::OnSearchPaneSuggestionsRequested(SearchPane^ sender, SearchPaneSuggestionsRequestedEventArgs^ e)
{
    // List of Japanese city/ward names
    static wstring suggestionList[] =
        {
            L"\u7279\u5225\u533a\u90e8", L"\u6a2a\u6d5c\u5e02", L"\u5927\u962a\u5e02", L"\u540d\u53e4\u5c4b\u5e02", L"\u672d\u5e4c\u5e02", L"\u795e\u6238\u5e02",
            L"\u4eac\u90fd\u5e02", L"\u798f\u5ca1\u5e02", L"\u5ddd\u5d0e\u5e02", L"\u3055\u3044\u305f\u307e\u5e02", L"\u5e83\u5cf6\u5e02", L"\u4ed9\u53f0\u5e02",
            L"\u5317\u4e5d\u5dde\u5e02", L"\u5343\u8449\u5e02", L"\u4e16\u7530\u8c37\u533a", L"\u583a\u5e02", L"\u65b0\u6f5f\u5e02", L"\u6d5c\u677e\u5e02",
            L"\u718a\u672c\u5e02", L"\u76f8\u6a21\u539f\u5e02", L"\u7df4\u99ac\u533a", L"\u9759\u5ca1\u5e02", L"\u5ca1\u5c71\u5e02", L"\u5927\u7530\u533a",
            L"\u8db3\u7acb\u533a", L"\u6c5f\u6238\u5ddd\u533a", L"\u8239\u6a4b\u5e02", L"\u9e7f\u5150\u5cf6\u5e02", L"\u516b\u738b\u5b50\u5e02", L"\u6749\u4e26\u533a",
            L"\u59eb\u8def\u5e02", L"\u677f\u6a4b\u533a", L"\u677e\u5c71\u5e02", L"\u5b87\u90fd\u5bae\u5e02", L"\u6771\u5927\u962a\u5e02", L"\u5ddd\u53e3\u5e02",
            L"\u677e\u6238\u5e02", L"\u897f\u5bae\u5e02", L"\u5009\u6577\u5e02", L"\u5e02\u5ddd\u5e02", L"\u5927\u5206\u5e02", L"\u91d1\u6ca2\u5e02",
            L"\u798f\u5c71\u5e02", L"\u6c5f\u6771\u533a", L"\u5c3c\u5d0e\u5e02", L"\u9577\u5d0e\u5e02", L"\u845b\u98fe\u533a", L"\u753a\u7530\u5e02",
            L"\u5bcc\u5c71\u5e02", L"\u8c4a\u7530\u5e02", L"\u9ad8\u677e\u5e02", L"\u6a2a\u9808\u8cc0\u5e02", L"\u5c90\u961c\u5e02", L"\u85e4\u6ca2\u5e02",
            L"\u679a\u65b9\u5e02", L"\u67cf\u5e02", L"\u5bae\u5d0e\u5e02", L"\u8c4a\u4e2d\u5e02", L"\u9577\u91ce\u5e02", L"\u8c4a\u6a4b\u5e02",
            L"\u4e00\u5bae\u5e02", L"\u5ca1\u5d0e\u5e02", L"\u9ad8\u5d0e\u5e02", L"\u548c\u6b4c\u5c71\u5e02", L"\u5948\u826f\u5e02", L"\u54c1\u5ddd\u533a",
            L"\u9ad8\u69fb\u5e02", L"\u5439\u7530\u5e02", L"\u65ed\u5ddd\u5e02", L"\u9ad8\u77e5\u5e02", L"\u5ddd\u8d8a\u5e02", L"\u3044\u308f\u304d\u5e02",
            L"\u6240\u6ca2\u5e02", L"\u524d\u6a4b\u5e02", L"\u90e1\u5c71\u5e02", L"\u5927\u6d25\u5e02", L"\u5317\u533a", L"\u8d8a\u8c37\u5e02",
            L"\u65b0\u5bbf\u533a", L"\u79cb\u7530\u5e02", L"\u90a3\u8987\u5e02", L"\u4e2d\u91ce\u533a", L"\u56db\u65e5\u5e02\u5e02", L"\u6625\u65e5\u4e95\u5e02",
            L"\u4e45\u7559\u7c73\u5e02", L"\u9752\u68ee\u5e02", L"\u76db\u5ca1\u5e02", L"\u798f\u5cf6\u5e02", L"\u660e\u77f3\u5e02", L"\u6d25\u5e02",
            L"\u8c4a\u5cf6\u533a", L"\u9577\u5ca1\u5e02", L"\u4e0b\u95a2\u5e02", L"\u5e02\u539f\u5e02", L"\u51fd\u9928\u5e02", L"\u8328\u6728\u5e02",
            L"\u6c34\u6238\u5e02", L"\u76ee\u9ed2\u533a", L"\u516b\u5c3e\u5e02", L"\u52a0\u53e4\u5ddd\u5e02", L"\u798f\u4e95\u5e02", L"\u5fb3\u5cf6\u5e02",
            L"\u4f50\u4e16\u4fdd\u5e02", L"\u5e73\u585a\u5e02", L"\u5e9c\u4e2d\u5e02", L"\u5c71\u5f62\u5e02", L"\u5bcc\u58eb\u5e02", L"\u58a8\u7530\u533a",
            L"\u8349\u52a0\u5e02", L"\u677e\u672c\u5e02", L"\u5449\u5e02", L"\u5bdd\u5c4b\u5ddd\u5e02", L"\u4f50\u8cc0\u5e02", L"\u516b\u6238\u5e02",
            L"\u6625\u65e5\u90e8\u5e02", L"\u8305\u30f6\u5d0e\u5e02", L"\u5927\u548c\u5e02", L"\u5b9d\u585a\u5e02", L"\u539a\u6728\u5e02", L"\u4e0a\u5c3e\u5e02",
            L"\u8abf\u5e03\u5e02", L"\u592a\u7530\u5e02", L"\u3064\u304f\u3070\u5e02", L"\u4f0a\u52e2\u5d0e\u5e02", L"\u6587\u4eac\u533a", L"\u6e2f\u533a",
            L"\u6e0b\u8c37\u533a", L"\u8352\u5ddd\u533a", L"\u4e0a\u8d8a\u5e02", L"\u718a\u8c37\u5e02", L"\u6cbc\u6d25\u5e02", L"\u9234\u9e7f\u5e02",
            L"\u5cb8\u548c\u7530\u5e02", L"\u7532\u5e9c\u5e02", L"\u5c0f\u7530\u539f\u5e02", L"\u9ce5\u53d6\u5e02", L"\u5c71\u53e3\u5e02", L"\u897f\u6771\u4eac\u5e02",
            L"\u4f0a\u4e39\u5e02", L"\u677e\u6c5f\u5e02", L"\u65e5\u7acb\u5e02", L"\u6771\u5e83\u5cf6\u5e02", L"\u516b\u5343\u4ee3\u5e02", L"\u5b87\u6cbb\u5e02",
            L"\u5c0f\u5e73\u5e02", L"\u4e09\u9df9\u5e02", L"\u548c\u6cc9\u5e02", L"\u5f18\u524d\u5e02", L"\u8c4a\u5ddd\u5e02", L"\u91e7\u8def\u5e02",
            L"\u7acb\u5ddd\u5e02", L"\u65e5\u91ce\u5e02", L"\u5b89\u57ce\u5e02", L"\u9ad8\u5ca1\u5e02", L"\u53f0\u6771\u533a", L"\u938c\u5009\u5e02",
            L"\u5b87\u90e8\u5e02", L"\u82eb\u5c0f\u7267\u5e02", L"\u4f50\u5009\u5e02", L"\u79e6\u91ce\u5e02", L"\u90fd\u57ce\u5e02", L"\u78d0\u7530\u5e02",
            L"\u677e\u962a\u5e02", L"\u5e2f\u5e83\u5e02", L"\u4eca\u6cbb\u5e02", L"\u897f\u5c3e\u5e02", L"\u6d66\u5b89\u5e02", L"\u5c0f\u5c71\u5e02",
            L"\u7fd2\u5fd7\u91ce\u5e02", L"\u6d41\u5c71\u5e02", L"\u5927\u57a3\u5e02", L"\u77f3\u5dfb\u5e02", L"\u4e0a\u7530\u5e02", L"\u65b0\u5ea7\u5e02",
            L"\u3072\u305f\u3061\u306a\u304b\u5e02", L"\u5ddd\u897f\u5e02", L"\u72ed\u5c71\u5e02", L"\u91ce\u7530\u5e02", L"\u8db3\u5229\u5e02",
            L"\u4e45\u559c\u5e02", L"\u6771\u6751\u5c71\u5e02", L"\u5165\u9593\u5e02", L"\u5468\u5357\u5e02", L"\u7c73\u5b50\u5e02", L"\u591a\u6469\u5e02",
            L"\u5c0f\u7267\u5e02", L"\u5b88\u53e3\u5e02", L"\u5208\u8c37\u5e02", L"\u5404\u52d9\u539f\u5e02", L"\u5c3e\u9053\u5e02", L"\u6df1\u8c37\u5e02",
            L"\u5ca9\u56fd\u5e02", L"\u51fa\u96f2\u5e02", L"\u713c\u6d25\u5e02", L"\u571f\u6d66\u5e02", L"\u53e4\u6cb3\u5e02", L"\u85e4\u679d\u5e02",
            L"\u8aeb\u65e9\u5e02", L"\u6851\u540d\u5e02", L"\u6803\u6728\u5e02", L"\u9752\u6885\u5e02", L"\u6b66\u8535\u91ce\u5e02", L"\u9db4\u5ca1\u5e02",
            L"\u7a32\u6ca2\u5e02", L"\u5927\u5d0e\u5e02", L"\u6211\u5b6b\u5b50\u5e02", L"\u516b\u4ee3\u5e02", L"\u702c\u6238\u5e02", L"\u5bcc\u58eb\u5bae\u5e02",
            L"\u5c0f\u6a3d\u5e02", L"\u98ef\u585a\u5e02", L"\u4e09\u90f7\u5e02", L"\u5ef6\u5ca1\u5e02", L"\u8349\u6d25\u5e02", L"\u9580\u771f\u5e02",
            L"\u4f0a\u52e2\u5e02", L"\u6c96\u7e04\u5e02", L"\u7b95\u9762\u5e02", L"\u671d\u971e\u5e02", L"\u6728\u66f4\u6d25\u5e02", L"\u5ea7\u9593\u5e02",
            L"\u6210\u7530\u5e02", L"\u6d77\u8001\u540d\u5e02", L"\u9727\u5cf6\u5e02", L"\u5927\u6771\u5e02", L"\u5510\u6d25\u5e02", L"\u4f1a\u6d25\u82e5\u677e\u5e02",
            L"\u5317\u898b\u5e02", L"\u6a7f\u539f\u5e02", L"\u5225\u5e9c\u5e02", L"\u5965\u5dde\u5e02", L"\u677e\u539f\u5e02", L"\u9577\u6d5c\u5e02",
            L"\u6c5f\u5225\u5e02", L"\u5927\u725f\u7530\u5e02", L"\u6238\u7530\u5e02", L"\u4e2d\u592e\u533a", L"\u65b0\u5c45\u6d5c\u5e02", L"\u6850\u751f\u5e02",
            L"\u4f50\u91ce\u5e02", L"\u56fd\u5206\u5bfa\u5e02", L"\u9d3b\u5de3\u5e02", L"\u5bcc\u7530\u6797\u5e02", L"\u5c0f\u91d1\u4e95\u5e02",
            L"\u534a\u7530\u5e02", L"\u4e00\u95a2\u5e02", L"\u751f\u99d2\u5e02", L"\u90a3\u9808\u5869\u539f\u5e02", L"\u7fbd\u66f3\u91ce\u5e02",
            L"\u3046\u308b\u307e\u5e02", L"\u9632\u5e9c\u5e02", L"\u6771\u4e45\u7559\u7c73\u5e02", L"\u639b\u5ddd\u5e02", L"\u6771\u8fd1\u6c5f\u5e02",
            L"\u52a0\u9808\u5e02", L"\u4e09\u7530\u5e02", L"\u5eff\u65e5\u5e02\u5e02", L"\u591a\u6cbb\u898b\u5e02", L"\u6cb3\u5185\u9577\u91ce\u5e02",
            L"\u662d\u5cf6\u5e02", L"\u897f\u6761\u5e02", L"\u5f66\u6839\u5e02", L"\u4e09\u5cf6\u5e02", L"\u9152\u7530\u5e02", L"\u767d\u5c71\u5e02",
            L"\u4e38\u4e80\u5e02", L"\u6d66\u6dfb\u5e02", L"\u53d6\u624b\u5e02", L"\u7b51\u897f\u5e02", L"\u5c0f\u677e\u5e02", L"\u938c\u30b1\u8c37\u5e02",
            L"\u6771\u6d77\u5e02", L"\u6625\u65e5\u5e02", L"\u5bcc\u58eb\u898b\u5e02", L"\u6d25\u5c71\u5e02", L"\u3075\u3058\u307f\u91ce\u5e02",
            L"\u98ef\u7530\u5e02", L"\u9e7f\u5c4b\u5e02", L"\u6c60\u7530\u5e02", L"\u9e7f\u6cbc\u5e02", L"\u4e09\u6761\u5e02", L"\u5742\u6238\u5e02",
            L"\u82b1\u5dfb\u5e02", L"\u65b0\u767a\u7530\u5e02", L"\u4f0a\u52e2\u539f\u5e02", L"\u6cc9\u4f50\u91ce\u5e02", L"\u4f50\u4e45\u5e02",
            L"\u4e09\u539f\u5e02", L"\u5cf6\u7530\u5e02", L"\u7b51\u7d2b\u91ce\u5e02", L"\u6c5f\u5357\u5e02", L"\u85a9\u6469\u5ddd\u5185\u5e02",
            L"\u7cf8\u5cf6\u5e02", L"\u6a2a\u624b\u5e02", L"\u53ef\u5150\u5e02", L"\u4f0a\u8cc0\u5e02", L"\u5b89\u66c7\u91ce\u5e02", L"\u5b97\u50cf\u5e02",
            L"\u5927\u91ce\u57ce\u5e02", L"\u795e\u6816\u5e02", L"\u5ba4\u862d\u5e02", L"\u9ad8\u7802\u5e02", L"\u5343\u6b73\u5e02", L"\u5c04\u6c34\u5e02",
            L"\u82a6\u5c4b\u5e02", L"\u5317\u4e0a\u5e02", L"\u8302\u539f\u5e02", L"\u9ad8\u5c71\u5e02", L"\u7532\u8cc0\u5e02", L"\u4e80\u5ca1\u5e02",
            L"\u5742\u4e95\u5e02", L"\u5b9c\u91ce\u6e7e\u5e02", L"\u67cf\u5d0e\u5e02", L"\u95a2\u5e02", L"\u8c9d\u585a\u5e02", L"\u5927\u6751\u5e02",
            L"\u5ca9\u898b\u6ca2\u5e02", L"\u6771\u677e\u5c71\u5e02", L"\u65e5\u5149\u5e02", L"\u56db\u56fd\u4e2d\u592e\u5e02", L"\u7c73\u6ca2\u5e02",
            L"\u541b\u6d25\u5e02", L"\u5929\u8349\u5e02", L"\u5fa1\u6bbf\u5834\u5e02", L"\u5927\u548c\u90e1\u5c71\u5e02", L"\u821e\u9db4\u5e02",
            L"\u5927\u4ed9\u5e02", L"\u5370\u897f\u5e02", L"\u56db\u8857\u9053\u5e02", L"\u3042\u307e\u5e02", L"\u884c\u7530\u5e02", L"\u8d8a\u524d\u5e02",
            L"\u8c4a\u5ca1\u5e02", L"\u5927\u5e9c\u5e02", L"\u7531\u5229\u672c\u8358\u5e02", L"\u888b\u4e95\u5e02", L"\u7a32\u57ce\u5e02", L"\u77e5\u591a\u5e02",
            L"\u4e2d\u6d25\u5e02", L"\u5b87\u548c\u5cf6\u5e02", L"\u65e5\u9032\u5e02", L"\u767b\u7c73\u5e02", L"\u6442\u6d25\u5e02", L"\u98ef\u80fd\u5e02",
            L"\u6e0b\u5ddd\u5e02", L"\u7dbe\u702c\u5e02", L"\u6771\u5927\u548c\u5e02", L"\u516b\u6f6e\u5e02", L"\u9999\u53d6\u5e02", L"\u771f\u5ca1\u5e02",
            L"\u84b2\u90e1\u5e02", L"\u672c\u5e84\u5e02", L"\u71d5\u5e02", L"\u8fd1\u6c5f\u516b\u5e61\u5e02", L"\u725b\u4e45\u5e02", L"\u5317\u540d\u53e4\u5c4b\u5e02",
            L"\u5c3e\u5f35\u65ed\u5e02", L"\u4e09\u6728\u5e02", L"\u4e2d\u6d25\u5ddd\u5e02", L"\u3042\u304d\u308b\u91ce\u5e02", L"\u548c\u5149\u5e02",
            L"\u305f\u3064\u306e\u5e02", L"\u9f8d\u30b1\u5d0e\u5e02", L"\u540d\u5f35\u5e02", L"\u57ce\u967d\u5e02", L"\u9577\u5ca1\u4eac\u5e02", L"\u77f3\u5ca1\u5e02",
            L"\u798f\u77e5\u5c71\u5e02", L"\u7b20\u9593\u5e02", L"\u9808\u8cc0\u5ddd\u5e02", L"\u7530\u8fba\u5e02", L"\u5927\u9928\u5e02", L"\u72db\u6c5f\u5e02",
            L"\u9928\u6797\u5e02", L"\u4ea4\u91ce\u5e02", L"\u5927\u7530\u539f\u5e02", L"\u6cc9\u5927\u6d25\u5e02", L"\u4f50\u4f2f\u5e02", L"\u5b88\u5c71\u5e02",
            L"\u963f\u5357\u5e02", L"\u56fd\u7acb\u5e02", L"\u9999\u829d\u5e02", L"\u72ac\u5c71\u5e02", L"\u6817\u539f\u5e02", L"\u67cf\u539f\u5e02",
            L"\u59f6\u826f\u5e02", L"\u6876\u5ddd\u5e02", L"\u516b\u5e61\u5e02", L"\u6e05\u702c\u5e02", L"\u7532\u6590\u5e02", L"\u6c17\u4ed9\u6cbc\u5e02",
            L"\u516b\u8857\u5e02", L"\u540d\u53d6\u5e02", L"\u5357\u30a2\u30eb\u30d7\u30b9\u5e02", L"\u78a7\u5357\u5e02", L"\u52a0\u8cc0\u5e02",
            L"\u8568\u5e02", L"\u4f0a\u6771\u5e02", L"\u67f3\u5ddd\u5e02", L"\u4f0a\u90a3\u5e02", L"\u65e5\u7530\u5e02", L"\u5357\u76f8\u99ac\u5e02",
            L"\u7b1b\u5439\u5e02", L"\u592a\u5bb0\u5e9c\u5e02", L"\u884c\u6a4b\u5e02", L"\u929a\u5b50\u5e02", L"\u6b66\u8535\u6751\u5c71\u5e02",
            L"\u9db4\u30f6\u5cf6\u5e02", L"\u6728\u6d25\u5ddd\u5e02", L"\u8c4a\u660e\u5e02", L"\u5fd7\u6728\u5e02", L"\u7389\u540d\u5e02", L"\u6075\u5ead\u5e02",
            L"\u5929\u7406\u5e02", L"\u65ed\u5e02", L"\u9ce5\u6816\u5e02", L"\u516b\u5973\u5e02", L"\u5317\u672c\u5e02", L"\u4e09\u8c4a\u5e02",
            L"\u5927\u548c\u9ad8\u7530\u5e02", L"\u77e5\u7acb\u5e02", L"\u85e4\u5ca1\u5e02", L"\u4eac\u7530\u8fba\u5e02", L"\u4e39\u6ce2\u5e02",
            L"\u6566\u8cc0\u5e02", L"\u5869\u5c3b\u5e02", L"\u9bd6\u6c5f\u5e02", L"\u7fbd\u5cf6\u5e02", L"\u79e9\u7236\u5e02", L"\u6751\u4e0a\u5e02",
            L"\u6a4b\u672c\u5e02", L"\u7dcf\u793e\u5e02", L"\u85e4\u4e95\u5bfa\u5e02", L"\u5341\u548c\u7530\u5e02", L"\u4f0a\u9054\u5e02", L"\u9e7f\u5d8b\u5e02",
            L"\u6e05\u9808\u5e02", L"\u7d00\u306e\u5ddd\u5e02", L"\u5e38\u7dcf\u5e02", L"\u5409\u5ddd\u5e02", L"\u6d25\u5cf6\u5e02", L"\u611b\u897f\u5e02",
            L"\u767d\u6cb3\u5e02", L"\u5c71\u967d\u5c0f\u91ce\u7530\u5e02", L"\u7389\u91ce\u5e02", L"\u6cc9\u5357\u5e02", L"\u7530\u539f\u5e02",
            L"\u6817\u6771\u5e02", L"\u84ee\u7530\u5e02", L"\u65e5\u5411\u5e02", L"\u591a\u8cc0\u57ce\u5e02", L"\u4f50\u6e21\u5e02", L"\u89b3\u97f3\u5bfa\u5e02",
            L"\u5b88\u8c37\u5e02", L"\u5929\u7ae5\u5e02", L"\u5343\u66f2\u5e02", L"\u5b87\u57ce\u5e02", L"\u6771\u91d1\u5e02", L"\u6d5c\u7530\u5e02",
            L"\u5357\u9b5a\u6cbc\u5e02", L"\u9cf4\u9580\u5e02", L"\u3080\u3064\u5e02", L"\u5b89\u4e2d\u5e02", L"\u9ce9\u30f6\u8c37\u5e02", L"\u571f\u5c90\u5e02",
            L"\u5317\u5e83\u5cf6\u5e02", L"\u8896\u30b1\u6d66\u5e02", L"\u767d\u4e95\u5e02", L"\u540d\u8b77\u5e02", L"\u685c\u4e95\u5e02",
            L"\u307f\u3088\u3057\u5e02", L"\u6e56\u897f\u5e02", L"\u4e8c\u672c\u677e\u5e02", L"\u798f\u751f\u5e02", L"\u9ad8\u77f3\u5e02", L"\u4e0b\u91ce\u5e02",
            L"\u77f3\u72e9\u5e02", L"\u5bae\u53e4\u5e02", L"\u80fd\u4ee3\u5e02", L"\u4eac\u4e39\u5f8c\u5e02", L"\u5b87\u4f50\u5e02", L"\u5341\u65e5\u753a\u5e02",
            L"\u5c0f\u90e1\u5e02", L"\u4e94\u6240\u5ddd\u539f\u5e02", L"\u9017\u5b50\u5e02", L"\u5927\u962a\u72ed\u5c71\u5e02", L"\u53e4\u8cc0\u5e02",
            L"\u4e03\u5c3e\u5e02", L"\u65e5\u5357\u5e02", L"\u76f4\u65b9\u5e02", L"\u56db\u689d\u7577\u5e02", L"\u65e5\u9ad8\u5e02", L"\u7cf8\u6e80\u5e02",
            L"\u8c4a\u898b\u57ce\u5e02", L"\u4f0a\u4e07\u91cc\u5e02", L"\u7fbd\u6751\u5e02", L"\u962a\u5357\u5e02", L"\u4e09\u6b21\u5e02", L"\u5869\u7ac8\u5e02",
            L"\u8305\u91ce\u5e02", L"\u671d\u5009\u5e02", L"\u5e38\u9678\u592a\u7530\u5e02", L"\u7fbd\u751f\u5e02", L"\u5742\u6771\u5e02", L"\u5c71\u6b66\u5e02",
            L"\u5742\u51fa\u5e02", L"\u51fa\u6c34\u5e02", L"\u798f\u6d25\u5e02", L"\u5c71\u9e7f\u5e02", L"\u8352\u5c3e\u5e02", L"\u4e0b\u677e\u5e02",
            L"\u5408\u5fd7\u5e02", L"\u5e38\u6ed1\u5e02", L"\u6d77\u5357\u5e02", L"\u7f8e\u6fc3\u52a0\u8302\u5e02", L"\u5357\u783a\u5e02", L"\u5fd7\u6469\u5e02",
            L"\u6e56\u5357\u5e02", L"\u4e94\u6cc9\u5e02", L"\u88fe\u91ce\u5e02", L"\u5411\u65e5\u5e02", L"\u7b20\u5ca1\u5e02", L"\u90a3\u73c2\u5e02",
            L"\u5e78\u624b\u5e02", L"\u8429\u5e02", L"\u6075\u90a3\u5e02", L"\u3055\u306c\u304d\u5e02", L"\u5149\u5e02", L"\u5ca9\u51fa\u5e02", L"\u5ca1\u8c37\u5e02",
            L"\u7d50\u57ce\u5e02", L"\u9ad8\u5cf6\u5e02", L"\u559c\u591a\u65b9\u5e02", L"\u5c0f\u7f8e\u7389\u5e02", L"\u9808\u5742\u5e02", L"\u5bcc\u5ca1\u5e02",
            L"\u5bae\u53e4\u5cf6\u5e02", L"\u745e\u7a42\u5e02", L"\u307f\u3069\u308a\u5e02", L"\u6c37\u898b\u5e02", L"\u767b\u5225\u5e02", L"\u6cbc\u7530\u5e02",
            L"\u8acf\u8a2a\u5e02", L"\u5bcc\u91cc\u5e02", L"\u4e80\u5c71\u5e02", L"\u6e6f\u6ca2\u5e02", L"\u65e5\u7f6e\u5e02", L"\u5009\u5409\u5e02",
            L"\u6b66\u96c4\u5e02", L"\u5bcc\u58eb\u5409\u7530\u5e02", L"\u7530\u5ddd\u5e02", L"\u8d64\u7a42\u5e02", L"\u5357\u5cf6\u539f\u5e02",
            L"\u83ca\u6c60\u5e02", L"\u927e\u7530\u5e02", L"\u76ca\u7530\u5e02", L"\u91ce\u6d32\u5e02", L"\u65b0\u57ce\u5e02", L"\u5357\u3042\u308f\u3058\u5e02",
            L"\u5c0f\u91ce\u5e02", L"\u5357\u56fd\u5e02", L"\u783a\u6ce2\u5e02", L"\u9928\u5c71\u5e02", L"\u4f0a\u8c46\u306e\u56fd\u5e02",
            L"\u7267\u4e4b\u539f\u5e02", L"\u771f\u5ead\u5e02", L"\u80fd\u7f8e\u5e02", L"\u7b51\u5f8c\u5e02", L"\u4e09\u6d66\u5e02", L"\u5c0f\u6797\u5e02",
            L"\u5bcc\u6d25\u5e02", L"\u52a0\u897f\u5e02", L"\u5317\u6597\u5e02", L"\u7cf8\u9b5a\u5ddd\u5e02", L"\u5cf6\u539f\u5e02", L"\u5ca9\u5009\u5e02",
            L"\u6d32\u672c\u5e02", L"\u96f2\u4ed9\u5e02", L"\u5927\u6d32\u5e02", L"\u5343\u4ee3\u7530\u533a", L"\u83ca\u5ddd\u5e02", L"\u5317\u8328\u57ce\u5e02",
            L"\u77f3\u57a3\u5e02", L"\u7a32\u6577\u5e02", L"\u5317\u675c\u5e02", L"\u6de1\u8def\u5e02", L"\u6771\u6839\u5e02", L"\u5944\u7f8e\u5e02",
            L"\u685c\u5ddd\u5e02", L"\u3044\u306a\u3079\u5e02", L"\u4e2d\u91ce\u5e02", L"\u963f\u8cc0\u91ce\u5e02", L"\u5e38\u9678\u5927\u5bae\u5e02",
            L"\u5c0f\u57ce\u5e02", L"\u4e0b\u59bb\u5e02", L"\u9b5a\u6d25\u5e02", L"\u3055\u304f\u3089\u5e02", L"\u90e1\u4e0a\u5e02",
            L"\u3064\u304f\u3070\u307f\u3089\u3044\u5e02", L"\u6307\u5bbf\u5e02", L"\u4e2d\u9593\u5e02", L"\u5ca9\u6cbc\u5e02", L"\u5409\u91ce\u5ddd\u5e02",
            L"\u5c0f\u8af8\u5e02", L"\u9ad8\u6d5c\u5e02", L"\u4e95\u539f\u5e02", L"\u5357\u8db3\u67c4\u5e02", L"\u304b\u3059\u307f\u304c\u3046\u3089\u5e02",
            L"\u8d64\u78d0\u5e02", L"\u5f25\u5bcc\u5e02", L"\u7be0\u5c71\u5e02", L"\u6edd\u5ddd\u5e02", L"\u6771\u677e\u5cf6\u5e02", L"\u897f\u8107\u5e02",
            L"\u5609\u9ebb\u5e02", L"\u5e9c\u4e2d\u5e02", L"\u5bd2\u6cb3\u6c5f\u5e02", L"\u5357\u623f\u7dcf\u5e02", L"\u897f\u4e88\u5e02", L"\u96f2\u5357\u5e02",
            L"\u898b\u9644\u5e02", L"\u9ed2\u90e8\u5e02", L"\u5b89\u6765\u5e02", L"\u81fc\u6775\u5e02", L"\u4e09\u6ca2\u5e02", L"\u7db2\u8d70\u5e02",
            L"\u3044\u3059\u307f\u5e02", L"\u5b8d\u7c9f\u5e02", L"\u5927\u8239\u6e21\u5e02", L"\u307f\u3084\u307e\u5e02", L"\u5c0f\u677e\u5cf6\u5e02",
            L"\u4e94\u5cf6\u5e02", L"\u7530\u6751\u5e02", L"\u745e\u6d6a\u5e02", L"\u9b5a\u6cbc\u5e02", L"\u5e84\u539f\u5e02", L"\u52a0\u6771\u5e02",
            L"\u7c73\u539f\u5e02", L"\u531d\u7473\u5e02", L"\u5357\u57ce\u5e02", L"\u7a1a\u5185\u5e02", L"\u71b1\u6d77\u5e02", L"\u91dc\u77f3\u5e02",
            L"\u8c4a\u5f8c\u5927\u91ce\u5e02", L"\u963f\u6ce2\u5e02", L"\u66fd\u65bc\u5e02", L"\u5357\u4e5d\u5dde\u5e02", L"\u65b0\u5e84\u5e02",
            L"\u5357\u3055\u3064\u307e\u5e02", L"\u5c0f\u5343\u8c37\u5e02", L"\u516b\u5e61\u6d5c\u5e02", L"\u9577\u9580\u5e02", L"\u5927\u7530\u5e02",
            L"\u4f0a\u4e88\u5e02", L"\u6d77\u6d25\u5e02", L"\u702c\u6238\u5185\u5e02", L"\u5099\u524d\u5e02", L"\u76f8\u99ac\u5e02", L"\u5b87\u571f\u5e02",
            L"\u884c\u65b9\u5e02", L"\u5927\u5ddd\u5e02", L"\u767d\u77f3\u5e02", L"\u3064\u304c\u308b\u5e02", L"\u4e45\u6148\u5e02", L"\u5c71\u68a8\u5e02",
            L"\u5317\u79cb\u7530\u5e02", L"\u4e0b\u5442\u5e02", L"\u4f0a\u9054\u5e02", L"\u9ed2\u77f3\u5e02", L"\u6d45\u53e3\u5e02", L"\u56db\u4e07\u5341\u5e02",
            L"\u845b\u57ce\u5e02", L"\u7dbe\u90e8\u5e02", L"\u9d28\u5ddd\u5e02", L"\u4eba\u5409\u5e02", L"\u5999\u9ad8\u5e02", L"\u77e2\u677f\u5e02",
            L"\u5927\u91ce\u5e02", L"\u6771\u6e29\u5e02", L"\u5357\u4e39\u5e02", L"\u5883\u6e2f\u5e02", L"\u672c\u5de3\u5e02", L"\u9ad8\u6881\u5e02",
            L"\u5e73\u6238\u5e02", L"\u67f3\u4e95\u5e02", L"\u7531\u5e03\u5e02", L"\u5fa1\u524d\u5d0e\u5e02", L"\u304b\u307b\u304f\u5e02", L"\u9e7f\u89d2\u5e02",
            L"\u4e94\u689d\u5e02", L"\u6f5f\u4e0a\u5e02", L"\u5bfe\u99ac\u5e02", L"\u5b87\u9640\u5e02", L"\u4f0a\u8c46\u5e02", L"\u7532\u5dde\u5e02",
            L"\u65b0\u898b\u5e02", L"\u4e0a\u5c71\u5e02", L"\u9999\u5357\u5e02", L"\u5584\u901a\u5bfa\u5e02", L"\u5e73\u5ddd\u5e02", L"\u99d2\u30f6\u6839\u5e02",
            L"\u6ed1\u5ddd\u5e02", L"\u5357\u967d\u5e02", L"\u6771\u304b\u304c\u308f\u5e02", L"\u90fd\u7559\u5e02", L"\u5fd7\u5e03\u5fd7\u5e02",
            L"\u795e\u57fc\u5e02", L"\u671d\u6765\u5e02", L"\u897f\u90fd\u5e02", L"\u7f8e\u99ac\u5e02", L"\u97ee\u5d0e\u5e02", L"\u7537\u9e7f\u5e02",
            L"\u6775\u7bc9\u5e02", L"\u5c0f\u77e2\u90e8\u5e02", L"\u56fd\u6771\u5e02", L"\u3046\u304d\u306f\u5e02", L"\u672c\u5bae\u5e02",
            L"\u5b89\u82b8\u9ad8\u7530\u5e02", L"\u65b0\u5bae\u5e02", L"\u80ce\u5185\u5e02", L"\u5c0f\u6d5c\u5e02", L"\u89d2\u7530\u5e02",
            L"\u4e2d\u592e\u5e02", L"\u897f\u6d77\u5e02", L"\u76f8\u751f\u5e02", L"\u3044\u3061\u304d\u4e32\u6728\u91ce\u5e02", L"\u9ad8\u8429\u5e02",
            L"\u9e7f\u5cf6\u5e02", L"\u6771\u5fa1\u5e02", L"\u6709\u7530\u5e02", L"\u540d\u5bc4\u5e02", L"\u6f6e\u6765\u5e02", L"\u7f8e\u4f5c\u5e02",
            L"\u5fa1\u6240\u5e02", L"\u5bae\u82e5\u5e02", L"\u3042\u308f\u3089\u5e02", L"\u4e09\u597d\u5e02", L"\u4e0a\u5929\u8349\u5e02",
            L"\u8f2a\u5cf6\u5e02", L"\u5927\u753a\u5e02", L"\u52a0\u8302\u5e02", L"\u4e8c\u6238\u5e02", L"\u5c71\u770c\u5e02", L"\u4ed9\u5317\u5e02",
            L"\u9577\u4e95\u5e02", L"\u58f1\u5c90\u5e02", L"\u9060\u91ce\u5e02", L"\u4f0a\u4f50\u5e02", L"\u6839\u5ba4\u5e02", L"\u90a3\u9808\u70cf\u5c71\u5e02",
            L"\u5b09\u91ce\u5e02", L"\u5927\u7af9\u5e02", L"\u9999\u7f8e\u5e02", L"\u571f\u4f50\u5e02", L"\u516b\u5e61\u5e73\u5e02", L"\u7af9\u539f\u5e02",
            L"\u7f8e\u7962\u5e02", L"\u963f\u8607\u5e02", L"\u5927\u6708\u5e02", L"\u306b\u304b\u307b\u5e02", L"\u4e0a\u91ce\u539f\u5e02", L"\u8c4a\u524d\u5e02",
            L"\u6c5f\u7530\u5cf6\u5e02", L"\u6c34\u4fe3\u5e02", L"\u6751\u5c71\u5e02", L"\u98db\u9a28\u5e02", L"\u990a\u7236\u5e02", L"\u5fa1\u574a\u5e02",
            L"\u7f8e\u5504\u5e02", L"\u6c5f\u6d25\u5e02", L"\u52dd\u5c71\u5e02", L"\u677e\u6d66\u5e02", L"\u4e0b\u7530\u5e02", L"\u7d0b\u5225\u5e02",
            L"\u9808\u5d0e\u5e02", L"\u7559\u840c\u5e02", L"\u7af9\u7530\u5e02", L"\u5bcc\u826f\u91ce\u5e02", L"\u8c4a\u5f8c\u9ad8\u7530\u5e02",
            L"\u6df1\u5ddd\u5e02", L"\u6795\u5d0e\u5e02", L"\u98ef\u5c71\u5e02", L"\u9678\u524d\u9ad8\u7530\u5e02", L"\u963f\u4e45\u6839\u5e02",
            L"\u7fbd\u548b\u5e02", L"\u7f8e\u6fc3\u5e02", L"\u5bbf\u6bdb\u5e02", L"\u58eb\u5225\u5e02", L"\u3048\u3073\u306e\u5e02", L"\u9ce5\u7fbd\u5e02",
            L"\u591a\u4e45\u5e02", L"\u52dd\u6d66\u5e02", L"\u4e32\u9593\u5e02", L"\u5c3e\u9df2\u5e02", L"\u5bae\u6d25\u5e02", L"\u6d25\u4e45\u898b\u5e02",
            L"\u718a\u91ce\u5e02", L"\u5b89\u82b8\u5e02", L"\u7802\u5ddd\u5e02", L"\u5c3e\u82b1\u6ca2\u5e02", L"\u5782\u6c34\u5e02", L"\u897f\u4e4b\u8868\u5e02",
            L"\u82a6\u5225\u5e02", L"\u73e0\u6d32\u5e02", L"\u571f\u4f50\u6e05\u6c34\u5e02", L"\u5ba4\u6238\u5e02", L"\u8d64\u5e73\u5e02", L"\u5915\u5f35\u5e02",
            L"\u4e09\u7b20\u5e02", L"\u6b4c\u5fd7\u5185\u5e02"
        };

    auto queryText = e->QueryText;
    wstring query = wstring(queryText->Data());
    if (queryText->Length() == 0)
    {
        MainPage::Current->NotifyUser("Use the search pane to submit a query", NotifyType::StatusMessage);
    }
    else
    {
        auto request = e->Request;
        auto queryTextAlternatives = e->LinguisticDetails->QueryTextAlternatives;
        auto size = queryTextAlternatives->Size;
        wstring *alternatives = new wstring[size];
        for (unsigned int i = 0; i < size; i++)
        {
            alternatives[i] = wstring(queryTextAlternatives->GetAt(i)->Data());
        }

        bool done = false;
        for (unsigned int i = 0; (i < size) && !done; i++)
        {
            for each(wstring suggestion in suggestionList)
            {
                if (suggestion.find(alternatives[i]) == 0)
                {
                    // if the string starts with the alternative, add suggestion to search pane.
                    request->SearchSuggestionCollection->AppendQuerySuggestion(ref new String(const_cast<wchar_t*>(suggestion.c_str())));

                    // Break since the search pane can show at most 5 suggestions.
                    if (request->SearchSuggestionCollection->Size >= MainPage::SearchPaneMaxSuggestions)
                    {
                        done = true;
                        break;
                    }
                }
            }
        }
        delete [] alternatives;

        if (request->SearchSuggestionCollection->Size > 0)
        {
            MainPage::Current->NotifyUser("Suggestions provided for query: " + queryText, NotifyType::StatusMessage);
        }
        else
        {
            MainPage::Current->NotifyUser("No suggestions provided for query: " + queryText, NotifyType::StatusMessage);
        }
    }
}
