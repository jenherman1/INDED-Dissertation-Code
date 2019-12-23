#include <iostream>

#include "RULE.H"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
///  Constructors
//////////////////////////////////////////////////////////////////////////////
rule_class::rule_class() : literal_class()
     {
         rnextnode = nullptr;
     }
rule_class::rule_class(int n) : literal_class(n)
     {
         rnextnode = nullptr;
     }
rule_class::rule_class(vertex_class *v_ptr, body_node_class *b_ptr)
    {
          val = 0;
          nextnode = nullptr;
          body_ptr = b_ptr;
          vertex_ptr = v_ptr;

          lnextnode = nullptr;
          rnextnode = nullptr;
    }
rule_class::rule_class(int rule_head, vertex_class *v_ptr, body_node_class *b_ptr)
    {
          val = rule_head; 
          nextnode = nullptr;
          body_ptr = b_ptr;
          vertex_ptr = v_ptr;

          lnextnode = nullptr;
          rnextnode = nullptr;
    }

int rule_class::get_value(){
    return val;
}

//////////////////////////////////////////////////////////////////////////////
///  Virtuals from NODE_CLASS
//////////////////////////////////////////////////////////////////////////////

void rule_class::assign_val(int n)
    {
       val = n;
    }

void rule_class::output()
    {
       cout << "------------------------------------------------ \n";
       //literal_class::output();

       cout << "....................................... \n";
       //node_class::output();
       cout << "val is " << val << "\n" ;

       cout << "vertex_pointer is " << vertex_ptr << "\n";
       cout << "literal nextnode is .. " << lnextnode << "\n";
       cout << "....................................... \n";

       cout << "body_pointer is " << body_ptr << "\n";
       cout << "rule_class nextnode is  " << rnextnode << "\n";
       cout << "------------------------------------------------ \n";


    }
void rule_class::clear()
    {
      //literal_class::clear();
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
