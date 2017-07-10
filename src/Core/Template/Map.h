/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef __TRITRANIUM_T_MAP_H__
#define __TRITRANIUM_T_MAP_H__

#include "Platform\Platform.h"
#include "Platform\PlatformAssertion.h"

#include <unordered_map>

BEGIN_TRITRANIUM

/**
 * An unordered map. All lookups are done based on the key's hash. Wrapper for the std::unordered_map at the moment.
 */
template<class K, class V>
class TMap
{
public: /* Ctor's, dtor's and operator '=' */
	TMap() 
	{ }
	
	TMap(const TMap &other) : map(other.map)
	{ }

	TMap(TMap &&other) : map(other.map)
	{ }

	TMap &operator=(const TMap &other)
	{
		if (this != &other)
		{
			list = other.map;
		}

		return *this;
	}

	TMap &operator=(TMap &&other)
	{
		if (this != &other)
		{
			list = other.map;
		}

		return *this;
	}

public: /* Modifier functions. */	
	FORCEINLINE void Put(K &key, V &val)
	{
		map[key] = val;		
	}

	FORCEINLINE void Put(const K &key, const V &val)
	{
		map[key] = val;
	}
	
	FORCEINLINE void Remove(const K &key)
	{
		map.erase(key)
	}		

public: /* Search and other utilities */
	bool Contains(const K &key) const
	{
		auto search = map.find(key);
		
		if (search != map.end())
			return true;
		else
			return false;
	}

public:	/* Standard small utility operations. */
	FORCEINLINE V &operator[](const K &key) const
	{
		return map[key];
	}

	FORCEINLINE V &operator[](K &&key) const
	{
		return map[key];
	}
	
	FORCEINLINE V &Get(const K &key) const
	{	
		return map[key];
	}

	FORCEINLINE V &Get(K &&key) const
	{
		return map[key];
	}

	FORCEINLINE void Clear()
	{
		map.clear();
	}

private:
	mutable ::std::unordered_map<K, V> map;
};

END_TRITRANIUM

#endif