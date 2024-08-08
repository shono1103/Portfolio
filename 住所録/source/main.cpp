#include"CFileImporter.h"
#include"CAddressBook.h"
#include"CAddressBookTrial.h"
#include"IAddressBookDirector.h"
#include"CAddressBookOperator.h"


int CAddress::ms_maxId = 0;

int main() {

	try {
		//CAddressBookOperator addressBookOperator("error_colon_AddressBook.txt");
		//CAddressBookOperator addressBookOperator("error_comma_AddressBook.txt");
		//CAddressBookOperator addressBookOperator("error_DuplicateID_AddressBook.txt");
		//CAddressBookOperator addressBookOperator("error_semicolon_AddressBook.txt");
		//CAddressBookOperator addressBookOperator("error_slash_AddressBook.txt");
		//CAddressBookOperator addressBookOperator("error_space_AddressBook.txt");
		//CAddressBookOperator addressBookOperator("error_type_AddressBook.txt");
		//CAddressBookOperator addressBookOperator("10_AddressBook.txt");
		CAddressBookOperator addressBookOperator("1000_AddressBook.txt");
		//CAddressBookOperator addressBookOperator("1001_AddressBook.txt");

		bool existAddressBook = addressBookOperator.initialize();



		if (!existAddressBook) {
			printf("ÉtÉ@ÉCÉãì«Ç›çûÇ›Ç≈Ç´Ç‹ÇπÇÒÇ≈ÇµÇΩ\n");
			return 1;
		}

		addressBookOperator.operateAddressBook();

		addressBookOperator.exportFile();

	}
	catch (int) {
		printf("Ç±Ç±ÇæÇÊ");
	}
	

	
	



	return 0;
}