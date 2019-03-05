#include <cstring>

#include "../include/parse_stream_packet.h"
#include "../include/DVB_table.h"
#include "../include/utils.h"
#include "../include/DVB_types.h"

using namespace DVB;
using namespace std;


DVB_parse_stream::DVB_parse_stream( const _u32_t size_buf)
    {
        m_stream.reserve(size_buf);
        m_reststream.reserve(376);
    }

void DVB_parse_stream::init(const _u32_t size_buf)
{
    m_stream.reserve(size_buf);
    m_reststream.reserve(376);
}

void DVB_parse_stream::addStream(const string& str)
{
    m_stream.append(str);
}

void DVB_parse_stream::addStream(const _byte* str, _u32_t size_buf)
{
    m_stream.append((char*)str, size_buf);
}

void DVB_parse_stream::addStream(const _byte* start_str, const _byte* end_str)
{
    m_stream.append((char*)start_str, end_str - start_str);
}

const bool DVB_parse_stream::getPack(ts_pack& _pack)
{
    bool result = false;
    hpack    hp = {};
    size_t   pos = string::npos;

    pos = m_stream.find(HEAD_START_BYTE, pos);
    if ( pos == string::npos)
    {
        m_stream.resize(0);
        clearRest();
        return result;
    }

    if ( m_stream.size() < SP_SIZE_STREAM)
    {
        return result;
    }

    parsePack(hp);
    result = checkPack(hp, _pack);

    return result;
}

void DVB_parse_stream::parsePack(head_pack& hs)
{
    hs._sync.u = m_stream[0];

    hs._err.u =  (m_stream[1] & MASK_HEAD_ERROR_INDICATOR) >> 7;
    hs._payl.u = (m_stream[1] & MASK_HEAD_PAYLOAD_START) >> 6;
    hs._prio.u = (m_stream[1] & MASK_HEAD_TRANSPORT_PRIORITY)>>5;

    hs._pid.c[0] = m_stream[1] & 0x1F;
    hs._pid.c[1] = m_stream[2] ;

    if (hs._payl.u == 1)
    {
        hs._size_p.u = hs._prio.u = m_stream[4];
    }
}

const bool DVB_parse_stream::checkPack(const head_pack& hp, ts_pack& o_pack)
{
    bool result = false;
    _u8_t tmp_size = SP_SIZE_STREAM;

    if (hp._err.u == 1)
    {
        m_stream.erase(0, SP_SIZE_STREAM);
        clearRest();
        return result;
    }

    o_pack.clear();
    o_pack._pid = hp._pid.u;
    if ( !m_reststream.empty())
    {
        o_pack._buf.append(m_reststream);
        m_reststream.resize(0);
    }

    if (hp._payl.u == 1)
    {
        o_pack._buf.append(m_stream.data() + 5, hp._size_p.u);
        m_stream.erase(0, hp._size_p.u + 5);

        tmp_size -= hp._size_p.u + 5;
        m_reststream.append(m_stream.data(), tmp_size);
        m_stream.erase(0, tmp_size);
    }
    else
    {
        o_pack._buf.append(m_stream.data() + 4, SP_SIZE_TAIL);
        m_stream.erase(0, SP_SIZE_TAIL);
    }

    result = true;
    return result;
}

void DVB_parse_stream::clearRest()
{
    if ( !m_reststream.empty())
    {
        m_reststream.resize(0);
    }
}
