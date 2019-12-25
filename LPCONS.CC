#pragma once

#include <iostream>

#include "LOGIC_PR.H"
#include "UTILITY2.H"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
///   Show state displays the current state of the logic program
///   by displaying the atom information of all TRUE variables
///   and the TRUE NEGATIVE variables by displaying negative literals
/////////////////////////////////////////////////////////////////////////////

void logic_program_class::show_state(ostream& fout)
{
    int   n_trues, n_falses, n_bottoms, n_tops;


    fout << " TRUE POSITIVE FACTS\n";
    fout << " -------------------  \n";
    print_truth_atoms(fout, 1);
    fout << "\n";
    fout << " TRUE NEGATIVE FACTS \n";
    fout << " --------------------  \n";
    print_truth_atoms(fout,0);
    fout << "\n";


    if ((total(&n_trues, &n_falses, &n_bottoms, &n_tops))==0) {
       fout << "The model is NOT TOTAL. \n";
       fout << "---------------------- \n";
       fout << " The following vertices were unassigned:\n";
       print_truth_atoms(fout, 2);             // 2 means BOTTOM
    }
    else if ((total(&n_trues, &n_falses, &n_bottoms, &n_tops))==2) {
       fout << "The model is CONTRADICTORY.\n";
       fout << "-------------------------- \n";
     fout << "The following vertices were ambiguously assigned :\n";
     print_truth_atoms(fout, 3);             // 3 means TOP
     fout << "\n";
    }
    else
       fout << "The model is TOTAL. \n";
    fout << "\n  \n";

    fout << "There were " << n_trues << " assigned TRUES. \n";
    fout << "There were " << n_falses << " assigned FALSES. \n";
    fout << "There were " << n_bottoms << " assigned BOTTOMS. \n";
    fout << "There were " << n_tops << " assigned TOPS. \n";
    fout << "\n \n ";

} // SHOW_STATE

/////////////////////////////////////////////////////////////////////////
/// Prints all vertex values with truth value  0,1,2,3 (F, T, BOT, TOP)
/////////////////////////////////////////////////////////////////////////
void logic_program_class::print_truth_atoms(ostream& fout, int t_val)
{

   vertex_class    *v_ptr;
   char            neg_symbol;

   if (t_val == 0) 
          neg_symbol = '~';
   else
          neg_symbol = ' ';

   v_ptr = Vertexlist.get_first();
   

   while (v_ptr != nullptr) {
       if ((v_ptr->get_truth())  == t_val)
           fout << neg_symbol << v_ptr->get_atominfo() << " ." << "\n";
       v_ptr = v_ptr->get_next_ptr();
   }// WHILE


} // PRINT_TRUTH_ATOMS



///////////////////////////////////////////////////////////////////////////
///  Traverse the program graph and find the vertex housing 
///  the same string as instr. 
///  
///////////////////////////////////////////////////////////////////////////
vertex_class *logic_program_class::find_fullstring_in_graph(
                                     char instr[LONG_STRING_LENGTH])

{
   body_node_class    *b_ptr;
   vertex_class       *v_ptr;
   char                tempstr1[LONG_STRING_LENGTH]; 
   char                tempstr2[LONG_STRING_LENGTH]; 

   strcpy(tempstr1, instr);
   v_ptr = Vertexlist.get_first();

   while (v_ptr != nullptr) {
       strcpy(tempstr2, v_ptr->get_atominfo());
       if (strcmp(tempstr1, tempstr2) == 0) 
              return v_ptr;
       v_ptr = v_ptr->get_next_ptr();
   }// WHILE
   
   return nullptr;

}


