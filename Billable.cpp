#include "Billable.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

namespace seneca {

	//Default constructor
	Billable::Billable() : m_name(nullptr), m_price(0.0) {}

	//Destructor
	Billable::~Billable() {
		delete[] m_name;
	}

	//Copy constructor
	Billable::Billable(const Billable& bill) {
		m_name = new char[ut.strlen(bill.m_name) + 1];
		ut.strcpy(m_name, bill.m_name);
		m_price = bill.m_price;
	}

	//The copy assignment operator
	Billable& Billable::operator=(const Billable& bill) {
		if (this != &bill) {
			ut.alocpy(m_name, bill.m_name);

			m_price = bill.m_price;
		}
		return *this;
	}

	//Sets item price
	void Billable::price(double value) {
		m_price = value;
	}

	// Sets the name
	void Billable::name(const char* name) {
		ut.alocpy(m_name, name);
	}

	//Gives the price of the item
	double Billable::price() const {
		return m_price;
	}

	// Operator overload
	Billable::operator const char* () const {
		return m_name;
	}

	//Conversion operators
	double operator+(double money, const Billable& B) {
		return money + B.price();
	}

	double& operator+=(double& money, const Billable& B) {
		money += B.price();
		return money;
	}
}
