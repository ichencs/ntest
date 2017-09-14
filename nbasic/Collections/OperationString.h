/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Operations

***********************************************************************/

#ifndef VCZH_COLLECTIONS_OPERATIONSTRING
#define VCZH_COLLECTIONS_OPERATIONSTRING

#include "Interfaces.h"
#include "../String.h"
#include "OperationCopyFrom.h"

namespace vl
{
	namespace collections
	{
		template<typename Ds, typename S>
		void CopyFrom(Ds& ds, const ObjectString<S>& ss, bool append = false)
		{
			const S* buffer = ss.Buffer();
			vint count = ss.Length();
			CopyFrom(ds, buffer, count, append);
		}
		
		template<typename D, typename Ss>
		void CopyFrom(ObjectString<D>& ds, const Ss& ss, bool append = false)
		{
			Array<D> da(ds.Buffer(), ds.Length());
			CopyFrom(da, ss, append);
			
			if (da.Count() == 0)
			{
				ds = ObjectString<D>();
			}
			else
			{
				ds = ObjectString<D>(&da[0], da.Count());
			}
		}
	}
	
	template<typename D, typename Ss>
	void SplitString(const ObjectString<D>& ds, Ss& lst, D delimiter)
	{
		vint index = -1;
		vint length = ds.Length();
		vint start;
		
		while (true)
		{
			start = index + 1;
			index = ds.IndexOf(delimiter, start);
			
			if (index < 0)
			{
				break;
			}
			
			lst.Add(ds.Sub(start, index - start));
		}
		
		if (start >= length)
		{
			start = 0;
			length = 0;
		}
		
		lst.Add(ds.Sub(start, length - start));
	}
	
}

#endif