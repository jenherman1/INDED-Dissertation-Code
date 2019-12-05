/////////////////////////////////////////////////////////////////////////////
//  Constructors
/////////////////////////////////////////////////////////////////////////////

predicate_expression_class::predicate_expression_class() : node_class()
{
   prednextnode = NULL;
   variablelist.set_first(NULL);
   variablelist.set_last(NULL);
   variablelist.set_num_entries(0);
   predicate_symbol.assign_symbol("");
   fullstring.assign_symbol("");
   IS_NEGATIVE = 0;
   fullstring.assign_IS_NEGATIVE(0);

  }

predicate_expression_class::predicate_expression_class(int num) : node_class(num)
{
   prednextnode = NULL;
   variablelist.set_first(NULL);
   variablelist.set_last(NULL);
   variablelist.set_num_entries(0);
   predicate_symbol.assign_symbol("");
   fullstring.assign_symbol("");
   IS_NEGATIVE = 0;
   fullstring.assign_IS_NEGATIVE(0);


 
  }
predicate_expression_class::predicate_expression_class( list_class<variable_class> participating_variables, 
                        char pred_symb[STRING_LENGTH])
{
   
   char        fullstring2[LONG_STRING_LENGTH];

   IS_NEGATIVE = 0;                        // EEEEEEKS
   fullstring.assign_IS_NEGATIVE(0);

   prednextnode = NULL;
   variablelist = participating_variables;
   predicate_symbol.assign_symbol(pred_symb);
   fullstring.assign_symbol("");

//  ASSIGN FULL_STRING OBJECT FIELD
      variable_class    *var_ptr;
      int                num_args;

      strcpy(fullstring2, "");
      strcat(fullstring2, pred_symb);
//      strcat(fullstring2, predicate_symbol.get_predicate_symbol()); 

      strcat(fullstring2, "(");

      var_ptr = get_first_variable();      
      num_args = get_num_variables();
   
      for (int i = 0; i < num_args; i++) {

            strcat(fullstring2, var_ptr->get_variable_symbol());
            if (i != (num_args - 1)) {
                   strcat(fullstring2, ", ");
                   var_ptr = var_ptr->get_next_ptr();
              } //IF
              else
                     strcat(fullstring2, ")" );
      } // FOR
   fullstring.assign_symbol(fullstring2);

  }


///////////////////////////////////////////////////////////


predicate_expression_class::predicate_expression_class(char full_s[LONG_STRING_LENGTH])   
{
   prednextnode = NULL;
   variablelist.set_first(NULL);
   variablelist.set_last(NULL);
   variablelist.set_num_entries(0);

   predicate_symbol.assign_symbol("");

// PARSE INPUT FULL_STRING INTO APPROPRIATE FIELDS

     char    new_variable[STRING_LENGTH];
     variable_class   *var_ptr;
     char   *ptr; 
     int   token_num = 1;     
     char  instr[LONG_STRING_LENGTH];

  //INITIALIZE new_variable
  strcpy(instr, full_s);
  strcpy(new_variable, "");

  ptr = strtok( instr, "(,)" );  
  while (ptr != NULL)
     {
           if (token_num++ == 1)
                 predicate_symbol.assign_symbol(ptr);
           else {
                 strcpy(new_variable, ptr);
                 var_ptr = new variable_class(new_variable);
                 variablelist.add_ptr(var_ptr);
            } // ELSE

           ptr = strtok(NULL, ",)" );
     } //WHILE

//  ASSIGN FULL_STRING OBJECT FIELD
      int                num_args;
      char               fullstring2[LONG_STRING_LENGTH];
      
      fullstring.assign_symbol("");
      strcpy(fullstring2, "");
      strcat(fullstring2, predicate_symbol.get_predicate_symbol()); 
      strcat(fullstring2, "(");

      var_ptr = get_first_variable();      
      num_args = get_num_variables();
   
      for (int i = 0; i < num_args; i++) {

            strcat(fullstring2, var_ptr->get_variable_symbol());
            if (i != (num_args - 1)) {
                   strcat(fullstring2, ", ");
                   var_ptr = var_ptr->get_next_ptr();
              } //IF
              else
                     strcat(fullstring2, ")" );
      } // FOR
   fullstring.assign_symbol(fullstring2);

}  //CONSTRUCTOR that parses a full string and assigns    

//////////////////////////////////////////////////////////////////////////////


