#include <iostream>

#include "LOGIC_PR.H"
#include "UTILITY1.H"
#include "UTILITY2.H"

using namespace std;

logic_program_class::logic_program_class()
{
   rulelist.initialize();
   Vertexlist.initialize();
   Spantreelist.initialize();
}
    



//////////////////////////////////////////////////////////////////////////////////
///
///     A logic program is created by this constructor.  The constructor
///     simultaneously creates rules and updates the program dependency graph.
///
///
///     The algorithm is as follows:
///
///           For each rule created (of which there are global Num_Rules):
///                1.  create head (random num)
///
///                2.  create body (via call to body_node_class constructor)
///
///                3.  update the graph with the head and _its causes_   
///                    (add exactly one incoming hyperedge to the head)
///                       a)  find or add the vertex node corresponding to head
///                       b)  add the body to this vertex node             
///
///                4.  add the rule to the program rule list (via *rulelist)
///                       a) create a rule node containing pointers to the
///                          newly created (or found) vertex node and body node 
///                       b) add this rule node to the rule list
///
///                5.  update the graph by augmenting each subgoal's
///                    dependent lists ("appearances") with a rule node
///                    containing pointers to this current rule's head and body
///                    That is, add exactly one outgoing piece of
///                    a hyperedge from each subgoal vertex TO
///                    the current head vertex.
///
///                         For each literal in the body:
///                               a) find or add the vertex corresponding
///                                  to the literal (...get its pointer)
///                               b) add the current rule node to its
///                                  appearances list
///
///////////////////////////////////////////////////////////////////////////////
logic_program_class::logic_program_class(int distribution)
{

vertex_class           *v_ptr;
body_node_class        *b_ptr;
rule_class             *r_ptr;
int                    head;
int                    temp;
int                    num_bodiless_created;
int                    i;
  

  // ASSIGN LISTS OF P

   rulelist.initialize();
   Vertexlist.initialize();
   Spantreelist.initialize();


  //  CREATE THE RULES 
  num_bodiless_created = 0;

  for (i = 0; i < Num_Rules; i++) {

      // CREATE HEAD
      head = get_random_val(Num_Variables);
  if ((Distribution < 5) || ( !(already_included(head)))) {

      // CREATE BODY
      if (num_bodiless_created < Num_Bodiless_Rules) {
            b_ptr = new body_node_class();
//            b_ptr->set_body_status(1);  // 1 means TRUE
            num_bodiless_created++;
      }
      else {
            b_ptr = new body_node_class(distribution, head);
      }

      // UPDATE GRAPH BY ADDING ONE INCOMING HYPEREDGE TO HEAD VERTEX
      v_ptr = find_add_vertex(head);

      // ADD BODY TO THE VERTEX
       v_ptr->add_body(b_ptr);
  
      // ADD THE RULE TO THE PROGRAM'S RULE LIST
      add_rule(head, v_ptr, b_ptr);

      // AUGMENT GRAPH BY ADDING ONE PIECE OF A HYPEREDGE FROM EACH
      //    SUBGOAL _TO_ THE HEAD...That is:  add subgoals' outgoing edge pieces

      add_subgoals_outgoing_edge_pieces(head, v_ptr, b_ptr);

   }// IF HEAD NOT ALREADY TAKEN

 } // FOR .. CREATE THE RULES


   // PREASSIGN VARIABLES TO FALSE AS MANDATED IN GLOBAL VARIABLE
   //   "Preassign_False_Percent"  AND "Num_Preassign_False"

   preassign_false_variables();
// update_graph();


} // LOGIC_PROGRAM_CLASS CONSTRUCTOR
    

///////////////////////////////////////////////////////////////////////////
///  Construct a logic program by reading an input file.
///////////////////////////////////////////////////////////////////////////
logic_program_class::logic_program_class(char *filename)
{

vertex_class           *v_ptr;
body_node_class        *b_ptr;
rule_class             *r_ptr;
int                    head;
int                    temp;
char                   line[80];
char                   *p, *ind;
char                   intarray[10];
char                   i, done;
int                    subgoal_val;
int                    neg_rule;


while (InputFile.getline(line,80)) 
  {
       p = line;

       // PARSE OUT THE VALUES IN line 
       ind = intarray;

       // IGNORE LEADING BLANK LINESS
       while (*p == ' ' || *p == '\n' || *p == '\t' || *p == '#')
               p++; 


       // READ IN THE HEAD
       while (*p != EOF  && *p != '\n' && *p != ' ' && *p != '#') 
        {     
               *ind = *p; 
               ind++;
               p++;
        } // WHILE

        *ind  = '\0';

        //*******************//
        // CREATE HEAD       //
        //*******************//

        head  = stoi(intarray);

       while (*p == ' ' || *p == '<' || *p == '-' )
              p++;

       if (*p == '#') 
          { done = 1;}
       else 
          { done = 0;}

       //********************************//
       //  CREATE BODY                   //
       //********************************//
         b_ptr = new body_node_class();

       // READ IN ALL SUBGOALS OF THE BODY 
       ind = intarray;
       while (done != 1) 
         {
             ind = intarray; 
             neg_rule = FALSE;

             // SKIP OVER THE "IF" SIGN AND BLANKS            
             while (*p == ' ' || *p == '<' || *p == '-' || *p == ',' )
                       p++; 
           
             // EXTRACT NEXT SUBGOAL INTEGER FROM STRING LINE

             while (*p != EOF  && *p != '\n' && *p  != ' ' && 
                    *p != ',' && *p != '#') 
                  {           
                        *ind = *p;
                         ind++;
                         p++;
                  } // WHILE

             // APPEND nullptr CHAR TO EXTRACTED BODY STRING
             *ind = '\0';
       
             if (*intarray == '~') 
                   neg_rule = TRUE;

             if (*intarray != '\0') 
                subgoal_val = bodystoi(intarray);

             //******************************************//
             //  APPEND THIS SUBGOAL TO NEWLY FORMED BODY//
             //******************************************//

             if (neg_rule == 1 )  // TRUE
                { (b_ptr->add_neg_literal(subgoal_val)); }
             else
                { (b_ptr->add_pos_literal(subgoal_val)); }

                 
             while (*p == ' ')
                    p++; 

             if (*p == EOF || *p == '\n' || *p == '#')
                  done = TRUE;  

        } // WHILE not done

        //***************************************************************//
        // UPDATE GRAPH BY ADDING ONE INCOMING HYPEREDGE TO HEAD VERTEX  //
        //***************************************************************//
         v_ptr = find_add_vertex(head);

        //***************************************************************//
        // ATTACH BODY TO VERTEX
        //***************************************************************//
         b_ptr->update_body_status();
         v_ptr->add_body(b_ptr);

        //***************************************************************//
        // ADD THE RULE TO THE PROGRAM'S RULE LIST
        //***************************************************************//
         add_rule(head, v_ptr, b_ptr);

        //***************************************************************//
        // AUGMENT GRAPH BY ADDING ONE PIECE OF A HYPEREDGE FROM EACH
        //    SUBGOAL _TO_ THE HEAD...
        //***************************************************************//

        add_subgoals_outgoing_edge_pieces(head, v_ptr, b_ptr);

      } // WHILE not EOF
      
      Num_Variables = Vertexlist.get_length();

   // PREASSIGN VARIABLES TO FALSE AS MANDATED IN GLOBAL VARIABLE
   //   "Preassign_False_Percent"  AND "Num_Preassign_False"
     preassign_false_variables();

     InputFile.close();

} // LOGIC_PROGRAM CONSTRUCTOR...INPUT FILE


#include "lpcons.cc"


////////////////////////////////////////////////////////////////////////////
///    DESTRUCTOR
////////////////////////////////////////////////////////////////////////////

logic_program_class::~logic_program_class()
{
   rulelist.cleanup();
   Vertexlist.cleanup();
   Spantreelist.cleanup();
}

////////////////////////////////////////////////////////////////////////////
void logic_program_class::clear()


{
   rulelist.cleanup();
   Vertexlist.cleanup();
   Spantreelist.cleanup();
}




/////////////////////////////////////////////////////////////////////////////
///  Outputs  the rules and graph in a verbose way.   Used for debugging.
/////////////////////////////////////////////////////////////////////////////    

void logic_program_class::output()
  {
    cout << " Outputting LOGIC PROGRAM: \n";
    cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
    cout << "The rules are:     \n";
    cout << "--------------    \n \n";
    rulelist.print();
    cout << "\n \n ************************************** \n \n";
    cout << "The graph is:   \n";
    cout << "--------------    \n \n";
    Vertexlist.print();
    cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
    Spantreelist.print(); 

  }
  
/////////////////////////////////////////////////////////////////////////////
///  Outputs  the graph in a verbose way.   Used for debugging.
/////////////////////////////////////////////////////////////////////////////    

void logic_program_class::output_graph()
  {
    cout << " Outputting LOGIC PROGRAM GRAPH: \n";
    cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
    cout << "The graph is:   \n";
    cout << "--------------    \n \n";
    Vertexlist.print();
    cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
  }
  
/////////////////////////////////////////////////////////////////////////////
///  Outputs  the spanning tree list
/////////////////////////////////////////////////////////////////////////////    

void logic_program_class::print_spanning_trees()
  {
    cout << " Outputting SPANNING TREES..\n";
    cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
    cout << "The span tree list is:   \n";
    cout << "--------------    \n \n";
    Spantreelist.print();
    cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
  }
  

//////////////////////////////////////////////////////////////////////
///  Routines to augment the program's graph and list of rules.
/////////////////////////////////////////////////////////////////////    



void logic_program_class::add_vertex(vertex_class *v_ptr)
{
      Vertexlist.add_ptr(v_ptr);
}

void logic_program_class::add_spantree(spantree_class *s_ptr)
{
      Spantreelist.add_ptr(s_ptr);
}


void logic_program_class::add_rule( int head_val,
                               vertex_class *v_ptr, body_node_class *b_ptr)
{
     rule_class *r_ptr;
     
     r_ptr = new rule_class(head_val, v_ptr, b_ptr);
     rulelist.add_ptr(r_ptr);
}

void logic_program_class::add_rule(rule_class *r_ptr)
{
      rulelist.add_ptr(r_ptr);
}


///////////////////////////////////////////////////////////////////////////////////
///  Checks program graph to determine whether or not a vertex has yet been added.
///////////////////////////////////////////////////////////////////////////////////    

int logic_program_class::already_included(int head_val)
{
     rule_class *r_ptr;

     r_ptr = nullptr;
     r_ptr = rulelist.find_val_ptr(head_val);

     if (r_ptr == nullptr)
          return 0;
     else
          return 1;

}



///////////////////////////////////////////////////////////////////////////////
//  Searches for a vertex with val k.  If it is not found,   this routine
//  creates and adds it to the vertex list.
///////////////////////////////////////////////////////////////////////////////


vertex_class *logic_program_class::find_add_vertex(int k)
{
    return (Vertexlist.find_add_val_ptr(k));
}


///////////////////////////////////////////////////////////////////////
///  Find_vertex traverses the program graph and returns a pointer
///  to the vertex with val, find_val.
//////////////////////////////////////////////////////////////////////

vertex_class *logic_program_class::find_vertex(int find_val)
{

         return (Vertexlist.find_val_ptr(find_val));
};


//////////////////////////////////////////////////////////////////////////
///  ADD_SUBGOALS_OUTGOING_EDGE_PIECES:
///
///      For each literal in the body:
///            a) find or add the vertex corresponding
///               to the literal (...get its pointer)
///            b) add the current rule node to its
///               appearances list
///
/////////////////////////////////////////////////////////////////////////

void logic_program_class::add_subgoals_outgoing_edge_pieces (int head_val,
                           vertex_class *head_ptr, body_node_class *body_ptr)
{
    vertex_class        *search_vertex; 
    literal_class       *cur_lit_ptr; 
    int                  search_head;



     //  TRAVERSE LISTS OF POSITIVE LITERALS
     cur_lit_ptr = body_ptr->get_first_pos_lit_ptr();

     while (cur_lit_ptr != nullptr) {
          // EXTRACT VALUE OF THE CURRENT LITERAL
          search_head = cur_lit_ptr->get_value();
          
          // FIND THAT VERTEX IN PROGRAM GRAPH
          search_vertex = find_add_vertex(search_head);
         
          // ADD A POSITIVE APPEARANCE TO THIS NEWLY FOUND VERTEX
          search_vertex->add_pos_appearance(head_val, head_ptr, body_ptr);

          // ADVANCE TO THE NEXT POSITIVE LITERAL IN BODY
          cur_lit_ptr = (cur_lit_ptr->get_next_ptr()); 

     } // WHILE
     
     //  TRAVERSE LISTS OF NEGATIVE LITERALS
     cur_lit_ptr = body_ptr->get_first_neg_lit_ptr();

     while (cur_lit_ptr != nullptr) {
          // EXTRACT VALUE OF THE CURRENT LITERAL
          search_head = cur_lit_ptr->get_value();
          
          // FIND THAT VERTEX IN PROGRAM GRAPH
          search_vertex = find_add_vertex(search_head);
         
          // ADD A NEGATIVE APPEARANCE TO THIS NEWLY FOUND VERTEX
          search_vertex->add_neg_appearance(head_val, head_ptr, body_ptr);

          // ADVANCE TO THE NEXT POSITIVE LITERAL IN BODY
          cur_lit_ptr = (cur_lit_ptr->get_next_ptr()); 

     } // WHILE
} // ADD_SUBGOALS_OUTGOING_EDGES


//////////////////////////////////////////////////////////////////////////////
///   Display a logic program in the standard format:  head <-- body.
///   Rules are displayed in the order in which they were generated.
//////////////////////////////////////////////////////////////////////////////
void logic_program_class::display()
{
   rule_class *r_ptr;

   r_ptr = rulelist.get_first();
   cout << "\n \n \n";
   cout << "LOGIC PROGRAM DISPLAYED BY ORDER OF RULE GENERATION: \n";
   cout << "\n";

   while (r_ptr != nullptr) {
       display_rule(r_ptr);
       r_ptr = r_ptr->get_next_ptr();
   }
 
   cout << "\n \n \n";
}


//////////////////////////////////////////////////////////////////////////////
///   Rules are displayed in clusters with common heads.
//////////////////////////////////////////////////////////////////////////////


void logic_program_class::display_head_groups()
{
   body_node_class *b_ptr;
   vertex_class    *v_ptr;

   v_ptr = Vertexlist.get_first();
   cout << "\n \n \n";
   cout << "LOGIC PROGRAM DISPLAYED BY COMMON HEAD GROUPINGS: \n";
   cout << "\n";

   while (v_ptr != nullptr) {
       b_ptr = v_ptr->get_first_body();
       while (b_ptr != nullptr) {
           display_rule(v_ptr, b_ptr);
           b_ptr = b_ptr->get_next_ptr();
       } // WHILE
       v_ptr = v_ptr->get_next_ptr();
       cout << "\n";
    }// WHILE

   cout << "\n \n \n";
}// DISPLAY_HEAD_GROUPS



////////////////////////////////////////////////////////////////////////////
//  Displays a rule pointed indicated by v_ptr and b_ptr.
//  Displays in the standard LP format:   head <-- body
////////////////////////////////////////////////////////////////////////////
void logic_program_class::display_rule(vertex_class *v_ptr,
                                       body_node_class *b_ptr)
{
   int              head_val;

   head_val = v_ptr->get_value();

   cout << "            " ;
   // DISPLAY LEADING NEGATION FOR NEGATIVE FACTS
   if (b_ptr->get_negative_fact() == 1)
       cout << '~';

   // DISPLAY THE RULE
   cout << head_val << " <-- ";

   // b_ptr IS NOW POINTING TO THE CORRECT BODY
   b_ptr->display_body();
                            
}  // DISPLAY_RULE




