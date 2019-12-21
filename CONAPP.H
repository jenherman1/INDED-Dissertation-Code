#pragma once

#include <fstream>

#include "VERTEX.H"

class constant_appearance_class 
   {
  public:
     constant_appearance_class();
     constant_appearance_class(int n);
     constant_appearance_class(vertex_class *v_ptr);
     constant_appearance_class(int rule_head, vertex_class *v_ptr);


     void      assign_val(int n);            // possibly hold vertex head val
     void      assign_next(constant_appearance_class *p_ptr);
     void      assign_vertex_ptr(vertex_class  *v_ptr);

     constant_appearance_class *get_next_ptr();
     vertex_class              *get_vertex_ptr();
     int                        get_value();

     void              output();
     void              display_appearance(std::ostream& fout);

     void clear();

  protected:

     int                          val;
     vertex_class                *appearance_v_ptr;
     constant_appearance_class   *cappnextnode;
};
