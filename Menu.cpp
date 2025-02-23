#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Menu.h"
#include  "Utils.h"
#include "constants.h"
using namespace std;
namespace seneca {
	MenuItem::MenuItem(const char* content, int row, int column, int number) {
		m_content = nullptr;
		m_row = row;
		m_column = column;
		m_number = number;
		if (content && !ut.isspace(content)) {
			m_content = ut.alocpy(content);
		}
	}


	MenuItem::~MenuItem() {
		delete[] m_content;
	}

	std::ostream& MenuItem::display(std::ostream& ostr) const {
		if (*this) {
			for (int i = 0; i < (m_row * m_column); ++i)
			{
				ostr << ' ';
			}

			//Output with the proper indentation
			if (m_number >= 0) {
				ostr << std::setw(2) << right << m_number << "- ";
			}

			const char* contentDisplayed = m_content;
			while (ut.isspace(*contentDisplayed)) {
				++contentDisplayed;
			}
			ostr << contentDisplayed;
		}
		else {
			ostr << "??????????";
		}
		return ostr;
	}

	MenuItem::operator bool() const {
		return m_content != nullptr && m_row <= 4 && m_column <= 4 && (m_number >= -1 && m_number <= static_cast<int>(MaximumNumberOfMenuItems));
	}

	//Constructor
	Menu::Menu(const char* title, const char* exitContent, int indent, int indentSize)
		: m_numberOfItems(0),
		m_title(title, indent, indentSize, -1),
		m_exitContent(exitContent, indent, indentSize, 0),
		m_selectionOption("> ", indent, indentSize, -1),
		m_indent(indent),
		m_indentSize(indentSize) {


		for (size_t i = 0; i < MaximumNumberOfMenuItems; i++) {
			m_menuItems[i] = nullptr;
		}
	}

	//Destructor
	Menu::~Menu() {
		for (size_t i = 0; i < m_numberOfItems; ++i) {
			delete m_menuItems[i];
			m_menuItems[i] = nullptr;
		}
	}

	// Overloaded << operator 
	Menu& Menu::operator<<(const char* itemContent) {
		if (m_numberOfItems < MaximumNumberOfMenuItems && itemContent && !ut.isspace(itemContent)) {
			m_menuItems[m_numberOfItems] = new MenuItem(itemContent, m_indent, m_indentSize, m_numberOfItems + 1);
			m_numberOfItems++;
		}
		return *this;
	}

	//Displaying and selecting from the menu

	size_t Menu::select() const {
		if (m_title) {
			m_title.display(cout) << endl;
		}

		for (size_t i = 0; i < m_numberOfItems; i++) {
			if (m_menuItems[i]) {
				m_menuItems[i]->display(cout) << endl;
			}
		}

		m_exitContent.display(cout) << endl;

		m_selectionOption.display(cout);
		return ut.getInt(0, static_cast<int>(m_numberOfItems));
	}

	size_t operator<<(ostream& ostr, const Menu& menu) {
		if (&ostr == &cout) {
			return menu.select();
		}
		return 0;
	}
}