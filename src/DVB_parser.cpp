#include "../include/DVB_parser.h"

using namespace std;
using namespace DVB;

DVB_parser::DVB_parser()
{
    /*tsection _s = {};
    ttable   _t;

    m_sections.insert(pair<uint16_t, tsection>(0x0000, _s));
    m_sections.insert(pair<uint16_t, tsection>(0x0001, _s));
    m_sections.insert(pair<uint16_t, tsection>(0x0002, _s));
    m_sections.insert(pair<uint16_t, tsection>(0x0012, _s));
    m_sections.insert(pair<uint16_t, tsection>(0x0010, _s));

    m_tables.insert(pair<uint16_t, ttable>(0x0000, _t));
    m_tables.insert(pair<uint16_t, ttable>(0x0001, _t));
    m_tables.insert(pair<uint16_t, ttable>(0x0002, _t));
    m_tables.insert(pair<uint16_t, ttable>(0x0012, _t));
    m_tables.insert(pair<uint16_t, ttable>(0x0010, _t));*/
}

DVB_parser::~DVB_parser()
{
    //dtortsection _s;
}

bool DVB_parser::addStreams(const _byte* _start_str, const _byte* _end_str)
{
    ts_pack         pack = {};        //current pack
    int                 result = -1;

    //auto its = m_sections.end();

    if ( _start_str == NULL || _end_str == NULL)
    {
        return result;
    }

    m_pars_stream.addStream(_start_str, _end_str);
    while( m_pars_stream.getPack( pack ) )
    {
        m_pars_section.addPack(pack);
    }
}
