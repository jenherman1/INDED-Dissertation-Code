#include <iostream>

#include "BODY.H"
#include "LITERAL.H"
#include "UTILITY1.H"
#include "UTILITY2.H"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
//  Constructors
////////////////////////////////////////////////////////////////////////////


body_node_class::body_node_class()
{
   bnextnode = nullptr;
   pos_literals.set_first(nullptr);
   pos_literals.set_last(nullptr);
   neg_literals.set_first(nullptr);
   neg_literals.set_last(nullptr);
   pos_literals.set_num_entries(0);
   neg_literals.set_num_entries(0);
   negative_fact = 0;
   num_literals_sat = 0;

   neg_assess = 1;               // initialize glb (min_so_far) at TRUE (max)
   pos_assess = 1;              
   val = BOTTOM
  }

body_node_class::body_node_class(int dummy)
{
   bnextnode = nullptr;
   pos_literals.set_first(nullptr);
   pos_literals.set_last(nullptr);
   neg_literals.set_first(nullptr);
   neg_literals.set_last(nullptr);
   pos_literals.set_num_entries(0);
   neg_literals.set_num_entries(0);

   negative_fact = 0;

   num_literals_sat = 0;

   neg_assess = 1;               // initialize glb (min_so_far) at TRUE (max)
   pos_assess = 1;              
   val = BOTTOM
  }


////////////////////////////////////////////////////////////////////////////
///  Generates a body of a rule according to the current distribution.
///
///         For each distribution: 
///                          -determine length of the body
///                          -determine the number of pos and neg subgoals
///                          -randomly create and add the postive literals
///                          -randomly create and add the negative literals
///
//////////////////////////////////////////////////////////////////////////

body_node_class::body_node_class(int distribution, int head_val)
{
   int               i;
   int               subgoal_val;
   int               num_subgoals;
   int               num_negative_subgoals;
   int               num_positive_subgoals;


  subgoal_val = 0;
///  --------------------------
///  node_class initializations

  //Issue 1: are these unused?
//   nextnode = nullptr;
//   vertex_ptr = nullptr;
//   body_ptr  = nullptr;

///---------------------
   bnextnode = nullptr;
   switch (distribution){ 
//       case NODIST 
         case 0: {
            num_subgoals = Body_Length;  
            num_negative_subgoals = get_random_val(Max_Negative_Subgoals);
            num_positive_subgoals = (num_subgoals - num_negative_subgoals);

            for (i=0; i < num_positive_subgoals; i++)   
                 find_add_pos_literal((get_random_val(Num_Variables)));

            for (i=0; i < num_negative_subgoals; i++)   
                  find_add_neg_literal((get_random_val(Num_Variables)));
            break;
       }  // CASE 0

//     case FIXED_MAX_BODY_LEN
       case 1: {
            num_subgoals = get_random_val(Body_Length);
            if (Max_Negative_Subgoals > num_subgoals) {
               num_negative_subgoals = get_random_val(num_subgoals); }
            else {
               num_negative_subgoals = get_random_val(Max_Negative_Subgoals); }

            num_positive_subgoals = (num_subgoals - num_negative_subgoals);

            for (i=0; i < num_positive_subgoals; i++)   
                find_add_pos_literal((get_random_val(Num_Variables)));

            for (i=0; i < num_negative_subgoals; i++)   
                find_add_neg_literal((get_random_val(Num_Variables)));
            break;
        }  // CASE 1

//      case  FIXED_BODY_LEN
        case 2: {
            num_subgoals = Body_Length;
            num_negative_subgoals = get_random_val(Max_Negative_Subgoals);
            num_positive_subgoals = (num_subgoals - num_negative_subgoals);
            
            for (i=0; i < num_positive_subgoals; i++)   
                 find_add_pos_literal((get_random_val(Num_Variables)));

            for (i=0; i < num_negative_subgoals; i++)   
                find_add_neg_literal((get_random_val(Num_Variables)));
            break;
        } // CASE 2

//      case  CONSTANT_PROB
        case 3: {
            for (i=1; i<=Num_Variables; i++)  {
                if (get_include_prob() <= Var_Prob) {
                      if (get_include_prob() <= Neg_Subgoal_Prob) {
                            add_neg_literal(i);
                      } // IF
                      else {
                            add_pos_literal(i);
                      } // ELSE
                  } // IF
             } // FOR
             break;
        } // CASE 3 
        // CASE FIXED_BODY_SMALL_BODILESS
        case 4: {
            num_subgoals = Body_Length;
            num_negative_subgoals = get_random_val(Max_Negative_Subgoals);
            num_positive_subgoals = (num_subgoals - num_negative_subgoals);
            
            for (i=0; i < num_positive_subgoals; i++)   
                 find_add_pos_literal((get_random_val(Num_Variables)));

            for (i=0; i < num_negative_subgoals; i++)   
                find_add_neg_literal((get_random_val(Num_Variables)));
            break;
        } // CASE 4

//     case UNI-RULE ...FIXED_MAX_BODY_LEN of Num_Variables
       case 5: {
            num_subgoals = get_random_val(Num_Variables);
            num_negative_subgoals = get_random_val(num_subgoals); 
            num_positive_subgoals = (num_subgoals - num_negative_subgoals);

            for (i=0; i < num_positive_subgoals; i++)   
               {
                subgoal_val = get_random_val(Num_Variables);
                if (!(head_val == subgoal_val)) 
                       find_add_pos_literal(subgoal_val);
               } // FOR

            for (i=0; i < num_negative_subgoals; i++)   
               {
                subgoal_val = get_random_val(Num_Variables);
                if (!(head_val == subgoal_val) )
                       find_add_neg_literal(subgoal_val);
                } // FOR
            break;
        }  // CASE 5
//--------------

   } //SWITCH



     //  INITIALIZE THE OTHER FIELDS IN THE BODY CLASS TYPE
     
     num_literals_sat = 0;
       
     neg_assess = true;  // Initialize the glb at MAX
     pos_assess = true;
     negative_fact = 0;
 
     val = BOTTOM
     

}    