void predicate_expression_class::assign_pred_info(char full_s[LONG_STRING_LENGTH],
                                                   int num)   
{
   IS_NEGATIVE = 0;                   //EEEEKS... FIX THESE
   fullstring.assign_IS_NEGATIVE(0);

   prednextnode = NULL;
   assign_val(num);
   variablelist.set_first(NULL);
   variablelist.set_last(NULL);
   variablelist.set_num_entries(0);
   predicate_symbol.assign_symbol("");
//   fullstring.assign_symbol(full_s);

// PARSE INPUT FULL_STRING INTO APPROPRIATE FIELDS

     char              new_variable[STRING_LENGTH];
     variable_class   *var_ptr;
     char   *ptr; 
     int   token_num = 1;     
     char  instr[LONG_STRING_LENGTH];

  //INITIALIZE new_variable
  strcpy(instr, full_s);
  strcpy(new_variable, "");

  ptr = strtok( instr, "(,)" );  
  while (ptr != NULL)
     {
           if (token_num++ == 1)
                 predicate_symbol.assign_symbol(ptr);
           else {
                 strcpy(new_variable, ptr);
                 var_ptr = new variable_class(new_variable);
                 variablelist.add_ptr(var_ptr);
            } // ELSE

           ptr = strtok(NULL, ",)" );
     } //WHILE

//  ASSIGN FULL_STRING OBJECT FIELD
      int                num_args;
      char               fullstring2[LONG_STRING_LENGTH];

      strcat(fullstring2, predicate_symbol.get_predicate_symbol()); 
      strcat(fullstring2, "(");

      var_ptr = get_first_variable();      
      num_args = get_num_variables();
   
      for (int i = 0; i < num_args; i++) {

            strcat(fullstring2, var_ptr->get_variable_symbol());
            if (i != (num_args - 1)) {
                   strcat(fullstring2, ", ");
                   var_ptr = var_ptr->get_next_ptr();
              } //IF
              else
                     strcat(fullstring2, ")" );
      } // FOR
   fullstring.assign_symbol(fullstring2);

}  // ASSIGN_PREDICATE_EXPRESSION_INFO

//////////////////////////////////////////////////////////////////////////////



void predicate_expression_class::assign_val (int n)
  {
     node_class::assign_val(n);
  }

void predicate_expression_class::assign_IS_NEGATIVE(int neg_indicator)
  {
     IS_NEGATIVE = neg_indicator;
     fullstring.assign_IS_NEGATIVE(neg_indicator);
  }


void predicate_expression_class::output()
  {
     char    tempstr[LONG_STRING_LENGTH];
     
     cout << "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP\n";
     cout << "IS_NEGATIVE is ...........   " << IS_NEGATIVE << endl;
     cout << "Predicate_Expresssion value is.." << val << endl;
     cout << "Predicate String..." << predicate_symbol.get_predicate_symbol() << endl;
     cout << "Variable List is of "<< get_num_variables() << "..." << endl;
     variablelist.print();
     cout << "The display version:  ";
     display();
     cout << endl;
     cout << "The pointer to the next predicate_expression is .." << prednextnode << endl;
     cout << "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP\n";

  } 

void predicate_expression_class::clear()
  {
   prednextnode = NULL;
   variablelist.set_first(NULL);
   variablelist.set_last(NULL);
   variablelist.set_num_entries(0);
   predicate_symbol.assign_symbol("");
   fullstring.assign_symbol("");
  }


void predicate_expression_class::assign_predicate_symbol(char pred_symb[STRING_LENGTH])       
  {
     predicate_symbol.assign_symbol(pred_symb);
  }

void predicate_expression_class::assign_fullstring(char full_s[LONG_STRING_LENGTH])       
  {
  
      char      inchar;
      int       i = 0;
      char      tempstr[LONG_STRING_LENGTH];
      
     // COMVERT ALL VARABLE SYMBOLS TO UPPER CASE

      //ADVANCE TO '('
      while (full_s[i] != '(')  { 
         tempstr[i] = full_s[i];
         i++;
      } //WHILE
      tempstr[i] = full_s[i];  i++;
      
      //ADVANCE TO '\0'
      while (full_s[i] != '\0')  { 
         tempstr[i] = toupper(full_s[i]);
         i++;
      } //WHILE
      tempstr[i] = '\0';

    fullstring.assign_symbol(tempstr);

  }


void predicate_expression_class::assign_next(predicate_expression_class *pred_ptr)
  {
     prednextnode = pred_ptr;
  }

predicate_expression_class  *predicate_expression_class::get_next_ptr()
  {
      return prednextnode; 
  }
     

int predicate_expression_class::get_pred_val()
{
     return val;
}
int predicate_expression_class::get_IS_NEGATIVE()
{
     return IS_NEGATIVE;
}

char *predicate_expression_class::get_predicate_symbol()
{
    return predicate_symbol.get_predicate_symbol();
}

char *predicate_expression_class::get_fullstring()
{
    return fullstring.get_fullstring_symbol();
}


int predicate_expression_class::get_num_variables()
{
     return variablelist.get_num_entries();
}

variable_class *predicate_expression_class::get_first_variable()
{
     return variablelist.get_first();
}

void predicate_expression_class::display()
{
    fullstring.display();
}
void predicate_expression_class::display(ostream& fout)
{
    fullstring.display(fout);
}

int predicate_expression_class::get_position_of_variable_str
              (char var_str[STRING_LENGTH])  
{
     variable_class     *cur_var_ptr;
     char                cur_var_str[STRING_LENGTH];
     int                 found = 0;
    
     cur_var_ptr = get_first_variable(); 
     int current_position = 0;
     while ((cur_var_ptr != NULL) && (!found)){
           current_position++;
           strcpy(cur_var_str, cur_var_ptr->get_variable_symbol());
           if (strcmp(cur_var_str, var_str)==0) 
                   found = 1;
           else
                   cur_var_ptr = cur_var_ptr->get_next_ptr(); 

     }//WHILE

     return current_position;
     
}
