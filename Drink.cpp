#include "Drink.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Menu.h"

using namespace std;
namespace seneca {
	Drink::Drink() : Billable(), m_size('\0') {}

	ostream& Drink::print(ostream& ostr) const {
		char buffer[26] = {};
		const char* name = *this;
		if (name)
			ut.strcpy(buffer, name);
		buffer[25] = '\0';

		ostr << left << setw(28) << setfill('.') << (m_name ? m_name : "");

		if (ordered())
		{
			if (m_size == 'S')
			{
				ostr << "SML..";
			}
			else if (m_size == 'M')
			{
				ostr << "MID..";
			}
			else if (m_size == 'L')
			{
				ostr << "LRG..";
			}
			else if (m_size == 'X')
			{
				ostr << "XLR..";
			}
		}
		else
		{
			ostr << ".....";
		}

		ostr.width(7);
		ostr.fill(' ');
		ostr.precision(2);
		ostr.setf(ios::fixed);
		ostr.setf(ios::right);
		ostr << price();
		ostr.unsetf(ios::right);

		return ostr;
	}

	bool Drink::order() {
		Menu drinkMenu("Drink Size Selection", "Back", 3);
		drinkMenu << "Small" << "Medium" << "Larg" << "Extra Large";

		int userInput = drinkMenu.select();

		switch (userInput)
		{
		case 1:
			m_size = 'S';
			return true;
		case 2:
			m_size = 'M';
			return true;
		case 3:
			m_size = 'L';
			return true;
		case 4:
			m_size = 'X';
			return true;
		case 0:
			m_size = '\0';
			return false;
		default:
			return false;

		}
	}

	bool Drink::ordered() const {
		return m_size != '\0';
	}

	std::ifstream& Drink::read(std::ifstream& read) {
		char item_name[100]{};
		double item_price;

		read.getline(item_name, 100, ',');
		read >> item_price;
		read.ignore();

		if (read)
		{
			name(item_name);

			Billable::price(item_price);
			m_size = '\0';
		}

		return read;
	}

	double Drink::price() const {
		double tempPrice = Billable::price();

		if (m_size == 'S')
		{
			tempPrice *= 0.5;
		}
		else if (m_size == 'M')
		{
			tempPrice *= 0.75;
		}
		else if (m_size == 'X')
		{
			tempPrice *= 1.5;
		}
		return tempPrice;
	}

}