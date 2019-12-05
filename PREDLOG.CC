predicate_log_class::predicate_log_class()
   { 
      val = 0;
      chosen = 0;
      truth_val = BOTTOM;
      predlogsymbol = NULL;
      predlognextnode = NULL;

   }

predicate_log_class::predicate_log_class(int n)
   {
      val = n;
      chosen = 0;
      truth_val = BOTTOM;
      predlogsymbol = NULL;
      predlognextnode = NULL;

   }

///////////////////////////////////////////////////////////////////////
/// Creates a new predicate_log_class by initializing its
///  fields to the corresponding atom fields and by inserting
///  each constant in the atom's list into the correct
///  position_class object in constantposlist.
///
//////////////////////////////////////////////////////////////////////
predicate_log_class::predicate_log_class(atom_class *newatom)
   {
       char              tempstr[STRING_LENGTH];
       position_class   *pos_ptr;
       constant_class   *atom_c_ptr;  
       int               position_ID;

       val = 0;
       chosen = 0;

       strcpy(tempstr,newatom->get_predicate_symbol());

       predlogsymbol = new predicate_symbol_class(tempstr);
       if (newatom->get_IS_NEGATIVE() == 1)
             truth_val = 0;
       else
             truth_val = 1;

        atom_c_ptr = newatom->get_first_constant();

        while (atom_c_ptr != NULL) {
           position_ID = constantposlist.get_length() + 1;

           //CREATE A NEW ARGUMENT POSITION
            pos_ptr = new position_class(position_ID);
         
           //ADD THE CONSTANT TO THAT POSITION LIST
            pos_ptr->add_constant(atom_c_ptr->get_constant_symbol());

           //ATTACH THE POSITION LIST TO THE PREDICATE_LOG OBJECT
            constantposlist.add_ptr(pos_ptr);

            atom_c_ptr = atom_c_ptr->get_next_ptr();
        } //WHILE
   }


void predicate_log_class::assign_val(int n)
  {
    val = n;
  }
void predicate_log_class::mark_chosen()
  {
      chosen = 1;
  }

void predicate_log_class::reinitialize_chosen()
  {
      chosen = 0;
  }
int predicate_log_class::is_chosen()
  {
      return chosen;
  }

int predicate_log_class::get_value()
{
     return val;
}

int predicate_log_class::get_chosen()
{
     return chosen;
}
int predicate_log_class::get_rank()
{
     return val;
}

int predicate_log_class::get_num_positions()
{
     return constantposlist.get_length();
}

void predicate_log_class::output()
  {
     char       tempstr[STRING_LENGTH];

     cout << "------------<predicate_log_class>------------------------\n";
     cout << "val is  " << val << endl;
     cout << "chosen is  " << chosen << endl;
     cout << "truth val is..." << truth_val << endl;
     strcpy(tempstr, predlogsymbol->get_predicate_symbol() );
     cout << "predlogsymbol is    " << tempstr << endl;
     cout << "the list of position class is.. \n";
     constantposlist.print();
     cout << "Next pointer predlognextnode is...  " << predlognextnode << endl;
     cout << "------------<predicate_log_class>-------------------------\n";
 } 


void predicate_log_class::clear()
{
   constantposlist.cleanup();
}

void predicate_log_class::assign_next(predicate_log_class *v_ptr)
 {
       predlognextnode = v_ptr;
 }

predicate_log_class  *predicate_log_class::get_next_ptr()
 {
       return predlognextnode;
}

 
position_class *predicate_log_class::get_first_pos_ptr()
{
    return constantposlist.get_first();
}

int predicate_log_class::get_predlog_truthval()
{
    return truth_val;
}
char *predicate_log_class::get_predlog_symbol()
{
    char     tempstr[STRING_LENGTH];

    strcpy(tempstr, (predlogsymbol->get_predicate_symbol()) ); 
    return tempstr;
}
void predicate_log_class::add_position(position_class *pos_ptr)
{
     constantposlist.add_ptr(pos_ptr);
}

