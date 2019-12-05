class node_class
    {
 public:
    node_class();
    node_class(node_class *node_cpy_ptr);
    node_class(int n);
    node_class(int n, vertex_class *v_ptr, body_node_class *b_ptr);


    virtual void      assign_val(int n);
    int               get_value();
    virtual void      output();
    virtual void      clear();


    void              assign_next(node_class *p_ptr);
    void              assign_vertex_ptr(vertex_class *v_ptr); 
    void              assign_body_ptr(body_node_class *b_ptr);

    node_class       *get_next_ptr();
    vertex_class     *get_vertex_ptr();
    body_node_class  *get_body_ptr();



 protected:
    int val;
    vertex_class    *vertex_ptr;
    body_node_class *body_ptr;
    node_class      *nextnode;
};
