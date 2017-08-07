#pragma once

#include<iostream>
#include<set>
#include<string>
class CObservable;


/*!
 * \class: 	CObserver
 *
 * \brief: 	�۲��ߣ����ࣩ
 *
 * \author: Chencs
 * \date:	2017/08/07 
 */
class CObserver
{
public:
	CObserver::CObserver() {};
	virtual CObserver::~CObserver() {};
	//�����۲��Ŀ�귢���仯ʱ��֪ͨ���ø÷���
	//���Ա��۲���pObs,��չ����ΪpArg
	virtual void Update(CObservable*pObs, void*pArg = NULL) = 0;
};


/*!
 * \class: 	CObservable
 *
 * \brief: 	���۲����
 *
 * \author: Chencs
 * \date:	2017/08/07 
 */
class CObservable
{
public:
	CObservable() :m_bChanged(false) {};
	virtual~CObservable() {};
	//ע��۲���

	void Attach(CObserver*pObs);
	//ע���۲���
	void Detach(CObserver*pObs);
	//ע�����й۲���
	void DetachAll();
	//��״̬�仯��������۲��ߣ����֪ͨ����
	void Notify(void*pArg = NULL);
	//����Ŀ��״̬�Ƿ�仯
	bool HasChanged();
	//��ȡ�۲�������
	int GetObserversCount();
protected:
	//����״̬�仯!!!����̳�CObservable��������Ŀ��״̬
	void SetChanged();
	//��ʼ��Ŀ��Ϊδ�仯״̬
	void ClearChanged();
private:
	bool m_bChanged;//״̬
	set<CObserver*>m_setObs;//set��֤Ŀ��Ψһ��

};

