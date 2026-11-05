#pragma once

#include "FilterBase.h"

namespace ip {

    class CropFilter : public FilterBase {
    public:
        CropFilter(int x, int y, int width, int height);

        void apply(ImageBuffer& image) const override;

    private:
        int m_x;
        int m_y;
        int m_width;
        int m_height;
    };

} // namespace ip
