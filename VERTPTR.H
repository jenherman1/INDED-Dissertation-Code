class vertex_ptr_class 
  {
  public:
      vertex_ptr_class();
      vertex_ptr_class(int n);
      vertex_ptr_class(int n, vertex_class *v_ptr);
      vertex_ptr_class(int n, vertex_class *v_ptr, body_node_class *b_ptr);

      void             assign_val(int n);
      void             assign_next(vertex_ptr_class *v_ptr);
      void             assign_graphspot(vertex_class *v_ptr);
      void             assign_bodyspot(body_node_class *b_ptr);

      vertex_class     *get_graphspot();
      vertex_ptr_class *get_next_ptr();
      int               get_value();
      body_node_class  *get_bodyspot();
   
      void              output();
      void              clear();

  protected:
      vertex_ptr_class                    *vpnext;
      int                                  val;
      vertex_class                        *graph_spot; 
      body_node_class                     *body_spot;
 };
 
