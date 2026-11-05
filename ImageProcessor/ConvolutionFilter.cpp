#include "ConvolutionFilter.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace ip {

    ConvolutionFilter::ConvolutionFilter(Type type) {
        if (type == Type::Blur) {
            m_kernel = {
                1.0 / 9, 1.0 / 9, 1.0 / 9,
                1.0 / 9, 1.0 / 9, 1.0 / 9,
                1.0 / 9, 1.0 / 9, 1.0 / 9
            };
        }
        else {
            m_kernel = {
                 0, -1,  0,
                -1,  5, -1,
                 0, -1,  0
            };
        }
    }

    void ConvolutionFilter::apply(ImageBuffer& image) const {
        if (image.empty()) {
            return;
        }

        // 원본을 복사해 계산 중 데이터 변경 방지
        const ImageBuffer source = image;

        const int width = image.width();
        const int height = image.height();

        for (int y = 0; y < height; ++y) {
            std::uint8_t* dstRow = image.rowPtr(y);

            for (int x = 0; x < width; ++x) {
                for (int channel = 0;
                    channel < ImageBuffer::CHANNELS;
                    ++channel) {

                    double sum = 0.0;

                    for (int ky = -1; ky <= 1; ++ky) {
                        for (int kx = -1; kx <= 1; ++kx) {
                            // 가장자리 좌표를 이미지 내부로 제한
                            const int sx =
                                std::clamp(x + kx, 0, width - 1);
                            const int sy =
                                std::clamp(y + ky, 0, height - 1);

                            const std::uint8_t* srcRow =
                                source.rowPtr(sy);

                            const double value =
                                srcRow[sx * ImageBuffer::CHANNELS + channel];

                            const double weight =
                                m_kernel[(ky + 1) * 3 + (kx + 1)];

                            sum += value * weight;
                        }
                    }

                    dstRow[x * ImageBuffer::CHANNELS + channel] =
                        static_cast<std::uint8_t>(
                            std::lround(std::clamp(sum, 0.0, 255.0)));
                }
            }
        }
    }

} // namespace ip
