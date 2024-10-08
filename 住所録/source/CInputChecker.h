#pragma once
#include<string>
#include<stdlib.h>
#include<vector>
#include"CAddress.h"
#include"define.h"
#include"enum.h"
using namespace std;


class CInputChecker
{
public:
//-------------------------------------------------------------------------------
// inputId()
//-------------------------------------------------------------------------------
//IDの入力を行う
	void inputId(
		const char* inMessage,//入力時に表示させたい文
		int& outId);//入力されたidを格納する
	
//-------------------------------------------------------------------------------
// inputName()
//-------------------------------------------------------------------------------
//名前の入力を行い、string型にする
	void inputName(
		string& outName);//入力された名前を格納する

//-------------------------------------------------------------------------------
// inputRegidence()
//-------------------------------------------------------------------------------
//住所の入力を行い、string型にする
	void inputResidence(
		string& outResidence);//入力された住所を格納する

//-------------------------------------------------------------------------------
// inputPhoneNumber()
//-------------------------------------------------------------------------------
//電話番号の入力を行い、string型にする
	void inputPhoneNumber(
		string& outPhoneNumber);//入力された電話番号を格納する

//-------------------------------------------------------------------------------
// inputEmail()
//-------------------------------------------------------------------------------
//メールアドレスの入力を行い、string型にする
	void inputEmail(
		string& outPhoneNumber);//入力されたメールアドレスを格納する

//-------------------------------------------------------------------------------
// inputSelectMove()
//-------------------------------------------------------------------------------
//追加、検索などの操作の選択をチェックをする
	void inputSelectMove(
		ESelectMove& outSelectMove);//操作の種類に応じた値を格納する


//-------------------------------------------------------------------------------
// inputSearchItem()
//-------------------------------------------------------------------------------
//CAddressBookでの検索機能の検索項目選択のチェックをする
	void inputSearchItem(
		ESearchItem& outSearchItem);//検索項目に応じた値を格納する

//-------------------------------------------------------------------------------
// inputSearchMode()
//-------------------------------------------------------------------------------
//CAddressBookでの検索機能での完全一致、部分一致（検索モード）の選択をチェックする
	void inputSearchMode(
		ESearchMode& outSearchMode);//検索モードに応じた値を格納する

//-------------------------------------------------------------------------------
//input_yorn()
//-------------------------------------------------------------------------------
//yもしくはnの入力を促し、そのチェックをする
	void input_yorn(
		char& out_yorn,//yもしくはnを格納する
		const char*  inMessage);//入力時のメッセージ


//-------------------------------------------------------------------------------
//inputMultiId()
//-------------------------------------------------------------------------------
//複数IDを受け取り、vectorにして返す
	void inputMultiId(
		vector<int>& invId);//複数のIDを格納する


};