///////////////////////////////////////////////////////////////////////////
///  Construct a logic program by reading an input stream
///  with EXTENSIONAL GROUND RULES using sentential variables in
///  in propositional logic.
///////////////////////////////////////////////////////////////////////////
logic_program_class::logic_program_class(ifstream& infile)
{

vertex_class           *head_v_ptr, *sub_v_ptr;
body_node_class        *ext_b_ptr;
rule_class             *r_ptr;
fullstring_class       *f_ptr;
int                    head;
int                    cur_sub_val;

list_class<fullstring_class>  *flist; 

char                  full_string[ EXTRA_LONG];
char                  gochar = '.';          
int                   vertex_count=1;
char                  tempstr[LONG_STRING_LENGTH];


  // READ IN FIRST EXTENSIONAL RULE
   gochar = *read_rule(infile, full_string);

   while (gochar == '.') {

       // CREATE A LIST OF FULLSTRING VERSIONS OF EXTENSIONAL RULE'S ATOMS
        flist = new list_class<fullstring_class>();
        extract_atom_strings(full_string, flist);

       // EXAMINE THE FIRST ATOM...THE HEAD OF THE EXTENSIONAL RULE
        f_ptr = flist->get_first();
        strcpy(tempstr,f_ptr->get_fullstring_symbol());        
      
       // DETERMINE WHETHER OR NOT FIRST ATOM ALREADY EXISTS
        head_v_ptr = find_fullstring_in_graph(tempstr);

        if (head_v_ptr == nullptr)   {        // CREATE NEW VERTEX
              head = vertex_count++; 
              head_v_ptr = new vertex_class(tempstr, head, f_ptr->get_IS_NEGATIVE());      
              Vertexlist.add_ptr(head_v_ptr); 
        } //IF
        else {                             // VERTEX ALREADY EXISTS
              head = head_v_ptr->get_value();
        } // ELSE
   
       //********************************************************************//
       // head_v_ptr NOW POINTS TO THE VERTEX OF THE HEAD ATOM in GRAPH;     //
       //********************************************************************//

         
        //*****************************************************************************//
        //  CREATE BODY :
        
        /*
        Create a body node and attach it to the VERTEX head_v_ptr's bodylist.
        
        For each fullstring atom in the subgoal list DO
             -- find the vertex housing the subgoal's fullstring atom 
             -- if it does not exist
                 +  create a vertex with that fullstring and VERTEXCOUNT as val;  ATTACH to graph
                 +  call this newly created  vertex, that pointed to by "sub_v_ptr"
                 +  assign cur_sub_num that integer val      
                else {it does exist}
                 +  assign cur_sub_num the _found_ vertex's val
                 +  call the found vertex's ptr:  "sub_v_ptr"
                    
        
             -- if subgoal is positive
                  +  create a literal node with CUR_SUB_VAL as the value and v_ptr: sub_v_ptr 
                  +  attach the literal onto the positive literal list of ext_b_ptr
                  +  create a positive appearance node with v_ptr=head_v_ptr, b_ptr=ext_b_ptr, 
                     val=head;  ATTACH TO THE VERTEX sub_v_ptr'S positive appearance list
        
             -- if subgoal is negative
                  +  create a literal node with CUR_SUB_VAL as the value and v_ptr: sub_v_ptr 
                  +  attach the literal onto the negative literal list of ext_b_ptr
                  +  create a negative appearance node with v_ptr=head_v_ptr, b_ptr=ext_b_ptr, 
                     val=head;  ATTACH TO THE VERTEX sub_v_ptr'S negative appearance list
        
        */
        //*************************************************************************************//
         ext_b_ptr = new body_node_class();
         head_v_ptr->add_body(ext_b_ptr);

        // IF HEAD IS A NEGATIVE FACT, ASSIGN FALSE
        if (f_ptr->get_IS_NEGATIVE()) {
            ext_b_ptr-> set_body_status(0);    
            ext_b_ptr-> set_pos_assess(0);    
            ext_b_ptr-> set_neg_assess(0);    
            ext_b_ptr-> assign_negative_fact(1);
        } // IF NEGATIVE HEAD
              

         // FOR EACH SUBGOAL IN THE RULE BODY....
         f_ptr = f_ptr->get_next_ptr();

         while (f_ptr != nullptr) {

            strcpy(tempstr,f_ptr->get_fullstring_symbol());        

            // DETERMINE WHETHER OR NOT SBUGOAL ATOM ALREADY EXISTS
            sub_v_ptr = find_fullstring_in_graph(tempstr);

            if (sub_v_ptr == nullptr)   {        // CREATE NEW VERTEX FOR CURRENT SUBGOAL
                  cur_sub_val = vertex_count++; 
                  sub_v_ptr = new vertex_class(tempstr, cur_sub_val);  
                  Vertexlist.add_ptr(sub_v_ptr); 
            } //IF
           else {                             // SUBGOAL VERTEX ALREADY EXISTS
                  cur_sub_val = sub_v_ptr->get_value();
            } // ELSE

           if (f_ptr->get_IS_NEGATIVE()) {    
                 ext_b_ptr->add_neg_literal(cur_sub_val, sub_v_ptr, nullptr);

                 //sub_v_ptr->add_neg_appearance(head, head_v_ptr, ext_b_ptr);
                 rule_class *p_ptr = new rule_class();
                 p_ptr->assign_val(head);
                 p_ptr->assign_body_ptr(ext_b_ptr);
                 p_ptr->assign_vertex_ptr(head_v_ptr);

                 sub_v_ptr->neg_appearances.add_ptr(p_ptr);
   
           } // IF CURRENT SUBGOAL IS NEGATIVE
           else  {  // CUR SUBGOAL IS POSITIVE
                 ext_b_ptr->add_pos_literal(cur_sub_val, sub_v_ptr, nullptr);

                 //sub_v_ptr->add_pos_appearance(head, head_v_ptr, ext_b_ptr);
                 rule_class *p_ptr = new rule_class();
                 p_ptr->assign_val(head);
                 p_ptr->assign_body_ptr(ext_b_ptr);
                 p_ptr->assign_vertex_ptr(head_v_ptr);

                 sub_v_ptr->pos_appearances.add_ptr(p_ptr);

           } // ELSE

          // ADVANCE TO THE NEXT FULLSTRING VERSIONED ATOM IN FULLSTRING LIST
          f_ptr = f_ptr->get_next_ptr();

     } // WHILE THERE ARE MORE SUBGOAL ATOMS (f_ptr != nullptr)

    //***************************************************************//
    // ADD THE RULE TO THE PROGRAM'S RULE LIST
    //***************************************************************//
    add_rule(head, head_v_ptr, ext_b_ptr);


    // READ IN THE NEXT RULE IN STRING FORM
    gochar = *read_rule(infile, full_string);

    flist->cleanup();
//    delete flist;

  }//WHILE there are more rules (gochar == '.')


   Num_Variables = Vertexlist.get_length();

   // PREASSIGN VARIABLES TO FALSE AS MANDATED IN GLOBAL VARIABLE
   //   "Preassign_False_Percent"  AND "Num_Preassign_False"
     preassign_false_variables();

    infile.close();
    flist->cleanup(); 


} // LOGIC_PROGRAM CONSTRUCTOR...INPUT FILE  OF EXTENSIONAL RULES



