#pragma once

#include "table_descriptors.h"

namespace DVB
{
    int parseDescriptor(const std::string& str, const _u8_t pos, const _u16_t len);

}
