#include <iostream>

#include "CONAPP.H"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
///  Constructors
//////////////////////////////////////////////////////////////////////////////
constant_appearance_class::constant_appearance_class()
     {
         val = 0;
         appearance_v_ptr = nullptr;
         cappnextnode = nullptr;
     }

//____________________________________________________________________________

constant_appearance_class::constant_appearance_class(int n) 
     {
         val = n;
         appearance_v_ptr = nullptr;
         cappnextnode = nullptr;
     }

//____________________________________________________________________________

constant_appearance_class::constant_appearance_class(vertex_class *v_ptr)
    {
          val = 0;
          appearance_v_ptr = v_ptr;
          cappnextnode = nullptr;
    }

//____________________________________________________________________________

constant_appearance_class::constant_appearance_class(int rule_head, vertex_class *v_ptr)
    {
          val = rule_head; 
          appearance_v_ptr = v_ptr;
          cappnextnode = nullptr;
    }


//____________________________________________________________________________

void constant_appearance_class::assign_val(int n)
    {
          val = n;
    }


//____________________________________________________________________________

void constant_appearance_class::output()
    {
       cout << "-------<begin constant appearance>-------------------- \n";
       cout << "val is " << val << "\n";
       cout << "vertex pointer is " << appearance_v_ptr << "\n";
       cout << "constant_appearance_class nextnode is  " << cappnextnode << "\n";
       cout << "------------<end constant appearance>----------------- \n";
    }

//____________________________________________________________________________

void constant_appearance_class::display_appearance(ostream& fout)
{
     char    neg_symbol = ' ';

     if (appearance_v_ptr != nullptr) {
         if (appearance_v_ptr->get_truth()==0)
            neg_symbol = '~';
         fout << "      ";
         fout << neg_symbol << appearance_v_ptr->get_predicate_symbol();
         fout << endl;
     } //IF
     else {
          fout << "### WATCH ### appearance node is nullptr \n";
     } //ELSE
}

//____________________________________________________________________________

void constant_appearance_class::clear()
    {
       val = 0;
       appearance_v_ptr = nullptr;
       cappnextnode = nullptr;
    }

//____________________________________________________________________________

   

void constant_appearance_class::assign_next(constant_appearance_class *p_ptr)
   {
         cappnextnode = p_ptr;
   }


//____________________________________________________________________________

constant_appearance_class  *constant_appearance_class::get_next_ptr()
   {
          return cappnextnode;
   }

//____________________________________________________________________________

void constant_appearance_class::assign_vertex_ptr(vertex_class *v_ptr)
    {
          appearance_v_ptr = v_ptr;
    }
//____________________________________________________________________________

vertex_class *constant_appearance_class::get_vertex_ptr()
    {
          return appearance_v_ptr;
    }
//____________________________________________________________________________

int constant_appearance_class::get_value()
    {
          return val;
    }
//____________________________________________________________________________