///////////////////////////////////////////////////////////////////////////
///  Augments a ground logic program parsing an input extensional (ground)
///  rule into head, body, vertex, body, literals, appearances.
///////////////////////////////////////////////////////////////////////////
void logic_program_class::add_extensional_rule(char new_rule[EXTRA_LONG]) 
{
vertex_class           *head_v_ptr, *sub_v_ptr;
body_node_class        *ext_b_ptr;
rule_class             *r_ptr;
fullstring_class       *f_ptr;
int                    head;
int                    cur_sub_val;

list_class<fullstring_class>  *flist; 

char                  full_string[ EXTRA_LONG];
char                  gochar = '.';          
char                  tempstr[LONG_STRING_LENGTH];





  // READ IN FIRST EXTENSIONAL RULE
   strcpy(full_string, new_rule);

  // CREATE A LIST OF FULLSTRING VERSIONS OF EXTENSIONAL RULE'S ATOMS
   flist = new list_class<fullstring_class>();
   extract_atom_strings(full_string, flist);

   // EXAMINE THE FIRST ATOM...THE HEAD OF THE EXTENSIONAL RULE
   f_ptr = flist->get_first();
   strcpy(tempstr,f_ptr->get_fullstring_symbol());        
      
   // DETERMINE WHETHER OR NOT FIRST ATOM ALREADY EXISTS
   head_v_ptr = find_fullstring_in_graph(tempstr);

   if (head_v_ptr == nullptr)   {        // CREATE NEW VERTEX
        head = (Vertexlist.get_length() + 1);
        head_v_ptr = new vertex_class(tempstr, head, f_ptr->get_IS_NEGATIVE());      
        Vertexlist.add_ptr(head_v_ptr); 
    } //IF
    else {                             // VERTEX ALREADY EXISTS
         head = head_v_ptr->get_value();
    } // ELSE
   
    //********************************************************************//
    // head_v_ptr NOW POINTS TO THE VERTEX OF THE HEAD ATOM in GRAPH;     //
    //********************************************************************//

         
    //*****************************************************************************//
    //  CREATE BODY :
    /*
        Create a body node and attach it to the VERTEX head_v_ptr's bodylist.
        
        For each fullstring atom in the subgoal list DO
             -- find the vertex housing the subgoal's fullstring atom 
             -- if it does not exist
                 +  create a vertex with that fullstring and VERTEXCOUNT as val;  ATTACH to graph
                 +  call this newly created  vertex, that pointed to by "sub_v_ptr"
                 +  assign cur_sub_num that integer val      
                else {it does exist}
                 +  assign cur_sub_num the _found_ vertex's val
                 +  call the found vertex's ptr:  "sub_v_ptr"
                    
        
             -- if subgoal is positive
                  +  create a literal node with CUR_SUB_VAL as the value and v_ptr: sub_v_ptr 
                  +  attach the literal onto the positive literal list of ext_b_ptr
                  +  create a positive appearance node with v_ptr=head_v_ptr, b_ptr=ext_b_ptr, 
                     val=head;  ATTACH TO THE VERTEX sub_v_ptr'S positive appearance list
        
             -- if subgoal is negative
                  +  create a literal node with CUR_SUB_VAL as the value and v_ptr: sub_v_ptr 
                  +  attach the literal onto the negative literal list of ext_b_ptr
                  +  create a negative appearance node with v_ptr=head_v_ptr, b_ptr=ext_b_ptr, 
                     val=head;  ATTACH TO THE VERTEX sub_v_ptr'S negative appearance list
        
    */
    //*************************************************************************************//
         ext_b_ptr = new body_node_class();
         head_v_ptr->add_body(ext_b_ptr);

        // IF HEAD IS A NEGATIVE FACT, ASSIGN FALSE
        if (f_ptr->get_IS_NEGATIVE()) {
            ext_b_ptr-> set_body_status(0);    
            ext_b_ptr-> set_pos_assess(0);    
            ext_b_ptr-> set_neg_assess(0);    
            ext_b_ptr-> assign_negative_fact(1);
        } // IF NEGATIVE HEAD
              

         // FOR EACH SUBGOAL IN THE RULE BODY....
         f_ptr = f_ptr->get_next_ptr();

         while (f_ptr != nullptr) {

            strcpy(tempstr,f_ptr->get_fullstring_symbol());        

            // DETERMINE WHETHER OR NOT SBUGOAL ATOM ALREADY EXISTS
            sub_v_ptr = find_fullstring_in_graph(tempstr);

            if (sub_v_ptr == nullptr)   {        // CREATE NEW VERTEX FOR CURRENT SUBGOAL
                  cur_sub_val = 
        (Vertexlist.get_length() + 1);

                  sub_v_ptr = new vertex_class(tempstr, cur_sub_val,
                                                f_ptr->get_IS_NEGATIVE());      
                  Vertexlist.add_ptr(sub_v_ptr); 
            } //IF
           else {                             // SUBGOAL VERTEX ALREADY EXISTS
                  cur_sub_val = sub_v_ptr->get_value();
            } // ELSE

           if (f_ptr->get_IS_NEGATIVE()) {    
                 ext_b_ptr->add_neg_literal(cur_sub_val, sub_v_ptr, nullptr);

                 //sub_v_ptr->add_neg_appearance(head, head_v_ptr, ext_b_ptr);
                 rule_class *p_ptr = new rule_class();
                 p_ptr->assign_val(head);
                 p_ptr->assign_body_ptr(ext_b_ptr);
                 p_ptr->assign_vertex_ptr(head_v_ptr);

                 sub_v_ptr->neg_appearances.add_ptr(p_ptr);
   
           } // IF CURRENT SUBGOAL IS NEGATIVE
           else  {  // CUR SUBGOAL IS POSITIVE
                 ext_b_ptr->add_pos_literal(cur_sub_val, sub_v_ptr, nullptr);

                 //sub_v_ptr->add_pos_appearance(head, head_v_ptr, ext_b_ptr);
                 rule_class *p_ptr = new rule_class();
                 p_ptr->assign_val(head);
                 p_ptr->assign_body_ptr(ext_b_ptr);
                 p_ptr->assign_vertex_ptr(head_v_ptr);

                 sub_v_ptr->pos_appearances.add_ptr(p_ptr);

           } // ELSE

          // ADVANCE TO THE NEXT FULLSTRING VERSIONED ATOM IN FULLSTRING LIST
          f_ptr = f_ptr->get_next_ptr();

     } // WHILE THERE ARE MORE SUBGOAL ATOMS (f_ptr != nullptr)

    //***************************************************************//
    // ADD THE RULE TO THE PROGRAM'S RULE LIST
    //***************************************************************//
    add_rule(head, head_v_ptr, ext_b_ptr);


   Num_Variables = Vertexlist.get_length();
   flist->cleanup();


} // LOGIC_PROGRAM ADD_EXTENSIONAL_RULE




