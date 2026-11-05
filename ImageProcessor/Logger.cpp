
#include "Logger.h"

#include <Windows.h>

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace ip {

    namespace {

        std::filesystem::path getLogPath() {
            std::vector<wchar_t> buffer(MAX_PATH);

            while (true) {
                const DWORD length = GetModuleFileNameW(
                    nullptr,
                    buffer.data(),
                    static_cast<DWORD>(buffer.size()));

                if (length == 0) {
                    throw std::runtime_error(
                        "Cannot determine executable path");
                }

                if (length < buffer.size()) {
                    return std::filesystem::path(
                        buffer.data()).parent_path() / L"ImageProcessor.log";
                }

                if (buffer.size() >= 32768) {
                    throw std::runtime_error(
                        "Executable path is too long");
                }

                buffer.resize(buffer.size() * 2);
            }
        }

        std::string currentTime() {
            const auto now = std::chrono::system_clock::now();
            const std::time_t time =
                std::chrono::system_clock::to_time_t(now);

            std::tm localTime{};

            if (localtime_s(&localTime, &time) != 0) {
                throw std::runtime_error(
                    "Cannot determine local time");
            }

            std::ostringstream stream;
            stream << std::put_time(
                &localTime, "%Y-%m-%d %H:%M:%S");

            return stream.str();
        }

        std::string sanitize(const std::string& text) {
            std::string result = text;

            for (char& ch : result) {
                if (ch == '\r' || ch == '\n') {
                    ch = ' ';
                }
            }

            return result;
        }

    } // anonymous namespace

    void Logger::write(
        bool success,
        long long durationMs,
        const std::string& filterInfo,
        const std::string& errorMessage) {

        std::ofstream file(getLogPath(), std::ios::app);

        if (!file) {
            throw std::runtime_error(
                "Cannot open log file");
        }

        file << "[" << currentTime() << "] "
            << (success ? "SUCCESS" : "FAILED")
            << " | " << durationMs << "ms"
            << " | " << sanitize(filterInfo);

        if (!success && !errorMessage.empty()) {
            file << " | " << sanitize(errorMessage);
        }

        file << '\n';

        if (!file) {
            throw std::runtime_error(
                "Cannot write log file");
        }
    }

} // namespace ip
