#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "gtest/gtest.h"

#define FILENAMEIN "in2.txt"
#define FILENAMEOUT "out.txt"

void remAllMatchedWords(std::string &sLine, std::string sToRemove);
std::string upperCase(std::string sString);


class DoTest : public ::testing::Test {};

TEST_F(DoTest, Check_remAllMatchedWords) {
	std::string sLine("Hello, world and the world's beautiful sky");
	std::string sToRemove("world");
	remAllMatchedWords(sLine, sToRemove);
	ASSERT_TRUE("Hello,  and the 's beautiful sky" == sLine);
}

TEST_F(DoTest, Check_upperCase) {
	std::string sLine("Hello, world!");
	std::string sToCompare("HELLO, WORLD!");
	ASSERT_TRUE(sToCompare == upperCase(sLine));
}

TEST_F(DoTest, Check_Comparing) {
	std::string sLine("hello, friend!");
	std::string sToCompare("HELLO, world!");
	ASSERT_TRUE(upperCase(sLine) < upperCase(sToCompare));
}

TEST_F(DoTest, Check_OpenFileIn) {
	std::ifstream fin(FILENAMEIN);
	ASSERT_TRUE(fin.is_open());
	fin.close();
}

TEST_F(DoTest, Check_OpenFileOut) {
	std::ofstream fout(FILENAMEOUT);
	ASSERT_TRUE(fout.is_open());
	fout.close();
}


int main(int nNumberOfArgs, char* pszArgs[]) {
	//::testing::InitGoogleTest(&nNumberOfArgs, pszArgs);
	//return RUN_ALL_TESTS();

	std::ifstream fin(FILENAMEIN);
	std::ofstream fout(FILENAMEOUT);
	std::string sCurLine, sLeastLine, sToRemove;
	bool* pbUsedLines = nullptr;
	int iNumOfLine = 0;
	int iNumOfLines = 0;
	int iNumOfLeastLine = 0;
	bool bIsFirstIteration = false;

	std::cout << "Enter the word, you want to remove: ";
	std::cin >> sToRemove;

	//��������� ���������� ����� � �����
	while (!fin.eof()) {
		std::getline(fin, sCurLine);
		++iNumOfLine;
	}
	iNumOfLines = iNumOfLine;
	iNumOfLine = 0;

	//������, ��� ������ �������� ����� ������ �����, � ������ �������� ����������, ���������� �� �� ��� ��� ������.
	pbUsedLines = new bool[iNumOfLines];
	for (int i = 0; i < iNumOfLines; ++i) {
		pbUsedLines[i] = false;
	}

	for (int i = 0; i < iNumOfLines; ++i)
	{
		//���������� ���� ������ failbit �� ������, ���� ��������� ������ � ����� - '\n'
		fin.clear();
		bIsFirstIteration = true;
		fin.seekg(0, std::ios::beg);

		iNumOfLine = 0;

		//����������� �� ����� ����� � ������� ���������� ������ (� ����� �� ����������� �������)
		while (!fin.eof()) {

			std::getline(fin, sCurLine);

			//���������, ����� �� �� ��� ��� ������. ���� ��, �� ���������� ��� ��������.
			if (pbUsedLines[iNumOfLine]) {
				++iNumOfLine;
				continue;
			}

			//���� ��� ������, �� ����������� �� ������� ����, ��������
			if (bIsFirstIteration) {
				sLeastLine = sCurLine;
				iNumOfLeastLine = iNumOfLine;
				bIsFirstIteration = false;
			}

			//���������� � ����������
			if (upperCase(sCurLine) < upperCase(sLeastLine)) {
				sLeastLine = sCurLine;
				iNumOfLeastLine = iNumOfLine;
			}

			++iNumOfLine;
		}
		
		//�������� ��� ����������� ������
		pbUsedLines[iNumOfLeastLine] = true;
		
		//������� ���������� � ����� ������ � ����
		remAllMatchedWords(sLeastLine, sToRemove);
		fout << sLeastLine + '\n';
	}
	
	//����������� �������
	fin.close();
	fout.close();
	delete[] pbUsedLines;
	system("pause");
	return 0;
}

//������� ��� ��������� ���������
void remAllMatchedWords(std::string &sLine, std::string sRemove) {
	std::string::size_type pos;
	do {
		pos = sLine.find(sRemove);
		if (pos != std::string::npos)
			sLine.erase(pos, sRemove.length());
	} while (pos != std::string::npos);
}

//��������� ������ � ������� �������
std::string upperCase(std::string sString) {
	std::string sTemp(sString);
	for (auto & symbol : sTemp)
		symbol = ::toupper(symbol);
	return sTemp;
}