background_knowledge_class::background_knowledge_class()
{
        predicateloglist.initialize();

} // CONSTRUCTOR for background_knowledge_class



///////////////////////////////////////////////////////////////////////////
///  Construct a predicate_log_class matrix of TRUE backgroung facts
///  read from input stream infile.
///////////////////////////////////////////////////////////////////////////
background_knowledge_class::background_knowledge_class(ifstream& infile)
{

list_class<fullstring_class> *flist;     
fullstring_class             *f_ptr;
char                          full_string[ EXTRA_LONG];
char                          gochar = '.';          
char                          tempstr[LONG_STRING_LENGTH];
atom_class                   *a_ptr;
predicate_log_class          *found_ptr;
int                           cur_atom_truthval=2;
char                          cur_atom_predsymbol[STRING_LENGTH];




  // READ IN FIRST BACKGROUND FACT 
   gochar = read_rule(infile, full_string);

   while (gochar == '.') {

        flist = new list_class<fullstring_class>();   
        extract_atom_strings(full_string, flist);       
        f_ptr = flist->get_first();      
        while (f_ptr != NULL) {
              strcpy(tempstr, f_ptr->get_fullstring_symbol());    
              a_ptr = new atom_class(tempstr, f_ptr->get_IS_NEGATIVE()); 

              // EXTRACT THE CURRENT ATOM'S PERTINENT INFO
              if ((f_ptr->get_IS_NEGATIVE()==1))
                   cur_atom_truthval = 0;
              else 
                   cur_atom_truthval = 1;

              strcpy(cur_atom_predsymbol, a_ptr->get_predicate_symbol());

              // CHECK TO SEE IF THE PREDICATE SYMBOL EXISTS IN THE LOG MATRIX
              found_ptr = NULL;
              found_ptr = find_predicate_log(cur_atom_truthval,cur_atom_predsymbol); 
              
              //IF IT DOES NOT EXIST, CREATE ONE
              if (found_ptr == NULL)   {
                       found_ptr = new predicate_log_class(a_ptr);   

                    // ADD the NEW LOG TO THE MATRIX
                       predicateloglist.add_ptr(found_ptr);
              } // IF
              else {
                       // IT EXISTS...JUST ADD ATOM INFO
                       found_ptr->add_new_atom(a_ptr);
              } // ELSE
              f_ptr = f_ptr->get_next_ptr();
              a_ptr->clear();
              delete a_ptr;
        }//WHILE
        
        flist->cleanup();
  //      delete flist;
        gochar = read_rule(infile, full_string);
   } // WHILE

} // CONSTRUCTOR for background_knowledge_class

//__________________________________________________________________________

background_knowledge_class::~background_knowledge_class()
{
        predicateloglist.cleanup();
}

//__________________________________________________________________________
void background_knowledge_class::output()
{
      cout << " - -BEGIN - - - -<background_knowledge_class>_ _ _ _ _ _ _ _ _ _ _\n";
      cout << "The list of position classes is.. \n";
      predicateloglist.print();
      cout << " -  -  END - - - -<background_knowledge_class>_ _ _ _ _ _ _ _ _ _ _\n";

}
//__________________________________________________________________________


predicate_log_class *background_knowledge_class::get_first_predlog_ptr()
{
        return  predicateloglist.get_first();
}

//__________________________________________________________________________
void background_knowledge_class::display(ostream& fout)
{

     predicate_log_class        *predlog_ptr;

     predlog_ptr = predicateloglist.get_first();

     fout << endl << endl;
     while (predlog_ptr != NULL)  {
           predlog_ptr->display(fout);
           fout << endl;
           predlog_ptr = predlog_ptr->get_next_ptr();
     }//WHILE

     fout << "@@@@@@@@@@@@@@@@@@@@@@" << endl;
}



//-------------------------------------------------------------------------

predicate_log_class *background_knowledge_class::find_predicate_log
                  (int truth_p_val, char  instr[STRING_LENGTH])   

{
   predicate_log_class  *predlog_ptr;
   char                  predstr1[STRING_LENGTH];
   int                   cur_truth_val = 2;       //INITIALIZE AT BOTTOM
   int                   found = 0;

   predlog_ptr = predicateloglist.get_first();

   while ((predlog_ptr != NULL) && (!found)) {
       cur_truth_val = predlog_ptr->get_predlog_truthval();
       if (truth_p_val == cur_truth_val) {
            strcpy(predstr1, predlog_ptr->get_predlog_symbol());
             if (strcmp(instr, predstr1) == 0)  {
                   found = 1;
             } // INNER IF
       } // OUTER IF
       if (!found)
              predlog_ptr = predlog_ptr->get_next_ptr();
   }// WHILE

   return predlog_ptr;

}




       
//-------------------------------------------------------------------------

void background_knowledge_class::clear()
{
     predicateloglist.cleanup();

}
//-------------------------------------------------------------------------

