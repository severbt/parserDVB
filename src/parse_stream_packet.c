#include <string.h>

#include "../include/parse_stream_packet.h"
#include "../include/DVB_types.h"
#include "../include/utils.h"

const unsigned char* find_start(const unsigned char* str)
{
    const unsigned char* p = str;

    do
    {
        if ( p == NULL || *p == '\0')
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

const unsigned char* parse_packet(const unsigned char* str, const uint16_t number_pid, unsigned char** section)
{
    const unsigned char* end = str + SP_SIZE_STREAM;
    struct head_stream hs = {};

    hs._sync.u = (*(uint8_t*)str);
    str += 1;

    hs._err.u   = (*(uint8_t*)str) & MASK_HEAD_ERROR_INDICATOR;
    hs._payl.u  = (*(uint8_t*)str) & MASK_HEAD_PAYLOAD_START;
    hs._prio.u  = (*(uint8_t*)str) & MASK_HEAD_TRANSPORT_PRIORITY;
    hs._pid.u  = (*(uint16_t*)str) & MASK_HEAD_PID;
    str += 2;

    hs._scra.u = (*(uint8_t*)str) & MASK_HEAD_TRANS_SCEABING;
    hs._afil.u = (*(uint8_t*)str) & MASK_HEAD_ADAPTION_FIELD;
    hs._indx.u = (*(uint8_t*)str) & MASK_HEAD_CONTINULY;
    swap_byte(&hs._pid.c[0], &hs._pid.c[1]);
    str += 1;

    if (hs._sync.u != HEAD_START_BYTE)
    {
        return end;
    }

    if (hs._err.u != 1)
    {
        return end;
    }

    if (hs._pid.u != TABLE_PID_NIT)
    {
        return end;
    }

    if (hs._payl.u == 1)
    {
        hs._size_p.u = (*(uint8_t*)str);
        str += hs._size_p.u + 1; //??? +1
    }

    memcpy(*section, str, end - str);

    return end;
}


