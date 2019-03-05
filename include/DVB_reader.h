#pragma once

#include <cstdint>

#include "DVB_parser.h"

namespace DVB
{
class DVB_reader
{
public:
			DVB_reader();
			~DVB_reader();
	bool	Open( const char *namefile );
	void	Close();
	bool	RunParser();

private:
	bool    ReadFile();

private:
	FILE*        m_file;

	_byte*      m_data_file;
	_u32_t      m_data_size;

	DVB_parser  m_parser;
};

}


