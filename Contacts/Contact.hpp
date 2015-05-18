#include <iostream>
#include <string>

class Contact {
  private:
	std::string firstName;
	std::string lastName;
	int strSize;
  public:
	void setFirstName(std::string name) {
		this->firstName = name;
	}
	std::string getFirstName() {
		return this->firstName;
	}

	void setLastName(std::string name) {
		this->lastName = name;
	}
	std::string getLastName() {
		return this->lastName;
	}

	std::string getFullName() {
		return firstName + " " + lastName;
	}

	int getNameLength() {
		return this->getFullName().size();
	}
};