////////////////////////////////////////////////////////////////////////////
///   Virtual routines from NODE_CLASS
////////////////////////////////////////////////////////////////////////////

void body_node_class::assign_val (int n)
  {
     val = n;
  }

void body_node_class::assign_negative_fact(int n)
  {
     if (n != 0)
        negative_fact = 1;
     else
        negative_fact = 0;
  }


void body_node_class::output()
  {
     
     cout << "================================================== \n";
     cout << "Negative Fact? ";
     if( negative_fact) 
            cout << "   YES! \n";
       else 
            cout << "   NO. \n";
     switch (val) {
        case 0: { cout << "val (status)  is FALSE \n"; break;} 
        case 1: { cout << "val (status)  is TRUE \n"; break;}
        case 2: { cout << "val (status)  is BOTTOM \n"; break;} 
        case 3: { cout << "val (status)  is TOP \n"; break;} 
     } // SWITCH

     cout << "num_literals_sat is " << num_literals_sat << "\n";
     cout << "pos_assess is " << pos_assess << "\n";
     cout << "list of positive literals is :\n";
     pos_literals.print();

     cout << "neg_assess is " << neg_assess << "\n";
     cout << "list of negative literals is :\n";
     neg_literals.print();
     cout << "body_class nextnode is " << bnextnode << "\n"; 
     cout << "================================================== \n";


  } 

void body_node_class::clear()
  {
     pos_literals.cleanup();
     neg_literals.cleanup();
  }

/////////////////////////////////////////////////////////////////////
///    Routines related to NODE_CLASS but not derived
////////////////////////////////////////////////////////////////////

void body_node_class::assign_next(body_node_class *b_ptr)
  {
     bnextnode = b_ptr;
  }

body_node_class  *body_node_class::get_next_ptr()
  {
      return bnextnode; 
  }
int body_node_class::get_negative_fact()
  {
     return negative_fact;
  }
     
int body_node_class::get_value()
   {
      return val;
   }

///////////////////////////////////////////////////////////////////
//  Add positive or negative literals specified by pointers
//  to their respective lists
//////////////////////////////////////////////////////////////////
void body_node_class::add_pos_literal(literal_class *p_ptr)
{
      pos_literals.add_ptr(p_ptr);
}

void body_node_class::add_neg_literal(literal_class *p_ptr)
{
      neg_literals.add_ptr(p_ptr);
} 

///////////////////////////////////////////////////////////////////
//  Add positive or negative literals indicated by integer values
//  to their respective lists
//////////////////////////////////////////////////////////////////
void body_node_class::add_pos_literal(int k)
{
      literal_class *p_ptr;
      p_ptr = new literal_class(k);
      pos_literals.add_ptr(p_ptr);
}

void body_node_class::add_neg_literal(int k) 
{
      literal_class *p1_ptr;
      p1_ptr = new literal_class(k);
      neg_literals.add_ptr(p1_ptr);
}

void body_node_class::add_neg_literal(int k, vertex_class *v_ptr,
                                             body_node_class *b_ptr) 
{

      literal_class *p1_ptr = new literal_class();

      p1_ptr->assign_val(k);
      p1_ptr->assign_vertex_ptr(v_ptr);
      p1_ptr->assign_body_ptr(b_ptr);

      neg_literals.add_ptr(p1_ptr);
}

