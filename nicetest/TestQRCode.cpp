#include "stdafx.h"
#include "qrcode\qr.h"
#include <iostream>
#include <fstream>  

using namespace vl;
using namespace vl::console;

using namespace std;

TEST_CASE(TestQRCode)
{
	int errcode = QR_ERR_NONE;
	//qrInit的5个参数分别是version,mode,纠错等级和掩码，使用过程中使用除了QR_EM_8BIT以外的mode会生成不正常的二维码，暂时不知道原因。
	QRCode* p = qrInit(10, QR_EM_8BIT, 2, -1, &errcode);
	if (p == NULL)
	{
		printf("error\n");
		return  ;
	}

	AString strData = "http://www.baidu.com中文";
	qrAddData(p, (const qr_byte_t*)strData.Buffer(), strData.Length());
	//注意需要调用qrFinalize函数
	if (!qrFinalize(p))
	{
		printf("finalize error\n");
		return  ;
	}
	int size = 0;
	//两个5分别表示：像素之间的距离和二维码图片的放大倍数，范围都是1-16
	qr_byte_t * buffer = qrSymbolToPNG(p, 5, 5, &size);
	if (buffer == NULL)
	{
		printf("error %s", qrGetErrorInfo(p));
		return ;
	}
	ofstream f("a.png");
	f.write((const char *)buffer, size);
	f.close();
	return  ;


}