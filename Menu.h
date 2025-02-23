#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>
#include <ostream>
#include "constants.h"
namespace seneca {
	class Menu;
	class MenuItem {
		friend class Menu;
		char* m_content;
		int m_row;
		int m_column;
		int m_number;

	public:

		//Normal Constructor
		MenuItem(const char* content = nullptr, int row = 0, int column = 0, int number = 0);

		// Rule of Three
		MenuItem(const MenuItem&) = delete;
		MenuItem& operator=(const MenuItem&) = delete;
		~MenuItem();

		operator bool() const;
		std::ostream& display(std::ostream& ostr = std::cout) const;

	};
	class Menu {
		MenuItem* m_menuItems[MaximumNumberOfMenuItems];
		size_t m_numberOfItems;
		MenuItem m_title;
		MenuItem m_exitContent;
		MenuItem m_selectionOption;
		int m_indent;
		int m_indentSize;

	public:
		Menu(const char* title, const char* exitContent = "Exit", int indent = 0, int indentSize = 3);
		~Menu();

		Menu& operator<<(const char* itemContent);
		size_t select() const;

		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;

	};
	size_t operator<<(std::ostream& ostr, const Menu& menu);

}
#endif // !SENECA_MENU_H


