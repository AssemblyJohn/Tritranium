/** Copyright (c) Lazu Ioan-Bogdan */

#pragma once

#include "Platform\Platform.h"
#include "Platform\PlatformMemory.h"

#include "Core\CoreLite.h"

// #include <EASTL\string.h>

#include <string>
#include <algorithm>
#include <functional>
#include <cctype>

BEGIN_TRITRANIUM

// Carefull on Android/iOS check this
typedef std::string TSTRING;

class PString
{
public:	/** Ctor's and dtor's and assignment */
	PString()
	{ }

	PString(const TCHAR *str) : string(str)
	{ }

	PString(const PString &other) : string(other.string)
	{ }

	PString(const TSTRING &other) : string(other)
	{ }

	PString(TSTRING &&other) : string(other)
	{ }

	void operator=(const PString &);
	void operator=(PString &&);

	void operator=(const TCHAR *);

public: /** Utils */
	const uint32 Length() const 
	{ 
		return string.length(); 
	}

	void Clear();
	void Reserve(size_t);

	FORCEINLINE void TrimLeft()
	{
		string.erase(string.begin(), ::std::find_if(string.begin(), string.end(), ::std::not1(::std::ptr_fun<int, int>(::std::isspace))));
	}

	FORCEINLINE void TrimRight()
	{
		string.erase(::std::find_if(string.rbegin(), string.rend(), ::std::not1(::std::ptr_fun<int, int>(::std::isspace))).base(), string.end());
	}

	FORCEINLINE void Trim()
	{
		TrimLeft();
		TrimRight();
	}

	bool PString::Contains(const PString &val);

	void Replace(const PString &val, const PString &with);

	PString &Append(const TCHAR *);
	PString &Append(const PString &);
	PString &Append(int32);
	PString &Append(int64);
	PString &Append(uint32);
	PString &Append(uint64);
	PString &Append(float);

	const TCHAR *c_str() const;
	TCHAR *c_str();

	TCHAR &operator[](const size_t);
	const TCHAR &operator[](const size_t) const;
	
	// Appends
	PString operator+(const TCHAR *);
	PString operator+(const PString &);
	PString operator+(const int32);
	PString operator+(const int64);
	PString operator+(const uint32);
	PString operator+(const uint64);
	PString operator+(const float);

	// Appends
	PString &operator+=(const TCHAR *);
	PString &operator+=(const PString &);
	PString &operator+=(const int32);
	PString &operator+=(const int64);
	PString &operator+=(const uint32);
	PString &operator+=(const uint64);
	PString &operator+=(const float);	

	bool operator==(const PString&) const;

public: /* Friend */
	friend PString operator+(const TCHAR *, const PString &);

public: /* Utils */
	static uint32 Split(TList<PString> &out, PString &toSplit, const PString &delimiter = TXT("\\s+"));
private:	
	TSTRING string;
};

END_TRITRANIUM

namespace std
{
	template<>
	struct ::std::hash<Tritranium::PString>
	{
		size_t operator()(const Tritranium::PString &val) const
		{
			return ::std::hash<Tritranium::TSTRING>()(val.c_str());
		}
	};

	template<>
	struct ::std::equal_to<Tritranium::PString>
	{
		bool operator()(const Tritranium::PString &a, const Tritranium::PString &b) const
		{
			return ::std::equal_to<Tritranium::TSTRING>()(a.c_str(), b.c_str());
		}
	};
}