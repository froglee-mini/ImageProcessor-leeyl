#pragma once

#include "ImageBuffer.h"

namespace ip {

    class FilterBase {
    public:
        virtual ~FilterBase() = default;

        virtual void apply(ImageBuffer& image) const = 0;
    };

} // namespace ip
