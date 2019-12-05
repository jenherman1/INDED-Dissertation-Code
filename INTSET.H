class int_ruleset_class
{
   public:
        int_ruleset_class();
        int_ruleset_class(ifstream& infile);
        int_ruleset_class(ifstream& infile, ifstream& learnfile);

  
        ~int_ruleset_class();

        void output();
        void add_rule(intensional_rule_class *i_ptr);
        void add_rule(char new_rule[EXTRA_LONG]);
    
        intensional_rule_class  *get_first_rule_ptr();
        
        void display(ostream& fout);
        void create_intrule_set_file(char filename[STRING_LENGTH]);        
  

 protected:
        list_class<intensional_rule_class>       intrulelist;

};
