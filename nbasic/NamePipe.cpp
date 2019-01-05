#include "NamePipe.h"
#include <windows.h>
#include "String.h"
#include "Basic.h"


namespace vl
{
	namespace namepipe_internal
	{
		struct NamePipeData
		{
			NamePipeData()
				:hNamePipe(0)
			{
				memset(&op, 0, sizeof(op));
			}
			WString name;
			OVERLAPPED op;
			HANDLE hNamePipe;
		};
	}

	NamePipe::NamePipe()
		:internalData(0)
	{
	}
	
	
	bool NamePipe::IsCreate()
	{
		return internalData != NULL;
	}

	bool NamePipe::Create(WString shortName, vint defBufferSize /*= 0*/)
	{
		if (IsCreate())
			return false;

		if (shortName.IndexOf(L'\\') != 0)
		{
			shortName = L"\\\\.\\pipe\\" + shortName;
		}
		HANDLE hNamePipe = CreateNamedPipe(shortName.Buffer(),
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
			PIPE_TYPE_BYTE, 1, defBufferSize, defBufferSize, 0, NULL);
		if (hNamePipe != INVALID_HANDLE_VALUE)
		{
			internalData = new namepipe_internal::NamePipeData;
			internalData->name = shortName;
			internalData->hNamePipe;
			internalData->op.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			return true;
		}
		return false;
	}

	bool NamePipe::Open(WString shortName)
	{
		if (shortName.IndexOf(L'\\') != 0)
		{
			shortName = L"\\\\.\\pipe\\" + shortName;
		}
		BOOL b = WaitNamedPipe(shortName.Buffer(), 0);
		if (b)
		{
			HANDLE hFile = CreateFile(shortName.Buffer(),
				GENERIC_READ | GENERIC_WRITE,
				0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				internalData = new namepipe_internal::NamePipeData;
				internalData->hNamePipe = hFile;
				return true;
			}
		}
		return false;
	}

	vint NamePipe::Read(void * _buffer, vint _size)
	{
		CHECK_ERROR(_size >= 0, L"NamePipe::Read(void*, vint)#Argument size cannot be negative.");
		if (!IsCreate())
			return -1;
		DWORD dwRead;
		BOOL b = ReadFile(internalData->hNamePipe, _buffer, _size, &dwRead, NULL);
		return b ? dwRead: -1;
	}

	vint NamePipe::Write(void * _buffer, vint _size)
	{
		CHECK_ERROR(_size >= 0, L"NamePipe::Read(void*, vint)#Argument size cannot be negative.");
		if (!IsCreate())
			return -1;
		DWORD dwRead;
		BOOL b = WriteFile(internalData->hNamePipe, _buffer, _size, &dwRead, NULL);
		return b ? dwRead : -1;
	}

	NamePipe::~NamePipe()
	{
		if (internalData)
		{
			if (internalData->hNamePipe)
			{
				::CloseHandle(internalData->hNamePipe);
			}
			if (internalData->op.hEvent)
			{
				::CloseHandle(internalData->op.hEvent);		
			}
			delete internalData;
		}
	}

	bool NamePipe::Connetct()
	{
		if (!IsCreate())
			return false;
		return ::ConnectNamedPipe(internalData->hNamePipe,&internalData->op) == TRUE;
	}

	void NamePipe::Disconnect()
	{
		if (internalData)
		{
			if (internalData->hNamePipe)
			{
				::DisconnectNamedPipe(internalData->hNamePipe);
			}
		}
	}

	bool NamePipe::WaitForConnect()
	{
		if (!IsCreate())
			return false;
		DWORD dw = WaitForSingleObject(internalData->op.hEvent, INFINITE);
		return dw == 0;
	}

}

