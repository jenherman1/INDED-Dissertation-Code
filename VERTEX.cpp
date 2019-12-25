#include <iostream>

#include "UTILITY1.H"
#include "VERTEX.H"

using namespace std;

/////////////////////////////////////////////////////////////////////
///      Constructors
/////////////////////////////////////////////////////////////////////

vertex_class::vertex_class()
   { 
      vnextnode = nullptr;
      truth_val = BOTTOM
       J_val = FALSE
       W_val = BOTTOM
       guess = 0;
       access = 0;
       postorder_num = 0;
   }
vertex_class::vertex_class(int n)
   {
       val = n;
       vnextnode = nullptr;
       truth_val = BOTTOM
       J_val = FALSE
       W_val = BOTTOM
       guess = 0;
       access = 0;
       postorder_num = 0;
   }

vertex_class::vertex_class(char f_str[LONG_STRING_LENGTH], int num)
   {
       char   tempstr[LONG_STRING_LENGTH];

       val = num;
       vnextnode = nullptr;
       truth_val = BOTTOM
       J_val = FALSE
       W_val = BOTTOM
       guess = 0;
       access = 0;
       postorder_num = 0;

       strcpy(tempstr, f_str);
       atominfo = new atom_class(); //Issue 1: TODO memory leak
       atominfo->assign_atom_info(tempstr, num);
   }
vertex_class::vertex_class(char f_str[LONG_STRING_LENGTH], int num, 
                          int is_negative_val)
   {
       char   tempstr[LONG_STRING_LENGTH];

       val = num;
       vnextnode = nullptr;
       truth_val = BOTTOM
       J_val = FALSE
       W_val = BOTTOM
       guess = 0;
       access = 0;
       postorder_num = 0;

       strcpy(tempstr, f_str);
       atominfo = new atom_class(); //Issue 1: TODO memory leak
       atominfo->assign_atom_info(tempstr, num, is_negative_val);
   }

int vertex_class::get_value(){
    return val;
}

////////////////////////////////////////////////////////////////////////////
///  Virtuals associated with NODE_CLASS
//////////////////////////////////////////////////////////////////////////

void vertex_class::assign_val(int n)
  {
    val = n;
  }

void vertex_class::assign_atominfo(char full_s[LONG_STRING_LENGTH])
  {
          atominfo = new atom_class(); //Issue 1: TODO memory leak
          atominfo->assign_fullstring(full_s);
 }

void vertex_class::assign_atom(atom_class newatom)
{
          atominfo = new atom_class(newatom); //Issue 1: TODO memory leak
 }


void vertex_class::output()
  {
     cout << "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV \n";   
     cout << "The ATOM Description information is...\n";
     atominfo->output();
     cout << "val is " << val <<  "\n";
     switch (truth_val) {
        case 0: { cout << "truth_val is FALSE \n"; break;} 
        case 1: { cout << "truth_val is TRUE \n"; break;}
        case 2: { cout << "truth_val is BOTTOM\n"; break;} 
        case 3: { cout << "truth_val is TOP\n"; break;} 
     } // SWITCH

     switch (J_val) {
        case 0: { cout << "J_val is FALSE \n"; break;} 
        case 1: { cout << "J_val is TRUE \n"; break;}
        case 2: { cout << "J_val is BOTTOM\n"; break;} 
        case 3: { cout << "J_val is TOP\n"; break;} 
     } // SWITCH

     switch (W_val) {
        case 0: { cout << "W_val is FALSE \n"; break;} 
        case 1: { cout << "W_val is TRUE \n"; break;}
        case 2: { cout << "W_val is BOTTOM\n"; break;} 
        case 3: { cout << "W_val is TOP\n"; break;} 
     } // SWITCH



     switch (guess) {
        case 0: { cout << "guess is FALSE \n"; break;} 
        case 1: { cout << "guess is TRUE \n"; break;}
     } // SWITCH

     switch (access) {
        case 0: { cout << "access is FALSE \n"; break;} 
        case 1: { cout << "access is TRUE \n"; break;}
     } // SWITCH
  
     cout << "Postorder Number:  " << postorder_num << "\n";

     cout << "list of rule bodies is :\n";
     bodylist.print();

     cout << "list of positive appearances is :\n";
     pos_appearances.print();
     cout << "list of negative appearances is :\n";
     neg_appearances.print();
     cout << "this vertex nextnode is " << vnextnode << "\n"; 
     cout << "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV \n";   


  } 


