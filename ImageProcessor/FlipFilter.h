#pragma once

#include "FilterBase.h"

namespace ip {

    class FlipFilter : public FilterBase {
    public:
        enum class Direction {
            Horizontal,
            Vertical
        };

        explicit FlipFilter(Direction direction);

        void apply(ImageBuffer& image) const override;

    private:
        Direction m_direction;
    };

} // namespace ip
