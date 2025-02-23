#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H
#include "Food.h"
#include "Drink.h"
#include "Billable.h"
#include "constants.h"
#include <iostream>
namespace seneca {
   class Ordering {

       // The Counters
       size_t at_foodCounter{};
       size_t at_drinkCounter{};
       size_t at_billableCounter{};
       size_t at_serialNum{ 1 };

       // Dynamic arrays
       Food* at_foodArray{ nullptr };
       Drink* at_drinkArray{ nullptr };
       Billable* at_billItems[MaximumNumberOfBillItems];

       // Private Methods
      size_t countRecords(const char* file)const;
      void billTitlePrint(std::ostream& ostr) const;
      void printTotals(std::ostream& ostr, double totalAmount) const;

   public:

       //Constructor and Decstructor
       Ordering(const char* drinksFile, const char* foodsFile);
       ~Ordering();

       // Copy prevention assignment
       Ordering(const Ordering&) = delete;
       Ordering& operator=(const Ordering&) = delete;
       operator bool() const;

       // Queries
       size_t noOfBillItems() const;
       bool hasUnsavedBill() const;

       // Menu options that can be called
       void listFoods() const;
       void ListDrinks() const;
       void orderFood();
       void orderDrink();
       void printBill(std::ostream& ostr) const;
       void resetBill();

   };
}
#endif // !SENECA_ORDERING_H


