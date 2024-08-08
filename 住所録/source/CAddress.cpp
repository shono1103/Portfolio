#include "CAddress.h"

//-------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------
//�A�h���X��̍쐬�ƃA�h���X�̑����ƈ�ԑ傫��id��ێ�����
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
//���̃I�u�W�F�N�g�̃����o�ϐ��̊J��
void CAddress::display()
{
	printf("ID:%d\n", m_id);
	printf("�����F%s\n", m_name.c_str());
	printf("�Z���F % s\n", m_residence.c_str());
	printf("�d�b�ԍ��F%s\n", m_phoneNumber.c_str());
	printf("���[���A�h���X�F%s\n", m_email.c_str());
	printf("\n");
}


//-------------------------------------------------------------------------------
// editAddress()
//-------------------------------------------------------------------------------
//�I�u�W�F�N�g�̃����o�ϐ��̕ҏW
void CAddress::editAddress(
	string inName,//�ҏW��̖��O
	string inResidence, //�ҏW��̏Z��
	string inPhoneNumber, //�ҏW��̓d�b�ԍ�
	string inEmail)//�ҏW���email�A�h���X
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


