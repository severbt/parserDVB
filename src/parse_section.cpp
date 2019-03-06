#include "../include/parse_section.h"

#include "../include/descriptor.h"

using namespace DVB;
using namespace std;

DVB_parse_section::DVB_parse_section()
    {
    }

const bool DVB_parse_section::addPack( const ts_pack& _pack )
{
    bool result = false;
    hsection hs = {};

    auto itstream = m_sections_stream.end();

    itstream = m_sections_stream.find(_pack._pid);
    if ( itstream == m_sections_stream.end())
    {
        m_sections_stream.insert(pair<_u16_t, string>(_pack._pid, _pack._buf));
    }
    else
    {
        result = isPidNIT(_pack._pid); //
        if ( result)
        {
            itstream->second.append(_pack._buf);
            result = parseSection(itstream->second, hs);
            if ( result)
            {
                addSection(hs);
            }
        }
    }

    return result;
}

const bool DVB_parse_section::isPidNIT( const _u16_t _pid)
{
    return _pid == 0x0010;
}

const bool DVB_parse_section::parseSection( string& stream, hsection& hs)
{
    _u16_t i = 0;
    _u16_t sw = 0;
    _u16_t lmax = stream.length();

    bool status = true;

    while( i < lmax && status )
    {
        switch(sw)
        {
        case 0:
            {
                hs._tabid.u = (_u8_t)stream[0];
                hs._slen.u = (((_u8_t)stream[1] & 0x0F) << 8) | (_u8_t)stream[2];

                if (hs._slen.u > lmax)
                {
                    status = false;
                    break;
                }
                else if (hs._slen.u > 1024 )
                {
                    stream.resize(0);
                    status = false;
                    break;
                }
                else if (hs._slen.u == 0)
                {
                    stream.resize(0);
                    status = false;
                    break;
                }

                hs._nid_.u =    ((_u8_t)stream[3] << 8) | (_u8_t)stream[4];
                hs._vnumb.u   = ((_u8_t)stream[5] & 0x3E) >> 1;
                hs._snumb.u   = (_u8_t)stream[6];
                hs._lsnumb.u  = (_u8_t)stream[7];

                if (hs._tabid.u != 0x40)
                {
                    stream.erase(0, hs._slen.u);
                    status = false;
                    break;
                }

                printf(" Table id       : %x\n"
                       " Section length : %d\n"
                       " Network id     : %d\n"
                       " Version number : %d\n"
                       " Section number : %d/%d\n", hs._tabid.u, hs._slen.u, hs._nid_.u, hs._vnumb.u, hs._snumb.u, hs._lsnumb.u);

                sw = 1; //next level =1
                //i += 7;
                i += 8;
                break;
            }
        case 1:
            {
                _u16_t len = (((_u8_t)stream[i] & 0x0F) << 8) | (_u8_t)stream[ i + 1 ];
                i += 2;

                if ( len > hs._slen.u )
                {
                    stream.erase(0, hs._slen.u);
                    status = false;
                    break;
                }
                else if (len > 0)
                {
                    parseDescriptor(stream.substr(i, len));
                }

                sw = 2;       //next level =2
                i += len;
                break;
            }
        case 2:
            {
                _u16_t len = (((_u8_t)stream[i] & 0x0F) << 8) | (_u8_t)stream[ i + 1 ];
                i += 2;
                if ( len > hs._slen.u )
                {
                    stream.erase(0, hs._slen.u);
                    status = false;
                    break;
                }
                else if (len > 0)
                {
                    parseTransportStream(stream.substr(i, len));
                }

                sw = 3;       //next level =2
                i += len; // 2 - size len.
                break;
            }
        case 3:
            {
                _u32_t CRC32 = 0;
                //check CRC32
                stream.erase(0, hs._slen.u);
                i = lmax;
                break;
            }
        default:
            {
                stream.resize(0);
                status = false;
                break;
            }
        }
    }

    return status;
}

void DVB_parse_section::addSection(hsection& hs)
{
    auto its = m_tables.find(hs._tabid.u);
    if ( its == m_tables.end())
    {
        list<head_section> l;
        l.push_back(hs);
        m_tables.insert(pair<_u8_t, list<head_section>>(hs._tabid.u, l));
    }
    else
    {
        if ( its->second.front()._vnumb.u != hs._vnumb.u)
        {
            its->second.resize(0);
            its->second.push_back(hs);
        }
        else if ((its->second.back()._snumb.u < hs._snumb.u) && (hs._snumb.u <= hs._lsnumb.u))
        {
            its->second.push_back(hs);
        }
    }
}
