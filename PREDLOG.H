class predicate_log_class 
  {
  public:
      predicate_log_class();
      predicate_log_class(int n);
      predicate_log_class(atom_class *newatom);

      void assign_val(int n);
      void assign_next(predicate_log_class *v_ptr);

      void output();
      void clear();
      void display(ostream& fout);

      int                  get_value();
      int                  get_chosen();
      char                *get_predlog_symbol();
      int                  get_predlog_truthval();
      position_class      *get_first_pos_ptr();
      predicate_log_class *get_next_ptr();
      int                  get_num_positions();

      void add_position(position_class  *p_ptr);
      void add_new_atom(atom_class *newatom);
      int get_rank();
      int is_member_of_mesh(atom_class *a_ptr);
      int is_member_of_mesh_any_order(atom_class *a_ptr);


      int has_constant(constant_class *c_ptr);
      int has_constant_in_position(int position_num, constant_class *c_ptr);
      int has_constant_in_pos_spot(int position_num, 
                                   int spot_num, 
                                   constant_class *c_ptr); 
      void name_variables(char startletter);
      void verify_named_variables();
      void reset_rank();
      void increment_rank();
      void increase_rank(int increase_amount);
      void decrement_rank();
      void decrease_rank(int decrease_amount);

      void mark_mesh_NOT_taken();

      void mark_chosen();
      void reinitialize_chosen();
      int  is_chosen();

      void                initialize_position_ranks();
      void                initialize_position_chosen_flags();
      char                get_max_variable_name();
      position_class     *get_max_ranked_unchosen_position_ptr();
     


  protected:
      int                                     val;    //USED FOR RANKING
      int                                     chosen;
      predicate_symbol_class                 *predlogsymbol;
      int                                     truth_val;
      list_class<position_class>              constantposlist;
      predicate_log_class                    *predlognextnode;
 };
