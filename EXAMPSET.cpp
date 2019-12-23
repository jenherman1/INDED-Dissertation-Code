#include <fstream>
#include <iostream>

#include "EXAMPSET.H"
#include "UTILITY2.H"

using namespace std;

example_set_class::example_set_class()
{
        logpositionobject = nullptr;
} // CONSTRUCTOR for example_set_class



///////////////////////////////////////////////////////////////////////////
///  Construct an intensional logic program by reading an input stream
///  of EXAMPLES in the form of ATOM_CLASS objects
///////////////////////////////////////////////////////////////////////////
example_set_class::example_set_class(ifstream& infile)
{

list_class<fullstring_class> *flist;     
fullstring_class             *f_ptr;
char                          full_string[ EXTRA_LONG];
char                          gochar = '.';          
char                          tempstr[LONG_STRING_LENGTH];
atom_class                   *a_ptr;


  logpositionobject = nullptr;


  // READ IN FIRST EXAMPLE 
   gochar = *read_rule(infile, full_string);


   while (gochar == '.') {

        flist = new list_class<fullstring_class>();   
        extract_atom_strings(full_string, flist);       
        f_ptr = flist->get_first();      
        while (f_ptr != nullptr) {
              strcpy(tempstr, f_ptr->get_fullstring_symbol());    
              a_ptr = new atom_class(tempstr, f_ptr->get_IS_NEGATIVE()); 

              // ADD NEW ATOM TO THE SET OF ATOM-VERSION EXAMPLES
              atomexamplelist.add_ptr(a_ptr);
 
              //IF THIS IS FIRST EXAMPLE, CREATE THE PRED-LOG STRUCTURE
              if (logpositionobject == nullptr)   {
                    // ADD NEW ATOM TO THE PREDICATE_LOG-VERSION SET
                       logpositionobject   = new predicate_log_class(a_ptr);   
              } // IF
              else {
                       logpositionobject->add_new_atom(a_ptr);
              } // ELSE
              f_ptr = f_ptr->get_next_ptr();
        }//WHILE
        
        gochar = *read_rule(infile, full_string);
   } // WHILE

} // CONSTRUCTOR for example_set_class

//__________________________________________________________________________

example_set_class::~example_set_class()
{
        atomexamplelist.cleanup();
}

//__________________________________________________________________________
void example_set_class::output()
{
      cout << "The list of atoms is.. \n";
      atomexamplelist.print();
      cout << "The structure of positions is... \n";
      logpositionobject->output();    
}
//__________________________________________________________________________

void example_set_class::add_atom_example(atom_class *a_ptr)
{
      atomexamplelist.add_ptr(a_ptr);
}
//__________________________________________________________________________

void example_set_class::add_atom_example(char new_example[LONG_STRING_LENGTH]) 
{
      atom_class        *a_ptr; 
      a_ptr = new atom_class(new_example);

      atomexamplelist.add_ptr(a_ptr);
}
//__________________________________________________________________________
void example_set_class::add_log_example(atom_class *a_ptr)    
{
     logpositionobject->add_new_atom(a_ptr);
}

//__________________________________________________________________________

void example_set_class::add_log_example(char new_example[LONG_STRING_LENGTH]) 
{
      atom_class        *a_ptr; 
      a_ptr = new atom_class(new_example);
      logpositionobject->add_new_atom(a_ptr);

}

//__________________________________________________________________________
atom_class *example_set_class::get_first_atom_ptr()
{
        return  atomexamplelist.get_first();
}

//__________________________________________________________________________
position_class  *example_set_class::get_first_position_ptr()
{
        return  logpositionobject->get_first_pos_ptr(); 
}

//__________________________________________________________________________
void example_set_class::display_atoms(ostream& fout)
{

     atom_class *a_ptr;

     a_ptr = atomexamplelist.get_first();

     while (a_ptr != nullptr)  {
           a_ptr->display(fout);
           fout << "  . \n";
           a_ptr = a_ptr->get_next_ptr();
     }//WHILE

     fout << "@@@@@@@@@@@@@@@@@@@@@@" << endl;
}
//__________________________________________________________________________
void example_set_class::display(ostream& fout)
{
     //  DISPLAY ATOMS
     atom_class *a_ptr;

     a_ptr = atomexamplelist.get_first();

     while (a_ptr != nullptr)  {
           a_ptr->display(fout);
           fout << "  . \n";
           a_ptr = a_ptr->get_next_ptr();
     }//WHILE

     fout << "@@@@@@@@@@@@@@@@@@@@@@" << endl;

     //  DISPLAY POSITION LOG MESH

     fout << endl << endl;
     fout << "Example Set Log:" << endl;
     fout << "================" << endl;
     logpositionobject->display(fout); 
     fout << "@@@@@@@@@@@@@@@@@@@@@@" << endl;
}

// -------------------------------------------------------------
void example_set_class::display_log(ostream& fout)
{

     fout << endl << endl;
     fout << "Example Set Log:" << endl;
     fout << "================" << endl;
     logpositionobject->display(fout); 
     fout << "@@@@@@@@@@@@@@@@@@@@@@" << endl;
}


// -------------------------------------------------------------
void example_set_class::name_example_variables()
{
      logpositionobject->name_variables('A');
}

//------------------------------------------------------------
void example_set_class::clear()
{
     logpositionobject->clear();
//     logpositionobject = nullptr;
     atomexamplelist.cleanup();
}
//------------------------------------------------------------
void example_set_class::initialize_position_rankings()   
{
     logpositionobject->initialize_position_ranks();  
}

//------------------------------------------------------------
void example_set_class::initialize_position_chosen_flags()   
{
     logpositionobject->initialize_position_chosen_flags();  
}


//------------------------------------------------------------
position_class *example_set_class::get_max_ranked_unchosen_position_ptr()
{
     return logpositionobject->get_max_ranked_unchosen_position_ptr();
}

//------------------------------------------------------------
char example_set_class::get_max_variable_name()
{
     return logpositionobject->get_max_variable_name();   
}

////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////
void example_set_class::initialize_coverage()
{
     atom_class  *cur_a_ptr;

     cur_a_ptr = get_first_atom_ptr();

     while (cur_a_ptr != nullptr) {
          cur_a_ptr->initialize_covered();
          cur_a_ptr = cur_a_ptr->get_next_ptr();
     } //WHILE
}


///////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////
int  example_set_class::get_num_examples()
{
       return atomexamplelist.get_length();  
}                                              


//////////////////////////////////////////////////////////////
predicate_log_class *example_set_class::get_predlog_object_ptr()
{
      return logpositionobject;
}
