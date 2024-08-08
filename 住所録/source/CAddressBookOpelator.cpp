#include "CAddressBookOperator.h"


//-------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------
//License�`�F�b�N������i�t�@�C���ɂ������̓t�@�C�����ɃA�J�E���g���Ȃ��Ƃ����C�Z���X�����ɂ���j
CAddressBookOperator::CAddressBookOperator(
	string inAddressBookFileName)//���삷��Z���^�̃t�@�C����
{

	m_addressBookFileName = inAddressBookFileName;
	m_isProLicense = false;
	

	m_pAddressBook = NULL;
	m_pAddressBookDirector = NULL;
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
//m_pAddressBook�̉��
CAddressBookOperator::~CAddressBookOperator()
{
	delete m_pAddressBook;
	//m_pAddressBookDirector��m_pAddressBook��
	//�������̂��w���Ă��邽�߁Adelete�s�v
}


//-------------------------------------------------------------------------------
// initialize()
//-------------------------------------------------------------------------------
//�ŏ��ɍs������
bool CAddressBookOperator::initialize()
{
	allowProLicense();
	return importFile();
}



//-------------------------------------------------------------------------------
// allowProLicense()
//-------------------------------------------------------------------------------
//License�`�F�b�N������
void CAddressBookOperator::allowProLicense()
{
	CLicenseChecker licenseChecker("License.txt");
	int AccountId = 0;


	if (licenseChecker.isOpening()) {

		printf("�A�J�E���gID����͂��Ă��������F");
		scanf_s("%d", &AccountId);
		
		m_isProLicense = licenseChecker.checkLicense(AccountId);
		
		if (m_isProLicense) {
			printf("pro���C�Z���X���m�F���܂���\n");
		}
	}	
}

//-------------------------------------------------------------------------------
// importFile()
//-------------------------------------------------------------------------------
//�Z���^�t�@�C����ǂݍ���ŏZ���^����̏���������
bool CAddressBookOperator::importFile()
{
	//string filePath = "./�Z���^�t�@�C��./" + m_addressBookFileName;
	string filePath = "./" + m_addressBookFileName;

	CFileImporter fileImporter(filePath);
	bool isFileOpened = fileImporter.fileOpen();

	if (!isFileOpened) {
		return false;
		
	}

	fileImporter.readFile();
	
	printf("%d���̏Z���^�f�[�^��ǂݍ��݂܂����B\n", 
		(int)fileImporter.setAddressVector().size());
	vector<CAddress>* AddressBookArray = &fileImporter.setAddressVector();
	//AddressBookArray = nullptr;
	if (m_isProLicense) {
		printf("[�Z���^�A�v���@pro��]\n");
		m_pAddressBook = new CAddressBookPro(AddressBookArray);//�f�X�g���N�^��delete
		m_pAddressBookDirector = m_pAddressBook;
	}
	else {
		printf("[�Z���^�A�v���@Trial��]\n");
		m_pAddressBook = new CAddressBookTrial(AddressBookArray);//�f�X�g���N�^��delete
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
//�����̏Z���^���t�@�C���ɏ㏑������
void CAddressBookOperator::exportFile()
{
	//string filePath = "./�Z���^�t�@�C��./" + m_addressBookFileName;
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
		printf("�t�@�C���𐳏�ɃI�[�v���ł��܂���ł����B\n");
	}
	
}


//-------------------------------------------------------------------------------
// selectAddressBookMove()
//-------------------------------------------------------------------------------
//�Z���^�ւ̑���
void CAddressBookOperator::operateAddressBook()
{

	ESelectMove selectMove = ESelectMove::Default;
	do {
		

		CInputChecker inputChecker;

		printf("1)�@�ǉ�\n");
		printf("2)�@�\��\n");
		printf("3)�@����\n");
		printf("4)�@�ҏW\n");
		printf("5)�@�폜\n");
		printf("6)�@�I��\n");
		printf("�@�@�I�����Ă��������F");


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


