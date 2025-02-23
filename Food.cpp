#include "Food.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Menu.h"

using namespace std;
namespace seneca {

	Food::Food() : Billable(), m_ordered(false), m_child(false), m_customize(nullptr) {}

	Food::~Food() {
		delete[] m_customize;
	}

	Food::Food(const Food& food) : Billable(food), m_ordered(food.m_ordered), m_child(food.m_child), m_customize(nullptr) {
		if (food.m_customize) {
			m_customize = ut.alocpy(food.m_customize);
		}
	}

	Food& Food::operator=(const Food& food) {
		if (this != &food) {
			Billable::operator=(food);
			m_ordered = food.m_ordered;
			m_child = food.m_child;
			delete[] m_customize;
			m_customize = nullptr;

			if (food.m_customize) {
				m_customize = ut.alocpy(food.m_customize);
			}
		}
		return *this;
	}

	ostream& Food::print(ostream& ostr) const {
		if (*this) {
			ostr << left << setw(28) << setfill('.') << (m_name ? m_name : "");

			if (ordered()) {
				ostr << (m_child ? "Child" : "Adult");
			}
			else {
				ostr << ".....";
			}

			ostr << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price();

			if (m_customize && &ostr == &cout) {
				ostr << " >> " << m_customize;
			}
		}
		return ostr;
	}

	bool Food::order() {
		Menu foodMenu("Food Size Selection", "Back", 3);
		foodMenu << "Adult" << "Child";

		int userInput = foodMenu.select();

		delete[] m_customize;
		m_customize = nullptr;

		switch (userInput) {
		case 1:
			m_ordered = true;
			m_child = false;
			break;
		case 2:
			m_ordered = true;
			m_child = true;
			break;
		default:
			m_ordered = false;
			return false;
		}

		char temp[100]{};
		cout << "Special instructions\n";
		cout << "> ";

		cin.getline(temp, 100);

		if (ut.strlen(temp) == 0)
		{
			delete[] m_customize;
			m_customize = nullptr;
		}
		else
		{
			ut.alocpy(m_customize, temp);
		}

		return true;
	}

	bool Food::ordered() const {
		return m_ordered;
	}

	ifstream& Food::read(ifstream& read) {
		char item_name[100];
		double item_price;

		if (read.getline(item_name, 256, ',') && read >> item_price) {
			name(item_name);
			this->Billable::price(item_price);
			m_ordered = false;
			m_child = false;
			delete[] m_customize;
			m_customize = nullptr;
			read.ignore();
			return read;
		}
		return read;
	}

	double Food::price() const {
		if (ordered() && m_child) {
			return Billable::price() / 2.0;
		}
		return Billable::price();
	}
}