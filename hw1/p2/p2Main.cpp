/****************************************************************************
  FileName     [ p2Main.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define main() function ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2016-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <string>
#include "p2Table.h"

using namespace std;

int main()
{
   Table table;

   // Read in the csv file. Do NOT change this part of code.
   string csvFile;
   cout << "Please enter the file name: ";
   cin >> csvFile;
   if (table.read(csvFile))
      cout << "File \"" << csvFile << "\" was read in successfully." << endl;
   else {
      cerr << "Failed to read in file \"" << csvFile << "\"!" << endl;
      exit(-1); // csvFile does not exist.
   }
     
      
      
   // TODO read and execute commands
   while (true) {
    				
      string comm;
      int Num_of_Cols;
      cin >> comm ;
      if(comm == "SUM" || comm == "AVE"|| comm == "MAX" || comm == "MIN" || comm == "DIST")
	{
           cin >>Num_of_Cols;         																											   if(comm == "SUM")
              table.sum(Num_of_Cols);
           else if(comm == "AVE")
              table.ave(Num_of_Cols);
           else if(comm == "MAX")
              table.max(Num_of_Cols);
           else if(comm == "MIN")
              table.min(Num_of_Cols);
           else if(comm == "DIST")
              table.dist(Num_of_Cols);
      
        }
      else if(comm == "ADD")
         table.add();
      else if(comm == "PRINT")
         table.print();
      else if(comm == "EXIT")
        break;
}
     return 0;
}

