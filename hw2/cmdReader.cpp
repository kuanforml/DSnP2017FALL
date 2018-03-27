/****************************************************************************
  FileName     [ cmdReader.cpp ]
  PackageName  [ cmd ]
  Synopsis     [ Define command line reader member functions ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2007-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#include <cassert>
#include <cstring>
#include "cmdParser.h"

using namespace std;

//----------------------------------------------------------------------
//    Extrenal funcitons
//----------------------------------------------------------------------
void mybeep();
char mygetc(istream&);
ParseChar getChar(istream&);

 
//----------------------------------------------------------------------
//    Member Function for class Parser
//----------------------------------------------------------------------
void
CmdParser::readCmd()
{
   if (_dofile.is_open()) {
      readCmdInt(_dofile);
      _dofile.close();
   }
   else
      readCmdInt(cin);
}

void
CmdParser::readCmdInt(istream& istr)
{
   resetBufAndPrintPrompt();

   while (1) {
      ParseChar pch = getChar(istr);
      if (pch == INPUT_END_KEY) break;
      switch (pch) {
         case LINE_BEGIN_KEY :
         case HOME_KEY       :{  
				char* temp = _readBufPtr; 
				for(int i = 0 ; i < temp - _readBuf ; i++)
			        moveBufPtr(_readBufPtr-1);
    			        break;
                              }
         case LINE_END_KEY   :
         case END_KEY        :{
				 char* temp = _readBufPtr;
                                 for(int i = 0 ; i < _readBufEnd - temp ; i++)
  				 moveBufPtr(_readBufPtr+1);
				 break;
			      }
         case BACK_SPACE_KEY : /* TODO */
				{ 
				if(_readBufPtr != _readBuf){
				moveBufPtr(_readBufPtr-1);
				deleteChar();}
				 break;
				}
         case DELETE_KEY     : deleteChar(); break;
         case NEWLINE_KEY    :
                               addHistory();
                               cout << char(NEWLINE_KEY);
                               resetBufAndPrintPrompt(); break;
         case ARROW_UP_KEY   : moveToHistory(_historyIdx - 1); break;
         case ARROW_DOWN_KEY : moveToHistory(_historyIdx + 1); break;
         case ARROW_RIGHT_KEY: /* TODO */ 
                               moveBufPtr(_readBufPtr+1);      break;
         case ARROW_LEFT_KEY : /* TODO */ 
    			       moveBufPtr(_readBufPtr-1); break;
         case PG_UP_KEY      : moveToHistory(_historyIdx - PG_OFFSET); break;
         case PG_DOWN_KEY    : moveToHistory(_historyIdx + PG_OFFSET); break;
         case TAB_KEY        : {
                                 insertChar(' ',8-((_readBufPtr-_readBuf)%8));  

                               /* TODO */ break;
                               }
         case INSERT_KEY     : // not yet supported; fall through to UNDEFINE
         case UNDEFINED_KEY:   mybeep(); break;
         default:  // printable character
            insertChar(char(pch)); break;
      }
      #ifdef TA_KB_SETTING
      taTestOnly();
      #endif
   }
}


// This function moves _readBufPtr to the "ptr" pointer
// It is used by left/right arrowkeys, home/end, etc.
//
// Suggested steps:
// 1. Make sure ptr is within [_readBuf, _readBufEnd].
//    If not, make a beep sound and return false. (DON'T MOVE)
// 2. Move the cursor to the left or right, depending on ptr
// 3. Update _readBufPtr accordingly. The content of the _readBuf[] will
//    not be changed
//
// [Note] This function can also be called by other member functions below
//        to move the _readBufPtr to proper position.
bool
CmdParser::moveBufPtr(char* const ptr)
{
   // TODO...

   if(ptr <_readBuf || ptr > _readBufEnd)
    {
 	 mybeep();
	 return false;
    }
   else
    {
        // _readBufPtr = ptr;
         if(ptr - _readBufPtr < 0)
           {       
               cout << char(8);
               _readBufPtr = ptr;
           }	
         else
           {
	    
               _readBufPtr = ptr;
               cout << *(_readBufPtr-1);
	   }
            
         return true;
    }
}


