#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct contact_t {
	string firstName;
	string lastName;
};

void writeFile(contact_t contact) {
	ofstream myfile("contacts.bin");
	if(myfile.is_open()) {
		myfile << contact.firstName << " " << contact.lastName;
		myfile.close();
	}
	else {
		cout << "Unable to open file\n";
	}
}

void readFile() {
	string line;
	ifstream myfile("contacts.bin");
	if(myfile.is_open()) {
		while(getline(myfile, line)) {
			cout << line << '\n';
		}
		myfile.close();
	}
	else {
		cout << "Unable to open file\n";
	}
}

void listContacts() {
	cout << "\nList contacts selected\n";
	readFile();
}

void addContact() {
	string * myptr, mystr;
	contact_t *cptr, contact;
	cptr = &contact;

	cout << "\nEnter the contact's first name: ";
	getline(cin, cptr->firstName);
	cout << "\nEnter the contact's last name: ";
	getline(cin, cptr->lastName);
	cout << "\nContact '" << contact.firstName << " " << contact.lastName << "' created.\n\n";
	writeFile(contact);
}
void editContact() {
	cout << "\nEdit contact selected\n";
}

void delContact() {
	cout << "\nDelete contact selected\n";
}

int frontend() {
	string mystr;

	int option;
	int * myptr = &option;

	cout << "What service would you like to use?\n\n";
	cout << "1. List contacts\n";
	cout << "2. Add new contact\n";
	cout << "3. Edit contact\n";
	cout << "4. Delete contact\n\n";

	getline(cin, mystr);
	(stringstream)mystr >> *myptr;
	switch(*myptr) {
	case 1:
		listContacts();
		frontend();
		break;
	case 2:
		addContact();
		frontend();
		break;
	case 3:
		editContact();
		frontend();
		break;
	case 4:
		delContact();
		frontend();
		break;
	default:
		return 0;
		break;
	}
}

int main() {
	cout << "Welcome.\n";
	frontend();

	system("PAUSE");
	return 0;
}