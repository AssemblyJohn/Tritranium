/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef __TRITRANIUM_T_LIST_H__
#define __TRITRANIUM_T_LIST_H__

#include "Platform\Platform.h"
#include "Platform\PlatformAssertion.h"

#include <vector>

#include <EASTL\vector.h>

BEGIN_TRITRANIUM


template <typename T>
using TVector = ::eastl::vector<T>;


/**
* Allocator class so that we are not forced to add elements initialized to 0.
*/
template<typename T, typename Alloc = std::allocator<T>>
class no_ctor_init : public Alloc
{
	typedef std::allocator_traits<Alloc> A_T;

public:
	template<typename U>
	struct rebind
	{
		using other = no_ctor_init<U, typename A_T::template rebind_alloc<U>>;
	};

	using Alloc::Alloc;

	template<typename U>
	void construct(U *ptr) noexcept(std::is_nothrow_default_constructible<U>::value)
	{
		::new(static_cast<void *>(ptr)) U;
	}

	template<typename U, typename...Args>
	void construct(U *ptr, Args&&... args)
	{
		A_T::construct(static_cast<Alloc&>(*this), ptr, std::forward<Args>(args)...);
	}
};


/**
* Basic list. Wrapper for the std::vector.
*/
template<typename T>
class TList
{	
public: /* Ctor's, dtor's and operator '=' */
	TList() { }

	/** Allocates an array with an initial count */
	TList(uint32 count) : list(count)
	{ }

	TList(const TList &other) : list(other.list)
	{ }

	TList(TList &&other) : list(other.list)
	{ }

	TList &operator=(const TList &other)
	{
		if (this != &other)
		{
			list = other.list;
		}

		return *this;
	}

	TList &operator=(TList &&other)
	{
		if (this != &other)
		{
			list = other.list;
		}

		return *this;
	}

public: /* Modifier functions. */

	/**
	 * Initializes the list to the specified count of items. Old items will be destroyed and the added items will be uninitialized.
	 */
	void Init(uint32 count)
	{
		list.clear();
		list.resize(count);
	}	

	/**
	 * Make sure that the array can hold the specified count of items.
	 */
	void Reserve(uint32 count)
	{
		if (count > Count())
		{
			list.reserve(count);
		}
	}

	/**
	* Adds elements to the array but does not initialize them. Do not use for
	* elements that require constructor calls!
	*
	* @param count
	*				Count of uninitialized elements to add. Defaults to 1.
	* @return Old count of elements or index of new element.
	*/
	uint32 AddNoCtor(uint32 count = 1)
	{
		uint32 oldCount = Count();
		
		list.resize(Count() + count);

		return oldCount;
	}

	/**
	* Same as above but will fill the added items with 0.
	*/
	uint32 AddNoCtorZero(uint32 count = 1)
	{
		const uint32 index = AddNoCtor(count);

		FMemory::Memzero((uint8*)GetAllocation() + index * GetSizeofT(), count * GetSizeofT());

		return index;
	}

	/**
	 * Adds the item but will call the constructor. Use for items needing a ctor.
	 *
	 * @return	Current index
	 */
	uint32 Add(T &&item)
	{
		list.emplace_back(item);

		return list.size() - 1;
	}

	// TODO:
	/**
	 * Adds the item but will call the constructor. Use for items needing a ctor.
	 *
	 * @return	Current index
	 */
	uint32 Add(const T &item)
	{
		list.emplace_back(item);

		return 0;

		// return index;
	}

	FORCEINLINE uint32 AddUnique(const T &item)
	{
		uint32 index = Find(item);

		if (index != -1)
		{
			return index;
		}

		return Add(item);
	}


	uint32 Insert(const T &item, uint32 index)
	{
		list.insert(list.begin() + index, item);

		return index;
	}

	uint32 Insert(T &&item, uint32 index)
	{		
		list.insert(list.begin() + index, item);

		return index;
	}

	/**
	* Erase the element from the list.
	*
	* @return True if we found and erased, false otherwise
	*/
	bool Erase(const T &item)
	{
		uint32 index = Find(item);

		if (index == -1)
		{
			return false;
		}

		return Erase(index);
	}

