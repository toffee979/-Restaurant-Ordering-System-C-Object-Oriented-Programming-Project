// Name: Imtihal Uddin
// Student Number: 178833232

#include <iostream>
#include "Menu.h"
#include "Ordering.h"
using namespace std;
using namespace seneca;

int main() {
	//Loading up the drinks and foods file
	Ordering order("drinks.csv", "foods.csv");

	//Starting off with creating the menu
	Menu mainMenu("Seneca Restaurant ", "End Program");
	mainMenu << "Order"
		<< "Print Bill"
		<< "Start a New Bill"
		<< "List Foods"
		<< "List Drinks";

	//Order	sub menu
	Menu orderMenu("Order Menu", "Back to main menu", 1);
	orderMenu << "Food" << "Drink";

	//unsavedBill menu
	Menu unsavedBillMenu("You have bills that are not saved, are you sue you want to exit?", "No");
	unsavedBillMenu << "Yes";


	bool complete = false;
	while (!complete) {
		switch (mainMenu.select()) {
		case 1:
		{
			bool orderComplete = false;
			while (!orderComplete) {
				switch (orderMenu.select()) {
				case 1: 
					order.orderFood();
					break;
				case 2: 
					order.orderDrink();
					break;
				case 0:
					orderComplete = true;
					break;
				}
			}
		}
		break;
		case 2:
			order.printBill(cout);
			break;
		case 3:
			order.resetBill();
			break;
		case 4:
			order.listFoods();
			break;
		case 5:
			order.ListDrinks();
			break;
		case 0:
			if (order.hasUnsavedBill()) {
				if (unsavedBillMenu.select() == 1) {
					complete = true;
				}
			}
			else {
				complete = true;
			}
			break;
			}
		}
	return 0;
}