#pragma once

#include "CONST.H"
#include "FULL.H"
#include "LIST.CC"
#include "NODE.H"
#include "PREDSYM.H"
#include "VARIABLE.H"

class predicate_expression_class : public node_class
   {
  public:
      predicate_expression_class();
//      predicate_expression_class(const predicate_expression_class& original_predexp);
      predicate_expression_class(int num);
      predicate_expression_class( list_class<variable_class> participating_variables,
                  char pred_symb[STRING_LENGTH] );     

      predicate_expression_class(char full_s[LONG_STRING_LENGTH]);

    // ASSIGN methods
      void assign_val(int n);
      void output();
      void clear();
      void assign_predicate_symbol(char pred_symb[STRING_LENGTH]); 
      void assign_next(predicate_expression_class *pred_ptr);
      void assign_fullstring(char full_s[LONG_STRING_LENGTH]); 
      void assign_pred_info(char full_s[LONG_STRING_LENGTH], int num);
      void assign_IS_NEGATIVE(int neg_indicator);

       
 
     // GET methods
      predicate_expression_class      *get_next_ptr();
      int              get_pred_val();   
      char            *get_predicate_symbol();
      char            *get_fullstring();
      int              get_num_variables();
      variable_class  *get_first_variable();
      int              get_IS_NEGATIVE();
      int              get_position_of_variable_str
                               (char var_str[STRING_LENGTH]);


      void display();      //Display the entire string as a predicate expression
      void display(std::ostream& fout);

  protected:
      int                              IS_NEGATIVE;
      predicate_expression_class      *prednextnode;
      predicate_symbol_class           predicate_symbol;
      fullstring_class                 fullstring;
      list_class<variable_class>       variablelist;
};