void background_knowledge_class::reinitialize_chosen_mesh()
{
   predicate_log_class  *predlog_ptr;
   char                  predstr1[STRING_LENGTH];
   int                   cur_truth_val = 2;       //INITIALIZE AT BOTTOM
   int                   found = 0;

   predlog_ptr = predicateloglist.get_first();

   while (predlog_ptr != NULL) {
        predlog_ptr->reinitialize_chosen(); 
        predlog_ptr = predlog_ptr->get_next_ptr();
   }// WHILE
}
//-------------------------------------------------------------------------

void background_knowledge_class::initialize_predicate_rankings()
{
   predicate_log_class  *predlog_ptr;

   predlog_ptr = predicateloglist.get_first();

   while (predlog_ptr != NULL) {
        predlog_ptr->reset_rank(); 
        predlog_ptr = predlog_ptr->get_next_ptr();
   }// WHILE
}
//-------------------------------------------------------------------------

void background_knowledge_class::initialize_mesh_chosen_and_predrank()
{
   predicate_log_class  *predlog_ptr;

   predlog_ptr = predicateloglist.get_first();

   while (predlog_ptr != NULL) {
        predlog_ptr->reset_rank(); 
        predlog_ptr->reinitialize_chosen(); 
        predlog_ptr = predlog_ptr->get_next_ptr();
   }// WHILE
}
//-------------------------------------------------------------------------

predicate_log_class *background_knowledge_class::get_max_unchosen_predlog()
{
   predicate_log_class  *predlog_ptr;
   char                  predstr1[STRING_LENGTH];
   int                   cur_truth_val = 2;       //INITIALIZE AT BOTTOM
   int                   found = 0;
   double                max_rank = 0.0;
    predicate_log_class  *max_predlog_ptr;  

   predlog_ptr = predicateloglist.get_first();


   // ADVANCE TO THE FIRST UNCHOSEN PRELOG AND INITIALIZE MAX AT THAT RANK
   while ( (predlog_ptr != NULL) && (predlog_ptr->is_chosen())){
          predlog_ptr = predlog_ptr->get_next_ptr();
   } // while preds are all chosen

   if (predlog_ptr != NULL) {
        max_rank = predlog_ptr->get_rank();
        max_predlog_ptr = predlog_ptr;

        predlog_ptr = predlog_ptr->get_next_ptr();


        while (predlog_ptr != NULL) {

             if ((!(predlog_ptr->is_chosen()) &&
                 (predlog_ptr->get_rank() > max_rank))) {
                  max_rank = predlog_ptr->get_rank();
                  max_predlog_ptr = predlog_ptr;
             }// IF

             predlog_ptr = predlog_ptr->get_next_ptr();
        }// WHILE

        max_predlog_ptr->mark_chosen();
        return max_predlog_ptr;   //NULL means all were chosen
   }//IF
   else {  //ALL WERE CHOSEN
        return NULL;
   } // ELSE
}


//////////////////////////////////////////////////////////////////////
////
//////////////////////////////////////////////////////////////////////
int background_knowledge_class::covers(atom_class   *example_a_ptr,
                                       predicate_expression_class
                                         *current_rule_literal_predexp_ptr)  
{
         

        predicate_log_class         *correct_bkg_predlog_ptr;
       int                          cur_truthval;
       char                         cur_bkg_str[STRING_LENGTH];  
       int                          is_covered;

//cout << "inside back::covers:  example_a_ptr is \n";
//example_a_ptr->display();
//cout << endl;


        is_covered = 0;

       //FIND THE CORRECT PREDLOG OBJECT IN MESH
         strcpy(cur_bkg_str, current_rule_literal_predexp_ptr->
                                       get_predicate_symbol());

         if (current_rule_literal_predexp_ptr->get_IS_NEGATIVE()==1)
                      cur_truthval = 0;
         else
                      cur_truthval = 1;

         correct_bkg_predlog_ptr=find_predicate_log(cur_truthval, cur_bkg_str);

         is_covered = correct_bkg_predlog_ptr->is_member_of_mesh(example_a_ptr);
//cout << "is_covered comes back from mesh as...." << is_covered << "\n";

         return is_covered;
}


/////////////////////////////////////////////////////////////////////
int background_knowledge_class::is_in_mesh_any_order(atom_class *temp_atom_ptr)
{
      predicate_log_class   *predlog_ptr;
      int                    found;
      char                   pred_sym[STRING_LENGTH];


      predlog_ptr = get_first_predlog_ptr();

      found = 0;
      while (predlog_ptr != NULL) {
strcpy(pred_sym, predlog_ptr->get_predlog_symbol());
      if (predlog_ptr->is_member_of_mesh_any_order(temp_atom_ptr)==1)
               found = 1;
cout << pred_sym << ":      " << predlog_ptr->is_member_of_mesh_any_order(temp_atom_ptr)
                  << endl;


              predlog_ptr = predlog_ptr->get_next_ptr();

      } //WHILE
      return found;                                                       
}
