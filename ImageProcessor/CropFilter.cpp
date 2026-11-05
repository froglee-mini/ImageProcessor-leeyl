#include "CropFilter.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace ip {

    CropFilter::CropFilter(int x, int y, int width, int height)
        : m_x(x), m_y(y), m_width(width), m_height(height)
    {
        if (x < 0 || y < 0 || width <= 0 || height <= 0) {
            throw std::invalid_argument(
                "Crop coordinates and dimensions are invalid");
        }
    }

    void CropFilter::apply(ImageBuffer& image) const {

        // 원본 이미지 범위를 벗어나는지 검사
        if (m_x >= image.width() || m_y >= image.height() ||
            m_width > image.width() - m_x ||
            m_height > image.height() - m_y) {
            throw std::out_of_range(
                "Crop region exceeds image bounds");
        }

        // 잘라낼 크기의 새 이미지 생성
        ImageBuffer result(m_width, m_height);

        for (int y = 0; y < m_height; ++y) {
            const std::uint8_t* sourceRow =
                image.rowPtr(m_y + y);

            std::uint8_t* destinationRow =
                result.rowPtr(y);

            const std::uint8_t* start =
                sourceRow + m_x * ImageBuffer::CHANNELS;

            std::copy_n(
                start,
                result.rowStride(),
                destinationRow
            );
        }

        // 기존 이미지를 잘라낸 이미지로 교체
        image = std::move(result);
    }

} // namespace ip