////////////////////////////////////////////////////////////////////////////
//  Displays a rule in the standard format :  head <-- body
//
////////////////////////////////////////////////////////////////////////////
void logic_program_class::display_rule(rule_class *r_ptr)
{
   vertex_class     *v_ptr;
   body_node_class  *b_ptr;
   node_class       *rule_bod;
   int              head_val;

   head_val = r_ptr->get_value();
   rule_bod = r_ptr->get_body_ptr();
   v_ptr = Vertexlist.find_val_ptr(head_val);

   // FIND THE RULE BODY 
   b_ptr = v_ptr->get_first_body();
   
   while ((rule_bod != b_ptr) && (rule_bod != nullptr))
       b_ptr = b_ptr->get_next_ptr();


   // DISPLAY THE RULE
   cout << "            " << head_val << " <-- ";

   // b_ptr IS NOW POINTING TO THE CORRECT BODY	
   b_ptr->display_body();

}  // DISPLAY_RULE

//////////////////////////////////////////////////////////////////////
///  Private routines to read in integers from Input file.
/////////////////////////////////////////////////////////////////////
int logic_program_class::stoi (char *iarray)
{
  int num;
  char *c;

  num = 0; c = iarray;
  
  while (*c != '\0') {
     num = (num * 10) + (*c - '0');
     c++;
  }
  return num;
} // STOI

int logic_program_class::bodystoi (char *iarray)
{
  int num;
  char *c;

  num = 0; c = iarray;
  if (*c == '~') {c++;}
  
  while (*c != '\0') {
     num = (num * 10) + (*c  - '0');
     c++;
  } // WHILE
  return num;
} // BODYSTOI


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
//        M O D E L   G E N E R A T I O N   R O U T I N E S
//
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *



///////////////////////////////////////////////////////////////////////
///  Performs exactly one traversal of the graph (Vertexlist) and
///  checks for vertices that satisfy the conditions for being TRUE.
///  The field:  truth_val is then set to TRUE (1).  
///
///     A vertex is true IF:
///          it has at least one body with the status ALL_TRUE
///          (recall:  ALL_TRUE is #defined as 2 in const.h)
///
//////////////////////////////////////////////////////////////////////

int logic_program_class::determine_truths()
{  
     vertex_class       *v_ptr;
     body_node_class    *b_ptr;
     int                 current_body_stat;
     int                 next_truth_val;
     int                 next_guess;
     int                 changed;
     int                 topped;


   v_ptr = Vertexlist.get_first();
   if (v_ptr != nullptr) {
       next_truth_val = v_ptr->get_truth();
       next_guess = v_ptr->get_guess();
   } // IF
     
   changed = 0;                    // 0 means FALSE

   while (v_ptr != nullptr) {
       switch (next_truth_val) {
          case 0  :  {   // FALSE 

                     // SEARCH FOR A BODY WHICH IS ALL_TRUE
                      b_ptr = v_ptr->get_first_body();
//                    topped = 0;

                      while (b_ptr != nullptr) {
                          current_body_stat = b_ptr->get_body_status();
                          if (current_body_stat == 2)  {   // 2 means ALL_TRUE 
                            v_ptr->assign_truth(3);    // 3 means TOP
                            changed = 1; 
                            b_ptr = nullptr;
                            break;
                          } // IF
//                          else if (current_body_stat == 3)  {  // 3 means TOPPED
//                             topped = 1;
//                        } // ELSE

                          b_ptr = b_ptr->get_next_ptr();
                      } // WHILE
                        

//                      // NO ALL_TRUES WERE FOUND..BUT SOME "TOPPED" BODIES WERE
//                      if ((changed == 0) && (topped == 1)) {
//                            v_ptr->assign_truth(3);
//                      }  // IF

                     break;

                   }  // CASE FALSE 


          case 1 : {   // TRUE ...skip
                        break;
                   }

          case 2 :  {   // BOTTOM .... process

                     // SEARCH FOR A BODY WHICH IS ALL_TRUE
                      b_ptr = v_ptr->get_first_body();
//                      topped = 0;

                      while (b_ptr != nullptr) {
                        current_body_stat = b_ptr->get_body_status();
                        if (current_body_stat == 2)  {   // 2 means ALL_TRUE 
                            v_ptr->assign_truth(1);    // 1 means TRUE
                            changed = 1; 
                            b_ptr = nullptr;
                            break;
                        } // IF
//                        else if (current_body_stat == 3)  {  // 3 means TOPPED
//                            topped = 1;
//                        } // ELSE

                        b_ptr = b_ptr->get_next_ptr();
                      } // WHILE
                        

                      // NO ALL_TRUES WERE FOUND..BUT SOME "TOPPED" BODIES WERE
//                      if ((changed == 0) && (topped == 1)) {
//                            v_ptr->assign_truth(3);
//                      }  // IF

                     break;

                   }  // CASE FALSE OR BOTTOM

       
          case 3 :  {   // TOP .... skip
                        break;
                    }

        } // SWITCH

        // ADVANCE TO NEXT VERT%EX IN GRAPH
        v_ptr = v_ptr->get_next_ptr();
        if (v_ptr != nullptr) {
            next_truth_val = v_ptr->get_truth();
            next_guess = v_ptr->get_guess();
        } // IF
     }// WHILE
     return changed;
} // DETERMINE_TRUTHS


// -----------------------------------------
//
//    S A V E   O L D    V E R S I O N
//
//int logic_program_class::determine_truths()
//{  
//     vertex_class       *v_ptr;
//     body_node_class    *b_ptr;
//     int                 current_body_stat;
//     int                 next_truth_val;
//     int                 next_guess;
//     int                 changed;
//
//
//   v_ptr = Vertexlist.get_first();
//   if (v_ptr != nullptr) {
///       next_truth_val = v_ptr->get_truth();
//      next_guess = v_ptr->get_guess();
//   } // IF
//     
//   changed = 0;                    // 0 means FALSE
//
//   while (v_ptr != nullptr) {
//    if (next_guess != 1) {  // IF THE NODE WAS NOT PREASSIGNED
//         // DON'T UPDATE AN ALREADY TRUE OR FALSE NODE
//         if ((next_truth_val != 1) && (next_truth_val != 0))  {
//
//             b_ptr = v_ptr->get_first_body();
//
//             while (b_ptr != nullptr) {
//                current_body_stat = b_ptr->get_body_status();
//                if (current_body_stat == 2)  {   // 2 means ALL_TRUE 
//                      v_ptr->assign_truth(1);    // 1 means TRUE
//                      changed = 1; 
//                      b_ptr = nullptr;
//                      break;
//                } // IF
//                b_ptr = b_ptr->get_next_ptr();
//            } // WHILE
//
//        } // IF  
//      } // IF GUESS != 1
//      else { //  THE NODE _WAS_ PREASSIGNED... GUESS IS TRUE ... 1
//
//          if (next_truth_val !=  1) { // IF NODE NOT ALREADY TRUE
//            
//              // DETERMINE WHETHER _ANY_ OF ITS BODIES ARE ALL_TRUE
//               b_ptr = v_ptr->get_first_body();
//
//               while (b_ptr != nullptr) {
//                   current_body_stat = b_ptr->get_body_status();
//                   if (current_body_stat == 2)  {   // 2 means ALL_TRUE
//                         v_ptr->assign_truth(3);    // 3 means TOP
//                         changed = 1;
//                         b_ptr = nullptr;
//                         break;
//                    } // IF
//                    b_ptr = b_ptr->get_next_ptr();
//                } // WHILE
//            } //IF  ... NOT ALREADY TRUE
//
//      } // ELSE .. PREASSIGNED
//        v_ptr = v_ptr->get_next_ptr();
//        if (v_ptr != nullptr) {
//            next_truth_val = v_ptr->get_truth();
//            next_guess = v_ptr->get_guess();
//        } // IF
////     }// WHILE
//     return changed;
// }   //END OLD VERSION 
//
//
//
//
////-------------------------------------------


///////////////////////////////////////////////////////////////////////
///  Performs exactly one traversal of the graph (Vertexlist) and
///  checks for vertices that satisfy the conditions for being FALSE.
///  The field:  truth_val is then set to FALSE (0).
///
///     A vertex is FALSE IF:
///          All of its bodies have status ELIMINATED
///          (recall:  ELIMINATED is #defined as 1 in const.h)
///       OR
///          its bodylist is nullptr
///
///     Only vertices that are not currently TRUE or FALSE are checked.
//////////////////////////////////////////////////////////////////////

int logic_program_class::determine_falsities_KK()
{  
     vertex_class       *v_ptr;
     body_node_class    *b_ptr;
     int                 current_body_stat;
     int                 next_truth_val;
     int                 next_guess;
     int                 changed;
     int                 all_eliminated;


     v_ptr = Vertexlist.get_first();
     if (v_ptr != nullptr) {
         next_truth_val = v_ptr->get_truth();
     } // IF

     changed = 0;       // 0 is FALSE
     while (v_ptr != nullptr) {

          // CONSIDER BOTTOM OR TRUE VERTICES...IGNORE FALSE AND TOP VERTICES
          if ((next_truth_val == 2) || (next_truth_val == 1)) {

               b_ptr = v_ptr->get_first_body();
               all_eliminated = 1;

               while (b_ptr != nullptr) {
                   current_body_stat = b_ptr->get_body_status();
                   if (current_body_stat != 1)  {   // 1 means ELIMINATED
                       b_ptr = nullptr;
                       all_eliminated = 0;
                       break;
                    } // IF
                    b_ptr = b_ptr->get_next_ptr();

                } // WHILE


                if (all_eliminated == 1) {
                    if (next_truth_val == 2) 
                           v_ptr->assign_truth(0);    // assign node FALSE
                    
                    else if (next_truth_val == 1)
                           v_ptr->assign_truth(3);    // assign node TOP

                   changed = 1;                 
                } // IF  ALL ELIMINATED

         } // IF NODE WAS A BOTTOM OR TRUE NODE 


        // PROCEED TO THE NEXT VERTEX IN THE GRAPH
        v_ptr = v_ptr->get_next_ptr();
        if (v_ptr != nullptr) {
             next_truth_val = v_ptr->get_truth();
        } // IF
     }// WHILE NOT END OF GRAPH

     return changed;
} // DETERMINE_FALSITIES



///////////////////////////////////////////////////////////////////////////////
///  Propogate truthfulness simplifies the program by replacing
///  literals with their truth values. 
///
///  The rules in which these replaced literals appear are modified as follows.
///        The body containing a TRUE literal is shortend by removing this
///        true subgoal.
///        ( body.num_literals_satisfied++ )
///
///        The body containg a FALSE literal is eliminated.
///        ( body.status = ELIMINATED)
///
///////////////////////////////////////////////////////////////////////////////

void logic_program_class::propogate_truthfulness_KK(vertex_class *v_ptr)
{
    vertex_class           *appearance_v_ptr;
    body_node_class        *appearance_b_ptr;
    rule_class             *r_ptr;
    node_class             *rule_bod;
    int                     appearance_head;
    int                     vertex_truth_val;

 
 vertex_truth_val = v_ptr->get_truth();

 // CASE VERTEX IS  T R U E  OR T O P .... 1 OR 3 RESPECTIVELY
 if ((vertex_truth_val == 1) || (vertex_truth_val == 3)) {  //

   // ************************************************* //
   //  Vertex TRUE or TOP  ... Appears POSITIVELY               //
   // ************************************************* //

    // EXCISE ALL POSITIVE APPEARANCES THROUGHOUT THE GRAPH

    r_ptr = v_ptr->get_first_pos_appearance();
    while (r_ptr != nullptr) {
         appearance_head = r_ptr->get_value();
         appearance_v_ptr = Vertexlist.find_val_ptr(appearance_head);
         rule_bod = r_ptr->get_body_ptr();

        //------------------------------------------------------------
        // FIND THE RULE BODY IN WHICH IT APPEARS
        // This is necessary to impose base class node_class onto
        //  derived class body_node_class
        // -----------------------------------------------------------

         appearance_b_ptr = appearance_v_ptr->get_first_body();
         while ((rule_bod != appearance_b_ptr) && (appearance_b_ptr != nullptr))
               appearance_b_ptr = appearance_b_ptr->get_next_ptr();

         // appearance_b_ptr IS NOW POINTING TO THE CORRECT BODY	
         appearance_b_ptr->increase_num_literals_sat(1);
         appearance_b_ptr->update_body_status();
         
         r_ptr = r_ptr->get_next_ptr();

     } // WHILE  vertex true, appears positively


        

   // ************************************************* //
   //  Vertex TRUE OR TOP ... Appears Negatively               //
   // ************************************************* //

    // ELIMINATE ALL RULES WITH NEGATIVE APPEARANCES... THEY ARE FALSE

    r_ptr = v_ptr->get_first_neg_appearance();
    while (r_ptr != nullptr) {
         appearance_head = r_ptr->get_value();
         appearance_v_ptr = Vertexlist.find_val_ptr(appearance_head);
         rule_bod = r_ptr->get_body_ptr();

        //------------------------------------------------------------
        // FIND THE RULE BODY IN WHICH IT APPEARS
        // This is necessary to impose base class node_class onto
        //  derived class body_node_class
        // -----------------------------------------------------------

         appearance_b_ptr = appearance_v_ptr->get_first_body();
         while ((rule_bod != appearance_b_ptr) && (appearance_b_ptr != nullptr))
               appearance_b_ptr = appearance_b_ptr->get_next_ptr();

         // appearance_b_ptr IS NOW POINTING TO THE CORRECT BODY
         appearance_b_ptr->set_body_status(1);      // 1 means ELIMINATED

         r_ptr = r_ptr->get_next_ptr();
     } // WHILE  vertex true, appears negatively
      
 } // IF truth_val is TRUE  or TOP




 // VERTEX IS FALSE OR TOP... 0 OR 3
 if ((vertex_truth_val == 0) || (vertex_truth_val == 3))
   {

   // ************************************************* //
   //  Vertex FALSE... Appears Negatively
   // ************************************************* //

    // EXCISE ALL NEGATIVE APPEARANCES THROUGHOUT THE GRAPH

    r_ptr = v_ptr->get_first_neg_appearance();
    while (r_ptr != nullptr) {
         appearance_head = r_ptr->get_value();
         appearance_v_ptr = Vertexlist.find_val_ptr(appearance_head);
         rule_bod = r_ptr->get_body_ptr();

        //------------------------------------------------------------
        // FIND THE RULE BODY IN WHICH IT APPEARS
        // This is necessary to impose base class node_class onto
        //  derived class body_node_class
        // -----------------------------------------------------------

         appearance_b_ptr = appearance_v_ptr->get_first_body();
         while ((rule_bod != appearance_b_ptr) && (appearance_b_ptr != nullptr))
               appearance_b_ptr = appearance_b_ptr->get_next_ptr();

         // appearance_b_ptr IS NOW POINTING TO THE CORRECT BODY	
         appearance_b_ptr->increase_num_literals_sat(1);
         appearance_b_ptr->update_body_status();
         
         r_ptr = r_ptr->get_next_ptr();

     } // WHILE  vertex false, appears negatively


        

   // ************************************************* //
   //  Vertex FALSE ... Appears Positively              //
   // ************************************************* //

    // ELIMINATE ALL RULES WITH POSITIVE APPEARANCES... THEY ARE FALSE

    r_ptr = v_ptr->get_first_pos_appearance();
    while (r_ptr != nullptr) {
         appearance_head = r_ptr->get_value();
         appearance_v_ptr = Vertexlist.find_val_ptr(appearance_head);
         rule_bod = r_ptr->get_body_ptr();

        //------------------------------------------------------------
        // FIND THE RULE BODY IN WHICH IT APPEARS
        // This is necessary to impose base class node_class onto
        //  derived class body_node_class
        // -----------------------------------------------------------

         appearance_b_ptr = appearance_v_ptr->get_first_body();
         while ((rule_bod != appearance_b_ptr) && (appearance_b_ptr != nullptr))
               appearance_b_ptr = appearance_b_ptr->get_next_ptr();

         // appearance_b_ptr IS NOW POINTING TO THE CORRECT BODY
         appearance_b_ptr->set_body_status(1);      // 1 means ELIMINATED

         r_ptr = r_ptr->get_next_ptr();
     } // WHILE  vertex true, appears negatively
      
 } // IF truth_val is FALSE  or TOP

} // PROPOGATE_TRUTHFULNESS


