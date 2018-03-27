/****************************************************************************
  FileName     [ p2Table.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define member functions of class Row and Table ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2016-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#include "p2Table.h"

using namespace std;

// Implement member functions of class Row and Table here

bool Table::read(const string& csvFile)
{
     ifstream input(csvFile.c_str());
     vector<string> temptab;
     temptab.clear();
     int _nRows =0;
   while(!input.eof()) 
    {
        string line;
        getline(input, line); 
        temptab.push_back(line);
        _nRows++;
    }
     
     input.close(); 
      
       size_t size = 1;
   for(int i = 0 ; i < temptab.at(0).size() ; i++)
     {
          if(temptab.at(0)[i]==',')
             size++;
          else
             continue;
     }
       _nCols = size;
       if(temptab.at(_nRows-1).size() == 0)
             temptab.pop_back();
   
  if(_nCols == 1)
   {
     for (int k =0 ; k < temptab.size() ; k++ )
     { 
	int b = 0;
        int ent = 13;
        char enting = (char)ent;
	//char* pch = strtok((char*) temptab.at(k).c_str() ,enting);
	Row row(1);
        int pos = temptab.at(k).size() - 1;
      if(temptab.at(k).size() != 0)
      {       
        if((int)temptab.at(k)[0]!=32 || (int)temptab.at(k)[0] != 13)
          {
            b = atoi(temptab.at(k).c_str());
            row[0] =b;
          }
       else
          {    
            row[0] = INT_MAX;
          }
      }
      else
      {
      /*
         if((int)temptab.at(k)[0]!=32 || (int)temptab.at(k)[0] != 13)
          {
          
            b = atoi(temptab.at(k).c_str());
            row[0] =b;
          }
       else
          {    
            row[0] = INT_MAX;
          }
*/     
            row[0] = INT_MAX;
    }
        _rows.push_back(row);
 
      

      
    }
     
   

     return true;

   }



  else
  {
   int commun = 0;//mid  
   for(int j = 0 ; j < temptab.size();j++)
    {

      for(int i = 0 ; i < temptab.at(j).size() ; i++)
        {

           if(temptab.at(j)[i] !=',')
              commun = 0;

          else if(temptab.at(j)[i]==',' && commun == 0)
             commun = 1;

          else if(temptab.at(j)[i]==',' && commun == 1)
            {
                 temptab.at(j).insert((size_t)i," ");
                 commun = 0;
            }
         }
     }

   for(int j = 0 ; j < temptab.size();j++)//head
      {
         size_t found = temptab.at(j).find(",");
         if(found == 0)
            temptab.at(j).insert(0," ");
         else
            continue;
      }

    for(int j = 0 ; j < temptab.size();j++) //tail
      {
          int a = temptab.at(j).size();
           if(j != temptab.size()-1 && temptab.at(j)[a-1] ==  char(13))
             {
                
                if(temptab.at(j)[a-2] == ',')
                     temptab.at(j).insert((size_t)a-1," ");
                else
                  continue;
             }
           
            else
             {
                 
                if(temptab.at(j)[a-1] == ',')
                    temptab.at(j).insert((size_t)a," ");
                else
                  continue;
             }
      }

  //    if(temptab.at(_nRows-1).size() == 0)
    //         temptab.pop_back();


     _rows.clear();

   for (int k =0 ; k < temptab.size() ; k++ )
   {
    int b = 0;
    char* pch = strtok((char*) temptab.at(k).c_str() , ",");
     Row row(_nCols);
     
       if((int)pch[0]!=32)
       {
            b = atoi((const char*)pch);
          row[0] =b;
       }
       else
       {
            b = atoi((const char*)pch);
           row[0] = INT_MAX;
       }

    for(int i = 1 ; i < _nCols ; i++)
         {

             pch = strtok(NULL,",");

             if(i != _nCols-1)
             b = atoi((const char*)pch);

       if((int)pch[0] != 32)
       {
            b = atoi((const char*)pch);
           row[i] =b;
       }
       else
       {
            b = atoi((const char*)pch);
           row[i] = INT_MAX;
       }

         }

          _rows.push_back(row);
          
   }
   
      return true; 
  }
                    

