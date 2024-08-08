#include "CInputChecker.h"
#include<stdio.h>


//-------------------------------------------------------------------------------
// inputId()
//-------------------------------------------------------------------------------
//ID�̓��͂��s��
void CInputChecker::inputId(
	const char* inMessage,//���͎��ɕ\������������
	int& outId)//���͂��ꂽid���i�[����
{
	bool isNormalInput = false;
	int scanId = 0;
		

	while (!isNormalInput) {

		isNormalInput = true;
		if (inMessage == nullptr) {
			printf("����:");
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
//���O�̓��͂��s���Astring�^�ɂ���
void CInputChecker::inputName(
	string& outName)//���͂��ꂽ���O���i�[����
{

	printf("�����F");
	char scanName[ADDRESS_NAME_LENGTH_] = "\0";
	gets_s(scanName,ADDRESS_NAME_LENGTH_);
	string name(scanName);
	outName = name;
}


//-------------------------------------------------------------------------------
// inputRegidence()
//-------------------------------------------------------------------------------
//�Z���̓��͂��s���Astring�^�ɂ���
void CInputChecker::inputResidence(
	string& outResidence)//���͂��ꂽ�Z�����i�[����
{
	printf("�Z���F");
	char scanResidence[ADDRESS_RESIDENCE_LENGTH_] = "\0";
	gets_s(scanResidence,ADDRESS_RESIDENCE_LENGTH_);
	string Residence(scanResidence);
	outResidence = Residence;
}


//-------------------------------------------------------------------------------
// inputPhoneNumber()
//-------------------------------------------------------------------------------
//�d�b�ԍ��̓��͂��s���Astring�^�ɂ���
void CInputChecker::inputPhoneNumber(
	string& outPhoneNumber)//���͂��ꂽ�d�b�ԍ����i�[����
{
	printf("�d�b�ԍ��F");
	char scanPhoneNumber[ADDRESS_PHONENUMBER_LENGTH_] = "\0";
	gets_s(scanPhoneNumber,ADDRESS_PHONENUMBER_LENGTH_);
	string PhoneNumber(scanPhoneNumber);
	outPhoneNumber = PhoneNumber;
}


//-------------------------------------------------------------------------------
// inputEmail()
//-------------------------------------------------------------------------------
//���[���A�h���X�̓��͂��s���Astring�^�ɂ���
void CInputChecker::inputEmail(
	string& outEmail)//���͂��ꂽ���[���A�h���X���i�[����
{
	printf("���[���A�h���X�F");
	char scanEmail[ADDRESS_EMAIL_LENGTH_] = "\0";
	gets_s(scanEmail,ADDRESS_EMAIL_LENGTH_);
	string Email(scanEmail);
	outEmail = Email;
}


//-------------------------------------------------------------------------------
// inputSelectMove()
//-------------------------------------------------------------------------------
//�ǉ��A�����Ȃǂ̑���̑I�����`�F�b�N������
void CInputChecker::inputSelectMove(
	ESelectMove& outSelectMove)//����̎�ނɉ������l���i�[����
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
			printf("�������l(1�`6)����͂��Ă��������F");
		}

	}
}


//-------------------------------------------------------------------------------
// inputSearchItem()
//-------------------------------------------------------------------------------
//CAddressBook�ł̌����@�\�̌������ڑI���̃`�F�b�N������
void CInputChecker::inputSearchItem(
	ESearchItem& outSearchItem)//�������ڂɉ������l���i�[����
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
			printf("�������l(1�`4)����͂��Ă��������F");
		}
	}
}
//-------------------------------------------------------------------------------
// inputSearchMode()
//-------------------------------------------------------------------------------
//CAddressBook�ł̌����@�\�ł̊��S��v�A������v�i�������[�h�j�̑I�����`�F�b�N����
void CInputChecker::inputSearchMode(
	ESearchMode& outSearchMode)//�������[�h�ɉ������l���i�[����
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
			printf("�������l(1�`2)����͂��Ă��������F");
		}

	}
}
//-------------------------------------------------------------------------------
//input_yorn()
//-------------------------------------------------------------------------------
//y��������n�̓��͂𑣂��A���̃`�F�b�N������
void CInputChecker::input_yorn(
	char& out_yorn,//y��������n���i�[����
	const char* inMessage)//���͎��̃��b�Z�[�W
{
	
	bool isSafe = false;
	

	while ((out_yorn != 'y' && out_yorn != 'n') || !isSafe) {
		isSafe = true;
		if (inMessage == nullptr) {
			printf("����:");
		}
		else {
			printf("%s", inMessage);
		}
		

		scanf_s("%c", &out_yorn, 1);

		//1�����ȏ���͂��ꂽ�ꍇ
		while (getchar() != '\n') {
			isSafe = false;
		}

	}

}

//-------------------------------------------------------------------------------
//inputMultiId()
//-------------------------------------------------------------------------------
//����ID���󂯎��Avector�ɂ��ĕԂ�
void CInputChecker::inputMultiId(
	vector<int>& invId)//������ID���i�[����
{
	
	char id[ADDRESS_ID_LENGTH_] = "";

	char box = '\0';
	printf("�폜����f�[�^����͂��Ă��������F");
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
