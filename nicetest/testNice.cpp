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
	cout << "数组（或指针）在函数中：" << sizeof(P) << endl;
}

void testNice::testSizeof()
{
	int A[10] = {0};
	int* B = new int[10];
	cout << "数组长度" << sizeof(A) << endl;
	cout << "指针长度" << sizeof(B) << endl;
	funSizeof(A);
}

void testNice::testObserve()
{
	CBloger* pBloger = new CBloger();
	CPortal* pPortal = new CPortal();
	//观察者.一个观察者可以观察多个目标
	CRSSReader* pRssReader = new CRSSReader("rss reader");
	CMailReader* pMailReader = new CMailReader("mail reader");
	pBloger->Attach(pRssReader);//bloger注册观察者
	pBloger->Attach(pMailReader);//bloger注册观察者
	pPortal->Attach(pRssReader);//portal注册观察者
	pPortal->Attach(pMailReader);//portal注册观察者
								 //博客发布信息
	pBloger->Publish("博客分享设计模式");
	cout << endl;
	//门户发布信息
	pPortal->Publish("门户分享设计模式");
	cout << "\n portal detached mail reader" << endl;
	pPortal->Detach(pMailReader);
	cout << "portal observers count:" << pPortal->GetObserversCount() << endl << endl;
	pPortal->Publish("门户分享设计模式");
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
// 				ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list); //得到地址字符串
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





