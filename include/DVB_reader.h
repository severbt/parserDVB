#pragma once

#include <stdio.h>
#include <stdint.h>

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
	//эти функции можно было вынести и в .cpp
	bool    ReadFile();

private:
	FILE*        m_file;         //дескриптор файла

	_byte*      m_data_file;    //буфер данных (часть файла)
	_u32_t      m_data_size;    //длина данных
	_u32_t      m_data_sold;    //длина файла old

	_byte*      m_start;        //начало строки
	_byte*      m_end;          //конец строки
	bool        m_part;         //флаг, который определяет часть ли строки
	DVB_parser  m_parser;
};

}


