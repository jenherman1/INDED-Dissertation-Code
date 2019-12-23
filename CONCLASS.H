#pragma once

#include "CONAPP.H"
#include "CONST.H"
#include "LIST.CC"
#include "VERTEX.H"

class constant_appearance_class;
class vertex_class;

class constant_class 
   {
  public:
      constant_class();
      constant_class(int num);
      constant_class(char instr[STRING_LENGTH]);

      void output();
      void clear();

      void assign_next(constant_class *c_ptr);
      void assign_val (int num);
      void assign_symbol(char instr[STRING_LENGTH]);

      int                        get_value();
      constant_class            *get_next_ptr();
      char                      *get_constant_symbol();
      constant_appearance_class *get_first_con_appearance();

      void  display();
      void  display(std::ostream& fout);
      void  display_appearance_list(std::ostream& fout);

      void      add_constant_appearance(vertex_class *v_ptr);
      void      add_constant_appearance(int headval, vertex_class *v_ptr);


      int       is_taken();
      void      mark_is_taken();
      void      mark_NOT_taken();


  protected:
      int                                    val;
      constant_class                        *cnextnode;
      char                                   constant_symbol[STRING_LENGTH];
      list_class<constant_appearance_class>  appearancelist;
};
