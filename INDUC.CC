inductive_engine_class::inductive_engine_class()
{
        target_predicate_expression_ptr = NULL;
        positive_examples= NULL;
        negative_examples= NULL;          
        background_knowledge = NULL;     
} // CONSTRUCTOR for inductive_engine_class


///////////////////////////////////////////////////////////////////////////
///  Construct an induction engine class by reading in the appropriate
///  input streams:  positive examples, negative examples, and 
///  background knowledge.
///////////////////////////////////////////////////////////////////////////
inductive_engine_class::inductive_engine_class(ifstream& posexamplefile,
                               ifstream& negexamplefile,
                               ifstream& backgroundknowfile)
                                 
{
   
        positive_examples = new example_set_class(posexamplefile);
        negative_examples = new example_set_class(negexamplefile);
        background_knowledge = new background_knowledge_class(backgroundknowfile);

        positive_examples->name_example_variables();

       //CONSTRUCT TARGET PREDICATE
         char                          pred_symb[STRING_LENGTH];
         list_class<variable_class>    target_var_list;
         variable_class                *var_ptr; 
         position_class                *pos_ptr;
         char                           var_name_str[STRING_LENGTH] = "";
         atom_class                    *first_pos_examp_ptr;
         
         //CONSTRUCT VARIABLE LIST 
         pos_ptr = get_first_positive_example_position();
         while (pos_ptr != NULL) {
                var_name_str[0] = pos_ptr->get_variable_name();
                var_name_str[1] = '\0';
                var_ptr = new variable_class(var_name_str);
                target_var_list.add_ptr(var_ptr);

                pos_ptr = pos_ptr->get_next_ptr();
         } // WHILE

         //GET THE TARGET PREDICATE SYMBOL
         first_pos_examp_ptr = positive_examples->get_first_atom_ptr();         
         strcpy(pred_symb,  first_pos_examp_ptr->get_predicate_symbol());          

         //CALL THE CONSTRUCTOR FOR TARGET PREDICATE
         target_predicate_expression_ptr = new predicate_expression_class
                                                  (target_var_list, pred_symb);

          perform_predicate_ranking(DEFAULT_PREDRANK_ALGO); 

} // CONSTRUCTOR for inductive_engine_class

//--------------------------------------------------------------------------

inductive_engine_class::~inductive_engine_class()
{
        target_predicate_expression_ptr->clear();
        target_predicate_expression_ptr = NULL;

        positive_examples->clear();
        positive_examples= NULL;

        negative_examples->clear();
        negative_examples= NULL;

        background_knowledge->clear();
        background_knowledge= NULL;

} // CONSTRUCTOR for inductive_engine_class


//--------------------------------------------------------------------------

void inductive_engine_class::add_POSexample(atom_class *a_ptr)
{
     positive_examples->add_atom_example(a_ptr);
     positive_examples->add_log_example(a_ptr);

}
//--------------------------------------------------------------------------

void inductive_engine_class::add_POSexample(char new_example[LONG_STRING_LENGTH])
{
     positive_examples->add_atom_example(new_example);
     positive_examples->add_log_example(new_example);

}
//--------------------------------------------------------------------------

void inductive_engine_class::add_NEGexample(atom_class *a_ptr)
{
     negative_examples->add_atom_example(a_ptr);
     negative_examples->add_log_example(a_ptr);

}
//--------------------------------------------------------------------------

void inductive_engine_class::add_NEGexample(char new_example[LONG_STRING_LENGTH])
{
     negative_examples->add_atom_example(new_example);
     negative_examples->add_log_example(new_example);

}
//--------------------------------------------------------------------------

atom_class *inductive_engine_class::get_first_negative_example()     
{
     return negative_examples->get_first_atom_ptr();  

}
//--------------------------------------------------------------------------

atom_class *inductive_engine_class::get_first_positive_example()     
{
     return positive_examples->get_first_atom_ptr();  

}
//--------------------------------------------------------------------------

position_class  *inductive_engine_class::get_first_positive_example_position()     
{
     return positive_examples->get_first_position_ptr();

}
//--------------------------------------------------------------------------

position_class  *inductive_engine_class::get_first_negative_example_position()     
{
     return negative_examples->get_first_position_ptr();

}
//--------------------------------------------------------------------------

predicate_log_class  *inductive_engine_class::get_first_background_predlog_ptr()   
{
     return background_knowledge->get_first_predlog_ptr(); 

}
//--------------------------------------------------------------------------
char *inductive_engine_class::get_target_predicate_symbol()
{
        char    tempstr[STRING_LENGTH];

        strcpy(tempstr, target_predicate_expression_ptr->get_predicate_symbol()); 
        return tempstr;
}

//--------------------------------------------------------------------------
char *inductive_engine_class::get_target_predicate_fullstring()
{
        char    tempstr[LONG_STRING_LENGTH];

        strcpy(tempstr, target_predicate_expression_ptr->get_fullstring()); 
        return tempstr;
}

//__________________________________________________________________________
void inductive_engine_class::output()
{
         cout << endl << endl << endl;
         cout << endl << endl << endl;
         cout << "TARGET PREDICATE EXPRESSION: \n";
         cout << "---------------------------- \n";
         target_predicate_expression_ptr->output();
         cout << endl << endl << endl;
         cout << "POSITIVE EXAMPLE SET: \n";
         cout << "---------------------\n";
         positive_examples->output();
         cout << endl << endl << endl;
         cout << "NEGATIVE EXAMPLE SET: \n";
         cout << "---------------------\n";
         negative_examples->output();
         cout << endl << endl << endl;
         cout << "BACKGROUND KNOWLEDGE FACTS:  \n";
         cout << "----------------------------- \n";
         background_knowledge->output();
         cout << endl << endl << endl;
         cout << endl << endl << endl;
}

//______________________________________________________________________

void inductive_engine_class::display(ostream& fout)
{
         fout << endl << endl << endl;
         fout << "C U R R E N T   I N D U C T I V E   E N G I N E  \n";
         fout << endl << endl << endl;
         fout << "TARGET PREDICATE EXPRESSION: \n";
         fout << "---------------------------- \n";
         target_predicate_expression_ptr->display(fout);
         fout << endl << endl << endl;
         fout << "POSITIVE EXAMPLE SET: \n";
         fout << "---------------------\n";
         positive_examples->display(fout);
         fout << endl << endl << endl;
         fout << "NEGATIVE EXAMPLE SET: \n";
         fout << "---------------------\n";
         negative_examples->display(fout);
         fout << endl << endl << endl;
         fout << "BACKGROUND KNOWLEDGE FACTS:  \n";
         fout << "----------------------------- \n";
         background_knowledge->display(fout);
         fout << endl << endl << endl;
         fout << endl << endl << endl;
}

//______________________________________________________________________

void inductive_engine_class::display_example_set(ostream& fout)
{
         fout << endl << endl << endl;
         fout << "E X A M P L E   S E T S : \n";
         fout << endl << endl << endl;
         fout << "POSITIVE EXAMPLE SET: \n";
         fout << "---------------------\n";
         positive_examples->display(fout);
         fout << endl << endl << endl;
         fout << "NEGATIVE EXAMPLE SET: \n";
         fout << "---------------------\n";
         negative_examples->display(fout);
         fout << endl << endl << endl;
         fout << endl << endl << endl;
}

//______________________________________________________________________

void inductive_engine_class::display_positive_examples(ostream& fout)
{
         fout << endl << endl << endl;
         fout << "P O S I T I V E    E X A M P L E   S E T : \n";
         fout << endl << endl << endl;
         positive_examples->display(fout);
         fout << endl << endl << endl;
         fout << endl << endl << endl;
}

//______________________________________________________________________

void inductive_engine_class::display_negative_examples(ostream& fout)
{
         fout << endl << endl << endl;
         fout << "N E G A T I V E    E X A M P L E   S E T : \n";
         fout << endl << endl << endl;
         negative_examples->display(fout);
         fout << endl << endl << endl;
         fout << endl << endl << endl;
}


////////////////////////////////////////////////////////////////////////////
/// RANK ALGORITHM 1:  Simple membership
/// ------------------------------------
///   For each positive example e+
///       For each constant c appearing in e+
///           For each predicate_log_class p in BACKGROUND
///                 If c appears anywhere (any position any spot) in  p 
///                           RANK(p)++
///
////////////////////////////////////////////////////////////////////////////

void inductive_engine_class::rank_simple_membership_pos_only()
{
     constant_class        *example_cur_constant_ptr;

     position_class        *example_cur_position_ptr;
     position_class        *background_cur_position_ptr;
     predicate_log_class   *background_cur_predlog_ptr;


    // TRAVERSE POSITIVE EXAMPLES 
     example_cur_position_ptr = get_first_positive_example_position();
     
     while (example_cur_position_ptr != NULL) {
           example_cur_constant_ptr = example_cur_position_ptr->
                                              get_first_poscon_ptr();

           while (example_cur_constant_ptr != NULL) {
                
                background_cur_predlog_ptr = get_first_background_predlog_ptr();
                while (background_cur_predlog_ptr != NULL) {
                       if ( (background_cur_predlog_ptr->has_constant
                           (example_cur_constant_ptr)) != 0)
                                background_cur_predlog_ptr->increment_rank();

                       background_cur_predlog_ptr = background_cur_predlog_ptr->
                                                   get_next_ptr(); 
                }// WHILE there are more meshes in the BACK KNOW
           


                example_cur_constant_ptr  = example_cur_constant_ptr->
                                                   get_next_ptr(); 
           } //WHILE more constants in this position of the pos example sets

           example_cur_position_ptr = example_cur_position_ptr->get_next_ptr();
     } // WHILE  there are more positions in the example set

    // *******************************************************************

} // rank_simple_membership_pos_only

