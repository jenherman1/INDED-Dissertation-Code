#pragma once

#include "CONCLASS.H"
#include "CONST.H"

class variable_class 
   {
  public:
      variable_class();
      variable_class(int num);
      variable_class(char instr[STRING_LENGTH]);

      void output();
      void clear();

      void assign_next(variable_class *var_ptr);
      void assign_symbol(char instr[STRING_LENGTH]);
      void assign_instantiated_constant_ptr(constant_class *c_ptr);

      int               get_value();
      variable_class   *get_next_ptr();
      char             *get_variable_symbol();
      constant_class   *get_instantiated_constant_ptr();

      void  display();
      int   advance_instantiated_constant_ptr(constant_class *first_cons_ptr);

  protected:
      int                             val;
      variable_class                 *varnextnode;
      constant_class                 *instantiated_constant_ptr;
      char                            variable_symbol[STRING_LENGTH];
};
