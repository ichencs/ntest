#pragma once

#pragma pack(push, 8)

struct MemoryA
{
	bool a;
	int b;
	bool c;
	double d;
	bool e;
};


struct MemoryB
{
	double d;
	int b;
	bool a;
	bool c;
	bool e;
};

struct MemoryC
{
	bool a;
	bool c;
	bool e;
	int b;
	double d;
};

#pragma pack(pop)

/*!
 * \class: 	testMemoryAlignment
 *
 * \brief: 	ÄÚ´æ¶ÔÆë²âÊÔ
 *
 * \author: Chencs
 * \date:	2017/08/15 
 */
class testMemoryAlignment
{
public:
	testMemoryAlignment();
	~testMemoryAlignment();
public:
	void test();

};

