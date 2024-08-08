#include "CAddressBookTrial.h"
#include"define.h"
//-------------------------------------------------------------------------------
// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//-------------------------------------------------------------------------------
//ZŠ˜^‚Ìì¬
CAddressBookTrial ::CAddressBookTrial(vector<CAddress>* inAddress)
{
	if (inAddress == nullptr) {
		printf("ZŠ˜^‚Ì€”õ‚É¸”s‚µ‚Ü‚µ‚½\n");
	}
	m_AddressArray = inAddress;
}


//-------------------------------------------------------------------------------
//addAdress
//-------------------------------------------------------------------------------
//ZŠ˜^‚ÉˆêŒ’Ç‰Á‚·‚é
void CAddressBookTrial::addAddress()
{
	if (m_AddressArray == nullptr) {
		printf("ZŠ˜^‚ª‚ ‚è‚Ü‚¹‚ñ\n");
		throw 0;
	}
	CAddressBook::addAddress();
}

//-------------------------------------------------------------------------------
//searchAddress
//-------------------------------------------------------------------------------
//ZŠ˜^‚©‚çŒŸõ‚·‚éi–¼‘O‚ÌŠ®‘Sˆê’vj
void CAddressBookTrial::searchAddress()
{
	if (m_AddressArray == nullptr) {
		printf("ZŠ˜^‚ª‚ ‚è‚Ü‚¹‚ñ\n");
		throw 0;
	}

	CInputChecker inputChecker;

	string name;
	inputChecker.inputName(name);

	vector<CAddress> *findingArray = m_AddressArray;

	vector<CAddress> empty;
	vector<CAddress>* foundArray = &empty;

	//ŒŸõ€–Ú‚ğ–¼‘O‚ÉŒÀ’è‚µ‚½Š®‘Sˆê’vŒŸõ
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
		printf("“ü—Í‚µ‚½–¼‘O‚Í‘¶İ‚µ‚Ü‚¹‚ñ\n");
	}
	
	
}

//-------------------------------------------------------------------------------
//editAddress
//-------------------------------------------------------------------------------
//ZŠ˜^‚ÌˆêŒ‚ğ•ÒWiID‚ªˆê’v‚µ‚½‚à‚Ìj
void CAddressBookTrial::editAddress()
{
	if (m_AddressArray == nullptr) {
		printf("ZŠ˜^‚ª‚ ‚è‚Ü‚¹‚ñ\n");
		throw 0;
	}
	CAddressBook::editAddress();
}


//-------------------------------------------------------------------------------
//removeAddress
//-------------------------------------------------------------------------------
//ZŠ˜^‚©‚çˆêŒíœ‚·‚é
void CAddressBookTrial::removeAddress()
{
	if (m_AddressArray == nullptr) {
		printf("ZŠ˜^‚ª‚ ‚è‚Ü‚¹‚ñ\n");
		throw 0;
	}
	CInputChecker inputChecker;
	
	int id;
	inputChecker.inputId("íœ‚·‚éID‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢", id);

	bool existId = false;

	for (vector<CAddress>::iterator AddressIt = m_AddressArray->begin();
		AddressIt != m_AddressArray->end();
		++AddressIt)
	{
		if (AddressIt->getId() == id) {
			AddressIt->display();

			char yorn = '\0';
			CInputChecker inputer;
			inputer.input_yorn(yorn, "ã‹L‚Ìƒf[ƒ^‚ğíœ‚µ‚Ä‚à‚¢‚¢‚Å‚·‚©H(y/n):");
			if (yorn == 'y') {
				//íœ‚³‚ê‚éƒCƒeƒŒ[ƒ^‚Ì‘O‚ÌƒCƒeƒŒ[ƒ^‚ğ•Ô‚·
				AddressIt = m_AddressArray->erase(AddressIt) - 1;

			}
			existId = true;

		}
	}
	if (!existId) {
		printf("“ü—Í‚µ‚½ID‚Í‘¶İ‚µ‚Ü‚¹‚ñ\n");
	}
	
}
