#pragma once

#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;


//-------------------------------------------------------------------------------
//CAddress 
//-------------------------------------------------------------------------------
//��l���̏Z���^�̂��߂̃N���X
class CAddress
{
public:
//-------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------
//�A�h���X��̍쐬�ƃA�h���X�̑����ƈ�ԑ傫��id��ێ�����
	CAddress(int inId,
		string inName,
		string inResidence,
		string inPhoneNumber, 
		string inEmail);
	
//-------------------------------------------------------------------------------
// display()
//-------------------------------------------------------------------------------
//�����o�ϐ��̊J��
	void display();

//-------------------------------------------------------------------------------
// editAddress()
//-------------------------------------------------------------------------------
//�����o�ϐ��̕ҏW
	void editAddress(
		string inName,//�ҏW��̖��O
		string inResidence, //�ҏW��̏Z��
		string inPhoneNumber, //�ҏW��̓d�b�ԍ�
		string inEmail);//�ҏW���email�A�h���X
	


	int getId()const;
	string getName()const;
	string getResidence()const;
	string getPhoneNumber()const;
	string getEmail()const;
	static int getMaxId();


private:
	int m_id;
	string m_name;
	string m_residence;
	string m_phoneNumber;
	string m_email;
	static int ms_maxId;
};

