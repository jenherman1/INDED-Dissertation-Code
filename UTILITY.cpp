#include <iostream>
#include <cstring>

#include "UTILITY1.H"
#include "UTILITY2.H"

using namespace std;

////////////////////////////////////////////////////////////////////////
///  output current run definitives to the output file.
////////////////////////////////////////////////////////////////////////
void show_bulk_run_stats()
{

int i;


for (i=0; i < 5; i++)
     OutputFile << "# \n";

  OutputFile << "#--------------- Current Run Stats ---------------------- \n";
  OutputFile << "#   Distribution:             "; 
  switch (Distribution) {
    case 0: {OutputFile << "NODIST               " << "\n"; break;}
    case 1: {OutputFile << "FIXED_MAX_BODY_LEN   " << "\n"; break;}
    case 2: {OutputFile << "FIXED_BODY_LEN       " << "\n"; break;}
    case 3: {OutputFile << "CONSTANT_PROB        " << "\n"; break;}
    case 4: {OutputFile << "FIXED_BOD_SMALL_BODILESS " << "\n"; break;}
  } 

  OutputFile << "#   Number of Trials:                 " << Num_Trials << " \n";
  OutputFile << "#   Increment of Ratio Change:        " << Ratio_Change_Increment << " \n";
  OutputFile << "# --------------------------------------------------------------- \n";
  OutputFile << "#   Body Length:                             " << Body_Length << " \n";
  OutputFile << "#   Number of Variables:                     " << Num_Variables << " \n";
  OutputFile << "#   Max Number of Negatives:                 " << Max_Negative_Subgoals << " \n";
  OutputFile << "#   Percentage of Forced Bodiless Rules:     " << Bodiless_Percent << " \n";
  OutputFile << "#   Percent Preassigned Variables FALSE:     " << Preassign_False_Percent << "\n";
  OutputFile << "#   Num_Preassign_False:                     " << Num_Preassign_False << "\n";

  OutputFile << "#-------------------------------------------------------- \n";

  for (i=0; i<5; i++)
      OutputFile << "#   \n";
    
} // SHOW_BULK_RUN_STATS



/////////////////////////////////////////////////////////////////////////
///  output current run definitives
////////////////////////////////////////////////////////////////////////
void show_run_stats()
{
 int i;

 for (i=0; i < 5; i++)
     cout << "\n";

  cout << "--------------- Current Run Stats ---------------------- \n";
  cout << "Distribution:             "; 
  switch (Distribution) {
    case 0: {cout << "NODIST               " << "\n"; break;}
    case 1: {cout << "FIXED_MAX_BODY_LEN   " << "\n"; break;}
    case 2: {cout << "FIXED_BODY_LEN       " << "\n"; break;}
    case 3: {cout << "CONSTANT_PROB        " << "\n"; break;}
    case 4: {cout << "FIXED_BOD_SMALL_BODILESS " << "\n"; break;}
  } 

  cout << "Number of Trials:                 " << Num_Trials << " \n";
  cout << "Increment of Ratio Change:        " << Ratio_Change_Increment << " \n";
  cout << "--------------------------------------------------------------- \n";
  cout << "Body Length:                             " << Body_Length << " \n";
  cout << "Number of Variables:                     " << Num_Variables << " \n";
  cout << "Max Number of Negatives:                 " << Max_Negative_Subgoals << " \n";
  cout << "Rule to Variable Ratio:                  " << Rule_to_Var_Ratio << " \n"; 
  cout << "Percentage of Forced Bodiless Rules:     " << Bodiless_Percent << " \n";
  cout << "Number of Rules:                         " << Num_Rules << "  \n";
  cout << "Number of Forced Bodiless Rules:         " << Num_Bodiless_Rules << "\n";
  cout << "Variable Appearance Prob:                " << Var_Prob << " \n";
  cout << "_Negative_ Appearance Prob:              " << Neg_Subgoal_Prob << " \n";
  cout << "Percent Preassigned Vars FALSE:          " << Preassign_False_Percent << "\n";
  cout << "Number Preassigned Vars FALSE:           " << Num_Preassign_False << "\n";


  cout << "--------------------------------------------------------------- \n";

  for (i=0; i<5; i++)
      cout << "\n";
    
} // SHOW_RUN_STATS






