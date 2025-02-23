/***********************************************************************
// OOP244 Project, milestone 56 : tester program
//
// File	ms56.cpp
// Version 1.0
// Date 2024-11-28
// Author Fardad
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************
#include <iostream>
#include "Menu.h"
#include "Ordering.h"
using namespace std;
using namespace seneca;
int main() {
   cout << "Testing Invalid Ordering if bad data is in data file!" << endl;
   Ordering badord("drinks.csv", "badfoods.csv");
   if (badord) {
      cout << "The ordering should have been invalid" << endl;
   }
   else {
      cout << "Passed!" << endl;
   }
   Ordering ord("drinks.csv", "foods.csv");
   cout << "Testing fool proofint..............................." << endl;
   ord.orderDrink();
   return 0;
}
*/