knowledge_base_class::knowledge_base_class()
{
        constantlist.set_first(NULL);
        constantlist.set_last(NULL);
        constantlist.set_num_entries(0);
        predexplist.set_first(NULL);
        predexplist.set_last(NULL);
        predexplist.set_num_entries(0);
        ground_instantiation = new logic_program_class();
        IDB = new int_ruleset_class(); 

} // CONSTRUCTOR for knowledge_base_class


///////////////////////////////////////////////////////////////////////////
///  Construct an intensional logic program by reading an input stream
///  of INTENSIONAL RULES
///////////////////////////////////////////////////////////////////////////
knowledge_base_class::knowledge_base_class(ifstream& edbfile, ifstream& idbfile)
{
   
        constant_class           *cons_ptr; 
        vertex_class             *v_ptr;
        char                      tempconstr[STRING_LENGTH];
        intensional_rule_class   *cur_i_ptr;

        constantlist.set_first(NULL);
        constantlist.set_last(NULL);
        constantlist.set_num_entries(0);
        predexplist.set_first(NULL);
        predexplist.set_last(NULL);
        predexplist.set_num_entries(0);

        ground_instantiation = new logic_program_class(edbfile);
        IDB = new int_ruleset_class(idbfile); 


       // CREATE LIST OF CONSTANTS USED IN INITIAL GROUND EDB 
       v_ptr = ground_instantiation->get_first_vertex();

       while (v_ptr != NULL) {
              cons_ptr =  v_ptr->get_first_atom_constant(); 

              while (cons_ptr != NULL) {
                  strcpy(tempconstr, (cons_ptr->get_constant_symbol()) );
                  add_constant_edb(tempconstr);
                  cons_ptr = cons_ptr->get_next_ptr();
              } //WHILE MORE CONSTANTS 

              v_ptr = v_ptr->get_next_ptr();

       } //WHILE MORE ATOMS 


       // AUGMENT THE EDB WITH THE INSTANTIATION OF EACH INTENSIONAL RULE
         cur_i_ptr = IDB->get_first_rule_ptr();   

         while (cur_i_ptr != NULL) {
                 augment_ground_instantiation_ptr(cur_i_ptr);
                 cur_i_ptr = cur_i_ptr->get_next_ptr();
         } //WHILE more intensional rules to instantiate


      // SCAN GROUND INSTANTIATION AND CREATE ALL CONSTANT
      //     DEPENDENCIES MANIFESTED AS APPEARANCES
       v_ptr = ground_instantiation->get_first_vertex();

       constant_class    *KB_cons_ptr = NULL;
       while (v_ptr != NULL) {

              cons_ptr =  v_ptr->get_first_atom_constant(); 
              KB_cons_ptr = find_constant(cons_ptr);

              while (cons_ptr != NULL) {

                 //FIND CONSTANT IN KB LIST
                  KB_cons_ptr = find_constant(cons_ptr);
                  KB_cons_ptr->add_constant_appearance(v_ptr);

                  cons_ptr = cons_ptr->get_next_ptr();
              } //WHILE MORE CONSTANTS 

              v_ptr = v_ptr->get_next_ptr();

       } //WHILE MORE ATOMS 

} // CONSTRUCTOR for knowledge_base_class