///////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void logic_program_class::nonmonotonically_update(istream& infile)   
{
   add_fact_to_stream(infile);
   update_state();
   show_state(cout);

} // NONMONOTONICALLY_UPDATE


///////////////////////////////////////////////////////////////////////////
///  ADD_FACT updates a logic program by creating a vertex with
///  the String version containing one extensional fact as its ATOM.
///  
///   If FACT is already in graph
///             +   if same polarity
///                     do nothing
///                 else 
///                     flip polarity  ... (negative_fact = 1 or 0)
///   else IF ATOM in GRAPH AS A RULE HEAD
///             + create a body
///             + assign negative_fact field 1 if FACT is negative,
///                       0, otherwise
///   else
///             + create a vertex
///             + create a body
///
///  CAUTION:  +GLOBAL VARIABLE Num_Variables MAY BE CHANGED  
///                    
///           
///////////////////////////////////////////////////////////////////////////
vertex_class *logic_program_class::add_fact(char tempstr[LONG_STRING_LENGTH],
                                    int is_negative_val)  
{

vertex_class           *head_v_ptr, *sub_v_ptr;
body_node_class        *cur_b_ptr;
rule_class             *r_ptr;
int                    head;
int                    cur_sub_val;
char                  full_string[ EXTRA_LONG];
int                   fact_found;


      
       // DETERMINE WHETHER OR NOT IT ALREADY EXISTS
        head_v_ptr = find_fullstring_in_graph(tempstr);

        if (head_v_ptr == nullptr)   {        // CREATE NEW VERTEX
              head = Vertexlist.get_length() + 1;
              head_v_ptr = new vertex_class(tempstr, head, is_negative_val);      
              Vertexlist.add_ptr(head_v_ptr); 
        } //IF
        else {                             // VERTEX ALREADY EXISTS
              head = head_v_ptr->get_value();
        } // ELSE
   
       //********************************************************************//
       // head_v_ptr NOW POINTS TO THE VERTEX OF THE FACT ATOM in GRAPH;     //
       //********************************************************************//

        // Check for a FACT presence in the BODY list and determine polarity
        // ---------------------------------------------------------- 

        cur_b_ptr = head_v_ptr->get_first_body();
        fact_found = 0;
        while ((cur_b_ptr != nullptr) && (!fact_found)) {
             if (cur_b_ptr->is_bodiless_rule())
                       fact_found = 1;
             else
                       cur_b_ptr = cur_b_ptr->get_next_ptr();
        } // WHILE
        
       if (cur_b_ptr == nullptr) {  // FACT DOESN'T EXIST..CREATE ONE
           cur_b_ptr = new body_node_class();
           head_v_ptr->add_body(cur_b_ptr);
       } // IF cur_b_ptr is nullptr

        //**************************************************
        // cur_b_ptr now points to the new FACT
        // ... alter polarity if necessary
        //**************************************************
        cur_b_ptr->assign_negative_fact(is_negative_val  );
                 

    //***************************************************************//
    // ADD THE RULE TO THE PROGRAM'S RULE LIST
    //***************************************************************//
    add_rule(head, head_v_ptr, cur_b_ptr);


   Num_Variables = Vertexlist.get_length();

   return head_v_ptr;
   

} // ADD_FACT (version 2)



