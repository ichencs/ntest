#include "stdafx.h"
#include "vlpp/Vlpp.h"
#include <math.h>

namespace tnum
{
	struct sCurveSizeInfo
	{
		sCurveSizeInfo() : nCount(0),
			dCommonSize(0.0),
			dRemainder(0.0),
			bRemainderValid(false)
		{}
		int nCount;					//数量
		double dCommonSize;			//常量
		double dRemainder;		//余量
		bool bRemainderValid;
	};
	
	// 	int Compair(double d1, double d2, int nPrecision)
	// 	{
	// 		double dtol = nPrecision > 0 ? pow(0.10, nPrecision) : 0.0;
	// 		return Compair(d1, d2, dtol);
	// 	}
	double GetTolerance(int nprecision)
	{
		return nprecision > 0 ? pow(0.10, nprecision) : 0.0;
	};
	
	int Compair(double d1, double d2, double dtolerance)
	{
		if (d1 - d2 > dtolerance)
		{
			return 1;
		}
		else
			if (d2 - d1 > dtolerance)
			{
				return -1;
			}
			
		return 0;
	}
	
	// 	double ZeroNumber(const double& d, int nprecision = 3)
	// 	{
	// 		double dtol = pow(0.10, nprecision);
	//
	// 		return ZeroNumber(d, dtol);
	// 	}
	
	double ZeroNumber(const double& d, double dtolerance = 0.001)
	{
		if (fabs(d) < dtolerance)
		{
			return 0.0;
		}
		
		return d;
	}
	
	bool GetSuperiorSize(double dTotal, double dMaxSize, double dMinSize, sCurveSizeInfo& scurve, int nprecision = 3)
	{
		if (Compair(dTotal, dMinSize, GetTolerance(nprecision)) < 0)
		{
			return false;
		}
		
		double dtol = pow(0.10, nprecision + 1);
		scurve.dCommonSize = dMaxSize;
		scurve.nCount = (int)floor(dTotal / dMaxSize);
		scurve.dRemainder = fmod(dTotal, dMaxSize);
		
		if (scurve.dRemainder > dtol)
		{
			scurve.nCount++;
			scurve.bRemainderValid = true;
		}
		else
			if (scurve.dRemainder == 0.0)
			{
				scurve.nCount;
				scurve.bRemainderValid = false;
			}
			else
			{
				// 				scurve.nCount--;
				scurve.bRemainderValid = false;
			}
			
		return true;
	}
}
TEST_CASE(TestFloatNum)
{
	using namespace tnum;
	sCurveSizeInfo info1;
	GetSuperiorSize(100, 1.0, 0.5, info1);
	GetSuperiorSize(99, 2.0 / 6.0, 1.0 / 3.0, info1);
	
	
	
	
}