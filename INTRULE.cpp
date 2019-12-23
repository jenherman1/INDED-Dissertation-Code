#include <iostream>

#include "INTRULE.H"
#include "UTILITY2.H"

using namespace std;

/////////////////////////////////////////////////////////////////////
///      Constructors
/////////////////////////////////////////////////////////////////////

intensional_rule_class::intensional_rule_class()
   { 
      val = 0;
      inextnode = nullptr;
      variablelist.set_first(nullptr);
      predexplist.set_first(nullptr);

   }
intensional_rule_class::intensional_rule_class(int n)
   {
       val = 0;
       inextnode = nullptr;
       variablelist.set_first(nullptr);
       predexplist.set_first(nullptr);

   }

intensional_rule_class::intensional_rule_class(char f_str[EXTRA_LONG])
   {

       fullstring_class               *f_ptr;
       char                            full_string[EXTRA_LONG];
       list_class<fullstring_class>   *flist; 
       char                            tempstr[LONG_STRING_LENGTH];
       char                            tempvarstr[STRING_LENGTH];

       predicate_expression_class      *pred_ptr;
       variable_class                  *var_ptr;


       variablelist.set_first(nullptr);
       predexplist.set_first(nullptr);
       val = Intensional_Rule_Count++;
       inextnode = nullptr;

       strcpy(full_string, f_str);

      // CREATE A LIST OF FULLSTRING VERSIONS OF INTENSIONAL RULE'S PREDICATE Exp 
        flist = new list_class<fullstring_class>();
        extract_atom_strings(full_string, flist);
     

      //  CREATE LIST OF PREDICATE EXPRESSIONS
        f_ptr = flist->get_first();


        while (f_ptr != nullptr)  {
            strcpy(tempstr, "");
            strcpy(tempstr, (f_ptr->get_fullstring_symbol())  );
            pred_ptr = new predicate_expression_class(tempstr);
            pred_ptr->assign_IS_NEGATIVE(f_ptr->get_IS_NEGATIVE());
            predexplist.add_ptr(pred_ptr);
            f_ptr = f_ptr->get_next_ptr();
        } //WHILE

        
   // CREATE LIST OF VARIABLES USED IN ALL RULE'S PRED EXPRESSIONS
       pred_ptr = get_first_predexp_ptr();

       while (pred_ptr != nullptr) {
              var_ptr =  pred_ptr->get_first_variable(); 

              while (var_ptr != nullptr) {
                  strcpy(tempvarstr, (var_ptr->get_variable_symbol()) );
                  add_variable(tempvarstr);
                  var_ptr = var_ptr->get_next_ptr();
              } //WHILE MORE VARS
              pred_ptr = pred_ptr->get_next_ptr();

       } //WHILE MORE PRED EXPS

    flist->cleanup();
    
   } // CONSTRUCTOR



void intensional_rule_class::output()
  {
     cout << "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n";
     cout << "The PREDICATELIST is...\n";
     predexplist.print();
     cout << "val is " << val <<  "\n";

     cout << "the list of variables used is...\n";
     variablelist.print();

     cout << "The fullstring version of this rule is..";
     display_intensional_rule(cout);
     cout << endl;
     cout << "this intensional rule nextnode is " << inextnode << "\n"; 
     cout << "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n";


  } 


void intensional_rule_class::clear()
{
   predexplist.cleanup();
   variablelist.cleanup();
}


void intensional_rule_class::display_intensional_rule(ostream& fout)
{
     predicate_expression_class  *pred_ptr;

     pred_ptr = get_first_predexp_ptr();

     // DISPLAY INTENSIONAL HEAD
     if (pred_ptr->get_IS_NEGATIVE()==1)
         fout << '~';
     fout << (pred_ptr->get_fullstring());
     fout << " <-- ";
     pred_ptr = pred_ptr->get_next_ptr();

     // DISPLAY BODY
     while (pred_ptr != nullptr) {
         if (pred_ptr->get_IS_NEGATIVE()==1)
             fout << '~';

         fout << (pred_ptr->get_fullstring());
         pred_ptr = pred_ptr->get_next_ptr();
         if (pred_ptr != nullptr) {
               fout << ", \n";
               fout << "                           "; 
         } //IF
     } //WHILE there are more subgoals
     fout << " . \n";
} // DISPLAY_INTENSIONAL_RULE


void intensional_rule_class::assign_val (int n)
 {
      val = n;
 }


void intensional_rule_class::assign_next(intensional_rule_class *i_ptr)
 {
       inextnode = i_ptr;
 }


intensional_rule_class  *intensional_rule_class::get_next_ptr()
 {
       return inextnode;
 }

int intensional_rule_class::get_value()
 {
       return val;
 }

