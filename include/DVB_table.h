#pragma once

#include <stdint.h>

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



