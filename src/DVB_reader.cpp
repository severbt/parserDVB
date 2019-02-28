#include "../include/DVB_reader.h"

#include <malloc.h>
#include <string.h>
#include <io.h>
#include <iostream>

const uint32_t DATA_SIZE = 4096;

DVBReader::DVBReader()
	:m_file(NULL)
	,m_data_file(NULL)
	,m_data_size(0)
	,m_data_sold(0)
	,m_start(NULL)
	,m_end(NULL)
	,m_part(false)
{
}

DVBReader::~DVBReader()
{
	Close();

	if (m_data_file != NULL)
	{
		free(m_data_file);
		m_data_file = NULL;
	}
}

bool DVBReader::Open(const char *namefile )
{
	bool result = false;

	if ( m_data_file == NULL)
	{
		m_data_file = (unsigned char*)malloc(DATA_SIZE + 1);
	}

	if ( m_data_file == NULL)
	{
		return result;
	}

	Close();
	m_file = fopen(namefile, "rb");
	if (m_file == NULL)
	{
		return result;
	}

	return result;
}

void DVBReader::Close()
{
	if (m_file != NULL)
	{
		fclose(m_file);
		m_file = NULL;
	}
}

bool DVBReader::GetNextSection(unsigned char *buf, const uint8_t bufsize)
{
	if (bufsize < 2)
	{
		return false;
	}

	//если строка еще не вся записана то записываем её
	/*if (m_part)
	{
		m_part = StrCopy(buf, bufsize);
		return true;
	}*/

	while (m_data_size || ReadFile())
	{
		//GetLine();
		//if (CheckStr(m_start, m_filter))
		//{
		//	m_part = StrCopy(buf, bufsize);
		//	return true;
		//}
	}

	return false;
}

bool DVBReader::IsPart() const
{
	return m_part;
}


bool DVBReader::ReadFile()
{
	bool result = false;

	m_data_size = fread(m_data_file, 1, DATA_SIZE, m_file);
	if ( m_data_size > 0)
	{
		m_data_sold = m_data_size;
		//если это не конец строки, нужно найти.

		m_data_file[m_data_size] = '\n';

		result = true;
	}

	return result;
}

void DVBReader::GetLine()
{
	if (m_end == NULL)
	{
		//m_end = m_start = m_data_file;
	}
	else
	{
		m_start = m_end + 1;
	}

	while (*++m_end != '\n');

	if (*(m_end - 1) == '\r')
	{
		*(m_end - 1) = 0;
	}
	else
	{
		*m_end = 0;
	}

	uint32_t def = m_end - m_start + 1;
	if (def > m_data_size)
	{
		m_data_size = 0;
	}
	else
	{
		m_data_size -= def;
	}
}

/****************************************************************/
//StrCopy() - копирует строку в буфер.
/****************************************************************/
bool DVBReader::StrCopy(char *buf, const int bufsize)
{
	bool result = false;

	int len = m_end - m_start;
	if (bufsize > len)
	{
		strncpy(buf, m_start, len);
		buf[len] = '\0';
	}
	else
	{
		strncpy(buf, m_start, bufsize - 1);
		buf[bufsize - 1] = '\0';
		m_start += bufsize - 1;
		result = true;
	}

	return result;
}
