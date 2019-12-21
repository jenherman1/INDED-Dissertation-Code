#pragma once

#include <fstream>

#include "ATOM.H"
#include "CONST.H"
#include "LIST.CC"
#include "PREDLOG.H"
#include "POS.H"

class example_set_class
{
   public:
        example_set_class();
        example_set_class(std::ifstream& infile);
  
        ~example_set_class();

        void add_atom_example(atom_class *a_ptr);
        void add_atom_example(char new_example[LONG_STRING_LENGTH]);

        void add_log_example(atom_class *a_ptr);
        void add_log_example(char new_example[LONG_STRING_LENGTH]);
    
        atom_class       *get_first_atom_ptr();
        position_class   *get_first_position_ptr();       
        predicate_log_class *get_predlog_object_ptr();
 
        int              get_num_examples();
        
        void output();
        void clear();
        void display(std::ostream& fout);
        void display_atoms(std::ostream& fout);
        void display_log(std::ostream& fout);
     
        void name_example_variables();
        void initialize_position_rankings();
        void initialize_position_chosen_flags();
 
        position_class *get_max_ranked_unchosen_position_ptr();
        char           get_max_variable_name();

        void  initialize_coverage();
  
   protected:
        predicate_log_class         *logpositionobject;
        list_class<atom_class>       atomexamplelist;

};
