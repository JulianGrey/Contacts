#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <new>
#include <sstream>
#include <string>
#include <vector>
#include "Contact.hpp"

char * convertStringToLower(char * cstring, int strSize) {
	const int arraySize = 26;
	char alphaUpper[arraySize] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
								  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	char alphaLower[arraySize] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
								  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	char * letter;

	for(size_t i = 0; i < strSize; i++) {
		letter = static_cast<char *>(std::addressof(cstring[i]));
		for(unsigned j = 0; j < arraySize; j++) {
			if(*letter == alphaUpper[j]) {
				*letter = alphaLower[j];
			}
		}
	}
	return cstring;
}

char * convertStrToChars(std::string input, char * cstring) {
	for(unsigned i = 0; i < input.size(); i++) {
		cstring[i] = input[i];
	}
	cstring[input.size()] = '\0';
	return cstring;
}

void writeFile(std::vector<Contact> * vcontact) {
	std::ofstream myfile("contacts.bin");
	if(myfile.is_open()) {
		for(size_t i = 0; i < (*vcontact).size(); i++) {
			myfile << (*vcontact)[i].getFullName() << '\n';
		}
		myfile.close();
	}
	else {
		std::cout << "Unable to open file\n";
	}
}

std::vector<Contact> * readFile(std::vector<Contact> * pvcontact) {
	std::ifstream myfile("contacts.bin");
	std::string * firstName = new std::string;
	std::string * lastName = new std::string;

	(*pvcontact).clear();

	if(myfile.is_open()) {
		while(myfile >> *firstName >> *lastName) {
			Contact contact;
			contact.setFirstName(*firstName);
			contact.setLastName(*lastName);
			(*pvcontact).push_back(contact);
		}
		myfile.close();
	}
	delete firstName;
	delete lastName;

	return pvcontact;
}

void listContacts(std::vector<Contact>* vcontact) {
	if((*vcontact).size() > 0) {
		for(size_t i = 0; i < (*vcontact).size(); i++) {
			std::cout << (*vcontact)[i].getFullName() << '\n';
		}
	}
	else {
		std::cout << "No contacts found\n";
	}
}

std::vector<Contact> * addContact(std::vector<Contact> * vcontact) {
	std::string * firstName = new std::string;
	std::string * lastName = new std::string;

	Contact contact;

	std::cout << "\nEnter the contact's first name: ";
	getline(std::cin, *firstName);

	std::cout << "\nEnter the contact's last name: ";
	getline(std::cin, *lastName);

	contact.setFirstName(*firstName);
	contact.setLastName(*lastName);
	(*vcontact).push_back(contact);

	std::cout << "\nContact '" << contact.getFullName() << "' created.";

	delete firstName;
	delete lastName;

	return vcontact;
}

void editContact() {
	std::cout << "Edit contact selected";
}

void delContact() {
	std::cout << "Delete contact selected";
}

void searchContacts(std::vector<Contact>* vcontact) {
	bool * complete = new bool;
	std::string * input = new std::string;
	std::vector<std::string> * listNames = new std::vector<std::string>;
	std::vector<Contact> * matchedNames = new std::vector<Contact>;

	for(size_t i = 0; i < (*vcontact).size(); i++) {
		char* cstring = new char[(*vcontact)[i].getNameLength() + 1];

		cstring = convertStrToChars((*vcontact)[i].getFullName(), cstring);
		cstring = convertStringToLower(cstring, (*vcontact)[i].getNameLength() + 1);
		(*listNames).push_back(std::string(cstring));

		delete cstring;
	}

	std::cout << "Enter search parameters: ";
	getline(std::cin, *input);
	char * cstring = new char[(*input).size() + 1];

	cstring = convertStrToChars(*input, cstring);
	cstring = convertStringToLower(cstring, (*input).size());

	for(size_t i = 0; i < (*listNames).size(); i++) { // separate the names in the list
		*complete = false;
		for(size_t j = 0; j < (*listNames)[i].size(); j++) { // separate the characters in the name
			if(*complete) { break; };
			for(size_t k = 0; k < (*input).size(); k++) { // separate the characters in the search string
				if(*complete) { break; }
				if(cstring[k] != (*listNames)[i][j + k]) { break; }
				else if(k != (*input).size() - 1) { // if we aren't checking the last letter of search string
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

	for(size_t i = 0; i < (*matchedNames).size(); i++) {
		std::cout << (*matchedNames)[i].getFullName() << '\n';
	}
	delete matchedNames;
}

std::vector<Contact>* frontend(std::vector<Contact>* vcontact, std::string* input, int* option, bool exit) {
	while(!exit) {
		std::cout << "\n\nWhat service would you like to use?\n\n";
		std::cout << "1. List contacts\n";
		std::cout << "2. Add new contact\n";
		std::cout << "3. Edit contact\n";
		std::cout << "4. Delete contact\n";
		std::cout << "5. Search contacts\n\n";
		std::cout << "0. Exit\n\n";

		getline(std::cin, *input);
		(std::stringstream)*input >> *option;
		std::cout << "\n";
		switch(*option) {
			case 1:
				listContacts(vcontact);
				break;
			case 2:
				vcontact = addContact(vcontact);
				break;
			case 3:
				editContact();
				break;
			case 4:
				delContact();
				break;
			case 5:
				searchContacts(vcontact);
				break;
			case 0:
				exit = true;
				break;
			default:
				std::cout << "Invalid option\n\n";
				break;
		}
	}
	return vcontact;
}

int main() {
	std::string input;
	std::string* inputPtr;
	int option;
	int* optionPtr;
	bool exit = false;

	inputPtr = &input;
	optionPtr = &option;

	std::vector<Contact> * vcontact = new std::vector<Contact>;
	vcontact = readFile(vcontact);

	std::cout << "Welcome.";
	vcontact = frontend(vcontact, inputPtr, optionPtr, exit);
	writeFile(vcontact);
	delete vcontact;

	return 0;
}