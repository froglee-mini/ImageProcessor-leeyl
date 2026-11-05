#include "HistogramFilter.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>

namespace ip {

    HistogramFilter::Histogram
        HistogramFilter::calculate(const ImageBuffer& image) const {

        Histogram histogram{};

        for (int y = 0; y < image.height(); ++y) {
            const std::uint8_t* row = image.rowPtr(y);

            for (int x = 0; x < image.width(); ++x) {
                const std::uint8_t* pixel =
                    row + x * ImageBuffer::CHANNELS;

                const double luminance =
                    0.114 * pixel[0] +
                    0.587 * pixel[1] +
                    0.299 * pixel[2];

                const int brightness = static_cast<int>(
                    std::lround(std::clamp(luminance, 0.0, 255.0)));

                ++histogram[brightness];
            }
        }

        return histogram;
    }

    void HistogramFilter::apply(ImageBuffer& image) const {
        const Histogram histogram = calculate(image);

        std::cout << "Intensity Histogram (0-255)\n";
        std::cout << "---------------------------\n";

        for (std::size_t i = 0; i < BIN_COUNT; ++i) {
            std::cout << i << ": " << histogram[i] << '\n';
        }
    }

} // namespace ip
