#pragma once

#include <stdint.h>

typedef unsigned char __byte;

typedef union __uu8
{
    uint8_t       u;
    unsigned char c[1];
} __u8;

typedef union __uu16
{
    uint16_t      u;
    unsigned char c[2];
} __u16;

typedef union __uu32
{
    uint32_t      u;
    unsigned char c[4];
} __u32;

typedef struct head_stream
{
    __u8  _sync;
    __u8  _err;
    __u8  _payl;
    __u8  _prio;
    __u16 _pid;
    __u8  _scra;
    __u8  _afil;
    __u8  _indx;

    __u8  _size_p;
} head_stream;

typedef struct buffer_section
{
    unsigned char  __pbuf[1024]; //buffer
    uint32_t       __cur;  //current position
    uint32_t       __cap;  //capacity
} buffer_section;
