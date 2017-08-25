#pragma once

/*----------------------------------------------*\
	函数：
		regex_match 
		regex_search 
		regex_replace 
		regex_format 
		regex_grep 
		regex_split 

	迭代器：
		regex_iterator
		regex_token_iterator 迭代器

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

	void match_url();	//简单url表达式
	void match_url2();	//详细url解析表达式
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

