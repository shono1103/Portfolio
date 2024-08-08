#include "CAddressBook.h"




//-------------------------------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------------------------------
//m_AddressArray�̓��I�������̉��
CAddressBook::~CAddressBook()
{
	m_AddressArray->clear();
	delete m_AddressArray;
}


//-------------------------------------------------------------------------------
// displayAddress()
//-------------------------------------------------------------------------------
//�Z���^�̕\��
void CAddressBook::displayAddress()
{
	if (m_AddressArray == nullptr) {
		printf("�Z���^�����킶�Ⴀ��܂���");
		return;
	}
	if (m_AddressArray->size() == 0) {
		printf("1������܂���\n");
	}
	else {
		
		for (vector<CAddress>::iterator AddressIt = m_AddressArray->begin();
			AddressIt != m_AddressArray->end();
			++AddressIt){
			AddressIt->display();
		}
	}
}

//-------------------------------------------------------------------------------
// getAddressVector()
//-------------------------------------------------------------------------------
//�Z���^���̂��̂�n���i�t�@�C���������݂Ŏg���j
const vector<CAddress>& CAddressBook::getAddressVector() const
{
	if (m_AddressArray == nullptr) {
		printf("�Z���^�����킶�Ⴀ��܂���");
	}
	return *m_AddressArray;
}


//-------------------------------------------------------------------------------
//addAdress
//-------------------------------------------------------------------------------
//�Z���^�ɒǉ�
void CAddressBook::addAddress()
{
	if (m_AddressArray == nullptr) {
		printf("�Z���^�����킶�Ⴀ��܂���");
		return;
	}

	if (m_AddressArray->size() >= ADDRESS_BOOK_MEMBER_MAX_) {
		printf_s("����ȏ�ǉ��ł��܂���\n");
		return;
	}
	if (CAddress::getMaxId() >= MAX_ID_) {
		printf("ID��%d�܂łł�\n", MAX_ID_);
		return;
	}
	CInputChecker inputChecker;

	string name;
	inputChecker.inputName(name);
	string residence;
	inputChecker.inputResidence(residence);
	string phoneNumber;
	inputChecker.inputPhoneNumber(phoneNumber);
	string email;
	inputChecker.inputEmail(email);
	
	CAddress Address(CAddress::getMaxId() + 1, name, residence, phoneNumber, email);

	m_AddressArray->push_back(Address);

	
}


//-------------------------------------------------------------------------------
//editAddress
//-------------------------------------------------------------------------------
//�Z���^��ҏW����
void CAddressBook::editAddress()
{
	if (m_AddressArray == nullptr) {
		printf("�Z���^�����킶�Ⴀ��܂���");
		return;
	}

	CInputChecker inputChecker;

	int id;
	inputChecker.inputId("�ҏW����ID����͂��Ă�������", id);

	bool existId = false;

	for (vector<CAddress>::iterator AddressIt = m_AddressArray->begin();
		AddressIt != m_AddressArray->end();
		++AddressIt)
	{
		if (AddressIt->getId() == id) {

			CInputChecker inputer;
			string name;
			inputer.inputName(name);
			string residence;
			inputer.inputResidence(residence);
			string phoneNumber;
			inputer.inputPhoneNumber(phoneNumber);
			string email;
			inputer.inputEmail(email);

			AddressIt->editAddress(name, residence, phoneNumber, email);
			existId = true;

			break;

		}
	}
	if (!existId) {
		printf("���͂���ID�͑��݂��܂���\n");
	}
}

//-------------------------------------------------------------------------------
// searchExact
//-------------------------------------------------------------------------------
//�Z���^���猟��������i���S��v�j
bool CAddressBook::searchExact(
	string inSearch, //�������镶����
	ESearchItem inSearchItem,//��������
	const vector<CAddress>& inSearchingArray,//�����Ώ�
	vector<CAddress>& outSearchedArray)//�������ꂽ�A�h���X
{

	if (m_AddressArray == nullptr) {
		printf("�Z���^�����킶�Ⴀ��܂���");
		return false;
	}

	bool exist = false;

	for (vector<CAddress>::const_iterator AddressIt = inSearchingArray.cbegin();
		AddressIt != inSearchingArray.cend();
		++AddressIt)
	{

		switch (inSearchItem)
		{
		case ESearchItem::Name:

			if (AddressIt->getName() == inSearch) {

				outSearchedArray.push_back(*AddressIt);
				
				exist = true;

			}
			break;
		case ESearchItem::Residence:
			if (AddressIt->getResidence() == inSearch) {

				outSearchedArray.push_back(*AddressIt);
				exist = true;

			}
			break;
		case ESearchItem::PhoneNumber:
			if (AddressIt->getPhoneNumber() == inSearch) {

				outSearchedArray.push_back(*AddressIt);
				exist = true;

			}
			break;
		case ESearchItem::Email:
			if (AddressIt->getEmail() == inSearch) {

				outSearchedArray.push_back(*AddressIt);
				exist = true;

			}
			break;
		default:
			assert(0);
			break;
		}

	}

	return exist;
}



//-------------------------------------------------------------------------------
// searchPartial()
//-------------------------------------------------------------------------------
//�Z���^���猟��������i������v�j
bool CAddressBook::searchPartial(
	string inSearch, //�������镶����
	ESearchItem inSearchItem,//��������
	const vector<CAddress>& inSearchingArray,//�����Ώ�
	vector<CAddress>& outSearchedArray) //�������ꂽ�A�h���X
	
{

	if (m_AddressArray == nullptr) {
		printf("�Z���^�����킶�Ⴀ��܂���");
		return false;
	}

	bool exist = false;

	for (vector<CAddress>::const_iterator AddressIt = inSearchingArray.cbegin();
		AddressIt != inSearchingArray.cend();
		++AddressIt)
	{

		switch (inSearchItem)
		{
		case ESearchItem::Name:

			if (AddressIt->getName().find(inSearch) != string::npos) {
				outSearchedArray.push_back(*AddressIt);
				exist = true;
			}
			
			break;
		case ESearchItem::Residence:
			if (AddressIt->getResidence().find(inSearch) != string::npos) {
				outSearchedArray.push_back(*AddressIt);
				exist = true;
			}
			break;
		case ESearchItem::PhoneNumber:
			if (AddressIt->getPhoneNumber().find(inSearch) != string::npos) {
				outSearchedArray.push_back(*AddressIt);
				exist = true;
			}
			break;
		case ESearchItem::Email:
			if (AddressIt->getEmail().find(inSearch) != string::npos) {
				outSearchedArray.push_back(*AddressIt);
				exist = true;
			}
			break;
		default:
			assert(0);
			break;
		}

	}

	return exist;
}

