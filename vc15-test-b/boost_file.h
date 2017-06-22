#pragma once
#include "boost/filesystem/operations.hpp"

namespace bf = boost::filesystem;
class boost_file
{
public:
	boost_file();
	~boost_file();
public:
	bf::path current_path();

};

