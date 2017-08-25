#pragma once

/*----------------------------------------------*\
	������
		regex_match 
		regex_search 
		regex_replace 
		regex_format 
		regex_grep 
		regex_split 

	��������
		regex_iterator
		regex_token_iterator ������

		//http://regexr.com/
\*----------------------------------------------*/
class testRegex
{
public:
	testRegex();
	~testRegex();
protected:
	void test();
	
protected:	//match
	void match();
	void match_date();
	void match_date2();
	void match_ip();
	void match_ip2();

	void match_url();	//��url���ʽ
	void match_url2();	//��ϸurl�������ʽ
	void match_email();
	void match_email2();
	void match_chs();
	void match_pid();
private:
	void match_res(std::string reg,std::wstring name,std::string text);
	void match_res(std::string reg, std::wstring name, std::vector<std::string> vtext);

protected:
	void search();
	void search1();
	void search2();

protected:
	void replace();
	void replace1();
	void replace2();

protected:
	void format();
	void split();



};

