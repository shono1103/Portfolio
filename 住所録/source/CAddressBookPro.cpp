#include "CAddressBookPro.h"


//-------------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------------
//住所録の作成
CAddressBookPro::CAddressBookPro(vector<CAddress>* inAddress)
{
	if (inAddress == nullptr) {
		printf("住所録がありません\n");
		throw 0;
	}
	m_AddressArray = inAddress;
}


//-------------------------------------------------------------------------------
//addAdress
//-------------------------------------------------------------------------------
//住所録に複数件追加する
void CAddressBookPro::addAddress()
{
	if (m_AddressArray == nullptr) {
		printf("住所録がありません\n");
		throw 0;
	}
	char yorn = '\0';
	
	do{
		CAddressBook::addAddress();
		
		CInputChecker inputChecker;
		inputChecker.input_yorn(yorn, "続けて追加しますか？(y/n)");

	} while (yorn == 'y');
	
}


//-------------------------------------------------------------------------------
//searchAddress
//-------------------------------------------------------------------------------
//住所録から検索する（各項目での絞り込み機能あり）
void CAddressBookPro::searchAddress()
{

	if (m_AddressArray == nullptr) {
		printf("住所録がありません\n");
		throw 0;
	}
	CInputChecker inputChecker;

	vector<CAddress>* findingArray = new vector<CAddress>;
	*findingArray = *m_AddressArray;
	vector<CAddress>* foundArray = new vector<CAddress>;

	char yorn = '\0';

	do{
		printf("1:氏名\n");
		printf("2:住所\n");
		printf("3:電話番号\n");
		printf("4:メールアドレス\n");
		printf("検索する項目を選んでください：");
		ESearchItem searchItem;
		inputChecker.inputSearchItem(searchItem);

		printf("1:完全一致\n");
		printf("2:部分一致\n");
		printf("検索条件を選んでください：");

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
			printf("入力したデータは存在しません\n");
		}

		findingArray->clear();
		delete findingArray;
		findingArray = foundArray;
		foundArray = new vector<CAddress>;

		inputChecker.input_yorn(yorn, "さらに検索しますか？(y/n)");
	} while (yorn=='y');
	delete findingArray;
	delete foundArray;
}




//-------------------------------------------------------------------------------
//editAddress
//-------------------------------------------------------------------------------
//住所録の複数件を編集する
void CAddressBookPro::editAddress()
{

	if (m_AddressArray == nullptr) {
		printf("住所録がありません\n");
		throw 0;
	}
	char yorn = '\0';
	CInputChecker inputChecker;

	
	do{
		CAddressBook::editAddress();

		inputChecker.input_yorn(yorn, "続けて編集しますか？(y/n)");

	}while (yorn == 'y');

}


//-------------------------------------------------------------------------------
//removeAddress
//-------------------------------------------------------------------------------
//住所録から複数件削除する（IDをもとに）
void CAddressBookPro::removeAddress()
{
	if (m_AddressArray == nullptr) {
		printf("住所録がありません\n");
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
				inputer.input_yorn(yorn, "上記のデータを削除してもいいですか？(y/n):");
				if (yorn == 'y') {
					AddressIt = m_AddressArray->erase(AddressIt) - 1;

				}
				existId = true;

			}
		}
		if (!existId) {
			printf("ID:%dは存在しません\n",*idIt);
		}

	}
}