///////////////////////////////////////////////////////////////////////////
///  Construct an intensional logic program by reading an input stream
///  of INTENSIONAL RULES
///////////////////////////////////////////////////////////////////////////
knowledge_base_class::knowledge_base_class(ifstream& edbfile, ifstream& idbfile,
                                           ifstream& learnfile)
{
   
        constant_class           *cons_ptr; 
        vertex_class             *v_ptr;
        char                      tempconstr[STRING_LENGTH];
        intensional_rule_class   *cur_i_ptr;

        constantlist.set_first(NULL);
        constantlist.set_last(NULL);
        constantlist.set_num_entries(0);
        predexplist.set_first(NULL);
        predexplist.set_last(NULL);
        predexplist.set_num_entries(0);

        ground_instantiation = new logic_program_class(edbfile);
        IDB = new int_ruleset_class(idbfile, learnfile); 


       // CREATE LIST OF CONSTANTS USED IN INITIAL GROUND EDB 
       v_ptr = ground_instantiation->get_first_vertex();

       while (v_ptr != NULL) {
              cons_ptr =  v_ptr->get_first_atom_constant(); 

              while (cons_ptr != NULL) {
                  strcpy(tempconstr, (cons_ptr->get_constant_symbol()) );
                  add_constant_edb(tempconstr);
                  cons_ptr = cons_ptr->get_next_ptr();
              } //WHILE MORE CONSTANTS 

              v_ptr = v_ptr->get_next_ptr();

       } //WHILE MORE ATOMS 


       // AUGMENT THE EDB WITH THE INSTANTIATION OF EACH INTENSIONAL RULE
         cur_i_ptr = IDB->get_first_rule_ptr();   

         while (cur_i_ptr != NULL) {
                 augment_ground_instantiation_ptr(cur_i_ptr);
                 cur_i_ptr = cur_i_ptr->get_next_ptr();
         } //WHILE more intensional rules to instantiate


      // SCAN GROUND INSTANTIATION AND CREATE ALL CONSTANT
      //     DEPENDENCIES MANIFESTED AS APPEARANCES
       v_ptr = ground_instantiation->get_first_vertex();

       constant_class    *KB_cons_ptr = NULL;
       while (v_ptr != NULL) {

              cons_ptr =  v_ptr->get_first_atom_constant(); 
              KB_cons_ptr = find_constant(cons_ptr);

              while (cons_ptr != NULL) {

                 //FIND CONSTANT IN KB LIST
                  KB_cons_ptr = find_constant(cons_ptr);
                  KB_cons_ptr->add_constant_appearance(v_ptr);

                  cons_ptr = cons_ptr->get_next_ptr();
              } //WHILE MORE CONSTANTS 

              v_ptr = v_ptr->get_next_ptr();

       } //WHILE MORE ATOMS 

} // CONSTRUCTOR for knowledge_base_class


//--------------------------------------------------------------------------

void knowledge_base_class::add_constant_edb(char cons_str[STRING_LENGTH])
{
        constant_class  *cur_cons_ptr;
        char             tempstr[STRING_LENGTH];
        int              found = 0;

        cur_cons_ptr = constantlist.get_first();

        while ((cur_cons_ptr != NULL) && (!found)) {

               strcpy(tempstr, (cur_cons_ptr->get_constant_symbol()) );
               if ( (strcmp(cons_str,tempstr)) == 0 )
                        found = 1;
               cur_cons_ptr = cur_cons_ptr->get_next_ptr();
        } //WHILE

        // IF CONSTANT SYMBOL IS NOT IN LIST, CREATE ONE AND ADD IT
        if (!found) {
               cur_cons_ptr = new constant_class(cons_str);
               cur_cons_ptr->assign_val(constantlist.get_length());
               add_cons_ptr(cur_cons_ptr);
        } // IF
}
//--------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////
///  Searches for constant.
///  If found,
///       -  adds vertex appearance to its appearance list
///  else
///       -  creates a constant
///       -  adds to KB constantlist
///       -  adds vertex to new constant's appearance list
///
////////////////////////////////////////////////////////////////////////
void knowledge_base_class::add_constant_and_appearance
                           (char cons_str[STRING_LENGTH],
                            vertex_class *vapp_ptr)
{
        constant_class  *cur_cons_ptr;
        char             tempstr[STRING_LENGTH];
        int              found = 0;

        cur_cons_ptr = constantlist.get_first();

        while ((cur_cons_ptr != NULL) && (!found)) {

               strcpy(tempstr, (cur_cons_ptr->get_constant_symbol()) );
               if ( (strcmp(cons_str,tempstr)) == 0 )
                        found = 1;
               else {
                        cur_cons_ptr = cur_cons_ptr->get_next_ptr();
              }
        } //WHILE

        // IF CONSTANT SYMBOL IS NOT IN LIST, CREATE ONE AND ADD IT
        if (!found) {
               cur_cons_ptr = new constant_class(cons_str);
               cur_cons_ptr->assign_val(constantlist.get_length());
               add_cons_ptr(cur_cons_ptr);
        } // IF

        cur_cons_ptr->add_constant_appearance(vapp_ptr);

}