/////////////////////////////////////////////////////////////////////////
///   Initialize global variables which determine logic program type.
////////////////////////////////////////////////////////////////////////

void get_user_data()
{
  int i;


  for (i=0; i < 5; i++)
     cout << "\n";




  cout << "------------------------------------------------------------------------ \n";
  cout << " Enter Distribution:  \n";
  cout << "      0 --  No Distribution..mechanical test  \n";
  cout << "      1 --  Fixed MAX Rule Body Length \n";  
  cout << "      2 --  Fixed Rule Body Length \n";
  cout << "      3 --  Constant Probability \n";
  cout << "      4 --  Fixed Body Size with Some Bodiless Rules \n";
  cout << "      5 --  Uni-Rule Programs (with arbitrarily many subgoals) \n";
  cout << "----------------------------------------------------------------------- \n";
  cout << " \n";

  cin >> Distribution;

  for (i=0; i < 5; i++)
     cout << "\n";

  switch (Distribution) {
    case 0: {
             Body_Length = 5;   // ARBITRARY ASSIGNMENT
             cout << "\n";
             Var_Prob = -1.0;
             Neg_Subgoal_Prob = -1.0;
             Max_Negative_Subgoals = 2;
             break; }

    case 1: {cout << "Enter maximum rule body length:  ";
             cin >> Body_Length;
             cout << "\n";
             Var_Prob = -1.0;
             Neg_Subgoal_Prob = -1.0;
             cout << "Enter maximum number of negative subgoals in each rule:  ";
             cin >> Max_Negative_Subgoals;

             break; }
             
    case 2: {cout << "Enter rule body length (Fixed Value):";
             cin >> Body_Length;
             cout << "\n";
             Var_Prob = -1.0;
             Neg_Subgoal_Prob = -1.0;
             cout << "Enter maximum number of negative subgoals in each rule:  ";
             cin >> Max_Negative_Subgoals;
             break; }


    case 3: {cout << "Enter probability of each variable's appearance:";
             cin >> Var_Prob;
             cout << "Enter the probability that an appearing variable ";
             cout << "will be Negative:  ";
             cin >> Neg_Subgoal_Prob;
             cout << "\n";
             Body_Length = -1;
             Max_Negative_Subgoals  = -1;
             break; }

    case 4: {cout << "Enter rule body length (Fixed Value):";
             cin >> Body_Length;
             cout << "\n";
             Var_Prob = -1.0;
             Neg_Subgoal_Prob = -1.0;
             cout << "Enter maximum number of negative subgoals in each rule:  ";
             cin >> Max_Negative_Subgoals;
             cout << "Enter percentage of Bodiless Rules:  ";
             cin >> Bodiless_Percent;
             break; }


    case 5: {
             Body_Length = -1;
             cout << "\n";
             Var_Prob = -1.0;
             Neg_Subgoal_Prob = -1.0;
             Max_Negative_Subgoals = -1;
             Bodiless_Percent = -1.0;
             break; }

   } // SWITCH


  for (i=0; i<3; i++)
        cout << "\n";

  cout << "Enter desired rule to variable ratio:  ";
  cin >> Rule_to_Var_Ratio;
  cout << "\n";

  cout << "Enter number of variables:  ";
  cin >> Num_Variables;
  cout << "\n";

  Num_Rules = static_cast<int>(Rule_to_Var_Ratio  *  Num_Variables);
  Num_Bodiless_Rules = static_cast<int>(Bodiless_Percent * 0.01f * Num_Rules);
  Num_Trials = 1;
  Ratio_Change_Increment = 0.0;
  cout << "\n";

}


/////////////////////////////////////////////////////////////////////////
//  Gets user's desired preassignment percentages.
////////////////////////////////////////////////////////////////////////
void get_percent_preassigned()
{
   
  cout << "\n";
  cout << "Enter percentage of pre-assigned variables to FALSE:  \n";
  cin >> Preassign_False_Percent;

  Num_Preassign_False = static_cast<int>(Preassign_False_Percent * Num_Variables * 0.01f);

  cout << "\n"; 
  cout << "Enter percentage of pre-assigned variables to TRUE:  \n";
  cin >> Preassign_True_Percent;
  Num_Preassign_True = static_cast<int>(Preassign_True_Percent *  Num_Variables * 0.01f);
  cout << "\n"; 
}



