#include "../include/DVB_parser.h"

#include "../include/parse_stream_packet.h"
#include "../include/parse_section.h"

#include <cstring>

using namespace std;
using namespace DVB;

DVB_parser::DVB_parser()
{
    tsection _s = {};
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
    m_tables.insert(pair<uint16_t, ttable>(0x0010, _t));
}

DVB_parser::~DVB_parser()
{
    //dtortsection _s;
}

bool DVB_parser::addStreams(const _byte* _bufstream, const _byte* _end_str)
{
    const _byte*  _p_start = _bufstream;
    const _byte*  _p = _bufstream;
    buffer_pack   _pack = {};

    static buffer_pack  _restpack = {};
    int           _status = -1;

    auto itt = m_sections.end();
    while(1)
    {
        _p = findStartPack(_p, _end_str);
        if ( _p == NULL )
        {
            return false;
        }

        //check on rest
        if ( (_p - _p_start) > 0)
        {
            _restpack._s = _p - _p_start;

            memcpy(_restpack._b, _p_start, _restpack._s);
            _restpack._b[_restpack._s] = 0;
        }

        if (getPacket(_p, _end_str, _pack) == true)
        {
            if (addPackToSection(_pack, _restpack))
            {
                _status = sectionIsFull( m_sections[_pack._pid] );
                if (_status > 0)
                {
                    addSectionToTable(_status, _pack._pid);
                }
            }
        }

        if (_pack._s != 0)
        {
            _pack._s    = 0;
            _pack._pid  = 0;
            _pack._b[0] = 0;
        }

        if (_restpack._s != 0)
        {
            _pack._s    = 0;
            _pack._b[0] = 0;
        }

       ++_p;
       _p_start = _p;
    }

}

bool DVB_parser::addPackToSection(buffer_pack& _pack, buffer_pack& _restpack)
{
    bool result = false;

    auto its = m_sections.find( _pack._pid);
    if (its != m_sections.end());
    {
        if (_restpack._s != 0)
        {
            memcpy(its->second._b + its->second._s, _restpack._b, _restpack._s);
            its->second._s += _restpack._s;
            _restpack._s = 0;
            _restpack._b[0] = 0;
        }

        memcpy(its->second._b + its->second._s, _pack._b, _pack._s);
        its->second._s += _pack._s;
        its->second._b[its->second._s] = '\0';
        result = true;
    }

    return result;
}

void DVB_parser::addSectionToTable(const _u16_t _len, const _u16_t _pid)
{
    info_section isec = {};

    auto itt = m_tables[_pid];
    auto its = m_sections[_pid];


    switch(_pid)
    {
    case 0x0000:
        {
            clear_section_garbage(_len, its);
            break;
        }
    case 0x0001:
        {
            clear_section_garbage(_len, its);
            break;
        }
    case 0x0002:
        {
            clear_section_garbage(_len, its);
            break;
        }
    case 0x0012:
        {
            clear_section_garbage(_len, its);
            break;
        }
    case 0x0010:
        {
            printSectionNit(_len, its);
            //itt.second.add(its);
            clear_section_garbage(_len, its);
            break;
        }
    default:
        {
            printf("--Unknow table!\n");
            break;
        }
    }
}
