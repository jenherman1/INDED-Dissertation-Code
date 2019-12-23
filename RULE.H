#pragma once

#include "BODY.H"
#include "LITERAL.H"
#include "VERTEX.H"

class vertex_class;
class body_node_class;
class literal_class;

class rule_class
   {
  public:
     rule_class();
     rule_class(int n);
     rule_class(vertex_class *v_ptr, body_node_class *b_ptr);
     rule_class(int rule_head, vertex_class *v_ptr, body_node_class *b_ptr);


    int       get_value();
    // VIRTUALS FROM NODE_CLASS

    void assign_val(int n);
    void output();
    void clear();
    
     void assign_next(rule_class *p_ptr);
     rule_class *get_next_ptr();
    
     void              assign_body_ptr(body_node_class  *b_ptr);
     void              assign_vertex_ptr(vertex_class  *v_ptr);
     void              display_rule() {};
     body_node_class  *get_body_ptr();
     vertex_class     *get_vertex_ptr();
     

  protected:
     int val;
     vertex_class    *vertex_ptr;
     body_node_class *body_ptr;
     literal_class  *lnextnode;
     rule_class *rnextnode;
};
