#include "../include/parse_section.h"

#include <cstring>

using namespace DVB;

DVB_parse_section::DVB_parse_section()
    :m_old_pid(-1)
    {
        m_buffer.reserve(2048);
    }

const bool DVB_parse_section::addPack( const ts_pack& _pack )
{
    bool result = false;
    hsection hs = {};

    result = isPidNIT(_pack._pid);
    if ( !result)
    {
        m_buffer.resize(0);
        return result;
    }

    m_buffer.append(_pack._buf);

    result = parseHeadSection(hs);
    if ( result)
    {
        m_buffer.erase(0, hs._slen.u);
    }
    return result;
}

const bool DVB_parse_section::isPidNIT( const _u16_t _pid)
{
    return _pid == 0x0010;
}

const bool DVB_parse_section::parseHeadSection(hsection& hs)
{
    bool status = false;

    hs._tabid.u = (_u8_t)m_buffer[0];

    hs._slen.u = (((_u8_t)m_buffer[1] & 0x0F) << 8) | (_u8_t)m_buffer[2];
    //hs._slen.c[0] = m_buffer[2];
    //hs._slen.c[1] = m_buffer[1] & 0x0F;

    if (hs._slen.u > 1024)
    {
        return status;
    }

    hs._nid_.c[0] = m_buffer[4];
    hs._nid_.c[1] = m_buffer[3];

    hs._vnumb.u   = (m_buffer[5] & 0x3E) >> 1;
    hs._snumb.u   = m_buffer[6];
    hs._lsnumb.u  = m_buffer[7];

    printf(" Table id : %x\n"
           " Section length : %d\n"
           " Network id : %d\n"
           " Version number : %d\n"
           " Section number : %d/%d\n", hs._tabid.u, hs._slen.u, hs._nid_.u, hs._vnumb.u, hs._snumb.u, hs._lsnumb.u);

    return true;
}
