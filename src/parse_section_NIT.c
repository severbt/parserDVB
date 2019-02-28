#include "../include/parse_stream_packet.h"
#include "../include/descriptor.h"


const unsigned char* get_section_NI(const unsigned char* str, const uint16_t number_pid, struct buffer_section* section)
{
    const char _p = str;
    int        _status = -1;
    _p = find_start(str);

    _status = add_stream( _p, number_pid, section);
    if ( _status == (-1))
    {
        _p = find_start(_p + 1);
    }
    else
    {


    }
}

int parse_section(const unsigned char* str, nit_section* ns)
{
    int result = -1;
    uint16_t  len = 0;

    ns->_tid.u   = (*(uint8_t*)str + len);
    len += 1;

    ns->_slen.u  = (*(uint16_t*)str + len) & MASK_SECTION_NIT_LENGTH;
    len += 2;

    ns->_nid.u   = (*(uint16_t*)str + len);
    len += 2;

    ns->_vern.u  = (*(uint8_t*)str + len) & MASK_SECTION_VERSION_NUM;
    len += 1;

    ns->_secn.u  = (*(uint8_t*)str + len);
    len += 1;

    ns->_lsecn.u = (*(uint8_t*)str + len);
    len += 1;

    ns->_ndlen.u = (*(uint16_t*)str + len) & MASK_SECTION_NET_LEN;
    len += 2;

    result = parse_descriptor(str + len, ns->_ndlen.u, &ns->_d1);
    if ( result < 1)
    {
        clear_list_desc(ns->_d1);
        return (-1);
    }

    len += result;
    ns->_tstrlen.u = (*(uint16_t*)str + len) & MASK_SECTION_NET_LEN;
    len += 2;

    result = parse_trans_loop(str + len, ns->_tstrlen.u, &ns->_tl);
    if ( result < 1)
    {
        clear_list_desc(ns->_d1);
        return (-1);
    }
    len += result;

    ns->_CRC_32.u  = (*(uint32_t*)str + len);

    return len;
}