// [Notes]
// 1. Delete the char at _readBufPtr
// 2. mybeep() and return false if at _readBufEnd
// 3. Move the remaining string left for one character
// 4. The cursor should stay at the same position
// 5. Remember to update _readBufEnd accordingly.
// 6. Don't leave the tailing character.
// 7. Call "moveBufPtr(...)" if needed.
//
// For example,
//
// cmd> This is the command
//              ^                (^ is the cursor position)
//
// After calling deleteChar()---
//
// cmd> This is he command
//              ^
//
bool
CmdParser::deleteChar()
{
   // TODO...
   if(_readBufPtr == _readBufEnd)
	{
	    mybeep();	
	    return false;	
	} 
   else
	{ 
	 //   moveBufPtr(_readBufPtr-1);
            for(int i = 0 ; i < _readBufEnd - _readBufPtr-1 ; i++)
                 *(_readBufPtr+i) = *(_readBufPtr+1+i);
           
            _readBufEnd--;
	    * _readBufEnd = 0;
              
           string str(_readBuf);
           
           int times = _readBufEnd - _readBufPtr; 
           char* temp  = _readBufPtr;
         for(int i = 0 ; i < times ; i++)
         { moveBufPtr(_readBufPtr+1);}
           cout << " ";            
         for(int i = 0 ; i < times ; i++)
          moveBufPtr(_readBufPtr-1);
         
        // moveBufPtr(_readBuf);
        // moveBufPtr(temp);
        cout << char(8);
         //cout << str;
         
          // moveBufPtr(temp);
          // cout << endl; 
         // cout << str;
           return true;
	}	
}

// 1. Insert character 'ch' for "repeat" times at _readBufPtr
// 2. Move the remaining string right for "repeat" characters
// 3. The cursor should move right for "repeats" positions afterwards
// 4. Default value for "repeat" is 1. You should assert that (repeat >= 1).
//
// For example,
//
// cmd> This is the command
//              ^                (^ is the cursor position)
//
// After calling insertChar('k', 3) ---
//
// cmd> This is kkkthe command
//                 ^
//
void
CmdParser::insertChar(char ch, int repeat)
{
   // TODO...
   
  //assert(repeat >= 1);
	
   if(_readBufEnd != _readBufPtr)
  {
   char* pos = _readBufEnd;
    _readBufEnd += repeat;
   
    for(int i = 0 ; i <= pos - 1 - _readBufPtr   ; i++)
	{
	  *(pos-1-i+repeat) = *(pos-1-i);     
	}
    for(int i = 0 ; i < repeat ; i++)
	{
          *(_readBufPtr+i) = ch;
	}
    for (int i = 0 ; i < repeat ; i++)
      cout << ch;
 
    _readBufPtr += repeat;
    for(int i = 0 ; i < _readBufEnd - _readBufPtr ; i++)
       cout  <<*(_readBufPtr+i) ;
    for(int i = 0 ; i < _readBufEnd - _readBufPtr ; i++)
       cout << char(8);
 
  /*  cout << endl ;
    string str(_readBuf);
    cout << str;*/
  }
  else
   {
      _readBufEnd += repeat;
     
      for(int i = 0 ; i < repeat ; i++)
      {
          *(_readBufPtr+i) = ch;
          cout << ch;
            
      }
     _readBufPtr += repeat;
     
   }

}

// 1. Delete the line that is currently shown on the screen
// 2. Reset _readBufPtr and _readBufEnd to _readBuf
// 3. Make sure *_readBufEnd = 0
//
// For example,
//
// cmd> This is the command
//              ^                (^ is the cursor position)
//
// After calling deleteLine() ---
//
// cmd>
//      ^
//1
void
CmdParser::deleteLine()
{
   // TODO...
   char* temp = _readBufPtr; 
   char* tempend = _readBufEnd;
   moveBufPtr( _readBuf);
  
   while(_readBufEnd != _readBuf)
   {  
       deleteChar();
   }
   
   for(int i = 0 ; i < temp - _readBuf-1 ; i++)
     cout << char(8)  ;  

   //moveBufPtr( _readBufEnd);
  
     string a(_readBuf);
     cout << a;
   /* cout << endl;
    string a(_readBuf);
    cout << a<<endl;
    cout << 24;*/
    insertChar(' ',tempend - _readBuf -1);
    for(int i = 0 ; i < tempend - _readBuf -1 ; i++)
        cout << char(8);
  
    _readBufEnd = _readBuf;
    *_readBufEnd = 0;
  
}