// TODO
}

Row::Row(size_t s)
{
    _data = new int[s];
}


Table::Table()
{
    _rows.clear();
}

Table::Table(vector<Row> rows)
{
    _rows = rows;
}

void Table::AddRows(Row a)
{
   
   _rows.push_back(a);

}

void Table::print()
{

   for(int i = 0 ; i < _rows.size() ; i++)
    {
        cout << setw(4) << right;
         for(int j = 0 ; j < _nCols ; j++)
            {
              if( _rows[i][j] != INT_MAX)
              cout << _rows[i][j] << setw(4) << right;
        
              else
               cout << '.' << setw(4) << right;
            }
          cout << endl << right;
    }

}

void Table::sum(int Num_of_Col)
{
     int sum = 0;
     for(int i = 0 ; i < _rows.size() ; i++)
         {
           if( _rows[i][Num_of_Col] != INT_MAX)
            sum += _rows[i][Num_of_Col];
           else
            sum += 0;
         }
     cout << "The summation of data in column #" << Num_of_Col << " is " << sum << "." << endl; 

} 

void Table::max(int Num_of_Col)
{

   int max = 0;
    for(int i = 0 ; i < _rows.size() ; i++)
         {
             if(_rows[i][Num_of_Col] == INT_MAX)
               continue;
             
             if(max < _rows[i][Num_of_Col])
                   max = _rows[i][Num_of_Col];
          }
     cout << "The maximum of data in column #" << Num_of_Col << " is " << max << "." << endl; 
}

void Table::min(int Num_of_Col)
{

   int min = 32;
    for(int i = 0 ; i < _rows.size() ; i++)
         {
             if(_rows[i][Num_of_Col] == INT_MAX)
               continue;

              if(min > _rows[i][Num_of_Col])
                   min = _rows[i][Num_of_Col];
          }
     cout << "The minimum of data in column #" << Num_of_Col << " is " << min << "." << endl; 
}
void Table::dist(int Num_of_Col)
{
      int unique = 1;
      vector<int> vec;
      for(int i = 0 ; i < _rows.size() ; i++)
         {
           if(_rows[i][Num_of_Col] != INT_MAX)
            vec.push_back(_rows[i][Num_of_Col]);
         }
        
     sort(vec.begin(),vec.end());
     for(int i = 0; i <vec.size() -1 ; i++)
      {
         if(vec.at(i)==vec.at(i+1))
           continue;
        else
          unique++;
     }

     cout << "The distinct count of data in column #" << Num_of_Col << " is " << unique << "." << endl; 
}

void Table::ave(int Num_of_Col)
{
     float sum = 0;
     int avesize = 0;
     for(int i = 0 ; i < _rows.size() ; i++)
         {
           if( _rows[i][Num_of_Col] != INT_MAX)
            {
              sum += _rows[i][Num_of_Col];
              avesize++;
            }
           else
            sum += 0;
         }
      float ave = sum/avesize ;
     cout << "The summation of data in column #" << Num_of_Col << " is " << fixed << setprecision(1) << ave << "." << endl; 

} 

void Table::add()
{
 
   Row row(_nCols);
   
   string x;
   cin.ignore();
   getline(cin,x);
 
  int b = 0;
   char* pch = strtok((char*) x.c_str() , " "); 
  
       if((int)pch[0]!=46)
       {
            b = atoi((const char*)pch);
          row[0] =b;
       }
       else
       {
           b = atoi((const char*)pch);
           row[0] = INT_MAX;
       }
   int i = 1;
    while(pch != NULL)
         {

             pch = strtok(NULL," ");

             if(pch == NULL)
            	 break;
          
               b = atoi((const char*)pch);
       if((int)pch[0] != 46)
       {
            b = atoi((const char*)pch);
           row[i] =b;
       }
       else
       {
            b = atoi((const char*)pch);
           row[i] = INT_MAX;
       }
              i++;
         }
  _rows.push_back(row);
 
}

