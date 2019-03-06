#pragma once

#include "DVB_types.h"
#include <map>
#include <list>

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
        const bool parseSection(std::string& stream, hsection& hs);
        void       addSection(hsection& hs);
    private:
        std::map< _u16_t, std::string > m_sections_stream;
        std::map< _u8_t, std::list<head_section>> m_tables;
    };
}