///////////////////////////////////////////////////////////////////////////
///   Proprogates the truthfulness of all nodes in the graph that are
///   TRUE or FALSE.
///////////////////////////////////////////////////////////////////////////
void logic_program_class::update_graph()
{
     vertex_class          *v_ptr;
     int                    next_truth_val;

     v_ptr = Vertexlist.get_first();
     if (v_ptr != nullptr)
        next_truth_val = v_ptr->get_truth();

     while (v_ptr != nullptr) {
       // DON'T PROPOGATE TRUTHFULNESS OF BOTTOM NODES
       if (next_truth_val != 2) {       //  WHERE 2 MEANS BOTTOM
             propogate_truthfulness_KK(v_ptr);
        } // IF TRUTH ESTABLISHED

       v_ptr = v_ptr->get_next_ptr();
       if (v_ptr != nullptr)
            next_truth_val = v_ptr->get_truth();
     }// WHILE NOT END OF GRAPH

} // UPDATE_GRAPH


////////////////////////////////////////////////////////////////////////////
///  Performs assigns truth values via the Kripke-Kleene Semantics.
///  The model is then displayed and totality is indicated. 
///////////////////////////////////////////////////////////////////////////
void logic_program_class::get_KK_model()
{

    int        has_changed1;
    int        has_changed2;

    has_changed1 = 1;  // INITIALIZED THIS WAY TO GET THE WHILE-LOOP STARTED
    has_changed2 = 1;
    while ((has_changed1 == 1) || (has_changed2 == 1)) {
       has_changed1 = 0;  
       has_changed2 = 0 ;
       has_changed1 = determine_truths();
       has_changed2 = determine_falsities_KK();
       update_graph();
    }// WHILE  

//    cout << "The Kripke Kleene Model: \n \n \n ";
//    display_model();
} // GET_KK_MODEL

///////////////////////////////////////////////////////////////////////////
///  Displays all TRUE, FALSE, BOTTOM, and TOP vertices.
///  Indicates whether or not the current assignment of the graph is total.
///////////////////////////////////////////////////////////////////////////
void logic_program_class::display_model()
{
    int   n_trues, n_falses, n_bottoms, n_tops;


    cout << " TRUE VERTICES \n";
    cout << " -------------  \n";
    print_truth_vals(1);
    cout << "\n";  
    cout << " FALSE VERTICES \n";
    cout << " --------------  \n";
    print_truth_vals(0);
    cout << "\n";  
    cout << " BOTTOM VERTICES \n";
    cout << " ---------------  \n";
    print_truth_vals(2);                // 2 means BOTTOM
    cout << "\n";  
    cout << " TOP VERTICES \n";
    cout << " -------------  \n";
    print_truth_vals(3);
    cout << "\n";  
    
    if ((total(&n_trues, &n_falses, &n_bottoms, &n_tops))==0) {
       cout << "The model is NOT TOTAL. \n";
       cout << "---------------------- \n";
       cout << " The following vertices were unassigned:\n";
       print_truth_vals(2);             // 2 means BOTTOM
    }
    else if ((total(&n_trues, &n_falses, &n_bottoms, &n_tops))==2) {
       cout << "The model is CONTRADICTORY.\n";
       cout << "-------------------------- \n";
//     cout << "The following vertices were unassigned:\n";
//     print_truth_vals(2);             // 2 means BOTTOM
//     cout << "\n";
       cout << "The following vertices were assigned TOP:\n";
       print_truth_vals(3);             // 3 means TOP 
       cout << "\n";
    }
    else
       cout << "The model is TOTAL. \n";
    cout << "\n  \n";

    cout << "There were " << n_trues << " assigned TRUES. \n";
    cout << "There were " << n_falses << " assigned FALSES. \n";
    cout << "There were " << n_bottoms << " assigned BOTTOMS. \n";
    cout << "There were " << n_tops << " assigned TOPS. \n";
    cout << "\n \n ";



} // DISPLAY_MODEL

/////////////////////////////////////////////////////////////////////////
/// Prints all vertex values with truth value  0,1,2,3 (F, T, BOT, TOP)
/////////////////////////////////////////////////////////////////////////
void logic_program_class::print_truth_vals(int t_val)
{

   vertex_class    *v_ptr;

   v_ptr = Vertexlist.get_first();

   while (v_ptr != nullptr) {
       if ((v_ptr->get_truth())  == t_val) 
           cout << v_ptr->get_value() << "\n"; 
       v_ptr = v_ptr->get_next_ptr();
   }// WHILE


} // PRINT_TRUTH_VALS


/////////////////////////////////////////////////////////////////////////
/// Prints all vertex postorder numbers
/////////////////////////////////////////////////////////////////////////
void logic_program_class::print_postorder_nums()
{

   vertex_class    *v_ptr;

   v_ptr = Vertexlist.get_first();

   while (v_ptr != nullptr) {
       v_ptr->print_postorder_num();
       v_ptr = v_ptr->get_next_ptr();
   }// WHILE


} // PRINT_POSTORDER_NUMS


//  J E N N I F E R
////////////////////////////////////////////////////////////////////////////
/// Determines whether or not the current assignment of the graph is total.
/// This function returns:
///        1 -- if the model is total  (every vertex assigned either 
///                                     TRUE or FALSE... 0 or 1)
///        0 -- if the model is NOT total (at least one vertex assigned
///                                     BOTTOM..2)
///        2 -- if the model is CONTRADICTORY (at least one vertex assigned
///                                     TOP...3)
////////////////////////////////////////////////////////////////////////////
int logic_program_class::total(int *num_true,  int *num_false, 
                               int *num_bottom, int *num_top)
{

   vertex_class    *v_ptr;
   int              cur_t_val;
   int              is_total;

   is_total = 1;
   *num_true = 0;
   *num_false = 0;
   *num_bottom = 0;
   *num_top = 0;

   v_ptr = Vertexlist.get_first();
   while (v_ptr != nullptr) {
       cur_t_val = v_ptr->get_truth();
       switch  (cur_t_val)  {
          case 0: { *num_false = *num_false + 1; break;}
          case 1: { *num_true = *num_true + 1; break;}
          case 2: { *num_bottom = *num_bottom + 1; is_total = 0;
                     break;}
          case 3: { *num_top = *num_top + 1; is_total = 2; break;}
       } // SWITCH

       v_ptr = v_ptr->get_next_ptr();
   }// WHILE
   

   if (*num_top > 0 )
         return(2);   // 2 means CONTRADICTORY
   else if (*num_bottom > 0)
         return(0);   // 0 means NOT TOTAL
   else
         return(1);   // 1 means TOTAL
    

} // TOTAL 

/////////////////////////////////////////////////////////////////////////
///  Performs the Tp* operation until there is no change.
/////////////////////////////////////////////////////////////////////////
void logic_program_class::Tp_star()
{

    int        has_changed;

    has_changed = 1;  // INITIALIZED THIS WAY TO GET THE WHILE-LOOP STARTED
    while (has_changed == 1) {
       has_changed = 0;  
       has_changed = determine_truths();
       update_graph();
    }// WHILE  

} // Tp*


////////////////////////////////////////////////////////////////////////////
///  Performs assigns truth values via the Well_Founded Semantics.
///  The model is then displayed and totality is indicated. 
///////////////////////////////////////////////////////////////////////////
void logic_program_class::get_WF_model_definition() 
{

    int        has_changed1, has_changed2;

    do  {
         has_changed1 = 0; has_changed2 = 0; 

         has_changed1 = determine_truths();

         determine_J();  
 
         has_changed2 = determine_falsities_WF();

         if ((has_changed1 == 1) || (has_changed2 == 1)) {
               update_graph();
         } // IF

    } // DO_WHILE

    while ((has_changed1 == 1) || (has_changed2 == 1));

} // GET_WF_MODEL


//---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////
///   Iteratively constructs J.  J is the complement of Up.
///   A vertex p is in J iff p has at least one body such that:
///        1)  none of its subgoals are false (i.e., it does not have
///            status of ELIMINATED)
///        2)  all of its positive subgoals are IN_J  (i.e., all of
///            its pos subgoals have access==1)
///
//////////////////////////////////////////////////////////////////////

void logic_program_class::determine_J()
{  
     vertex_class       *v_ptr;
     body_node_class    *b_ptr;
     int                 current_body_stat;
     int                 next_access_val;
     int                 changed;
     int                 in_J; 
     int                 performed_assign;

 reassign_access();

 do { 
    v_ptr = Vertexlist.get_first();
    next_access_val = v_ptr->get_access();
    changed = 0;                    // 0 means FALSE
    while (v_ptr != nullptr) {

         // DON'T UPDATE VERTICES ALREADY IN J
         if (next_access_val != 1) {

           // EXAMINE BODYLIST FOR NON-ELIMINATED BODIES WHOSE POS LITS ARE IN_J 
           b_ptr = v_ptr->get_first_body();

           while (b_ptr != nullptr) {
                current_body_stat = b_ptr->get_body_status();
                if (current_body_stat != 1)  {   // 1 means ELIMINATED 
                      in_J = check_all_pos_subgoals(b_ptr);

                      if (in_J == 1) {
                          v_ptr->assign_access(1);    // 1 means TRUE

                          changed = 1; 
                          b_ptr = nullptr;
                          break;
                       } // IF in_J = 1
                 } // IF CURRENT BODY NOT ELIMINATED

                 b_ptr = b_ptr->get_next_ptr();

            } // WHILE THERE ARE MORE BODIES

       } // IF NODE ISN'T ALREADY IN J

       v_ptr = v_ptr->get_next_ptr();
       if (v_ptr != nullptr)
            next_access_val = v_ptr->get_access();

     }// WHILE  STILL MORE VERTICES IN THE LIST

  } // DO_WHILE
  while (changed == 1);

} // DETERMINE_J


////////////////////////////////////////////////////////////////////////
///  Verifies that all positive subgoals are in J.
///////////////////////////////////////////////////////////////////////
int logic_program_class::check_all_pos_subgoals(body_node_class *b_ptr)
{
    literal_class      *l_ptr;
    vertex_class       *v_ptr;
    int                 all_in_J;

    l_ptr = b_ptr->get_first_pos_lit_ptr();

    all_in_J = 1;
    while (l_ptr != nullptr) {
      v_ptr = Vertexlist.find_val_ptr((l_ptr->get_value()));

      if ((v_ptr->get_access()) != 1) {
              all_in_J = 0;
              l_ptr = nullptr;
              break;
      } // IF

      l_ptr = l_ptr->get_next_ptr();
    } // WHILE
    
    return all_in_J;
 } // CHECK_ALL_POS_SUBGOALS

    


///////////////////////////////////////////////////////////////////////
///  Performs exactly one traversal of the graph (Vertexlist) and
///  checks for vertices that satisfy the conditions for being FALSE.
///  The field:  truth_val is then set to FALSE (0).
///
///     A vertex is FALSE IF:
///           It is not in J  (its access field is 0)  
//////////////////////////////////////////////////////////////////////

int logic_program_class::determine_falsities_WF()
{  
     vertex_class       *v_ptr;
     body_node_class    *b_ptr;
     int                 current_body_stat;
     int                 next_truth_val;
     int                 next_access_val;
     int                 changed;

    v_ptr = Vertexlist.get_first();
    changed = 0;

    while (v_ptr != nullptr) {
       next_truth_val = v_ptr->get_truth();
       next_access_val = v_ptr->get_access(); 

      if ( (next_truth_val == 2)  && (next_access_val == 0)) {
               v_ptr->assign_truth(0);    // 0 means FALSE
               changed = 1;
      } // IF

      else if ( (next_truth_val == 1)  && (next_access_val == 0)) {
               v_ptr->assign_truth(3);    // 3 means TOP  
               changed = 1;
      } // ELSE


      // PROCEED TO THE NEXT VERTEX IN THE GRAPH
      v_ptr = v_ptr->get_next_ptr();
    } // WHILE

    return changed;
     
} // DETERMINE_FALSITIES_WF

////////////////////////////////////////////////////////////////////////
///  Reinitializes the "access" field used for generating the
///  the complement of the greatest unfounded set.  This routine
///  assigns all TRUE and TOP nodes to automatically be in J (ie: access == TRUE) 
///////////////////////////////////////////////////////////////////////

void logic_program_class::reassign_access()
{
     vertex_class    *v_ptr;
     int              cur_truth;

     v_ptr = Vertexlist.get_first();
     while (v_ptr != nullptr) {
          cur_truth = v_ptr->get_truth();
           
          // AUTOMATICALLY INCLUDE TRUE AND TOP VERTICES IN J
          if ((cur_truth == 1) || (cur_truth == 3)) {
               v_ptr->assign_access(1);
          } // IF

          else {
               v_ptr->assign_access(0);  
          } // ELSE

          v_ptr = v_ptr->get_next_ptr();
     } // WHILE
}


//////////////////////////////////////////////////////////////////////////
///  Preassigns variables FALSE for 4-value logic implementation
///      Repeat Num_Preassign_False (a global var) times:
///            --generate a random number 
///            --find it in the graph
///            --if it exists, preassign it FALSE, increment cur_vert
///            --if it doesn't exist, continue and do NOT increment cur_vert
///
//////////////////////////////////////////////////////////////////////////

void logic_program_class::preassign_false_variables()
{
     vertex_class    *v_ptr;
     int              cur_vert;
     int              head_val;

     cur_vert = 0;

//DDDDDDDDDDDDDDDDDDDDDDDd
//cout << "just entered preassign_false_vari...   curvert is " << cur_vert << "\n";
//DDDDDDDDDDDDDDDDDDDDDDDDdd

     while  (cur_vert < Num_Preassign_False) {
         // GENERATE A RANDOM NUMBER

//DDDDDDDDDDDDDDDDDDDDDDDd
//cout << "inside WHILE curvert is " << cur_vert << "\n";
//cout << "inside WHILE Num_Variables is " << Num_Variables << "\n";
//DDDDDDDDDDDDDDDDDDDDDDDDdd

          head_val = get_random_val(Num_Variables);
//DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDd
//cout << "inside WHILE head_val is " << head_val << "\n";
//DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDd

          v_ptr = Vertexlist.find_val_ptr(head_val); 
//DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDd
//cout << "inside WHILE found vertex is " << v_ptr << "\n";
//DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDd


          // IF VERTEX EXISTS 
          if (v_ptr != nullptr) {
//DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDd
//cout << "inside WHILE/IF vertex is \n";
//v_ptr->output();
//DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDd


              if ((v_ptr->get_guess()) != 1) { // IF NOT ALREADY PREASSIGNED
//                 v_ptr->assign_truth(0);
                   v_ptr->assign_W_val(0);
                   v_ptr->assign_guess(1);
                   cur_vert++;
               } // IF

//DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDd
//cout << "inside WHILE after IF vertex is: \n";
//v_ptr->output();
//cout << "cur_vert is.. " << cur_vert << "\n";
//DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDd



          } // IF
     } // WHILE

} // PREASSIGN_FALSE_VARIABLES

//////////////////////////////////////////////////////////////////////////
///  Transfers contents of field W_val to field "truth_val"...used to
///  prepare for "display_model"
//////////////////////////////////////////////////////////////////////////

void logic_program_class::transfer_W_to_truth()
{
     vertex_class    *v_ptr;
     int              cur_vert;

     v_ptr = Vertexlist.get_first();


     while (v_ptr != nullptr) {

          v_ptr->assign_truth((v_ptr->get_W_val()));
          v_ptr = v_ptr->get_next_ptr();
     } // WHILE
} // TRANSFER_W_TO_TRUTH


