#pragma once


using namespace std;

#include<iostream>
#include<set>
#include<string>
#include "Observable.h"

class CBloger :public CObservable
{
public:
	CBloger();
	~CBloger();

public:
	void Publish(const string& strContent)
	{
		cout << "bloger publish, content:" << strContent << endl;
		SetChanged();
		Notify(const_cast<char*>(strContent.c_str()));
	}
};


//portal是发布者，即被观察者(subject)
class CPortal:public CObservable
{
public:
	void Publish(const string&strContent)
	{
		cout << "portal publish, content:" << strContent << endl;
		SetChanged();
		Notify(const_cast<char*>(strContent.c_str()));
	}
};
		

	//RSS阅读器，观察者
	class CRSSReader:public CObserver
	{
	public:
		CRSSReader(const string&strName) :m_strName(strName) {}
		virtual void Update(CObservable*pObs,void*pArg = NULL)
		{
			char*pContent = static_cast<char*>(pArg);
			//观察多个目标
			if (dynamic_cast<CBloger*>(pObs))
			{
				cout << m_strName << "updated from bloger,content:" << pContent << endl;
			}
			else if(dynamic_cast<CPortal*>(pObs))
			{
				cout << m_strName << "updated from portal,content:" << pContent << endl;
			}
		}
	private:
		string m_strName;
	};


		//Mail阅读器，观察者
	class CMailReader: public CObserver
	{
	public:
		CMailReader(const string&strName) :m_strName(strName) {}
		virtual void Update(CObservable*pObs,void*pArg = NULL)
		{
			char*pContent = static_cast<char*>(pArg);
			if (dynamic_cast<CBloger*>(pObs))
			{
				cout << m_strName << "updated from bloger,content:" << pContent << endl;
			}
			if (dynamic_cast<CPortal*>(pObs))
			{
				cout << m_strName << "updated from portal,content:" << pContent << endl;
			}
		}
	private:
		string m_strName;
	};


