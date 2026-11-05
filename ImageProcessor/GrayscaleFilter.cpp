
#include "GrayscaleFilter.h"

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <thread>
#include <vector>

namespace ip {

    GrayscaleFilter::GrayscaleFilter(int threadCount)
        : m_threadCount(threadCount)
    {
        if (threadCount < 1 || threadCount > 16) {
            throw std::invalid_argument(
                "Thread count must be between 1 and 16");
        }
    }

    void GrayscaleFilter::processRows(
        ImageBuffer& image,
        int startY,
        int endY) const
    {
        for (int y = startY; y < endY; ++y) {
            std::uint8_t* row = image.rowPtr(y);

            for (int x = 0; x < image.width(); ++x) {
                std::uint8_t* pixel =
                    row + x * ImageBuffer::CHANNELS;

                const double luminance =
                    0.114 * pixel[0] +
                    0.587 * pixel[1] +
                    0.299 * pixel[2];

                const auto gray =
                    static_cast<std::uint8_t>(
                        luminance + 0.5);

                pixel[0] = gray;
                pixel[1] = gray;
                pixel[2] = gray;
            }
        }
    }

    void GrayscaleFilter::apply(ImageBuffer& image) const {
        if (image.empty()) {
            return;
        }

        const int threadCount =
            std::min(m_threadCount, image.height());

        if (threadCount == 1) {
            processRows(image, 0, image.height());
            return;
        }

        std::vector<std::thread> workers;
        workers.reserve(threadCount - 1);

        const int rowsPerThread =
            image.height() / threadCount;

        int startY = 0;

        try {
            for (int i = 0; i < threadCount - 1; ++i) {
                const int endY = startY + rowsPerThread;

                workers.emplace_back(
                    &GrayscaleFilter::processRows,
                    this,
                    std::ref(image),
                    startY,
                    endY);

                startY = endY;
            }
        }
        catch (...) {
            for (auto& worker : workers) {
                if (worker.joinable()) {
                    worker.join();
                }
            }
            throw;
        }

        // 마지막 영역은 현재 스레드에서 처리
        processRows(image, startY, image.height());

        for (auto& worker : workers) {
            worker.join();
        }
    }

} // namespace ip
