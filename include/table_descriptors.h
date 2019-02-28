#pragma once

#include "DVB_types.h"

typedef struct data_descriptor
{
    __u8     _tag;
    __u8     _len;
    uint8_t* _buf;

    struct data_descriptor* _next;

} datad;

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
    datad  _d1;

    struct transport_stream_loop* _next;
    //_byte* _p;
} tsloop;

