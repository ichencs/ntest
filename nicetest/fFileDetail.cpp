#include "stdafx.h"
#include "fFileDetail.h"
#include <Shlwapi.h>

using namespace std;
namespace fFileAttribute
{
	fFileDetail::fFileDetail()
	{
		m_pBlock = nullptr;
	}
	
	
	fFileDetail::~fFileDetail()
	{
		FreeBlock();
	}

	bool fFileDetail::Initialize(std::wstring file_path)
	{
		if (!FileExist(file_path))
		{
			return false;
		}
		FreeBlock();

		DWORD dwSize = GetFileVersionInfoSizeW(file_path.c_str(), NULL);
		m_pBlock = malloc(dwSize * sizeof(wchar_t));
		BOOL BRes = GetFileVersionInfoW(file_path.c_str(), 0, dwSize, m_pBlock);
		if (!BRes)
		{
			FreeBlock();
			return false;
		}
		DWORD* pVerValue = nullptr;
		UINT nSize = 0;
		BRes = VerQueryValueW(m_pBlock, L"\\VarFileInfo\\Translation", (LPVOID*)&pVerValue, &nSize);
		if (!BRes)
		{
			FreeBlock();
			return false;
		}
		DWORD LangCharset = MAKELONG(HIWORD(pVerValue[0]), LOWORD(pVerValue[0]));

		wchar_t strBlockName[256] = { 0 };
		int nlen = swprintf(strBlockName, sizeof(strBlockName), L"%08lx", LangCharset);//10进制转换成16进制，如果输出大写的字母是sprintf(str,"%X",a)
		m_strTranslation = strBlockName;

		return true;
	}

	std::wstring fFileDetail::InternalName()
	{
		if (m_pBlock)
		{
			wchar_t* pVerValue = NULL;
			UINT nSize = 0;
			wstring strSubBlock = L"\\StringFileInfo\\" + m_strTranslation + L"\\InternalName";
			BOOL BRes = VerQueryValue(m_pBlock, strSubBlock.c_str(), (LPVOID*)&pVerValue, &nSize);
			if (BRes)
			{
				return wstring(pVerValue);
			}
		}
		return wstring();
	}

	std::wstring fFileDetail::ProductName()
	{
		if (m_pBlock)
		{
			wchar_t* pVerValue = NULL;
			UINT nSize = 0;
			wstring strSubBlock = L"\\StringFileInfo\\" + m_strTranslation + L"\\ProductName";
			BOOL BRes = VerQueryValue(m_pBlock, strSubBlock.c_str(), (LPVOID*)&pVerValue, &nSize);
			if (BRes)
			{
				return wstring(pVerValue);
			}
		}
		return wstring();
	}

	std::wstring fFileDetail::ProductVersion()
	{
		if (m_pBlock)
		{	
			wchar_t* pVerValue = NULL;
			UINT nSize = 0;
			wstring strSubBlock = L"\\StringFileInfo\\" + m_strTranslation + L"\\ProductVersion";
			BOOL BRes = VerQueryValue(m_pBlock, strSubBlock.c_str(), (LPVOID*)&pVerValue, &nSize);
			if (BRes)
			{
				return wstring(pVerValue);
			}
		}
		return wstring();
	}

	std::wstring fFileDetail::OriginalFileName()
	{
		if (m_pBlock)
		{
			wchar_t* pVerValue = NULL;
			UINT nSize = 0;
			wstring strSubBlock = L"\\StringFileInfo\\" + m_strTranslation + L"\\OriginalFileName";
			BOOL BRes = VerQueryValue(m_pBlock, strSubBlock.c_str(), (LPVOID*)&pVerValue, &nSize);
			if (BRes)
			{
				return wstring(pVerValue);
			}
		}
		return wstring();
	}

	std::wstring fFileDetail::LegalTradeMarks()
	{
		if (m_pBlock)
		{
			wchar_t* pVerValue = NULL;
			UINT nSize = 0;
			wstring strSubBlock = L"\\StringFileInfo\\" + m_strTranslation + L"\\LegalTradeMarks";
			BOOL BRes = VerQueryValue(m_pBlock, strSubBlock.c_str(), (LPVOID*)&pVerValue, &nSize);
			if (BRes)
			{
				return wstring(pVerValue);
			}
		}
		return wstring();
	}

	std::wstring fFileDetail::CompanyName()
	{
		if (m_pBlock)
		{
			wchar_t* pVerValue = NULL;
			UINT nSize = 0;
			wstring strSubBlock = L"\\StringFileInfo\\" + m_strTranslation + L"\\CompanyName";
			BOOL BRes = VerQueryValue(m_pBlock, strSubBlock.c_str(), (LPVOID*)&pVerValue, &nSize);
			if (BRes)
			{
				return wstring(pVerValue);
			}
		}
		return wstring();
	}

	std::wstring fFileDetail::FileDescription()
	{
		if (m_pBlock)
		{
			wchar_t* pVerValue = NULL;
			UINT nSize = 0;
			wstring strSubBlock = L"\\StringFileInfo\\" + m_strTranslation + L"\\FileDescription";
			BOOL BRes = VerQueryValue(m_pBlock, strSubBlock.c_str(), (LPVOID*)&pVerValue, &nSize);
			if (BRes)
			{
				return wstring(pVerValue);
			}
		}
		return wstring();
	}

	bool fFileDetail::FileExist(const std::wstring& file_path)
	{
		return ::PathFileExists(file_path.c_str()) == TRUE;
	}

	void fFileDetail::FreeBlock()
	{
		if (m_pBlock)
		{
			free(m_pBlock);
			m_pBlock = nullptr;
		}
	}

}
