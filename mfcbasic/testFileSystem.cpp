#include "stdafx.h"
#include "testFileSystem.h"
#include <locale.h>
#include "testTime.h"
// #include "..\ntestdlg\vc15DlgTest.h"


testFileSystem::testFileSystem()
{
}


testFileSystem::~testFileSystem()
{
}

CString testFileSystem::GetDllName()
{
	CString strName = GetDllNameExt();
	int nsel = strName.ReverseFind('.');
	if (nsel > 0)
	{
		strName = strName.Mid(0, nsel);
	}
	return strName;
}

CString testFileSystem::GetDllNameExt()
{
	CString strPath;
	HMODULE hModuleInst = _AtlBaseModule.GetModuleInstance();
	GetModuleFileName(hModuleInst, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	int nPos = strPath.ReverseFind('\\');
	CString str = strPath.Mid(nPos + 1);
	return str;
}

CString testFileSystem::GetDllPathName()
{
	CString strPath;
	HMODULE hModuleInst = _AtlBaseModule.GetModuleInstance();
	GetModuleFileName(hModuleInst, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	return strPath;
}

CString testFileSystem::GetDllPath()
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

CString testFileSystem::GetDesktopPath()
{
	CString str;
// 	str = ::GetDesktopPath();	
	::SHGetSpecialFolderPath(NULL, str.GetBufferSetLength(MAX_PATH + 1), CSIDL_DESKTOP, FALSE);
	str.ReleaseBuffer();
	return str;
}

bool testFileSystem::WriteDllPathFileLine(__in LPCTSTR szText)
{
	CString strfile = GetDllPathName();
	int nsel = strfile.ReverseFind('.');
	strfile = strfile.Mid(0, nsel) + _T(".txt");
	testTime t;
	return WriteFileLine(strfile,t.toStringTime(t.getCurrentTime()) + _T("  ") + szText);
}

bool testFileSystem::WriteFileLine(__in LPCTSTR szPathName, __in LPCTSTR szText)
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
// 	ULONGLONG ul = file.SeekToEnd();
	file.WriteString(CString(szText) + _T("\n"));
	file.Close();

	setlocale(LC_CTYPE, old_locale);
	free(old_locale);//还原区域设定
	return true;
}


bool testFileSystem::SelDir(__out CString& strDir)
{
	return false;
}

bool testFileSystem::SelFileDlg(__in LPCTSTR defPath, __out CString& strPathName)
{
	CFileDialog ff(FALSE, _T("*.*"), defPath,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("所有文件 (*.*)|*.*||"), NULL);
	if (ff.DoModal() != IDOK)
		return false;

	strPathName = ff.GetPathName();	
	return true;
}


bool testFileSystem::SaveFileDlg(__in LPCTSTR savePath, __out CString& strPathName)
{
	CFileDialog ff(FALSE, _T("*.*"), savePath,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files (*.*)|*.*||"), NULL);
	if (ff.DoModal() != IDOK)
		return false;

	strPathName = ff.GetPathName();
	return true;
}


bool testFileSystem::SaveFile(__in LPCTSTR origin_file, __in LPCTSTR target_file, BOOL bFailIfExists /*= TRUE*/)
{
	if (!PathFileExists(origin_file) || PathFileExists(target_file))
		return false;

	BOOL b = ::CopyFile(origin_file, target_file, bFailIfExists);	//bFailIfExists = TRUE 不覆盖
	return b == TRUE;
}

bool testFileSystem::UrlFileSaveAs(__in LPCTSTR szUrl, __in LPCTSTR szPath)
{
		SHFILEOPSTRUCT FileOp = { 0 };
		FileOp.fFlags = FOF_ALLOWUNDO         //允许放回回收站
			| FOF_NOCONFIRMATION    //不出现确认对话框
									//                   |FOF_SILENT            //Does not display a progress dialog box. 
									//                   |FOF_NOERRORUI        //No user interface will be displayed if an error occurs.
			| FOF_NOCONFIRMMKDIR    //如需要创建新文件夹，直接创建，不需确认
									//                   |FOF_RENAMEONCOLLISION //如果文件(夹)已存在，自动为其添加序列号修改文件名。此时不会出现确认对话框
									//                   |FOF_MULTIDESTFILES     //把文件夹里的多个文件复制过去，而不是直接复制一个文件夹
									//                   |FOF_SIMPLEPROGRESS  //Displays a progress dialog box but does not show the file names
									//                   |FOF_CONFIRMMOUSE    //Not currently implemented. 
			;            //注意这里需要分号
		FileOp.pFrom = szUrl;
		FileOp.pTo = szPath;
		FileOp.wFunc = FO_COPY;
		return SHFileOperation(&FileOp) == 0;
}

