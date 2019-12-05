class spantree_class 
  {
  public:
      spantree_class();
      spantree_class(int n);
      spantree_class(int val, int start_truth);

      void output();
      void clear();

      void assign_vertval(int val);
      void assign_next(spantree_class *s_ptr);
      void assign_truth(int truth_v);
      void assign_status(int _v);
      void assign_conflict_val(int con_v);

      int get_truth();
      int get_status();
      int get_vertval();
      int get_value();
      int get_conflict_val();
      spantree_class *get_next_ptr();

      void  determine_status();



      int             is_conflict();
      int             is_total();
      int             is_nontotal_with_only_pos_edges();
      int             is_nontotal_with_only_neg_edges();
      int             is_nontotal_with_both();


  protected:
      spantree_class                    *snextnode;
      int                                vertval;
      int                                truth_val;
      int                                conflict_val;
      int                                status;
 };
 
