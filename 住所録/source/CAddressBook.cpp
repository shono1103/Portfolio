#include "CAddressBook.h"




//-------------------------------------------------------------------------------
//デストラクタ
//-------------------------------------------------------------------------------
//m_AddressArrayの動的メモリの解放
CAddressBook::~CAddressBook()
{
	m_AddressArray->clear();
	delete m_AddressArray;
}


//-------------------------------------------------------------------------------
// displayAddress()
//-------------------------------------------------------------------------------
//住所録の表示
void CAddressBook::displayAddress()
{
	if (m_AddressArray == nullptr) {
		printf("住所録が正常じゃありません");
		return;
	}
	if (m_AddressArray->size() == 0) {
		printf("1つもありません\n");
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
//住所録そのものを渡す（ファイル書き込みで使う）
const vector<CAddress>& CAddressBook::getAddressVector() const
{
	if (m_AddressArray == nullptr) {
		printf("住所録が正常じゃありません");
	}
	return *m_AddressArray;
}


//-------------------------------------------------------------------------------
//addAdress
//-------------------------------------------------------------------------------
//住所録に追加
void CAddressBook::addAddress()
{
	if (m_AddressArray == nullptr) {
		printf("住所録が正常じゃありません");
		return;
	}

	if (m_AddressArray->size() >= ADDRESS_BOOK_MEMBER_MAX_) {
		printf_s("これ以上追加できません\n");
		return;
	}
	if (CAddress::getMaxId() >= MAX_ID_) {
		printf("IDは%dまでです\n", MAX_ID_);
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
//住所録を編集する
void CAddressBook::editAddress()
{
	if (m_AddressArray == nullptr) {
		printf("住所録が正常じゃありません");
		return;
	}

	CInputChecker inputChecker;

	int id;
	inputChecker.inputId("編集するIDを入力してください", id);

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
		printf("入力したIDは存在しません\n");
	}
}

//-------------------------------------------------------------------------------
// searchExact
//-------------------------------------------------------------------------------
//住所録から検索をする（完全一致）
bool CAddressBook::searchExact(
	string inSearch, //検索する文字列
	ESearchItem inSearchItem,//検索項目
	const vector<CAddress>& inSearchingArray,//検索対象
	vector<CAddress>& outSearchedArray)//検索されたアドレス
{

	if (m_AddressArray == nullptr) {
		printf("住所録が正常じゃありません");
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
//住所録から検索をする（部分一致）
bool CAddressBook::searchPartial(
	string inSearch, //検索する文字列
	ESearchItem inSearchItem,//検索項目
	const vector<CAddress>& inSearchingArray,//検索対象
	vector<CAddress>& outSearchedArray) //検索されたアドレス
	
{

	if (m_AddressArray == nullptr) {
		printf("住所録が正常じゃありません");
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

