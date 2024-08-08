#include "CLicenseChecker.h"


//-------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------
//�t�@�C�����I�[�v�����Ă��̌�̑�����\�ɂ���
CLicenseChecker::CLicenseChecker(string inFilePath)
{
	m_isLicense = false;


	try {
		m_err = fopen_s(&m_fp, inFilePath.c_str(), "r");
		if (m_err != 0) {
			throw m_err;
		}
	}
	catch (errno_t) {
		m_fp = nullptr;
		char errMessage[255] = "";
		strerror_s(errMessage, sizeof(errMessage) / sizeof(char), m_err);
		printf("%s:%d\n", errMessage, m_err);
	}


}


//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
//�t�@�C���I�[�v�����Ă���Ȃ����
CLicenseChecker::~CLicenseChecker()
{
	if (m_fp != nullptr) {
		fclose(m_fp);
	}

}




//-------------------------------------------------------------------------------
// checkLicense()
//-------------------------------------------------------------------------------
//���C�Z���X�̃`�F�b�N����
bool CLicenseChecker::checkLicense(int inLicenseId)
{
	
	if (m_fp == nullptr) {
		return false;
	}

	

	char scanLicenseId[LICENSE_ID_LENGTH_] = "";

	

	while (fgets(scanLicenseId, LICENSE_ID_LENGTH_, m_fp) != NULL)
	{

		int licenseId = atoi(scanLicenseId);
		
		if (licenseId == inLicenseId ) {
			return true;
		}

		

	}
	return false;
}


//-------------------------------------------------------------------------------
// isOpen()
//-------------------------------------------------------------------------------
//�t�@�C���I�[�v�����Ă��邩��Ԃ�
bool CLicenseChecker::isOpening()
{
	return m_fp != nullptr;
}