void vertex_class::clear()
{
   bodylist.cleanup();
   pos_appearances.cleanup();
   neg_appearances.cleanup();
}


///////////////////////////////////////////////////////////////////////
///  Routines associated with NODE_CLASS but not derived from it.
///////////////////////////////////////////////////////////////////////

void vertex_class::assign_next(vertex_class *v_ptr)
 {
       vnextnode = v_ptr;
 }

vertex_class  *vertex_class::get_next_ptr()
 {
       return vnextnode;
 }

void vertex_class:: print_postorder_num()
{
    cout << val << "\t        " << postorder_num << "\n";
}


char *vertex_class::get_atominfo()
 {
       return atominfo->get_fullstring();
 }

constant_class *vertex_class::get_first_atom_constant()
{
      return atominfo->get_first_constant();
}

char *vertex_class::get_predicate_symbol()
{
      return atominfo->get_predicate_symbol();
}

     
///////////////////////////////////////////////////////////////////////
//  Add positive or negative appearances (specified by pointers)
//  to their respective lists.  Note:  input parm, p_ptr, actually
//  points to an rule_class object, a derivation of a node_class.
///////////////////////////////////////////////////////////////////////

void vertex_class::add_pos_appearance(rule_class *p_ptr)
{
      pos_appearances.add_ptr(p_ptr);
}

void vertex_class::add_neg_appearance(rule_class *p_ptr)
{
      neg_appearances.add_ptr(p_ptr);
} 

///////////////////////////////////////////////////////////////////////////
//  Add positive or negative appearance indicated by the rule in which 
//  they appear.  "The rule" is specified by input parms: v_ptr and 
//  b_ptr, which point to the head and body resepectively. 
///////////////////////////////////////////////////////////////////////////
void vertex_class::add_pos_appearance(vertex_class *v_ptr, body_node_class *b_ptr)
{
      rule_class *p_ptr = new rule_class();
      p_ptr->assign_val(0);
      p_ptr->assign_body_ptr(b_ptr);
      p_ptr->assign_vertex_ptr(v_ptr);

      pos_appearances.add_ptr(p_ptr);
}
void vertex_class::add_neg_appearance(vertex_class *v_ptr, body_node_class *b_ptr)
{
      rule_class *p_ptr = new rule_class();
      p_ptr->assign_val(0);
      p_ptr->assign_body_ptr(b_ptr);
      p_ptr->assign_vertex_ptr(v_ptr);

      neg_appearances.add_ptr(p_ptr);
}

///////////////////////////////////////////////////////////////////////////
//  Add positive or negative appearance indicated by the rule in which 
//  they appear.  "The rule" is specified by input parms: v_ptr and 
//  b_ptr, which point to the head and body resepectively AND its head Value. 
///////////////////////////////////////////////////////////////////////////
void vertex_class::add_pos_appearance( int head_val,
                                vertex_class *v_ptr, body_node_class *b_ptr)
{
    rule_class *p_ptr = new rule_class();
    p_ptr->assign_val(head_val);
    p_ptr->assign_body_ptr(b_ptr);
    p_ptr->assign_vertex_ptr(v_ptr);

    pos_appearances.add_ptr(p_ptr);
}
void vertex_class::add_neg_appearance( int head_val,
                                vertex_class *v_ptr, body_node_class *b_ptr)
{
    rule_class *p_ptr = new rule_class();
    p_ptr->assign_val(head_val);
    p_ptr->assign_body_ptr(b_ptr);
    p_ptr->assign_vertex_ptr(v_ptr);

    neg_appearances.add_ptr(p_ptr);
}


///////////////////////////////////////////////////////////////////////////
//  Add a body node to the body list.  There is a body node for each rule
//  in which the field "val" appears as the head.
//////////////////////////////////////////////////////////////////////////
void vertex_class::add_body(body_node_class *b_ptr)
{
      bodylist.add_ptr(b_ptr);
} 

