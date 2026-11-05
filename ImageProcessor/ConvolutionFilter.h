#pragma once

#include "FilterBase.h"

#include <array>

namespace ip {

    class ConvolutionFilter : public FilterBase {
    public:
        enum class Type {
            Blur,
            Sharpen
        };

        explicit ConvolutionFilter(Type type);

        void apply(ImageBuffer& image) const override;

    private:
        std::array<double, 9> m_kernel;
    };

} // namespace ip
