#pragma once

#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;


//-------------------------------------------------------------------------------
//CAddress 
//-------------------------------------------------------------------------------
//一人分の住所録のためのクラス
class CAddress
{
public:
//-------------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------------
//アドレス一つの作成とアドレスの総数と一番大きいidを保持する
	CAddress(int inId,
		string inName,
		string inResidence,
		string inPhoneNumber, 
		string inEmail);
	
//-------------------------------------------------------------------------------
// display()
//-------------------------------------------------------------------------------
//メンバ変数の開示
	void display();

//-------------------------------------------------------------------------------
// editAddress()
//-------------------------------------------------------------------------------
//メンバ変数の編集
	void editAddress(
		string inName,//編集後の名前
		string inResidence, //編集後の住所
		string inPhoneNumber, //編集後の電話番号
		string inEmail);//編集後のemailアドレス
	


	int getId()const;
	string getName()const;
	string getResidence()const;
	string getPhoneNumber()const;
	string getEmail()const;
	static int getMaxId();


private:
	int m_id;
	string m_name;
	string m_residence;
	string m_phoneNumber;
	string m_email;
	static int ms_maxId;
};