/////////////////////////////////////////////////////////////////////////
///  Return the pointer to the first body with head vertex.
/////////////////////////////////////////////////////////////////////////
body_node_class *vertex_class::get_first_body()
{
   return (bodylist.get_first());
}

/////////////////////////////////////////////////////////////////////////
///  Return the pointer to the first positive appearance
/////////////////////////////////////////////////////////////////////////
rule_class *vertex_class::get_first_pos_appearance()
{
   return (pos_appearances.get_first());
}

/////////////////////////////////////////////////////////////////////////
///  Return the pointer to the first positive appearance
/////////////////////////////////////////////////////////////////////////
rule_class *vertex_class::get_first_neg_appearance()
{
   return (neg_appearances.get_first());
}


/////////////////////////////////////////////////////////////////////////
//   Assign truth value to vertex.  The possible truth values are:
//           BOTTOM   2 ...  Not true and not false
//           TOP      3 ...  Both true and false
//           FALSE    0 ...  false
//           TRUE     1 ...  true
//
//   Assignments to  guess and access are simply TRUE and FALSE.
////////////////////////////////////////////////////////////////////////
void vertex_class::assign_truth(int truth_v)
{
      truth_val = truth_v;
}

void vertex_class::assign_J_val(int jval)
{
       J_val = jval;
}

void vertex_class::assign_W_val(int wval)
{
       W_val = wval;
}


void vertex_class::assign_access(int acc_v)
{
      access  = acc_v;
}

void vertex_class::assign_postorder_num(int n)
{
      postorder_num = n;
}

////////////////////////////////////////////////////////////////////////
///   Mark vertex by placing a nonzero value in access field.
////////////////////////////////////////////////////////////////////////

void vertex_class::mark()
{
      access  = 1;
}
void vertex_class::assign_guess(int g)
{
      guess = g;
}




/////////////////////////////////////////////////////////////////////////
//  Extract the truth value.
/////////////////////////////////////////////////////////////////////////

int vertex_class::get_truth()
{
      return truth_val;
}

int vertex_class::get_J_val()
{
      return J_val;
}

int vertex_class::get_W_val()
{
      return W_val;
}


/////////////////////////////////////////////////////////////////////////
//  Return whether or not this vertex is access.
/////////////////////////////////////////////////////////////////////////

int vertex_class::get_access()
{
      return access;
}


/////////////////////////////////////////////////////////////////////////
//  Return whether or not this vertex has been visited.
/////////////////////////////////////////////////////////////////////////

int vertex_class::visited()
{
      return access;
}



/////////////////////////////////////////////////////////////////////////////
//  Return whether or not the truth value of this vertex was an
//  initial guess.  (for use with the backtracking search for stable models)
/////////////////////////////////////////////////////////////////////////////

int vertex_class::get_guess()
{
      return guess;
}



int vertex_class::determine_new_J_val(logic_program_class *P)
{
     body_node_class               *b_ptr;
     int                            lub_so_far;
     int                            b_val;

         lub_so_far = 0;               // 0 is FALSE...lowest in the <_t

         //Traverse bodylist and establish each body status;  Incrementally
         //  decide whether or not the status is higher than lub_so_far

         b_ptr = get_first_body();
         while (b_ptr != nullptr)  {
               b_ptr->determine_neg_assess(P);
               b_ptr->determine_pos_assess(P);
               b_val = b_ptr->determine_body_status();
               lub_so_far = lub_t(lub_so_far, b_val);
               b_ptr = b_ptr->get_next_ptr();
         } // WHILE

         return lub_so_far;
}


int vertex_class::no_head_appearance()
{
     if ((bodylist.get_length()) == 0)
          return 1;
     else
          return 0;
}

int vertex_class::has_negative_appearances()
{
     if ((neg_appearances.get_length()) > 0)
          return 1;
     else
          return 0;
}

int vertex_class::has_positive_appearances()
{
     if ((pos_appearances.get_length()) > 0)
          return 1;
     else
          return 0;
}
