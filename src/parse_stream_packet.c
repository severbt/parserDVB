#include <string.h>

#include "../include/parse_stream_packet.h"
#include "../include/DVB_table.h"
#include "../include/utils.h"

const unsigned char* find_start(const unsigned char* str)
{
    const unsigned char* p = str;

    do
    {
        if ( (p == NULL) || (*p == '\0'))
        {
            return (NULL);
        }

        //printf("p=%s -- HEAD=%s",*p, HEAD_START_BYTE);
        if (*p == HEAD_START_BYTE)
        {
            return (p);
        }

        ++p;
    }while(1);

    return (NULL);
}

const unsigned char* add_stream(const unsigned char* str, const uint16_t number_pid, struct buffer_section* section)
{
     uint8_t size_tmp = SP_SIZE_TAIL; //size payload
     struct head_stream hs = {};
     const unsigned char* p_start = NULL;
     const unsigned char* p_end   = str + SP_SIZE_STREAM;

     //parse packet stream
     p_start = parse_packet(str, &hs);

    if (hs._sync.u != HEAD_START_BYTE)
    {
        return p_end ;
    }

    if (hs._err.u != 1)
    {
        return p_end ;
    }

    if (hs._pid.u != number_pid)
    {
        return p_end ;
    }

    //check memory!!!!
    if (hs._payl.u == 1)
    {
        size_tmp = hs._size_p.u;
    }

    if ((section->__cur + size_tmp) > (section->__cap) )
    {
        section->__cap = (section->__cur + size_tmp)*2;
        unsigned char* _p = allocate_uc(section->__cap);
        memcpy(_p, section->__pbuf, section->__cur);
        clear_uc(section->__pbuf);
        section->__pbuf = _p;
    }

    memcpy(section->__pbuf + section->__cur, p_start, size_tmp);
    section->__cur += size_tmp;
    p_start += size_tmp;

    return (p_end - p_start);
}

const unsigned char* parse_packet(const unsigned char* str, struct head_stream* hs)
{
    hs->_sync.u = (*(uint8_t*)str);
    str += 1;

    hs->_err.u   = (*(uint8_t*)str) & MASK_HEAD_ERROR_INDICATOR;
    hs->_payl.u  = (*(uint8_t*)str) & MASK_HEAD_PAYLOAD_START;
    hs->_prio.u  = (*(uint8_t*)str) & MASK_HEAD_TRANSPORT_PRIORITY;
    hs->_pid.u  = (*(uint16_t*)str) & MASK_HEAD_PID;
    str += 2;

    hs->_scra.u = (*(uint8_t*)str) & MASK_HEAD_TRANS_SCEABING;
    hs->_afil.u = (*(uint8_t*)str) & MASK_HEAD_ADAPTION_FIELD;
    hs->_indx.u = (*(uint8_t*)str) & MASK_HEAD_CONTINULY;
    swap_byte(&hs->_pid.c[0], &hs->_pid.c[1]);
    str += 1;

    if (hs->_payl.u == 1)
    {
        hs->_size_p.u = (*(uint8_t*)str);
        str += 1;
    }

    return str;
}


