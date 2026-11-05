#include "FilterFactory.h"

#include "GrayscaleFilter.h"
#include "BrightnessContrastFilter.h"
#include "ThresholdFilter.h"
#include "ConvolutionFilter.h"
#include "HistogramFilter.h"
#include "CropFilter.h"
#include "ResizeFilter.h"
#include "FlipFilter.h"
#include "Exceptions.h"

#include <cmath>
#include <stdexcept>
#include <vector>

namespace ip {

    namespace {

        // 문자열을 정수로 변환하고 전체 입력을 검증
        int parseInt(const std::string& text) {
            try {
                std::size_t pos = 0;
                int value = std::stoi(text, &pos);

                if (pos != text.size()) {
                    throw FilterError("Invalid integer: " + text);
                }
                return value;
            }
            catch (const std::invalid_argument&) {
                throw FilterError("Invalid integer: " + text);
            }
            catch (const std::out_of_range&) {
                throw FilterError("Integer out of range: " + text);
            }
        }

        // 문자열을 실수로 변환
        double parseDouble(const std::string& text) {
            try {
                std::size_t pos = 0;
                double value = std::stod(text, &pos);

                if (pos != text.size() || !std::isfinite(value)) {
                    throw FilterError("Invalid number: " + text);
                }
                return value;
            }
            catch (const std::invalid_argument&) {
                throw FilterError("Invalid number: " + text);
            }
            catch (const std::out_of_range&) {
                throw FilterError("Number out of range: " + text);
            }
        }

        // 쉼표로 구분된 정수 매개변수 분석
        std::vector<int> parseNumbers(
            const std::string& text, std::size_t expectedCount) {

            std::vector<int> numbers;
            numbers.reserve(expectedCount);
            std::size_t start = 0;

            while (true) {
                const std::size_t end = text.find(',', start);
                const std::string token = text.substr(
                    start, end == std::string::npos
                    ? end : end - start);

                if (numbers.size() >= expectedCount) {
                    throw FilterError("Too many parameters: " + text);
                }

                numbers.push_back(parseInt(token));

                if (end == std::string::npos) {
                    break;
                }
                start = end + 1;
            }

            if (numbers.size() != expectedCount) {
                throw FilterError("Invalid parameter count: " + text);
            }

            return numbers;
        }

    } // anonymous namespace

    std::unique_ptr<FilterBase> FilterFactory::create(
        const std::string& filterName) {

        try {

            if (filterName == "grayscale") {
                return std::make_unique<GrayscaleFilter>();
            }
            else if (filterName.rfind("grayscale:", 0) == 0) {
                const int threads = parseInt(filterName.substr(10));

                if (threads < 1 || threads > 16) {
                    throw FilterError(
                        "Thread count must be between 1 and 16");
                }

                return std::make_unique<GrayscaleFilter>(threads);
            }
            else if (filterName.rfind("brightness:", 0) == 0) {
                int value = parseInt(filterName.substr(11));
                return std::make_unique<BrightnessContrastFilter>(
                    value, 1.0);
            }
            else if (filterName.rfind("contrast:", 0) == 0) {
                double value = parseDouble(filterName.substr(9));
                return std::make_unique<BrightnessContrastFilter>(
                    0, value);
            }
            else if (filterName.rfind("threshold:", 0) == 0) {
                int value = parseInt(filterName.substr(10));
                return std::make_unique<ThresholdFilter>(value);
            }
            else if (filterName == "blur") {
                return std::make_unique<ConvolutionFilter>(
                    ConvolutionFilter::Type::Blur);
            }
            else if (filterName == "sharpen") {
                return std::make_unique<ConvolutionFilter>(
                    ConvolutionFilter::Type::Sharpen);
            }
            else if (filterName == "histogram") {
                return std::make_unique<HistogramFilter>();
            }
            else if (filterName.rfind("crop:", 0) == 0) {
                auto v = parseNumbers(filterName.substr(5), 4);
                return std::make_unique<CropFilter>(
                    v[0], v[1], v[2], v[3]);
            }
            else if (filterName.rfind("resize:", 0) == 0) {
                auto v = parseNumbers(filterName.substr(7), 2);
                return std::make_unique<ResizeFilter>(
                    v[0], v[1]);
            }
            else if (filterName == "flip-horizontal") {
                return std::make_unique<FlipFilter>(
                    FlipFilter::Direction::Horizontal);
            }
            else if (filterName == "flip-vertical") {
                return std::make_unique<FlipFilter>(
                    FlipFilter::Direction::Vertical);
            }

            throw FilterError("Unknown filter: " + filterName);
        }
        catch (const std::invalid_argument& e) {
            throw FilterError(e.what());
        }
        catch (const std::out_of_range& e) {
            throw FilterError(e.what());
        }
    }
} // namespace ip