////////////////////////////////////////////////////////////////////////////
/// RANK ALGORITHM 2:  Simple membership
/// ------------------------------------
///   For each positive example e+
///       For each constant c appearing in e+
///           For each predicate_log_class p in BACKGROUND
///                 If c appears anywhere (any position any spot) in  p 
///                           RANK(p)++
///
///   For each negative example e-
///       For each constant c appearing in e-
///           For each predicate_log_class p in BACKGROUND
///                 If c appears anywhere (any position any spot) in  p 
///                           RANK(p)--
///
////////////////////////////////////////////////////////////////////////////

void inductive_engine_class::rank_simple_membership()
{
     constant_class        *example_cur_constant_ptr;

     position_class        *example_cur_position_ptr;
     position_class        *background_cur_position_ptr;
     predicate_log_class   *background_cur_predlog_ptr;


    // TRAVERSE POSITIVE EXAMPLES 
     example_cur_position_ptr = get_first_positive_example_position();
     
     while (example_cur_position_ptr != NULL) {
           example_cur_constant_ptr = example_cur_position_ptr->
                                              get_first_poscon_ptr();

           while (example_cur_constant_ptr != NULL) {
                
                background_cur_predlog_ptr = get_first_background_predlog_ptr();
                while (background_cur_predlog_ptr != NULL) {
                       if ( (background_cur_predlog_ptr->has_constant
                           (example_cur_constant_ptr)) != 0)
                                background_cur_predlog_ptr->increment_rank();

                       background_cur_predlog_ptr = background_cur_predlog_ptr->
                                                   get_next_ptr(); 
                }// WHILE there are more meshes in the BACK KNOW
           


                example_cur_constant_ptr  = example_cur_constant_ptr->
                                                   get_next_ptr(); 
           } //WHILE more constants in this position of the pos example sets

           example_cur_position_ptr = example_cur_position_ptr->get_next_ptr();
     } // WHILE  there are more positions in the example set

    // *******************************************************************


    // TRAVERSE NEGATIVE EXAMPLES 
     example_cur_position_ptr = get_first_negative_example_position();
     
     while (example_cur_position_ptr != NULL) {
           example_cur_constant_ptr = example_cur_position_ptr->
                                              get_first_poscon_ptr();

           while (example_cur_constant_ptr != NULL) {
                
                background_cur_predlog_ptr = get_first_background_predlog_ptr();
                while (background_cur_predlog_ptr != NULL) {
                       if ( (background_cur_predlog_ptr->has_constant
                           (example_cur_constant_ptr)) != 0)
                                background_cur_predlog_ptr->decrement_rank();

                       background_cur_predlog_ptr = background_cur_predlog_ptr->
                                                   get_next_ptr(); 
                }// WHILE there are more meshes in the BACK KNOW
           


                example_cur_constant_ptr  = example_cur_constant_ptr->
                                                   get_next_ptr(); 
           } //WHILE more constants in this position of the pos example sets

           example_cur_position_ptr = example_cur_position_ptr->get_next_ptr();
     } // WHILE  there are more positions in the example set

}

////////////////////////////////////////////////////////////////////////////
/// RANK ALGORITHM 3:  Num Times Found Each Position Positive Examples ONLY
/// ------------------------------------------------------------------------
///   For each positive example e+
///       For each constant c appearing in e+
///           For each predicate_log_class p in BACKGROUND
///                For each position POS of p 
///                           RANK(p)+= number times c appears in POS
///
///
///  In essence,      RANK(p) = total appearances of e+ constants
////////////////////////////////////////////////////////////////////////////

void inductive_engine_class::rank_num_times_found_each_pos_pos_only()
{
     constant_class        *example_cur_constant_ptr;

     position_class        *example_cur_position_ptr;
     position_class        *background_cur_position_ptr;
     predicate_log_class   *background_cur_predlog_ptr;
     int                    number_occurences = 0;


    // TRAVERSE POSITIVE EXAMPLES 
     example_cur_position_ptr = get_first_positive_example_position();
     
     while (example_cur_position_ptr != NULL) {
           example_cur_constant_ptr = example_cur_position_ptr->
                                              get_first_poscon_ptr();

           while (example_cur_constant_ptr != NULL) {
                
                background_cur_predlog_ptr = get_first_background_predlog_ptr();
                while (background_cur_predlog_ptr != NULL) {


                    background_cur_position_ptr = background_cur_predlog_ptr->
                              get_first_pos_ptr();

                    while (background_cur_position_ptr != NULL) {
                       number_occurences = 0;

                       // INCREASE THE RANK BY NUM TIMES CONSTANT FOUND THERE   
                       number_occurences = 
                           background_cur_position_ptr->number_times_constant_found
                                                 (example_cur_constant_ptr); 
                       background_cur_predlog_ptr->increase_rank(number_occurences);

                              
                       background_cur_position_ptr = background_cur_position_ptr->
                                   get_next_ptr();
                    } // WHILE more positions in current predlog of bkg

                       background_cur_predlog_ptr = background_cur_predlog_ptr->
                                                   get_next_ptr(); 
                }// WHILE there are more meshes in the BACK KNOW
           


                example_cur_constant_ptr  = example_cur_constant_ptr->
                                                   get_next_ptr(); 
           } //WHILE more constants in this position of the pos example sets

           example_cur_position_ptr = example_cur_position_ptr->get_next_ptr();
     } // WHILE  there are more positions in the example set

    // *******************************************************************


} // RANK NUMBER TIMES FOUND IN PREDLOG.. POS ONLY



////////////////////////////////////////////////////////////////////////////
/// RANK ALGORITHM 4:  Num Times Found Each Position
/// --------------------------------------------------
///   For each positive example e+
///       For each constant c appearing in e+
///           For each predicate_log_class p in BACKGROUND
///                For each position POS of p 
///                           RANK(p)+= number times c appears in POS
///
///   For each negative example e-
///       For each constant c appearing in e-
///           For each predicate_log_class p in BACKGROUND
///                 For each position POS of p
///                           RANK(p)-= number times c appears in POS
///
///  In essence,      RANK(p) = total appearances of e+ constants MINUS
///                             total appearances of e- constants
////////////////////////////////////////////////////////////////////////////

void inductive_engine_class::rank_num_times_found_each_pos()
{
     constant_class        *example_cur_constant_ptr;

     position_class        *example_cur_position_ptr;
     position_class        *background_cur_position_ptr;
     predicate_log_class   *background_cur_predlog_ptr;
     int                    number_occurences = 0;


    // TRAVERSE POSITIVE EXAMPLES 
     example_cur_position_ptr = get_first_positive_example_position();
     
     while (example_cur_position_ptr != NULL) {
           example_cur_constant_ptr = example_cur_position_ptr->
                                              get_first_poscon_ptr();

           while (example_cur_constant_ptr != NULL) {
                
                background_cur_predlog_ptr = get_first_background_predlog_ptr();
                while (background_cur_predlog_ptr != NULL) {


                    background_cur_position_ptr = background_cur_predlog_ptr->
                              get_first_pos_ptr();

                    while (background_cur_position_ptr != NULL) {
                       number_occurences = 0;

                       // INCREASE THE RANK BY NUM TIMES CONSTANT FOUND THERE   
                       number_occurences = 
                           background_cur_position_ptr->number_times_constant_found
                                                 (example_cur_constant_ptr); 
                       background_cur_predlog_ptr->increase_rank(number_occurences);

                              
                       background_cur_position_ptr = background_cur_position_ptr->
                                   get_next_ptr();
                    } // WHILE more positions in current predlog of bkg

                       background_cur_predlog_ptr = background_cur_predlog_ptr->
                                                   get_next_ptr(); 
                }// WHILE there are more meshes in the BACK KNOW
           


                example_cur_constant_ptr  = example_cur_constant_ptr->
                                                   get_next_ptr(); 
           } //WHILE more constants in this position of the pos example sets

           example_cur_position_ptr = example_cur_position_ptr->get_next_ptr();
     } // WHILE  there are more positions in the example set

    // *******************************************************************

    // TRAVERSE NEGATIVE EXAMPLES 
     example_cur_position_ptr = get_first_negative_example_position();
     
     while (example_cur_position_ptr != NULL) {
           example_cur_constant_ptr = example_cur_position_ptr->
                                              get_first_poscon_ptr();

           while (example_cur_constant_ptr != NULL) {
                
                background_cur_predlog_ptr = get_first_background_predlog_ptr();
                while (background_cur_predlog_ptr != NULL) {


                    background_cur_position_ptr = background_cur_predlog_ptr->
                              get_first_pos_ptr();

                    while (background_cur_position_ptr != NULL) {
                        number_occurences = 0;

                       // INCREASE THE RANK BY NUM TIMES CONSTANT FOUND THERE   
                      number_occurences = 
                          background_cur_position_ptr->number_times_constant_found
                                                 (example_cur_constant_ptr); 
                              
                       background_cur_predlog_ptr->decrease_rank(number_occurences);

                       background_cur_position_ptr = background_cur_position_ptr->
                                   get_next_ptr();
                    } // WHILE more positions in current predlog of bkg

                    background_cur_predlog_ptr = background_cur_predlog_ptr->
                                                   get_next_ptr(); 
                }// WHILE there are more meshes in the BACK KNOW

                example_cur_constant_ptr  = example_cur_constant_ptr->
                                                   get_next_ptr(); 
           } //WHILE more constants in this position of the pos example sets

           example_cur_position_ptr = example_cur_position_ptr->get_next_ptr();
     } // WHILE  there are more positions in the example set

} // RANK NUMBER TIMES FOUND IN PREDLOG