//__________________________________________________________________________

knowledge_base_class::~knowledge_base_class()
{
        predexplist.cleanup();
        constantlist.cleanup();
}

//__________________________________________________________________________
void knowledge_base_class::add_intensional_rule(intensional_rule_class *i_ptr)
{
     IDB->add_rule(i_ptr);

}

//__________________________________________________________________________
void knowledge_base_class::add_intensional_rule(char new_rule[EXTRA_LONG])
{
     IDB->add_rule(new_rule);

}

//__________________________________________________________________________
void knowledge_base_class::add_extensional_rule(char new_rule[EXTRA_LONG])
{
     ground_instantiation->add_extensional_rule(new_rule);

}

//__________________________________________________________________________
void knowledge_base_class::add_cons_ptr(constant_class *c_ptr) 
{
     constantlist.add_ptr(c_ptr); 
}

//__________________________________________________________________________
void knowledge_base_class::add_predicate_expression
                          (predicate_expression_class *pred_ptr)   
{
     predexplist.add_ptr(pred_ptr); 
}

//__________________________________________________________________________
void knowledge_base_class::add_predicate_expression(char 
                                  full_s[LONG_STRING_LENGTH])
{
     predicate_expression_class    *pred_ptr;
     
     pred_ptr = new predicate_expression_class(full_s);
     predexplist.add_ptr(pred_ptr); 
}
//__________________________________________________________________________

void knowledge_base_class::get_first_extensional_rule
                                      ( vertex_class *v_ptr,
                                             body_node_class *b_ptr)     
{
         v_ptr = ground_instantiation->get_first_vertex();
         b_ptr = v_ptr->get_first_body();
}

//__________________________________________________________________________
constant_class *knowledge_base_class::get_first_constant()
{
        return constantlist.get_first();
}

//__________________________________________________________________________
predicate_expression_class *knowledge_base_class::get_first_predicate_expression()   
{
         return predexplist.get_first();
}

//__________________________________________________________________________
intensional_rule_class *knowledge_base_class::get_first_intensional_rule()
{
         return IDB->get_first_rule_ptr();
}

//__________________________________________________________________________
void knowledge_base_class::output()
{
         cout << endl << endl << endl;
         cout << "INTENSIONAL RULE SET \n";
         cout << "-------------------- \n";
         IDB->output();
         cout << endl << endl << endl;
         cout << "CONSTANT LIST\n";
         cout << "-------------\n";
         constantlist.print();
         cout << endl << endl << endl;
         cout << "PREDICATE EXPRESSIONS: \n";
         cout << "---------------------- \n";
         predexplist.print();
         cout << endl << endl << endl;
         cout << "GROUND INSTANTIATION \n";
         cout << "-------------------- \n";
         ground_instantiation->output();

         cout << endl << endl << endl;
}

//______________________________________________________________________

void knowledge_base_class::output_constants()
{
         cout << endl << endl << endl;
         cout << "CONSTANTS OF THE GROUND INSTANTIATION: \n";
         cout << "------------------------------------- \n";
         constantlist.print();
         cout << endl << endl << endl;
}

//______________________________________________________________________

void knowledge_base_class::display_constant_appearances(ostream& fout)
{
         constant_class  *c_ptr;
 
         fout << endl << endl << endl;
         fout << "CONSTANTS with ATOM APPEARANCES IN GROUND INSTANTIATION: \n";
         fout << "-------------------------------------------------------- \n";

         c_ptr = get_first_constant();
         while (c_ptr != NULL) {
             c_ptr->display_appearance_list(fout);
             c_ptr = c_ptr->get_next_ptr();
         } // WHILE
         fout << endl << endl << endl;
}

