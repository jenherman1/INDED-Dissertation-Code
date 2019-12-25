#pragma once

#include <fstream>

#include "CONST.H"

class fullstring_class 
   {
  public:
      fullstring_class();
      fullstring_class(int num);
      fullstring_class(const char instr[LONG_STRING_LENGTH]);

      void output();
      void clear();

      void assign_next(fullstring_class *f_ptr);
      void assign_symbol(const char instr[LONG_STRING_LENGTH]);
      void assign_IS_NEGATIVE(int neg_val);

      int               get_value();
      int               get_IS_NEGATIVE();
      fullstring_class *get_next_ptr();
      char             *get_fullstring_symbol();

      void  display();
      void  display(std::ostream& fout);


  protected:
      int                             val;
      int                             IS_NEGATIVE;
      fullstring_class                 *fnextnode;
      char                            fullstring_symbol[LONG_STRING_LENGTH];
};
