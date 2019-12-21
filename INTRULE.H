#pragma once

#include <fstream>

#include "CONST.H"
#include "LIST.CC"
#include "PREDEXP.H"
#include "VARIABLE.H"

class intensional_rule_class
  {
  public:
      intensional_rule_class();
      intensional_rule_class(int n);
      intensional_rule_class(char f_str[EXTRA_LONG]);

      void output();
      void clear();
      void display_intensional_rule(std::ostream& fout);


      void assign_val(int n);
      void assign_next(intensional_rule_class *i_ptr);
      void assign_intensional_rule (char f_str[EXTRA_LONG]);
                                                              

      intensional_rule_class     *get_next_ptr();
      int                         get_value();
      
      variable_class             *get_first_variable_ptr();
      predicate_expression_class *get_first_predexp_ptr();


      void add_var_ptr(variable_class *var_ptr);
      void add_variable(char var_str[STRING_LENGTH]);
      void add_predicate_exp_ptr(predicate_expression_class *p_ptr);
      void add_predicate_exptression(char pred_str[LONG_STRING_LENGTH]);

  protected:

      int                                      val;
      intensional_rule_class                  *inextnode;
      list_class<variable_class>               variablelist;
      list_class<predicate_expression_class>   predexplist;
 };