//___________________________________________________________________

void knowledge_base_class::display_KB(ostream& fout)
{
         fout << endl << endl << endl;
         fout << "C U R R E N T   K N O W L E D G E   B A S E \n";
         fout << endl << endl << endl;
         fout << "INTENSIONAL RULE SET \n";
         fout << "-------------------- \n";
         IDB->display(fout);
         fout << endl << endl << endl;
         fout << "GROUND INSTANTIATION \n";
         fout << "--------------------\n";
         ground_instantiation->display_ground_instantiation(fout);
         fout << endl << endl << endl;
}


//////////////////////////////////////////////////////////////////////////
///  Creates n^k extensional (ground) rules from one intensional
///  rule *i_ptr, where n is the number of constants in the KB constantlist
///  and k is the number of different variables in the intensional
///  rule *i_ptr  (the length of the variable list of i_ptr).
///
///  Three steps are repeated until all n^k ground rules are created.
///    1.  advance the instantiation of the variables so each variable
///        points to an updated constant with which to be replaced
///    2.  create an EXTRA_LONG string form of ground rule from these
///        substitutions
///    3.  add the ground rule to logic_program_class "ground_instantiation"
///
///
//////////////////////////////////////////////////////////////////////////

void knowledge_base_class::augment_ground_instantiation_ptr
                      (intensional_rule_class  *i_ptr)
{
     int        done_instantiating = 0;
     char       ground_rule[EXTRA_LONG];

     initialize_instantiated_constant_ptrs(i_ptr);

     while (!done_instantiating) {
          
           // FORM A GROUND RULE OF LENGTH 'EXTRA_LONG'
            strcpy(ground_rule, "");
            strcpy(ground_rule, catenate_ground_rule(i_ptr) );

           // ADD NEW GROUND RULE TO LOGIC PROGRAM : "ground_instantiation"
            ground_instantiation->add_extensional_rule(ground_rule);
 
           // REINSTANTIATE VARIABLES
            done_instantiating = advance_instantiated_constant_ptrs(i_ptr);

     } //WHILE more producible ground rules exist

}//AUGMENT_GROUND_INSTANTIATION

//----------------------------------------------------------------------
void knowledge_base_class::initialize_instantiated_constant_ptrs
               (intensional_rule_class *i_ptr)
{

    variable_class     *var_ptr;
    constant_class     *first_cons_ptr;
 
    first_cons_ptr = get_first_constant();
    var_ptr = i_ptr->get_first_variable_ptr();

    while (var_ptr != NULL) {
       var_ptr->assign_instantiated_constant_ptr(first_cons_ptr);
       var_ptr = var_ptr->get_next_ptr();
    } //WHILE

} //initialize_instantiated_constant_ptrs

//----------------------------------------------------------------------

int  knowledge_base_class::advance_instantiated_constant_ptrs
               (intensional_rule_class *i_ptr)
{

    variable_class     *var_ptr;
    variable_class     *col_var_ptr;
    constant_class     *first_constant_ptr;
    int                 column_NULL = 1;
    int                 finished_instantiating = 0;
 
    first_constant_ptr = get_first_constant();
    col_var_ptr = i_ptr->get_first_variable_ptr();

    while ((column_NULL) && (col_var_ptr != NULL))  {
         column_NULL =  col_var_ptr->advance_instantiated_constant_ptr
                                     (first_constant_ptr);
         col_var_ptr = col_var_ptr->get_next_ptr();
    }//WHILE

    if ((col_var_ptr == NULL) && (column_NULL == 1)) {
         finished_instantiating = 1; 
    } // IF

    return finished_instantiating;

} //advance_instantiated_constant_ptrs


//----------------------------------------------------------------------

