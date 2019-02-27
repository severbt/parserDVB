
#include "../include/DVB_types.h"

const unsigned char* find_start(const unsigned char* str);
const unsigned char* add_stream(const unsigned char* str, const uint16_t number_pid, struct buffer_section* section);
const unsigned char* parse_packet(const unsigned char* str, struct head_stream* hs);

