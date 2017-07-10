/** Copyright (c) Lazu Ioan-Bogdan */

#include "String.h"

#include <regex>

BEGIN_TRITRANIUM

void PString::Clear()
{
	string.clear();		
}

void PString::Reserve(size_t i)
{
	string.reserve(i);
}

void PString::Replace(const PString &val, const PString &with)
{
	uint32 start = 0;

	while ((start = string.find(val.string, start)) != TSTRING::npos)
	{
		string.replace(start, val.Length(), with.string);
		start += with.Length();
	}
}

bool PString::Contains(const PString &val)
{
	return string.find(val.string) != TSTRING::npos;
}

PString &PString::Append(const TCHAR *ptr)
{
	string.append(ptr);

	return *this;
}

PString &PString::Append(const PString &other)
{
	string.append(other.string);

	return *this;
}

PString &PString::Append(int32 v)
{	
	char buff[10];
	PMemory::Memset(buff, 0, sizeof(buff));
	sprintf(buff, "%d", v);
	
	string.append(buff);

	return *this;
}

PString &PString::Append(uint32 v)
{
	char buff[10];
	PMemory::Memset(buff, 0, sizeof(buff));
	sprintf(buff, "%ud", v);

	return *this;
}

PString &PString::Append(uint64 v)
{
	char buff[30];
	PMemory::Memset(buff, 0, sizeof(buff));
	sprintf(buff, "%llu", v);

	string.append(buff);

	return *this;
}

PString &PString::Append(float v)
{
	char buff[30];
	PMemory::Memset(buff, 0, sizeof(buff));
	sprintf(buff, "%f", v);

	string.append(buff);

	return *this;
}

PString &PString::Append(int64 v)
{
	char buff[30];
	PMemory::Memset(buff, 0, sizeof(buff));
	sprintf(buff, "%lld", v);

	string.append(buff);

	return *this;
}

const CHAR *PString::c_str() const
{
	
	return (CHAR *)string.c_str();
}

CHAR *PString::c_str()
{	
	return (CHAR *)(string.c_str());
}

TCHAR &PString::operator[](const size_t i)
{
	return string[i];
}

const TCHAR &PString::operator[](const size_t i) const
{
	return string[i];
}

void PString::operator=(const PString &other)
{
	string = other.string;
}

void PString::operator=(PString &&other)
{
	string = other.string;
}

void PString::operator=(const TCHAR *ptr)
{
	string = ptr;
}

PString PString::operator+(const TCHAR *ptr)
{
	return PString(string + ptr);
}

PString PString::operator+(const PString &other)
{
	return PString(string + other.string);
}

PString PString::operator+(const int32 v)
{
	return (*this).Append(v);
}

PString PString::operator+(const int64 v)
{
	return (*this).Append(v);
}

PString PString::operator+(const uint32 v)
{
	return (*this).Append(v);
}

PString PString::operator+(const uint64 v)
{
	return (*this).Append(v);
}

PString PString::operator+(const float v)
{
	return (*this).Append(v);
}

PString &PString::operator+=(const TCHAR *ptr)
{	
	return (*this).Append(ptr);
}

PString &PString::operator+=(const PString &v)
{
	return (*this).Append(v.string);
}

PString &PString::operator+=(const int32 v)
{
	return (*this).Append(v);
}

PString &PString::operator+=(const int64 v)
{
	return (*this).Append(v);
}

PString &PString::operator+=(const uint32 v)
{
	return (*this).Append(v);
}

PString &PString::operator+=(const uint64 v)
{
	return (*this).Append(v);
}

PString &PString::operator+=(const float v)
{
	return (*this).Append(v);
}

bool PString::operator==(const PString &other) const
{
	return (string == other.string);
}

PString operator+(const TCHAR *ptr, const PString &other)
{	
	return PString(ptr) + other;
}

uint32 PString::Split(TList<PString> &out, PString &toSplit, const PString &delimiter)
{
	uint32 written = 0;

	::std::regex regex(delimiter.string);
	
	::std::sregex_token_iterator iter(toSplit.string.begin(), toSplit.string.end(), regex, -1);
	::std::sregex_token_iterator end;

	while (iter != end)
	{
		out.Add(PString(*iter));
		++iter;

		written++;
	}	

	return written;
}

END_TRITRANIUM