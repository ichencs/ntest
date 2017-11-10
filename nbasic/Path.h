#ifndef NICE_PATH
#define NICE_PATH
#include "String.h"
namespace vl
{

	namespace path
	{
		class Path : public Object
		{
		 public:
			Path();
			~Path();
			Path(const WString& _filePath);
			Path(const wchar_t* _filePath);
			Path(const Path& _filePath);
		 public:
			//************************************
			// Method:    UnquoteSpaces
			// FullName:  vl::path::Path::UnquoteSpaces
			// Access:    public
			// Returns:   vl::WString
			// Qualifier: �Ӵ����ŵ�·����ȡ��·��
			//************************************
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
			// L"c:\\Program Files\\File.txt\\" -> L"c:\\Program Files\\File.txt"
			// L"c:\\Program Files\\File.txt/" -> L"c:\\Program Files\\File.txt"
			// ȥ��·�����ķ�б�ܡ�\��(��ȥ����\��)
			//************************************
			void RemoveBackslash();
			void RemoveExtension();
			/// <summary>
			/// ��ȡ�ļ�·����·������"\\"��������Ƿ���Ч ��Ч GetFolder()
			/// �Ƴ��ļ�����/+�ļ����� ��б��
			/// L"c:\\Program Files\\File.txt\\" -> L"c:\\Program Files\\File.txt"
			/// L"c:\\Program Files\\File.txt" -> L"c:\\Program Files"
			///  L"c:\\Program Files\\File.txt/" -> L"c:\\Program Files"
			/// </summary>
			/// <returns></returns>
			bool RemoveFileSpec();
			WString FindFileName()const;
			WString FindExtension()const;
			virtual	WString						GetFullPath()const;
			
		 public:
			bool FileExists();
		 protected:
			WString						fullPath;
			virtual void				Initialize();
			
			
		};
	}
}

#endif