constant_class *knowledge_base_class::get_inst_constant_ptr
               (intensional_rule_class *i_ptr,
                variable_class  *source_var_ptr)
{
     char              source_var_str[STRING_LENGTH];     
     char              dest_var_str[STRING_LENGTH];     
     int               found = 0;

     constant_class   *c_ptr;
     variable_class   *var_ptr;

     strcpy(source_var_str, "");
     strcpy(source_var_str, source_var_ptr->get_variable_symbol() );

     //TRAVERSE i_ptr's VARIABLE LIST TO FIND THE MATCHING VAR SYMBOL OF
     //   source_var_ptr

     var_ptr = i_ptr->get_first_variable_ptr();
     while ((var_ptr != NULL) && (!found)) {
           strcpy(dest_var_str, "");
           strcpy(dest_var_str, var_ptr->get_variable_symbol());
           if ( (strcmp(source_var_str, dest_var_str) == 0 ) )
                   found = 1;
           else
                   var_ptr = var_ptr->get_next_ptr();

     } // WHILE not found
 
     if (var_ptr != NULL)
             return var_ptr->get_instantiated_constant_ptr();
     else
             return NULL;

     
} // get_inst_constant_ptr
       
//_________________________________________________________________________ 

char *knowledge_base_class::catenate_ground_rule(intensional_rule_class *i_ptr)
{

     char   new_ground_rule[EXTRA_LONG];
                                           
     predicate_expression_class  *pred_ptr;
     variable_class              *pred_var_ptr;
     constant_class              *pred_inst_var_const_ptr;

     pred_ptr = i_ptr->get_first_predexp_ptr();
     strcpy(new_ground_rule, "");

     // CONNECT INTENSIONAL HEAD
     if (pred_ptr->get_IS_NEGATIVE()==1)
         strcat(new_ground_rule, "~");
     strcat(new_ground_rule, pred_ptr->get_predicate_symbol() );
     strcat(new_ground_rule, "(");

     //TRAVERSE THE PREDICATE EXPRESSIONS's VARIABLE LIST
     //    ATTACH THE INSTANTIATED CONSTANTS TO THE GROUND RULE

     pred_var_ptr = pred_ptr->get_first_variable();
     while ( pred_var_ptr != NULL ) {
         pred_inst_var_const_ptr = 
                get_inst_constant_ptr(i_ptr, pred_var_ptr);

         if (pred_inst_var_const_ptr != NULL)
         //ATTACH THE NEWLY FOUND CONSTANT 
           strcat(new_ground_rule, 
                     pred_inst_var_const_ptr->get_constant_symbol() );

         pred_var_ptr = pred_var_ptr->get_next_ptr();
        if (pred_var_ptr != NULL)
                 strcat(new_ground_rule, ",");
         
     } //WHILE more VARIABLES IN THE CURRENT PRED EXP
     strcat(new_ground_rule, ")");
     strcat(new_ground_rule, "<--");

     pred_ptr = pred_ptr->get_next_ptr();

     // CONSTRUCT GROUND RULE BODY
     while (pred_ptr != NULL) {

         if (pred_ptr->get_IS_NEGATIVE()==1)
             strcat(new_ground_rule, "~");

         strcat(new_ground_rule, pred_ptr->get_predicate_symbol() );
         strcat(new_ground_rule, "(");

        //TRAVERSE THE PREDICATE EXPRESSIONS's VARIABLE LIST
        //    ATTACH THE INSTANTIATED CONSTANTS TO THE GROUND RULE

         pred_var_ptr = pred_ptr->get_first_variable();
         while ( pred_var_ptr != NULL ) {
             pred_inst_var_const_ptr = 
                    get_inst_constant_ptr(i_ptr, pred_var_ptr);
            //ATTACH THE NEWLY FOUND CONSTANT 
             strcat(new_ground_rule, 
                     pred_inst_var_const_ptr->get_constant_symbol() );


             pred_var_ptr = pred_var_ptr->get_next_ptr();
             if (pred_var_ptr != NULL)
                     strcat(new_ground_rule, ",");

         } //WHILE more VARIABLES IN THE CURRENT PRED EXP

         strcat(new_ground_rule, ")");

         pred_ptr = pred_ptr->get_next_ptr();

         if (pred_ptr != NULL)
                strcat(new_ground_rule, ",");

   } //WHILE there are more subgoals in BODY

   strcat(new_ground_rule, ".");

   return new_ground_rule;

}


