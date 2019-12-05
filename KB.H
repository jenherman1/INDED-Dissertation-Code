class knowledge_base_class
{
   public:
        knowledge_base_class();
        knowledge_base_class(ifstream& edbfile, ifstream& idbfile);
        knowledge_base_class(ifstream& edbfile, ifstream& idbfile,
                             ifstream& learnfile);

        ~knowledge_base_class();


        void add_intensional_rule(intensional_rule_class *i_ptr);
        void add_intensional_rule(char new_rule[EXTRA_LONG]);
        void add_extensional_rule(char new_rule[EXTRA_LONG]);
        void add_cons_ptr(constant_class *c_ptr);
        void add_constant_edb(char instr[STRING_LENGTH]);     
        void add_constant_and_appearance(char instr[STRING_LENGTH],
                          vertex_class *vapp_ptr);     

        void add_predicate_expression(predicate_expression_class *pred_ptr);
        void add_predicate_expression(char full_s[LONG_STRING_LENGTH]);   

        void                             get_first_extensional_rule
                                            ( vertex_class *v_ptr,
                                             body_node_class *b_ptr);
        constant_class                   *get_first_constant();
        predicate_expression_class       *get_first_predicate_expression();
        intensional_rule_class           *get_first_intensional_rule();
        constant_class                   *find_constant(constant_class *source_c_ptr);

        void augment_ground_instantiation_ptr(intensional_rule_class *i_ptr);
        void augment_ground_instantiation(char new_intrule[EXTRA_LONG]);   
        void augment_GI_new_constant(constant_class *new_c_ptr);



        void add_fact_KB(istream& fin);
        void nonmonotonically_update(istream& fin);
        
                                       
        void output();
        void clear();
        void output_constants();
        void display_KB(ostream& fout);
        void display_constant_appearances(ostream& fout);
 
        void show_current_state(ostream& fout);
        void compute_current_state();
        void create_background_knowledge_file(char filename[STRING_LENGTH]);
        void create_ground_instantiation_file(char filename[STRING_LENGTH]);
        void create_intrule_set_file(char filename[STRING_LENGTH]);

  

 protected:

        void             initialize_instantiated_constant_ptrs
                                (intensional_rule_class *i_ptr);
        int              advance_instantiated_constant_ptrs(intensional_rule_class *i_ptr);
        char            *catenate_ground_rule(intensional_rule_class *i_ptr);
        constant_class  *get_inst_constant_ptr(intensional_rule_class *i_ptr,
                                            variable_class *source_var_ptr);
        int              new_constant_in_instantiation
                             (intensional_rule_class *i_ptr,
                              constant_class         *new_c_ptr);     

        logic_program_class                     *ground_instantiation;
        int_ruleset_class                       *IDB;
        list_class<predicate_expression_class>   predexplist;
        list_class<constant_class>               constantlist;
};
