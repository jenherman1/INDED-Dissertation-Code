#pragma once

#include <fstream>

#include "ATOM.H"
#include "CONST.H"
#include "LIST.CC"
#include "PREDEXP.H"
#include "PREDLOG.H"

class background_knowledge_class
{
   public:
        background_knowledge_class();
        background_knowledge_class(std::ifstream& infile);
  
        ~background_knowledge_class();

    
        predicate_log_class  *get_first_predlog_ptr();
        
        void output();
        void display(std::ostream& fout);
        void clear();
        predicate_log_class   *get_max_unchosen_predlog();
        void                   reinitialize_chosen_mesh();
        void                   initialize_predicate_rankings();
        void                   initialize_mesh_chosen_and_predrank();



        int     covers(atom_class   *example_a_ptr, 
                      predicate_expression_class *current_rule_literal_predexp_ptr);
    
        int     is_in_mesh_any_order(atom_class *temp_atom_ptr);


  
   protected:
        predicate_log_class 
               *find_predicate_log(int truth_p_val, char  instr[STRING_LENGTH]);


        list_class<predicate_log_class>         predicateloglist;

};
