#pragma once
/*
 * 
 * brief:����Pod����
 * POD��ȫ��plain old data��
 *	plain��������һ����ͨ���ͣ�
 *	old������������c���ݣ�����ʹ�ñ���memcpy()����c����ԭʼ�������в�����
 *  �����readme
 */
class testPod
{
public:
	testPod();
	~testPod();
private:
	void test();
	void test_trival();		//ƽ����
	void test_layout();		//���ֵ�


};