///////////////////////////////////////////////////////////////////////////
///  ADD_FACT updates a logic program by reading an input stream input
///  containing one extensional fact.
///  
///   If FACT is already in graph
///             +   if same polarity
///                     do nothing
///                 else 
///                     flip polarity  ... (negative_fact = 1 or 0)
///   else IF ATOM in GRAPH AS A RULE HEAD
///             + create a body
///             + assign negative_fact field 1 if FACT is negative,
///                       0, otherwise
///   else
///             + create a vertex
///             + create a body
///
///  CAUTION:  +GLOBAL VARIABLE Num_Variables MAY BE CHANGED  
///            +calls reinitialize_graph
///                   update_state()
///                   show_state()
///                    
///           
///////////////////////////////////////////////////////////////////////////
void logic_program_class::add_fact_to_stream(istream& infile)
{

vertex_class           *head_v_ptr, *sub_v_ptr;
body_node_class        *cur_b_ptr;
rule_class             *r_ptr;
fullstring_class       *f_ptr;
int                    head;
int                    cur_sub_val;

list_class<fullstring_class>  *flist; 

char                  full_string[ EXTRA_LONG];
char                  gochar = '.';          
char                  tempstr[LONG_STRING_LENGTH];
int                   fact_found;


   // READ IN THE FACT
   cout << endl << endl <<"Enter new fact.\n ";
   gochar = *read_rule(infile, full_string);
   cout << endl;

   if (gochar == '.') {

       // CREATE A LIST OF FULLSTRING VERSIONS OF EXTENSIONAL RULE'S ATOMS
        flist = new list_class<fullstring_class>();
        extract_atom_strings(full_string, flist);

       // EXAMINE THE ATOM...THE HEAD OF THE EXTENSIONAL RULE
        f_ptr = flist->get_first();
        strcpy(tempstr,f_ptr->get_fullstring_symbol());        
      
       // DETERMINE WHETHER OR NOT IT ALREADY EXISTS
        head_v_ptr = find_fullstring_in_graph(tempstr);

        if (head_v_ptr == nullptr)   {        // CREATE NEW VERTEX
              head = Vertexlist.get_length() + 1;
              head_v_ptr = new vertex_class(tempstr, head, f_ptr->get_IS_NEGATIVE());      
              Vertexlist.add_ptr(head_v_ptr); 
        } //IF
        else {                             // VERTEX ALREADY EXISTS
              head = head_v_ptr->get_value();
        } // ELSE
   
       //********************************************************************//
       // head_v_ptr NOW POINTS TO THE VERTEX OF THE FACT ATOM in GRAPH;     //
       //********************************************************************//

        // Check for a FACT presence in the BODY list and determine polarity
        // ---------------------------------------------------------- 

        cur_b_ptr = head_v_ptr->get_first_body();
        fact_found = 0;
        while ((cur_b_ptr != nullptr) && (!fact_found)) {
             if (cur_b_ptr->is_bodiless_rule())
                       fact_found = 1;
             else
                       cur_b_ptr = cur_b_ptr->get_next_ptr();
        } // WHILE
        
       if (cur_b_ptr == nullptr) {  // FACT DOESN'T EXIST..CREATE ONE
           cur_b_ptr = new body_node_class();
           head_v_ptr->add_body(cur_b_ptr);
       } // IF cur_b_ptr is nullptr

        //**************************************************
        // cur_b_ptr now points to the new FACT
        // ... alter polarity if necessary
        //**************************************************
        cur_b_ptr->assign_negative_fact( ( f_ptr->get_IS_NEGATIVE())  );
                 
     } // IF gochar == '.'

    //***************************************************************//
    // ADD THE RULE TO THE PROGRAM'S RULE LIST
    //***************************************************************//
    add_rule(head, head_v_ptr, cur_b_ptr);


   Num_Variables = Vertexlist.get_length();
   flist->cleanup();
   

} // ADD_FACT



