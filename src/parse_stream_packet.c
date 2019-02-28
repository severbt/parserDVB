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

//return rest
int add_stream(const unsigned char* str, const uint16_t number_pid, struct buffer_section* section)
{
    static unsigned char s_bufrest[188] = {};
    static uint8_t       s_courest = 0;

    uint8_t size_tmp = SP_SIZE_TAIL; //size payloadize_tmp
    struct head_stream hs = {};
    const unsigned char* p_start = NULL;
    const unsigned char* p_end   = str + SP_SIZE_STREAM;

    //parse packet stream
    p_start = parse_packet(str, &hs);

    if (hs._sync.u != HEAD_START_BYTE)
    {
        if (s_courest > 0)
        {
            s_bufrest[0] = 0;
            s_courest = 0;
        }
        return (-1);
    }

    //check error on pack
    if (hs._err.u == 1)
    {
        if (s_courest > 0)
        {
            s_bufrest[0] = 0;
            s_courest = 0;
        }
        return (-1);
    }

    //check pid
    if (hs._pid.u != number_pid)
    {
        if (s_courest > 0)
        {
            s_bufrest[0] = 0;
            s_courest = 0;
        }
        return (-1);
    }

    //if is rest add in buffer section
    if (s_courest > 0)
    {
        memcpy(section->__pbuf + section->__cur, s_bufrest, s_courest);
        section->__cur += s_courest;

        s_bufrest[0] = 0;
        s_courest = 0;
    }

    if (hs._payl.u == 1)
    {
        size_tmp = hs._size_p.u;
        s_courest = p_end - (p_start + size_tmp);
        memcpy(s_bufrest, p_start + size_tmp, s_courest);
        s_bufrest[s_courest] = 0;
    }

    if ((section->__cur + size_tmp) > (section->__cap) )
    {
        return (-1);
    }

    memcpy(section->__pbuf + section->__cur, p_start, size_tmp);
    section->__cur += size_tmp;

    return 1;
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
