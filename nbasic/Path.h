#ifndef NICE_PATH
#define NICE_PATH
#include "String.h"
namespace vl
{
	
	namespace path
	{
		class Path :public Object
		{
		public:
			Path();
			~Path();
			Path(const WString& _filePath);
			Path(const wchar_t* _filePath);
			Path(const Path& _filePath);
		public:
			WString UnquoteSpaces();
			bool IsDirectory();
			//************************************
			// Method:    IsFileSpec
			// FullName:  vl::path::Path::IsFileSpec
			// Access:    public 
			// Returns:   bool
			// Qualifier:
			// ���ܣ����·�����Ƿ���� ��:�� �� ��\�� �ָ���
			//************************************
			bool IsFileSpec();
			bool IsUNC();
			bool IsUNCServer();
			bool IsUNCServerShare();
			bool IsURL();
			bool IsNetworkPath();
			bool IsPrefix(WString strPrefix);
			//************************************
			// Method:    MatchSpec
			// FullName:  vl::path::Path::MatchSpec
			// Access:    public 
			// Returns:   bool
			// Qualifier:
			// Parameter: WString strSpec
			// �ô���ͨ�����*�ź�?�ţ����ַ���ȥ�Ƚ���һ���ַ���
			// PathMatchSpec( ��http://news.sina.com.cn�� , ��*sina.com*�� ) ����TRUE
			//************************************
			bool MatchSpec(WString strSpec);
		public:
			//************************************
			// Method:    RemoveBackslash
			// FullName:  vl::path::Path::RemoveBackslash
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// ȥ��·�����ķ�б�ܡ�\��
			//************************************
			void RemoveBackslash();
			void RemoveExtension();
			bool RemoveFileSpec();
		public:
			WString FindFileName();
			bool FileExists();
		protected:
			WString						fullPath;
			virtual void				Initialize();
		
		
		};
	}
}

#endif