////////////////////////////////////////////////////////////////////////
///  Initializes the program graph and recomputes the WF model
////////////////////////////////////////////////////////////////////////
void logic_program_class::update_state()
{
     initialize_graph();
//     get_WF_4_value_optimize();      
      find_first_stable_model();   
}


/////////////////////////////////////////////////////////////////////////
///   Display the logic program in extensional rule format.
///
/////////////////////////////////////////////////////////////////////////
void logic_program_class::display_ground_instantiation(ostream& fout)
{

   body_node_class    *b_ptr;
   vertex_class       *v_ptr;
   char                tempstr1[LONG_STRING_LENGTH]; 
   char                tempstr2[LONG_STRING_LENGTH]; 


   v_ptr = Vertexlist.get_first();
   fout << "\n \n \n";
   fout << "GROUND INSTANTIATION \n \n ";

   while (v_ptr != nullptr) {

      b_ptr = v_ptr->get_first_body();
      while (b_ptr != nullptr) {
            display_extensional_rule(v_ptr, b_ptr, fout);
            b_ptr = b_ptr->get_next_ptr();
       } // WHILE
       v_ptr = v_ptr->get_next_ptr();
       fout << "\n";
    }// WHILE     
    
     fout << "@@@@@@@@@@@@@@@ \n";

}// DISPLAY_GROUND_INSTANTIATION


