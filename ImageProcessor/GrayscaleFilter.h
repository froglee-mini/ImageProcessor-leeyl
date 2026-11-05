#pragma once

#include "FilterBase.h"

namespace ip {

    class GrayscaleFilter : public FilterBase {
    public:
        explicit GrayscaleFilter(int threadCount = 1);

        void apply(ImageBuffer& image) const override;

    private:
        int m_threadCount;

        void processRows(
            ImageBuffer& image,
            int startY,
            int endY) const;
    };

} // namespace ip
