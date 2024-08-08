#include "CAddressBookOperator.h"


//-------------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------------
//Licenseチェックをする（ファイルにもしくはファイル内にアカウントがないときライセンス無しにする）
CAddressBookOperator::CAddressBookOperator(
	string inAddressBookFileName)//操作する住所録のファイル名
{

	m_addressBookFileName = inAddressBookFileName;
	m_isProLicense = false;
	

	m_pAddressBook = NULL;
	m_pAddressBookDirector = NULL;
}

//-------------------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------------------
//m_pAddressBookの解放
CAddressBookOperator::~CAddressBookOperator()
{
	delete m_pAddressBook;
	//m_pAddressBookDirectorはm_pAddressBookと
	//同じものを指しているため、delete不要
}


//-------------------------------------------------------------------------------
// initialize()
//-------------------------------------------------------------------------------
//最初に行う処理
bool CAddressBookOperator::initialize()
{
	allowProLicense();
	return importFile();
}



//-------------------------------------------------------------------------------
// allowProLicense()
//-------------------------------------------------------------------------------
//Licenseチェックをする
void CAddressBookOperator::allowProLicense()
{
	CLicenseChecker licenseChecker("License.txt");
	int AccountId = 0;


	if (licenseChecker.isOpening()) {

		printf("アカウントIDを入力してください：");
		scanf_s("%d", &AccountId);
		
		m_isProLicense = licenseChecker.checkLicense(AccountId);
		
		if (m_isProLicense) {
			printf("proライセンスを確認しました\n");
		}
	}	
}

//-------------------------------------------------------------------------------
// importFile()
//-------------------------------------------------------------------------------
//住所録ファイルを読み込んで住所録操作の準備をする
bool CAddressBookOperator::importFile()
{
	//string filePath = "./住所録ファイル./" + m_addressBookFileName;
	string filePath = "./" + m_addressBookFileName;

	CFileImporter fileImporter(filePath);
	bool isFileOpened = fileImporter.fileOpen();

	if (!isFileOpened) {
		return false;
		
	}

	fileImporter.readFile();
	
	printf("%d件の住所録データを読み込みました。\n", 
		(int)fileImporter.setAddressVector().size());
	vector<CAddress>* AddressBookArray = &fileImporter.setAddressVector();
	//AddressBookArray = nullptr;
	if (m_isProLicense) {
		printf("[住所録アプリ　pro版]\n");
		m_pAddressBook = new CAddressBookPro(AddressBookArray);//デストラクタでdelete
		m_pAddressBookDirector = m_pAddressBook;
	}
	else {
		printf("[住所録アプリ　Trial版]\n");
		m_pAddressBook = new CAddressBookTrial(AddressBookArray);//デストラクタでdelete
		m_pAddressBookDirector = m_pAddressBook;
	}

	if (m_pAddressBook == nullptr) {
		return false;
	}

	return true;
}


//-------------------------------------------------------------------------------
// exportFile()
//-------------------------------------------------------------------------------
//操作後の住所録をファイルに上書きする
void CAddressBookOperator::exportFile()
{
	//string filePath = "./住所録ファイル./" + m_addressBookFileName;
	string filePath = "./" + m_addressBookFileName;

	CFileExporter fileExporter(filePath);
	bool isOpenExport = fileExporter.fileOpen();
	if (isOpenExport) {


		const vector<CAddress>* AddressArray = &m_pAddressBook->getAddressVector();

		if (AddressArray == nullptr) {
			throw 0;
		}

		fileExporter.writeFile(*AddressArray);
		
	}
	else {
		printf("ファイルを正常にオープンできませんでした。\n");
	}
	
}


//-------------------------------------------------------------------------------
// selectAddressBookMove()
//-------------------------------------------------------------------------------
//住所録への操作
void CAddressBookOperator::operateAddressBook()
{

	ESelectMove selectMove = ESelectMove::Default;
	do {
		

		CInputChecker inputChecker;

		printf("1)　追加\n");
		printf("2)　表示\n");
		printf("3)　検索\n");
		printf("4)　編集\n");
		printf("5)　削除\n");
		printf("6)　終了\n");
		printf("　　選択してください：");


		inputChecker.inputSelectMove(selectMove);

		switch (selectMove)
		{
		case ESelectMove::Add:
		{
			m_pAddressBookDirector->addAddress();
		}
		break;
		case ESelectMove::Display:
		{
			m_pAddressBook->displayAddress();
		}
		break;
		case ESelectMove::Search:
		{
			m_pAddressBookDirector->searchAddress();
		}
		break;
		case ESelectMove::Edit:
		{
			
			m_pAddressBookDirector->editAddress();
			
		}
		break;
		case ESelectMove::Remove:
		{
			
			m_pAddressBookDirector->removeAddress();
		}
		break;
		case ESelectMove::End:
			break;
		default:
			break;
		}


	} while (selectMove!=ESelectMove::End);

	

}


