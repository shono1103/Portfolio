#include "CAddressBookPro.h"


//-------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------
//�Z���^�̍쐬
CAddressBookPro::CAddressBookPro(vector<CAddress>* inAddress)
{
	if (inAddress == nullptr) {
		printf("�Z���^������܂���\n");
		throw 0;
	}
	m_AddressArray = inAddress;
}


//-------------------------------------------------------------------------------
//addAdress
//-------------------------------------------------------------------------------
//�Z���^�ɕ������ǉ�����
void CAddressBookPro::addAddress()
{
	if (m_AddressArray == nullptr) {
		printf("�Z���^������܂���\n");
		throw 0;
	}
	char yorn = '\0';
	
	do{
		CAddressBook::addAddress();
		
		CInputChecker inputChecker;
		inputChecker.input_yorn(yorn, "�����Ēǉ����܂����H(y/n)");

	} while (yorn == 'y');
	
}


//-------------------------------------------------------------------------------
//searchAddress
//-------------------------------------------------------------------------------
//�Z���^���猟������i�e���ڂł̍i�荞�݋@�\����j
void CAddressBookPro::searchAddress()
{

	if (m_AddressArray == nullptr) {
		printf("�Z���^������܂���\n");
		throw 0;
	}
	CInputChecker inputChecker;

	vector<CAddress>* findingArray = new vector<CAddress>;
	*findingArray = *m_AddressArray;
	vector<CAddress>* foundArray = new vector<CAddress>;

	char yorn = '\0';

	do{
		printf("1:����\n");
		printf("2:�Z��\n");
		printf("3:�d�b�ԍ�\n");
		printf("4:���[���A�h���X\n");
		printf("�������鍀�ڂ�I��ł��������F");
		ESearchItem searchItem;
		inputChecker.inputSearchItem(searchItem);

		printf("1:���S��v\n");
		printf("2:������v\n");
		printf("����������I��ł��������F");

		ESearchMode searchMode;
		inputChecker.inputSearchMode(searchMode);

		string search = "";

		switch (searchItem)
		{
		case ESearchItem::Name:
			inputChecker.inputName(search);
			break;
		case ESearchItem::Residence:
			inputChecker.inputResidence(search);
			break;
		case ESearchItem::PhoneNumber:
			inputChecker.inputPhoneNumber(search);
			break;
		case ESearchItem::Email:
			inputChecker.inputEmail(search);
			break;
		default:
			assert(0);
			break;
		}

		bool exist = false;

		

		switch (searchMode)
		{
		case ESearchMode::Partial:
			exist = CAddressBook::searchPartial(
				search, 
				searchItem,
				*findingArray,
				*foundArray);
			break;
		case ESearchMode::Exact:
			exist = CAddressBook::searchExact(
				search,
				searchItem,
				*findingArray,
				*foundArray);
			break;
		default:
			break;
		}

		if (exist) {
			for (vector<CAddress>::iterator AddressIt = foundArray->begin();
				AddressIt != foundArray->end();
				++AddressIt) {
				AddressIt->display();
			}
		}
		else {
			printf("���͂����f�[�^�͑��݂��܂���\n");
		}

		findingArray->clear();
		delete findingArray;
		findingArray = foundArray;
		foundArray = new vector<CAddress>;

		inputChecker.input_yorn(yorn, "����Ɍ������܂����H(y/n)");
	} while (yorn=='y');
	delete findingArray;
	delete foundArray;
}




//-------------------------------------------------------------------------------
//editAddress
//-------------------------------------------------------------------------------
//�Z���^�̕�������ҏW����
void CAddressBookPro::editAddress()
{

	if (m_AddressArray == nullptr) {
		printf("�Z���^������܂���\n");
		throw 0;
	}
	char yorn = '\0';
	CInputChecker inputChecker;

	
	do{
		CAddressBook::editAddress();

		inputChecker.input_yorn(yorn, "�����ĕҏW���܂����H(y/n)");

	}while (yorn == 'y');

}


//-------------------------------------------------------------------------------
//removeAddress
//-------------------------------------------------------------------------------
//�Z���^���畡�����폜����iID�����ƂɁj
void CAddressBookPro::removeAddress()
{
	if (m_AddressArray == nullptr) {
		printf("�Z���^������܂���\n");
		throw 0;
	}

	CInputChecker inputChecker;

	vector<int> vId;
	
	inputChecker.inputMultiId(vId);
	

	bool existId = false;




	for (vector<int>::iterator idIt = vId.begin();
		idIt != vId.end();
		++idIt) {

		for (vector<CAddress>::iterator AddressIt = m_AddressArray->begin();
			AddressIt != m_AddressArray->end();
			++AddressIt) {

			if (AddressIt->getId() == *idIt) {
				AddressIt->display();

				char yorn = '\0';
				CInputChecker inputer;
				inputer.input_yorn(yorn, "��L�̃f�[�^���폜���Ă������ł����H(y/n):");
				if (yorn == 'y') {
					AddressIt = m_AddressArray->erase(AddressIt) - 1;

				}
				existId = true;

			}
		}
		if (!existId) {
			printf("ID:%d�͑��݂��܂���\n",*idIt);
		}

	}
}
