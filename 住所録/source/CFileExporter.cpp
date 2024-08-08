#include "CFileExporter.h"

#include "CFileImporter.h"


//-------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------
//�ȍ~�̑���̂��ߏ���
CFileExporter::CFileExporter(
	string inFilePath)//�������ރt�@�C���̑��΃p�X
{
	
	m_filePath = inFilePath;
	m_fp = nullptr;
	
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
//�t�@�C�������
CFileExporter::~CFileExporter()
{
	if (m_fp!=nullptr) {
		fclose(m_fp);
	}

}

//-------------------------------------------------------------------------------
// fileOpen()
//-------------------------------------------------------------------------------
//�t�@�C���I�[�v�������Am_fp�Ɋi�[����
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
//�Z���^�̑����̏Z���^���t�@�C���ɏ�������
void CFileExporter::writeFile(const vector<CAddress>& inAddressArray)
{
	if (m_fp == nullptr) {
		printf("�t�@�C���ɏ������߂܂���\n");
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

	printf("%s\n�ɓo�^�f�[�^���o�͂��܂���\n",m_filePath.c_str());
}




