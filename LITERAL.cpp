#include <iostream>

#include "LITERAL.H"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
///   CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////////

literal_class::literal_class()
    {
       lnextnode = nullptr;
    }

literal_class::literal_class(int n)
    {
       val = n;
       lnextnode = nullptr;

    } 
literal_class::literal_class(int n, vertex_class *v_ptr, body_node_class *b_ptr)
    {
       lnextnode = nullptr;
       val = n;
       body_ptr = b_ptr;
       vertex_ptr = v_ptr;
    } 



///////////////////////////////////////////////////////////////////////////////
///     VIRTUALS FROM NODE_CLASS
//////////////////////////////////////////////////////////////////////////////
void literal_class::assign_val(int n)
    {
       //node_class::assign_val(n);
        val = n;
    }

int literal_class::get_value(){
    return val;
}


void literal_class::output()
    {
       cout << "....................................... \n";
       //node_class::output();
       cout << "val is " << val << "\n" ;

       cout << "vertex_pointer is " << vertex_ptr << "\n";
       cout << "literal nextnode is .. " << lnextnode << "\n";
       cout << "....................................... \n";
    }
void literal_class::clear()
    {
       //node_class::clear();
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
        vertex_ptr = v_ptr;
    }
void literal_class::assign_body_ptr(body_node_class *b_ptr)
    {
        body_ptr = b_ptr;
    }

vertex_class *literal_class::get_vertex_ptr()
    {
        return vertex_ptr;
    }
body_node_class  *literal_class::get_body_ptr()
    {
        return body_ptr;
    }
