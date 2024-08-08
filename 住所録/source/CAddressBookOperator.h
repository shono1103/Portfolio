#pragma once
#include"CAddressBook.h"
#include"CAddressBookTrial.h"
#include"CFileImporter.h"
#include"CFileExporter.h"
#include"IAddressBookDirector.h"
#include"CInputChecker.h"
#include"enum.h"
#include"CLicenseChecker.h"
#include"CAddressBookPro.h"




//-------------------------------------------------------------------------------
// CAddressBookOperator
//-------------------------------------------------------------------------------
//住所録の操作をする
class CAddressBookOperator
{
public:
//-------------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------------
//各メンバ変数の初期化をする
	CAddressBookOperator(
		string inAddressBookFileName);//操作する住所録のファイル名


//-------------------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------------------
//m_pAddressBookの解放
	~CAddressBookOperator();


//-------------------------------------------------------------------------------
// initialize()
//-------------------------------------------------------------------------------
//最初に行う処理
	bool initialize();


//-------------------------------------------------------------------------------
// selectAddressBookMove()
//-------------------------------------------------------------------------------
//住所録への操作
	void operateAddressBook();




//-------------------------------------------------------------------------------
// exportFile()
//-------------------------------------------------------------------------------
//操作後の住所録をファイルに上書きする
	void exportFile();

private:
//-------------------------------------------------------------------------------
// importFile()
//-------------------------------------------------------------------------------
//住所録ファイルを読み込んで住所録操作の準備をする
	bool importFile();
//-------------------------------------------------------------------------------
// checkLicense()
//-------------------------------------------------------------------------------
//Licenseチェックをする
	void allowProLicense();






	//proもしくはtrialの住所録が入る
	CAddressBook* m_pAddressBook;
	//住所録の処理を管理する
	IAddressBookDirector* m_pAddressBookDirector;
	//ライセンスの有無を保持する
	bool m_isProLicense;
	//読み込み書き込みをするファイル名
	string m_addressBookFileName;
};