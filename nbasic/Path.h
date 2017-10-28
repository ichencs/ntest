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
			// 功能：检查路径中是否带有 ‘:’ 和 ‘\’ 分隔符
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
			// 用带有通配符（*号和?号）的字符串去比较另一个字符串
			// PathMatchSpec( “http://news.sina.com.cn” , “*sina.com*” ) 返回TRUE
			//************************************
			bool MatchSpec(WString strSpec);
		public:
			//************************************
			// Method:    RemoveBackslash
			// FullName:  vl::path::Path::RemoveBackslash
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// 去除路径最后的反斜杠“\”
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