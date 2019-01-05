#pragma once
// #include <windef.h>
#include <string>

namespace fFileAttribute
{
	class fFileDetail
	{
	public:
		fFileDetail();
		~fFileDetail();
	public:
		bool Initialize(std::wstring file_path);

		std::wstring InternalName();
		std::wstring ProductName();
		std::wstring ProductVersion();

		std::wstring OriginalFileName();
		std::wstring LegalTradeMarks();
		std::wstring CompanyName();
		std::wstring FileDescription();


	public:
		static bool FileExist(const std::wstring& file_path);
		
	private:
		void FreeBlock();

	private:
		LPVOID m_pBlock ;
		std::wstring m_strTranslation;
	};
	
}