///////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////
void predicate_log_class::add_new_atom(atom_class *newatom)
   {
       char              tempstr[LONG_STRING_LENGTH];
       position_class   *pos_ptr;
       constant_class   *atom_c_ptr;  

       val = 0;

        // ADD THE CONSTANTS CONTAINED IN THE NEWATOM TO PRED LOG OBJECT

        //VERIFY THAT THE CORRECT NUMBER OF ARGUMENTS ARE COMING IN
        if (newatom->get_num_constants() == constantposlist.get_length()) {
        
            atom_c_ptr = newatom->get_first_constant();
            pos_ptr = get_first_pos_ptr();

            while (atom_c_ptr != NULL) {
         
                //ADD THE CONSTANT TO THAT POSITION LIST
                pos_ptr->add_constant(atom_c_ptr->get_constant_symbol());
                atom_c_ptr = atom_c_ptr->get_next_ptr();
                pos_ptr = pos_ptr->get_next_ptr();
            } //WHILE
         }//IF
         else  {
             cout << "ERROR...(predlog.cc)incorrect number of arguments.\n";
             exit(1);
         }//ELSE
   }
 
//--------------------------------------------------------------------------------
void predicate_log_class::display(ostream& fout)
{
    constant_class         *c_ptr;
    position_class         *pos_ptr;
    char                    pred_symbol_str[STRING_LENGTH];
    char                    neg_symbol = ' ';
   
    if (truth_val == 0) neg_symbol = '~';
    strcpy(pred_symbol_str, get_predlog_symbol() );
    fout << "Predicate Symbol:  " << neg_symbol <<pred_symbol_str 
         << "       Ranked:  " << get_rank() 
         << "   Chosen Status:   " << is_chosen() << endl;
    fout << "----------------   " << endl;
    pos_ptr = get_first_pos_ptr();  
    while (pos_ptr != NULL ) {
         fout << "        Position " << pos_ptr->get_value() << 
                 "   (variable " << pos_ptr->get_variable_name() << ")" 
              << "    Position Rank:   " << pos_ptr->get_posrank() <<   
                        endl;
         c_ptr = pos_ptr->get_first_poscon_ptr();
         while (c_ptr != NULL) {
             fout << "             ";
             c_ptr->display(fout);
             fout << endl;
             c_ptr = c_ptr->get_next_ptr();
         } // WHILE

         pos_ptr = pos_ptr->get_next_ptr();
    } // WHILE

}

//---------------------------------------------------------------------------
// Returns spot number in  some position of predicate_log_object
// which constant c_ptr was found; zero if not found.
//---------------------------------------------------------------------------
int predicate_log_class::has_constant(constant_class *c_ptr)
{
    position_class         *pos_ptr;
    int                     found = 0;
   
    pos_ptr = get_first_pos_ptr();  

    while ((pos_ptr != NULL ) && (found == 0))  {
         found =  pos_ptr->is_a_member(c_ptr);
         pos_ptr = pos_ptr->get_next_ptr();
    } // WHILE

    return found;

}

//--------------------------------------------------------------------------

int predicate_log_class::has_constant_in_position(int             position_num,   
                                                  constant_class *c_ptr)
{
    position_class    *pos_ptr;

    pos_ptr = constantposlist.get_ith(position_num);
    if (pos_ptr != NULL)
        return   pos_ptr->is_a_member(c_ptr);
    else
        return 0;
}

//--------------------------------------------------------------------------

int predicate_log_class::has_constant_in_pos_spot(int             position_num,   
                                                  int             spot_num,
                                                  constant_class *c_ptr)
{
    position_class  *pos_ptr;
    pos_ptr = constantposlist.get_ith(position_num);
    if (pos_ptr != NULL)
        return   pos_ptr->is_a_member_in_spot(spot_num, c_ptr);
    else
        return 0;
}