////////////////////////////////////////////////////////////////////////////
/// RANK ALGORITHM 5:  Position/Spot Membership One Element.. Pos Only
/// -------------------------------------------------------------------
///   For each positive example e+  (located at spot EXAMPLE_SPOT_NUM)
///       For each constant c appearing in e+
///           For each predicate_log_class CUR_PREDLOG_OBJECT in BACKGROUND
///                 If c appears in position CUR_PREDLOG_POS ( in spot
///                      CUR_PREDLOG_SPOT in CUR_PREDLOG_OBJECT)
///                      --  for each other constant c' in e+ (also located at spot
///                                 EXAMPLE_SPOT_NUM in example set)
///                                 if c' appears in some other position 
///                                       at spot CUR_PREDLOG_SPOT in CUR_PREDLOG_OBJECT 
///                                                 RANK(CUR_PREDLOG_OBJECT)++
///
//////////////////////////////////////////////////////////////////////////////

void inductive_engine_class::rank_pos_spot_membership_one_pos_only()
{
     constant_class        *example_cur_constant_ptr;
     constant_class        *cur_neighbor_c_ptr;

     position_class        *example_cur_position_ptr;
     position_class        *cur_example_neighbor_position_ptr;
     position_class        *background_cur_position_ptr;
     predicate_log_class   *background_cur_predlog_ptr;
     int                    example_spot_number;
     int                    predlog_position_number;
     int                    num_total_predlog_positions;
     int                    chk_predlog_pos_number;
     int                    cur_predlog_spot;


     // TRAVERSE POSITIVE EXAMPLES 
     example_cur_position_ptr = get_first_positive_example_position();
     
     while (example_cur_position_ptr != NULL) {
           example_cur_constant_ptr = example_cur_position_ptr->
                                              get_first_poscon_ptr();
           example_spot_number=0;

           while (example_cur_constant_ptr != NULL) {
                 example_spot_number++;
                
                background_cur_predlog_ptr = get_first_background_predlog_ptr();
                while (background_cur_predlog_ptr != NULL) {

                       background_cur_predlog_ptr->mark_mesh_NOT_taken();
                       cur_predlog_spot = background_cur_predlog_ptr->has_constant
                                             (example_cur_constant_ptr);
                       if (cur_predlog_spot != 0) {

                              //INCREASE RANK BY 1 BECAUSE THE EXAMPLE CONSTANT WAS FOUND AT ALL
                              background_cur_predlog_ptr->increment_rank();

                              //CHECK FOR NEIGHBORING CONSTANTS OF CUR_EXAMPLE_C_PTR
                              //APPEARING IN THE SAME SPOT IN OTHER POSITIONS OF SAME
                              // CUR_PREDLOG OBJECT
                               cur_example_neighbor_position_ptr = 
                                      get_first_positive_example_position();

                               while (cur_example_neighbor_position_ptr != NULL) {
                                    if (cur_example_neighbor_position_ptr !=
                                        example_cur_position_ptr) { // DON'T CONSIDER A CONSTANT ITS OWN NEIGHBOR

                                       cur_neighbor_c_ptr = 
                                           cur_example_neighbor_position_ptr->
                                               get_constant_in_spot(example_spot_number);

                                       if (cur_neighbor_c_ptr ==NULL) {
                                            cout << "cur_neighbor_c_ptr  is NULL...problem with example_structure \n";
                                            cout << "System is exiting.";
                                            exit(1);
                                       }
                                        
                                       chk_predlog_pos_number = 1;
                                       num_total_predlog_positions = background_cur_predlog_ptr->
                                                                      get_num_positions();

                                       while (chk_predlog_pos_number <= num_total_predlog_positions) {
                                           if ( (background_cur_predlog_ptr->has_constant_in_pos_spot
                                                (chk_predlog_pos_number, cur_predlog_spot, cur_neighbor_c_ptr))==1) 
                                           { //BEGIN IF
                                                         background_cur_predlog_ptr->increment_rank();
                                           } //IF
                                           chk_predlog_pos_number++;
                                       } //WHILE more positions in cur_predlog to check for neighbors                                    

                                    }//IF current_example_neighbor_ptr is not current_example_pos_ptr itself

                                    cur_example_neighbor_position_ptr = 
                                          cur_example_neighbor_position_ptr->get_next_ptr();
                               } // WHILE more neighbors to example_cur_constant_ptr exist
 
                       } //IF

                       background_cur_predlog_ptr = background_cur_predlog_ptr->
                                                   get_next_ptr(); 
                } //WHILE there are more meshes in the BACK KNOW

                example_cur_constant_ptr  = example_cur_constant_ptr->
                                                   get_next_ptr(); 
           }// WHILE more constants in this position of the pos example sets

           example_cur_position_ptr = example_cur_position_ptr->get_next_ptr();
     } // WHILE  there are more positions in the example set

   //     *******************************************************************

}  //RANK_POS_SPOT_MEMBERSHIP_ONE POS ONLY


////////////////////////////////////////////////////////////////////////////
/// RANK ALGORITHM 6:  Position/Spot Membership One Element
/// -------------------------------------------------------
///   For each positive example e+  (located at spot EXAMPLE_SPOT_NUM)
///       For each constant c appearing in e+
///           For each predicate_log_class CUR_PREDLOG_OBJECT in BACKGROUND
///                 If c appears in position CUR_PREDLOG_POS ( in spot
///                      CUR_PREDLOG_SPOT in CUR_PREDLOG_OBJECT)
///                      --  for each other constant c' in e+ (also located at spot
///                                 EXAMPLE_SPOT_NUM in example set)
///                                 if c' appears in some other position 
///                                       at spot CUR_PREDLOG_SPOT in CUR_PREDLOG_OBJECT 
///                                                 RANK(CUR_PREDLOG_OBJECT)++
///
///   For each negative  example e-  (located at spot EXAMPLE_SPOT_NUM)
///       For each constant c appearing in e-
///           For each predicate_log_class CUR_PREDLOG_OBJECT in BACKGROUND
///                 If c appears in position CUR_PREDLOG_POS ( in spot
///                      CUR_PREDLOG_SPOT in CUR_PREDLOG_OBJECT)
///                      --  for each other constant c' in e- (also located at spot
///                                 EXAMPLE_SPOT_NUM)
///                                 if c' appears in some other position 
///                                       at spot CUR_PREDLOG_SPOT in CUR_PREDLOG_OBJECT 
///                                                 RANK(CUR_PREDLOG_OBJECT)--
///
//////////////////////////////////////////////////////////////////////////////