void body_node_class::add_pos_literal(int k, vertex_class *v_ptr,
                                             body_node_class *b_ptr) 
{
      literal_class *p1_ptr = new literal_class();

      p1_ptr->assign_val(k);
      p1_ptr->assign_vertex_ptr(v_ptr);
      p1_ptr->assign_body_ptr(b_ptr);

      pos_literals.add_ptr(p1_ptr);
}


/////////////////////////////////////////////////////////////////////////
//  Add positive or negative literals (indicated by integer values
//  and by their determining vertex pointers) to their respective lists
////////////////////////////////////////////////////////////////////////
void body_node_class::add_pos_literal(int k, vertex_class *v_ptr)
{
      literal_class *p_ptr;
      p_ptr = new literal_class(k);
      p_ptr->assign_vertex_ptr(v_ptr);
      pos_literals.add_ptr(p_ptr);
}

void body_node_class::add_neg_literal(int k, vertex_class *v_ptr) 
{
      literal_class *p_ptr;
      p_ptr = new literal_class(k);
      p_ptr->assign_vertex_ptr(v_ptr);
      neg_literals.add_ptr(p_ptr);
}

///////////////////////////////////////////////////////////////////////////////
//  Searches for a literal with val k.  If it is not found,   this routine
//  creates and adds it to the appropriate literal list.
///////////////////////////////////////////////////////////////////////////////

void body_node_class::find_add_pos_literal( int k)
{
     literal_class   *p_ptr;

     p_ptr = pos_literals.find_val_ptr(k);
     
     if (p_ptr == nullptr) {
          p_ptr = new literal_class(k);
          pos_literals.add_ptr(p_ptr);
     } //IF
} // FIND_ADD_POS_LITERAL 


void body_node_class::find_add_neg_literal( int k)
{
     literal_class *p_ptr;

     p_ptr = neg_literals.find_val_ptr(k);
     
     if (p_ptr == nullptr) {
          p_ptr = new literal_class(k);
          neg_literals.add_ptr(p_ptr);
     } //IF
} // FIND_ADD_NEG_LITERAL 



/////////////////////////////////////////////////////////////////////////////
//   Retrieves the status of the body.  Possible states are:
//        FALSE ..0   
//        TRUE  ..1  
//        BOTTOM..2 
//        TOP   ..3  
/////////////////////////////////////////////////////////////////////////////

int body_node_class::get_body_status()
{
     return val;
}

void body_node_class::set_body_status(int k)
{
     val = k;
};

void body_node_class::set_pos_assess(int tval)
{
     pos_assess = tval;
};

void body_node_class::set_neg_assess(int tval)
{
     neg_assess = tval;
}


int body_node_class::get_pos_assess()
{
     return pos_assess;
}

void body_node_class::determine_pos_assess(logic_program_class *P)
{
     if (negative_fact == 1)
          pos_assess = 0 ;
     else 
          pos_assess = glb_pos_lits(P);
}

//void body_node_class::determine_UNIT_BODY_pos_assess()
//{
//
//  int               curlit_J;
//  literal_class    *curlit_ptr;
//  
//
//  curlit_ptr = get_first_pos_lit_ptr();
//
//  if (curlit_ptr == nullptr)
//         pos_assess = 1;
//  else
//  {
//       curlit_J = P->get_lit_Jval(curlit_ptr);
//       pos_assess = curlit_J;
//   } // ELSE
//}
//  
//void body_node_class:determine_UNIT_BODY_neg_assess()
//{
//  int               curlit_neg_W;
//  literal_class    *curlit_ptr;
//  
//  curlit_ptr = get_first_pos_lit_ptr();
//  if (curlit_ptr == nullptr)
//   {
//         neg_assess = 1;
//   }
//  else
//  {
//       curlit_neg_W  = P->get_neg_lit_Wval(curlit_ptr);
//       neg_assess = curlit_new_W;
//   } // ELSE  
//}
//


int body_node_class::get_neg_assess()
{
     return neg_assess;
}

void body_node_class::determine_neg_assess(logic_program_class *P)
{
     if (negative_fact == 1)
         neg_assess = 0;
     else
         neg_assess = glb_neg_lits(P);
}


void body_node_class::set_num_literals_sat(int num)
{
     num_literals_sat = num;
}

literal_class *body_node_class::get_first_pos_lit_ptr()
{
     return (pos_literals.get_first());
}

literal_class *body_node_class::get_first_neg_lit_ptr()
{
     return (neg_literals.get_first());
}

