#include "CAddress.h"

//-------------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------------
//アドレス一つの作成とアドレスの総数と一番大きいidを保持する
CAddress::CAddress(
	int inId, 
	string inName,
	string inResidence,
	string inPhoneNumber, 
	string inEmail)
{
	m_id = inId;
	m_name = inName;
	m_residence = inResidence;
	m_phoneNumber = inPhoneNumber;
	m_email = inEmail;
	
	if (ms_maxId <= m_id) {
		ms_maxId = m_id;
	}
}


//-------------------------------------------------------------------------------
// display()
//-------------------------------------------------------------------------------
//このオブジェクトのメンバ変数の開示
void CAddress::display()
{
	printf("ID:%d\n", m_id);
	printf("氏名：%s\n", m_name.c_str());
	printf("住所： % s\n", m_residence.c_str());
	printf("電話番号：%s\n", m_phoneNumber.c_str());
	printf("メールアドレス：%s\n", m_email.c_str());
	printf("\n");
}


//-------------------------------------------------------------------------------
// editAddress()
//-------------------------------------------------------------------------------
//オブジェクトのメンバ変数の編集
void CAddress::editAddress(
	string inName,//編集後の名前
	string inResidence, //編集後の住所
	string inPhoneNumber, //編集後の電話番号
	string inEmail)//編集後のemailアドレス
{
	m_name = inName;
	m_residence = inResidence;
	m_phoneNumber = inPhoneNumber;
	m_email = inEmail;
}

int CAddress::getId()const
{
	return m_id;
}

string CAddress::getName()const
{
	return m_name;
}

string CAddress::getResidence()const
{
	return m_residence;
}

string CAddress::getPhoneNumber()const
{
	return m_phoneNumber;
}

string CAddress::getEmail()const
{
	return m_email;
}



int CAddress::getMaxId()
{
	return ms_maxId;
}


