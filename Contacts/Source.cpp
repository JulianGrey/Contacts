#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct contact_t {
	string firstName;
	string lastName;
};

void writeFile(vector<contact_t> vcontact) {
	ofstream myfile("contacts.bin");
	if(myfile.is_open()) {
		for(unsigned i = 0; i < vcontact.size(); i++) {
			myfile << (vcontact)[i].firstName << " " << (vcontact)[i].lastName << '\n';
		}
		myfile.close();
	}
	else {
		cout << "Unable to open file\n";
	}
}

vector<contact_t> readFile() {
	ifstream myfile("contacts.bin");
	contact_t contact;
	contact_t * pcontact;
	string firstName, lastName;
	string * pFirstName = &firstName;
	string * pLastName = &lastName;
	vector<contact_t> vcontact;
	vector<contact_t> * pvcontact;

	pcontact = &contact;
	pvcontact = &vcontact;

	if(myfile.is_open()) {
		while(myfile >> *pFirstName >> *pLastName) {
			(*pcontact).firstName = *pFirstName;
			(*pcontact).lastName = *pLastName;
			(*pvcontact).push_back(*pcontact);
		}
		myfile.close();
	}
	return vcontact;
}

void listContacts() {
	cout << "\nList contacts selected\n";
	vector<contact_t> vcontact = readFile();
	vector<contact_t> *pvcontact = &vcontact;
	for(unsigned i = 0; i < (*pvcontact).size(); i++) {
		cout << (*pvcontact)[i].firstName << " " << (*pvcontact)[i].lastName << '\n';
	}
}

vector<contact_t> addContact(vector<contact_t> vcontact) {
	string firstName, lastName, input;
	string * myptr;
	contact_t contact;
	contact_t * pcontact;

	cout << "\nEnter the contact's first name: ";
	myptr = &firstName;
	getline(cin, input);
	(stringstream)input >> *myptr;

	cout << "\nEnter the contact's last name: ";
	myptr = &lastName;
	getline(cin, input);
	(stringstream)input >> *myptr;

	pcontact = &contact;
	(*pcontact).firstName = firstName;
	(*pcontact).lastName = lastName;
	vcontact.push_back(*pcontact);
	writeFile(vcontact);

	cout << "\nContact '" << contact.firstName << " " << contact.lastName << "' created.\n\n";
	return vcontact;
}
void editContact() {
	cout << "\nEdit contact selected\n";
}

void delContact() {
	cout << "\nDelete contact selected\n";
}

int frontend(vector<contact_t> vcontact) {
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
	cout << "Welcome.\n";

	vector<contact_t> vcontact = readFile();
	vector<contact_t> * pvcontact = &vcontact;

	for(unsigned i = 0; i < (*pvcontact).size(); i++) {
		cout << (*pvcontact)[i].firstName << " " << (*pvcontact)[i].lastName << '\n';
	}

	frontend(vcontact);

	system("PAUSE");
	return 0;
}