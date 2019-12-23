#pragma once

#include <fstream>

#include "BODY.H"
#include "CONST.H"
#include "LIST.CC"
#include "LITERAL.H"
#include "RULE.H"
#include "SPANTREE.H"
#include "VERTEX.H"

class logic_program_class
{
   public:
        logic_program_class();
        logic_program_class(int distribution);
        logic_program_class(char *filename);
        logic_program_class(std::ifstream& infile);
  
        ~logic_program_class();

        void output();
        void clear();
        void output_graph();
        void add_vertex(vertex_class *v_ptr);
        void add_spantree(spantree_class *s_ptr);
        void add_rule(rule_class *r_ptr);
        void add_rule(vertex_class *v_ptr, body_node_class *b_ptr);
        void add_rule(int head_val, vertex_class *v_ptr, 
                      body_node_class *b_ptr);
        void add_extensional_rule(char  new_rule[EXTRA_LONG]); 

        void  get_KK_model();
        void  get_WF_model_definition();

        void  get_WF_4_value();
        void  get_WF_4_value_optimize();
        void find_first_stable_model();
        void  get_WF_linear();
        void  get_WF_linear_2();
        void  get_WF_linear_stack();
        void  get_WF_linear_combine();
        void  get_WF_linear_unit();
        int  get_num_vertices();

         
        void display();
        void display_head_groups();
        void display_model();
        void show_state(std::ostream& fout);
        void update_state();
        void add_fact_to_stream(std::istream& infile);
        vertex_class *add_fact(char tempstr[LONG_STRING_LENGTH], int is_negative_fact);

        void nonmonotonically_update(std::istream& infile);
        void display_ground_instantiation(std::ostream& outfile);
  
        void update_graph();
        void initialize_graph();
        int total(int *num_true, int *num_false, int *num_bottom,
                  int *num_top);
        void compute_postorder_nums();


//   ----  WF 4-value version  -----
        int                      get_lit_Jval(literal_class *l_ptr);

        int                      get_lit_truth(literal_class *l_ptr);        
        int                      get_neg_lit_Wval(literal_class *l_ptr);
        void                     transfer_W_to_truth();
        logic_program_class     *factor_out();
        vertex_class            *get_first_vertex();
        spantree_class          *grow_spanning_tree(vertex_class *v_ptr,
                                                    int         start_val);
        void                     form_all_spanning_trees();
        void                     print_spanning_trees();

        void print_truth_atoms(std::ostream& fout, int t_val);
        int compute_num_assignments(int num_vars);



 protected:
        void add_subgoals_outgoing_edge_pieces(int head_val,
                                               vertex_class *head_ptr,
                                               body_node_class *body_ptr);
        int determine_truths();

        int already_included (int head_val);
        int determine_falsities_KK();
        void propogate_truthfulness_KK(vertex_class *v_ptr);
//
        void Tp_star();
        int determine_falsities_WF();  // Assign false those NOT IN J
        void determine_J();            // Construct J where J is Bp - Up
        int check_all_pos_subgoals(body_node_class *b_ptr);        
        int any_positive_lits();
        int any_negative_lits();
        void reassign_access();
        void reinitialize_graph_for_spantree();
        vertex_class   *find_fullstring_in_graph( char instr[LONG_STRING_LENGTH]);

//   ----  WF 4-value version  -----
 
        void          perform_neg_assess_on_bodies(); 
        void          reinitialize_J_vals();
        int           determine_J_vals();
        void          determine_J_vals_optimize();
        int           update_W_vals();
        vertex_class *get_lit_vertex(literal_class *l_ptr); 
        vertex_class *get_vertex_ptr(rule_class *r_ptr);
        body_node_class *get_body_ptr(rule_class *r_ptr);
        void          initialize_Q_all();
        void          initialize_Q_appearances();
        void          initialize_Q_only_neg_subgoals();
        void          initialize_Q_neg_subgoals();
        void          initialize_Q_head_bod();
        void          initialize_Q_bodiless();
        void          initialize_Q_headless();
        void          initialize_Q_negatives();
        void          initialize_Q_positives();

        void          initialize_Q_negatives_stack();
        void          initialize_Q_headless_stack();
        void          initialize_Q_bodiless_stack();
        void          initialize_Q_positives_stack();     

        void          final_scan_W_vals_Q();

//

        vertex_class *find_add_vertex(int k);
        vertex_class *find_vertex(int find_val);
        

        int bodystoi (char *iarray);
        int stoi(char *iarray);

        void display_rule(rule_class *r_ptr);
        void display_rule(vertex_class    *v_ptr,
                          body_node_class *b_ptr);
        void display_extensional_rule( vertex_class    *head_v_ptr,
                                       body_node_class *body_b_ptr,
                                       std::ostream& fout );

        void print_truth_vals(int t_val);
        void print_postorder_nums();

        list_class<rule_class>       rulelist;
        list_class<vertex_class>     Vertexlist;
        list_class<spantree_class>   Spantreelist;
        void preassign_false_variables();
        void assign_all_false_variables();
        void assign_binary(int model_num);         
        
};
