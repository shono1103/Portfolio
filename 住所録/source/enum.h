#pragma once


//CAddressOperator�ł̑���@�\�I��p
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

//CAddressBookPro�̌����@�\�ł̍��ڑI��p
enum class ESearchItem
{
	
	Name = 1,
	Residence,
	PhoneNumber,
	Email
};

//CAddressBook�̌������[�h�I��p
enum class ESearchMode
{
	Exact = 1,
	Partial
};