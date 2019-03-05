#include <string>
#include <iostream>

#include "../include/DVB_reader.h"

using namespace DVB;

const uint32_t DATA_SIZE = 4096;

DVB_reader::DVB_reader()
	:m_file(NULL)
	,m_data_file(NULL)
	,m_data_size(0)
{
}

DVB_reader::~DVB_reader()
{
	Close();

	if (m_data_file != NULL)
	{
		free(m_data_file);
		m_data_file = NULL;
	}
}

bool DVB_reader::Open(const char *namefile )
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

void DVB_reader::Close()
{
	if (m_file != NULL)
	{
		fclose(m_file);
		m_file = NULL;
	}
}

bool DVB_reader::RunParser()
{
	while (ReadFile())
	{
	    m_parser.addStreams(m_data_file, m_data_file + m_data_size);
	}

	return false;
}

bool DVB_reader::ReadFile()
{
	bool result = false;

	m_data_size = fread(m_data_file, 1, DATA_SIZE, m_file);
	if ( m_data_size > 0)
	{
        m_data_file[m_data_size] = 0;

		result = true;
	}

	return result;
}
