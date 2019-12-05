/////////////////////////////////////////////////////////////////////
///      Constructors
/////////////////////////////////////////////////////////////////////

spantree_class::spantree_class()
   { 
      vertval = -99;
      snextnode = NULL;
      truth_val = BOTTOM;
      conflict_val = -99;
       status = 0;                   // NONTOTAL
   }
spantree_class::spantree_class(int n)
   {
       snextnode = NULL;
       truth_val = BOTTOM;
       status = 0;
       conflict_val = -99;
       vertval = n;
   }

spantree_class::spantree_class(int val, int start_truth)
   {
       snextnode = NULL;
       truth_val = start_truth;
       status = 0;
       vertval = val;
       conflict_val = -99;
   }

////////////////////////////////////////////////////////////////////////////
///  Virtuals associated with NODE_CLASS
//////////////////////////////////////////////////////////////////////////

void spantree_class::assign_vertval(int n)
  {
    vertval = n;
  }


void spantree_class::output()
  {
     cout << "SPAN TREE SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS \n";   
     cout << "vertval is " << vertval <<  "\n";
     switch (truth_val) {
        case 0: { cout << "truth_val is FALSE \n"; break;} 
        case 1: { cout << "truth_val is TRUE \n"; break;}
        case 2: { cout << "truth_val is BOTTOM\n"; break;} 
        case 3: { cout << "truth_val is TOP\n"; break;} 
     } // SWITCH

     switch (status) {
        case 0: { cout << "Status is NON TOTAL with both pos and neg edges \n";break;}
        case 1: { cout << "Status is TOTAL \n";break;}
        case 2: { cout << "Status is NON TOTAL with ONLY POSITIVE edges \n";break;}
        case 3: { cout << "Status is NON TOTAL with ONLY NEGATIVE edges \n";break;}
        case 4: { cout << "Status is CONFLICT ...";
                  cout << "with node..." << conflict_val << "\n";
                   break;}
     } // SWITCH

     cout << "this spantree nextnode is " << snextnode << "\n"; 
     cout << "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS \n";   
  } 


///////////////////////////////////////////////////////////////////////
///  Assign Routines
///////////////////////////////////////////////////////////////////////

void spantree_class::assign_next(spantree_class *s_ptr)
 {
       snextnode = s_ptr;
 }

spantree_class  *spantree_class::get_next_ptr()
 {
       return snextnode;
 }

     
void spantree_class::assign_truth(int truth_v)
{
      truth_val = truth_v;
}

void spantree_class::assign_conflict_val(int con_v)
{
      conflict_val = con_v;
}


void spantree_class::assign_status(int stat_v)
{
      status  = stat_v;
}

int spantree_class::get_vertval()
{
      return vertval;
}

int spantree_class::get_value()
{
      return vertval;
}
 
int spantree_class::get_conflict_val()
{
      return conflict_val;
}

void spantree_class::clear()
{
}

/////////////////////////////////////////////////////////////////////////
//  Return whether or not this spantree possesses status characterizing
//     properties.
/////////////////////////////////////////////////////////////////////////

int spantree_class::get_status()
{
      return status;
}


int spantree_class::is_conflict()
{
      
      if (status == 4)    // if status is CONFLICT
           return 1;      //        return TRUE
      else                // otherwise return FALSE
           return 0;
}

int spantree_class::is_total()
{
      
      if (status == 1)    // if status is TOTAL
           return 1;      //        return TRUE
      else                // otherwise return FALSE
           return 0;
}


int spantree_class::is_nontotal_with_only_pos_edges() 
{
      
      if (status == 2)    // if status is NONTOTALPOS
           return 1;      //        return TRUE
      else                // otherwise return FALSE
           return 0;
}


int spantree_class::is_nontotal_with_only_neg_edges()  
{
      
      if (status == 3)    // if status is NONTOTALNEG
           return 1;      //        return TRUE
      else                // otherwise return FALSE
           return 0;
}

