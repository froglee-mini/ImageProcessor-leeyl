#pragma once

#include "FilterBase.h"

namespace ip {

    class ResizeFilter : public FilterBase {
    public:
        ResizeFilter(int width, int height);

        void apply(ImageBuffer& image) const override;

    private:
        int m_width;
        int m_height;
    };

} // namespace ip
