#pragma once

#include "../include/DVB_types.h"

namespace DVB
{
    const _byte* findStartPack(const _byte* str, const _byte* _end);
    const bool getPacket(const _byte* _start, const _byte* _end, buffer_pack& _pack);
   // bool                 getPacketSection(const _byte* str, stream_packet& sp);
}



