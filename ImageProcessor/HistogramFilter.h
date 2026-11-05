#pragma once

#include "FilterBase.h"

#include <array>
#include <cstddef>

namespace ip {

    class HistogramFilter : public FilterBase {
    public:
        static constexpr std::size_t BIN_COUNT = 256;

        using Histogram = std::array<std::size_t, BIN_COUNT>;

        Histogram calculate(const ImageBuffer& image) const;

        void apply(ImageBuffer& image) const override;
    };

} // namespace ip
