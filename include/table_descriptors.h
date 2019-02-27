#include "DVB_types.h"

typedef struct network_name
{
    __u8 desc_tag;
    __u8 desc_len; //count char


} nndesc;

typedef struct transport_stream
{
    __u8 desc_tag;
    __u8 desc_len; // count bytes

} tsdesc;

typedef struct transport_stream_loop
{
    __u16  _tra_id;
    __u16  _net_id;
    __u8   _res;
    __u16  _tra_len;

    tsdesc _d;
    _byte* _p;
}tsloop;
