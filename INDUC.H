#pragma once

#include <fstream>

#include "ATOM.H"
#include "BACK.H"
#include "CONST.H"
#include "EXAMPSET.H"
#include "INTRULE.H"
#include "INTSET.H"
#include "POS.H"
#include "PREDEXP.H"
#include "PREDLOG.H"

class inductive_engine_class
{
   public:
        inductive_engine_class();
        inductive_engine_class(std::ifstream& posexamplefile,
                               std::ifstream& negexamplefile,
                               std::ifstream& backgroundknowfile);

        ~inductive_engine_class();

        void add_POSexample(atom_class *a_ptr);
        void add_POSexample(char new_example[LONG_STRING_LENGTH]);
        void add_NEGexample(atom_class *a_ptr);
        void add_NEGexample(char new_example[LONG_STRING_LENGTH]);
//      void add_background_fact(atom_class *new_fact);
//      void add_background_fact(char new_fact[LONG_STRING_LENGTH]);


        atom_class                       *get_first_positive_example();
        atom_class                       *get_first_negative_example();
        position_class                   *get_first_positive_example_position();
        position_class                   *get_first_negative_example_position();

        predicate_log_class              *get_first_background_predlog_ptr();        
        char                             *get_target_predicate_symbol();
        char                             *get_target_predicate_fullstring();



        void output();
        void clear();
        void display(std::ostream& fout);
        void display_example_set(std::ostream& fout);
        void display_positive_examples(std::ostream& fout);
        void display_negative_examples(std::ostream& fout);
        void display_background_knowledge(std::ostream& fout);

       int_ruleset_class       *learn_rule();
       int_ruleset_class       *learn_rule_defaults();

       int                      is_covered
                                  ( atom_class *ground_example_atom_ptr,
                                  intensional_rule_class *i_ptr);      
        
       double determine_ratio_of_neg_examples_covered
                         (intensional_rule_class  *i_ptr);
       double determine_ratio_of_pos_examples_covered
                         (intensional_rule_class  *i_ptr);
      
       int is_in_mesh_any_order(atom_class *temp_atom_ptr);

        void         make_empty_learned_file(); 

        

 protected:

        void                             get_user_learner_data
                                           ( int&    predicate_rank_algorithm,
                                             int&    position_name_algorithm,
                                             double& suff_stop_crit,
                                             double& nec_stop_crit);
                                 

        void                             perform_example_position_ranking
                                        (  int   position_algorithm_choice,
                                           predicate_log_class *chosen_predlog_ptr);

        void                             initialize_example_position_rankings();

   // POSITION NAME ALGO #1
        void                             rank_and_name_positions_membership_pos_only
                                             (predicate_log_class *chosen_predlog_ptr);

   // POSITION NAME ALGO #2
        void                             rank_and_name_positions_membership
                                             (predicate_log_class *chosen_predlog_ptr);

        void                             name_chosen_predicate_variables
                                            (int pos_name_algo,
                                             predicate_log_class *chosen_predlog_ptr);

        void                             create_learned_rule_file(char filename[STRING_LENGTH]);    


// ----  Predicate Ranking ----
        void                             perform_predicate_ranking
                                              (int predicate_algorithm_choice);

        void                             initialize_predicate_rankings();

   // PREDICATE RANK ALGO #1
        void                             rank_simple_membership_pos_only();
   // PREDICATE RANK ALGO #2
        void                             rank_simple_membership();

   // PREDICATE RANK ALGO #3
        void                             rank_num_times_found_each_pos_pos_only();
   // PREDICATE RANK ALGO #4
        void                             rank_num_times_found_each_pos();


   // PREDICATE RANK ALGO #5
        void                             rank_pos_spot_membership_one_pos_only();
   // PREDICATE RANK ALGO #6
        void                             rank_pos_spot_membership_one();

   // PREDICATE RANK ALGO #7
        void                             rank_predicates_by_coverage_pos_only_single();
   // PREDICATE RANK ALGO #8
        void                             rank_predicates_by_coverage_single();

   // PREDICATE RANK ALGO #9
        void                             rank_predicates_by_coverage_pos_only();
   // PREDICATE RANK ALGO #10
        void                             rank_predicates_by_coverage();




        predicate_expression_class      *construct_next_literal
                                           (int position_naming_choice);
        void                            *name_chosen_variables();
        atom_class   *form_ground_instance
                          (atom_class *ground_source_atom_ptr,  
                           predicate_expression_class *nonground_predexp_ptr);

        double       get_user_inconsistency_coef();
        double       check_for_example_inconsistency();   


                                                                       
        

        predicate_expression_class     *target_predicate_expression_ptr;
        example_set_class              *positive_examples;
        example_set_class              *negative_examples;
        background_knowledge_class     *background_knowledge;
};
