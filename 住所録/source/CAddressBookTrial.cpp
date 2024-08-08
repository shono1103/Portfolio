#include "CAddressBookTrial.h"
#include"define.h"
//-------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------
//�Z���^�̍쐬
CAddressBookTrial ::CAddressBookTrial(vector<CAddress>* inAddress)
{
	if (inAddress == nullptr) {
		printf("�Z���^�̏����Ɏ��s���܂���\n");
	}
	m_AddressArray = inAddress;
}


//-------------------------------------------------------------------------------
//addAdress
//-------------------------------------------------------------------------------
//�Z���^�Ɉꌏ�ǉ�����
void CAddressBookTrial::addAddress()
{
	if (m_AddressArray == nullptr) {
		printf("�Z���^������܂���\n");
		throw 0;
	}
	CAddressBook::addAddress();
}

//-------------------------------------------------------------------------------
//searchAddress
//-------------------------------------------------------------------------------
//�Z���^���猟������i���O�̊��S��v�j
void CAddressBookTrial::searchAddress()
{
	if (m_AddressArray == nullptr) {
		printf("�Z���^������܂���\n");
		throw 0;
	}

	CInputChecker inputChecker;

	string name;
	inputChecker.inputName(name);

	vector<CAddress> *findingArray = m_AddressArray;

	vector<CAddress> empty;
	vector<CAddress>* foundArray = &empty;

	//�������ڂ𖼑O�Ɍ��肵�����S��v����
	bool exist = CAddressBook::searchExact(
		name,
		ESearchItem::Name,
		*foundArray,
		*findingArray);
	
	if (exist) {
		for (vector<CAddress>::iterator AddressIt = foundArray->begin();
			AddressIt != foundArray->end();
			++AddressIt) {
			AddressIt->display();	
		}
	}
	else {
		printf("���͂������O�͑��݂��܂���\n");
	}
	
	
}

//-------------------------------------------------------------------------------
//editAddress
//-------------------------------------------------------------------------------
//�Z���^�̈ꌏ��ҏW�iID����v�������́j
void CAddressBookTrial::editAddress()
{
	if (m_AddressArray == nullptr) {
		printf("�Z���^������܂���\n");
		throw 0;
	}
	CAddressBook::editAddress();
}


//-------------------------------------------------------------------------------
//removeAddress
//-------------------------------------------------------------------------------
//�Z���^����ꌏ�폜����
void CAddressBookTrial::removeAddress()
{
	if (m_AddressArray == nullptr) {
		printf("�Z���^������܂���\n");
		throw 0;
	}
	CInputChecker inputChecker;
	
	int id;
	inputChecker.inputId("�폜����ID����͂��Ă�������", id);

	bool existId = false;

	for (vector<CAddress>::iterator AddressIt = m_AddressArray->begin();
		AddressIt != m_AddressArray->end();
		++AddressIt)
	{
		if (AddressIt->getId() == id) {
			AddressIt->display();

			char yorn = '\0';
			CInputChecker inputer;
			inputer.input_yorn(yorn, "��L�̃f�[�^���폜���Ă������ł����H(y/n):");
			if (yorn == 'y') {
				//�폜�����C�e���[�^�̑O�̃C�e���[�^��Ԃ�
				AddressIt = m_AddressArray->erase(AddressIt) - 1;

			}
			existId = true;

		}
	}
	if (!existId) {
		printf("���͂���ID�͑��݂��܂���\n");
	}
	
}
