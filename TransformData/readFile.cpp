#include "stdafx.h"

#include <fstream>
#include <vector>
#include "readFile.h"
extern CString separator;
extern CString indexList;//存储坐标、向量各个值所在的位置
						  //数据从1开始；数组下标从0开始，这里的数据减一才是真正分割出来的数据的位置

maple::readFile::readFile(std::string fsrc, std::string fdst) :fileSrc(fsrc), fileDst(fdst) {
	std::ifstream infile;
	std::ofstream outfile;

	outfile.open(fileDst);
	infile.open(fileSrc);
	dataLines.clear();
	if (!infile)
	{
		outfile << "input data cannot be open!";
	}
	else
	{//最好的方法是在读取的时候已经对文件内容处理
		while (!infile.eof())
		{
			std::string line;
			while (getline(infile, line)) {
				dataLines.push_back(line);
			}
		}
	}
	infile.close();

}

/*如果这里的写好了，看能不能并入readFile构造函数中，减少循环，提高速度*/
bool maple::readFile:: dealData() {
	//已经获取每一行的data，进行处理
	/*std::vector<int> indexInLines;*/

	size_t index;
	std::vector<std::string> inLines;
	std::vector<std::string> dataOutLines;


	//CString to string
	std::string separate;
	separate = CStringA(separator);
	if (separate[0] < 0)
	{
		return false;
	}

	std::string  indexNum;
	indexNum = CStringA(indexList);

/*	std::ofstream debug;
	debug.open("debug.txt");
	debug << separate << std::endl;

	for (int i = 0; i < indexNum.size(); ++i)
	{
		debug << indexNum[i];
	}
	debug.close();*/
	//------------------

	for (int i = 0; i < dataLines.size(); ++i)
	{
		if (dataLines[i][0] == '#')
			continue;//


		dataOutLines.resize( dataLines.size() );
		inLines.clear();
		dataLines[i];
		//需求: "," " "
		if (separate=="")
		{
			if ((index = dataLines[i].find(' ')) == std::string::npos  
				&& (index = dataLines[i].find(',')) == std::string::npos)
			{
				return false;
			}

			while ((index = dataLines[i].find(',')) != std::string::npos)
			{
				dataLines[i][index] = ' ';
			}//下面通过‘ ’来进行划分数据
		}
		else if ((separate == " "))
		{
			;
		}
		else
		{
			if ((index = dataLines[i].find(separate)) == std::string::npos)
			{
				return false;
			}
			while ((index = dataLines[i].find(separate)) != std::string::npos)
			{
				dataLines[i][index] = ' ';
			}//下面通过‘ ’来进行划分数据
		}

		/*对字符串进行处理，获得下标数据*/
		std::vector<int> indexlist;
		
		for (int j = 0; j < indexNum.size(); ++j)
		{
			if (indexNum[j] != ' ')
			{
				indexlist.push_back( std::stoi(&indexNum[j]) - 1);
			}
		}

		/*std::ofstream debug;
		debug.open("debug.txt");
		debug << separate << std::endl;

		for (int j = 0; j < indexlist.size(); ++j)
		{
			debug << indexlist[j];
		}
		debug.close();*/


		do
		{
			std::string tmp_s = "";
			index = dataLines[i].find(" ");
			if (-1 == index)
			{
				tmp_s = dataLines[i].substr(0, dataLines[i].length());
				inLines.push_back(tmp_s);
				break;
			}
			if (-1 != index)
			{
				tmp_s = dataLines[i].substr(0, index);
				dataLines[i].erase(0, index + 1);
				inLines.push_back(tmp_s);
			}
		} while (true);

		//根据下标数据来进行选择有用的。假设下标数据



		std::string normal = "0 0 1 3 0 1 0";
		dataOutLines[i] = "";

		for (int j = 0; j < indexlist.size(); ++j)
		{
			dataOutLines[i] = dataOutLines[i]+inLines[indexlist[j]] + " ";
		}
		dataOutLines[i] += normal;

		indexlist.clear();
	}

	std::ofstream outfile;
	outfile.open(fileDst);
	if (!outfile)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < dataOutLines.size(); ++i)
		{
			if (dataLines[i][0] == '#')
				continue;//
			outfile << dataOutLines[i] << std::endl;
		}
	}

	outfile.close();
	dataOutLines.clear();
	inLines.clear();
	dataLines.clear();
	return true;
}