/////////////////////////////////////////////////////////////////////////////////////
///  Augment the ground_instantiation with a character string version of int rule.
/////////////////////////////////////////////////////////////////////////////////////
void knowledge_base_class::augment_ground_instantiation
                                 (char new_intrule[EXTRA_LONG])
{
       intensional_rule_class  *i_ptr;
  
       i_ptr = new intensional_rule_class(new_intrule);
       augment_ground_instantiation_ptr(i_ptr); 
}


/////////////////////////////////////////////////////////////////////////////////////
///  Compute the stable model of the current ground instantiation
/////////////////////////////////////////////////////////////////////////////////////
void knowledge_base_class::compute_current_state()
{
         ground_instantiation->update_state();  
}

/////////////////////////////////////////////////////////////////////////////////////
///  Display the stable model of the current ground instantiation
/////////////////////////////////////////////////////////////////////////////////////
void knowledge_base_class::show_current_state(ostream& fout)
{
         ground_instantiation->show_state(fout);
}

/////////////////////////////////////////////////////////////////////////////////////
///  creates a file of TRUE FACTS according to the current knowledge base state
/////////////////////////////////////////////////////////////////////////////////////
void knowledge_base_class::create_background_knowledge_file(char filename[STRING_LENGTH])
{
         ofstream   outfile;

         outfile.open(filename);
         ground_instantiation->print_truth_atoms(outfile, 1);
         ground_instantiation->print_truth_atoms(outfile, 0);
         outfile << "@@@@@@@@@@@@@@@@@@@@" << endl;
         outfile.close();
}

/////////////////////////////////////////////////////////////////////////////////////
///  creates a file of the current GROUND_INSTANTIATION
/////////////////////////////////////////////////////////////////////////////////////
void knowledge_base_class::create_ground_instantiation_file
                         (char filename[STRING_LENGTH])
{
         ofstream   outfile;

         outfile.open(filename);
         ground_instantiation->display_ground_instantiation(outfile);
         outfile.close();
}
/////////////////////////////////////////////////////////////////////////////////////
///  creates a file of the current INTENSIONAL RULE SET
/////////////////////////////////////////////////////////////////////////////////////
void knowledge_base_class::create_intrule_set_file
                         (char filename[STRING_LENGTH])
{
         ofstream   outfile;

         outfile.open(filename);
         IDB->display(outfile);
         outfile.close();
}


////////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
void knowledge_base_class::nonmonotonically_update(istream& fin)
{
      add_fact_KB(fin);
      ground_instantiation->update_state();

}

