#include <cstring>

#include "../include/parse_stream_packet.h"
#include "../include/DVB_table.h"
#include "../include/utils.h"
#include "../include/DVB_types.h"

const _byte* parse_packet(const _byte* str, head_pack* hs);
void print_packet(const hpack& hs);
bool is_real_pid( const _u16_t);

using namespace DVB;

const _byte* DVB::findStartPack(const _byte* str, const _byte* estr)
{
    const _byte* p = str;

    do
    {
        if ( (p == NULL) || (p == estr))
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

const bool DVB::getPacket(const _byte* _start, const _byte* _end, buffer_pack& _pack)
{
    static _byte _restbuf[188] = {};
    static _u8_t _restsize     = 0;
    _u8_t        _sizetmp      = 0;
    bool         _result = false;

    hpack hp = {};

    if (_start == NULL || _end == NULL)
    {
        return _result;
    }

    if (_pack._s != 0)
    {
        _pack._s    = 0;
        _pack._pid  = 0;
        _pack._b[0] = 0;
    }

    _start = parse_packet(_start, &hp);


    if (is_real_pid(hp._pid.u) == false)
    {
        return _result;
    }
    print_packet(hp);
    //memcpy(&hp, _start, 4);  //check;
   // _start += 4;

    //check error on pack
    if (hp._err.u == 1)
    {
        if (_restsize > 0)
        {
            _restbuf[0] = 0;
            _restsize   = 0;
        }
        return _result;
    }

    if (_restsize > 0)
    {
        memcpy(_pack._b + _pack._s, _restbuf, _restsize);
        _pack._s += _restsize;

        _restbuf[0] = 0;
        _restsize   = 0;
    }

    if (hp._payl.u == 1)
    {
        _sizetmp = (*(_u8_t*)_start);

        _restsize = SP_SIZE_STREAM - (5 + _sizetmp);
        memcpy(_restbuf, _start + _sizetmp, _restsize);
        _restbuf[_restsize] = 0;
    }

    memcpy(_pack._b + _pack._s, _start, _sizetmp);
    _pack._s += _sizetmp;

    _result = true;
    return _result;////???
}

/*//return rest
int add_stream(const unsigned char* str, struct buffer_section* section)
{
    uint8_t size_tmp = SP_SIZE_TAIL; //size payloadize_tmp
    hpack hp = {};
    const unsigned char* p_start = NULL;
    const unsigned char* p_end   = str + SP_SIZE_STREAM;getPacket

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
        s_courest = 0;    p_start + sizetmp + _restsize
    }

    if (hs._payl.u == 1)
    {
        size_tmp = hs._size_p.u;getPacket
        s_courest = p_end - (p_start + size_tmp);
        memcpy(s_bufrest, p_start + size_tmp, s_courest);
        s_bufrest[s_courest] = 0;
    }

    if ((section->__cur + size_tmp) > (section->__cap) )
    {
        return (-1);
    }

    membool is_real_pid( const _u16_t);cpy(section->__pbuf + section->__cur, p_start, size_tmp);
    section->__cur += size_tmp;

    return 1;
}

*/
const _byte* parse_packet(const _byte* str, head_pack* hs)
{
    hs->_sync.u = str[0];

    hs->_err.u =  (str[1] & MASK_HEAD_ERROR_INDICATOR) >> 7;
    hs->_payl.u = (str[1] & MASK_HEAD_PAYLOAD_START) >> 6;
    hs->_prio.u = (str[1] & MASK_HEAD_TRANSPORT_PRIORITY)>>5;

    //hs->_pid.u  = ((str[1] & 0x1F)<<8) | (str[2] & 0xFF);
    hs->_pid.c[0] = str[1] & 0x1F;
    hs->_pid.c[1] = str[2] ;

    printf("packet :%x  %x  %x  %x\n", str[0], str[1], str[2], str[3]);

   // hs->_scra.u = (*(uint8_t*)str) & MASK_HEAD_TRANS_SCEABING;
   // hs->_afil.u = (*(uint8_t*)str) & MASK_HEAD_ADAPTION_FIELD;
   // hs->_indx.u = (*(uint8_t*)str) & MASK_HEAD_CONTINULY;
   // swap_byte(&hs->_pid.c[0], &hs->_pid.c[1]);
   // str += 1;

    str += 4;
    return str;
}

 void print_packet(const hpack& hs)
 {
     printf(" sync byte  : %x;   "
            " error indi : %x;   "
            " pid        : %x;\n ", hs._sync.u, hs._err.u, hs._pid.u);
 }

 bool is_real_pid( const _u16_t _pid)
 {
     switch ( _pid)
     {
     //case 0x0000:
    // case 0x0001:
    // case 0x0002:
    // case 0x0003:
   //  case 0x000F:
     case 0x0010:
    // case 0x0011:
   //  case 0x0012:
   //  case 0x0013:
   //  case 0x0014:
   //  case 0x0015:
  //   case 0x0016:
  //   case 0x0017:
  //   case 0x001b:
   //  case 0x001c:
   //  case 0x001d:
  //   case 0x001e:
  //   case 0x001f:
         {
             printf("TABLE PID.\n");
             return true;
         }

     default: break;
     }

     return false;
 }
