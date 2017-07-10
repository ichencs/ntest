#pragma once
/*
 * 
 * brief:测试Pod类型
 * POD，全称plain old data，
 *	plain代表它是一个普通类型，
 *	old代表它可以与c兼容，可以使用比如memcpy()这类c中最原始函数进行操作。
 *  详见：readme
 */
class testPod
{
public:
	testPod();
	~testPod();
private:
	void test();
	void test1();
	void test2();


};

