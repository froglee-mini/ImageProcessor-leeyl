
#pragma once

#include "FilterBase.h"

namespace ip {

    class BrightnessContrastFilter : public FilterBase {
    public:
        BrightnessContrastFilter(int brightness, double contrast);

        void apply(ImageBuffer& image) const override;

    private:
        int m_brightness;
        double m_contrast;
    };

} // namespace ip