variable_class *intensional_rule_class::get_first_variable_ptr()
 {
       return variablelist.get_first();
 }

predicate_expression_class *intensional_rule_class::get_first_predexp_ptr()
 {
       return (predexplist.get_first());
 }


void intensional_rule_class::add_var_ptr(variable_class *var_ptr)
{
        variablelist.add_ptr(var_ptr);
}

void intensional_rule_class::add_variable(char var_str[STRING_LENGTH])
{
        variable_class  *cur_var_ptr;
        char             tempstr[STRING_LENGTH];
        int              found = 0;

//cout << "inside ADD_VARIABLE" << endl;
//cout << "variable to add via input par..." << var_str << endl;
//cout << "The current variablelist inside intensional_rule_class is..";
//variablelist.print();
        cur_var_ptr = variablelist.get_first();
//cout << "cur_var_ptr points to list on which to add:..." << cur_var_ptr << endl;

        
        while ((cur_var_ptr != nullptr) && (!found)) {

               strcpy(tempstr, (cur_var_ptr->get_variable_symbol()) );
               if ( (strcmp(var_str,tempstr)) == 0 )
                        found = 1;
               cur_var_ptr = cur_var_ptr->get_next_ptr(); 
        } //WHILE
//cout << "after while... found is.." << found << endl;

        // IF VARIABLE IS NOT IN LIST, CREATE ONE AND ADD IT
        if (!found) {

               cur_var_ptr = new variable_class(var_str);
               add_var_ptr(cur_var_ptr); 
        } // IF
}


void intensional_rule_class::assign_intensional_rule(char f_str[EXTRA_LONG])
{


       fullstring_class               *f_ptr;
       char                            full_string[EXTRA_LONG];
       list_class<fullstring_class>   *flist; 
       char                            tempstr[LONG_STRING_LENGTH];
       char                            tempvarstr[STRING_LENGTH];

       predicate_expression_class      *pred_ptr;
       variable_class                  *var_ptr;


       variablelist.set_first(nullptr);
       predexplist.set_first(nullptr);
       val = Intensional_Rule_Count++;
       inextnode = nullptr;

       strcpy(full_string, f_str);

      // CREATE A LIST OF FULLSTRING VERSIONS OF INTENSIONAL RULE'S PREDICATE Exp 
        flist = new list_class<fullstring_class>();
        extract_atom_strings(full_string, flist);
     
cout << "Just created a list of fullstrings with...\n";
flist->print();

   //  CREATE LIST OF PREDICATE EXPRESSIONS
        f_ptr = flist->get_first();

//cout << "entering while where predicate_expression_classes created.. \n";

        while (f_ptr != nullptr)  {
            strcpy(tempstr, (f_ptr->get_fullstring_symbol())  );
//cout << "about to create a predicate_expression with string..." << tempstr << endl;
            pred_ptr = new predicate_expression_class(tempstr);
            pred_ptr->assign_IS_NEGATIVE(f_ptr->get_IS_NEGATIVE());
//cout << "the newly created predicate_exprssion_class is........\n";
//pred_ptr->output();
            predexplist.add_ptr(pred_ptr);
            f_ptr = f_ptr->get_next_ptr();
        } //WHILE

        
   // CREATE LIST OF VARIABLES USED IN ALL RULE'S PRED EXPRESSIONS
//cout << endl << endl << endl << endl;
//cout << "about to create a list of variables for this intensionalruelclass \n";
       pred_ptr = get_first_predexp_ptr();

       while (pred_ptr != nullptr) {
//cout << "top of WHILE.. \n";
//cout << "pred_ptr is pointing to...";
//pred_ptr->display();
//cout << endl;
              var_ptr =  pred_ptr->get_first_variable(); 
//cout << "the first variable of predicate: ";
//var_ptr->display();

              while (var_ptr != nullptr) {
                  strcpy(tempvarstr, (var_ptr->get_variable_symbol()) );

//cout << "the variable is now is tempvarstr which is.." << tempvarstr << endl;
                  add_variable(tempvarstr);
                  var_ptr = var_ptr->get_next_ptr();
              } //WHILE MORE VARS
              pred_ptr = pred_ptr->get_next_ptr();

       } //WHILE MORE PRED EXPS
       flist->cleanup();
} //ASSIGN_INTENSIONAL_RULE


void intensional_rule_class::add_predicate_exp_ptr( predicate_expression_class *p_ptr)
{
          predexplist.add_ptr(p_ptr);
}



void intensional_rule_class::add_predicate_exptression(char pred_str[LONG_STRING_LENGTH])
{
         predicate_expression_class       *pred_ptr;

         pred_ptr = new predicate_expression_class(pred_str);
         add_predicate_exp_ptr(pred_ptr);
}
