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

const int DVB_parse_stream::getPack(ts_pack& _pack)
{
    int      result = -1;
    hpack    hp = {};
    size_t   pos = string::npos;

    pos = findStartPack();
    if ( pos == string::npos)
    {
        m_stream.resize(0);
        clearRest();
        return result;
    }
    else if ( pos > 0)
    {
        m_stream.erase(0, pos);
    }

    if ( m_stream.size() < SP_SIZE_STREAM)
    {
        return result;
    }

    parsePack(hp);
    if (checkPack(hp, _pack))
    {
        result = 1;
    }
    else
    {
        result = 0;
    }

    return result;
}

const size_t DVB_parse_stream::findStartPack()
{
    size_t pos = 0;
    size_t len = m_stream.size();

    while(pos < len)
    {
        if (HEAD_START_BYTE == (_u8_t)m_stream[pos])
        {
            return pos;
        }
        ++pos;
    }

    pos = string::npos;
    return pos;
}

void DVB_parse_stream::parsePack(head_pack& hp)
{
    hp._sync.u = (_u8_t)m_stream[0];

    hp._err.u =  ((_u8_t)m_stream[1] & MASK_HEAD_ERROR_INDICATOR) >> 7;
    hp._payl.u = ((_u8_t)m_stream[1] & MASK_HEAD_PAYLOAD_START) >> 6;
    hp._prio.u = ((_u8_t)m_stream[1] & MASK_HEAD_TRANSPORT_PRIORITY)>>5;

    hp._pid.u = (((_u8_t)m_stream[1] & 0x1F)<<8) | (_u8_t)m_stream[2];

    if (hp._payl.u == 1)
    {
        hp._size_p.u  = (_u8_t)m_stream[4];
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
        m_reststream.resize(0);
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