//----------------------------------------------------------------
                         
void logic_program_class::display_extensional_rule
                   ( vertex_class    *head_v_ptr,
                     body_node_class *body_b_ptr,
                     ostream& fout                     )
{

   body_node_class    *b_ptr;
   vertex_class       *sub_v_ptr;
   literal_class      *p_ptr, *n_ptr;
   char                tempstr1[LONG_STRING_LENGTH];
   char                tempstr2[LONG_STRING_LENGTH];


   // DISPLAY LEADING NEGATION FOR NEGATIVE FACT 
   if (body_b_ptr->get_negative_fact() == 1 )
       fout << '~';

   // DISPLAY HEAD ATOM
   fout << (head_v_ptr->get_atominfo()) << " <-- ";

   // INITIALIZE LIST POINTERS TO POS AND NEG SUBGOALS
   p_ptr = body_b_ptr->get_first_pos_lit_ptr();
   n_ptr = body_b_ptr->get_first_neg_lit_ptr();


   // DISPLAY THE BODY ATOMS OF POSITIVE SUBGOALS

   while (p_ptr != nullptr) {
         sub_v_ptr = p_ptr->get_vertex_ptr();  
//fout << endl << endl ;
//fout << "sub_v_ptr points to VERTEX...";        
//sub_v_ptr->output();
//fout << "sub_v_ptr points to ATOM...";        

         fout << (sub_v_ptr->get_atominfo());

         // ADVANCE TO NEXT POSITIVE SUBGOAL
         p_ptr = p_ptr->get_next_ptr();
         if ((p_ptr != nullptr) || (n_ptr != nullptr)) {
                   fout << ", \n";
                   fout << "                                ";
          } // IF                   
//         else {
//                   fout << ".";
//          } // ELSE
 
   } // WHILE more positive subgoals      


   while (n_ptr != nullptr) {
         sub_v_ptr = n_ptr->get_vertex_ptr();  
         fout << "~" << (sub_v_ptr->get_atominfo());

         // ADVANCE TO NEXT NEGATIVE SUBGOAL
         n_ptr = n_ptr->get_next_ptr();
         if (n_ptr != nullptr) {
                   fout << ",  \n";
                   fout << "                       ";
          } // IF                   
//         else {
//                   fout << ".";
//         } //ELSE
 
   } // WHILE more negative subgoals      
   fout << " . ";
   fout << endl;

} // DISPLAY_EXTENSIONAL_RULE

