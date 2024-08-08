#include "CAddressBook.h"




//-------------------------------------------------------------------------------
//ƒfƒXƒgƒ‰ƒNƒ^
//-------------------------------------------------------------------------------
//m_AddressArray‚Ì“®“Iƒƒ‚ƒŠ‚Ì‰ğ•ú
CAddressBook::~CAddressBook()
{
	m_AddressArray->clear();
	delete m_AddressArray;
}


//-------------------------------------------------------------------------------
// displayAddress()
//-------------------------------------------------------------------------------
//ZŠ˜^‚Ì•\¦
void CAddressBook::displayAddress()
{
	if (m_AddressArray == nullptr) {
		printf("ZŠ˜^‚ª³í‚¶‚á‚ ‚è‚Ü‚¹‚ñ");
		return;
	}
	if (m_AddressArray->size() == 0) {
		printf("1‚Â‚à‚ ‚è‚Ü‚¹‚ñ\n");
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
//ZŠ˜^‚»‚Ì‚à‚Ì‚ğ“n‚·iƒtƒ@ƒCƒ‹‘‚«‚İ‚Åg‚¤j
const vector<CAddress>& CAddressBook::getAddressVector() const
{
	if (m_AddressArray == nullptr) {
		printf("ZŠ˜^‚ª³í‚¶‚á‚ ‚è‚Ü‚¹‚ñ");
	}
	return *m_AddressArray;
}


//-------------------------------------------------------------------------------
//addAdress
//-------------------------------------------------------------------------------
//ZŠ˜^‚É’Ç‰Á
void CAddressBook::addAddress()
{
	if (m_AddressArray == nullptr) {
		printf("ZŠ˜^‚ª³í‚¶‚á‚ ‚è‚Ü‚¹‚ñ");
		return;
	}

	if (m_AddressArray->size() >= ADDRESS_BOOK_MEMBER_MAX_) {
		printf_s("‚±‚êˆÈã’Ç‰Á‚Å‚«‚Ü‚¹‚ñ\n");
		return;
	}
	if (CAddress::getMaxId() >= MAX_ID_) {
		printf("ID‚Í%d‚Ü‚Å‚Å‚·\n", MAX_ID_);
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
//ZŠ˜^‚ğ•ÒW‚·‚é
void CAddressBook::editAddress()
{
	if (m_AddressArray == nullptr) {
		printf("ZŠ˜^‚ª³í‚¶‚á‚ ‚è‚Ü‚¹‚ñ");
		return;
	}

	CInputChecker inputChecker;

	int id;
	inputChecker.inputId("•ÒW‚·‚éID‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢", id);

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
		printf("“ü—Í‚µ‚½ID‚Í‘¶İ‚µ‚Ü‚¹‚ñ\n");
	}
}

//-------------------------------------------------------------------------------
// searchExact
//-------------------------------------------------------------------------------
//ZŠ˜^‚©‚çŒŸõ‚ğ‚·‚éiŠ®‘Sˆê’vj
bool CAddressBook::searchExact(
	string inSearch, //ŒŸõ‚·‚é•¶š—ñ
	ESearchItem inSearchItem,//ŒŸõ€–Ú
	const vector<CAddress>& inSearchingArray,//ŒŸõ‘ÎÛ
	vector<CAddress>& outSearchedArray)//ŒŸõ‚³‚ê‚½ƒAƒhƒŒƒX
{

	if (m_AddressArray == nullptr) {
		printf("ZŠ˜^‚ª³í‚¶‚á‚ ‚è‚Ü‚¹‚ñ");
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
//ZŠ˜^‚©‚çŒŸõ‚ğ‚·‚éi•”•ªˆê’vj
bool CAddressBook::searchPartial(
	string inSearch, //ŒŸõ‚·‚é•¶š—ñ
	ESearchItem inSearchItem,//ŒŸõ€–Ú
	const vector<CAddress>& inSearchingArray,//ŒŸõ‘ÎÛ
	vector<CAddress>& outSearchedArray) //ŒŸõ‚³‚ê‚½ƒAƒhƒŒƒX
	
{

	if (m_AddressArray == nullptr) {
		printf("ZŠ˜^‚ª³í‚¶‚á‚ ‚è‚Ü‚¹‚ñ");
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

