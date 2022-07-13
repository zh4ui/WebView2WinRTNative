#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "winrt/WinRTAdapter.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WebView2WinRTNative::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        initializeWebView2Async();
    }


    winrt::fire_and_forget MainWindow::initializeWebView2Async()
    {
        co_await myWebView().EnsureCoreWebView2Async();

        auto dispatchAdapter = WinRTAdapter::DispatchAdapter();

        myWebView().CoreWebView2().AddHostObjectToScript(
            L"Windows", dispatchAdapter.WrapNamedObject(L"Windows", dispatchAdapter));

        myWebView().CoreWebView2().AddScriptToExecuteOnDocumentCreatedAsync(LR"JS(
(() => {
    if (chrome && chrome.webview) {
        console.log('Setting up WinRT projection options');
        chrome.webview.hostObjects.options.defaultSyncProxy = true;
        chrome.webview.hostObjects.options.forceAsyncMethodMatches = [/Async$/,/AsyncWithSpeller$/];
        chrome.webview.hostObjects.options.ignoreMemberNotFoundError = true;
        window.Windows = chrome.webview.hostObjects.sync.Windows;
    }
})();
)JS");

        myWebView().CoreWebView2().NavigateToString(LR"(
<h1>Hello, WebView2</h1>
)");

    }
}
