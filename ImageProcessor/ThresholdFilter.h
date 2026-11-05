#pragma once

#include "FilterBase.h"
#include <cstdint>

namespace ip {

    class ThresholdFilter : public FilterBase {
    public:
        explicit ThresholdFilter(int threshold);

        void apply(ImageBuffer& image) const override;

    private:
        int m_threshold;
    };

} // namespace ip