/////////////////////////////////////////////////////////////////////////
///  Reads in from user number of vars to preinitialize.  For use with
///  reading graphs in from input files.
////////////////////////////////////////////////////////////////////////
void get_number_preassigned()
{
    cout << "\n";
    cout << "Enter number of pre-assigned variables to FALSE:  \n";
    cin >> Num_Preassign_False;
cout << "Just determined  Num_Preassign_False ..." <<
     Num_Preassign_False << "\n";

    cout << "\n";
    cout << "Enter number of pre-assigned variables to TRUE:  \n";
    cin >> Num_Preassign_True;
    cout << "\n";
}
      

/////////////////////////////////////////////////////////////////////////
///   Initialize global variables used for multiple program runs.
////////////////////////////////////////////////////////////////////////

void get_user_bulk_data()

{
  int i;
  for (i=0; i < 5; i++)
     cout << "\n";

  cout << "----------------------------------------------------------- \n";
  cout << " Enter Number of Trials per Ratio Value:  \n";
  cout << "----------------------------------------------------------- \n";
  cout << " \n";

  cin >> Num_Trials;
  cout << "----------------------------------------------------------- \n";
  cout << " Enter Clause-to-Var-Ratio CHANGE INCREMENT: \n";
  cout << "----------------------------------------------------------- \n";
  cout << " \n";
  cin >> Ratio_Change_Increment;

  for (i=0; i < 5; i++)
     cout << "\n";
  
} // GET_USER_BULK_DATA






//////////////////////////////////////////////////////////////////////////////
///  Returns a random integer k such that 0 <= k <= upper_bound
//////////////////////////////////////////////////////////////////////////////
int get_random_val(int upper_bound)
{
   float flt_temp;

   flt_temp = static_cast<float>(rand());

   flt_temp = flt_temp / RANDOM_SCALE    // **** activate this for LINUX
   flt_temp = flt_temp / 32768.0f;
   flt_temp = flt_temp * (upper_bound + 1) ;

   return  static_cast<int>(flt_temp);
} 








//////////////////////////////////////////////////////////////////////////////
///  Returns a random float x such that 0 <= x <=  1.0
//////////////////////////////////////////////////////////////////////////////
float get_include_prob()
{
   float flt_temp;

   flt_temp = static_cast<float>(rand());
   flt_temp = flt_temp / RANDOM_SCALE   // **** activate this for LINUX
   flt_temp = flt_temp / 32768.0f;

   return flt_temp;

}

//////////////////////////////////////////////////////////////////////////////
///  Determines whether logic program is generated randomly or read
///  from an input file.
//////////////////////////////////////////////////////////////////////////////
int determine_program_source()
{
   int source;
   cout << "\n \n \n ";
   cout << "-------------------------------------------------------------- \n";
   cout << " Enter Program Source: \n";
   cout << "     1 --  Input File  \n";
   cout << "     2 --  Random Generation \n";
   cout << "     3 --  Random Generation of Many Programs \n";
   cout << "     4 --  Random Generation Many..Comparing Semantics \n";
   cout << " ------------------------------------------------------------- \n";
   cout << "\n \n \n";
   cin >> source;
   return source;
}


////////////////////////////////////////////////////////////////////////////////
///  Bilattice routines...
///               
///               t 1                             Top 3
///             /   \                              /   \
///       2 Bottom  Top 3                       f 0   t  1
///            \    /                              \   /
///              f 0                              Bottom 2
///        
///          Truth Ordering                       Knowledge Ordering
///
///
///   lub_t:  returns the lub in the truth ordering lattice  (max so far)
///   glb_t:  returns the glb in the truth ordering lattice  (min so far)
///   lub_k:  returns the lub in the knowledge ordering lattice (max so far)
///
////////////////////////////////////////////////////////////////////////////////

int lub_t(int tval1, int tval2)

// MAX SO FAR IN THE TRUTH LATTICE
{
   int lub_val;

   lub_val = 0;

   switch (tval1)  {
       case 0:  { // FALSE with any other value produces that other value
                  return(tval2);
                  break;
                }
      
       case 2:  { // BOTTOM with TOP or TRUE returns TRUE 
                  if ((tval2 == 3) || (tval2 == 1)) 
                       lub_val = 1;
                  else  // RETURN BOTTOM
                       lub_val = 2;
                  break;
                 }

        case 3:  { // TOP with BOTTOM or TRUE returns TRUE
                   if ((tval2 == 2) || (tval2 == 1))
                       lub_val = 1;
                   else // RETURN TOP
                       lub_val = 3;
                   break;
                  }

        case 1:  { // TRUE with anything returns TRUE
                   lub_val = 1;
                   break;
                 }
       
     } // SWITCH
     return(lub_val);
} // LUB_T

