#pragma once

#include <map>
#include <list>
#include <string>

#include "parse_stream_packet.h"
#include "parse_section.h"

namespace DVB
{

class DVB_parser
{
    //typedef buffer_section tsection;
    typedef std::string tsection;
    typedef std::list<tsection> ttable;

    public:
        DVB_parser();
        ~DVB_parser();

        bool addStreams(const _byte* _buf, const _byte* _end_str);
        bool getSection(const _u16_t _pid, tsection& _s);
        bool checkSection(const _u16_t _pid, tsection& _s);

    private:
        bool addPackToSection(ts_pack& _pack, ts_pack& _rpack);
        void addSectionToTable(const _u16_t _len, const _u16_t _pid);

    private:
       // std::map<_u16_t, tsection> m_sections;
      //  std::map<_u16_t, ttable>   m_tables;
        DVB_parse_stream           m_pars_stream;
        DVB_parse_section          m_pars_section;
};

}


