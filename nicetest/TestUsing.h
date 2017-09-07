#pragma once
#include <iostream>

using namespace std;

class Base
{
public:
	void menfcn()
	{
		cout << "Base function" << endl;
	}

	void menfcn(int n)
	{
		cout << "Base function with int" << endl;
	}
	//private:   
	//  void menfcn(std::string _name) {}//���û���usingʱ�����ɷ��ʵĴ�  
};

class Derived : private Base
{
public:
 	using Base::menfcn;//using����ֻ��ָ��һ�����֣����ܴ��βα��һ���ĸú���������˽�а汾��������뱨��  
					   //using���෽������Ҫ������ʵ�ֿ���������ʵ���е��õ���������ذ汾  
	int menfcn(int num)
	{
		cout << "Derived function with int : " << num << endl;
		return num;
	}
};

/*!
 * \class: 	TestUsing
 *
 * \brief: 	����using��ʹ��
 *
 * \author: Chencs
 * \date:	2017/09/04 
 */
class TestUsing
{
public:
	TestUsing();
	~TestUsing();

public:
	void Test();

};