void inductive_engine_class::rank_pos_spot_membership_one()
{
     constant_class        *example_cur_constant_ptr;
     constant_class        *cur_neighbor_c_ptr;

     position_class        *example_cur_position_ptr;
     position_class        *cur_example_neighbor_position_ptr;
     position_class        *background_cur_position_ptr;
     predicate_log_class   *background_cur_predlog_ptr;
     int                    example_spot_number;
     int                    predlog_position_number;
     int                    num_total_predlog_positions;
     int                    chk_predlog_pos_number;
     int                    cur_predlog_spot;


     // TRAVERSE POSITIVE EXAMPLES 
     example_cur_position_ptr = get_first_positive_example_position();
     
     while (example_cur_position_ptr != NULL) {
           example_cur_constant_ptr = example_cur_position_ptr->
                                              get_first_poscon_ptr();
           example_spot_number=0;

           while (example_cur_constant_ptr != NULL) {
                 example_spot_number++;
                
                background_cur_predlog_ptr = get_first_background_predlog_ptr();
                while (background_cur_predlog_ptr != NULL) {

                       background_cur_predlog_ptr->mark_mesh_NOT_taken();
                       cur_predlog_spot = background_cur_predlog_ptr->has_constant
                                             (example_cur_constant_ptr);
                       if (cur_predlog_spot != 0) {
                              //INCREASE RANK BY 1 BECAUSE THE EXAMPLE CONSTANT WAS FOUND AT ALL
                              background_cur_predlog_ptr->increment_rank();
          
                              //CHECK FOR NEIGHBORING CONSTANTS OF CUR_EXAMPLE_C_PTR
                              //APPEARING IN THE SAME SPOT IN OTHER POSITIONS OF SAME
                              // CUR_PREDLOG OBJECT
                               cur_example_neighbor_position_ptr = 
                                      get_first_positive_example_position();

                               while (cur_example_neighbor_position_ptr != NULL) {
                                    if (cur_example_neighbor_position_ptr !=
                                        example_cur_position_ptr) { // DON'T CONSIDER A CONSTANT ITS OWN NEIGHBOR

                                       cur_neighbor_c_ptr = 
                                           cur_example_neighbor_position_ptr->
                                               get_constant_in_spot(example_spot_number);

                                       if (cur_neighbor_c_ptr ==NULL) {
                                            cout << "cur_neighbor_c_ptr  is NULL...problem with example_structure \n";
                                            cout << "System is exiting.";
                                            exit(1);
                                       }
                                        
                                       chk_predlog_pos_number = 1;
                                       num_total_predlog_positions = background_cur_predlog_ptr->
                                                                      get_num_positions();

                                       while (chk_predlog_pos_number <= num_total_predlog_positions) {
                                           if ( (background_cur_predlog_ptr->has_constant_in_pos_spot
                                                (chk_predlog_pos_number, cur_predlog_spot, cur_neighbor_c_ptr))==1) 
                                           { //BEGIN IF
                                                         background_cur_predlog_ptr->increment_rank();
                                           } //IF
                                           chk_predlog_pos_number++;
                                       } //WHILE more positions in cur_predlog to check for neighbors                                    

                                    }//IF current_example_neighbor_ptr is not current_example_pos_ptr itself

                                    cur_example_neighbor_position_ptr = 
                                          cur_example_neighbor_position_ptr->get_next_ptr();
                               } // WHILE more neighbors to example_cur_constant_ptr exist
 
                       } //IF

                       background_cur_predlog_ptr = background_cur_predlog_ptr->
                                                   get_next_ptr(); 
                } //WHILE there are more meshes in the BACK KNOW

                example_cur_constant_ptr  = example_cur_constant_ptr->
                                                   get_next_ptr(); 
           }// WHILE more constants in this position of the pos example sets

           example_cur_position_ptr = example_cur_position_ptr->get_next_ptr();
     } // WHILE  there are more positions in the example set

   //     *******************************************************************

     // TRAVERSE NEGATIVE EXAMPLES 
     example_cur_position_ptr = get_first_negative_example_position();
     
     while (example_cur_position_ptr != NULL) {
           example_cur_constant_ptr = example_cur_position_ptr->
                                              get_first_poscon_ptr();
           example_spot_number=0;

           while (example_cur_constant_ptr != NULL) {

                example_spot_number++;
                
                background_cur_predlog_ptr = get_first_background_predlog_ptr();
                while (background_cur_predlog_ptr != NULL) {

                       background_cur_predlog_ptr->mark_mesh_NOT_taken();

                       cur_predlog_spot = background_cur_predlog_ptr->has_constant
                                             (example_cur_constant_ptr);
                       if (cur_predlog_spot != 0) {

                              //DECREASE RANK BY 1 BECAUSE THE EXAMPLE CONSTANT WAS FOUND AT ALL
                              background_cur_predlog_ptr->decrement_rank();

          
                              //CHECK FOR NEIGHBORING CONSTANTS OF CUR_EXAMPLE_C_PTR
                              //APPEARING IN THE SAME SPOT IN OTHER POSITIONS OF SAME
                              // CUR_PREDLOG OBJECT
                               cur_example_neighbor_position_ptr = 
                                      get_first_negative_example_position();

                               while (cur_example_neighbor_position_ptr != NULL) {
                                    if (cur_example_neighbor_position_ptr !=
                                        example_cur_position_ptr) { // DON'T CONSIDER A CONSTANT ITS OWN NEIGHBOR

                                       cur_neighbor_c_ptr = 
                                           cur_example_neighbor_position_ptr->
                                               get_constant_in_spot(example_spot_number);

                                       if (cur_neighbor_c_ptr ==NULL) {
                                            cout << "cur_neighbor_c_ptr  is NULL...problem with example_structure \n";
                                            cout << "System is exiting.";
                                            exit(1);
                                       }
                                        
                                       chk_predlog_pos_number = 1;
                                       num_total_predlog_positions = background_cur_predlog_ptr->
                                                                      get_num_positions();

                                       while (chk_predlog_pos_number <= num_total_predlog_positions) {
                                           if ( (background_cur_predlog_ptr->has_constant_in_pos_spot
                                                (chk_predlog_pos_number, cur_predlog_spot, cur_neighbor_c_ptr))==1) 
                                           { //BEGIN IF
                                                         background_cur_predlog_ptr->decrement_rank();
                                           } //IF
                                           chk_predlog_pos_number++;
                                       } //WHILE more positions in cur_predlog to check for neighbors                                    

                                    }//IF current_example_neighbor_ptr is not current_example_pos_ptr itself

                                    cur_example_neighbor_position_ptr = 
                                          cur_example_neighbor_position_ptr->get_next_ptr();
                               } // WHILE more neighbors to example_cur_constant_ptr exist
 
                       } //IF

                       background_cur_predlog_ptr = background_cur_predlog_ptr->
                                                   get_next_ptr(); 
                } //WHILE there are more meshes in the BACK KNOW

                example_cur_constant_ptr  = example_cur_constant_ptr->
                                                   get_next_ptr(); 
           }// WHILE more constants in this position of the pos example sets

           example_cur_position_ptr = example_cur_position_ptr->get_next_ptr();
     } // WHILE  there are more positions in the example set
}  //RANK_POS_SPOT_MEMBERSHIP_ONE





////////////////////////////////////////////////////////////////////////////
/// RANK ALGORITHM 7:  Rank Predicates by Coverage .. POS ONLY
/// ------------------------------------------------------------
///   For each predicate_log_class CUR_PREDLOG_OBJECT in BACKGROUND
///       For each positive example e+
///             If e+ is in CUR_PREDLOG_OBJECT mesh in any order,
///                      Rank(CUR_PREDLOG_OBJECT) ++
//////////////////////////////////////////////////////////////////////////////

void inductive_engine_class::rank_predicates_by_coverage_pos_only_single()
{
     constant_class        *example_cur_constant_ptr;
     constant_class        *cur_neighbor_c_ptr;
     atom_class            *cur_example_a_ptr;

     position_class        *example_cur_position_ptr;
     position_class        *cur_example_neighbor_position_ptr;
     position_class        *background_cur_position_ptr;
     predicate_log_class   *background_cur_predlog_ptr;
     int                    example_spot_number;
     int                    predlog_position_number;
     int                    num_total_predlog_positions;
     int                    chk_predlog_pos_number;
     int                    cur_predlog_spot;


                
        background_cur_predlog_ptr = get_first_background_predlog_ptr();

        while (background_cur_predlog_ptr != NULL) {
             background_cur_predlog_ptr->mark_mesh_NOT_taken();

             // TRAVERSE POSITIVE EXAMPLE LIST TO UPDATE RANK
             cur_example_a_ptr = positive_examples->get_first_atom_ptr();        
             while (cur_example_a_ptr != NULL) {

                if (background_cur_predlog_ptr->
                     is_member_of_mesh_any_order(cur_example_a_ptr)==1)
                          background_cur_predlog_ptr->increment_rank();
                cur_example_a_ptr = cur_example_a_ptr->get_next_ptr();          
             }// WHILE


             background_cur_predlog_ptr = background_cur_predlog_ptr->
                                get_next_ptr(); 
        } //WHILE there are more meshes in the BACK KNOW

} //RANK_PREDICATES_BY_COVERAGE_POS_ONLY




////////////////////////////////////////////////////////////////////////////
/// RANK ALGORITHM 8:  Rank Predicates by Coverage
/// -------------------------------------------------------
///   For each predicate_log_class CUR_PREDLOG_OBJECT in BACKGROUND
///       For each positive example e+
///             If e+ is in CUR_PREDLOG_OBJECT mesh in any order,
///                      Rank(CUR_PREDLOG_OBJECT) ++
///       For each negative example e- 
///             If e- is in CUR_PREDLOG_OBJECT mesh in any order,
///                      Rank(CUR_PREDLOG_OBJECT)--
//////////////////////////////////////////////////////////////////////////////

void inductive_engine_class::rank_predicates_by_coverage_single()
{
     constant_class        *example_cur_constant_ptr;
     constant_class        *cur_neighbor_c_ptr;
     atom_class            *cur_example_a_ptr;

     position_class        *example_cur_position_ptr;
     position_class        *cur_example_neighbor_position_ptr;
     position_class        *background_cur_position_ptr;
     predicate_log_class   *background_cur_predlog_ptr;
     int                    example_spot_number;
     int                    predlog_position_number;
     int                    num_total_predlog_positions;
     int                    chk_predlog_pos_number;
     int                    cur_predlog_spot;


                
        background_cur_predlog_ptr = get_first_background_predlog_ptr();

        while (background_cur_predlog_ptr != NULL) {
             background_cur_predlog_ptr->mark_mesh_NOT_taken();

             // TRAVERSE POSITIVE EXAMPLE LIST TO UPDATE RANK
             cur_example_a_ptr = positive_examples->get_first_atom_ptr();        
             while (cur_example_a_ptr != NULL) {

                if (background_cur_predlog_ptr->
                     is_member_of_mesh_any_order(cur_example_a_ptr)==1)
                          background_cur_predlog_ptr->increment_rank();
                cur_example_a_ptr = cur_example_a_ptr->get_next_ptr();          
             }// WHILE

             // TRAVERSE NEGATIVE EXAMPLE LIST TO UPDATE RANK
             cur_example_a_ptr = negative_examples->get_first_atom_ptr();        
             while (cur_example_a_ptr != NULL) {

                if (background_cur_predlog_ptr->
                     is_member_of_mesh_any_order(cur_example_a_ptr)==1)
                          background_cur_predlog_ptr->decrement_rank();
                cur_example_a_ptr = cur_example_a_ptr->get_next_ptr();          
             }// WHILE


             background_cur_predlog_ptr = background_cur_predlog_ptr->
                                get_next_ptr(); 
        } //WHILE there are more meshes in the BACK KNOW

}  //RANK_PREDICATES_BY_COVERAGE_SINGLE

//--------------------------------------------------------------------------




////////////////////////////////////////////////////////////////////////////
/// RANK ALGORITHM 9:  Rank Predicates by Coverage .. POS ONLY
///      For example sets with more than one argument
/// ------------------------------------------------------------
///   For each predicate_log_class CUR_PREDLOG_OBJECT in BACKGROUND
///       For each positive example e+
///             If e+ is in CUR_PREDLOG_OBJECT mesh in any order,
///                      Rank(CUR_PREDLOG_OBJECT) ++
//////////////////////////////////////////////////////////////////////////////

void inductive_engine_class::rank_predicates_by_coverage_pos_only()
{
     constant_class        *example_cur_constant_ptr;
     constant_class        *cur_neighbor_c_ptr;
     atom_class            *cur_example_a_ptr;

     position_class        *example_cur_position_ptr;
     position_class        *cur_example_neighbor_position_ptr;
     position_class        *background_cur_position_ptr;
     predicate_log_class   *background_cur_predlog_ptr;
     int                    example_spot_number;
     int                    predlog_position_number;
     int                    num_total_predlog_positions;
     int                    chk_predlog_pos_number;
     int                    cur_predlog_spot;


                
        background_cur_predlog_ptr = get_first_background_predlog_ptr();

        while (background_cur_predlog_ptr != NULL) {
             background_cur_predlog_ptr->mark_mesh_NOT_taken();

             // TRAVERSE POSITIVE EXAMPLE LIST TO UPDATE RANK
             cur_example_a_ptr = positive_examples->get_first_atom_ptr();        
             while (cur_example_a_ptr != NULL) {

                if (background_cur_predlog_ptr->
                     is_member_of_mesh_any_order(cur_example_a_ptr)==1)
                          background_cur_predlog_ptr->increment_rank();
                cur_example_a_ptr = cur_example_a_ptr->get_next_ptr();          
             }// WHILE


             background_cur_predlog_ptr = background_cur_predlog_ptr->
                                get_next_ptr(); 
        } //WHILE there are more meshes in the BACK KNOW

} //RANK_PREDICATES_BY_COVERAGE_POS_ONLY




