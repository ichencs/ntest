#pragma once

#include<iostream>
#include<set>
#include<string>
class CObservable;


/*!
 * \class: 	CObserver
 *
 * \brief: 	观察者（基类）
 *
 * \author: Chencs
 * \date:	2017/08/07 
 */
class CObserver
{
public:
	CObserver::CObserver() {};
	virtual CObserver::~CObserver() {};
	//当被观察的目标发生变化时，通知调用该方法
	//来自被观察者pObs,扩展参数为pArg
	virtual void Update(CObservable*pObs, void*pArg = NULL) = 0;
};


/*!
 * \class: 	CObservable
 *
 * \brief: 	被观察对象
 *
 * \author: Chencs
 * \date:	2017/08/07 
 */
class CObservable
{
public:
	CObservable() :m_bChanged(false) {};
	virtual~CObservable() {};
	//注册观察者

	void Attach(CObserver*pObs);
	//注销观察者
	void Detach(CObserver*pObs);
	//注销所有观察者
	void DetachAll();
	//若状态变化，则遍历观察者，逐个通知更新
	void Notify(void*pArg = NULL);
	//测试目标状态是否变化
	bool HasChanged();
	//获取观察者数量
	int GetObserversCount();
protected:
	//设置状态变化!!!必须继承CObservable才能设置目标状态
	void SetChanged();
	//初始化目标为未变化状态
	void ClearChanged();
private:
	bool m_bChanged;//状态
	set<CObserver*>m_setObs;//set保证目标唯一性

};

