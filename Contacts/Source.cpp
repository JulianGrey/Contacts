#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <new>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct contact_t {
	string firstName;
	string lastName;
};

char * convertStringToLower(char * cstring, int strSize) {
	const int arraySize = 26;
	char alphaUpper[arraySize] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	char alphaLower[arraySize] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	char * letter;

	for(unsigned i = 0; i < strSize; i++) {
		letter = static_cast<char *>(std::addressof(cstring[i]));
		for(unsigned j = 0; j < arraySize; j++) {
			if(*letter == alphaUpper[j]) {
				*letter = alphaLower[j];
			}
		}
	}
	return cstring;
}

char * convertStrToChars(string * input, char * cstring) {
	for(unsigned i = 0; i < (*input).size(); i++) {
		cstring[i] = (*input)[i];
	}
	cstring[(*input).size()] = '\0';

	return cstring;
}

char * convertStrToChars(string input, char * cstring) {
	for(unsigned i = 0; i < input.size(); i++) {
		cstring[i] = input[i];
	}
	cstring[input.size()] = '\0';
	return cstring;
}

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
	vector<contact_t> * pvcontact = new vector<contact_t>;
	pvcontact = readFile(pvcontact);
	if((*pvcontact).size() > 0) {
		for(unsigned i = 0; i < (*pvcontact).size(); i++) {
			cout << (*pvcontact)[i].firstName << " " << (*pvcontact)[i].lastName << '\n';
		}
	}
	else {
		cout << "No contacts found\n";
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

	cout << "\nContact '" << (*contact).firstName << " " << (*contact).lastName << "' created.";

	delete firstName;
	delete lastName;
	delete contact;

	return vcontact;
}

void editContact() {
	cout << "Edit contact selected";
}

void delContact() {
	cout << "Delete contact selected";
}

void searchContacts() {
	ifstream myfile("contacts.bin");

	bool * complete = new bool;
	contact_t * contact = new contact_t;
	string * firstName = new string;
	string * lastName = new string;
	string * input = new string;
	vector<contact_t> * vcontact = new vector<contact_t>;
	vector<string> * listNames = new vector<string>;
	vector<contact_t> * matchedNames = new vector<contact_t>;

	if(myfile.is_open()) {
		while(myfile >> *firstName >> *lastName) {
			(*contact).firstName = *firstName;
			(*contact).lastName = *lastName;
			(*vcontact).push_back(*contact);
		}
		myfile.close();
	}
	delete firstName;
	delete lastName;

	for(unsigned i = 0; i < (*vcontact).size(); i++) {
		char * cstring = new char[(*vcontact)[i].firstName.size() + (*vcontact)[i].lastName.size() + 2];

		(*listNames).push_back((*vcontact)[i].firstName + " " + (*vcontact)[i].lastName);
		(*listNames)[i] = convertStrToChars((*listNames)[i], cstring);
		(*listNames)[i] = convertStringToLower(cstring, (*listNames)[i].size());

		delete cstring;
	}

	std::cout << "Enter search parameters: ";
	getline(cin, *input);
	char * cstring = new char[(*input).size() + 1];

	cstring = convertStrToChars(input, cstring);
	cstring = convertStringToLower(cstring, (*input).size());

	for(unsigned i = 0; i < (*listNames).size(); i++) { // separate the names in the list
		*complete = false;
		for(unsigned j = 0; j < (*listNames)[i].size(); j++) { // separate the characters in the name
			if(*complete) { break; };
			for(unsigned k = 0; k < (*input).size(); k++) { // separate the characters in the search string
				if(*complete) { break; }
				if(cstring[k] != (*listNames)[i][j + k]) { break; }
				else if(k != (*input).size() - 1) { // if we aren't checking the last letter
					if(cstring[k] != (*listNames)[i][j + k]) { break; }
				}
				else {
					if(cstring[k] == (*listNames)[i][j + k]) {
						(*matchedNames).push_back((*vcontact)[i]);
						*complete = true;
					}
				}
			}
		}
	}
	delete complete;
	delete listNames;
	delete[] cstring;
	delete input;

	if((*matchedNames).size() > 1) {
		std::cout << "\n" << (*matchedNames).size() << " results found:\n\n";
	}
	else if((*matchedNames).size() == 1) {
		std::cout << "\n" << (*matchedNames).size() << " result found:\n\n";
	}
	else {
		std::cout << "\nNo results found.";
	}

	for(unsigned i = 0; i < (*matchedNames).size(); i++) {
		std::cout << (*matchedNames)[i].firstName << " " << (*matchedNames)[i].lastName << '\n';
	}
	delete matchedNames;
}

void deleteFrontendInputs(string * input, int * option) {
	delete input;
	delete option;
}

int frontend(vector<contact_t> * vcontact) {
	string * input = new string;
	int * option = new int;

	cout << "\n\nWhat service would you like to use?\n\n";
	cout << "1. List contacts\n";
	cout << "2. Add new contact\n";
	cout << "3. Edit contact\n";
	cout << "4. Delete contact\n";
	cout << "5. Search contacts\n\n";
	cout << "0. Exit\n\n";

	getline(cin, *input);
	(stringstream)*input >> *option;
	cout << "\n";
	switch(*option) {
	case 1:
		listContacts();
		deleteFrontendInputs(input, option);
		frontend(vcontact);
		break;
	case 2:
		vcontact = addContact(vcontact);
		deleteFrontendInputs(input, option);
		frontend(vcontact);
		break;
	case 3:
		editContact();
		deleteFrontendInputs(input, option);
		frontend(vcontact);
		break;
	case 4:
		delContact();
		deleteFrontendInputs(input, option);
		frontend(vcontact);
		break;
	case 5:
		searchContacts();
		deleteFrontendInputs(input, option);
		frontend(vcontact);
		break;
	default:
		deleteFrontendInputs(input, option);
		return 0;
		break;
	}
}

int main() {
	vector<contact_t> * pvcontact = new vector<contact_t>;
	pvcontact = readFile(pvcontact);

	cout << "Welcome.";
	frontend(pvcontact);
	delete pvcontact;

	system("PAUSE");
	return 0;
}