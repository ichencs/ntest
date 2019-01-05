#pragma once
#include "Basic.h"
#include "String.h"

namespace vl
{
	namespace namepipe_internal
	{
		struct NamePipeData;
	}
	class NamePipe:
		public NotCopyable
	{
	public:
		NamePipe();
		virtual ~NamePipe();
		bool IsCreate();
 		bool Create(WString shortName,vint defBufferSize = 0);
		bool Open(WString shortName);

	public:
		vint Read(void* _buffer,vint _size);
		vint Write(void* _buffer, vint _size);
	public:		//serverʹ��
		bool WaitForConnect();
		bool Connetct();		//ʹclient������
		void Disconnect();		//

	protected:
		namepipe_internal::NamePipeData* internalData;
	};
}