///////////////////////////////////////////////////////////////////////////
///  Updates the Knowledge Base by reading one extensional fact
///  from input stream "fin".
///
///    1.  Read the string from input stream
///    2.  Update the ground_instantiation (logic_program_class)
///    3.  Construct an ATOM (of type atom_class) from string
///    4.  For each constant in the ATOM:
///          If the constant is NEW (doesn't exist in KB  
///              -- create a new constant
///              -- add the constant to KB's constantlist
///              -- augment the ground instantiation with
///                 instantiated intensional rules using the new constant
/// 
///////////////////////////////////////////////////////////////////////////
void knowledge_base_class::add_fact_KB(istream& infile)
{
       

   char                           fact_str[LONG_STRING_LENGTH];    
   char                           full_string[ EXTRA_LONG];  
   fullstring_class              *f_ptr;
   list_class<fullstring_class>  *flist;
   char                           gochar = '.';
   atom_class                    *a_ptr;
   constant_class                *c_ptr;
   constant_class                *new_c_ptr;
   constant_class                *find_c_ptr;
   char                           new_c_string[STRING_LENGTH];
   vertex_class                  *vertex_app_ptr;

   // READ THE STRING VERSION OF THE FACT FROM THE INPUT STREAM
   cout << endl << endl <<"Enter new fact.\n ";
   gochar = read_rule(infile, full_string);
   cout << endl;


    if (gochar == '.') {

       // CREATE A LIST OF FULLSTRING VERSIONS OF EXTENSIONAL RULE'S ATOMS
        flist = new list_class<fullstring_class>();
        extract_atom_strings(full_string, flist);

       // EXTRACT THE FACT ..
        f_ptr = flist->get_first();
        strcpy(fact_str,f_ptr->get_fullstring_symbol());         
//cout << "Inside KB:add_fact...full_string is.. \n";
//cout << fact_str << endl << endl;

        // ADD FACT TO GROUND INSTANTIATION in vertex *vertex_app_ptr
        vertex_app_ptr = 
             ground_instantiation->
                     add_fact(fact_str, f_ptr->get_IS_NEGATIVE());
//cout << "after adding the fact to the ground_instantiation... it is..\n";
//ground_instantiation->output_graph();
//cout << "#######################333333333333333 \n";

       // CONSTRUCT AN ATOM FROM THE FACT
        a_ptr = new atom_class(fact_str);

       // TRAVERSE THE ATOM's CONSTANTLIST TO FIND NEW CONSTANTS
        c_ptr = a_ptr->get_first_constant();

        while (c_ptr != NULL) {
              find_c_ptr = NULL;           // INITIALIZE
              find_c_ptr = find_constant(c_ptr); 

              if (find_c_ptr == NULL) {  
                  //CONSTANT DOES NOT EXIST IN KB

                   strcpy(new_c_string, "");
                   strcpy(new_c_string, c_ptr->get_constant_symbol() ); 
                   new_c_ptr = new constant_class(new_c_string);
                   new_c_ptr->add_constant_appearance(vertex_app_ptr);

                   // ADD NEW CONSTANT STRING TO KB CONSTANTLIST
                   add_cons_ptr(new_c_ptr);

                  // AUGMENT THE GROUND INSTANTIATION WITH INTENSIONALS 
                  //    INSTANTIATED WITH NEW CONSTANT AND COMBINATIONS   
                   augment_GI_new_constant(new_c_ptr);
              } //IF
              else {
                  // ADD APPEARANCE TO FOUND CONSTANT IN KB
                   find_c_ptr->add_constant_appearance(vertex_app_ptr);
              }

            // ADVANCE TO THE NEXT CONSTANT IN THE ATOM

            c_ptr = c_ptr->get_next_ptr();

        } // WHILE more constants in ATOM's list

   } // IF gochar = .
   else {
       cout << "ERROR in ADD_FACT..invalid input...don't forget '.' ! " << endl << endl;
       exit(my_exit_status);
   } //ELSE

   flist->cleanup();

}// KB:ADD_FACT




////////////////////////////////////////////////////////////////////////
/// Traverses the KB constantlist to find the same constant string
///  as the string contained in *source_c_ptr.
///  Returns the pointer to the constant having the same string.
///  If one doesn't exist, it returns NULL.
///////////////////////////////////////////////////////////////////////

constant_class  *knowledge_base_class::find_constant(constant_class *source_c_ptr)
{
    constant_class    *c_ptr;
    char               source_str[STRING_LENGTH];
    char               dest_str[STRING_LENGTH];
    int                found = 0;

    strcpy(source_str, source_c_ptr->get_constant_symbol());
    c_ptr = get_first_constant();  //INITIALIZE TO FIRST CONSTANT IN KB

    while ((c_ptr != NULL) && (!found)) {
        strcpy(dest_str, "");
        strcpy(dest_str, c_ptr->get_constant_symbol());
        if  ( strcmp(source_str, dest_str) == 0 )
                found = 1;
        else
                 c_ptr = c_ptr->get_next_ptr();
    } //WHILE
    return c_ptr;
} //FIND_CONSTANT



