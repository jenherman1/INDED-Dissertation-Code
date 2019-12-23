#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctype.h>
// -------------    P R O T O T Y P E   F I L E S    -------------------

#include "ATOM.H"
#include "BACK.H"
#include "BODY.H"
#include "CONAPP.H"
#include "CONCLASS.H"
#include "CONST.H"
#include "EXAMPSET.H"
#include "FULL.H"
#include "INDUC.H"
#include "INTRULE.H"
#include "INTSET.H"
#include "KB.H"
#include "LIST.CC"
#include "LITERAL.H"
#include "LOGIC_PR.H"
#include "NODE.H"
#include "POS.H"
#include "PREDEXP.H"
#include "PREDSYM.H"
#include "PREDLOG.H"
#include "RULE.H"
#include "SPANTREE.H"
#include "UTILITY1.H"             //Global Functions using integers
#include "UTILITY2.H"              //Global Functions using strings
#include "VARIABLE.H"
#include "VERTEX.H"
#include "VERTPTR.H"

//--------------   G L O B A L   V A R I A B L E S   -----------

using namespace std;

//TODO: This is not good practice!
//#include "UTILITY.cpp"
//#include "NODE.cpp"
//#include "CONAPP.cpp"
//#include "CONCLASS.cpp"
//#include "POS.cpp"
//#include "PREDLOG.cpp"
//#include "VARIABLE.cpp"
//#include "PREDSYM.cpp"
//#include "FULL.cpp"
//#include "PREDEXP.cpp"
//#include "INTRULE.cpp"
//#include "ATOM.cpp"
//#include "BODY.cpp"
//#include "LITERAL.cpp"
//#include "RULE.cpp"
//#include "VERTEX.cpp"
//#include "VERTPTR.cpp"
//#include "SPANTREE.cpp"
//#include "LOGIC_PR.cpp"
//#include "EXAMPSET.cpp"
//#include "INTSET.cpp"
//#include "BACK.cpp"
//#include "KB.cpp"
//#include "INDUC.cpp"

// -------------   I M P L E M E N T A T I O N   F I L E S   -----------

int main(int argc, char **argv)
///////////////////////////////////////////////////////////////////////
///    Main samp57_learn24
///
///    GOAL:  To correctly implement:
///
///           1.  Repair predicate ranking algorithms
///           2.  Build real world example sets:
///                  --butterfly vs. moth
///                  --secondary structure of proteins 
///                  --negatively recursive predicates
///
///    STATUS: Success
///
///
////////////////////////////////////////////////////////////////////////