void body_node_class::display_body()
{
    literal_class    *p_ptr, *n_ptr;

    p_ptr = pos_literals.get_first();
    n_ptr = neg_literals.get_first();

    // DISPLAY POSITIVE LITERALS
    while (p_ptr != nullptr) {
        cout << (p_ptr->get_value());
        p_ptr = p_ptr->get_next_ptr();
        if ((p_ptr != nullptr) || (n_ptr != nullptr)) {
                cout << ", ";
        } // IF
    } // WHILE

    // DISPLAY NEGATIVE LITERALS
    while (n_ptr != nullptr) {
        cout << "~" << (n_ptr->get_value());
        n_ptr = n_ptr->get_next_ptr();
        if (n_ptr != nullptr) {
                cout << ", ";
        } // IF
    } // WHILE
    cout << "\n";
} // DISPLAY_BODY


///////////////////////////////////////////////////////////////////////////
///   Update body status..
///////////////////////////////////////////////////////////////////////////
void body_node_class::update_body_status()
{
                 val = glb_t(pos_assess, neg_assess);     
}

///////////////////////////////////////////////////////////////////////////
///   Same as Update body status..but returns the procured value 
///////////////////////////////////////////////////////////////////////////
int body_node_class::determine_body_status()
{
        val = glb_t(pos_assess, neg_assess);     
        return val;
}


///////////////////////////////////////////////////////////////////////////
///   Increase the number of literals satisfied by num..
///////////////////////////////////////////////////////////////////////////
void body_node_class::increase_num_literals_sat(int num)
{
     num_literals_sat = (num_literals_sat +  num);
}


/////////////////////////////////////////////////////////////////////////////
///   These routines take the conjunction over the respective sets of 
///   literals.  Glb_neg_lits()  negates the negative literals wrt to the
///   previous iterations W values.  Glb_pos_lits computes the conjunction
///   of the positive literals wrt J values.
///
/////////////////////////////////////////////////////////////////////////////

int body_node_class::glb_pos_lits(logic_program_class *P)
{
  int               glb_so_far;
  int               curlit_J;
  literal_class    *curlit_ptr;
  vertex_class      *curlit_v_ptr;
  
  glb_so_far = TRUE                     // Initialize Min_so_far at the Max

  curlit_ptr = get_first_pos_lit_ptr();
//DD 
//cout << "Inside glb_pos_lits...." << endl;
     while (curlit_ptr != nullptr)  {
//cout << "curlit_ptr is.............";
//curlit_ptr->output();
        curlit_J = P->get_lit_Jval(curlit_ptr);
//cout << "curlit_J is........." << curlit_J << endl;
//cout << "before integrating curlit_J, glb_so_far is......." << glb_so_far << endl;
        glb_so_far = glb_t(glb_so_far, curlit_J);
//cout << "after integrating...glb_so_far is......." << glb_so_far << endl;
        curlit_ptr = curlit_ptr->get_next_ptr();
     } // WHILE

//cout << "about to return glb_so_far=" << glb_so_far << endl;
     return glb_so_far;

}
  


int body_node_class::glb_neg_lits(logic_program_class *P)
{
  int               glb_so_far;
  int               curlit_neg_W;
  literal_class    *curlit_ptr;
  
  glb_so_far = TRUE;                     // Initialize Min_so_far at the Max

  curlit_ptr = get_first_neg_lit_ptr();

     while (curlit_ptr != nullptr)  {
        curlit_neg_W  = P->get_neg_lit_Wval(curlit_ptr);
        glb_so_far = glb_t(glb_so_far, curlit_neg_W);
        curlit_ptr = curlit_ptr->get_next_ptr();
      } // WHILE

      return glb_so_far;

}

int body_node_class::is_bodiless_rule()
{
     if( ((neg_literals.get_length()) == 0) &&
        ((pos_literals.get_length()) == 0))  
               return 1;
     else
               return 0;
}


int body_node_class::has_only_negative_subgoals()
{
     if( ((neg_literals.get_length()) > 0) &&
        ((pos_literals.get_length()) == 0))  
               return 1;
     else
               return 0;
}


int body_node_class::has_only_positive_subgoals()
{
     if( ((pos_literals.get_length()) > 0) &&
        ((neg_literals.get_length()) == 0))  
               return 1;
     else
               return 0;
}


int body_node_class::has_any_negative_subgoals()
{
     if  ((neg_literals.get_length()) > 0) 
               return 1;
     else
               return 0;
}


int body_node_class::has_any_positive_subgoals()
{
     if  ((pos_literals.get_length()) > 0) 
               return 1;
     else
               return 0;
}

