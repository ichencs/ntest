#include "stdafx.h"
#include "testNice.h"
#include "Bloger.h"
// #include <ncrypt.h>

#include "winsock2.h"
#include <cmath>
#pragma comment(lib,"ws2_32.lib")


testNice::testNice()
{
	test();
}


testNice::~testNice()
{
}

void testNice::test()
{
	double d1 = 1.23456789;
	double d2 = dPrecision(d1);

	testSizeof();
	testDomain();
// 	testIP();
// 	testObserve();
// 	testMd5();
}

void funSizeof(int *P)
{
	cout << "���飨��ָ�룩�ں����У�" << sizeof(P) << endl;
}

void testNice::testSizeof()
{
	int A[10] = {0};
	int* B = new int[10];
	cout << "���鳤��" << sizeof(A) << endl;
	cout << "ָ�볤��" << sizeof(B) << endl;
	funSizeof(A);
}

void testNice::testObserve()
{
	CBloger* pBloger = new CBloger();
	CPortal* pPortal = new CPortal();
	//�۲���.һ���۲��߿��Թ۲���Ŀ��
	CRSSReader* pRssReader = new CRSSReader("rss reader");
	CMailReader* pMailReader = new CMailReader("mail reader");
	pBloger->Attach(pRssReader);//blogerע��۲���
	pBloger->Attach(pMailReader);//blogerע��۲���
	pPortal->Attach(pRssReader);//portalע��۲���
	pPortal->Attach(pMailReader);//portalע��۲���
								 //���ͷ�����Ϣ
	pBloger->Publish("���ͷ������ģʽ");
	cout << endl;
	//�Ż�������Ϣ
	pPortal->Publish("�Ż��������ģʽ");
	cout << "\n portal detached mail reader" << endl;
	pPortal->Detach(pMailReader);
	cout << "portal observers count:" << pPortal->GetObserversCount() << endl << endl;
	pPortal->Publish("�Ż��������ģʽ");
}


// void testNice::testIP()
// {
// 	WSADATA wsaData;
// 	char name[155] = {0};
// 	char *ip;
// 	PHOSTENT hostinfo;
// 	if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)
// 	{
// 		if (gethostname(name, sizeof(name)) == 0)
// 		{
// 			printf("hostname=%s\n", name);
// 			if ((hostinfo = gethostbyname(name)) != NULL)
// 			{
// 				ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list); //�õ���ַ�ַ���
// 				printf("local host ip: %s\n", ip);
// 			}
// 		}
// 		WSACleanup();
// 	}
// }

void testNice::testDomain()
{
}

double testNice::dPrecision(double d, int npre)
{
	double dp = pow(10.0, npre);
	d = floor(d * dp + 0.5) / dp;
	return d;
}





