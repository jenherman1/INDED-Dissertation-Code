//_________________________________________________________________________
constant_class::constant_class()
{
   val = 0;
   cnextnode = NULL;
   strcpy(constant_symbol,"");
//   appearancelist.initialize();
  }

//_________________________________________________________________________
constant_class::constant_class(int num)
{
   val = num;
   cnextnode = NULL;
   strcpy(constant_symbol,"");
//   appearancelist.initialize();
  }

//_________________________________________________________________________

constant_class::constant_class(char instr[STRING_LENGTH]) 
{
   val = 0;
   cnextnode = NULL;
   strcpy(constant_symbol,instr);
//   appearancelist.initialize();

}

//_________________________________________________________________________

void constant_class::output()
  {
     cout << "^_^_^_^_^_^_^_^_^_^^^_^_^_^_^_^_^_^_^_^_\n";
     cout << "Constant symbol is " << constant_symbol << endl;
     cout << "Val is..  " << val << endl;
     cout << "Appearance list is:  " << endl;
     appearancelist.print();
     cout << "The pointer to Next Constant (cnextnode) is: " << cnextnode << endl;
     cout << "^_^_^_^_^_^_^_^_^_^^^_^_^_^_^_^_^_^_^_^_\n";


  } 
//_________________________________________________________________________

void constant_class::clear()
  {
   val = 0;
   cnextnode = NULL;
   strcpy(constant_symbol,"");
   appearancelist.cleanup();
  }
//_________________________________________________________________________


void constant_class::assign_next(constant_class *c_ptr)
  {
     cnextnode = c_ptr;
  }
//_________________________________________________________________________

void constant_class::assign_val(int num)
  {
     val = num;
  }
//_________________________________________________________________________


void constant_class::assign_symbol(char instr[STRING_LENGTH])
  {
     strcpy(constant_symbol, instr);
  }
//_________________________________________________________________________

constant_class  *constant_class::get_next_ptr()
  {
      return cnextnode; 
  }
//_________________________________________________________________________

int constant_class::get_value()
  {
      return 0;
  }
//_________________________________________________________________________


char *constant_class::get_constant_symbol()
  {
      return constant_symbol;
  }
//_________________________________________________________________________
constant_appearance_class *constant_class::get_first_con_appearance()
  {
      return appearancelist.get_first();
  }
//_________________________________________________________________________

void constant_class::display()
  {
     cout << constant_symbol;
  }
//_________________________________________________________________________

void constant_class::display(ostream& fout)
  {
     fout << constant_symbol;
  }
//_________________________________________________________________________

void constant_class::add_constant_appearance(vertex_class *v_ptr)
{
       
      constant_appearance_class    *p_ptr;
      p_ptr = new  constant_appearance_class(v_ptr);
      appearancelist.add_ptr(p_ptr);
}       
//_________________________________________________________________________

void constant_class::add_constant_appearance(int headval, vertex_class *v_ptr)
{
       
      constant_appearance_class    *p_ptr;
      p_ptr = new  constant_appearance_class(headval, v_ptr);
      appearancelist.add_ptr(p_ptr);
}       

//_________________________________________________________________________

void constant_class::display_appearance_list(ostream& fout)
{
      constant_appearance_class  *capp_ptr;
      vertex_class               *v_ptr;

      fout << constant_symbol << ": \n";
      capp_ptr = get_first_con_appearance();
      while (capp_ptr != NULL) {
          capp_ptr->display_appearance(fout);
          capp_ptr = capp_ptr->get_next_ptr();
      } //WHILE
}
//------------------------------------------------------------------------
void constant_class::mark_is_taken()
{
      val = 1;
}
//------------------------------------------------------------------------
void constant_class::mark_NOT_taken()
{
      val = 0;
}

//------------------------------------------------------------------------
int constant_class::is_taken()
{
      return val;
}