////////////////////////////////////////////////////////////////////////////
/// RANK ALGORITHM 10:  Rank Predicates by Coverage
///    For example sets with more than one argument
/// -------------------------------------------------------
///   
///   For each predicate_log_class CUR_PREDLOG_OBJECT in BACKGROUND
///       For each positive example e+
///             If e+ is in CUR_PREDLOG_OBJECT mesh in any order,
///                      Rank(CUR_PREDLOG_OBJECT) ++
///       For each negative example e- 
///             If e- is in CUR_PREDLOG_OBJECT mesh in any order,
///                      Rank(CUR_PREDLOG_OBJECT)--
//////////////////////////////////////////////////////////////////////////////

void inductive_engine_class::rank_predicates_by_coverage()
{
     constant_class        *example_cur_constant_ptr;
     constant_class        *cur_neighbor_c_ptr;
     atom_class            *cur_example_a_ptr;

     position_class        *example_cur_position_ptr;
     position_class        *cur_example_neighbor_position_ptr;
     position_class        *background_cur_position_ptr;
     predicate_log_class   *background_cur_predlog_ptr;
     int                    example_spot_number;
     int                    predlog_position_number;
     int                    num_total_predlog_positions;
     int                    chk_predlog_pos_number;
     int                    cur_predlog_spot;


                
        background_cur_predlog_ptr = get_first_background_predlog_ptr();

        while (background_cur_predlog_ptr != NULL) {
             background_cur_predlog_ptr->mark_mesh_NOT_taken();

             // TRAVERSE POSITIVE EXAMPLE LIST TO UPDATE RANK
             cur_example_a_ptr = positive_examples->get_first_atom_ptr();        
             while (cur_example_a_ptr != NULL) {

                if (background_cur_predlog_ptr->
                     is_member_of_mesh_any_order(cur_example_a_ptr)==1)
                          background_cur_predlog_ptr->increment_rank();
                cur_example_a_ptr = cur_example_a_ptr->get_next_ptr();          
             }// WHILE

             // TRAVERSE NEGATIVE EXAMPLE LIST TO UPDATE RANK
             cur_example_a_ptr = negative_examples->get_first_atom_ptr();        
             while (cur_example_a_ptr != NULL) {

                if (background_cur_predlog_ptr->
                     is_member_of_mesh_any_order(cur_example_a_ptr)==1)
                          background_cur_predlog_ptr->decrement_rank();
                cur_example_a_ptr = cur_example_a_ptr->get_next_ptr();          
             }// WHILE


             background_cur_predlog_ptr = background_cur_predlog_ptr->
                                get_next_ptr(); 
        } //WHILE there are more meshes in the BACK KNOW

}  //RANK_PREDICATES_BY_COVERAGE











//------------------------------------------------------------------------







//////////////////////////////////////////////////////////////////////////
///   P R E D I C A T E    R A N K I N G.............
///   TO CHANGE RANKING : change the below call
/////////////////////////////////////////////////////////////////////////
void inductive_engine_class::perform_predicate_ranking
                              (int predicate_algorithm_choice)

{

      background_knowledge->initialize_predicate_rankings();  
//cout << "inside INduc::perform_predicate_ranking input parm predicate_algorithm_choice is:  ";
//cout << predicate_algorithm_choice << endl << endl;
      switch (predicate_algorithm_choice)
      {
         case 1: rank_simple_membership_pos_only(); 
                 break;
         case 2: rank_simple_membership();
                 break;
         case 3: rank_num_times_found_each_pos_pos_only(); 
                 break;
         case 4: rank_num_times_found_each_pos(); 
                 break;
         case 5: rank_pos_spot_membership_one_pos_only();  
                 break;
         case 6: rank_pos_spot_membership_one();  
                 break;
         case 7: rank_predicates_by_coverage_pos_only_single();  
                 break;
         case 8: rank_predicates_by_coverage_single(); 
                 break;
         case 9: rank_predicates_by_coverage_pos_only();  
                 break;
         case 10: rank_predicates_by_coverage(); 
                 break;
      } //SWITCH
} // perform_predicate_ranking    
//////////////////////////////////////////////////////////////////////////
///  Returns a pointer to an intensional rule set, each member of which
///    has the target predicate target_predicate_expression_ptr 
///    as its head.  The following top-down empirical algorithm is
///    employed.
///
///    while ( [# pos examples covered ] < SUFFICIENCY_STOP_CRITEREON ) Do
///         Make new intensional rule:
///             --head is the target predicate
///             --make body as follows:
///               while ([# neg examples covered ] > NECESSITY_STOP_CRITEREON ) Do  
///                     - Add literal to the body by choosing the highest ranked
///                          unchosen predexp in the bkg mesh 
///                          (ranked in inductive engine constructor)
///                     - Name the variables of this chosen literal
///               end while
///         Add the new intensional rule to the rule set to be returned
///    end while
/////////////////////////////////////////////////////////////////////////
int_ruleset_class *inductive_engine_class::learn_rule_defaults()
{
     predicate_expression_class    *chosen_predicate_ptr;
     predicate_expression_class    *head_predicate_ptr;
     predicate_expression_class    *other_pred_exp_ptr;

     intensional_rule_class        *i_ptr;
     int_ruleset_class             *learned_rule_set;
     char                           target_fullstr[LONG_STRING_LENGTH];
     double                         neg_ratio = 1.0;
     double                         pos_ratio = 0.0;

cout << "Entered learn_rule...\n";

    learned_rule_set  = new int_ruleset_class();

    // ESTABLISH DEFAULTS
    background_knowledge->initialize_mesh_chosen_and_predrank();
    perform_predicate_ranking(DEFAULT_PREDRANK_ALGO);    
    SUFFICIENCY_STOP_CRITEREON = DEFAULT_SUFF;
    NECESSITY_STOP_CRITEREON = DEFAULT_NEC;


    int predicates_all_chosen = 0;
    positive_examples->initialize_coverage();
    negative_examples->initialize_coverage();

     while ((pos_ratio < SUFFICIENCY_STOP_CRITEREON) && 
           (!(predicates_all_chosen == 1))){


         //MAKE NEW INTENSIONAL RULE
          i_ptr = new intensional_rule_class();
  
         //CREATE HEAD
          strcpy(target_fullstr, target_predicate_expression_ptr->get_fullstring());
          head_predicate_ptr = new predicate_expression_class(target_fullstr);   
          i_ptr->add_predicate_exp_ptr(head_predicate_ptr);

         //CREATE BODY
        neg_ratio = 1.0;
        while (( neg_ratio > NECESSITY_STOP_CRITEREON)&& 
              (!(predicates_all_chosen==1))) {
     
                 //CHOOSE THE NEXT LITERAL
                 chosen_predicate_ptr = construct_next_literal(DEFAULT_POS_ALGO);
                if (chosen_predicate_ptr != NULL) {
  
                         i_ptr->add_predicate_exp_ptr(chosen_predicate_ptr); 
  
                         neg_ratio = determine_ratio_of_neg_examples_covered(i_ptr);

                } // IF
                else {
                         predicates_all_chosen = 1;
                 } //ELSE

        } //WHILE inner
 
        // CHECK WHETHER OR NOT SCULPTED RULE HAS OTHER PRED EXP BESIDES TARGET
        other_pred_exp_ptr = i_ptr->get_first_predexp_ptr(); 
        if (other_pred_exp_ptr == NULL) {
              cout << "INduc.cc, learn_defaults:  Problem with rule creation... \n";
              cout << "   ...should have target pred as head...\n";
              exit(1);
        }
        else {
             other_pred_exp_ptr = other_pred_exp_ptr->get_next_ptr(); 
             if (other_pred_exp_ptr != NULL) {     //RULE NOT EMPTY
                  learned_rule_set->add_rule(i_ptr);
             } //IF rule contains predexp's other than target
        } //ELSE

        pos_ratio = determine_ratio_of_pos_examples_covered(i_ptr);

          
    } //OUTER WHILE LOOP
    return learned_rule_set;
}


