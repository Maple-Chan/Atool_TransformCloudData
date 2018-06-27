#pragma once
#include <string>
#include <vector>


namespace maple
{
	class readFile {
		std:: string fileSrc;
		std:: string fileDst;
		std::vector<std::string> dataLines;
	public:
		readFile() {}
		readFile(std::string fsrc, std::string fdst);
		bool dealData();
	};







}