///////////////////////////////////////////////////////////////////
///  Retains all rule values (heads and subgoals) but
///  reinitializes all MODEL pertinent information.
///////////////////////////////////////////////////////////////////
void logic_program_class::initialize_graph()
{
    vertex_class       *v_ptr;
    body_node_class    *b_ptr;


    v_ptr = Vertexlist.get_first();
    while (v_ptr != nullptr) {
           // RESET VERTEX FIELDS OF TRUTH_VAl, ACCESS, AND GUESS
           v_ptr->assign_truth(2);    // 2 means BOTTOM
           v_ptr->assign_W_val(2);    // 2 means BOTTOM
           v_ptr->assign_J_val(0);    // 0 means FALSE 
           v_ptr->assign_access(0);   // 0 means FALSE
           v_ptr->assign_guess(0);
           v_ptr->assign_postorder_num(0);

           // INITIALIZE BODYLIST
           b_ptr = v_ptr->get_first_body();

           while (b_ptr != nullptr) {
              b_ptr->set_body_status(2);  // 2 means UNDETERMINED..BOTTOM
              if (b_ptr->get_negative_fact() == 1) {
                  b_ptr->set_pos_assess(0);   // 1 means TRUE.. init min to max
                  b_ptr->set_neg_assess(0);   //  (same)
              } // IF 
              else { //NOT A NEGATIVE FACT
                  b_ptr->set_pos_assess(1);   // 1 means TRUE.. init min to max
                  b_ptr->set_neg_assess(1);   //  (same)
              } // ELSE

              b_ptr = b_ptr->get_next_ptr();

            } // WHILE THERE ARE MORE BODIES

       v_ptr = v_ptr->get_next_ptr();
    }// WHILE  STILL MORE VERTICES IN THE LIST

} // INITIALIZE_GRAPH



/////////////////////////////////////////////////////////////////////////////
///  W E L L   F O U N D E D      F O U R  V A L U E   V E R S I O N
///
////////////////////////////////////////////////////////////////////////////

void logic_program_class::get_WF_4_value()
{
   int       W_change;
   int       J_change;

   do { 

         W_change = 0;

         perform_neg_assess_on_bodies();

         reinitialize_J_vals();

         do {
               J_change = 0;
               J_change = determine_J_vals();

             }
         while (J_change == 1);

         W_change = update_W_vals();

      }
   while (W_change == 1);


   ////////////////////////////////////////////////
   //   Move W_vals to the "truth_val" field
   ////////////////////////////////////////////////
   transfer_W_to_truth();


} // GET_WF_4_VALUE


void logic_program_class::get_WF_4_value_optimize()
{
   int       W_change;

   do { 

         W_change = 0;

         perform_neg_assess_on_bodies();

         reinitialize_J_vals();

         determine_J_vals_optimize();

         W_change = update_W_vals();

      }
   while (W_change == 1);


   ////////////////////////////////////////////////
   //   Move W_vals to the "truth_val" field
   ////////////////////////////////////////////////
   transfer_W_to_truth();


} // GET_WF_4_VALUE_OPTIMIZE



///////////////////////////////////////////////////////////////////////////
///  Returns the number 2^num_vars
///////////////////////////////////////////////////////////////////////////
int logic_program_class::compute_num_assignments(int num_vars)
{
    int  num_so_far = 1;

    for (int i = 0; i < num_vars; i++)
           num_so_far *= 2;

    return num_so_far;

}// compute_num_assignments

// ---------------------------------------------------------------------
void logic_program_class::assign_all_false_variables()
{
     vertex_class    *v_ptr;
     int              cur_vert;
     int              head_val;

     v_ptr = get_first_vertex();

     while (v_ptr != nullptr) {
        v_ptr->assign_W_val(0);
        v_ptr = v_ptr->get_next_ptr();
     } //WHILE

} // assign_all_false_variables


// ---------------------------------------------------------------------
//  Assigns the truth assignment to the THIS by using the
//  binary string model num as a map.  For example: model_num==14
//  assigns 1110  or FALSE - TRUE - TRUE - TRUE
//----------------------------------------------------------------------
void logic_program_class::assign_binary(int model_num)
{
     vertex_class    *v_ptr;

     v_ptr = get_first_vertex();

     while ((model_num > 0) && (v_ptr != nullptr)) {
        if ((model_num % 2)== 1) {
                v_ptr->assign_W_val(1);
                v_ptr->assign_J_val(1);
        }//IF
        model_num /= 2;
        v_ptr = v_ptr->get_next_ptr();
     } //WHILE

} // assign_binary

//-----------------------------------------------------------------

int logic_program_class::get_num_vertices()
{
    return Vertexlist.get_length();
}



//////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////

void logic_program_class::find_first_stable_model()
{
      logic_program_class  *wf_residual;
      vertex_class         *cur_factor_vertex;
      vertex_class         *orig_graph_vertex;
      int                   fact_totality = 99;
      int                   fact_num_true = 0;
      int                   fact_num_false = 0;
      int                   fact_num_bottom = 0;
      int                   fact_num_top = 0;
      int                   not_stable_yet;

       get_WF_4_value_optimize();

       //=====================================================================

       // IF THE WELL-FOUNDED MODEL IS NOT TOTAL..CREATE THE WF-REDISUAL
       if (total(&fact_num_true, &fact_num_false,
                                    &fact_num_bottom, &fact_num_top)!= 1) {

           wf_residual = this->factor_out();

           //EXHAUSTIVELY GENERATE ALL MODELS UNTIL A STABLE MODEL IS FOUND 
        
            int total_in_factor = wf_residual->get_num_vertices();
            int num_assignments = compute_num_assignments(total_in_factor);

            int cur_binary_model = 0;
            int model_found = 0;

            while ((cur_binary_model < num_assignments) && (!model_found)) {

                     wf_residual->assign_all_false_variables(); 
                     wf_residual->assign_binary(cur_binary_model);

                    //CHECK STABILITY
                     wf_residual->get_WF_4_value_optimize();

                  if (wf_residual->total(&fact_num_true, &fact_num_false,
                                         &fact_num_bottom, &fact_num_top)==1)
                              model_found = 1;
                  else
                              cur_binary_model++;

            } //WHILE 

            // IF the wf_residual was able to be stably assigned...copy to original graph
            if (model_found) {
                 cur_factor_vertex = wf_residual->get_first_vertex();   
                 while (cur_factor_vertex != nullptr) {
                       orig_graph_vertex = find_vertex(cur_factor_vertex->get_value());
                       orig_graph_vertex->assign_truth(cur_factor_vertex->get_truth()); 

                       cur_factor_vertex = cur_factor_vertex->get_next_ptr();
                 }//WHILE
            }//IF

            wf_residual->clear();
            delete wf_residual;
       } // IF


} //find_first_stable_model

/////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////
void logic_program_class::perform_neg_assess_on_bodies()
{
      vertex_class       *v_ptr;
      body_node_class    *b_ptr;
     
      v_ptr = Vertexlist.get_first();

      while (v_ptr != nullptr) {
             
             // TRAVERSE BODY LIST SEARCHING FOR BODIES WITH NON-NIL
             //     NEGATIVE LITERAL LISTS
             b_ptr = v_ptr->get_first_body();

             while (b_ptr != nullptr) {
                     b_ptr->determine_neg_assess(this);
                     b_ptr = b_ptr->get_next_ptr();
             } //WHILE

             v_ptr = v_ptr->get_next_ptr();
      } // WHILE

} //PERFORM_NEG_ASSESS_ON_BODIES




//////////////////////////////////////////////////////////////////////


void logic_program_class::reinitialize_J_vals()
{
     vertex_class    *v_ptr;

     v_ptr = Vertexlist.get_first();
     while (v_ptr != nullptr) {
          v_ptr->assign_J_val(0);  // 0 is FALSE
          v_ptr = v_ptr->get_next_ptr();
     } // WHILE
}

//////////////////////////////////////////////////////////////////////////
///  For each variable in the graph
///         For each body of variable
///              perform positive assessment (glb of pos lits' J_vals)
///              determine body val (glb of neg_assess and pos_assess)
///         Take the lub (truth order) of all its bodies' vals
///           to ascertain the J_val of the variable
///
///  This routine traverses the graph exactly once.
///
//////////////////////////////////////////////////////////////////////////

int logic_program_class::determine_J_vals()
{
     vertex_class     *v_ptr;
     body_node_class  *b_ptr;
     int               change;
     int               lub_so_far;
     int               b_val;

     v_ptr = Vertexlist.get_first();
     change = 0;
     while (v_ptr != nullptr)   {
         lub_so_far = 0;               // 0 is FALSE
         
         //Traverse bodylist and establish each body status;  Incrementally
         //  decide whether or not the status is higher than lub_so_far

         b_ptr = v_ptr->get_first_body();
         while (b_ptr != nullptr)  {
               b_ptr->determine_pos_assess(this);  
               b_val = b_ptr->determine_body_status();
               lub_so_far = lub_t(lub_so_far, b_val);
               b_ptr = b_ptr->get_next_ptr();
         } // WHILE

         if (lub_so_far != v_ptr->get_J_val()) {
               v_ptr->assign_J_val(lub_so_far);
               change = 1;
         } // IF

         v_ptr = v_ptr->get_next_ptr();
    } // WHILE

    return change;

}// DETERMINE_J_VALS 

//------------------------


//////////////////////////////////////////////////////////////////////////
///  OPTIMIZED VERSION:
///  This routine traverses the graph exactly once simultaneously
///  assessing each variable's new J_val and storing all of that
///  changed variable's POSITIVE APPEARNCES on the queue.
///
///  It then proceeds to perform the same assessments on Q entries
///  until the Q is empty.
///
//////////////////////////////////////////////////////////////////////////