//////////////////////////////////////////////////////////////////////////
///  Returns a pointer to an intensional rule set, each member of which
///    has the target predicate target_predicate_expression_ptr 
///    as its head.  The following top-down empirical algorithm is
///    employed.
///
///    while ( [# pos examples covered ] < SUFFICIENCY_STOP_CRITEREON ) Do
///         Make new intensional rule:
///             --head is the target predicate
///             --make body as follows:
///               while ([# neg examples covered ] > NECESSITY_STOP_CRITEREON ) Do  
///                     - Add literal to the body by choosing the highest ranked
///                          unchosen predexp in the bkg mesh 
///                          (ranked in inductive engine constructor)
///                     - Name the variables of this chosen literal
///               end while
///         Add the new intensional rule to the rule set to be returned
///    end while
/////////////////////////////////////////////////////////////////////////
int_ruleset_class *inductive_engine_class::learn_rule()
{
     predicate_expression_class    *chosen_predicate_ptr;
     predicate_expression_class    *head_predicate_ptr;
     predicate_expression_class    *other_pred_exp_ptr;

     intensional_rule_class        *i_ptr;
     int_ruleset_class             *learned_rule_set;
     char                           target_fullstr[LONG_STRING_LENGTH];
     int                            user_predrank_algorithm;
     int                            user_posname_algorithm;
     double                         user_specified_inconsistency_coef =
                                             DEFAULT_INCONSISTENCY_COEF;    
     double                         example_inconsistency = 0.0;              

    user_specified_inconsistency_coef = get_user_inconsistency_coef();
    example_inconsistency = check_for_example_inconsistency();

if (example_inconsistency  <= user_specified_inconsistency_coef) {

 int rule_acceptable_flag = 0;
 do {

    double neg_ratio = 1.0;
    double pos_ratio = 0.0;
    char stop_char   = ' ';


    learned_rule_set  = new int_ruleset_class();
    background_knowledge->initialize_mesh_chosen_and_predrank();
    int predicates_all_chosen = 0;
    positive_examples->initialize_coverage();
    negative_examples->initialize_coverage();

    //GET USER'S CHOICES TO LEARN
    get_user_learner_data(user_predrank_algorithm, 
                         user_posname_algorithm,
                         SUFFICIENCY_STOP_CRITEREON,
                         NECESSITY_STOP_CRITEREON);
     
                        
    perform_predicate_ranking(user_predrank_algorithm);
    

     while ((pos_ratio < SUFFICIENCY_STOP_CRITEREON) && 
           (!(predicates_all_chosen == 1))){

         //MAKE NEW INTENSIONAL RULE
          i_ptr = new intensional_rule_class();
  
         //CREATE HEAD
          strcpy(target_fullstr, target_predicate_expression_ptr->get_fullstring());
          head_predicate_ptr = new predicate_expression_class(target_fullstr);   
          head_predicate_ptr->assign_IS_NEGATIVE(0);
          i_ptr->add_predicate_exp_ptr(head_predicate_ptr);


         //CREATE BODY
        neg_ratio = 1.0;
        while (( neg_ratio > NECESSITY_STOP_CRITEREON)&& 
              (!(predicates_all_chosen==1))) {
     

                 //CHOOSE THE NEXT LITERAL
                 chosen_predicate_ptr = construct_next_literal(user_posname_algorithm);
                if (chosen_predicate_ptr != NULL) {
  
                         i_ptr->add_predicate_exp_ptr(chosen_predicate_ptr); 
                         neg_ratio = determine_ratio_of_neg_examples_covered(i_ptr);

                } // IF
                else {
                         predicates_all_chosen = 1;
                 } //ELSE

        } //WHILE inner
 
        // CHECK WHETHER OR NOT SCULPTED RULE HAS OTHER PRED EXP BESIDES TARGET
        other_pred_exp_ptr = i_ptr->get_first_predexp_ptr(); 
        if (other_pred_exp_ptr == NULL) {
              cout << "INduc.cc:  Problem with rule creation... \n";
              cout << "   ...should have target pred as head...\n";
              exit(1);
        }
        else {
             other_pred_exp_ptr = other_pred_exp_ptr->get_next_ptr(); 
             if (other_pred_exp_ptr != NULL) {     //RULE NOT EMPTY
                  learned_rule_set->add_rule(i_ptr);
             } //IF rule contains predexp's other than target
        } //ELSE

        pos_ratio = determine_ratio_of_pos_examples_covered(i_ptr);

    } //OUTER WHILE LOOP


    clear_screen(NUM_LINES_HALFSCREEN);
    learned_rule_set->display(cout);
    cout << "Is this rule acceptable? (Y/N) ";
    cin >> stop_char;
    if ((stop_char == 'y') || (stop_char == 'Y')) {
         rule_acceptable_flag = 1;
    } // IF

    else {
        delete learned_rule_set;
    } // ELSE
        
  } // DO WHILE 

  while ( rule_acceptable_flag != 1 );
  return learned_rule_set;

}// IF example_inconsistency < limit
else {

   clear_screen(NUM_LINES_HALFSCREEN);
   cout << "-------------------------------------------------------\n";
   cout << "Example Sets had an inconsistency measure of: " <<
            example_inconsistency << "\n";
   cout << "Add negated target predicate (y/n)? \n";
   cout << "-------------------------------------------------------\n";
   cout << endl << endl;

   char learn_char = ' ';
   cin >> learn_char;
   if ((learn_char == 'y') || (learn_char == 'Y')){              
          learned_rule_set  = new int_ruleset_class();
          i_ptr = new intensional_rule_class();

         //CREATE RULE WITH NEGATED TARGET 
          strcpy(target_fullstr, target_predicate_expression_ptr->get_fullstring());
          head_predicate_ptr = new predicate_expression_class(target_fullstr);   
          head_predicate_ptr->assign_IS_NEGATIVE(1);
          i_ptr->add_predicate_exp_ptr(head_predicate_ptr);

          learned_rule_set->add_rule(i_ptr);
          return learned_rule_set;
   }
   else {
         return NULL;
   }

}// ELSE !example_set_consistent 


}

////////////////////////////////////////////////////////////////////////////
///  
///
////////////////////////////////////////////////////////////////////////////

predicate_expression_class *inductive_engine_class::construct_next_literal
                                               (int position_naming_choice)
{
    predicate_expression_class    *predexp_ptr;
    predicate_log_class           *predlog_ptr;
    position_class                *pos_ptr;
    char                           pred_symb[STRING_LENGTH];
    list_class<variable_class>     cur_var_list;
    variable_class                *var_ptr;
    char                           var_name_str[STRING_LENGTH];



    predlog_ptr = background_knowledge->get_max_unchosen_predlog();
    
    if (predlog_ptr != NULL ) {

         name_chosen_predicate_variables(position_naming_choice, predlog_ptr);


         strcpy(pred_symb, predlog_ptr->get_predlog_symbol());

         // CREATE VARIABLE LIST FOR NEW PRED EXP
          pos_ptr = predlog_ptr->get_first_pos_ptr();
          while (pos_ptr != NULL) {
              var_name_str[0] = pos_ptr->get_variable_name();
              var_name_str[1] = '\0';
              var_ptr = new variable_class(var_name_str);

              cur_var_list.add_ptr(var_ptr);
              pos_ptr = pos_ptr->get_next_ptr();
         } // WHILE

         predexp_ptr = new predicate_expression_class(cur_var_list, pred_symb);

         if (predlog_ptr->get_predlog_truthval() == 0)
               predexp_ptr->assign_IS_NEGATIVE(1);

         return predexp_ptr;
     } // IF predlog != NULL
     else {
         return NULL;
     } //ELSE
}//CONSTRUCT_NEXT_LITERAL

/////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////

void inductive_engine_class::initialize_example_position_rankings()     
{
        positive_examples->initialize_position_rankings();
        negative_examples->initialize_position_rankings(); 

}

//////////////////////////////////////////////////////////////////////////
///   E X A M P L E   R A N K I N G   P O S I T I O N .............
///   TO CHANGE RANKING : change the below call
/////////////////////////////////////////////////////////////////////////

void inductive_engine_class::perform_example_position_ranking   
                             ( int   position_algorithm_choice,   
                               predicate_log_class *chosen_predlog_ptr)
{

      initialize_example_position_rankings();

      switch (position_algorithm_choice)
      {
         case 1: rank_and_name_positions_membership_pos_only(chosen_predlog_ptr); 
                 break;
         case 2: rank_and_name_positions_membership(chosen_predlog_ptr);    
                 break;
      } //SWITCH                  
}

//////////////////////////////////////////////////////////////////////////////
///// POSITION RANK ALGORITHM 1:  rank_and_name_positions_membership_pos_only
///// --------------------------------------------------
/////    DON'T CONSIDER NEGATIVE EXAMPLES !!!!
/////
///// For each position POS of chosen predicate_Log p 
/////     For each constant c appearing in POS 
/////           For each position EXPOS of positive_example_set 
/////                           RANK(EXPOS)+= number times c appears in EXPOS
/////
/////     Name position POS the maxranked position's var name in E+
///// END FOR
/////
/////  In essence,  RANK(EXPOS) = total appearances in E+ 
/////                                   of chosen predlog's constants
//////////////////////////////////////////////////////////////////////////////
//
void inductive_engine_class::rank_and_name_positions_membership_pos_only   
                             (predicate_log_class *chosen_predlog_ptr)
{

     constant_class        *example_cur_constant_ptr;
     position_class        *pos_example_cur_position_ptr;
     position_class        *neg_example_cur_position_ptr;


     position_class        *chosen_cur_position_ptr;
     position_class        *max_pos_ptr;
     constant_class        *chosen_cur_constant_ptr;
     int                    number_pos_occurrences = 0;

     char                   new_name_char = ' ';
     char                   nextchar = ' ';


     nextchar = positive_examples->get_max_variable_name();
     nextchar++;

     chosen_cur_position_ptr = chosen_predlog_ptr->get_first_pos_ptr();
     while (chosen_cur_position_ptr != NULL) {
            chosen_cur_constant_ptr = chosen_cur_position_ptr->get_first_poscon_ptr();

            while (chosen_cur_constant_ptr != NULL) { 
                //TRAVERSE THE POSTIVE EXAMPLE SET BY POSITION 
                //   AND ADJUST THAT EXAMPLE POSITION BY THE NUMBER OF 
                //   TIMES THE CONSTANT APPEARS THERE 
                          positive_examples->initialize_position_rankings();

                          pos_example_cur_position_ptr  = 
                               positive_examples->get_first_position_ptr();

                          while (pos_example_cur_position_ptr != NULL) {
                                number_pos_occurrences = 0; 

                                number_pos_occurrences =  
                                     pos_example_cur_position_ptr->number_times_constant_found  
                                                  (chosen_cur_constant_ptr);

                                pos_example_cur_position_ptr->increase_posrank
                                       ( number_pos_occurrences);



                                pos_example_cur_position_ptr = 
                                         pos_example_cur_position_ptr->get_next_ptr();

                          } // WHILE example_cur_position_ptrs ARE NOT NULL
                 

                 chosen_cur_constant_ptr = chosen_cur_constant_ptr->get_next_ptr();
            } // WHILE chosen_cur_constant_ptr != NULL    

            // NAME THE CHOSEN PREDICATE'S CURRENT POSITION ACCORDING TO RANKING OF POS EXAMPLES
            new_name_char = ' ';
            max_pos_ptr = positive_examples->get_max_ranked_unchosen_position_ptr();
            if (max_pos_ptr != NULL) {
                 max_pos_ptr->mark_position_chosen(); 
                 new_name_char = max_pos_ptr->get_variable_name();

            } //IF
            else {
                 new_name_char = nextchar++;
            } //ELSE
            chosen_cur_position_ptr->assign_variable_name(new_name_char);

            chosen_cur_position_ptr = chosen_cur_position_ptr->get_next_ptr();
     } // WHILE (chosen_cur_position_ptr != NULL) 

} // rank_and_name_positions_membership_pos_only 

