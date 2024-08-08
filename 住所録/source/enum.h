#pragma once


//CAddressOperatorでの操作機能選択用
enum class ESelectMove
{
	Default,
	Add = 1,
	Display,
	Search,
	Edit,
	Remove,
	End

};

//CAddressBookProの検索機能での項目選択用
enum class ESearchItem
{
	
	Name = 1,
	Residence,
	PhoneNumber,
	Email
};

//CAddressBookの検索モード選択用
enum class ESearchMode
{
	Exact = 1,
	Partial
};