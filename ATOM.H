#pragma once

#include <fstream>

#include "BODY.H"
#include "CONCLASS.H"
#include "CONST.H"
#include "FULL.H"
#include "LIST.CC"
#include "NODE.H"
#include "PREDSYM.H"
#include "VERTEX.H"

class body_node_class;
class constant_class;
class node_class;
class vertex_class;

class atom_class
   {
  public:
      atom_class();
      atom_class(int num);
      atom_class( list_class<constant_class> participating_constants,
                  char pred_symb[STRING_LENGTH] );     

      atom_class(char full_s[LONG_STRING_LENGTH]);
      atom_class(char full_s[LONG_STRING_LENGTH], int is_negative_val);
      ~atom_class();


    // ASSIGN methods
      void assign_val(int n);
      void output();
      void clear();
      void assign_predicate(char pred_symb[STRING_LENGTH]); 
      void assign_next(atom_class *a_ptr);
      void assign_fullstring(char full_s[LONG_STRING_LENGTH]); 
      void assign_atom_info(char full_s[LONG_STRING_LENGTH], int num);
      void assign_atom_info(char full_s[LONG_STRING_LENGTH], int num,
                              int is_negative_val);
      void assign_IS_NEGATIVE(int num);

       
 
     // GET methods
      atom_class *get_next_ptr();
      int              get_atom_val();   
      char            *get_predicate_symbol();
      char            *get_fullstring();
      int              get_num_constants();
      int              get_IS_NEGATIVE();
      constant_class  *get_first_constant();
      char            *get_ith_constant_symbol(int num);


      void display();      //Display the entire string as a ground predicate
      void display(std::ostream& fout);

      void initialize_covered();
      void mark_covered();
      void mark_NOT_covered();
      int get_is_covered();


  protected:
      int val;
      vertex_class    *vertex_ptr;
      body_node_class *body_ptr;
      node_class      *nextnode;
      atom_class                      *anextnode;
      predicate_symbol_class           predicate_symbol;
      fullstring_class                 fullstring;
      list_class<constant_class>       constantlist;
};
