//_________________________________________________________________________
fullstring_class::fullstring_class()
{
   val = 0;
   fnextnode = NULL;
   IS_NEGATIVE = 0;
   strcpy(fullstring_symbol,"");
  }

//_________________________________________________________________________
fullstring_class::fullstring_class(int num)
{
   val = num;
   fnextnode = NULL;
   IS_NEGATIVE = 0;
   strcpy(fullstring_symbol,"");
  }

//_________________________________________________________________________

fullstring_class::fullstring_class(const char instr[LONG_STRING_LENGTH]) 
{
   char   *ptr;
   char   instr2[LONG_STRING_LENGTH];  

   val = 0;
   fnextnode = NULL;
   IS_NEGATIVE = 0;
  
   strcpy(instr2, instr);
   ptr = instr2;

   if (instr2[0] == '~') {
      IS_NEGATIVE = 1;
      ptr++;
                                     //      ptr = strtok(instr2, "~");
      strcpy(instr2, ptr);
   } // IF 

   strcpy(fullstring_symbol,instr2);
}

//_________________________________________________________________________

void fullstring_class::output()
  {
     cout << "^_^_^_^_^_^_^_^_^_^^^_^_^_^_^_^_^_^_^_^_\n";
     cout << "IS_NEGATIVE is...."  << IS_NEGATIVE << endl;
     cout << "Fullstring symbol is ";
     if (IS_NEGATIVE)
          cout << " ~ ";    
     cout  << fullstring_symbol << endl;
     cout << "The pointer to Next Constant (fnextnode) is: " << fnextnode << endl;
     cout << "^_^_^_^_^_^_^_^_^_^^^_^_^_^_^_^_^_^_^_^_\n";


  } 
//_________________________________________________________________________

void fullstring_class::clear()
  {
   fnextnode = NULL;
   strcpy(fullstring_symbol,"");
   IS_NEGATIVE = 0;
  }
//_________________________________________________________________________


void fullstring_class::assign_next(fullstring_class *f_ptr)
  {
     fnextnode = f_ptr;
  }
//_________________________________________________________________________

void fullstring_class::assign_IS_NEGATIVE(int neg_val)
  {
     IS_NEGATIVE = neg_val;
  }
//_________________________________________________________________________

void fullstring_class::assign_symbol(const char instr[LONG_STRING_LENGTH])
  {  

   char   *ptr;
   char   instr2[LONG_STRING_LENGTH];  

   IS_NEGATIVE = 0;
   strcpy(instr2, instr);
   ptr = instr2;

   if (instr2[0] == '~') {
      IS_NEGATIVE = 1;
      ptr++;
                                     //      ptr = strtok(instr2, "~");
      strcpy(instr2, ptr);
   } // IF 

   strcpy(fullstring_symbol,instr2);
}

//_________________________________________________________________________

fullstring_class  *fullstring_class::get_next_ptr()
  {
      return fnextnode; 
  }
//_________________________________________________________________________

int fullstring_class::get_value()
  {
      return 0;
  }
//_________________________________________________________________________


char *fullstring_class::get_fullstring_symbol()
  {
      return fullstring_symbol;
  }
//_________________________________________________________________________


int fullstring_class::get_IS_NEGATIVE()
  {
      return IS_NEGATIVE;
  }
//_________________________________________________________________________

void fullstring_class::display()
  {
     if (IS_NEGATIVE)
        cout << " ~ ";

     cout << fullstring_symbol;
  }
//_________________________________________________________________________
void fullstring_class::display(ostream& fout)
  {
     if (IS_NEGATIVE)
        fout << " ~ ";

     fout << fullstring_symbol;
  }
//_________________________________________________________________________
