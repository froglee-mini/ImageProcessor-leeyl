
#include "ThresholdFilter.h"

#include <stdexcept>

namespace ip {

    ThresholdFilter::ThresholdFilter(int threshold)
        : m_threshold(threshold)
    {
        if (threshold < 0 || threshold > 255) {
            throw std::invalid_argument(
                "Threshold must be between 0 and 255");
        }
    }

    void ThresholdFilter::apply(ImageBuffer& image) const {
        for (int y = 0; y < image.height(); ++y) {
            std::uint8_t* row = image.rowPtr(y);

            for (int x = 0; x < image.width(); ++x) {
                std::uint8_t* pixel =
                    row + x * ImageBuffer::CHANNELS;

                const double luminance =
                    0.114 * pixel[0] +
                    0.587 * pixel[1] +
                    0.299 * pixel[2];

                const std::uint8_t binary =
                    (luminance >= m_threshold) ? 255 : 0;

                pixel[0] = binary;
                pixel[1] = binary;
                pixel[2] = binary;
            }
        }
    }

} // namespace ip
