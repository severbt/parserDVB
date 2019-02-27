#include <stdint.h>

//Stream Packet size
const uint8_t SP_SIZE_STREAM = 188;
const uint8_t SP_SIZE_TAIL = 184;
const uint8_t SP_SIZE_HEAD = 4;

//Head Stream mask
const uint8_t  MASK_HEAD_ERROR_INDICATOR    = 0x80;
const uint8_t  MASK_HEAD_PAYLOAD_START      = 0x40;
const uint8_t  MASK_HEAD_TRANSPORT_PRIORITY = 0x20;
const uint16_t MASK_HEAD_PID                = 0x1FFF;

const uint8_t MASK_HEAD_TRANS_SCEABING = 0xC0;
const uint8_t MASK_HEAD_ADAPTION_FIELD = 0x30;
const uint8_t MASK_HEAD_CONTINULY      = 0x0F;

//HEAD
const uint8_t HEAD_START_BYTE = 0x47;

//PID TABLES
const uint16_t TABLE_PID_NIT  = 0x0010;
