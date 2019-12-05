node_class::node_class() 
   {
      val = 0;
      nextnode = NULL;
      vertex_ptr = NULL;
      body_ptr = NULL;
   }

node_class::node_class(int n)
   {
      val = n;
      nextnode = NULL;
      vertex_ptr = NULL;
      body_ptr = NULL;
   }
node_class::node_class(int n, vertex_class *v_ptr, body_node_class *b_ptr)
   {
      val = n;
      nextnode = NULL;
      vertex_ptr = v_ptr;
      body_ptr = b_ptr;
   }

///////////////////////////////////
//  assignment routines
//////////////////////////////////

void node_class::assign_val(int n)
   {
      val = n;
   }
void node_class::assign_next(node_class *p_ptr)
   {
      nextnode = p_ptr;
   }  

////////////////////////////////////
//  retrieval routines
////////////////////////////////////

int node_class::get_value()
   {
      return val;
   }
  
node_class *node_class::get_next_ptr()
   {
      return nextnode;
   }
vertex_class *node_class::get_vertex_ptr()
   {
      return vertex_ptr;
   }
body_node_class *node_class::get_body_ptr()
   {
      return body_ptr;
   }
void node_class::assign_vertex_ptr(vertex_class *v_ptr)
   {
      vertex_ptr = v_ptr;
   }
void node_class::assign_body_ptr(body_node_class *b_ptr)
   {
      body_ptr = b_ptr;
   }

////////////////////////////////////////
//  output routines
///////////////////////////////////////
void node_class::output()
   {
      cout << "val is " << val << "\n" ;
 //     cout << "nextnode is " << nextnode << "\n";
   };


/////////////////////////////////////////
//  Clean up routines
////////////////////////////////////////

void node_class::clear()
{
}
