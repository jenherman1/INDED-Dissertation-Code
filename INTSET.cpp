#include <fstream>

#include "INTSET.H"
#include "UTILITY2.H"

using namespace std;

int_ruleset_class::int_ruleset_class()
{
        intrulelist.set_first(nullptr);
        intrulelist.set_last(nullptr);
        intrulelist.set_num_entries(0);

} // CONSTRUCTOR for int_ruleset_class



///////////////////////////////////////////////////////////////////////////
///  Construct an intensional logic program by reading an input stream
///  of INTENSIONAL RULES
///////////////////////////////////////////////////////////////////////////
int_ruleset_class::int_ruleset_class(ifstream& infile)
{

char                      full_string[ EXTRA_LONG];
char                      gochar = '.';          
char                      tempstr[LONG_STRING_LENGTH];
intensional_rule_class   *i_ptr;


  // READ IN FIRST EXTENSIONAL RULE
   gochar = *read_rule(infile, full_string);

   while (gochar == '.') {
        i_ptr = new intensional_rule_class(full_string);
        intrulelist.add_ptr(i_ptr);
        gochar = *read_rule(infile, full_string);
   } // WHILE

} // CONSTRUCTOR for int_ruleset_class




///////////////////////////////////////////////////////////////////////////
///  Construct an intensional logic program by reading an input stream
///  of INTENSIONAL RULES from two files:  original IDB and learn file
///////////////////////////////////////////////////////////////////////////
int_ruleset_class::int_ruleset_class(ifstream& infile, ifstream& learnfile)
{

char                      full_string[ EXTRA_LONG];
char                      gochar = '.';          
char                      tempstr[LONG_STRING_LENGTH];
intensional_rule_class   *i_ptr;


  // READ IN FIRST EXTENSIONAL RULE
   gochar = *read_rule(infile, full_string);

   while (gochar == '.') {
        i_ptr = new intensional_rule_class(full_string);
        intrulelist.add_ptr(i_ptr);
        gochar = *read_rule(infile, full_string);
   } // WHILE


  // APPEND LEARNED INTENSIONAL RULES
   gochar = *read_rule(learnfile, full_string);

   while (gochar == '.') {
        i_ptr = new intensional_rule_class(full_string);
        intrulelist.add_ptr(i_ptr);
        gochar = *read_rule(learnfile, full_string);
   } // WHILE


} // CONSTRUCTOR for int_ruleset_class

//__________________________________________________________________________

int_ruleset_class::~int_ruleset_class()
{
        intrulelist.cleanup();
}

//__________________________________________________________________________
void int_ruleset_class::output()
{
      intrulelist.print();
}
//__________________________________________________________________________

void int_ruleset_class::add_rule(intensional_rule_class *i_ptr)
{
      intrulelist.add_ptr(i_ptr);
}
//__________________________________________________________________________
void int_ruleset_class::add_rule(char new_rule[EXTRA_LONG])
{
      intensional_rule_class  *i_ptr;       
 
      i_ptr = new intensional_rule_class(new_rule);
      intrulelist.add_ptr(i_ptr);
}

//__________________________________________________________________________
intensional_rule_class *int_ruleset_class::get_first_rule_ptr()
{
        return intrulelist.get_first();
}

//__________________________________________________________________________
void int_ruleset_class::display(ostream& fout)
{

     intensional_rule_class *i_ptr;

     i_ptr = intrulelist.get_first();

     while (i_ptr != nullptr)  {
           i_ptr->display_intensional_rule(fout);
           i_ptr = i_ptr->get_next_ptr();
            
     }//WHILE

     fout << "@@@@@@@@@@@@@@@@@@@@@@" << endl;
}

//////////////////////////////////////////////////////////////////////
///  Create External File.
//////////////////////////////////////////////////////////////////////
void int_ruleset_class::create_intrule_set_file
                         (char filename[STRING_LENGTH])
{                                                               
         ofstream   outfile;

         outfile.open(filename);
         display(outfile);
         outfile.close();
}
