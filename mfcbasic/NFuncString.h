#pragma once
class NFuncString abstract
{
public:
	NFuncString();
	~NFuncString();
public:
	/// <summary>
	/// ÊÇ/·ñ£»yes/no ×ª bool
	/// </summary>
	/// <param name="szVal"></param>
	/// <returns></returns>
	static bool ParseBool(LPCTSTR szVal);
	static bool ParseBool(int nVal);

};

