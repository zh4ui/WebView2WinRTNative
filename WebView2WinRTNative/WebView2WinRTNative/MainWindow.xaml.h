#pragma once
#include "MainWindow.g.h"

namespace winrt::WebView2WinRTNative::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();
        winrt::fire_and_forget initializeWebView2Async();
    };
}

namespace winrt::WebView2WinRTNative::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
