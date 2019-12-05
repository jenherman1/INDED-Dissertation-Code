class vertex_class : public node_class
  {
  public:
      vertex_class();
      vertex_class(int n);
      vertex_class(char f_str[LONG_STRING_LENGTH], int num);
      vertex_class(char f_str[LONG_STRING_LENGTH], int num,
                   int is_negative_val);


      void assign_val(int n);
      void output();
      void clear();

      void assign_next(vertex_class *v_ptr);
      vertex_class *get_next_ptr();
//      int get_value();


      void add_pos_appearance(rule_class *p_ptr);
      void add_neg_appearance(rule_class *p_ptr);
      void add_pos_appearance(int  head_val,
                              vertex_class *v_ptr, body_node_class *b_ptr);
      void add_pos_appearance(vertex_class *v_ptr, body_node_class *b_ptr);
      void add_neg_appearance(vertex_class *v_ptr, body_node_class *b_ptr);
      void add_neg_appearance(int  head_val,
                              vertex_class *v_ptr, body_node_class *b_ptr);

      void add_body(body_node_class *b_ptr);
      void assign_truth(int truth_v);
      void assign_J_val(int jval);
      void assign_W_val(int wval);
      void assign_access(int acc_v);
      void assign_guess(int g);
      void assign_postorder_num(int n);
      void assign_atominfo(char full_s[LONG_STRING_LENGTH]);
      void assign_atom(atom_class newatom);

      int get_truth();
      int get_J_val();
      int get_W_val();
      int get_access();
      int get_guess();
      int get_postorder_num();
      char           *get_atominfo();
      constant_class *get_first_atom_constant();
      char           *get_predicate_symbol();

      int visited();
      void mark();
      body_node_class *get_first_body();
      rule_class      *get_first_pos_appearance();
      rule_class      *get_first_neg_appearance(); 

// ------  WF 4 value ------------//

      int             determine_new_J_val(logic_program_class *P);

      int             no_head_appearance();
      int             has_negative_appearances();
      int             has_positive_appearances();
      void            print_postorder_num();



  protected:
      vertex_class                    *vnextnode;
      atom_class                       atominfo;
      int                              truth_val;
      int                              J_val;            //CREDIBILITY
      int                              W_val;
      int                              guess;
      int                              access;
      int                              postorder_num;
      list_class<body_node_class>      bodylist;
      list_class<rule_class>           pos_appearances;
      list_class<rule_class>           neg_appearances; 
 };
 
