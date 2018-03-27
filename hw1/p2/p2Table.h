/****************************************************************************
  FileName     [ p2Table.h]
  PackageName  [ p2 ]
  Synopsis     [ Header file for class Row and Table ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2016-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#ifndef P2_TABLE_H
#define P2_TABLE_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <algorithm> 
#include <climits>
using namespace std;

class Row
{
public:
   // TODO: define constructor and member functions on your own
    Row() {};
    Row(size_t);
   // void setRow(int* _data);		
 
    
      
     
    
   // Basic access functions
   const int operator[] (size_t i) const { return _data[i]; }
   int& operator[] (size_t i) { return _data[i]; }

private:
   int    *_data; // DO NOT change this definition. Use it to store data.
};

class Table
{
public:
   // TODO: define constructor and member functions on your own
   Table();
   Table(vector<Row>);
   
   void AddRows(Row);
   //int getRowSize();

   bool read(const string&);
   void print();
   void sum(int);
   void max(int);
   void min(int);
   void dist(int);
   void ave(int);
   void add();
   // Basic access functions
   size_t nCols() const { return _nCols; }
   const Row& operator[] (size_t i) const { return _rows[i]; }
   Row& operator[] (size_t i) { return _rows[i]; }

private:
   size_t       _nCols; // You should record the number of columns.
   vector<Row>  _rows;  // DO NOT change this definition. Use it to store rows.
};

#endif // P2_TABLE_H
