#include "CLicenseChecker.h"


//-------------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------------
//ファイルをオープンしてその後の操作を可能にする
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
// デストラクタ
//-------------------------------------------------------------------------------
//ファイルオープンしているなら閉じる
CLicenseChecker::~CLicenseChecker()
{
	if (m_fp != nullptr) {
		fclose(m_fp);
	}

}




//-------------------------------------------------------------------------------
// checkLicense()
//-------------------------------------------------------------------------------
//ライセンスのチェックする
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
//ファイルオープンしているかを返す
bool CLicenseChecker::isOpening()
{
	return m_fp != nullptr;
}


