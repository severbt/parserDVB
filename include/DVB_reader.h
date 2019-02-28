#pragma once

#include <stdio.h>
#include <stdint.h>

class DVBReader
{
public:
			DVBReader();
			~DVBReader();
	bool	Open( const char *namefile );
	void	Close();
	bool	GetNextSection(unsigned char *buf, const uint8_t bufsize);

	bool    IsPart() const;

private:
	//эти функции можно было вынести и в .cpp
	bool    ReadFile();
	bool    CheckStr(const char* str,
					 const char* sub);
	bool    StrCopy(char *buf,
		            const int bufsize);
	void    GetLine();

private:
	FILE*        m_file;         //дескриптор файла


	unsigned char* m_data_file;    //буфер данных (часть файла)
	uint32_t       m_data_size;    //длина данных
	uint32_t       m_data_sold;    //длина файла

	char*        m_start;        //начало строки
	char*        m_end;          //конец строки
	bool         m_part;         //флаг, который определяет часть ли строки
};

