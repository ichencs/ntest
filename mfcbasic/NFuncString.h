#pragma once
class NFuncString abstract
{
public:
	NFuncString();
	~NFuncString();
public:
	/// <summary>
	/// ��/��yes/no ת bool
	/// </summary>
	/// <param name="szVal"></param>
	/// <returns></returns>
	static bool ParseBool(LPCTSTR szVal);
	static bool ParseBool(int nVal);

};

