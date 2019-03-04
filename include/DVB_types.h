#pragma once

#include <string>
#include <cstdint>

//Stream Packet size
const uint8_t SP_SIZE_STREAM = 188;
const uint8_t SP_SIZE_TAIL = 184;
const uint8_t SP_SIZE_HEAD = 4;

//MASK Head Stream
const uint8_t  MASK_HEAD_ERROR_INDICATOR    = 0x80;
const uint8_t  MASK_HEAD_PAYLOAD_START      = 0x40;
const uint8_t  MASK_HEAD_TRANSPORT_PRIORITY = 0x20;
const uint16_t MASK_HEAD_PID                = 0x1FFF;

const uint8_t MASK_HEAD_TRANS_SCEABING = 0xC0;
const uint8_t MASK_HEAD_ADAPTION_FIELD = 0x30;
const uint8_t MASK_HEAD_CONTINULY      = 0x0F;

//Tag Descriptors
const uint8_t DESC_NETWORK_NAME     = 0x40;
const uint8_t DESC_TRANSPORT_STREAM = 0x67;

//HEAD
const uint8_t HEAD_START_BYTE = 0x47;

//PID TABLES
const uint16_t TABLE_PID_NIT  = 0x0010;

//SECTION TABLES_SIZE
const uint16_t SIZE_SECTION_NIT = 1021;

//MASK section NIT
const uint16_t MASK_SECTION_NIT_SYNTAX_I = 0x8000;

const uint16_t MASK_SECTION_NIT_LENGTH   = 0x03FF;
const uint8_t  MASK_SECTION_VERSION_NUM  = 0x3E;
const uint16_t MASK_SECTION_NET_LEN      = 0x0FFF;


const uint8_t  SECTION_VAL_NUMBER_MAX = 63;


typedef uint8_t  _byte;

typedef uint8_t  _u8_t;
typedef uint16_t _u16_t;
typedef uint32_t _u32_t;
typedef uint64_t _u64_t;

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

typedef struct head_pack
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
} hpack;


typedef struct head_section
{
    __u8   _tabid;
    __u8   _sec_indi;
    __u8   _reserv;
    __u16  _slen;
}hsection;

struct buffer_pack
{
    _byte     _b[376]; // 188 + 188
    _u16_t    _s;       // size
    _u16_t   _pid;
};

struct buffer_section
{
    _byte       _b[1400]; // 1024 + 188 + 188
    _u16_t      _s;       // size
};

struct info_section
{
    _byte       _b[1024];
    _u16_t      _s;

    _u8_t       _tid;
    _u8_t       _vnumb;
    _u8_t       _secnumb;
    _u8_t       _lsecnumb;
};

struct head_section_NIT
{
    head_section _head;

    _u16_t       _netid;
    _u8_t        _reser0  :2,
                 _vernumb :5,
                 _curnext :1;
    _u8_t        _secnumb;
    _u8_t        _lsectnumb;
};
