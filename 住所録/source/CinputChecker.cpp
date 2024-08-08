#include "CInputChecker.h"
#include<stdio.h>


//-------------------------------------------------------------------------------
// inputId()
//-------------------------------------------------------------------------------
//IDの入力を行う
void CInputChecker::inputId(
	const char* inMessage,//入力時に表示させたい文
	int& outId)//入力されたidを格納する
{
	bool isNormalInput = false;
	int scanId = 0;
		

	while (!isNormalInput) {

		isNormalInput = true;
		if (inMessage == nullptr) {
			printf("入力:");
		}
		else {
			printf("%s", inMessage);
		}

		scanf_s("%d", &scanId);
		while (getchar()!='\n')
		{
			isNormalInput = false;
		}

	}

	outId = scanId;
}


//-------------------------------------------------------------------------------
// inputName()
//-------------------------------------------------------------------------------
//名前の入力を行い、string型にする
void CInputChecker::inputName(
	string& outName)//入力された名前を格納する
{

	printf("氏名：");
	char scanName[ADDRESS_NAME_LENGTH_] = "\0";
	gets_s(scanName,ADDRESS_NAME_LENGTH_);
	string name(scanName);
	outName = name;
}


//-------------------------------------------------------------------------------
// inputRegidence()
//-------------------------------------------------------------------------------
//住所の入力を行い、string型にする
void CInputChecker::inputResidence(
	string& outResidence)//入力された住所を格納する
{
	printf("住所：");
	char scanResidence[ADDRESS_RESIDENCE_LENGTH_] = "\0";
	gets_s(scanResidence,ADDRESS_RESIDENCE_LENGTH_);
	string Residence(scanResidence);
	outResidence = Residence;
}


//-------------------------------------------------------------------------------
// inputPhoneNumber()
//-------------------------------------------------------------------------------
//電話番号の入力を行い、string型にする
void CInputChecker::inputPhoneNumber(
	string& outPhoneNumber)//入力された電話番号を格納する
{
	printf("電話番号：");
	char scanPhoneNumber[ADDRESS_PHONENUMBER_LENGTH_] = "\0";
	gets_s(scanPhoneNumber,ADDRESS_PHONENUMBER_LENGTH_);
	string PhoneNumber(scanPhoneNumber);
	outPhoneNumber = PhoneNumber;
}


//-------------------------------------------------------------------------------
// inputEmail()
//-------------------------------------------------------------------------------
//メールアドレスの入力を行い、string型にする
void CInputChecker::inputEmail(
	string& outEmail)//入力されたメールアドレスを格納する
{
	printf("メールアドレス：");
	char scanEmail[ADDRESS_EMAIL_LENGTH_] = "\0";
	gets_s(scanEmail,ADDRESS_EMAIL_LENGTH_);
	string Email(scanEmail);
	outEmail = Email;
}


//-------------------------------------------------------------------------------
// inputSelectMove()
//-------------------------------------------------------------------------------
//追加、検索などの操作の選択をチェックをする
void CInputChecker::inputSelectMove(
	ESelectMove& outSelectMove)//操作の種類に応じた値を格納する
{
	bool isSafe = false;





	while (!isSafe) {
		isSafe = true;
		scanf_s("%d", &outSelectMove);
		while (getchar()!='\n')
		{
			isSafe = false;
		}
		if (outSelectMove != ESelectMove::Add &&
			outSelectMove != ESelectMove::Display &&
			outSelectMove != ESelectMove::Search &&
			outSelectMove != ESelectMove::Edit &&
			outSelectMove != ESelectMove::Remove &&
			outSelectMove != ESelectMove::End) {
			isSafe = false;
		}
		
		if (!isSafe) {
			printf("正しい値(1～6)を入力してください：");
		}

	}
}


//-------------------------------------------------------------------------------
// inputSearchItem()
//-------------------------------------------------------------------------------
//CAddressBookでの検索機能の検索項目選択のチェックをする
void CInputChecker::inputSearchItem(
	ESearchItem& outSearchItem)//検索項目に応じた値を格納する
{
	bool isSafe = false;

	while (!isSafe){isSafe = true;
		scanf_s("%d", &outSearchItem);
		while (getchar()!='\n')
		{
			isSafe = false;
		}
		if (outSearchItem != ESearchItem::Name &&
			outSearchItem != ESearchItem::Residence &&
			outSearchItem != ESearchItem::PhoneNumber &&
			outSearchItem != ESearchItem::Email) {
			isSafe = false;
		}
		
		if (!isSafe) {
			printf("正しい値(1～4)を入力してください：");
		}
	}
}
//-------------------------------------------------------------------------------
// inputSearchMode()
//-------------------------------------------------------------------------------
//CAddressBookでの検索機能での完全一致、部分一致（検索モード）の選択をチェックする
void CInputChecker::inputSearchMode(
	ESearchMode& outSearchMode)//検索モードに応じた値を格納する
{
	bool isSafe = false;

	while (!isSafe) {
		isSafe = true;
		scanf_s("%d", &outSearchMode);
		while (getchar() != '\n')
		{
			isSafe = false;
		}
		if (outSearchMode != ESearchMode::Partial &&
			outSearchMode != ESearchMode::Exact) {
			isSafe = false;
		}

		if (!isSafe) {
			printf("正しい値(1～2)を入力してください：");
		}

	}
}
//-------------------------------------------------------------------------------
//input_yorn()
//-------------------------------------------------------------------------------
//yもしくはnの入力を促し、そのチェックをする
void CInputChecker::input_yorn(
	char& out_yorn,//yもしくはnを格納する
	const char* inMessage)//入力時のメッセージ
{
	
	bool isSafe = false;
	

	while ((out_yorn != 'y' && out_yorn != 'n') || !isSafe) {
		isSafe = true;
		if (inMessage == nullptr) {
			printf("入力:");
		}
		else {
			printf("%s", inMessage);
		}
		

		scanf_s("%c", &out_yorn, 1);

		//1文字以上入力された場合
		while (getchar() != '\n') {
			isSafe = false;
		}

	}

}

//-------------------------------------------------------------------------------
//inputMultiId()
//-------------------------------------------------------------------------------
//複数IDを受け取り、vectorにして返す
void CInputChecker::inputMultiId(
	vector<int>& invId)//複数のIDを格納する
{
	
	char id[ADDRESS_ID_LENGTH_] = "";

	char box = '\0';
	printf("削除するデータを入力してください：");
	int count = 0;

	
	 while (box!='\n'){
		
		box = getchar();
		
		if ((count >= ADDRESS_ID_LENGTH_ - 1)||
			(box < '0'||'9' < box)) {
			
			int setId = atoi(id);
			if (setId > 0) {
				invId.push_back(setId);
			}
			for (int i = 0; i <= count; ++i) {
				id[i] = '\0';
			}
			count = 0;
		}
		else {
			id[count] = box;
			++count;
		}
	 }
	
}