//////////////////////////////////////////////////////////////////////////
///  Creates (n+1)^k - n^k extensional (ground) rules from each intensional
///  in the KB intruleset, where n is the old number of constants in the KB constantlist
///  and k is the number of different variables in any given intensional
///  rule *i_ptr  (the length of the variable list of i_ptr).
///
///  Three steps are repeated until all ground rules are created.
///    1.  advance the instantiation of the variables so each variable
///        points to an updated constant with which to be replaced
///    2.  IGNORE ANY INSTANTIATION THAT DOES NOT INCLUDE THE NEW CONSTANT
///    3.  create an EXTRA_LONG string form of ground rule from these
///        substitutions
///    4.  add the ground rule to logic_program_class "ground_instantiation"
///
///
//////////////////////////////////////////////////////////////////////////

void knowledge_base_class::augment_GI_new_constant
                      (constant_class  *new_c_ptr)
{
     int                       done_instantiating = 0;
     char                      ground_rule[EXTRA_LONG];
     intensional_rule_class   *i_ptr;

   
  i_ptr  = get_first_intensional_rule();

  while (i_ptr != NULL) {
     done_instantiating = 0;

//cout<< "inside WHILE of augment GI the rule is i_ptr" << i_ptr << endl;
//i_ptr->display_intensional_rule(cout);
//cout << endl << endl;

     initialize_instantiated_constant_ptrs(i_ptr);

     while (!done_instantiating) {

        if (new_constant_in_instantiation(i_ptr, new_c_ptr)==1) {
           // FORM A GROUND RULE OF LENGTH 'EXTRA_LONG'
//cout << "inside IF because had new constnat..\n";
            strcpy(ground_rule, "");
            strcpy(ground_rule, catenate_ground_rule(i_ptr) );

           // ADD NEW GROUND RULE TO LOGIC PROGRAM : "ground_instantiation"
            ground_instantiation->add_extensional_rule(ground_rule);
//cout << "JENNIFER \n";
//cout << ground_rule << endl << endl;

        } // IF...instantiation includes new constant

 
        // REINSTANTIATE VARIABLES
        done_instantiating = advance_instantiated_constant_ptrs(i_ptr);

     } //WHILE more producible ground rules exist

     i_ptr = i_ptr->get_next_ptr();
  }//WHILE MORE INTENSIONAL RULES IN KB RULE SET

}//AUGMENT_GI_NEW_CONSTANT

//////////////////////////////////////////////////////////////////////////
/// Returns a 1 if one of the variables in intensional rule i_ptr
///   is instantiated to constant new_c_ptr
/////////////////////////////////////////////////////////////////////////

int knowledge_base_class::new_constant_in_instantiation
                  (intensional_rule_class *i_ptr, 
                   constant_class         *new_c_ptr) 
{

    int               found = 0; 
    variable_class   *var_ptr;
    constant_class   *instantiation_c_ptr;
    char              source_string[STRING_LENGTH];
    char              dest_string[STRING_LENGTH];


    strcpy(source_string, new_c_ptr->get_constant_symbol());

    //TRAVERSE THE VARIABLE LIST OF INT RULE i_ptr TO FIND THE NEW CONSTANT
    //  INSTANTIATION

    var_ptr = i_ptr->get_first_variable_ptr();

//cout << "inside  new_constant_in_instantiation  i_ptr is..\n";
//i_ptr->display_intensional_rule(cout);
//cout << endl;
//cout << "new_c_ptr points to";
//new_c_ptr->output();
//cout << endl << endl;

    while ((!found) && (var_ptr != NULL)) {

        instantiation_c_ptr = var_ptr->get_instantiated_constant_ptr(); 
        strcpy(dest_string, instantiation_c_ptr->get_constant_symbol());
//cout << "source string is.." << source_string << endl;
//cout << "dest string is.." << dest_string << endl;


       
        if (strcmp(source_string, dest_string) == 0)  {
             found = 1; 
//cout << "found is..." << found << endl;
        } //
        else  {
             var_ptr = var_ptr->get_next_ptr();
        }
    } // WHILE not found AND more vars in int rule i_ptr
    
    return found;

} //NEW_CONSTANT_IN_INSTANTIATION
