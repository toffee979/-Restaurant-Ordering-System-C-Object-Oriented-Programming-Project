#define _CRT_SECURE_NO_WARNINGS
#include "Drink.h"
#include "Food.h"
#include "Billable.h"
#include "Ordering.h"
#include "constants.h"
#include "Menu.h"
#include "Utils.h"
#include <cstdio>
#include <fstream>
#include <iomanip>

using namespace std;
namespace seneca {
	size_t Ordering::countRecords(const char* thefile)const {
		ifstream inFile(thefile);
		size_t count = 0;
		char character;

		while (inFile.get(character)) {
			if (character == '\n') {
				count++;
			}
		}
		return count;
	}

	void Ordering::billTitlePrint(std::ostream& ostr) const {
		ostr << "Bill # " << right << setfill('0') << setw(3)  << at_serialNum
			<< setfill(' ') << " =============================" << endl;
	}

	void Ordering::printTotals(ostream& ostr, double totalAmount) const {
		double taxAmount = totalAmount * Tax;
		double totalAfterTax = totalAmount + taxAmount;

		ostr << std::fixed << std::setprecision(2);
		ostr << std::setw(21) << std::left << "" << std::left << "Total: "
			<< std::right << std::setw(12) << totalAmount << std::endl;
		ostr << std::setw(21) << std::left << "" << std::left << "Tax: "
			<< std::right << std::setw(14) << taxAmount << std::endl;
		ostr << std::setw(21) << std::left << "" << std::left << "Total+Tax: "
			<< std::right << std::setw(8) << totalAfterTax << std::endl;
		ostr << "========================================" << std::endl;
	}

	Ordering::Ordering(const char* drinksFile, const char* foodsFile) {
		ifstream drinkData(drinksFile);
		ifstream foodData(foodsFile);

		if (drinkData && foodData) {
			at_drinkCounter = countRecords(drinksFile);
			at_foodCounter = countRecords(foodsFile);

			at_drinkArray = new Drink[at_drinkCounter];
			at_foodArray = new Food[at_foodCounter];

			size_t drinkCount = 0;
			size_t foodCount = 0;

			for (size_t i = 0; i < at_drinkCounter && drinkData; i++) {
				if (at_drinkArray[i].read(drinkData)) {
					drinkCount++;
				}
			}

			for (size_t i = 0; i < at_foodCounter && foodData; i++) {
				if (at_foodArray[i].read(foodData)) {
					foodCount++;
				}
			}

			if (drinkCount != at_drinkCounter || foodCount != at_foodCounter) {
				delete[] at_drinkArray;
				delete[] at_foodArray;
				at_drinkArray = nullptr;
				at_foodArray = nullptr;
				at_drinkCounter = at_foodCounter = 0;
			}
		}
		else {
			at_drinkArray = nullptr;
			at_foodArray = nullptr;
			at_drinkCounter = at_foodCounter = 0;
		}
	}

	Ordering::~Ordering() {
		delete[] at_drinkArray;
		delete[] at_foodArray;

		for (size_t i = 0; i < at_billableCounter; i++) {
			delete at_billItems[i];
		}
	}

	Ordering::operator bool() const {
		return at_drinkArray != nullptr && at_foodArray != nullptr;
	}

	size_t Ordering::noOfBillItems() const {
		return at_billableCounter;
	}

	bool Ordering::hasUnsavedBill() const {
		return at_billableCounter > 0;
	}

	void Ordering::listFoods() const {
		cout << "List Of Avaiable Meals" << endl
			<< "========================================" << endl;

		for (size_t i = 0; i < at_foodCounter; i++) {
			at_foodArray[i].print() << endl;
		}
		cout << "========================================" << endl;
	}

	void Ordering::ListDrinks() const {
		cout << "List Of Avaiable Drinks" << endl
			<< "========================================" << endl;

		for (size_t i = 0; i < at_drinkCounter; i++) {
			at_drinkArray[i].print() << endl;
		}
		cout << "========================================" << endl;
	}

	void Ordering::orderFood() {
		if (at_billableCounter < MaximumNumberOfBillItems) {
			Menu foodMenu("Food Menu", "Back to Order", 2);
			for (size_t i = 0; i < at_foodCounter; i++) {
				foodMenu << at_foodArray[i];
			}

			size_t selection = foodMenu.select();
			if (selection > 0 && selection <= at_foodCounter) {
				Food* foodDMA = new Food(at_foodArray[selection - 1]);
				if (foodDMA->order()) {
					at_billItems[at_billableCounter++] = foodDMA;
				}
				else {
					delete foodDMA;
				}
			}
		}
	}

	void Ordering::orderDrink() {
		if (at_billableCounter < MaximumNumberOfBillItems) {
			Menu drinkMenu("Drink Menu", "Back to Order", 2);
			for (size_t i = 0; i < at_drinkCounter; i++) {
				drinkMenu << at_drinkArray[i];
			}

			size_t selection = drinkMenu.select();
			if (selection > 0 && selection <= at_drinkCounter) {
				Drink* drinkDMA = new Drink(at_drinkArray[selection - 1]);
				if (drinkDMA->order()) {
					at_billItems[at_billableCounter++] = drinkDMA;
				}
				else {
					delete drinkDMA;
				}
			}
		}
	}

	void Ordering::printBill(ostream& ostr) const {
		double totalAmount = 0.0;
		billTitlePrint(ostr);

		for (size_t i = 0; i < at_billableCounter; i++) {
			at_billItems[i]->print(ostr) << endl;
			totalAmount += at_billItems[i]->price();
		}

		printTotals(ostr, totalAmount);
	}

	void Ordering::resetBill() {
		char fileName[100];
		ut.makeBillFileName(fileName, at_serialNum);

		ofstream billFile(fileName);
		printBill(billFile);

		cout << "Saved bill number " << at_serialNum << endl;
		cout << "Starting bill number " << at_serialNum + 1 << endl;

		for (size_t i = 0; i < at_billableCounter; i++) {
			delete at_billItems[i];
			at_billItems[i] = nullptr;
		}

		at_billableCounter = 0;
		at_serialNum++;
	}

}