	bool Erase(uint32 index)
	{
		list.erase(list.begin() + index);
		return true;
	}

	/**
	* Completely clears the list, destroying all the old elements.
	*
	* @param newSize
	*				If != 0 will set the list to a new size of uninitialized elements.
	*/
	void Clear(uint32 newSize = 0)
	{
		list.clear();

		if (newSize > 0)
		{
			Init(newSize);
		}
	}

	/** Compacts the list so it does not have any extra elements that are not used. */
	void Compact()
	{
		list.shrink_to_fit();
	}

public: /* Search and other utilities */

	/**
	* Finds the index of the item that equals the passed item value. If many lookups
	* are required consider using a 'Map'.
	*/
	uint32 Find(const T &item) const
	{
		const T *begin = GetAllocation();

		// Basic ptr arithmetic
		for (const T *current = begin, *end = current + list.size(); current != end; ++current)
		{
			if (*current == item)
			{
				return static_cast<uint32>(current - begin);
			}
		}

		return -1;
	}

	/** Finds the index of a item with a predicate. */
	template <typename Predicate>
	uint32 Find(Predicate pred) const
	{
		const T *begin = GetAllocation();

		// Basic ptr arithmetic
		for (const T *current = begin, *end = current + elementNum; current != end; ++current)
		{
			if (pred(*current))
			{
				return static_cast<uint32>(current - begin);
			}
		}

		return -1;
	}

	bool Contains(const T &item) const
	{
		const T *begin = GetAllocation();

		for (const T *current = begin, *end = current + list.size(); current != end; ++current)
		{
			if (*current == item)
			{
				return true;
			}
		}

		return false;
	}
	
public:	/* Standard small utility operations. */

	/** Returns sizeof template param. */
	FORCEINLINE uint32 GetSizeofT() const
	{
		return sizeof(T);
	}

	/** @return How many bytes did we allocated for this array. Counts the capacity for the current size. */
	FORCEINLINE uint32 GetAllocationSize() const
	{
		return GetSizeofT() * Capacity();
	}

	/** @return How many bytes we currently have active for this array. It is a difference between 'GetAllocationSize' and this! Carefull! */
	FORCEINLINE uint32 GetCountSize() const
	{
		return GetSizeofT() * Count();
	}

	/** @return How many elements are not used. max - count */
	FORCEINLINE uint32 GetExtra() const
	{
		return list.capacity() - list.size();
	}

	/** Current count of actually held elements. Same as 'Size' */
	FORCEINLINE uint32 Count() const
	{
		return list.size();
	}

	/** Current count of actually held elements. Same as 'Count' */
	FORCEINLINE uint32 Size() const
	{
		return list.size();
	}

	/** Maximum capacity of elements that can be held before realocating. */
	FORCEINLINE uint32 Capacity() const
	{
		return list.capacity();
	}

	FORCEINLINE bool IsEmpty() const
	{
		return (list.empty());
	}

	FORCEINLINE bool IsNotEmpty() const
	{
		return (list.empty() == false);
	}

	FORCEINLINE const T &Get(uint32 index) const
	{
		return list[index];
	}

	FORCEINLINE T &Get(uint32 index)
	{
		return list[index];
	}

	FORCEINLINE const T &operator[](uint32 index) const
	{		
		return list[index];
	}

	FORCEINLINE T &operator[](uint32 index)
	{		
		return list[index];
	}

	/** 
	 * Returns a ptr to the first element. Can be used
	 * to fill the array with primitive data. Use with great care.
	 * 
	 * Note that a 'Resize' is required before NOT a 'Reserve'
	 */
	FORCEINLINE T* GetAllocation()
	{
		return (T*)list.data();
	}

	/** Returns a ptr to the first element. */
	FORCEINLINE const T* GetAllocation() const
	{		
		return (T*)list.data();
		
	}
public:
	void Sort(bool(*)(T &, T &)) {}

private:
	::std::vector<T, no_ctor_init<T>> list;
	::eastl::vector<T> someList;
};

END_TRITRANIUM

#endif