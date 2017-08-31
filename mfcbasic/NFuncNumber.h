#pragma once
class NFuncNumber abstract
{
public:
	NFuncNumber();
	~NFuncNumber();

	/// <summary>
	/// 解决 -0 的问题
	/// </summary>
	/// <param name="d"></param>
	/// <param name="nprecision"> 小数点后位数 </param>
	/// <returns></returns>
	static double ParseZero(double d, int nprecision = 3);
	static double ParseZeroEx(double& d,int nprecision = 3);
	/// <summary>
	/// 四舍五入
	/// </summary>
	/// <param name="d">输入值</param>
	/// <param name="nprec"> 小数点后位数 </param>
	/// <returns></returns>
	static double ParsePercision(double d,int nprec = 3);
	static CString ParseString(double d, int nprec = 3);
	static CString ParseString(int n);


};

