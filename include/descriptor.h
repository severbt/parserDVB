#pragma once

#include "table_descriptors.h"

int parse_descriptor(unsigned char* str, const uint16_t n, datad* p);
int parse_trans_loop(unsigned char* str, const uint16_t n, tsloop* p);