//---------------------------------------------------------------------------
//  Checks that named variables are named equivalently if the 
//  position columns are equal.
//---------------------------------------------------------------------------
void predicate_log_class::verify_named_variables()
{

      char    source_letter = ' ';
      
      position_class *LHS_pos_ptr;
      position_class *RHS_pos_ptr;

      LHS_pos_ptr = get_first_pos_ptr(); 

      while (LHS_pos_ptr != NULL) {
             source_letter = LHS_pos_ptr->get_variable_name(); 

             RHS_pos_ptr = LHS_pos_ptr->get_next_ptr();
             while (RHS_pos_ptr != NULL) {     
                   if (equal_positions(LHS_pos_ptr, RHS_pos_ptr)==1) 
                          RHS_pos_ptr->assign_variable_name(source_letter);

                   RHS_pos_ptr = RHS_pos_ptr->get_next_ptr(); 
             }//WHILE
            LHS_pos_ptr = LHS_pos_ptr->get_next_ptr();
      } //WHILE

}//VERIFY_NAMED_VARIABLES

//---------------------------------------------------------------------------
// Traverses each position's constantlist  and names position variables' 
// equally if the respective positions are equal.  This version
// starts with a start_char.
//---------------------------------------------------------------------------
void predicate_log_class::name_variables(char start_char)
{

      char    nextchar = start_char;
      char    source_letter = ' ';
      
      position_class *LHS_pos_ptr;
      position_class *RHS_pos_ptr;

   
      LHS_pos_ptr = get_first_pos_ptr(); 

      if (LHS_pos_ptr != NULL)  
            LHS_pos_ptr->assign_variable_name(nextchar++);

      while (LHS_pos_ptr != NULL) {
             source_letter = LHS_pos_ptr->get_variable_name(); 

             RHS_pos_ptr = LHS_pos_ptr->get_next_ptr();
             while (RHS_pos_ptr != NULL) {     
                   if (equal_positions(LHS_pos_ptr, RHS_pos_ptr)==1) 
                          RHS_pos_ptr->assign_variable_name(source_letter);
                   else
                          RHS_pos_ptr->assign_variable_name(nextchar++);

                   RHS_pos_ptr = RHS_pos_ptr->get_next_ptr(); 
             }//WHILE
            LHS_pos_ptr = LHS_pos_ptr->get_next_ptr();
      } //WHILE

}//NAME_VARIABLES


//////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////
void predicate_log_class::reset_rank()
{
      val = 0;
}

//////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////
void predicate_log_class::increment_rank()
{
      val++;
}

void predicate_log_class::decrement_rank()
{
      val--;
}
void predicate_log_class::increase_rank(int increase_amount)
{
      val+=increase_amount;
}
void predicate_log_class::decrease_rank(int decrease_amount)
{
      val-=decrease_amount;
}

void predicate_log_class::mark_mesh_NOT_taken()
{
    position_class         *pos_ptr;
   
    pos_ptr = get_first_pos_ptr();  

    while (pos_ptr != NULL ) {
           pos_ptr->mark_all_constants_NOT_taken();
           pos_ptr = pos_ptr->get_next_ptr();
    } //WHILE
}


//-------------------------------------------------------------------

void predicate_log_class::initialize_position_ranks()
{
   position_class       *pos_ptr;

   pos_ptr = get_first_pos_ptr();

   while (pos_ptr != NULL) {
        pos_ptr->initialize_posrank();
        pos_ptr = pos_ptr->get_next_ptr();
   }// WHILE
}
//-------------------------------------------------------------------

void predicate_log_class::initialize_position_chosen_flags()
{
   position_class       *pos_ptr;

   pos_ptr = get_first_pos_ptr();

   while (pos_ptr != NULL) {
        pos_ptr->initialize_position_chosen();
        pos_ptr = pos_ptr->get_next_ptr();
   }// WHILE
}
//-------------------------------------------------------------------

char predicate_log_class::get_max_variable_name()
{
   char                  maxchar; 
   position_class       *pos_ptr;

   pos_ptr = get_first_pos_ptr();
   if (pos_ptr != NULL)  {
        maxchar = pos_ptr->get_variable_name();
        pos_ptr = pos_ptr->get_next_ptr();
   }
   else {
        cout << "Problem with learner position mesh...exiting program. \n";
        exit(1);
   }

   while (pos_ptr != NULL) {
        if (maxchar < pos_ptr->get_variable_name())
                 maxchar = pos_ptr->get_variable_name();
        pos_ptr = pos_ptr->get_next_ptr();
   }// WHILE

   return maxchar;
}