void logic_program_class::determine_J_vals_optimize()
{
     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     rule_class                    *r_ptr;
     int                            lub_so_far;
     int                            b_val;
//     list_class<vertex_ptr_class>   Q;
     vertex_ptr_class              *cur_appear;
     int                            tempval;
     vertex_class                  *tempvert;
     body_node_class               *tempbody;


     v_ptr = Vertexlist.get_first();
     while (v_ptr != nullptr)   {
         lub_so_far = 0;               // 0 is FALSE
         
         //Traverse bodylist and establish each body status;  Incrementally
         //  decide whether or not the status is higher than lub_so_far

         b_ptr = v_ptr->get_first_body();
         while (b_ptr != nullptr)  {
               b_ptr->determine_pos_assess(this);  
               b_val = b_ptr->determine_body_status();
               lub_so_far = lub_t(lub_so_far, b_val);
               b_ptr = b_ptr->get_next_ptr();
         } // WHILE

         if (lub_so_far != v_ptr->get_J_val()) {
               v_ptr->assign_J_val(lub_so_far);
  

               // TRAVERSE THE POSITIVE APPEARANCE LIST AND ENQUEUE EACH ONE 
                r_ptr = v_ptr->get_first_pos_appearance();
                while (r_ptr != nullptr) {
                   tempval = r_ptr->get_value();
                   tempvert = this->get_vertex_ptr(r_ptr);
                   tempbody = this->get_body_ptr(r_ptr);
                   cur_appear = new vertex_ptr_class(tempval, tempvert, tempbody);
                   Q.add_ptr(cur_appear);
                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE

         } // IF

         v_ptr = v_ptr->get_next_ptr();
    } // WHILE


   while ( (Q.get_length()) > 0) {

         cur_appear = Q.dequeue();           

         v_ptr = cur_appear->get_graphspot(); 

         b_ptr = cur_appear->get_bodyspot();

         tempval =   v_ptr->get_J_val();   // OLD J_VAL

         delete cur_appear;

         b_ptr->determine_pos_assess(this);  
         b_val = b_ptr->determine_body_status();

         lub_so_far = lub_t(tempval, b_val);

         if (lub_so_far != tempval) {  // IS LUB > OLD  J_VAL?
              // MAKE A CHANGE
               v_ptr->assign_J_val(lub_so_far);

              ///  PROPOGATE THE CHANGE BY ENQUEUE THE POSITIVE APPEARANCE LIST
                r_ptr = v_ptr->get_first_pos_appearance();
                while (r_ptr != nullptr) {
                   tempval = r_ptr->get_value();
                   tempvert = this->get_vertex_ptr(r_ptr);
                   tempbody = this->get_body_ptr(r_ptr);
                   cur_appear = new vertex_ptr_class(tempval, tempvert, tempbody);
                   Q.add_ptr(cur_appear);
                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE

         } // IF

   } // WHILE

   Q.cleanup();

}// DETERMINE_J_VALS_OPTIMIZE 




////////////////////////////////////////////////////////////////////////////
///  Travers graph and compute the lub (knowledge ordering) of
///  newly found J_val and last iteration's W_val
////////////////////////////////////////////////////////////////////////////

int logic_program_class::update_W_vals()
{

    vertex_class       *v_ptr;
    int                 change;
    int                 Jval, Wval, newWval;

    v_ptr = Vertexlist.get_first();
    change = 0;
    
    while (v_ptr != nullptr)  {
         Jval = v_ptr->get_J_val();
         Wval = v_ptr->get_W_val();
         newWval = lub_k(Jval, Wval);

         if (newWval != Wval)  {
              change = 1;
              v_ptr->assign_W_val(newWval);
         } // IF

         v_ptr = v_ptr->get_next_ptr();

    } // WHILE 


    return change;
} // UPDATE_W_VALS

    
//////////////////////////////////////////////////////////////////////////////
///  Traverses the graph locating the specified literal's vertex.
///  This returns that vertex's J value.
//////////////////////////////////////////////////////////////////////////////

int logic_program_class::get_lit_Jval(literal_class *l_ptr)
{
     vertex_class   *v_ptr;
     
     v_ptr = get_lit_vertex(l_ptr);
     
     return (v_ptr->get_J_val());
} // GET_LIT_JVAL


//////////////////////////////////////////////////////////////////////////////
///  Traverses the graph locating the specified literal's vertex.
///  This returns that vertex's J value.
//////////////////////////////////////////////////////////////////////////////

int logic_program_class::get_neg_lit_Wval(literal_class *l_ptr)
{
     vertex_class   *v_ptr;
     int             Wval;
     
     v_ptr = get_lit_vertex(l_ptr);
     Wval = v_ptr->get_W_val();
     switch (Wval) {
        case 0 :  return(1); break;
        case 1 :  return(0); break;
        case 2 :  return(2); break;
        case 3 :  return(3); break;
     }  //SWITCH
} // GET_NEG_LIT_WVAL   


//////////////////////////////////////////////////////////////////////////////
///  Traverses the graph locating the specified literal's vertex.
//////////////////////////////////////////////////////////////////////////////

vertex_class  *logic_program_class::get_lit_vertex(literal_class *l_ptr)
{
     vertex_class   *search_vertex;
     int             search_head;

     search_head = l_ptr->get_value();
     search_vertex = find_add_vertex(search_head);
     return(search_vertex);
     
} // GET_LIT_VERTEX


//////////////////////////////////////////////////////////////////////////////
///  Traverses the graph locating the specified rule's vertex.
//////////////////////////////////////////////////////////////////////////////

vertex_class  *logic_program_class::get_vertex_ptr(rule_class *r_ptr)
{
     vertex_class   *search_vertex;
     int             search_head;

     search_head = r_ptr->get_value();
     search_vertex = find_add_vertex(search_head);
     return(search_vertex);
     
} // GET_VERTEX_PTR


//////////////////////////////////////////////////////////////////////////////
///  Traverses the graph locating the specified rule's body.
//////////////////////////////////////////////////////////////////////////////

body_node_class *logic_program_class::get_body_ptr(rule_class *r_ptr)
{
     vertex_class   *search_vertex;
     int             search_head;
     body_node_class *b_ptr;
     node_class      *n_ptr;


     search_vertex = get_vertex_ptr(r_ptr);
     n_ptr = r_ptr->get_body_ptr();
     b_ptr = search_vertex->get_first_body();
     while (b_ptr != nullptr)  {
           if (b_ptr == n_ptr)
                    break;
           else
                    b_ptr = b_ptr->get_next_ptr();

    } //WHILE

    return b_ptr;
     
} // GET_BODY_PTR


// * * * * * * * * * * * * * * * * * * * * * * * ** * ** *** * *

// 1   JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ


// * * * * * * * * * * * * * * * * * * * * * * * ** * ** *** * *


void logic_program_class::get_WF_linear_unit()
{

     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     rule_class                    *r_ptr;
     int                            lub_so_far;
     int                            b_val;
     vertex_ptr_class              *cur_appear;
     int                            old_J, old_W, new_J, new_W;
     int                            tempval;
     int                            temptruth;
     vertex_class                  *tempvert;
     int                            temp_unit_pos, temp_unit_neg;
     int                             J_change, W_change;
     
                 

//cout << "Upon entering WF_linear_unit, the graph is.... \n \n";
//output_graph();
//cout << "\n \n \n";

//cout << "The Q has been initialized to ... \n \n ";
//Q.print();

//***************************************************************************
// PERFORM INITIAL NEGATIVE ASSESSMENTS BASED ON ALL NEGATIVES BEING BOTTOM
//***************************************************************************

   perform_neg_assess_on_bodies();
   
   do {
        J_change = 0;
        J_change = determine_J_vals();
      }
   while (J_change == 1);


   W_change = update_W_vals();

//cout << "\n  =====================================================\n";
//cout << "After the LOOP of WF_linear_unit, the graph is.... \n \n";
//output_graph();
//cout << "\n \n \n";
//cout << "The Q is ... \n \n ";
//cout << "\n  =====================================================\n";
//Q.print();




/* ----------------------------------------------------------------------------

    Enqueue all variables v such that W_val(v) is bottom and v
      heads a rule   v <-- ~s, where W_val(s) is true or false
   ----------------------------------------------------------------------------
*/

   v_ptr = Vertexlist.get_first();
   while (v_ptr != nullptr)   {
        tempval = v_ptr->get_W_val();

        if ((tempval==0) || (tempval==1)) {

          //Enqueue all negative appearances that are not yet assigned

          // TRAVERSE THE NEGATIVE APPEARANCE LIST AND ENQUEUE EACH ONE OF VAL BOTTOM
                r_ptr = v_ptr->get_first_neg_appearance();
                while (r_ptr != nullptr) {
                   tempval = r_ptr->get_value();
                   tempvert = this->get_vertex_ptr(r_ptr);
                   temptruth = tempvert->get_W_val();
                   if (temptruth == 2) {    // ENQUEUE ONLY BOTTOMS
                      cur_appear = new vertex_ptr_class(tempval, tempvert);
                      Q.add_ptr(cur_appear);
                   }  // IF 
                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE

         } // IF W_VAL \in {TRUE, FALSE}


//       else // {  W_VAL is BOTTOM }
//         {
//              v_ptr->assign_J_val(0);   // REINITIALIZE J_VAL TO FALSE
//         }// ELSE


         v_ptr = v_ptr->get_next_ptr();
    } // WHILE 

//cout << "\n  =====================================================\n";
//cout << "After the INITIAL ENQUEUE of WF_linear_unit, the graph is.... \n \n";
//output_graph();
//cout << "\n \n \n";
//cout << "The Q is ... \n \n ";
//cout << "\n  =====================================================\n";
//Q.print();


//***************************************************************************
// Propogate truths dependent upon negative literals
//***************************************************************************

  while ( (Q.get_length()) > 0) {

      cur_appear = Q.dequeue();
         

      v_ptr = cur_appear->get_graphspot();
      delete cur_appear;
      tempval = v_ptr->get_W_val();

      if (tempval == 2) {    // ONLY COMPUTE VERTICES OF VAL BOTTOM

         new_J = v_ptr->determine_new_J_val(this);

         if ((new_J == 0) || (new_J ==1)) {
                v_ptr->assign_J_val(new_J);
                v_ptr->assign_W_val(new_J);

               ///  PROPOGATE THE CHANGE BY ENQUEUING THE POSITIVE APPEARANCE LIST
                r_ptr = v_ptr->get_first_pos_appearance();
                while (r_ptr != nullptr) {
                   tempval = r_ptr->get_value();
                   tempvert = this->get_vertex_ptr(r_ptr);
                   temptruth = tempvert->get_W_val();
                   if (temptruth == 2) {    // ENQUEUE ONLY BOTTOMS
                      cur_appear = new vertex_ptr_class(tempval, tempvert);
                      Q.add_ptr(cur_appear);
                   } // IF DEQUEUE IS BOTTOM
                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE


               ///  PROPOGATE THE CHANGE BY ENQUEUING THE NEGATIVE APPEARANCE LIST
                r_ptr = v_ptr->get_first_neg_appearance();
                while (r_ptr != nullptr) {
                   tempval = r_ptr->get_value();
                   tempvert = this->get_vertex_ptr(r_ptr);
                   temptruth = tempvert->get_W_val();
                   if (temptruth == 2) {    // ENQUEUE ONLY BOTTOMS
                      cur_appear = new vertex_ptr_class(tempval, tempvert);
                      Q.add_ptr(cur_appear);
                   } // IF DEQUEUE IS BOTTOM
                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE

         } // IF J is true or false

        } // IF HEAD of Queue has truth value BOTTOM

   } // WHILE Q NOT EMPTY
                        
      

Q.cleanup();
         

//cout << "After semantics the graph is... \n \n";
//output_graph();
//cout << "\n \n \n";

//cout << "The Q is  ... \n \n ";
//Q.print();



   ////////////////////////////////////////////////
   //   Move W_vals to the "truth_val" field
   ////////////////////////////////////////////////
   transfer_W_to_truth();

} // GET_WF_LINEAR_UNIT

// 3   JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ

// * * * * * * * * * * * * * * * * * * * * * * * ** * ** *** * *


void logic_program_class::get_WF_linear_stack()
{

     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     rule_class                    *r_ptr;
     int                            lub_so_far;
     int                            b_val;
     vertex_ptr_class              *cur_appear;
     int                            old_J, old_W, new_J, new_W;
     int                            tempval;
     vertex_class                  *tempvert;
                 



//initialize_Q_bodiless();
//initialize_Q_headless();
//initialize_Q_negatives();
//initialize_Q_positives();

//cout << "Upon entering WF_linear_stack, the graph is.... \n \n";
//output_graph();
//cout << "\n \n \n";

  initialize_Q_negatives_stack();
  initialize_Q_headless_stack();
  initialize_Q_bodiless_stack();

//  initialize_Q_positives_stack();

//cout << "The Q has been initialized to ... \n \n ";
//Q.print();

         
  while ( (Q.get_length()) > 0) {

         cur_appear = Q.pop();

         v_ptr = cur_appear->get_graphspot();

         delete cur_appear;

         // UPDATE J
         old_J = v_ptr->get_J_val();
         v_ptr->assign_J_val(0); // JUST IN CASE THE RULE IS POS RECURSIVE
         new_J = v_ptr->determine_new_J_val(this);
         if (old_J != new_J) {

//cout << "just changed v_ptr's J_VAL...\n \n";
//v_ptr->output();

                v_ptr->assign_J_val(new_J);


               ///  PROPOGATE THE CHANGE BY PUSHING THE POSITIVE APPEARANCE LIST
                r_ptr = v_ptr->get_first_pos_appearance();
                while (r_ptr != nullptr) {
                   tempval = r_ptr->get_value();
                   tempvert = this->get_vertex_ptr(r_ptr);
                   cur_appear = new vertex_ptr_class(tempval, tempvert);

//cout << " About to enqueue ... \n \n";
//cur_appear->output();

                   Q.push(cur_appear);

//cout << " Just enqueued ... Q is now... \n \n";
//Q.print();

                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE

         } // IF
         else  {  //REASSIGN THE J_VAL THE PREVIOUS VAL BEFORE RECURSION CONSID
                v_ptr->assign_J_val(old_J);

         } // ELSE
      
        // UPDATE W
        old_W = v_ptr->get_W_val();
        new_W = lub_k(old_W, new_J);

/////////////////////////////////////////////////////////
// C A U T I O N ! ! ! ! ! ! !   JUSTIFY THIS !!!!!!
/////////////////////////////////////////////////////////
//        if ( new_W == 3 ) {
//                new_W = new_J; 
//           }

        if (old_W != new_W) {

           v_ptr->assign_W_val(new_W); 

          ///  PROPOGATE THE CHANGE BY ENQUEUEING THE NEGATIVE APPEARANCE LIST
           r_ptr = v_ptr->get_first_neg_appearance();

           while (r_ptr != nullptr) {
                tempval = r_ptr->get_value();
                tempvert = this->get_vertex_ptr(r_ptr);
                cur_appear = new vertex_ptr_class(tempval, tempvert);
                Q.push(cur_appear);
                r_ptr = r_ptr->get_next_ptr();
           } // WHILE

        } // IF

   } // WHILE STACK Q NOT EMPTY


     Q.cleanup();

   final_scan_W_vals_Q();

// --------------------------------------------------------------------
//  BEGIN  SECOND   SCAN
//
//


//cout << "  \n \n \n \n S E C O N D   S C A N   \n \n \n \n ";


  while ( (Q.get_length()) > 0) {

         cur_appear = Q.pop();

         v_ptr = cur_appear->get_graphspot();

         delete cur_appear;

         // UPDATE J
         old_J = v_ptr->get_J_val();

         // TEMPORARILY REINIT J TO ACCOUNT FOR POSITIVE RECURSION
         v_ptr->assign_J_val(0); 

         new_J = v_ptr->determine_new_J_val(this);

         if (old_J != new_J) {

                v_ptr->assign_J_val(new_J);

               ///  PROPOGATE THE CHANGE BY ENQUEUEING THE POSITIVE APPEARANCE LIST
                r_ptr = v_ptr->get_first_pos_appearance();
                while (r_ptr != nullptr) {
                   tempval = r_ptr->get_value();
                   tempvert = this->get_vertex_ptr(r_ptr);
                   cur_appear = new vertex_ptr_class(tempval, tempvert);

//cout << " About to enqueue ... \n \n";
//cur_appear->output();

                   Q.push(cur_appear);

//cout << " Just enqueued ... Q is now... \n \n";
//Q.print();

                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE

         } // IF
         else {  // Reinstate J after considering positive recursion
             v_ptr->assign_J_val(old_J);
         } // ELSE
        // UPDATE W
        old_W = v_ptr->get_W_val();
        new_W = lub_k(old_W, new_J);

/////////////////////////////////////////////////////////
// C A U T I O N ! ! ! ! ! ! !   JUSTIFY THIS !!!!!!
/////////////////////////////////////////////////////////
//        if ( new_W == 3 )
//                new_W = new_J;

        if (old_W != new_W) {

           v_ptr->assign_W_val(new_W); 

          ///  PROPOGATE THE CHANGE BY ENQUEUEING THE NEGATIVE APPEARANCE LIST
           r_ptr = v_ptr->get_first_neg_appearance();

           while (r_ptr != nullptr) {
                tempval = r_ptr->get_value();
                tempvert = this->get_vertex_ptr(r_ptr);
                cur_appear = new vertex_ptr_class(tempval, tempvert);

//cout << " About to enqueue ... \n \n";
//cur_appear->output();

                Q.push(cur_appear);

//cout << " Just enqueued ... Q is now... \n \n";
//Q.print();

                r_ptr = r_ptr->get_next_ptr();
           } // WHILE

        } // IF

   } // WHILE

// -------------------------------------------------------------------


   Q.cleanup();

   ////////////////////////////////////////////////
   //   Move W_vals to the "truth_val" field
   ////////////////////////////////////////////////
   transfer_W_to_truth();


} // GET_WF_LINEAR_STACK


// * * * * * * * ** ** * * ** * * * ***** **** ** ** ** ** ** ** 

///////////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////////
void logic_program_class::get_WF_linear_2()
{

     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     rule_class                    *r_ptr;
     int                            lub_so_far;
     int                            b_val;
     vertex_ptr_class              *cur_appear;
     int                            old_J, old_W, new_J, new_W;
     int                            tempval;
     vertex_class                  *tempvert;
                 



  initialize_Q_bodiless();
  initialize_Q_headless();
  initialize_Q_negatives();
  initialize_Q_positives();

//cout << "The Q has been initialized to ... \n \n ";
//Q.print();

         
  while ( (Q.get_length()) > 0) {

         cur_appear = Q.dequeue();

         v_ptr = cur_appear->get_graphspot();

         delete cur_appear;

         // UPDATE J
         old_J = v_ptr->get_J_val();
         new_J = v_ptr->determine_new_J_val(this);
         if (old_J != new_J) {

//cout << "just changed v_ptr's J_VAL...\n \n";
//v_ptr->output();

                v_ptr->assign_J_val(new_J);


               ///  PROPOGATE THE CHANGE BY ENQUEUEING THE POSITIVE APPEARANCE LIST
                r_ptr = v_ptr->get_first_pos_appearance();
                while (r_ptr != nullptr) {
                   tempval = r_ptr->get_value();
                   tempvert = this->get_vertex_ptr(r_ptr);
                   cur_appear = new vertex_ptr_class(tempval, tempvert);

//cout << " About to enqueue ... \n \n";
//cur_appear->output();

                   Q.add_ptr(cur_appear);

//cout << " Just enqueued ... Q is now... \n \n";
//Q.print();

                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE

         } // IF
      
        // UPDATE W
        old_W = v_ptr->get_W_val();
        new_W = lub_k(old_W, new_J);

/////////////////////////////////////////////////////////
// C A U T I O N ! ! ! ! ! ! !   JUSTIFY THIS !!!!!!
/////////////////////////////////////////////////////////
          if ( new_W == 3 ) {
                new_W = new_J; 

           }

        if (old_W != new_W) {

           v_ptr->assign_W_val(new_W); 

          ///  PROPOGATE THE CHANGE BY ENQUEUEING THE NEGATIVE APPEARANCE LIST
           r_ptr = v_ptr->get_first_neg_appearance();

           while (r_ptr != nullptr) {
                tempval = r_ptr->get_value();
                tempvert = this->get_vertex_ptr(r_ptr);
                cur_appear = new vertex_ptr_class(tempval, tempvert);
                Q.add_ptr(cur_appear);
                r_ptr = r_ptr->get_next_ptr();
           } // WHILE

        } // IF

   } // WHILE Q NOT EMPTY


     Q.cleanup();

   final_scan_W_vals_Q();

// --------------------------------------------------------------------
//  BEGIN  SECOND   SCAN
//
//


//cout << "  \n \n \n \n S E C O N D   S C A N   \n \n \n \n ";


  while ( (Q.get_length()) > 0) {

         cur_appear = Q.dequeue();

         v_ptr = cur_appear->get_graphspot();

         delete cur_appear;

         // UPDATE J
         old_J = v_ptr->get_J_val();
         new_J = v_ptr->determine_new_J_val(this);

         if (old_J != new_J) {

                v_ptr->assign_J_val(new_J);

               ///  PROPOGATE THE CHANGE BY ENQUEUEING THE POSITIVE APPEARANCE LIST
                r_ptr = v_ptr->get_first_pos_appearance();
                while (r_ptr != nullptr) {
                   tempval = r_ptr->get_value();
                   tempvert = this->get_vertex_ptr(r_ptr);
                   cur_appear = new vertex_ptr_class(tempval, tempvert);

//cout << " About to enqueue ... \n \n";
//cur_appear->output();

                   Q.add_ptr(cur_appear);

//cout << " Just enqueued ... Q is now... \n \n";
//Q.print();

                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE

         } // IF
      
        // UPDATE W
        old_W = v_ptr->get_W_val();
        new_W = lub_k(old_W, new_J);

/////////////////////////////////////////////////////////
// C A U T I O N ! ! ! ! ! ! !   JUSTIFY THIS !!!!!!
/////////////////////////////////////////////////////////
          if ( new_W == 3 )
                new_W = new_J;

        if (old_W != new_W) {

           v_ptr->assign_W_val(new_W); 

          ///  PROPOGATE THE CHANGE BY ENQUEUEING THE NEGATIVE APPEARANCE LIST
           r_ptr = v_ptr->get_first_neg_appearance();

           while (r_ptr != nullptr) {
                tempval = r_ptr->get_value();
                tempvert = this->get_vertex_ptr(r_ptr);
                cur_appear = new vertex_ptr_class(tempval, tempvert);

//cout << " About to enqueue ... \n \n";
//cur_appear->output();

                Q.add_ptr(cur_appear);

//cout << " Just enqueued ... Q is now... \n \n";
//Q.print();

                r_ptr = r_ptr->get_next_ptr();
           } // WHILE

        } // IF

   } // WHILE

// -------------------------------------------------------------------


   Q.cleanup();

   ////////////////////////////////////////////////
   //   Move W_vals to the "truth_val" field
   ////////////////////////////////////////////////
   transfer_W_to_truth();


} // GET_WF_LINEAR_2


// * * * * * * * * * * * * * * * * * * * * * * * ** * ** *** * *


void logic_program_class::initialize_Q_bodiless()
{

     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     vertex_ptr_class              *cur_appear;
     int                            tempval;
     vertex_class                  *tempvert;


//   cout << "upon entry to initialize_Q_bodiless() queue is... \n";
//   Q.print();

    // ENQUEUE ALL HEADS OF BODILESS RULES
     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         b_ptr = v_ptr->get_first_body();
         while (b_ptr != nullptr) {
            if( (b_ptr->is_bodiless_rule()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.add_ptr(cur_appear);
                  break;
             } // IF
            b_ptr = b_ptr->get_next_ptr();

          } // WHILE B-PTR NOT nullptr

          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr

} // INITIALIZE_Q_BODILESS



// * * * * * * * * * * * * * * * * * * * * * * * ** * ** *** * *


void logic_program_class::initialize_Q_bodiless_stack()
{

     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     vertex_ptr_class              *cur_appear;
     int                            tempval;
     vertex_class                  *tempvert;


//   cout << "upon entry to initialize_Q_bodiless() queue is... \n";
//   Q.print();

    // ENQUEUE ALL HEADS OF BODILESS RULES
     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         b_ptr = v_ptr->get_first_body();
         while (b_ptr != nullptr) {
            if( (b_ptr->is_bodiless_rule()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.push(cur_appear);
                  break;
             } // IF
            b_ptr = b_ptr->get_next_ptr();

          } // WHILE B-PTR NOT nullptr

          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr

} // INITIALIZE_Q_BODILESS_STACK


///////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////

void logic_program_class::initialize_Q_headless()
{

     vertex_class                  *v_ptr;
     vertex_ptr_class              *cur_appear;
     int                            tempval;
     vertex_class                  *tempvert;


//cout << "upon entry to initialize_Q_headless() queue is... \n";
//Q.print();

    // ENQUEUE ALL VARIABLES WITH NO HEAD APPEARANCES 
     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)  {
        if ((v_ptr->no_head_appearance()==1)) {
              tempval = v_ptr->get_value();    
              cur_appear = new vertex_ptr_class(tempval, v_ptr);
              Q.add_ptr(cur_appear);
         } // IF

         v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr

} // INITIALIZE_Q_HEADLESS

///////////////////////////////////////////////////////////////////////


void logic_program_class::initialize_Q_headless_stack()
{

     vertex_class                  *v_ptr;
     vertex_ptr_class              *cur_appear;
     int                            tempval;
     vertex_class                  *tempvert;
     int                            no_appear;


//cout << "upon entry to initialize_Q_headless_stack() queue is... \n";
//Q.print();


    // ENQUEUE ALL HEADS OF BODILESS RULES
     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
            no_appear = 0;  // INITIALIZE
            no_appear = v_ptr->no_head_appearance();

            if( no_appear == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.push(cur_appear);
             } // IF
          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr

} // INITIALIZE_Q_HEADLESS_STACK




void logic_program_class::initialize_Q_negatives()
{

     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     vertex_ptr_class              *cur_appear;
     int                            tempval;
     vertex_class                  *tempvert;

//cout << "upon entry to initialize_Q_negative() queue is... \n";
//Q.print();


    // ENQUEUE ALL VARIABLES THAT HAVE ONLY NEGATIVE SUBGOALS

     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         b_ptr = v_ptr->get_first_body();
         while (b_ptr != nullptr) {
            if( (b_ptr->has_only_negative_subgoals()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.add_ptr(cur_appear);
                  break;
             } // IF
            b_ptr = b_ptr->get_next_ptr();

          } // WHILE B-PTR NOT nullptr

          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr

} // INITIALIZE_Q_NEGATIVE



///////////////////////////////////////////////////////////////////////



void logic_program_class::initialize_Q_negatives_stack()
{

     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     vertex_ptr_class              *cur_appear;
     int                            tempval;
     vertex_class                  *tempvert;

//cout << "upon entry to initialize_Q_negative_stack() queue is... \n";
//Q.print();


    // ENQUEUE ALL VARIABLES THAT HAVE ONLY NEGATIVE SUBGOALS

     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         b_ptr = v_ptr->get_first_body();
         while (b_ptr != nullptr) {
            if( (b_ptr->has_only_negative_subgoals()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.push(cur_appear);
                  break;
             } // IF
            b_ptr = b_ptr->get_next_ptr();

          } // WHILE B-PTR NOT nullptr

          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr

} // INITIALIZE_Q_NEGATIVES_STACK





void logic_program_class::initialize_Q_positives()
{

     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     vertex_ptr_class              *cur_appear;
     int                            tempval;
     vertex_class                  *tempvert;


//cout << "upon entry to initialize_Q_positives() queue is... \n";
//Q.print();

    // ENQUEUE ALL VARIABLES THAT HAVE ANY NEGATIVE SUBGOALS

     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         b_ptr = v_ptr->get_first_body();
         while (b_ptr != nullptr) {
            if( (b_ptr->has_only_positive_subgoals()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.add_ptr(cur_appear);
                  break;
             } // IF
            b_ptr = b_ptr->get_next_ptr();

          } // WHILE B-PTR NOT nullptr

          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr

} // INITIALIZE_Q_POSITIVES_





void logic_program_class::initialize_Q_positives_stack()
{

     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     vertex_ptr_class              *cur_appear;
     int                            tempval;
     vertex_class                  *tempvert;


//cout << "upon entry to initialize_Q_positives() queue is... \n";
//Q.print();

    // ENQUEUE ALL VARIABLES THAT HAVE ANY NEGATIVE SUBGOALS

     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         b_ptr = v_ptr->get_first_body();
         while (b_ptr != nullptr) {
            if( (b_ptr->has_only_positive_subgoals()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.push(cur_appear);
                  break;
             } // IF
            b_ptr = b_ptr->get_next_ptr();

          } // WHILE B-PTR NOT nullptr

          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr

} // INITIALIZE_Q_POSITIVES_STACK

///////////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////////
void logic_program_class::get_WF_linear()
{

     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     rule_class                    *r_ptr;
     int                            lub_so_far;
     int                            b_val;
     vertex_ptr_class              *cur_appear;
     int                            old_J, old_W, new_J, new_W;
     int                            tempval;
     vertex_class                  *tempvert;
                 



//  initialize_Q_appearances();
    initialize_Q_only_neg_subgoals();

         
  while ( (Q.get_length()) > 0) {

         cur_appear = Q.dequeue();

         v_ptr = cur_appear->get_graphspot();

         delete cur_appear;

         // UPDATE J
         old_J = v_ptr->get_J_val();
         new_J = v_ptr->determine_new_J_val(this);
         if (old_J != new_J) {

                v_ptr->assign_J_val(new_J);

               ///  PROPOGATE THE CHANGE BY ENQUEUEING THE POSITIVE APPEARANCE LIST
                r_ptr = v_ptr->get_first_pos_appearance();
                while (r_ptr != nullptr) {
                   tempval = r_ptr->get_value();
                   tempvert = this->get_vertex_ptr(r_ptr);
                   cur_appear = new vertex_ptr_class(tempval, tempvert);
                   Q.add_ptr(cur_appear);
                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE

         } // IF
      
        // UPDATE W
        old_W = v_ptr->get_W_val();
        new_W = lub_k(old_W, new_J);

/////////////////////////////////////////////////////////
// C A U T I O N ! ! ! ! ! ! !   JUSTIFY THIS !!!!!!
/////////////////////////////////////////////////////////
          if ( new_W == 3 )
                new_W = new_J;

        if (old_W != new_W) {

           v_ptr->assign_W_val(new_W); 

          ///  PROPOGATE THE CHANGE BY ENQUEUEING THE NEGATIVE APPEARANCE LIST
           r_ptr = v_ptr->get_first_neg_appearance();

           while (r_ptr != nullptr) {
                tempval = r_ptr->get_value();
                tempvert = this->get_vertex_ptr(r_ptr);
                cur_appear = new vertex_ptr_class(tempval, tempvert);
                Q.add_ptr(cur_appear);
                r_ptr = r_ptr->get_next_ptr();
           } // WHILE

        } // IF

   } // WHILE


     Q.cleanup();

   final_scan_W_vals_Q();

// --------------------------------------------------------------------
//  BEGIN  SECOND   SCAN
//
//



  while ( (Q.get_length()) > 0) {

         cur_appear = Q.dequeue();

         v_ptr = cur_appear->get_graphspot();

         delete cur_appear;

         // UPDATE J
         old_J = v_ptr->get_J_val();
         new_J = v_ptr->determine_new_J_val(this);
         if (old_J != new_J) {

                v_ptr->assign_J_val(new_J);

               ///  PROPOGATE THE CHANGE BY ENQUEUEING THE POSITIVE APPEARANCE LIST
                r_ptr = v_ptr->get_first_pos_appearance();
                while (r_ptr != nullptr) {
                   tempval = r_ptr->get_value();
                   tempvert = this->get_vertex_ptr(r_ptr);
                   cur_appear = new vertex_ptr_class(tempval, tempvert);
                   Q.add_ptr(cur_appear);
                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE

         } // IF
      
        // UPDATE W
        old_W = v_ptr->get_W_val();
        new_W = lub_k(old_W, new_J);

/////////////////////////////////////////////////////////
// C A U T I O N ! ! ! ! ! ! !   JUSTIFY THIS !!!!!!
/////////////////////////////////////////////////////////
          if ( new_W == 3 )
                new_W = new_J;

        if (old_W != new_W) {

           v_ptr->assign_W_val(new_W); 

          ///  PROPOGATE THE CHANGE BY ENQUEUEING THE NEGATIVE APPEARANCE LIST
           r_ptr = v_ptr->get_first_neg_appearance();

           while (r_ptr != nullptr) {
                tempval = r_ptr->get_value();
                tempvert = this->get_vertex_ptr(r_ptr);
                cur_appear = new vertex_ptr_class(tempval, tempvert);
                Q.add_ptr(cur_appear);
                r_ptr = r_ptr->get_next_ptr();
           } // WHILE

        } // IF

   } // WHILE

// -------------------------------------------------------------------



   ////////////////////////////////////////////////
   //   Move W_vals to the "truth_val" field
   ////////////////////////////////////////////////
   transfer_W_to_truth();


} // GET_WF_LINEAR

//////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////
void logic_program_class::initialize_Q_all()
{

     vertex_class                  *v_ptr;
     vertex_ptr_class              *cur_appear;
     int                            tempval;
     vertex_class                  *tempvert;


     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
          tempval = v_ptr->get_value();    
          cur_appear = new vertex_ptr_class(tempval, v_ptr);
          Q.add_ptr(cur_appear);
          v_ptr = v_ptr->get_next_ptr();
     } // WHILE

} // INITIALIZE_Q



///////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////

void logic_program_class::initialize_Q_appearances()
{

     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     vertex_ptr_class              *cur_appear;
     int                            tempval;
     vertex_class                  *tempvert;


//cout << "upon entry to initialize_Q_appearnaces() queue is... \n";
//Q.print();

    // ENQUEUE ALL HEADS OF BODILESS RULES
     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         b_ptr = v_ptr->get_first_body();
         while (b_ptr != nullptr) {
            if( (b_ptr->is_bodiless_rule()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.add_ptr(cur_appear);
                  break;
             } // IF
            b_ptr = b_ptr->get_next_ptr();

          } // WHILE B-PTR NOT nullptr

          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr

//cout << "after heads_only() queue is... \n";
//Q.print();


    // ENQUEUE ALL VARIABLES THAT DO NOT APPEAR AS HEADS
     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         if( (v_ptr->no_head_appearance()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.add_ptr(cur_appear);
          } // IF
          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr

//cout << "after no_head_appearance() queue is... \n";
//Q.print();



    // ENQUEUE ALL VARIABLES THAT HAVE NEGATIVE APPEARANCES
     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         if( (v_ptr->has_negative_appearances()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.add_ptr(cur_appear);
          } // IF
          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr

//cout << "after neg_appearnaces() queue is... \n";
//Q.print();



    // ENQUEUE ALL VARIABLES THAT HAVE POSITIVE APPEARANCES
     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         if( (v_ptr->has_positive_appearances()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.add_ptr(cur_appear);
          } // IF
          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr

//cout << "after pos_appearnaces() queue is... \n";
//Q.print();


} // INITIALIZE_Q_APPEARANCES

  
//////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////

void logic_program_class::initialize_Q_only_neg_subgoals()
{

     vertex_class                  *v_ptr;
     body_node_class               *b_ptr;
     vertex_ptr_class              *cur_appear;
     int                            tempval;
     vertex_class                  *tempvert;


    // ENQUEUE ALL HEADS OF BODILESS RULES
     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         b_ptr = v_ptr->get_first_body();
         while (b_ptr != nullptr) {
            if( (b_ptr->is_bodiless_rule()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.add_ptr(cur_appear);
                  break;
             } // IF
            b_ptr = b_ptr->get_next_ptr();

          } // WHILE B-PTR NOT nullptr

          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr



    // ENQUEUE ALL VARIABLES THAT DO NOT APPEAR AS HEADS
     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         if( (v_ptr->no_head_appearance()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.add_ptr(cur_appear);
          } // IF
          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr


    // ENQUEUE ALL VARIABLES THAT HAVE ANY NEGATIVE SUBGOALS

     v_ptr = Vertexlist.get_first();

     while (v_ptr != nullptr)   {
         b_ptr = v_ptr->get_first_body();
         while (b_ptr != nullptr) {
            if( (b_ptr->has_only_negative_subgoals()) == 1) {
                  tempval = v_ptr->get_value();    
                  cur_appear = new vertex_ptr_class(tempval, v_ptr);
                  Q.add_ptr(cur_appear);
                  break;
             } // IF
            b_ptr = b_ptr->get_next_ptr();

          } // WHILE B-PTR NOT nullptr

          v_ptr = v_ptr->get_next_ptr();
     } // WHILE  V-PTR NOT nullptr



} // INITIALIZE_Q_ONLY_NEG_SUBGOALS

//////////////////////////////////////////////////////////////////////


void logic_program_class::final_scan_W_vals_Q()
{
     vertex_class     *v_ptr;
     vertex_ptr_class *cur_appear;
     vertex_class     *tempvert;
     rule_class       *r_ptr;
     int               tempval;
     int               current_J;
     int               current_W;
     int               new_W_val;

     v_ptr = Vertexlist.get_first();
     while (v_ptr != nullptr) {
          current_J = v_ptr->get_J_val();
          current_W = v_ptr->get_W_val(); 

          if (current_J != current_W) {
               new_W_val = lub_k(current_J, current_W);
               v_ptr->assign_W_val(new_W_val); 

          ///  PROPOGATE THE CHANGE BY ENQUEUEING THE NEGATIVE APPEARANCE LIST
           r_ptr = v_ptr->get_first_neg_appearance();

           while (r_ptr != nullptr) {
                tempval = r_ptr->get_value();
                tempvert = this->get_vertex_ptr(r_ptr);
                cur_appear = new vertex_ptr_class(tempval, tempvert);
                Q.add_ptr(cur_appear);
                r_ptr = r_ptr->get_next_ptr();
           } // WHILE

          } // IF

          v_ptr = v_ptr->get_next_ptr();
     } // WHILE
}


////////////////////////////////////////////////////////////////////////
///  F A C T O R   O U T
///////////////////////////////////////////////////////////////////////

logic_program_class *logic_program_class::factor_out()
{
   
    logic_program_class  *F;

    vertex_class           *v_ptr, *new_v_ptr;
    body_node_class        *b_ptr, *new_b_ptr;
    literal_class          *l_ptr, *new_l_ptr;
    rule_class             *r_ptr, *new_r_ptr;
    int                    head;
    int                    temp_truth;
    int                    body_val;
    int                    lit_truth_val;
    int                    lit_val;
  
   F = new logic_program_class();


   //  TRAVERSE THE GRAPH AND COPY THOSE NODES OF VALUE BOTTOM (2)

   v_ptr = Vertexlist.get_first();
   while (v_ptr != nullptr) {
      
      temp_truth = v_ptr->get_truth();

      if (temp_truth == 2) {
           head = v_ptr->get_value();
           new_v_ptr = F->find_add_vertex(head);

//cout << "\n \n \n just added vertex to FACTOR.  FACTOR is now... \n \n \n";
//F->output_graph();


         // ATTACH BOTTOM BODIES TO NEW VERTEX 
           b_ptr = v_ptr->get_first_body();
        
           while (b_ptr != nullptr) {
              body_val = b_ptr->get_value();
              if (body_val == 2) {
                 new_b_ptr = new body_node_class();
                 
                 // ATTACH BOTTOM POSITIVE SUBGOALS
                 l_ptr = b_ptr->get_first_pos_lit_ptr();
                 while (l_ptr != nullptr) {
                     lit_truth_val = get_lit_truth(l_ptr);
                     if (lit_truth_val == 2) {
                          lit_val = l_ptr->get_value();   
                          new_l_ptr = new literal_class(lit_val);
                          new_b_ptr->add_pos_literal(new_l_ptr); 
                     } // IF
                     l_ptr = l_ptr->get_next_ptr();
                 } // WHILE

                 // ATTACH BOTTOM NEGATIVE SUBGOALS
                 l_ptr = b_ptr->get_first_neg_lit_ptr();
                 while (l_ptr != nullptr) {
                     lit_truth_val = get_lit_truth(l_ptr);
                     if (lit_truth_val == 2) {
                          lit_val = l_ptr->get_value();   
                          new_l_ptr = new literal_class(lit_val);
                          new_b_ptr->add_neg_literal(new_l_ptr); 
                     } // IF
                     l_ptr = l_ptr->get_next_ptr();
                 } // WHILE
                
                 // ATTACH NEWLY CREATED BODY TO NEW VERTEX
                 new_v_ptr->add_body(new_b_ptr);

                 // ATTACH OUTGOING EDGES DEFINED BY THIS BODY
                 F->add_subgoals_outgoing_edge_pieces(head, new_v_ptr, new_b_ptr);

               } // IF BODY IS BOTTOM
             b_ptr = b_ptr->get_next_ptr();

           } // WHILE b_ptr != nullptr

      } // IF v_ptr POINTS TO A BOTTOM VERTEX   


      v_ptr = v_ptr->get_next_ptr();


   } // WHILE v_ptr != nullptr

   return F;
}


////////////////////////////////////////////////////////////////////////////
///  COMPUTE POSTORDER NUMS  performs a Depth First Forest on the
///  graph.  In the outer loop, each vertex is examined exactly once.
///             if node has been visited, continue to the next
///             else
///                  perform a dfs starting from this unvisited node
///
///
///  The dfs(v) is an interative implementation using the following psuedocode:
///   
///             mark(v)
///             push(v)
///             while stack not empty DO
///                  if all adjacents to TOS have been marked then
///                        u := POP Stack
///                        assign u the next postorder value (global:
///                               Currnet_Postorder_Val)
///                  else
///                        choose one unmarked neighbor to TOS, w
///                        mark(w)
///                        push(w)
///                  endif
///       
///////////////////////////////////////////////////////////////////////////

void logic_program_class::compute_postorder_nums()
{

     vertex_class                  *v_ptr, *top_v_ptr;
     body_node_class               *b_ptr;
     rule_class                    *r_ptr;
     int                            lub_so_far;
     int                            b_val;
     vertex_ptr_class              *cur_node, *cur_top, *cur_appear;
     int                            old_J, old_W, new_J, new_W;
     int                            tempval;
     vertex_class                  *tempvert;
                 

  Current_Postorder_Val = 1;

  v_ptr = Vertexlist.get_first();

  while (v_ptr != nullptr) {

     /////////////////////////////////////////////////////////
     // if node is not marked, perform iterative dfs on this node
     /////////////////////////////////////////////////////////

     if (!v_ptr->visited()) {
            v_ptr->mark(); 
            // ________________________
            // push this node onto stack
            // ------------------------
            tempval = v_ptr->get_value();
            cur_node = new vertex_ptr_class(tempval, v_ptr);
            Stack.push(cur_node);
            // ----------------------------------------------------------
            // perform dfs on the current nonempty stack..corresponding
            // to the current connected component of the graph
            // ----------------------------------------------------------
           while ( (Stack.get_length()) > 0) {
                 cur_top = Stack.stack_top();
                 top_v_ptr = cur_top->get_graphspot();

                 //___________________________________________________
                 // Determine if _any_ of top_v_ptr's neighbors are
                 // unmarked.  If so, perform dfs on one of them.
                 // Implementationwise:  traverse the appearance lists
                 // and choose the first unmarked appearance.
                 // --------------------------------------------------

                r_ptr = top_v_ptr->get_first_pos_appearance();
                while (r_ptr != nullptr) {
                   tempvert = this->get_vertex_ptr(r_ptr);
                   if (tempvert->visited()==0) {
                         tempvert->mark();
                         tempval = tempvert->get_value();
                         cur_appear = new vertex_ptr_class(tempval, tempvert);
                         Stack.push(cur_appear);
                         break;       
                   }  //IF
                   else {
                        r_ptr = r_ptr->get_next_ptr();
                   } // ELSE
                } // WHILE 

                //-------------------------------------------------------
                // if r_ptr is nullptr then there was no unmarked neighbor
                // in the positive appearance list.  Now check the negative
                // appearance list.
                //-------------------------------------------------------
                if (r_ptr == nullptr) {
                    r_ptr = top_v_ptr->get_first_neg_appearance();
                    while (r_ptr != nullptr) {
                       tempvert = this->get_vertex_ptr(r_ptr);
                       if (tempvert->visited()==0) {
                          tempvert->mark();
                          tempval = tempvert->get_value();
                          cur_appear = new vertex_ptr_class(tempval, tempvert);
                          Stack.push(cur_appear);
                          break;       
                        }  //IF
                       else {
                          r_ptr = r_ptr->get_next_ptr();
                        } // ELSE
                     } // WHILE
                } // IF r_ptr nullptr

                //-------------------------------------------------------
                // if r_ptr is nullptr then there was no unmarked neighbor,
                // so top_v_ptr should be POPPED.
                //-------------------------------------------------------
                if (r_ptr==nullptr) {
                     top_v_ptr->assign_postorder_num(Current_Postorder_Val);
                     Current_Postorder_Val++;
                     cur_top = Stack.pop(); // remove TOS
                     delete(cur_top);
                } // IF
             } // WHILE STACK NOT EMPTY

        } // IF NODE NOT YET VISITED
                       
      v_ptr = v_ptr->get_next_ptr();
      } // WHILE v_ptr NOT nullptr
} // compute_postorder_nums



//////////////////////////////////////////////////////////////////////////////
///  Traverses the graph locating the specified literal's vertex.
///  This returns that vertex's truth  value.
//////////////////////////////////////////////////////////////////////////////

int logic_program_class::get_lit_truth(literal_class *l_ptr)
{
     vertex_class   *v_ptr;

     v_ptr = get_lit_vertex(l_ptr);

     return (v_ptr->get_truth());
} // GET_LIT_TRUTH






//////////////////////////////////////////////////////////////////////////////
///  This returns a pointer to the first vertex in the logic program graph
//////////////////////////////////////////////////////////////////////////////

vertex_class *logic_program_class::get_first_vertex()
{
    return (Vertexlist.get_first());

} // GET_FIRST_VERTEX



///////////////////////////////////////////////////////////////////
///  Retains all rule values (heads and subgoals) but
///  reinitializes all MODEL pertinent information.
///////////////////////////////////////////////////////////////////
void logic_program_class::reinitialize_graph_for_spantree()
{
    vertex_class       *v_ptr;
    body_node_class    *b_ptr;


    v_ptr = Vertexlist.get_first();
    while (v_ptr != nullptr) {
           // RESET VERTEX FIELDS OF TRUTH_VAl, ACCESS, AND GUESS
           v_ptr->assign_truth(2);    // 2 means BOTTOM
           v_ptr->assign_W_val(2);    // 2 means BOTTOM
           v_ptr->assign_J_val(2);    // 2 means BOTTOM 
           v_ptr->assign_access(0);   // 0 means FALSE
           v_ptr->assign_guess(0);
           v_ptr->assign_postorder_num(0);

           // INITIALIZE BODYLIST
           b_ptr = v_ptr->get_first_body();

           while (b_ptr != nullptr) {
                  b_ptr->set_body_status(2);  // 2 means UNDETERMINED..BOTTOM
                  b_ptr->set_pos_assess(1);   // 1 means TRUE.. init min to max
                  b_ptr->set_neg_assess(1);   //  (same)

                  b_ptr = b_ptr->get_next_ptr();

            } // WHILE THERE ARE MORE BODIES

       v_ptr = v_ptr->get_next_ptr();
    }// WHILE  STILL MORE VERTICES IN THE LIST

} // REINITIALIZE_GRAPH_FOR_SPANTREE

          



//////////////////////////////////////////////////////////////////////////////
///  FOR UNI-PROGRAMS!!!!!!!  (This algorithm is for Uni-Rule Programs!)
///
///  Creates a spanning tree of truth assignments with
///  vertex v_ptr assigned start_val as the spanning tree root.
///
///  The Algorithm:
///          assign root
///          enqueue root
///   ??     assign, evaluate, and enqueue all incoming neighbors to root
///   ??     assign, evaluate, and enqueue all outgoing neighbors to root
///            
///          While Q not empty do
///               current := dequeue
///               assign current
///               assign, evaluate, and enqueue all incoming neighbors to current
///               assign, evaluate, and enqueue all outgoing neighbors to current
///
//////////////////////////////////////////////////////////////////////////////

spantree_class *logic_program_class::grow_spanning_tree(vertex_class *root_v_ptr, int start_val)
{
     int              there_exists_conflict;
     spantree_class   *s_ptr;
     int               temp_vval;
     int               neighbor_val;
     int               neighbor_truth_val;
     int               neighbor_b_truth;
     int               eval_without_neighbor_change,
                       eval_with_neighbor_change;
     vertex_class     *neighbor_v_ptr,
                      *current_v_ptr;
     int               current_truthval;
     int               current_val;
     int               current_b_truth;    // used in cases 6 and 7
     body_node_class  *neighbor_b_ptr, *current_b_ptr;
     literal_class    *l_ptr;
     rule_class       *r_ptr;
     vertex_ptr_class *cur_enqueue, *cur_dequeue;
     int               n_trues, n_falses, n_bottoms, n_tops;
     int               conflict_node;


     // INITIALIZE
     there_exists_conflict = 0;
     conflict_node = -99;
     this->reinitialize_graph_for_spantree(); 

// ---------------------------
//cout << "after REINIT the graph is..\n";
//this->output_graph();
//---------------------------------
     temp_vval  = root_v_ptr->get_value();
     s_ptr = new spantree_class(temp_vval, start_val);


     
     // ................................................................... 
     //
     // EXPAND TREE THRU PROGRAM GRAPH AND DETERMINE SPANNING TREE STATUS

     /* Assign Root */
     root_v_ptr->assign_truth(start_val);
     root_v_ptr->assign_J_val(start_val);
     root_v_ptr->assign_W_val(start_val);


     /* Enqueue Root */
     cur_enqueue = new vertex_ptr_class(temp_vval, root_v_ptr);
     Q.add_ptr(cur_enqueue);   

     /////////////////////////////
     /*  While Q not Empty:
              assign, evaluate, and enqueue all neighbors to Q.FRONT
     */
     ////////////////////////////
//8888888888888888888888888888888888888888888888888888888


 while (( (Q.get_length()) > 0)  && (!there_exists_conflict)){

      cur_dequeue = Q.dequeue();

      current_v_ptr = cur_dequeue->get_graphspot();
      delete cur_dequeue;
      current_truthval = current_v_ptr->get_truth();
      current_val = current_v_ptr->get_value();
   
      // IF CURRENT NODE IS TRUE, ASSIGN/FORCE  EVERY INCOMING NEIGHBOR
     if (current_truthval == 1) {  // CURRENT NODE IS TRUE

         // CASE 1:  True node...incoming positives
         // Handle neighbors of INCOMING POSITIVE edges...
            current_b_ptr = current_v_ptr->get_first_body();
            l_ptr = current_b_ptr->get_first_pos_lit_ptr();
            while (l_ptr != nullptr) {

//cout << "Inside Case 1 " << endl;
//cout << "The Q is...." << endl;
//Q.print();

                      neighbor_val = l_ptr->get_value();
                      neighbor_v_ptr = get_lit_vertex(l_ptr);
                      neighbor_truth_val = neighbor_v_ptr->get_truth();

                      // CHECK FOR CONFLICT
                      if (neighbor_truth_val == 0) {
                              there_exists_conflict = 1 ;
//cout << "CONFLICT in Case 1 \n";
                              conflict_node = neighbor_val;
                              break;
                      } // IF

                      // IF BOTTOM.. ASSIGN and ENQUEUE
                      else if  (neighbor_truth_val == 2)  {
                             neighbor_v_ptr->assign_truth(1); // ASSIGN TRUE
                             neighbor_v_ptr->assign_J_val(1); // ASSIGN TRUE
                             neighbor_v_ptr->assign_W_val(1); // ASSIGN TRUE
                             
                             cur_enqueue = new vertex_ptr_class(neighbor_val, neighbor_v_ptr);
                             Q.add_ptr(cur_enqueue);   
                      } //ELSE IF

                      else {  // DO NOTHING... IT WAS ALREADY TRUE
                      } //ELSE

                     l_ptr = l_ptr->get_next_ptr();
            }// WHILE more positive incoming neighbors




           // CASE 2:  True node...incoming negatives
           // Handle neighbors of INCOMING NEGATIVE edges...

//cout << "Inside Case 2 " << endl;
//cout << "The Q is...." << endl;
//Q.print();


            l_ptr = current_b_ptr->get_first_neg_lit_ptr();
            while (l_ptr != nullptr) {
                      neighbor_val = l_ptr->get_value();
                      neighbor_v_ptr = get_lit_vertex(l_ptr);
                      neighbor_truth_val = neighbor_v_ptr->get_truth();

                      // CHECK FOR CONFLICT
                      if (neighbor_truth_val == 1) {
                              there_exists_conflict = 1 ;
//cout << "CONFLICT IN CASE 2 \n";
                              conflict_node = neighbor_val;

                              break;
                      } // IF

                      // IF BOTTOM.. ASSIGN and ENQUEUE
                      else if  (neighbor_truth_val == 2)  {
                             neighbor_v_ptr->assign_truth(0); // ASSIGN FALSE
                             neighbor_v_ptr->assign_J_val(0); 
                             neighbor_v_ptr->assign_W_val(0); 

                             cur_enqueue = new vertex_ptr_class(neighbor_val, neighbor_v_ptr);
                             Q.add_ptr(cur_enqueue);   

                      } //ELSE IF

                      else {  // DO NOTHING... IT WAS ALREADY FALSE
                      } //ELSE

                     l_ptr = l_ptr->get_next_ptr();
             }// WHILE more negative incoming neighbors




             // CASE 3:  True node...outgoing negatives
             //Handle neighbors of NEGATIVE OUTGOING edges

//cout << "Inside Case 3 " << endl;
//cout << "The Q is...." << endl;
//Q.print();


                r_ptr = current_v_ptr->get_first_neg_appearance();
                while (r_ptr != nullptr) {
                   neighbor_val = r_ptr->get_value();
                   neighbor_v_ptr = this->get_vertex_ptr(r_ptr);
                   neighbor_truth_val = neighbor_v_ptr->get_truth();

                   // CHECK FOR CONFLICT
                   if (neighbor_truth_val == 1) {
                           there_exists_conflict = 1 ;
//cout << "CONFLICT in Case 3 \n";
                              conflict_node = neighbor_val;

                           break;
                   } // IF

                   // IF BOTTOM.. ASSIGN and ENQUEUE
                   else if  (neighbor_truth_val == 2)  {
                          neighbor_v_ptr->assign_truth(0); // ASSIGN FALSE
                          neighbor_v_ptr->assign_J_val(0); 
                          neighbor_v_ptr->assign_W_val(0); 

                          cur_enqueue = new vertex_ptr_class(neighbor_val, neighbor_v_ptr);
                          Q.add_ptr(cur_enqueue);   

                   } //ELSE IF

                   else {  // DO NOTHING... IT WAS ALREADY FALSE
                   } //ELSE

                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE more negative OUTGOING edges



               // CASE 4:  True Node...Outgoing Positives..EVALUATION REQUIRED
               // ***********************************************************
               //  Check to see if destination vertices of POSITIVE OUTGOING
               //   can be assigned..EVALUATE THESE DEST VERTICES
               // ***********************************************************
              
//DD
//cout << "Inside CASE 4...............\n";
//cout << "The Q is...." << endl;
//Q.print();

                r_ptr = current_v_ptr->get_first_pos_appearance();
                while (r_ptr != nullptr) {
                   neighbor_val = r_ptr->get_value();
                   neighbor_v_ptr = this->get_vertex_ptr(r_ptr);
                   neighbor_truth_val = neighbor_v_ptr->get_truth();

                   // IF BOTTOM.. EVALUATE, POSSIBLY ASSIGN and ENQUEUE
                  if  (neighbor_truth_val == 2)  {
                          neighbor_b_truth = -99;          // INITIALIZE
                          neighbor_b_ptr = neighbor_v_ptr->get_first_body(); 

                          // Compute new truth value of neighbor
//D
//cout << "current node is............" << endl;
//current_v_ptr->output();
//cout << "neighbor being examined is...............\n";
//neighbor_v_ptr->output();
                          neighbor_b_ptr->determine_pos_assess(this); 
                          neighbor_b_ptr->determine_neg_assess(this); 
                          neighbor_b_truth =  neighbor_b_ptr->determine_body_status();
                          if (neighbor_b_truth != 2) { // PERFORM NEW TRUTH ASSIGNMENT!!
                                 neighbor_v_ptr->assign_truth(neighbor_b_truth); // ASSIGN FALSE
                                 neighbor_v_ptr->assign_J_val(neighbor_b_truth); 
                                 neighbor_v_ptr->assign_W_val(neighbor_b_truth); 

                                 cur_enqueue = new vertex_ptr_class(neighbor_val, neighbor_v_ptr);
                                 Q.add_ptr(cur_enqueue);      

                          } // IF able to assign dest T or F to neighbor
                   } // IF dest vertex is BOTTOM

                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE more positive OUTGOING edges

        }  // IF current node on QUEUE is TRUE
        else  {     // current node on QUEUE is FALSE
             
             //CASE 5...False node...outgoing positives JUST FORCE
             //****************************************************
             //Handle neighbors of POSITIVE OUTGOING edges
             //****************************************************

//cout << "inside case 5 " << endl;
//cout << "The Q is...." << endl;
//Q.print();

                r_ptr = current_v_ptr->get_first_pos_appearance();
                while (r_ptr != nullptr) {
                   neighbor_val = r_ptr->get_value();
//cout << "neighbor val is.." << neighbor_val << endl;
                   neighbor_v_ptr = this->get_vertex_ptr(r_ptr);
//cout << "neighbor vertex is...." << endl;

                   neighbor_truth_val = neighbor_v_ptr->get_truth();

                   // CHECK FOR CONFLICT
                   if (neighbor_truth_val == 1) {
                           there_exists_conflict = 1 ;
//cout << "CONFLICT in Case 5 \n";
                              conflict_node = neighbor_val;

                           break;
                   } // IF

                   // IF BOTTOM.. ASSIGN and ENQUEUE
                   else if  (neighbor_truth_val == 2)  {
                          neighbor_v_ptr->assign_truth(0); // ASSIGN FALSE
                          neighbor_v_ptr->assign_J_val(0); 
                          neighbor_v_ptr->assign_W_val(0); 

                          cur_enqueue = new vertex_ptr_class(neighbor_val, neighbor_v_ptr);
                          Q.add_ptr(cur_enqueue);   

                   } //ELSE IF

                   else {  // DO NOTHING... IT WAS ALREADY FALSE
                   } //ELSE

                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE more positive OUTGOING edges from FALSE current


        // ***********************************************************
        //  CASES 6 and 7...False node:  Incoming negatives and positives
        //    EVALUATION required
        // ***********************************************************
        //  Check to see if one origin vertex of POSITIVE INCOMING  edges
        //   can be assigned..EVALUATE CURRENT WITH and WITHOUT ASSIGNMENT
        // ***********************************************************

         // For each incoming edge, Examine evaluation of Current with a 
         // changed origin source neighbor and an unchanged origin source
         // neighbor


         // check to see if evaluation of Current is different 
         //  than FORCED assignment  of Current

//DD
//  cout << "inside case 6" << endl;
//cout << "The Q is...." << endl;
//Q.print();


//cout << "CURRENT IS...." << endl;
//current_v_ptr->output();


            current_b_truth = -99;          // INITIALIZE
            current_b_ptr = current_v_ptr->get_first_body(); 
            current_b_ptr->determine_pos_assess(this); 
            current_b_ptr->determine_neg_assess(this); 
            current_b_truth =  current_b_ptr->determine_body_status();

//DD
//cout << "WITHOUT assigning incoming neighbors...." << endl;
//cout << "current_b_truth evaluates to " << current_b_truth << endl;

                          
            if (current_b_truth == 0) {
               
            } //IF already evaluates to FALSE

            // Rule out CONFLICT..that is, if current evaluates to TRUE!
            else if (current_b_truth == 1) {
                     there_exists_conflict = 1;
//cout << "CONFLICT in Case 6 and 7 \n";
                      conflict_node = neighbor_val;

                     break;
            } //IF  current evaluated to TRUE (when it was FORCED FALSE)


            // If Bottom...check to see if all other incoming neighbors are
            //   TRUE;  if so, force this neighbor FALSE
            //   possibly assigning one origin vertex FALSE 
            //     will cause current to evaluate to False

            else if (current_b_truth == 2) {
//DD
//cout << "INSIDE ELSE...current_b_truth is BOTTOM." << endl;

               l_ptr = current_b_ptr->get_first_pos_lit_ptr();

               while (l_ptr != nullptr) {
//DD
//cout << "The literal being examined ..incoming pos edge is..." << endl;
//l_ptr->output();
                  neighbor_val = l_ptr->get_value();
                  neighbor_v_ptr = get_lit_vertex(l_ptr);
                  neighbor_truth_val = neighbor_v_ptr->get_truth();
//DD
//cout << "The vertex associated with the literal being examined " << endl;
//neighbor_v_ptr->output();

                  // Temporarily assign neighbor TRUE  to see if any difference
                   neighbor_v_ptr->assign_J_val(1);
//DD
//cout << "After assigning its J-Val TRUE , the vertex of incoming positive " << endl;
//neighbor_v_ptr->output();

                   current_b_ptr->determine_pos_assess(this);   
//cout << "after   current_b_ptr->determine_pos_assess(this)  body is...\n";
//current_b_ptr->output();
                   current_b_ptr->determine_neg_assess(this);
//cout << "after   current_b_ptr->determine_neg_assess(this)  body is...\n";
//current_b_ptr->output();

                   current_b_truth = current_b_ptr->determine_body_status();         
//cout << "after determine_body_status...body is....\n";
//current_b_ptr->output();
//cout << "current_b_truth is..." << current_b_truth << endl;

                   
                   if (current_b_truth == 1) // this neighbor will force it FALSE
                   {
                         neighbor_v_ptr->assign_truth(0);
                         neighbor_v_ptr->assign_J_val(0);
                         neighbor_v_ptr->assign_W_val(0);

                         // Enqueue
                          cur_enqueue = new vertex_ptr_class(neighbor_val, neighbor_v_ptr);
                          Q.add_ptr(cur_enqueue);   

                   } //IF
                   else // Unassign
                   {
                         neighbor_v_ptr->assign_J_val(2);
                   } //ELSE

                   l_ptr = l_ptr->get_next_ptr();  
               } // WHILE no more positive incoming edges


              // Test and substitute incoming negative edges
              l_ptr = current_b_ptr->get_first_neg_lit_ptr();
//cout << "Inside case 7" << endl;
//cout << "The Q is...." << endl;
//Q.print();


              while (l_ptr != nullptr) {
                  neighbor_val = l_ptr->get_value();
                  neighbor_v_ptr = get_lit_vertex(l_ptr);
                  neighbor_truth_val = neighbor_v_ptr->get_truth();

                  // Temporarily assign neighbor TRUE  (since it's a neg
                  //   edge, we assign its atom FALSE)to see if any difference

                   neighbor_v_ptr->assign_W_val(0);
                   current_b_ptr->determine_neg_assess(this);   
                   current_b_truth = current_b_ptr->determine_body_status();         
                   
                   if (current_b_truth == 1)
                   {
                         neighbor_v_ptr->assign_truth(1);
                         neighbor_v_ptr->assign_W_val(1);
                         neighbor_v_ptr->assign_J_val(1);

                         // Enqueue
                          cur_enqueue = new vertex_ptr_class(neighbor_val, neighbor_v_ptr);
                          Q.add_ptr(cur_enqueue);   
                   }
                   else
                   {
                         neighbor_v_ptr->assign_W_val(2);
                   }

                   l_ptr = l_ptr->get_next_ptr();  
               } // WHILE no more negative incoming edges

            }// ELSE IF current_b_truth is BOTTOM   


             //***********************************************************
             //   C A S E   8  :   FALSE NODE...check outgoing negative edges
             //      Requires evaluation
             //***********************************************************
             //  Check to see if destination vertices of NEGATIVE OUTGOINGS
             //   can be assigned..EVALUATE THESE DEST VERTICES
             // ***********************************************************
              
//cout << "inside case 8" << endl;
//cout << "The Q is...." << endl;
//Q.print();

                r_ptr = current_v_ptr->get_first_neg_appearance();
                while (r_ptr != nullptr) {
                   neighbor_val = r_ptr->get_value();
                   neighbor_v_ptr = this->get_vertex_ptr(r_ptr);
                   neighbor_truth_val = neighbor_v_ptr->get_truth();

                   // IF BOTTOM.. EVALUATE, POSSIBLY ASSIGN and ENQUEUE
                  if  (neighbor_truth_val == 2)  {
                          neighbor_b_truth = -99;          // INITIALIZE
                          neighbor_b_ptr = neighbor_v_ptr->get_first_body(); 
                          neighbor_b_ptr->determine_pos_assess(this); 
                          neighbor_b_ptr->determine_neg_assess(this); 
                          neighbor_b_truth =  neighbor_b_ptr->determine_body_status();
                          if (neighbor_b_truth != 2) { // PERFORM NEW TRUTH ASSIGNMENT!!
                                 neighbor_v_ptr->assign_truth(neighbor_b_truth); // ASSIGN FALSE
                                 neighbor_v_ptr->assign_J_val(neighbor_b_truth); 
                                 neighbor_v_ptr->assign_W_val(neighbor_b_truth); 

                                 cur_enqueue = new vertex_ptr_class(neighbor_val, neighbor_v_ptr);
                                 Q.add_ptr(cur_enqueue);      

                          } // IF
                   } // IF dest vertex is BOTTOM

                   r_ptr = r_ptr->get_next_ptr();
                } // WHILE more positive OUTGOING edges


        } // ELSE (current_truthval  is FALSE)

    }//WHILE Q not Empty

   /////////////////////////////////////////////////////////////////////////
   //      Determine Status of Tree
   ////////////////////////////////////////////////////////////////////////

   if (there_exists_conflict) {
          s_ptr->assign_status(4);
          s_ptr->assign_conflict_val(conflict_node);
   } // IF..Conflict
   else if ((total(&n_trues, &n_falses, &n_bottoms, &n_tops))==1)    {
          s_ptr->assign_status(1);
   } // ELSE IF...Total assignment
   else // Non-total assignment..determine whether or not both edge types exist
     {
         logic_program_class           *Temp_F;

         Temp_F = factor_out();
//DD
//cout << "the new factor of spanning tree is....\n";
//Temp_F->display_head_groups();


       // BOTH POS AND NEG
       if (((Temp_F->any_negative_lits()) == 1) && ((Temp_F->any_positive_lits()) == 1))
                s_ptr->assign_status(0);
       // ONLY NEG
       else if (((Temp_F->any_negative_lits()) == 1) && ((Temp_F->any_positive_lits()) == 0))
                s_ptr->assign_status(3);
       // ONLY POS 
       else if (((Temp_F->any_negative_lits()) == 0) && ((Temp_F->any_positive_lits()) == 1))
                s_ptr->assign_status(2);


        delete Temp_F;
      }// ELSE...Nontotal assignment
        
     return s_ptr;
} // GROW_SPANNING_TREE


/////////////////////////////////////////////////////////////////////
//   any_positive_lits ... returns 1 if there are more than zero 
//      positive literals in the logic program
////////////////////////////////////////////////////////////////////

int logic_program_class::any_positive_lits()
{

     vertex_class         *v_ptr;
     body_node_class      *b_ptr;
     literal_class        *l_ptr;
     int                  pos_lits_flag;

     pos_lits_flag = 0;                // Initialize to FALSE
     v_ptr = Vertexlist.get_first();
     while ((v_ptr != nullptr) && (pos_lits_flag == 0)) {
         b_ptr = v_ptr->get_first_body();
         while ((b_ptr != nullptr) && (pos_lits_flag == 0)) {
            if (b_ptr->has_any_positive_subgoals() == 1) {
                 pos_lits_flag = 1;
            } //IF
            else {
                 b_ptr = b_ptr->get_next_ptr();
            }//ELSE
         } // WHILE more bodies in bodylist

         v_ptr = v_ptr->get_next_ptr();

     }// WHILE more vertices in Vertexlist

} // ANY_POSITIVE_LITERALS 

/////////////////////////////////////////////////////////////////////
//   any_negative_lits ... returns 1 if there are more than zero 
//      negative literals in the logic program
////////////////////////////////////////////////////////////////////

int logic_program_class::any_negative_lits()
{

     vertex_class         *v_ptr;
     body_node_class      *b_ptr;
     literal_class        *l_ptr;
     int                  neg_lits_flag;

     neg_lits_flag = 0;                // Initialize to FALSE
     v_ptr = Vertexlist.get_first();
     while ((v_ptr != nullptr) && (neg_lits_flag == 0)) {
         b_ptr = v_ptr->get_first_body();
         while ((b_ptr != nullptr) && (neg_lits_flag == 0)) {
            if (b_ptr->has_any_negative_subgoals() == 1) {
                 neg_lits_flag = 1;
            } //IF
            else {
                 b_ptr = b_ptr->get_next_ptr();
            }//ELSE
         } // WHILE more bodies in bodylist

         v_ptr = v_ptr->get_next_ptr();

     }// WHILE more vertices in Vertexlist

} // ANY_NEGATIVE_LITERALS 



/////////////////////////////////////////////////////////////////////
//   form all spanning trees and attach to THIS spantree list    
//      1.  Form Factor
//      2.  With each vertex of Factor...form a tree
//      3.  Attach the spantree object to THIS spantree list
////////////////////////////////////////////////////////////////////


void logic_program_class::form_all_spanning_trees()
{

     spantree_class  *S_Tree;
     logic_program_class   *F;
     vertex_class         *Temp_vertex_pointer;


     F = this->factor_out();
     cout << endl << endl;
     cout << "FACTOR GRAPH:  GRAPH ON WHICH SPANNING TREES ARE BUILT: \n";
     F->display_head_groups();

     Temp_vertex_pointer = F->get_first_vertex();

     while (Temp_vertex_pointer != nullptr) {
               S_Tree = F->grow_spanning_tree(Temp_vertex_pointer, 1);
               this->add_spantree(S_Tree);
               S_Tree = F->grow_spanning_tree(Temp_vertex_pointer, 0);
               this->add_spantree(S_Tree);
               Temp_vertex_pointer = Temp_vertex_pointer->get_next_ptr();
     }//WHILE
     
     delete F;


} // FORM_ALL_SPANNING_TREES
