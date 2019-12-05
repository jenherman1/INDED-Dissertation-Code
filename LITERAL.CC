///////////////////////////////////////////////////////////////////////////////
///   CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////////

literal_class::literal_class() : node_class()
    {
       lnextnode = NULL;
    }
literal_class::literal_class(node_class *v_ptr)
    {
       lnextnode = NULL;
    }
literal_class::literal_class(int n) : node_class(n)
    {
       lnextnode = NULL;

    } 
literal_class::literal_class(int n, vertex_class *v_ptr,
                                    body_node_class *b_ptr) : 
                                    node_class(n, v_ptr, b_ptr)
    {
       lnextnode = NULL;

    } 



///////////////////////////////////////////////////////////////////////////////
///     VIRTUALS FROM NODE_CLASS
//////////////////////////////////////////////////////////////////////////////
void literal_class::assign_val(int n)
    {
       node_class::assign_val(n);
    }


void literal_class::output()
    {
       cout << "....................................... \n";
       node_class::output();
       cout << "vertex_pointer is " << vertex_ptr << "\n";
       cout << "literal nextnode is .. " << lnextnode << "\n";
       cout << "....................................... \n";
    }
void literal_class::clear()
    {
       node_class::clear();
    }



///////////////////////////////////////////////////////////////////////////////
///     LITERAL NODE SPECIFIC MEMBER FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
void  literal_class::assign_next(literal_class *p_ptr)
{
    lnextnode = p_ptr;
}   

literal_class  *literal_class::get_next_ptr()
    {
        return lnextnode;
    } 


void literal_class::assign_vertex_ptr(vertex_class *v_ptr)
    {
        node_class::assign_vertex_ptr(v_ptr);
    }
void literal_class::assign_body_ptr(body_node_class *b_ptr)
    {
        node_class::assign_body_ptr(b_ptr);
    }

vertex_class *literal_class::get_vertex_ptr()
    {
        node_class::get_vertex_ptr();
    }
body_node_class  *literal_class::get_body_ptr()
    {
        node_class::get_body_ptr();
    }