// This functions moves _historyIdx to index and display _history[index]
// on the screen.
//
// Need to consider:
// If moving up... (i.e. index < _historyIdx)
// 1. If already at top (i.e. _historyIdx == 0), beep and do nothing.
// 2. If at bottom, temporarily record _readBuf to history.
//    (Do not remove spaces, and set _tempCmdStored to "true")
// 3. If index < 0, let index = 0.
//
// If moving down... (i.e. index > _historyIdx)
// 1. If already at bottom, beep and do nothing
// 2. If index >= _history.size(), let index = _history.size() - 1.
//
// Assign _historyIdx to index at the end.
//
// [Note] index should not = _historyIdx
//
void
CmdParser::moveToHistory(int index)
{
   // TODO...
    if(index < _historyIdx)
	{    

	   if(_historyIdx == 0)
                {
		  mybeep();
                  return;	
		}
           if(_historyIdx == _history.size())
                {
                  _tempCmdStored = true;
		  addHistory();
                
            //      _historyIdx = index;
		}
           if(index < 0)
              { index = 0; mybeep(); }
	}

    else
	{
	    if(_historyIdx == _history.size())
		{
		  mybeep();
       return;
		}
            if(index >= _history.size()-1 && _tempCmdStored == true)
                {
		  index = _history.size()-1;
		  _historyIdx = index;
		  retrieveHistory();
		  _history.pop_back();
		  _tempCmdStored = false; 
		 return;
		}
      
	}
       _historyIdx = index;
       retrieveHistory();
     
}


// This function adds the string in _readBuf to the _history.
// The size of _history may or may not change. Depending on whether 
// there is a temp history string.
//
// 1. Remove ' ' at the beginning and end of _readBuf
// 2. If not a null string, add string to _history.
//    Be sure you are adding to the right entry of _history.
// 3. If it is a null string, don't add anything to _history.
// 4. Make sure to clean up "temp recorded string" (added earlier by up/pgUp,
//    and reset _tempCmdStored to false
// 5. Reset _historyIdx to _history.size() // for future insertion
//
void
CmdParser::addHistory()
{
   // TODO...
    if(_tempCmdStored)
	{
            if(_historyIdx == _history.size())
		{
		    string tmp1(_readBuf);
                    string tmp;
                    tmp.append(tmp1,0,_readBufEnd - _readBuf);
                    _history.push_back(tmp);
                 //  _historyIdx = _history.size();
		}
	    else
		{
		   string add2(_readBuf);
		   _history.pop_back();
	           int count = 0;
		   string add;
                   add.append(add2,0,_readBufEnd - _readBuf);	   
                    while(add[count] == ' ')
          	      {
            		  count++;
             		  if(count == add.size())
                	  break;
	              } 
  	 	     if(count == add.size()) // all spaces
                        {
			   deleteLine();
		           _historyIdx = _history.size();
			   return;
			}
                     else if(count != 0)// remove spaces at the beginning
                     add.erase(0,count);
       
         	      int count2 = 0;//reomve spaces at the end	 
	              while(add[add.size()-1-count2] == ' ')
            		 {
			 	count2++;	
	     		 }
       		     add.erase((add.size()-count2),count2);
	 	     _readBufEnd = _readBuf;
		     _history.push_back(add);
                     _historyIdx = _history.size();
                  
		}     
	}
    else
	{  
	string str2(_readBuf);
        string str;
        str.append(str2,0,_readBufEnd - _readBuf);
        	
            

    	 int count = 0;
         while(str[count] == ' ')
           {
              count++;
              if(count == str.size())
                 break;
	   } 
  	  if(count == str.size()) // all spaces
             {return;}
          else if(count != 0)// remove spaces at the beginning
             str.erase(0,count);
       
          int count2 = 0;//reomve spaces at the end	 
          while(str[str.size()-1-count2] == ' ')
             {
	 	count2++;	
	     }
          str.erase((str.size()-count2),count2);
         _readBufEnd = _readBuf;
         *_readBuf = 0;
 	 _history.push_back(str);
         str.clear();
         _historyIdx = _history.size();
	
	}

}


// 1. Replace current line with _history[_historyIdx] on the screen
// 2. Set _readBufPtr and _readBufEnd to end of line
//
// [Note] Do not change _history.size().
//
void
CmdParser::retrieveHistory()
{
   deleteLine();
   strcpy(_readBuf, _history[_historyIdx].c_str());
   cout << _readBuf;
   _readBufPtr = _readBufEnd = _readBuf + _history[_historyIdx].size();
}
