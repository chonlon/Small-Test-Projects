#pragma once

#include "App.xaml.g.h"

namespace winrt::desktop::implementation
{
    struct App : AppT<App>
    {
        App() noexcept;
    };
} // namespace winrt::desktop::implementation


