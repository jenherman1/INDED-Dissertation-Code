#include "UTILITY1.H"
#include "UTILITY2.H"
#include "VARIABLE.H"

//_________________________________________________________________________
variable_class::variable_class()
{
   val = 0;
   varnextnode = nullptr;
   instantiated_constant_ptr = nullptr;
   strcpy(variable_symbol,"");
  }

//_________________________________________________________________________
variable_class::variable_class(int num)
{
   val = num;
   varnextnode = nullptr;
   instantiated_constant_ptr = nullptr;
   strcpy(variable_symbol,"");
  }

//_________________________________________________________________________

variable_class::variable_class(char instr[STRING_LENGTH])
{
   // AUTOMATICAALY CONVERTS VARIABLE STRINGS TO UPPER CASE

   char   upper[STRING_LENGTH];

   val = 0;
   varnextnode = nullptr;
   instantiated_constant_ptr = nullptr;

   strcpy(upper,(upper_string(instr))  );
   strcpy(variable_symbol,upper);

}

//_________________________________________________________________________

void variable_class::output()
  {
     cout << "______________________________________________________________\n";
     cout << ".............................................................. \n";
     cout << "Variable VAL is.. " << val << endl;
     cout << "Variable symbol is ";
     cout  << variable_symbol << endl;
     cout << "Instantiated Constant Pointer is.. " << instantiated_constant_ptr
             << endl;
     cout << "The pointer to Next Variable (varnextnode) is: " << varnextnode << endl;
     cout << ".............................................................. \n";
     cout << "---------------------------------------------------------------- \n";



  } 
//_________________________________________________________________________

void variable_class::clear()
  {
   varnextnode = nullptr;
   instantiated_constant_ptr = nullptr;
   strcpy(variable_symbol,"");
  }
//_________________________________________________________________________


void variable_class::assign_next(variable_class *var_ptr)
  {
     varnextnode = var_ptr;
  }
//_________________________________________________________________________

void variable_class::assign_instantiated_constant_ptr(constant_class *c_ptr)
  {
     instantiated_constant_ptr = c_ptr;
  }
//_________________________________________________________________________


void variable_class::assign_symbol(char instr[STRING_LENGTH])
  {  
   // AUTOMATICAALY CONVERTS VARIABLE STRINGS TO UPPER CASE

   char   upper[STRING_LENGTH];
   strcpy(upper,(upper_string(instr))  );
   strcpy(variable_symbol,upper);

   }

//_________________________________________________________________________

variable_class  *variable_class::get_next_ptr()
  {
      return varnextnode; 
  }
//_________________________________________________________________________

int variable_class::get_value()
  {
      return 0;
  }
//_________________________________________________________________________


char *variable_class::get_variable_symbol()
  {
      return variable_symbol;
  }
//_________________________________________________________________________

constant_class *variable_class::get_instantiated_constant_ptr()
  {
      return instantiated_constant_ptr;
  }
//_________________________________________________________________________


void variable_class::display()
  {
     cout << variable_symbol;
  }
//_________________________________________________________________________

int variable_class::advance_instantiated_constant_ptr
                                 (constant_class *first_cons_ptr)
{
        int advance_next_var = 0; 

        instantiated_constant_ptr = 
           instantiated_constant_ptr->get_next_ptr();

        if (instantiated_constant_ptr == nullptr) {
               advance_next_var = 1;
               instantiated_constant_ptr = first_cons_ptr;
        } // IF

        return advance_next_var;
}

