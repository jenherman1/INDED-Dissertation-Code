#pragma once

#include "CONST.H"

class predicate_symbol_class 
   {
  public:
      predicate_symbol_class();
      predicate_symbol_class(int num);
      predicate_symbol_class(char instr[STRING_LENGTH]);
 

      void output();
      void clear();

      void assign_next(predicate_symbol_class *pr_ptr);
      void assign_symbol(char instr[STRING_LENGTH]);

      int get_value();
      predicate_symbol_class *get_next_ptr();
      char *get_predicate_symbol();
      void  display();

  protected:
      int                             val;
      predicate_symbol_class         *pnextnode;
      char                            predicate_symbol[STRING_LENGTH];
};
