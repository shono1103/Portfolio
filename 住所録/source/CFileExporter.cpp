#include "CFileExporter.h"

#include "CFileImporter.h"


//-------------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------------
//以降の操作のため準備
CFileExporter::CFileExporter(
	string inFilePath)//書き込むファイルの相対パス
{
	
	m_filePath = inFilePath;
	m_fp = nullptr;
	
}

//-------------------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------------------
//ファイルを閉じる
CFileExporter::~CFileExporter()
{
	if (m_fp!=nullptr) {
		fclose(m_fp);
	}

}

//-------------------------------------------------------------------------------
// fileOpen()
//-------------------------------------------------------------------------------
//ファイルオープンをし、m_fpに格納する
bool CFileExporter::fileOpen()
{
	try {
		m_err = fopen_s(&m_fp, m_filePath.c_str(), "w");
		if (m_err != 0) {
			throw m_err;
		}
	}
	catch (errno_t m_err) {
		m_fp = nullptr;
		char errMessage[255] = "";
		strerror_s(errMessage, sizeof(errMessage) / sizeof(char), m_err);
		printf("%s:%d\n", errMessage, m_err);
	}
	return (m_fp != nullptr);
}



//-------------------------------------------------------------------------------
// writeFile()
//-------------------------------------------------------------------------------
//住所録の操作後の住所録をファイルに書き込む
void CFileExporter::writeFile(const vector<CAddress>& inAddressArray)
{
	if (m_fp == nullptr) {
		printf("ファイルに書き込めません\n");
		return;
	}

	vector<CAddress>::const_iterator AddressIt = inAddressArray.begin();

	while (AddressIt != inAddressArray.end())
	{
		fprintf(m_fp, "%d\t%s\t%s\t%s\t%s\n", 
			AddressIt->getId(),
			AddressIt->getName().c_str(),
			AddressIt->getResidence().c_str(),
			AddressIt->getPhoneNumber().c_str(), 
			AddressIt->getEmail().c_str());

		++AddressIt;
	}

	printf("%s\nに登録データを出力しました\n",m_filePath.c_str());
}




