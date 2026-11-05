
#include "ResizeFilter.h"

#include <cstdint>
#include <stdexcept>
#include <utility>

namespace ip {

    ResizeFilter::ResizeFilter(int width, int height)
        : m_width(width), m_height(height)
    {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument(
                "Resize dimensions must be positive");
        }
    }

    void ResizeFilter::apply(ImageBuffer& image) const {
        if (image.empty()) {
            throw std::invalid_argument(
                "Cannot resize an empty image");
        }

        ImageBuffer result(m_width, m_height);

        for (int y = 0; y < m_height; ++y) {
            const int sourceY = static_cast<int>(
                static_cast<std::int64_t>(y) *
                image.height() / m_height);

            const std::uint8_t* sourceRow =
                image.rowPtr(sourceY);

            std::uint8_t* destinationRow =
                result.rowPtr(y);

            for (int x = 0; x < m_width; ++x) {
                const int sourceX = static_cast<int>(
                    static_cast<std::int64_t>(x) *
                    image.width() / m_width);

                for (int channel = 0;
                    channel < ImageBuffer::CHANNELS;
                    ++channel) {

                    destinationRow[
                        x * ImageBuffer::CHANNELS + channel
                    ] = sourceRow[
                        sourceX * ImageBuffer::CHANNELS + channel
                    ];
                }
            }
        }

        image = std::move(result);
    }

} // namespace ip
