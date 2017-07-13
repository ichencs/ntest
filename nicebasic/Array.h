#pragma once
#include "Basic.h"

template<typename T, bool PODType>
class ListStore abstract : public Object
{
};


template<typename T>
class ListStore<T, false> abstract : public Object
{
protected:
	static void InitializeItemsByDefault(void* dst, int count)
	{
		T* ds = (T*)dst;

		for (int i = 0; i < count; i++)
		{
			new(&ds[i])T();
		}
	}

	static void InitializeItemsByMove(void* dst, void* src, int count)
	{
		T* ds = (T*)dst;
		T* ss = (T*)src;

		for (int i = 0; i < count; i++)
		{
			new(&ds[i])T(MoveValue(ss[i]));
		}
	}

	static void InitializeItemsByCopy(void* dst, void* src, int count)
	{
		T* ds = (T*)dst;
		T* ss = (T*)src;

		for (int i = 0; i < count; i++)
		{
			new(&ds[i])T(ss[i]);
		}
	}

	static void MoveItemsInTheSameBuffer(void* dst, void* src, int count)
	{
		T* ds = (T*)dst;
		T* ss = (T*)src;

		if (ds < ss)
		{
			for (int i = 0; i < count; i++)
			{
				ds[i] = MoveValue(ss[i]);
			}
		}
		else if (ds > ss)
		{
			for (int i = count - 1; i >= 0; i--)
			{
				ds[i] = MoveValue(ss[i]);
			}
		}
	}

	static void ReleaseItems(void* dst, int count)
	{
		T* ds = (T*)dst;

		for (int i = 0; i < count; i++)
		{
			ds[i].~T();
		}
	}

	static void* AllocateBuffer(int size)
	{
		if (size <= 0) return nullptr;
		return (void*)malloc(sizeof(T) * size);
	}

	static void DeallocateBuffer(void* buffer)
	{
		if (buffer == nullptr)return;
		free(buffer);
	}
public:
};

template<typename T>
class ListStore<T, true> abstract : public Object
{
protected:
	static void InitializeItemsByDefault(void* dst, int count)
	{
	}

	static void InitializeItemsByMove(void* dst, void* src, int count)
	{
		if (count > 0)
		{
			memcpy(dst, src, sizeof(T) * count);
		}
	}

	static void InitializeItemsByCopy(void* dst, void* src, int count)
	{
		if (count > 0)
		{
			memcpy(dst, src, sizeof(T) * count);
		}
	}

	static void MoveItemsInTheSameBuffer(void* dst, void* src, int count)
	{
		if (count > 0)
		{
			memmove(dst, src, sizeof(T) * count);
		}
	}

	static void ReleaseItems(void* dst, int count)
	{
	}

	static void* AllocateBuffer(int size)
	{
		if (size <= 0) return nullptr;
		return (void*)malloc(sizeof(T) * size);
	}

	static void DeallocateBuffer(void* buffer)
	{
		if (buffer == nullptr) return;
		free(buffer);
	}
public:
};

/***********************************************************************
ArrayBase
***********************************************************************/

/// <summary>Base type of all linear container.</summary>
/// <typeparam name="T">Type of elements.</typeparam>
template<typename T>
class ArrayBase abstract : public ListStore<T, POD<T>::Result>, public virtual IEnumerable<T>
{
protected:
	class Enumerator : public Object, public virtual IEnumerator<T>
	{
	private:
		const ArrayBase<T>*				container;
		int							index;

	public:
		Enumerator(const ArrayBase<T>* _container, int _index = -1)
		{
			container = _container;
			index = _index;
		}

		IEnumerator<T>* Clone()const
		{
			return new Enumerator(container, index);
		}

		const T& Current()const
		{
			return container->Get(index);
		}

		int Index()const
		{
			return index;
		}

		bool Next()
		{
			index++;
			return index >= 0 && index < container->Count();
		}

		void Reset()
		{
			index = -1;
		}
	};

	void*					buffer = nullptr;
	int					count = 0;

	static void* AddressOf(void* bufferOfTs, int index)
	{
		return (void*)((char*)bufferOfTs + sizeof(T) * index);
	}

	const T& ItemOf(int index)const
	{
		return *(const T*)AddressOf(buffer, index);
	}

	T& ItemOf(int index)
	{
		return *(T*)AddressOf(buffer, index);
	}
public:
	ArrayBase()
	{
	}

	IEnumerator<T>* CreateEnumerator()const
	{
		return new Enumerator(this);
	}

	/// <summary>Get the number of elements in the container.</summary>
	/// <returns>The number of elements.</returns>
	int Count()const
	{
		return count;
	}

	/// <summary>Get the reference to the specified element.</summary>
	/// <returns>The reference to the specified element.</returns>
	/// <param name="index">The index of the element.</param>
	const T& Get(int index)const
	{
		CHECK_ERROR(index >= 0 && index < this->count, L"ArrayBase<T, K>::Get(int)#Argument index not in range.");
		return ItemOf(index);
	}

	/// <summary>Get the reference to the specified element.</summary>
	/// <returns>The reference to the specified element.</returns>
	/// <param name="index">The index of the element.</param>
	const T& operator[](int index)const
	{
		CHECK_ERROR(index >= 0 && index < this->count, L"ArrayBase<T, K>::operator[](int)#Argument index not in range.");
		return ItemOf(index);
	}
};