///////////////////////////////////////////////////////////////////////////

int glb_t(int tval1, int tval2)

// MIN  SO FAR IN THE TRUTH LATTICE
{

   switch (tval1)  {
       case 0:  { // FALSE with any other value produces FALSE
                  return(0);
                  break;
                }
      
       case 2:  { // BOTTOM with FALSE or TOP returns FALSE
                  if ((tval2 == 0) || (tval2 == 3)) 
                       return(0);
                  else  // RETURN BOTTOM
                       return(2);
                  break;
                 }

        case 3:  { // TOP with BOTTOM or FALSE returns FALSE
                   if ((tval2 == 2) || (tval2 == 0))
                       return(0);
                   else // RETURN TOP
                       return(3);
                   break;
                  }

        case 1:  { // TRUE with any other value returns that value
                   return(tval2);
                   break;
                 }
       
     } // SWITCH
} // GLB_T

///////////////////////////////////////////////////////////////////////////

int lub_k(int tval1, int tval2)

// MAX  SO FAR IN THE KNOWLEDGE LATTICE
{

   switch (tval1)  {
       case 2:  { // BOTTOM with any other value produces that other value
                  return(tval2);
                  break;
                }
      
       case 0:  { // FALSE with TRUE or TOP returns TOP
                  if ((tval2 == 1) || (tval2 == 3)) 
                       return(3);
                  else  // RETURN FALSE 
                       return(0);
                  break;
                 }

        case 1:  { // TRUE with FALSE or TOP returns TOP
                   if ((tval2 == 0) || (tval2 == 3))
                       return(3);
                   else // RETURN TRUE
                       return(1);
                   break;
                  }

        case 3:  { // TOP always returns TOP
                   return(3);
                   break;
                 }
       
     } // SWITCH
} // LUB_K
       

///////////////////////////////////////////////////////////////////////////////
///  Produce Hash val for an atom.
///////////////////////////////////////////////////////////////////////////////
int        produce_hash_val(char instr[LONG_STRING_LENGTH], int instr_len)
{

    int num = 0;
    int i = 0;

    while (i < instr_len) {
//       cout << "instr[" << i << "] is..." << instr[i] << ";   number is..." << (int (instr[i]) )
//            << endl;
       num = num + (int(instr[i])); 
//       cout << "new number is..." << num;
       i++;
    } // WHILE

    return num;

}// PRODUCE_HASH_VAL



// -----------------------------------------------------------------------


char *read_rule(   istream& fin,
                   char readstr[EXTRA_LONG])
{

    int   i = 0;
    char  inchar = ' ';


//cout << "inside read_rule... \n \n";


    fin >> inchar;
//cout << "inchar is..   " << inchar << endl << endl;
    if (inchar != '@') {
       while ((inchar != '.') && (inchar != '@')){
//cout << "inchar is..   " << inchar << endl << endl;


            if (inchar != '\n' && inchar != ' ') {
                   readstr[i++] = inchar;
//cout << "readstr["<< i-1 << "  is..   " <<  readstr[i - 1] << endl << endl;

             } //IF
             fin >> inchar;
        } //WHILE

       readstr[i++] = '.';
       readstr[i] = '\0';
//cout << "about to return " << inchar << endl << endl;

       return (new char('.')); //TODO issue-1: memory leak!
    } //IF
    else {
//cout << "about to return " << inchar << endl << endl;
       return (new char('@')); //TODO issue-1: memory leak!
    } // ELSE

}  // FUNCTION READ_RULE

        
void show_rule(ostream& fout, char instr2[EXTRA_LONG])
{
       fout << instr2;
} 

// ------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
/// Returns a list of fullstring_class entities.
///////////////////////////////////////////////////////////////

void extract_atom_strings(const char extensional_rule[EXTRA_LONG],
         list_class<fullstring_class> *flist )   

