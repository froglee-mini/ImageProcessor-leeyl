
#pragma once

#include <string>

namespace ip {

    class Logger {
    public:
        static void write(
            bool success,
            long long durationMs,
            const std::string& filterInfo,
            const std::string& errorMessage = "");
    };

} // namespace ip
