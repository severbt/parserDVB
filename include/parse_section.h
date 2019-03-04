#pragma once

#include "DVB_types.h"

namespace DVB
{
    const int sectionIsFull(buffer_section& _sect);

    void clear_section_garbage(const _u16_t _len, buffer_section& sect);
    //const unsigned char* get_section(const unsigned char* str, const uint16_t number_pid, struct buffer_section* section);

    void printSectionNit(const _u16_t _len, const buffer_section& sect);

}


