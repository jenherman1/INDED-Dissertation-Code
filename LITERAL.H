class literal_class : public node_class
   {
  public:
     literal_class();
     literal_class(node_class *v_ptr);
     literal_class(int n, vertex_class *v_ptr, body_node_class *b_ptr);
     literal_class(int n);

     // VIRTUALS FROM NODE_CLASS
     void          assign_val(int n);
     void          output();
     void          clear();
                                 
     void           assign_next(literal_class *p_ptr);
     literal_class *get_next_ptr();
     vertex_class  *get_vertex_ptr();
     body_node_class *get_body_ptr();
     void           assign_vertex_ptr(vertex_class *v_ptr);
     void           assign_body_ptr(body_node_class *b_ptr);

  protected:
     literal_class  *lnextnode;
 };