{

    char               extracted_atom_str[STRING_LENGTH];
    char              *ptr, *clean_ptr;
    int                atom_num = 0;
    fullstring_class  *f_ptr;



    ptr = strtok( const_cast<char *>(extensional_rule), ")<-" );
    while (ptr != nullptr) {
           strcpy(extracted_atom_str, ""); 

           atom_num++;
           // APPEND A CLOSING RIGHT PAREN
           strcpy(extracted_atom_str, ptr);
           strcat(extracted_atom_str, ")" );

           if (atom_num > 2) {    // REMOVE LEADING COMMA
                clean_ptr = extracted_atom_str;
                clean_ptr++;
                strcpy(extracted_atom_str, clean_ptr);
           } //ELSE

           f_ptr = new fullstring_class(extracted_atom_str);

           flist->add_ptr(f_ptr);

           ptr = strtok(nullptr, ")<-." );

     }  //WHILE
} // EXTRACT_ATOM_STRINGS       

char *upper_string(char instr[STRING_LENGTH])   
{

           char      inchar;
           char* upperstring = new char[STRING_LENGTH]; //TODO: issue-1 memory leak

           int i = 0;

          inchar = instr[i];
          if (inchar != '\0') {
           do {
               upperstring[i++] = toupper(inchar);
               inchar = instr[i];
           } //DO par of DO-WHILE
           while (inchar != '\0'); 
      
          } // IF
          upperstring[i] = '\0';
        
          return (upperstring);
}
/////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////
void clear_screen(int num_blank_lines)
{
   for (int i=0; i < num_blank_lines; i++ )
        cout << endl; 
}

//////////////////////////////////////////////////////////////////////////
///
///
//////////////////////////////////////////////////////////////////////////

void display_menu()
{

      cout << "       *********************************************************** \n";
      cout << "       *                                                         * \n";
      cout << "       *     N  -- Nonmonotonic Update of Pos or Neg FACT        * \n";
      cout << "       *                                                         * \n";
      cout << "       *     R  -- Add an INTENSIONAL RULE to IDB                * \n";
      cout << "       *                                                         * \n";
      cout << "       *     S  -- Compute Current STATE of Knowledge Base       * \n";
      cout << "       *                                                         * \n";
      cout << "       *     F  -- Create a FILE of current STATE                * \n";
      cout << "       *                                                         * \n";
      cout << "       *     G  -- Create a FILE of current GOUND INSTANTIATION  * \n";
      cout << "       *                                                         * \n";
      cout << "       *     I  -- Create a FILE of current INTENSIONAL RULES    * \n";
      cout << "       *                                                         * \n";
      cout << "       *     L  -- Learn a TARGET PREDICATE using Induction      * \n";
      cout << "       *                                                         * \n";
      cout << "       *     Q  -- QUIT                                          * \n";
      cout << "       *                                                         * \n";
      cout << "       *********************************************************** \n";

}


////////////////////////////////////////////////////////////////////////////////
/// Returns a 1 if positions are equal..returns zero otherwise.
////////////////////////////////////////////////////////////////////////////////
int equal_positions(position_class *source_pos_ptr,
                     position_class *dest_pos_ptr)
{

    constant_class   *source_c_ptr;
    constant_class   *dest_c_ptr;
    char              source_str[STRING_LENGTH] = "";
    char              dest_str[STRING_LENGTH]   = "";

    source_c_ptr = source_pos_ptr->constantlist.get_first();
    dest_c_ptr = dest_pos_ptr->constantlist.get_first();

    int num_constants = source_pos_ptr->constantlist.get_length();
    double num_not_equal = 0.0;

    while ((source_c_ptr != nullptr)  &&
          ((num_not_equal/num_constants) <= EQUAL_FACTOR))  {
               strcpy(source_str, source_c_ptr->get_constant_symbol());
               strcpy(dest_str, dest_c_ptr->get_constant_symbol());

               if (strcmp(source_str,dest_str)!=0) {
                     num_not_equal++;            
                } // IF

               source_c_ptr = source_c_ptr->get_next_ptr();
               dest_c_ptr = dest_c_ptr->get_next_ptr();
    } //WHILE

   if  ((num_not_equal/num_constants) >  EQUAL_FACTOR)
               return 0;
   else
               return 1;

}//EQUAL_POSITIONS
