#include "stdafx.h"
#include "vc15FileSystem.h"
#include <locale.h>
#include "vc15Time.h"
#include "..\vc15-test-dlg\vc15DlgTest.h"


vc15FileSystem::vc15FileSystem()
{
}


vc15FileSystem::~vc15FileSystem()
{
}

CString vc15FileSystem::GetDllName()
{
	CString strName = GetDllNameExt();
	int nsel = strName.ReverseFind('.');
	if (nsel > 0)
	{
		strName = strName.Mid(0, nsel);
	}
	return strName;
}

CString vc15FileSystem::GetDllNameExt()
{
	CString strPath;
	HMODULE hModuleInst = _AtlBaseModule.GetModuleInstance();
	GetModuleFileName(hModuleInst, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	int nPos = strPath.ReverseFind('\\');
	CString str = strPath.Mid(nPos + 1);
	return str;
}

CString vc15FileSystem::GetDllPathName()
{
	CString strPath;
	HMODULE hModuleInst = _AtlBaseModule.GetModuleInstance();
	GetModuleFileName(hModuleInst, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	return strPath;
}

CString vc15FileSystem::GetDllPath()
{
	CString strPath;
	HMODULE hModuleInst = _AtlBaseModule.GetModuleInstance();
	GetModuleFileName(hModuleInst, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	int nPos = strPath.ReverseFind('\\');
	if (nPos >= 0)
		strPath = strPath.Left(nPos);
	return strPath;
}

CString vc15FileSystem::GetDesktopPath()
{
	CString str;
// 	str = ::GetDesktopPath();	
	::SHGetSpecialFolderPath(NULL, str.GetBufferSetLength(MAX_PATH + 1), CSIDL_DESKTOP, FALSE);
	str.ReleaseBuffer();
	return str;
}

bool vc15FileSystem::WriteDllPathFileLine(__in LPCTSTR szText)
{
	CString strfile = GetDllPathName();
	int nsel = strfile.ReverseFind('.');
	strfile = strfile.Mid(0, nsel) + _T(".txt");
	vc15Time t;
	return WriteFileLine(strfile,t.toStringTime(t.getCurrentTime()) + _T("  ") + szText);
}

bool vc15FileSystem::WriteFileLine(__in LPCTSTR szPathName, __in LPCTSTR szText)
{
	CStdioFile file;
	char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
	setlocale(LC_CTYPE, "chs");//设定，修复中文写入失败
	UINT nOpenFlags;
 	if (!PathFileExists(szPathName))
	{
		nOpenFlags = CFile::modeCreate | CFile::modeReadWrite | CFile::typeText;
	}
 	else
 	{
		nOpenFlags = CFile::modeReadWrite | CFile::typeText;
 	}
	if (!file.Open(szPathName, nOpenFlags))
		return false;
	ULONGLONG ul = file.SeekToEnd();
	file.WriteString(CString(szText) + _T("\n"));
	file.Close();

	setlocale(LC_CTYPE, old_locale);
	free(old_locale);//还原区域设定
	return true;
}


bool vc15FileSystem::SelDir(__out CString& strDir)
{
	return false;
}

bool vc15FileSystem::SelFileDlg(__in LPCTSTR defPath, __out CString& strPathName)
{
	CFileDialog ff(TRUE, _T("*.*"), defPath,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("所有文件 (*.*)|*.*||"), NULL);
	if (ff.DoModal() != IDOK)
		return false;

	strPathName = ff.GetPathName();	
	return true;
}


bool vc15FileSystem::SaveFileDlg(__in LPCTSTR savePath, __out CString& strPathName)
{
	CFileDialog ff(FALSE, _T("*.*"), savePath,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files (*.*)|*.*||"), NULL);
	if (ff.DoModal() != IDOK)
		return false;

	strPathName = ff.GetPathName();
	return true;
}


bool vc15FileSystem::SaveFile(__in LPCTSTR origin_file, __in LPCTSTR target_file, BOOL bFailIfExists /*= TRUE*/)
{
	if (!PathFileExists(origin_file) || PathFileExists(target_file))
		return false;

	BOOL b = ::CopyFile(origin_file, target_file, bFailIfExists);	//bFailIfExists = TRUE 不覆盖
	return b == TRUE;
}
