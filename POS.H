class position_class 
   {
  public:
      friend int  equal_positions(position_class *source_pos_ptr,
                                  position_class *dest_pos_ptr);

      position_class();
      position_class(int n);

     ~position_class();

      void output();
      void clear();

      void assign_val(int n);
      void assign_posrank(int n);
      void assign_next(position_class *b_ptr);
      void assign_variable_name(char letter);

      position_class *get_next_ptr();
      int             get_value();
      char            get_variable_name();
      int             get_posrank();
      int             get_position_chosen();

      constant_class       *get_first_poscon_ptr();
      void                  add_constant(char instr[STRING_LENGTH]);  
      constant_class       *find_constant(constant_class *source_c_ptr,
                                          int& found_spot);
      constant_class       *find_constant_taken(constant_class *source_c_ptr,
                                          int& found_spot);

      constant_class       *get_constant_in_spot(int find_spot_number);
      int                   is_a_member(constant_class *source_c_ptr);
      int                   is_a_member_in_spot(int             spot_number,
                                                constant_class *source_c_ptr);
      int                   number_times_constant_found(constant_class *source_c_ptr); 
      void                  mark_all_constants_NOT_taken();

      void                 increment_posrank();
      void                 decrement_posrank();
      void                 increase_posrank(int increase_amount);
      void                 decrease_posrank(int decrease_amount);
      void                 initialize_posrank(); 

      void                 mark_position_chosen();
      void                 initialize_position_chosen();
      void                 mark_position_unchosen();

  protected:
      position_class                 *posnextnode;
      int                             val;     //  POSITION NUMBER OF ARGUMENT
      int                             posrank;
      int                             position_chosen_flag;
      list_class<constant_class>      constantlist;
      char                            variable_name;
};