{


    list_class<fullstring_class> *flist;
    fullstring_class             *f_ptr;
    char                          full_string[EXTRA_LONG];
    char                          inpred[LONG_STRING_LENGTH];
    char                          inrule[EXTRA_LONG];
    char                          new_rule[EXTRA_LONG];
    char                          current_atom_string[LONG_STRING_LENGTH];

    intensional_rule_class       *i_ptr, other_i_rule;

    char                          gochar;

    ofstream                      outfile;
    char                          tempstr[LONG_STRING_LENGTH];
    int_ruleset_class            *my_learned_ruleset;



    knowledge_base_class         *Background;
    inductive_engine_class       *Learner;

    char                          choice = ' ';
    char                          back_filename[STRING_LENGTH];
    char                          gins_filename[STRING_LENGTH];
    char                          intset_filename[STRING_LENGTH];

    char                          waitchar = ' ';





    // DECLARE I/O STREAMS
    // -------------------

    ifstream              domedb_ifstream;        //creating DED Engine
    ifstream              domidb_ifstream;        

    ifstream              posexamp_ifstream;      //creating IND Engine
    ifstream              negexamp_ifstream;      //  "
    ifstream              background_ifstream;    //  "

    ifstream              new_learned_int_ifstream;    //iterating back to DED Engine
    ifstream              cummulative_intset_ifstream; //  "
    
    ofstream              learned_ofstream;       //output of IND Engine
    ofstream              intset_ofstream;        //Cummulative INTRULES by DED
    ofstream              newstate_ofstream;      //output of DED Engine


    // DECLARE I/O STREAM STRING FILE NAMES
    // ------------------------------------

    char              domedb_filename_str[STRING_LENGTH]; //creating DED Engine
    char              domidb_filename_str[STRING_LENGTH];        

    char              posexamp_filename_str[STRING_LENGTH];      //creating IND Engine
    char              negexamp_filename_str[STRING_LENGTH];      //  "

    char              background_filename_str[STRING_LENGTH] = "newstate.bkg";  //DED output; IND input
    char              new_learned_int_filename_str[STRING_LENGTH] = "learned.int";  //IND output; DED input
    char              cummulative_intset_filename_str[STRING_LENGTH] = "cumint.mid";  //DED output; DED input
    



    // CREATE DEDUCTION ENGINE
    // ------------------------
    clear_screen(NUM_LINES_CLEARSCREEN);

    cout << "Enter input file name of the EDB:   ";
    cin >> domedb_filename_str;
    domedb_ifstream.open(domedb_filename_str);
    while (!domedb_ifstream) {
           domedb_ifstream.close();
           cout << "Nonexistent File...Please enter EDB file again.\n";
           cin >> domedb_filename_str;
           domedb_ifstream.open(domedb_filename_str);
    } // WHILE


//------ ESTABLISH IDB SOURCE ------------------

    cout << "Enter input file name of the IDB:   ";
    cin >> domidb_filename_str;
    domidb_ifstream.open(domidb_filename_str);
    while (!domidb_ifstream) {
           domidb_ifstream.close();
           cout << "Nonexistent File...Please enter IDB file again.\n";
           cin >> domidb_filename_str;
           domidb_ifstream.open(domidb_filename_str);
    } // WHILE

//---------------

    Background = new knowledge_base_class(domedb_ifstream, domidb_ifstream);

    domedb_ifstream.close();
    domidb_ifstream.close();


    Background->compute_current_state();



    // ASSUME INTERACTIVE MODE ... ALLOW USER TO CHOOSE
    // ------------------------------------------------

    clear_screen(NUM_LINES_CLEARSCREEN);
    display_menu();
    cout << "Enter menu choice for operation.  Enter 'Q' to quit. \n";
    cin >> choice;
 
    while ( (choice != 'q') && (choice != 'Q') ) {
          switch (choice) {
             case 'N':
             case 'n': 
                         Background->nonmonotonically_update(cin);
                         break;
                       
             case 'R':
             case 'r': 
                         clear_screen(NUM_LINES_HALFSCREEN); 
                         cout << "\n Enter new rule to add to KNOWLEDGE BASE..\n ";
                         strcpy(new_rule, "");
                         gochar = *read_rule(cin, new_rule);
                         show_rule(cout, new_rule);
                         i_ptr = new intensional_rule_class(new_rule);

                         Background->augment_ground_instantiation_ptr(i_ptr);
                         Background->add_intensional_rule(i_ptr);
                         break;

             case 'S':
             case 's':  
                         Background->compute_current_state();
                         Background->show_current_state(cout);
                         break;
           
             case 'F':
             case 'f': 
                         cout << "Enter new background file name. \n";
                         cin >> back_filename;
                         Background->create_background_knowledge_file(back_filename);       
                         break;

             case 'G':
             case 'g': 
                         cout << endl << endl << endl;
                         cout << "Enter new GROUND INSTANTIATION file name. \n";
                         cin >> gins_filename;
                         Background->create_ground_instantiation_file(gins_filename);       
                         break;
             case 'I':
             case 'i': 
                         cout << endl << endl << endl;
                         cout << "Enter new INTENSIONAL RULE SET file name. \n";
                         cin >> intset_filename;
                         Background->create_intrule_set_file(intset_filename);       
                         break;

            case 'L':
            case 'l':
                         cout << endl << endl << endl;
                         // CREATE INTERMEDIATE INTENSIONAL RULESET FOR RETURN TO DED
                         Background->create_intrule_set_file
                                 (cummulative_intset_filename_str);

                         // COMPUTE THE MOST RECENT STATE
                         Background->compute_current_state();

                         // CREATE THE BACKGROUND FILE FOR INDUCTION ENGINE
                         Background->create_background_knowledge_file
                                 (background_filename_str);

                         // LOCATE TARGET EXAMPLES

                         //------ ESTABLISH POSITIVE EXAMPLE SOURCE ------------------

                         cout << "Enter input file name of the POSITIVE EXAMPLE Set:   ";
                         cin >> posexamp_filename_str;
                         posexamp_ifstream.open(posexamp_filename_str);
                         while (!posexamp_ifstream) {
                             posexamp_ifstream.close();
                             cout << "Nonexistent File...Please enter POSITIVE EXAMPLE file again.\n";
                             cin >> posexamp_filename_str;
                             posexamp_ifstream.open(posexamp_filename_str);
                         } // WHILE

                        //------ ESTABLISH NEGATIVE EXAMPLE SOURCE ------------------

                         cout << "Enter input file name of the NEGATIVE EXAMPLE Set:   ";
                         cin >> negexamp_filename_str;
                         negexamp_ifstream.open(negexamp_filename_str);
                         while (!negexamp_ifstream) {
                             negexamp_ifstream.close();
                             cout << "Nonexistent File...Please enter NEGATIVE EXAMPLE file again.\n";
                             cin >> negexamp_filename_str;
                             negexamp_ifstream.open(negexamp_filename_str);
                         } // WHILE

                        //-------------------------

                         background_ifstream.open(background_filename_str);

                         // FREE UP MEMORY USED BY DEDUCTION ENGINE
                         delete Background;      

                         // BUILD INDUCTION ENGINE AND INDUCT NEW RULE
                         Learner = new inductive_engine_class( posexamp_ifstream,
                                                               negexamp_ifstream,
                                                               background_ifstream);
                         posexamp_ifstream.close();
                         negexamp_ifstream.close();
                         background_ifstream.close();
// Learner->display(cout);

                         my_learned_ruleset = Learner->learn_rule();
                         
                         clear_screen(NUM_LINES_CLEARSCREEN);
                         if (my_learned_ruleset != nullptr) {
                             my_learned_ruleset->display(cout);

                             waitchar = ' ';
                             cout << endl << endl << "Press 'c' to continue..   ";
                             cin >> waitchar;
 
                            //CREATE AN EXTERNAL FILE CONTAINING THE NEW RULES
                              my_learned_ruleset->create_intrule_set_file
                                          (new_learned_int_filename_str);

                         }//IF
                         else { //CREATE AN EMPTY learned.int FILE
                              Learner->make_empty_learned_file();
                         } //ELSE
                         delete Learner;

                        //REBUILD THE DEDUCTION ENGINE
                         cummulative_intset_ifstream.open
                                          (cummulative_intset_filename_str);
                         new_learned_int_ifstream.open
                                          (new_learned_int_filename_str);
                         domedb_ifstream.open
                                          (domedb_filename_str);

                         Background = new knowledge_base_class(domedb_ifstream, 
                                               cummulative_intset_ifstream,
                                               new_learned_int_ifstream);

                         cummulative_intset_ifstream.close();
                         new_learned_int_ifstream.close();
                         domedb_ifstream.close();
                         
                         Background->compute_current_state();
                         
                         break;


            default :   
                         cout << "Invalid choice.  Enter again. \n";
         } //SWITCH        

         display_menu();
        cin >> choice;
   } // WHILE
//
//

    return 0;
}  // MAIN

