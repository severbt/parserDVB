#include "../include/parse_stream_packet.h"
#include "../include/descriptor.h"


const unsigned char* get_section_NI(const unsigned char* str, const uint16_t number_pid, struct buffer_section* section)
{
    //while
}

int parse_section(const unsigned char* str, nit_section* ns)
{
    int result = -1;

    ns->_tid.u  = (*(uint8_t*)str);
    str += 1;

    ns->_slen.u  = (*(uint16_t)str) & MASK_SECTION_NIT_LENGTH;
    str += 2;

    ns->_nid.u   = (*(uint16_t)str);
    str += 2;

    ns->_vern.u  = (*(uint8_t)str) & MASK_SECTION_VERSION_NUM;
    str += 1;

    ns->_secn.u  = (*(uint8_t)str);
    str += 1;

    ns->_lsecn.u = (*(uint8_t)str);
    str += 1;

    ns->_ndlen.u = (*(uint16_t)str) & MASK_SECTION_NET_LEN;
    str += 2;

    result = parse_descriptor(str, ns->_ndlen.u, &ns->_d1);
    if ( result < 1)
    {
        clear_list_desc(ns->_d1);
        return (-1);
    }

    ns->_tstrlen.u = (*(uint16_t)str) & MASK_SECTION_NET_LEN;
    str += 2;

    result = parse_trans_loop(str, ns->_tstrlen.u, &ns->_tl);
    if ( result < 1)
    {
        clear_list_desc(ns->_d1);
        return (-1);
    }

    ns->_CRC_32.u  = (*(uint32_t)str);

    return 1;
}
