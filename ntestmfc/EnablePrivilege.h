#pragma once
class EnablePrivilege
{
public:
	EnablePrivilege();
	~EnablePrivilege();
public:          
	//
	//���õ�ǰ�������ȼ�Ϊ���(ʵʱ)
	//
	BOOL SetRealTimePriority();

	//
	//������ǰ����Ȩ�޺���("SeShutdownPrivilege"�ػ�Ȩ��)
	//
	BOOL EnableShutdownPriv();

	//
	//������ǰ����Ȩ�޺���("SeDebugPrivilege"����д����Ȩ��)
	//
	BOOL EnableDebugPriv();

	//
	//������ǰ����Ȩ�޺���("SeBackupPrivilege"ע�����Ȩ��)
	//
	BOOL EnableBackupPriv();

	//
	//������ǰ����Ȩ�޺���("SeRestorePrivilege"�ָ�����Ȩ��)
	//
	BOOL EnableRestorePriv();

private:           //˽��(�ڲ�ʹ�õĽӿ�)


};

