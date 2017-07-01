#pragma once

class testFileSystem
{
public:
	testFileSystem();
	~testFileSystem();

public:
	static CString GetDllName();			//不带扩展名
 	static CString GetDllNameExt();			//带扩展名
	static CString GetDllPathName();		//全名
	static CString GetDllPath();
	static CString GetDesktopPath();
	static bool WriteDllPathFileLine(__in LPCTSTR szText);
	static bool WriteFileLine(__in LPCTSTR szPathName, __in LPCTSTR szText);

	//DLG
public:
	static bool SelDir(__out CString& strDir);
	static bool SelFileDlg(__in LPCTSTR defPath ,__out CString& strPathName);
	static bool SaveFileDlg(__in LPCTSTR savePath, __out CString& strPathName);
	static bool SaveFile(__in LPCTSTR origin_file,__in LPCTSTR target_file,BOOL bFailIfExists = TRUE);

public:
	static bool UrlFileSaveAs(__in LPCTSTR szUrl, __in LPCTSTR szPath);
};

