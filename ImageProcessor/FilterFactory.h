#pragma once

#include "FilterBase.h"

#include <memory>
#include <string>

namespace ip {

    class FilterFactory {
    public:
        static std::unique_ptr<FilterBase> create(
            const std::string& filterName);
    };

} // namespace ip
