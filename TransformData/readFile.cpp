#include "stdafx.h"

#include <fstream>
#include <vector>
#include "readFile.h"
extern CString separator;
extern CString indexList;//�洢���ꡢ��������ֵ���ڵ�λ��
						  //���ݴ�1��ʼ�������±��0��ʼ����������ݼ�һ���������ָ���������ݵ�λ��

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
	{//��õķ������ڶ�ȡ��ʱ���Ѿ����ļ����ݴ���
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

/*��������д���ˣ����ܲ��ܲ���readFile���캯���У�����ѭ��������ٶ�*/
bool maple::readFile:: dealData() {
	//�Ѿ���ȡÿһ�е�data�����д���
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
		//����: "," " "
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
			}//����ͨ���� �������л�������
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
			}//����ͨ���� �������л�������
		}

		/*���ַ������д�������±�����*/
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

		//�����±�����������ѡ�����õġ������±�����



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