//-------------------------------------------------------------------

position_class *predicate_log_class::get_max_ranked_unchosen_position_ptr() 
{
   int                   max_rank = -99;
   
   position_class       *pos_ptr, *max_pos_ptr;

   pos_ptr = get_first_pos_ptr();
   while ((pos_ptr != NULL) && (pos_ptr->get_position_chosen()==1)){
             pos_ptr = pos_ptr->get_next_ptr();
   } //WHILE

   // INITIALIZE MAX TO  POS_PTR
   if (pos_ptr != NULL)  
        max_rank = pos_ptr->get_posrank();

   max_pos_ptr = pos_ptr;

   if (pos_ptr != NULL)
        pos_ptr = pos_ptr->get_next_ptr();
   

   while (pos_ptr != NULL) {
      if (pos_ptr->get_position_chosen()==0) {

          if (max_rank < pos_ptr->get_posrank() ) {
                 max_rank = pos_ptr->get_posrank();
                 max_pos_ptr = pos_ptr;
           } //IF NEW MAX
      }//IF NOT CHOSEN

        pos_ptr = pos_ptr->get_next_ptr();
   }// WHILE

   return max_pos_ptr;   // IF MAX_POS_PTR IS NULL, THEY WERE ALL CHOSEN
}
////////////////////////////////////////////////////////////////////////////////
////  
////
///////////////////////////////////////////////////////////////////////////////
int predicate_log_class::is_member_of_mesh(atom_class *example_a_ptr)
{
    position_class    *pos_ptr;
    constant_class    *mesh_c_ptr;
    constant_class    *mesh_LHS_c_ptr;

    constant_class    *example_c_ptr; 
    char               LHS_cons_str[STRING_LENGTH];
    char               new_cons_str[STRING_LENGTH];
    int                spot_number;
    int                covered_so_far;
    


    example_c_ptr = example_a_ptr->get_first_constant();

    strcpy(LHS_cons_str, example_c_ptr->get_constant_symbol());
    pos_ptr = get_first_pos_ptr();
    mesh_LHS_c_ptr = pos_ptr->get_first_poscon_ptr();

    spot_number = 1;
    covered_so_far = 0;
    while ((mesh_LHS_c_ptr != NULL) && (!(covered_so_far))) {
        
       //SEARCH FOR NEXT OCCURENCE OF LHS_cons_str
       strcpy(new_cons_str, mesh_LHS_c_ptr->get_constant_symbol());
       if (strcmp(LHS_cons_str, new_cons_str)==0) {

            //CHECK IF OTHER CONSTANTS OF INPUT EXAMPLES RESIDE IN 
            // NEIGHBORING SPOTS

            //...Initialize and advance past the LHS column
            pos_ptr = get_first_pos_ptr();  
            if (pos_ptr != NULL)
                 pos_ptr = pos_ptr->get_next_ptr();

            //GET THE NEXT CONSTANT IN THE GROUND EXAMPLE
            example_c_ptr = example_a_ptr->get_first_constant();

            covered_so_far = 1; 
            while ((pos_ptr != NULL) && (covered_so_far))  {
                 example_c_ptr = example_c_ptr->get_next_ptr();
                 if (pos_ptr->is_a_member_in_spot(spot_number,
                                           example_c_ptr)==0)
                       covered_so_far = 0;
                 else
                       pos_ptr=pos_ptr->get_next_ptr();
            } //WHILE    

       } //IF

        mesh_LHS_c_ptr = mesh_LHS_c_ptr->get_next_ptr();
        spot_number++;
    } //WHILE
    
   return covered_so_far;
}
////////////////////////////////////////////////////////////////////////////////
////  
////
///////////////////////////////////////////////////////////////////////////////
int predicate_log_class::is_member_of_mesh_any_order(atom_class *example_a_ptr)
{
    position_class    *example_pos_ptr;
    position_class    *mesh_pos_ptr;
    position_class    *neigh_pos_ptr;
    constant_class    *mesh_c_ptr;
    constant_class    *example_c_ptr; 
    constant_class    *neigh_example_c_ptr; 

    
    char               example_cons_str[STRING_LENGTH];
    char               curmesh_cons_str[STRING_LENGTH];
    char               jenn_tempstr[STRING_LENGTH]; 
    char               jenn_tempstr2[STRING_LENGTH];
    char               jenn_tempstr3[LONG_STRING_LENGTH];


    int                mesh_spot_number;
    int                covered_so_far;
    int                num_found = 0;
    int                found;
    int                neigh_pos_number;
    


    int max_spot_num = 0;
    int max_num_found = 0;


//strcpy(jenn_tempstr2, this->get_predlog_symbol());
//cout << "MESH for predicate:      " << jenn_tempstr2 << endl;
//strcpy(jenn_tempstr3, example_a_ptr->get_fullstring());
//cout << "         input example is:   " << jenn_tempstr3 << endl;



    example_c_ptr = example_a_ptr->get_first_constant();

    // FIND THE EXAMPLE CONSTANT SOMEWHERE IN MESH
    while (example_c_ptr != NULL) {

          strcpy(example_cons_str, example_c_ptr->get_constant_symbol());       

          mesh_pos_ptr =  get_first_pos_ptr();   
          while (mesh_pos_ptr != NULL) {
               mesh_c_ptr = mesh_pos_ptr->get_first_poscon_ptr();
               mesh_spot_number = 0;
               while (mesh_c_ptr != NULL) {
                    mesh_spot_number++;
                    strcpy(curmesh_cons_str, mesh_c_ptr->get_constant_symbol());


                    //EXAMPLE CONSTANT FOUND !!!
                    if (strcmp(example_cons_str, curmesh_cons_str)==0) {     
                      //CHECK FOR EXAMPLE'S OTHER CONSTANTS PRESENCE IN MESH
                      //    NEIGHBORING SPOTS

                     //GET THE NEXT CONSTANT IN THE GROUND EXAMPLE
                      num_found = 1;
                      neigh_example_c_ptr = example_a_ptr->get_first_constant();
                      while (neigh_example_c_ptr != NULL)   {

                           if (neigh_example_c_ptr != example_c_ptr)  {

                              // SEARCH THE MESH IN ALL POSITIONS IN SPOT NUM
                              //   FOR NEIGHBOR
                              found = 0;
                              neigh_pos_ptr = get_first_pos_ptr();        
                              neigh_pos_number = 1;
                              while ((neigh_pos_ptr != NULL) && (found==0))  {
                                  if( (neigh_pos_ptr->is_a_member_in_spot(mesh_spot_number,
                                           neigh_example_c_ptr)) != 0){

                                       num_found++;
                                       found = 1;

                                  } //IF neighbor is in mesh_spot_number in diff pos
                                  else {
                                       neigh_pos_ptr=neigh_pos_ptr->get_next_ptr();
                                       neigh_pos_number++;
                                  }//ELSE 
                              } //WHILE  more positions in mesh to check for neighbor appear  
                            }//  IF neigh_example_c_ptr != example_c_ptr
                            neigh_example_c_ptr = neigh_example_c_ptr->get_next_ptr(); 
                       }//WHILE more neighbor constants left to check
                      if (num_found > max_num_found) {
                           max_num_found = num_found;
                           max_spot_num = mesh_spot_number;
                      } // IF num_found > max_num_found
                  }//IF THE EXAMPLE CONSTANT WAS FOUND

                  mesh_c_ptr = mesh_c_ptr->get_next_ptr();
               } //WHILE more constants in this mesh position
               mesh_pos_ptr = mesh_pos_ptr->get_next_ptr();
          } // WHILE MORE MESH POSITIONS TO CHECK
  
         example_c_ptr = example_c_ptr->get_next_ptr();
    } //WHILE more example constants to find in the mesh
    
   if (max_num_found >= (example_a_ptr->get_num_constants()) ) {
          return 1;
   } //IF
   else {
//cout << "about to return 0 \n";
          return 0;

   } //ELSE
}
