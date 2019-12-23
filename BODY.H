#pragma once

#include "LITERAL.H"
#include "LOGIC_PR.H"
#include "VERTEX.H"

class body_node_class
   {
  public:
      body_node_class();
      body_node_class(int dummy);
      body_node_class(int distribution, int head_val);

      void assign_val(int n);
      void output();
      void clear();

      int       get_value();

      void assign_next(body_node_class *b_ptr);
      body_node_class *get_next_ptr();

      void add_pos_literal(literal_class *p_ptr);
      void add_pos_literal(int k);  
      void add_pos_literal(int k, vertex_class *v_ptr);
      void add_pos_literal(int k, vertex_class *v_ptr,
                                  body_node_class *b_ptr);


      void add_neg_literal(int k);    
      void add_neg_literal(literal_class *p_ptr);
      void add_neg_literal(int k, vertex_class *v_ptr);
      void add_neg_literal(int k, vertex_class *v_ptr,
                                  body_node_class *b_ptr);


      void find_add_neg_literal(int k);              // WILL NOT ADD REPEATS
      void find_add_pos_literal(int k);              // WILL NOT ADD REPEATS

      int get_body_status();   
      int get_pos_assess();
      int get_neg_assess();

      literal_class *get_first_pos_lit_ptr();
      literal_class *get_first_neg_lit_ptr();

      void set_body_status(int stat);
      void set_pos_assess(int tval);
      void set_neg_assess(int tval);
      void assign_negative_fact(int n);
      void set_num_literals_sat(int num);

      void determine_pos_assess(logic_program_class *P);
      void determine_neg_assess(logic_program_class *P);

//      void determine_UNIT_BODY_pos_assess();
//      void determine_UNIT_BODY_neg_assess();



      void increase_num_literals_sat( int num);
      void display_body();
      void update_body_status();
      int determine_body_status();

      int is_bodiless_rule();
      int get_negative_fact();
      int has_only_negative_subgoals();
      int has_only_positive_subgoals();

      int has_any_negative_subgoals();
      int has_any_positive_subgoals();



  protected:
      //Issue 1: from node_class
      int val;

      body_node_class                 *bnextnode;
      int num_literals_sat;           //  NUMBER LITERALS TRUE
      int pos_assess;
      int neg_assess;
      list_class<literal_class>        neg_literals;
      list_class<literal_class>        pos_literals;
      int                              negative_fact;   // 0 no; 1 yes
      int                              glb_pos_lits(logic_program_class *P);
      int                              glb_neg_lits(logic_program_class *P);
      

};
