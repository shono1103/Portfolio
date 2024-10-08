#include "CAddressBookTrial.h"
#include"define.h"
//-------------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------------
//住所録の作成
CAddressBookTrial ::CAddressBookTrial(vector<CAddress>* inAddress)
{
	if (inAddress == nullptr) {
		printf("住所録の準備に失敗しました\n");
	}
	m_AddressArray = inAddress;
}


//-------------------------------------------------------------------------------
//addAdress
//-------------------------------------------------------------------------------
//住所録に一件追加する
void CAddressBookTrial::addAddress()
{
	if (m_AddressArray == nullptr) {
		printf("住所録がありません\n");
		throw 0;
	}
	CAddressBook::addAddress();
}

//-------------------------------------------------------------------------------
//searchAddress
//-------------------------------------------------------------------------------
//住所録から検索する（名前の完全一致）
void CAddressBookTrial::searchAddress()
{
	if (m_AddressArray == nullptr) {
		printf("住所録がありません\n");
		throw 0;
	}

	CInputChecker inputChecker;

	string name;
	inputChecker.inputName(name);

	vector<CAddress> *findingArray = m_AddressArray;

	vector<CAddress> empty;
	vector<CAddress>* foundArray = &empty;

	//検索項目を名前に限定した完全一致検索
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
		printf("入力した名前は存在しません\n");
	}
	
	
}

//-------------------------------------------------------------------------------
//editAddress
//-------------------------------------------------------------------------------
//住所録の一件を編集（IDが一致したもの）
void CAddressBookTrial::editAddress()
{
	if (m_AddressArray == nullptr) {
		printf("住所録がありません\n");
		throw 0;
	}
	CAddressBook::editAddress();
}


//-------------------------------------------------------------------------------
//removeAddress
//-------------------------------------------------------------------------------
//住所録から一件削除する
void CAddressBookTrial::removeAddress()
{
	if (m_AddressArray == nullptr) {
		printf("住所録がありません\n");
		throw 0;
	}
	CInputChecker inputChecker;
	
	int id;
	inputChecker.inputId("削除するIDを入力してください", id);

	bool existId = false;

	for (vector<CAddress>::iterator AddressIt = m_AddressArray->begin();
		AddressIt != m_AddressArray->end();
		++AddressIt)
	{
		if (AddressIt->getId() == id) {
			AddressIt->display();

			char yorn = '\0';
			CInputChecker inputer;
			inputer.input_yorn(yorn, "上記のデータを削除してもいいですか？(y/n):");
			if (yorn == 'y') {
				//削除されるイテレータの前のイテレータを返す
				AddressIt = m_AddressArray->erase(AddressIt) - 1;

			}
			existId = true;

		}
	}
	if (!existId) {
		printf("入力したIDは存在しません\n");
	}
	
}
