#pragma once

#include "table_descriptors.h"

namespace DVB
{
    int parseDescriptor(const std::string& str);
    int parseTransportStream(const std::string& str);
}
