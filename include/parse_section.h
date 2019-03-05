#pragma once

#include "DVB_types.h"

namespace DVB
{
    class DVB_parse_section
    {
    public:
        DVB_parse_section();

        const bool addPack( const ts_pack& );
    private:

        const bool isPidNIT( const _u16_t _pid);
        const bool sectionIsFull(buffer_section& _sect);
        const bool parseHeadSection(hsection& hs);
    private:
        std::string m_buffer;
        _u16_t      m_old_pid;
    };
}


