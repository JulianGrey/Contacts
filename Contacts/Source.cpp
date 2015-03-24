#include <algorithm>
#include <fstream>
#include <iostream>
#include <new>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct contact_t {
	string firstName;
	string lastName;
};

void writeFile(vector<contact_t> * vcontact) {
	ofstream myfile("contacts.bin");
	if(myfile.is_open()) {
		for(unsigned i = 0; i < (*vcontact).size(); i++) {
			myfile << (*vcontact)[i].firstName << " " << (*vcontact)[i].lastName << '\n';
		}
		myfile.close();
	}
	else {
		cout << "Unable to open file\n";
	}
}

vector<contact_t> * readFile(vector<contact_t> * pvcontact) {
	ifstream myfile("contacts.bin");
	contact_t * contact = new contact_t;
	string * firstName = new string;
	string * lastName = new string;

	(*pvcontact).clear();

	if(myfile.is_open()) {
		while(myfile >> *firstName >> *lastName) {
			(*contact).firstName = *firstName;
			(*contact).lastName = *lastName;
			(*pvcontact).push_back(*contact);
		}
		myfile.close();
	}
	delete contact;
	delete firstName;
	delete lastName;

	return pvcontact;
}

void listContacts() {
	cout << "\nList contacts selected\n";
	vector<contact_t> * pvcontact = new vector<contact_t>;
	pvcontact = readFile(pvcontact);
	for(unsigned i = 0; i < (*pvcontact).size(); i++) {
		cout << (*pvcontact)[i].firstName << " " << (*pvcontact)[i].lastName << '\n';
	}
	delete pvcontact;
}

vector<contact_t> * addContact(vector<contact_t> * vcontact) {
	string * firstName = new string;
	string * lastName = new string;

	contact_t * contact = new contact_t;

	cout << "\nEnter the contact's first name: ";
	getline(cin, *firstName);

	cout << "\nEnter the contact's last name: ";
	getline(cin, *lastName);

	(*contact).firstName = *firstName;
	(*contact).lastName = *lastName;
	(*vcontact).push_back(*contact);
	writeFile(vcontact);

	cout << "\nContact '" << (*contact).firstName << " " << (*contact).lastName << "' created.\n\n";

	delete firstName;
	delete lastName;
	delete contact;

	return vcontact;
}

void editContact() {
	cout << "\nEdit contact selected\n";
}

void delContact() {
	cout << "\nDelete contact selected\n";
}

int frontend(vector<contact_t> * vcontact) {
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
		frontend(vcontact);
		break;
	case 2:
		vcontact = addContact(vcontact);
		frontend(vcontact);
		break;
	case 3:
		editContact();
		frontend(vcontact);
		break;
	case 4:
		delContact();
		frontend(vcontact);
		break;
	default:
		return 0;
		break;
	}
}

int main() {
	vector<contact_t> * pvcontact = new vector<contact_t>;
	pvcontact = readFile(pvcontact);

	cout << "Welcome.\n";
	frontend(pvcontact);
	delete pvcontact;

	system("PAUSE");
	return 0;
}