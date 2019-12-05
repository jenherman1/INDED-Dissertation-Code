/////////////////////////////////////////////////////////////////////////////
//  Constructors
////////////////////////////////////////////////////////////////////////////
position_class::position_class()
{
   val = 0;
   posnextnode = NULL;
   variable_name = ' ';
   posrank = 0;
   position_chosen_flag = 0;
 }

position_class::position_class(int n)
{
   val = n;
   posnextnode = NULL;
   variable_name = ' ';
   posrank = 0;
   position_chosen_flag = 0;


}

position_class::~position_class(int n)
{
   val = 0;
   posnextnode = NULL;
   constantlist.cleanup();

}


void position_class::assign_val (int n)
  {
     val = n;
  }
void position_class::assign_posrank(int n)
  {
     posrank = n;
  }

void position_class::assign_variable_name (char letter)
  {
     variable_name = letter;
  }


void position_class::output()
  {
     
     cout << "=============<position_object>==================== \n";
     cout << "Val is  " << val << "      Ranked at:   "
             << get_posrank()  << endl;
     cout << "Variable name is   " << variable_name << endl;
     cout << "list of constants is :\n";
     constantlist.print();
     cout << "position nextnode is " << posnextnode << "\n"; 
     cout << "==============<position_object>=================== \n";
  } 

void position_class::clear()
 {
     constantlist.cleanup();
 }

void position_class::assign_next(position_class *b_ptr)
  {
     posnextnode = b_ptr;
  }

position_class  *position_class::get_next_ptr()
  {
      return posnextnode; 
  }
int position_class::get_value()
  {
     return val;
  }

int position_class::get_posrank()
  {
     return posrank;
  }

int position_class::get_position_chosen()
  {
     return   position_chosen_flag; 
  }
void position_class::increment_posrank()
{
    posrank++;
}
void position_class::mark_position_chosen()
{
     position_chosen_flag  = 1; 
}
void position_class::mark_position_unchosen()
{
     position_chosen_flag  = 0; 
}
void position_class::initialize_position_chosen()
{
     position_chosen_flag  = 0; 
}
void position_class::decrement_posrank()
{
    posrank--;
}
void position_class::increase_posrank(int increase_amount)
{
    posrank+=increase_amount;
}
void position_class::decrease_posrank(int decrease_amount)
{
    posrank-=decrease_amount;
}
void position_class::initialize_posrank()
{
    posrank = 0;
}
char position_class::get_variable_name()
  {
     return variable_name;
  }

void position_class::add_constant(char instr[STRING_LENGTH])
{
      constant_class  *c_ptr;
      c_ptr = new constant_class(instr);
      constantlist.add_ptr(c_ptr);
}
constant_class  *position_class::get_first_poscon_ptr()
{
     return (constantlist.get_first());
}


constant_class *position_class::find_constant(constant_class *source_c_ptr,
                                              int& found_spot)
{

    constant_class    *c_ptr;
    char               source_str[STRING_LENGTH];
    char               dest_str[STRING_LENGTH];
    int                found = 0;

    found_spot = 0;

    strcpy(source_str, source_c_ptr->get_constant_symbol());
    c_ptr = get_first_poscon_ptr();  //INITIALIZE TO FIRST CONSTANT IN POS LIST


    while ((c_ptr != NULL) && (!found)) {
        strcpy(dest_str, "");
        strcpy(dest_str, c_ptr->get_constant_symbol());
        if  ( strcmp(source_str, dest_str) == 0 ) {
                found = 1;

        } // IF
        else {
                 c_ptr = c_ptr->get_next_ptr();
        } //ELSE
        found_spot++;
    } //WHILE
    return c_ptr;
} //FIND_CONSTANT         


