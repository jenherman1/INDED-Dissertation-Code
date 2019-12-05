/////////////////////////////////////////////////////////////////////////////
//  Constructors
////////////////////////////////////////////////////////////////////////////

atom_class::atom_class() : node_class()
{
   anextnode = NULL;
   constantlist.set_first(NULL);
   constantlist.set_last(NULL);
   constantlist.set_num_entries(0);
   predicate_symbol.assign_symbol("");
   fullstring.assign_symbol("");
   fullstring.assign_IS_NEGATIVE(0);

  }

atom_class::atom_class(int num) : node_class(num)
{
   anextnode = NULL;
   constantlist.set_first(NULL);
   constantlist.set_last(NULL);
   constantlist.set_num_entries(0);
   predicate_symbol.assign_symbol("");
   fullstring.assign_symbol("");
   fullstring.assign_IS_NEGATIVE(0);
 
  }

atom_class::atom_class( list_class<constant_class> participating_constants, 
                        char pred_symb[STRING_LENGTH])
{
   
   char        fullstring2[LONG_STRING_LENGTH];

   anextnode = NULL;
   constantlist = participating_constants;
   predicate_symbol.assign_symbol(pred_symb);
   fullstring.assign_symbol("");
   fullstring.assign_IS_NEGATIVE(0);

//  ASSIGN FULL_STRING OBJECT FIELD
      constant_class    *c_ptr;
      int                num_args;
      strcat(fullstring2, predicate_symbol.get_predicate_symbol()); 
      strcat(fullstring2, "(");

      c_ptr = get_first_constant();      
      num_args = get_num_constants();
   
      for (int i = 0; i < num_args; i++) {

            strcat(fullstring2, c_ptr->get_constant_symbol());
            if (i != (num_args - 1)) {
                   strcat(fullstring2, ", ");
                   c_ptr = c_ptr->get_next_ptr();
              } //IF
              else
                     strcat(fullstring2, ")" );
      } // FOR
   fullstring.assign_symbol(fullstring2);

  }


///////////////////////////////////////////////////////////


atom_class::atom_class(char full_s[LONG_STRING_LENGTH])   
{
   anextnode = NULL;
   constantlist.set_first(NULL);
   constantlist.set_last(NULL);
   constantlist.set_num_entries(0);
   predicate_symbol.assign_symbol("");
   fullstring.assign_symbol(full_s);
   fullstring.assign_IS_NEGATIVE(0);

// PARSE INPUT FULL_STRING INTO APPROPRIATE FIELDS

     char    cons[STRING_LENGTH];
     constant_class   *c_ptr;
     char   *ptr; 
     int   token_num = 1;     
     char  instr[LONG_STRING_LENGTH];

  //INITIALIZE cons
  strcpy(instr, full_s);
  strcpy(cons, "");

  ptr = strtok( instr, "(,)" );  
  while (ptr != NULL)
     {
           if (token_num++ == 1)
                 predicate_symbol.assign_symbol(ptr);
           else {
                 strcpy(cons, ptr);
                 c_ptr = new constant_class(cons);
                 constantlist.add_ptr(c_ptr);
            } // ELSE

           ptr = strtok(NULL, ",)" );
     } //WHILE

}  //CONSTRUCTOR that parses a full string     


atom_class::atom_class(char full_s[LONG_STRING_LENGTH],
                       int is_negative_val)   
{
   anextnode = NULL;
   constantlist.set_first(NULL);
   constantlist.set_last(NULL);
   constantlist.set_num_entries(0);
   predicate_symbol.assign_symbol("");
   fullstring.assign_symbol(full_s);
   fullstring.assign_IS_NEGATIVE(is_negative_val);

// PARSE INPUT FULL_STRING INTO APPROPRIATE FIELDS

     char    cons[STRING_LENGTH];
     constant_class   *c_ptr;
     char   *ptr; 
     int   token_num = 1;     
     char  instr[LONG_STRING_LENGTH];

  //INITIALIZE cons
  strcpy(instr, full_s);
  strcpy(cons, "");

  ptr = strtok( instr, "(,)" );  
  while (ptr != NULL)
     {
           if (token_num++ == 1)
                 predicate_symbol.assign_symbol(ptr);
           else {
                 strcpy(cons, ptr);
                 c_ptr = new constant_class(cons);
                 constantlist.add_ptr(c_ptr);
            } // ELSE

           ptr = strtok(NULL, ",)" );
     } //WHILE

}  //CONSTRUCTOR that parses a full string and assigns negation 


//JENNIFER

atom_class::~atom_class()
{
   constantlist.cleanup();
   predicate_symbol.clear();
   fullstring.clear();
  }



//////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


