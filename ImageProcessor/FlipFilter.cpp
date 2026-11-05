#include "FlipFilter.h"

#include <algorithm>
#include <cstdint>

namespace ip {

    FlipFilter::FlipFilter(Direction direction)
        : m_direction(direction)
    {
    }

    void FlipFilter::apply(ImageBuffer& image) const {
        const int width = image.width();
        const int height = image.height();

        if (image.empty()) {
            return;
        }

        if (m_direction == Direction::Horizontal) {
            // 좌우 반전: 같은 행에서 픽셀 교환
            for (int y = 0; y < height; ++y) {
                std::uint8_t* row = image.rowPtr(y);

                for (int x = 0; x < width / 2; ++x) {
                    const int oppositeX = width - 1 - x;

                    for (int channel = 0;
                        channel < ImageBuffer::CHANNELS;
                        ++channel) {

                        std::swap(
                            row[x * ImageBuffer::CHANNELS + channel],
                            row[oppositeX * ImageBuffer::CHANNELS + channel]
                        );
                    }
                }
            }
        }
        else if (m_direction == Direction::Vertical) {
            // 상하 반전: 위쪽 행과 아래쪽 행 교환
            for (int y = 0; y < height / 2; ++y) {
                std::uint8_t* topRow = image.rowPtr(y);
                std::uint8_t* bottomRow =
                    image.rowPtr(height - 1 - y);

                for (int i = 0; i < image.rowStride(); ++i) {
                    std::swap(topRow[i], bottomRow[i]);
                }
            }
        }
    }

} // namespace ip
