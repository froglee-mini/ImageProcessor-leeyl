
#include "BrightnessContrastFilter.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace ip {

    BrightnessContrastFilter::BrightnessContrastFilter(
        int brightness, double contrast)
        : m_brightness(brightness), m_contrast(contrast)
    {
        if (brightness < -255 || brightness > 255) {
            throw std::invalid_argument(
                "Brightness must be between -255 and 255");
        }

        if (!std::isfinite(contrast) || contrast < 0.0) {
            throw std::invalid_argument(
                "Contrast must be finite and non-negative");
        }
    }

    void BrightnessContrastFilter::apply(ImageBuffer& image) const {
        for (int y = 0; y < image.height(); ++y) {
            std::uint8_t* row = image.rowPtr(y);

            for (int x = 0; x < image.width(); ++x) {
                std::uint8_t* pixel =
                    row + x * ImageBuffer::CHANNELS;

                for (int channel = 0;
                    channel < ImageBuffer::CHANNELS;
                    ++channel) {

                    const double value =
                        (static_cast<double>(pixel[channel]) - 128.0)
                        * m_contrast + 128.0 + m_brightness;

                    pixel[channel] = static_cast<std::uint8_t>(
                        std::lround(std::clamp(value, 0.0, 255.0)));
                }
            }
        }
    }

} // namespace ip