//////////////////////////////////////////////////////////////////////////////
///// POSITION RANK ALGORITHM 2:  rank_and_name_positions_membership
///// --------------------------------------------------
///// For each position POS of chosen predicate_Log p 
/////     For each constant c appearing in POS 
/////           For each position EXPOS of positive_example_set 
/////                           RANK(EXPOS)+= number times c appears in EXPOS
/////
/////                           RANK(EXPOS)-= number times c appears in 
/////                                 the corresponding NEGEXPOS in
/////                                 negative_example_set
/////     Name position POS the maxranked position's var name in E+
///// END FOR
/////
/////  In essence,  RANK(EXPOS) = total appearances in E+  MINUS
/////                             total appearances in E-
/////                                   of chosen predlog constants
//////////////////////////////////////////////////////////////////////////////
//
void inductive_engine_class::rank_and_name_positions_membership   
                             (predicate_log_class *chosen_predlog_ptr)
{

     constant_class        *example_cur_constant_ptr;
     position_class        *pos_example_cur_position_ptr;
     position_class        *neg_example_cur_position_ptr;


     position_class        *chosen_cur_position_ptr;
     position_class        *max_pos_ptr;
     constant_class        *chosen_cur_constant_ptr;
     int                    number_pos_occurrences = 0;
     int                    number_neg_occurrences = 0;

     char                   new_name_char = ' ';
     char                   nextchar = ' ';


     nextchar = positive_examples->get_max_variable_name();
     nextchar++;

     chosen_cur_position_ptr = chosen_predlog_ptr->get_first_pos_ptr();
     while (chosen_cur_position_ptr != NULL) {
            chosen_cur_constant_ptr = chosen_cur_position_ptr->get_first_poscon_ptr();

            while (chosen_cur_constant_ptr != NULL) { 
                //TRAVERSE THE POSTIVE EXAMPLE SET BY POSITION 
                //   AND ADJUST THAT EXAMPLE POSITION BY THE NUMBER OF 
                //   TIMES THE CONSTANT APPEARS THERE 
                          positive_examples->initialize_position_rankings();
                          negative_examples->initialize_position_rankings();

                          pos_example_cur_position_ptr  = 
                               positive_examples->get_first_position_ptr();
                          neg_example_cur_position_ptr  = 
                               negative_examples->get_first_position_ptr();

                          while (pos_example_cur_position_ptr != NULL) {
                                number_pos_occurrences = 0; 
                                number_neg_occurrences = 0; 

                                number_pos_occurrences =  
                                     pos_example_cur_position_ptr->number_times_constant_found  
                                                  (chosen_cur_constant_ptr);

                                number_neg_occurrences =  
                                     neg_example_cur_position_ptr->number_times_constant_found  
                                                  (chosen_cur_constant_ptr);

                                pos_example_cur_position_ptr->increase_posrank
                                       ( number_pos_occurrences -  number_neg_occurrences);



                                pos_example_cur_position_ptr = 
                                         pos_example_cur_position_ptr->get_next_ptr();

                                neg_example_cur_position_ptr = 
                                         neg_example_cur_position_ptr->get_next_ptr();

                          } // WHILE example_cur_position_ptrs ARE NOT NULL
                 

                 chosen_cur_constant_ptr = chosen_cur_constant_ptr->get_next_ptr();
            } // WHILE chosen_cur_constant_ptr != NULL    

            // NAME THE CHOSEN PREDICATE'S CURRENT POSITION ACCORDING TO RANKING OF POS EXAMPLES
            new_name_char = ' ';
            max_pos_ptr = positive_examples->get_max_ranked_unchosen_position_ptr();
            if (max_pos_ptr != NULL) {
                 max_pos_ptr->mark_position_chosen(); 
                 new_name_char = max_pos_ptr->get_variable_name();

            } //IF
            else {
                 new_name_char = nextchar++;
            } //ELSE
            chosen_cur_position_ptr->assign_variable_name(new_name_char);

            chosen_cur_position_ptr = chosen_cur_position_ptr->get_next_ptr();
     } // WHILE (chosen_cur_position_ptr != NULL) 

} // rank_and_name_positions_membership 

///////////////////////////////////////////////////////////////////////////////////////////////
void inductive_engine_class::name_chosen_predicate_variables 
                                (int position_naming_choice,
                                 predicate_log_class *chosen_predlog_ptr)
{

     positive_examples->initialize_position_chosen_flags();    
     if (position_naming_choice == 1)
           rank_and_name_positions_membership_pos_only(chosen_predlog_ptr);
     else if (position_naming_choice == 2)
           rank_and_name_positions_membership(chosen_predlog_ptr);
     else {
           cout << "INduc.cc, name_chosen_var:  Invalid position naming choice...\n";
           exit(1);
     } //ELSE

     chosen_predlog_ptr->verify_named_variables();

}

/////////////////////////////////////////////////////////////////////////////////////
///
///
////////////////////////////////////////////////////////////////////////////////////

atom_class *inductive_engine_class::form_ground_instance
                                ( atom_class *ground_source_atom_ptr,
                                  predicate_expression_class *nonground_predexp_ptr)
{

      variable_class       *cur_target_var_ptr;
      variable_class       *cur_source_var_ptr;
      constant_class       *cur_source_c_ptr;
      atom_class           *ground_atom_ptr;
      char                  ground_atom_str[LONG_STRING_LENGTH];
      int                   target_location;
      char                  current_var_str[STRING_LENGTH];
      char                  found_constant[STRING_LENGTH];


      // FORM A FULL STRING VERSION OF AN ATOM
       strcpy(ground_atom_str, "");
       
       strcat(ground_atom_str, nonground_predexp_ptr->get_predicate_symbol());
       strcat(ground_atom_str,"(");
   
       cur_source_var_ptr = nonground_predexp_ptr->get_first_variable();
       while ( cur_source_var_ptr != NULL) {

             strcpy(current_var_str, cur_source_var_ptr->get_variable_symbol());

             // FIND POSITION IN TARGET PREDICATE
                target_location = target_predicate_expression_ptr->
                                     get_position_of_variable_str(current_var_str);

            // EXTRACT THAT TARGET POSITIONED CONSTANT FROM GROUND INPUT
                strcpy(found_constant, 
                            ground_source_atom_ptr->get_ith_constant_symbol(target_location)); 

           // APPEND EXTRACTED CONSTANT TO FULLSTRING

                 strcat(ground_atom_str, found_constant);

             cur_source_var_ptr =  cur_source_var_ptr->get_next_ptr();
             if (cur_source_var_ptr == NULL)
                    strcat(ground_atom_str, ")");
             else
                    strcat(ground_atom_str, ",");

       } //WHILE

      ground_atom_ptr = new atom_class(ground_atom_str,
                                        nonground_predexp_ptr->get_IS_NEGATIVE());

      return ground_atom_ptr;
}// FORM GROUND INSTANCE
//////////////////////////////////////////////////////////////////////////////
////
////
////
/////////////////////////////////////////////////////////////////////////////

