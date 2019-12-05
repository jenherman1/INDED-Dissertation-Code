//////////////////////////////////////////////////////////////////////////////
///  Constructors
//////////////////////////////////////////////////////////////////////////////
rule_class::rule_class() : literal_class()
     {
         rnextnode = NULL;
     }
rule_class::rule_class(int n) : literal_class(n)
     {
         rnextnode = NULL;
     }
rule_class::rule_class(vertex_class *v_ptr, body_node_class *b_ptr)
    {
          val = 0;
          nextnode = NULL;
          body_ptr = b_ptr;
          vertex_ptr = v_ptr;

          lnextnode = NULL;
          rnextnode = NULL;
    }
rule_class::rule_class(int rule_head, vertex_class *v_ptr, body_node_class *b_ptr)
    {
          val = rule_head; 
          nextnode = NULL;
          body_ptr = b_ptr;
          vertex_ptr = v_ptr;

          lnextnode = NULL;
          rnextnode = NULL;
    }


//////////////////////////////////////////////////////////////////////////////
///  Virtuals from NODE_CLASS
//////////////////////////////////////////////////////////////////////////////

void rule_class::assign_val(int n)
    {
       literal_class::assign_val(n);
    }

void rule_class::output()
    {
       cout << "------------------------------------------------ \n";
       literal_class::output();
       cout << "body_pointer is " << body_ptr << "\n";
       cout << "rule_class nextnode is  " << rnextnode << "\n";
       cout << "------------------------------------------------ \n";


    }
void rule_class::clear()
    {
      literal_class::clear();
    }
   
//////////////////////////////////////////////////////////////////////////////
///  RULE_CLASS Specific Member Functions
//////////////////////////////////////////////////////////////////////////////

void rule_class::assign_next(rule_class *p_ptr)
   {
         rnextnode = p_ptr;
   }

rule_class  *rule_class::get_next_ptr()
   {
          return rnextnode;
   }

void rule_class::assign_body_ptr(body_node_class *b_ptr)
    {
          body_ptr = b_ptr;
    }
body_node_class *rule_class::get_body_ptr()
    {
          return body_ptr;
    }
vertex_class *rule_class::get_vertex_ptr()
    {
          return vertex_ptr;
    }
