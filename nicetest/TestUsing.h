#pragma once
#include <iostream>

using namespace std;

namespace TestUsing
{
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
		//  void menfcn(std::string _name) {}//会让基类using时报不可访问的错
	};
	
	class Derived : private Base
	{
	 public:
		using Base::menfcn;//using声明只能指定一个名字，不能带形参表，且基类的该函数不能有私有版本，否则编译报错
		//using父类方法，主要是用来实现可以在子类实例中调用到父类的重载版本
		int menfcn(int num)
		{
			cout << "Derived function with int : " << num << endl;
			return num;
		}
	};
	
}

