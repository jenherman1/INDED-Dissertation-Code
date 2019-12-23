#include <iostream>

#include "PREDSYM.H"

using namespace std;

//_________________________________________________________________________
predicate_symbol_class::predicate_symbol_class()
{
   val = 0;
   pnextnode = nullptr;
   strcpy(predicate_symbol,"");
  }

//_________________________________________________________________________
predicate_symbol_class::predicate_symbol_class(int num)
{
   val = num;
   pnextnode = nullptr;
   strcpy(predicate_symbol,"");
  }

//_________________________________________________________________________

predicate_symbol_class::predicate_symbol_class(char instr[STRING_LENGTH]) 
{
   val = 0;
   pnextnode = nullptr;
   strcpy(predicate_symbol,instr);
}

//_________________________________________________________________________

void predicate_symbol_class::output()
  {
     cout << "^_^_^_^_^_^_^_^_^_^^^_^_^_^_^_^_^_^_^_^_\n";
     cout << "Predicate symbol is " << predicate_symbol << endl;
     cout << "The pointer to Next Constant (pnextnode) is: " << pnextnode << endl;
     cout << "^_^_^_^_^_^_^_^_^_^^^_^_^_^_^_^_^_^_^_^_\n";


  } 
//_________________________________________________________________________

void predicate_symbol_class::clear()
  {
   pnextnode = nullptr;
   strcpy(predicate_symbol,"");
  }
//_________________________________________________________________________


void predicate_symbol_class::assign_next(predicate_symbol_class *pr_ptr)
  {
     pnextnode = pr_ptr;
  }
//_________________________________________________________________________


void predicate_symbol_class::assign_symbol(char instr[STRING_LENGTH])
  {
     strcpy(predicate_symbol, instr);
  }
//_________________________________________________________________________

predicate_symbol_class  *predicate_symbol_class::get_next_ptr()
  {
      return pnextnode; 
  }
//_________________________________________________________________________

int predicate_symbol_class::get_value()
  {
      return 0;
  }
//_________________________________________________________________________


char *predicate_symbol_class::get_predicate_symbol()
  {
      return predicate_symbol;
  }
//_________________________________________________________________________

void predicate_symbol_class::display()
  {
     cout << predicate_symbol;
  }
//_________________________________________________________________________
