#include "CFileImporter.h"


//-------------------------------------------------------------------------------
// CFileImporter
//-------------------------------------------------------------------------------
//�t�@�C�����J���Ă��̌�̏������\�ɂ���
CFileImporter::CFileImporter(
	string inFilePath)//�ǂݍ��ރt�@�C���̑��΃p�X
{
	m_AddressArray = nullptr;
	m_filePath = inFilePath;
	m_err = 0;
	m_fp = nullptr;
	
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
//�t�@�C���I�[�v�����Ă���Ȃ����
CFileImporter::~CFileImporter()
{
	if (m_fp!=nullptr) {
		fclose(m_fp);
	}

}


//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
//
bool CFileImporter::fileOpen()
{
	try {
		m_err = fopen_s(&m_fp, m_filePath.c_str(), "r");
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
// readFile
//-------------------------------------------------------------------------------
//�t�@�C������Z���^�̍쐬�̂��߂̃x�N�^���쐬����
void CFileImporter::readFile()
{
	if (m_fp == nullptr) {
		printf("�t�@�C����ǂݍ��߂܂���\n");
		return;
	}


	m_AddressArray = new vector<CAddress>;//CAddressBook�̃f�X�g���N�^��delete

	char scanId[ADDRESS_ID_LENGTH_] = "\0";
	char scanName[ADDRESS_NAME_LENGTH_] = "\0";
	char scanResidence[ADDRESS_RESIDENCE_LENGTH_] = "\0";
	char scanPhone[ADDRESS_PHONENUMBER_LENGTH_] = "\0";
	char scanEmail[ADDRESS_EMAIL_LENGTH_] = "\0";
	char line[ADDRESS_IMPORT_STR_LENGTH_] = "\0";
	

	while (fgets(line, ADDRESS_IMPORT_STR_LENGTH_, m_fp) != NULL)
	{
		//�s�ł̓ǂݎ��̕���
		int field = sscanf_s(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%s",
			&scanId,ADDRESS_ID_LENGTH_,
			scanName, ADDRESS_NAME_LENGTH_,
			scanResidence, ADDRESS_RESIDENCE_LENGTH_,
			scanPhone, ADDRESS_PHONENUMBER_LENGTH_,
			scanEmail, ADDRESS_EMAIL_LENGTH_);

		if (field != 5) {
			printf("�ُ�ȍs�����m���܂���\n");
			continue;

		}
		
		int id = atoi(scanId);
		string name(scanName);
		string residence(scanResidence);
		string phone(scanPhone);
		string email(scanEmail);

		bool isSame = false;//����ID�̗L��

		for (vector<CAddress>::iterator AddressIt = m_AddressArray->begin();
			AddressIt != m_AddressArray->end();
			++AddressIt)
		{
			if (AddressIt->getId() == id) {
				isSame = true;
				break;
			}
		}

		if (isSame) {
			printf("ID�����Ԃ�܂����B\n");
			continue;
		}



		if (id > MAX_ID_) {
			printf("ID��%d�܂łł�\n", MAX_ID_);
			continue;
		}
	


		m_AddressArray->push_back(CAddress(id, name, residence, phone, email));
		if (m_AddressArray->size() >= ADDRESS_BOOK_MEMBER_MAX_) {
			printf("�ő�v�f���ɒB���܂���\n");
			break;
		}		
	}		
}
	

	


//-------------------------------------------------------------------------------
// setAddressVector()
//-------------------------------------------------------------------------------
//���̃N���X�̓ǂݍ���Address�̃x�N�^��n��
vector<CAddress>& CFileImporter::setAddressVector()
{
	return *m_AddressArray;
}