////////////////////////////////////////////////////////////////////////////////////////////////
constant_class *position_class::find_constant_taken(constant_class *source_c_ptr,
                                              int& found_spot)
{
         
    constant_class    *c_ptr;
    char               source_str[STRING_LENGTH];
    char               dest_str[STRING_LENGTH];
    int                found = 0;

    found_spot = 0;

    strcpy(source_str, source_c_ptr->get_constant_symbol());
    c_ptr = get_first_poscon_ptr();  //INITIALIZE TO FIRST CONSTANT IN POS LIST 


    while ((c_ptr != NULL) && (!found)) {
        strcpy(dest_str, "");
        strcpy(dest_str, c_ptr->get_constant_symbol());
        if  ( strcmp(source_str, dest_str) == 0 ) {
            if (!(c_ptr->is_taken())) {
                found = 1;
                c_ptr->mark_is_taken();
            }
            else {
                  c_ptr = c_ptr->get_next_ptr();  
            } //ELSE                
        } // IF
        else {
                 c_ptr = c_ptr->get_next_ptr();
        } //ELSE
        found_spot++;
    } //WHILE

    return c_ptr;
} //FIND_CONSTANT

///////////////////////////////////////////////////////////////////
///  Returns the spot number of constant if found, zero otherwise.
///////////////////////////////////////////////////////////////////
int position_class::is_a_member(constant_class *source_c_ptr) 
{
     constant_class  *found_ptr;
     int              new_spot;

     found_ptr = find_constant_taken(source_c_ptr, new_spot );
     if (found_ptr != NULL)
         return new_spot;
     else 
         return 0;
}
//////////////////////////////////////////////////////////////////////////
///  Returns a 1 if the constant symbol is found in the indicated spot.
///  Returns a 0 otherwise.
/////////////////////////////////////////////////////////////////////////
int position_class::is_a_member_in_spot(int             spot_number,
                                        constant_class *source_c_ptr) 
{
     constant_class  *dest_c_ptr;
     char             source_str[STRING_LENGTH];
     char             dest_str[STRING_LENGTH];

     strcpy(source_str, source_c_ptr->get_constant_symbol());

     dest_c_ptr = constantlist.get_ith(spot_number);
      
     if (dest_c_ptr != NULL) {
         strcpy(dest_str, dest_c_ptr->get_constant_symbol());

         //CHECK FOR EQUALITY
         if (strcmp(source_str, dest_str)==0) 
                return 1;
          else
                return 0;

     } // IF
     else  {
         return 0;
     } // ELSE

} // IS_A_MEMBER_IN_SPOT



/////////////////////////////////////////////////////////////////////////////////
///  Returns the number of times a constant source_c_ptr appears in position
/////////////////////////////////////////////////////////////////////////////////
int position_class::number_times_constant_found(constant_class *source_c_ptr)
{
         
    constant_class    *c_ptr;
    char               source_str[STRING_LENGTH];
    char               dest_str[STRING_LENGTH];
    int                num_times_found = 0;

    strcpy(source_str, source_c_ptr->get_constant_symbol());
    c_ptr = get_first_poscon_ptr();  //INITIALIZE TO FIRST CONSTANT IN POS LIST 


    while (c_ptr != NULL)  {
        strcpy(dest_str, "");
        strcpy(dest_str, c_ptr->get_constant_symbol());
        if  ( strcmp(source_str, dest_str) == 0 ) {
                 num_times_found++;
        } // IF
        c_ptr = c_ptr->get_next_ptr();
    } //WHILE

    return  num_times_found; 

} //NUMBER_TIMES_CONSTANT_FOUND
////////////////////////////////////////////////////////////////////////////////////////////////////////
///  returns the constant at  spot FIND_SPOT_NUMBER
////////////////////////////////////////////////////////////////////////////////////////////////////////
constant_class *position_class::get_constant_in_spot(int find_spot_number)
{
         
    constant_class    *c_ptr;
    char               source_str[STRING_LENGTH];
    char               dest_str[STRING_LENGTH];
    int                found = 0;

    return   constantlist.get_ith(find_spot_number);

} //GET_CONSTANT_AT_SPOT

////////////////////////////////////////////////////////////////////////////////////////////////////////
///  Initializes entire list to NOT TAKEN
////////////////////////////////////////////////////////////////////////////////////////////////////////
void  position_class::mark_all_constants_NOT_taken()
{
         
    constant_class    *c_ptr;

    c_ptr = get_first_poscon_ptr();           //INITIALIZE TO FIRST CONSTANT IN POS LIST 

    while (c_ptr != NULL)  {
        c_ptr->mark_NOT_taken();
        c_ptr = c_ptr->get_next_ptr();
    } //WHILE

} //MARK_ALL_CONSTANTS_NOT_TAKEN
