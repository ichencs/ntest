#pragma once
class NFuncNumber abstract
{
public:
	NFuncNumber();
	~NFuncNumber();

	/// <summary>
	/// ��� -0 ������
	/// </summary>
	/// <param name="d"></param>
	/// <param name="nprecision"> С�����λ�� </param>
	/// <returns></returns>
	static double ParseZero(double d, int nprecision = 3);
	static double ParseZeroEx(double& d,int nprecision = 3);
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="d">����ֵ</param>
	/// <param name="nprec"> С�����λ�� </param>
	/// <returns></returns>
	static double ParsePercision(double d,int nprec = 3);
	static CString ParseString(double d, int nprec = 3);
	static CString ParseString(int n);


};

