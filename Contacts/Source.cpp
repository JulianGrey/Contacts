#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void addContact() {
	cout << "\nAdd contact selected\n";
}
void editContact() {
	cout << "\nEdit contact selected\n";
}
void delContact() {
	cout << "\nDelete contact selected\n";
}

int main() {
	string mystr;
	
	int option;
	int * myptr = &option;

	cout << "Welcome.\n";
	cout << "What service would you like to use?\n\n";
	cout << "1. Add new contact\n";
	cout << "2. Edit contact\n";
	cout << "3. Delete contact\n\n";

	getline(cin, mystr);
	(stringstream)mystr >> *myptr;
	switch(*myptr) {
		case 1:
			addContact();
			break;
		case 2:
			editContact();
			break;
		case 3:
			delContact();
			break;
		default:
			break;
	}

	system("PAUSE");
	return 0;
}