void atom_class::assign_atom_info(char full_s[LONG_STRING_LENGTH], int num)   
{
   anextnode = NULL;
   assign_val(num);
   constantlist.set_first(NULL);
   constantlist.set_last(NULL);
   constantlist.set_num_entries(0);
   predicate_symbol.assign_symbol("");
   fullstring.assign_symbol(full_s);
   fullstring.assign_IS_NEGATIVE(0);

// PARSE INPUT FULL_STRING INTO APPROPRIATE FIELDS

     char    cons[STRING_LENGTH];
     constant_class   *c_ptr;
     char   *ptr; 
     int   token_num = 1;     
     char  instr[LONG_STRING_LENGTH];

  //INITIALIZE cons
  strcpy(instr, full_s);
  strcpy(cons, "");

  ptr = strtok( instr, "(,)" );  
  while (ptr != NULL)
     {
           if (token_num++ == 1)
                 predicate_symbol.assign_symbol(ptr);
           else {
                 strcpy(cons, ptr);
                 c_ptr = new constant_class(cons);
                 constantlist.add_ptr(c_ptr);
            } // ELSE

           ptr = strtok(NULL, ",)" );
     } //WHILE

}  // ASSIGN_ATOM_INFO

//////////////////////////////////////////////////////////////////////////////



void atom_class::assign_atom_info(char full_s[LONG_STRING_LENGTH], int num,
                                  int is_negative_val)   
{
   anextnode = NULL;
   assign_val(num);
   constantlist.set_first(NULL);
   constantlist.set_last(NULL);
   constantlist.set_num_entries(0);
   predicate_symbol.assign_symbol("");
   fullstring.assign_symbol(full_s);
   fullstring.assign_IS_NEGATIVE(is_negative_val);

// PARSE INPUT FULL_STRING INTO APPROPRIATE FIELDS

     char    cons[STRING_LENGTH];
     constant_class   *c_ptr;
     char   *ptr; 
     int   token_num = 1;     
     char  instr[LONG_STRING_LENGTH];

  //INITIALIZE cons
  strcpy(instr, full_s);
  strcpy(cons, "");

  ptr = strtok( instr, "(,)" );  
  while (ptr != NULL)
     {
           if (token_num++ == 1)
                 predicate_symbol.assign_symbol(ptr);
           else {
                 strcpy(cons, ptr);
                 c_ptr = new constant_class(cons);
                 constantlist.add_ptr(c_ptr);
            } // ELSE

           ptr = strtok(NULL, ",)" );
     } //WHILE

}  // ASSIGN_ATOM_INFO

//////////////////////////////////////////////////////////////////////////////


void atom_class::assign_val (int n)
  {
     node_class::assign_val(n);
  }


void atom_class::output()
  {
     cout << "^^^^^^^^^^^^^^^__________________^^^^^^^^^^^^^^^^ \n";
     cout << "Atom value is.." << val << endl;
     cout << "IS_NEGATIVE is .." << get_IS_NEGATIVE() << endl;
     cout << "Predicate String..." << predicate_symbol.get_predicate_symbol() << endl;
     cout << "Constant List is of "<< get_num_constants() << "..." << endl;
     constantlist.print();
     cout << "The Full String version of this atom...." 
          << fullstring.get_fullstring_symbol() << endl;
     cout << "The pointer to the next atom is .." << anextnode << endl;
     cout << "^^^^^^^^^^^^^^^__________________^^^^^^^^^^^^^^^^ \n";
  } 

void atom_class::clear()
  {
   anextnode = NULL;
   constantlist.cleanup();
   predicate_symbol.clear();
   fullstring.clear();
  }


void atom_class::assign_predicate(char pred_symb[STRING_LENGTH])       
  {
     predicate_symbol.assign_symbol(pred_symb);
  }

void atom_class::assign_fullstring(char full_s[LONG_STRING_LENGTH])       
  {
    fullstring.assign_symbol(full_s);
  }


void atom_class::assign_next(atom_class *a_ptr)
  {
     anextnode = a_ptr;
  }

atom_class  *atom_class::get_next_ptr()
  {
      return anextnode; 
  }
     
int atom_class::get_IS_NEGATIVE()
  {
      return fullstring.get_IS_NEGATIVE();
  }
     
void atom_class::assign_IS_NEGATIVE(int num)
  {
      fullstring.assign_IS_NEGATIVE(num);
  }
     


int atom_class::get_atom_val()
{
     return val;
}

char *atom_class::get_predicate_symbol()
{
     return predicate_symbol.get_predicate_symbol();
}

char *atom_class::get_fullstring()
{
     return fullstring.get_fullstring_symbol();
}


int atom_class::get_num_constants()
{
     return constantlist.get_num_entries();
}

constant_class *atom_class::get_first_constant()
{
     return constantlist.get_first();
}

void atom_class::display()
{
      fullstring.display();
}


void atom_class::display(ostream& fout)
{
      fullstring.display(fout);
}

char *atom_class::get_ith_constant_symbol(int num)
{
       constant_class   *c_ptr;
       char              found_str[STRING_LENGTH];
 
       c_ptr = constantlist.get_ith(num);
       if (c_ptr != NULL) {      
           strcpy(found_str, c_ptr->get_constant_symbol());
       }
       else {
           strcpy(found_str, "");
       } //ELSE
       return found_str;
}
///////////////////////////////////////////////////////////////////////////
///
///
///////////////////////////////////////////////////////////////////////////
void atom_class::initialize_covered()  
{
     val = 0;
}

void atom_class::mark_covered()  
{
     val = 1;
}

void atom_class::mark_NOT_covered()  
{
     val = 0;
}

int atom_class::get_is_covered()  
{
    if (val == 1)
       return 1;
    else 
       return 0;
}