int inductive_engine_class::is_covered
                               ( atom_class *ground_example_atom_ptr,
                                  intensional_rule_class *i_ptr)
{ 

       atom_class                  *current_ground_literal_a_ptr;
       predicate_expression_class  *current_rule_literal_predexp_ptr;
       int                          cover_fail_flag = 0;



       current_rule_literal_predexp_ptr = i_ptr->get_first_predexp_ptr();

       //SKIP HEAD (target predicate)
       current_rule_literal_predexp_ptr = 
              current_rule_literal_predexp_ptr->get_next_ptr();

       //VERIFY THAT GROUND INSTANCES ARE IN BACKGROUND MESH
       while ((current_rule_literal_predexp_ptr != NULL) &&
             (!cover_fail_flag))

       { //begin WHILE
              current_ground_literal_a_ptr = form_ground_instance
                             ( ground_example_atom_ptr, 
                                   current_rule_literal_predexp_ptr);

              if (background_knowledge->covers(current_ground_literal_a_ptr,
                                                 current_rule_literal_predexp_ptr)==0)
              { //begin IF
                     cover_fail_flag = 1; 
              } //IF
               else {
                     current_rule_literal_predexp_ptr =
                               current_rule_literal_predexp_ptr->get_next_ptr();

              }//ELSE
              current_ground_literal_a_ptr->clear();
              delete  current_ground_literal_a_ptr;
       } //WHILE
      
      if (cover_fail_flag == 1)
          return 0;
      else
          return 1;
           

}
/////////////////////////////////////////////////////////////////////////////
double inductive_engine_class::determine_ratio_of_neg_examples_covered
                                 ( intensional_rule_class  *i_ptr)
{

     intensional_rule_class      *cur_i_ptr;
     atom_class                  *example_a_ptr;
     double                       num_covered = 0.0;
     double                       det_ratio = 0.0;

     example_a_ptr = negative_examples->get_first_atom_ptr();

     while ( example_a_ptr != NULL) {
            
             if (is_covered(example_a_ptr, i_ptr)==1) {
                    num_covered+=1.0;  
                    example_a_ptr->mark_covered();
              } //IF

             example_a_ptr = example_a_ptr->get_next_ptr();

     } // WHILE MORE examples
   
     det_ratio = num_covered/negative_examples->get_num_examples();
     return det_ratio;

}
/////////////////////////////////////////////////////////////////////////////
double inductive_engine_class::determine_ratio_of_pos_examples_covered
                                 ( intensional_rule_class  *i_ptr)
{

     intensional_rule_class      *cur_i_ptr;
     atom_class                  *example_a_ptr;
     double                       num_covered = 0.0;
     double                       det_ratio = 0.0;

     example_a_ptr = positive_examples->get_first_atom_ptr();
     while ( example_a_ptr != NULL) {
             if (example_a_ptr->get_is_covered()==1) {
                num_covered+=1.0;
             } //IF
             else if
                (is_covered(example_a_ptr, i_ptr)) {
                    num_covered+=1.0;  
                    example_a_ptr->mark_covered();
              } //ELSE IF
             else {
             } //ELSE
             example_a_ptr = example_a_ptr->get_next_ptr();

     } // WHILE MORE examples
   
     det_ratio = num_covered/positive_examples->get_num_examples();
     return det_ratio;

}

                               
////////////////////////////////////////////////////////////////////
int inductive_engine_class::is_in_mesh_any_order(atom_class *temp_atom_ptr)
{
 
     return background_knowledge->is_in_mesh_any_order(temp_atom_ptr);
}

////////////////////////////////////////////////////////////////////////////
void inductive_engine_class::get_user_learner_data( int& predicate_rank_algorithm,    
                                                    int& position_name_algorithm,
                                                    double& suff_stop_crit,
                                                   double& nec_stop_crit) 
{
  const  int PREDLOWCHOICE = 1; 
  const  int PREDHIGHCHOICE = 10; 
  const  int POSLOWCHOICE = 1; 
  const  int POSHIGHCHOICE = 2; 
  const  int SUFFLOWCHOICE = 0.0; 
  const  int SUFFHIGHCHOICE = 1.0; 
  const  int NECLOWCHOICE = 0.0; 
  const  int NECHIGHCHOICE = 1.0; 





  for (int i = 0; i < 6; i++) cout << endl;

  cout << "--------------------------------------------------------------------- \n";
  cout << " Choose Predicate Ranking Technique :  \n";
  cout << "      1 -- Simple Set Membership (Positives only..E+) \n";
  cout << "      2 -- Simple Set Membership (Positives and Negatives ..E+ U E- \n"; 
  cout << "      3 -- Greedy Set Membership (Positives only..E+) \n";    
  cout << "      4 -- Greedy Set Membership (Positives and Negatives ..E+ U E- \n";   
  cout << "      5 -- Spot Position Membership (Positives only..E+) \n";
  cout << "      6 -- Spot Position Membership (Positives and Negatives ..E+ U E- \n"; 
  cout << "      7 -- Example Neighbor Membership Single(Positives only..E+) \n";    
  cout << "      8 -- Example Neighbor Membership Single(Positives and Negatives ..E+ U E- \n";   
  cout << "      9 -- Example Neighbor Membership (Positives only..E+) \n";    
  cout << "     10 -- Example Neighbor Membership (Positives and Negatives ..E+ U E- \n";   
  cout << "--------------------------------------------------------------------- \n";
  cout << " \n";

  for (int i = 0; i < 6; i++) cout << endl;
  
  cin >> predicate_rank_algorithm;    
  while ((predicate_rank_algorithm < PREDLOWCHOICE ) || 
         (predicate_rank_algorithm > PREDHIGHCHOICE )) {
         cout << endl << endl;
         cout << "Invalid PREDICATE RANKING choice...\n";
         cout << "     Please enter again between " << PREDLOWCHOICE << " and "
              << PREDHIGHCHOICE << endl;
         predicate_rank_algorithm = DEFAULT_PREDRANK_ALGO;
         cin >> predicate_rank_algorithm;
      
  } //WHILE invalid predicate ranking choice

// --------- DETERMINE POSITION RANKING FOR VARIABLE NAMING ---------------

  for (int i = 0; i < 6; i++) cout << endl;

  cout << "--------------------------------------------------------------------- \n";
  cout << " Choose POSITION Ranking Technique :  \n";
  cout << "      1 -- Greedy Set Membership (Positives only..E+) \n";
  cout << "      2 -- Greedy Set Membership (Positives and Negatives ..E+ U E- \n"; 
  cout << "--------------------------------------------------------------------- \n";
  cout << " \n";

  for (int i = 0; i < 6; i++) cout << endl;

  cin >> position_name_algorithm;    
  while ((position_name_algorithm < POSLOWCHOICE ) || 
         (position_name_algorithm > POSHIGHCHOICE )) {
         cout << endl << endl;
         cout << "Invalid POSITION NAMING choice...\n";
         cout << "     Please enter again between " << POSLOWCHOICE << " and "
              << POSHIGHCHOICE << endl;
         cin >> position_name_algorithm;
      
  } //WHILE invalid position ranking choice

// --------- DETERMINE STOPPING CRITEREA -----------------------------------------

  for (int i = 0; i < 6; i++) cout << endl;

  cout << "--------------------------------------------------------------------- \n";
  cout << " Enter Sufficiency Stopping Critereon...\n";
  cout << "          (Num Pos examples Covered / Total Num Pos examples \n";
  cout << "--------------------------------------------------------------------- \n";
  cout << " \n";

  for (int i = 0; i < 6; i++) cout << endl;

  cin >>  SUFFICIENCY_STOP_CRITEREON;
  while (( SUFFICIENCY_STOP_CRITEREON < SUFFLOWCHOICE) || 
         ( SUFFICIENCY_STOP_CRITEREON > SUFFHIGHCHOICE )) {
         cout << endl << endl;
         cout << "Invalid  SUFFICIENCY_STOP_CRITEREON choice...\n";
         cout << "     Please enter again between " << SUFFLOWCHOICE << " and "
              << SUFFHIGHCHOICE  << endl;
         cin >>  suff_stop_crit;
      
  } //WHILE invalid  SUFFICIENCY_STOP_CRITEREON  choice
   

  for (int i = 0; i < 6; i++) cout << endl;


  cout << "--------------------------------------------------------------------- \n";
  cout << " Enter Necessity Stopping Critereon...\n";
  cout << "          (Num Neg examples Covered / Total Num Neg examples \n";
  cout << "--------------------------------------------------------------------- \n";
  cout << " \n";

  for (int i = 0; i < 6; i++) cout << endl;

  cin >>  nec_stop_crit;
  while (( NECESSITY_STOP_CRITEREON < NECLOWCHOICE) || 
         ( NECESSITY_STOP_CRITEREON > NECHIGHCHOICE )) {
         cout << endl << endl;
         cout << "Invalid  NECESSITY_STOP_CRITEREON choice...\n";
         cout << "     Please enter again between " << NECLOWCHOICE << " and "
              << NECHIGHCHOICE  << endl;
         cin >>  NECESSITY_STOP_CRITEREON ;
      
  } //WHILE invalid  NECESSITY_STOP_CRITEREON  choice
   
  for (int i = 0; i < 6; i++) cout << endl;

  
}// function get_user_learner_data

//-------------------------------------------------------------------
void inductive_engine_class:: make_empty_learned_file()
{
        ofstream    outfile;

        outfile.open("learned.int");
        outfile << "@@@@@@@@@@@@@@";
        outfile.close();
}

//-------------------------------------------------------------------

double inductive_engine_class::get_user_inconsistency_coef()
{
  const    double INCONCOEFLOW = 0.0;
  const    double INCONCOEFHIGH = 1.0;

  double    incon_coef = 0.0;

  for (int i = 0; i < 6; i++) cout << endl;


  cout << "--------------------------------------------------------------------- \n";
  cout << " Enter Example Set Inconsistency Coefficient...\n";
  cout << "          (Max coefficient of tuples appearing in both E+ and E-) \n";
  cout << "--------------------------------------------------------------------- \n";
  cout << " \n";

  for (int i = 0; i < 6; i++) cout << endl;

  cin >>  incon_coef;
  while (( incon_coef < INCONCOEFLOW) || 
         ( incon_coef > INCONCOEFHIGH )) {
         cout << endl << endl;
         cout << "Invalid  inconsistency coefficient choice...\n";
         cout << "     Please enter again between " << INCONCOEFLOW << " and "
              << INCONCOEFHIGH << endl;
         cin >>  incon_coef;
      
  } //WHILE invalid  inconsistency_coeffieicent 

  return incon_coef;
}
   


double inductive_engine_class::check_for_example_inconsistency() 
{
    atom_class          *cur_pos_a_ptr;
    predicate_log_class *neg_example_mesh;
    double               num_inconsistent = 0.0;

    neg_example_mesh = negative_examples->get_predlog_object_ptr();
    cur_pos_a_ptr = get_first_positive_example(); 
    while (cur_pos_a_ptr != NULL) {
         if ( neg_example_mesh->is_member_of_mesh(cur_pos_a_ptr))
               num_inconsistent += 2.0;
         cur_pos_a_ptr = cur_pos_a_ptr->get_next_ptr(); 
    } //WHILE

    return (num_inconsistent / (positive_examples->get_num_examples() +
                                negative_examples->get_num_examples()));


}

