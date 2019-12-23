#include <iostream>

#include "VERTPTR.H"

/////////////////////////////////////////////////////////////////////
///      Constructors
/////////////////////////////////////////////////////////////////////

using namespace std;
vertex_ptr_class::vertex_ptr_class()
   { 
      vpnext = nullptr;
      val = 0;
      graph_spot = nullptr;
      body_spot = nullptr;
   }
vertex_ptr_class::vertex_ptr_class(int n) 
   {
      vpnext = nullptr;
      val = n;
      graph_spot = nullptr;
      body_spot = nullptr;
   }
vertex_ptr_class::vertex_ptr_class(int n, vertex_class *v_ptr)
   {
      vpnext = nullptr;
      val = n;
      graph_spot = v_ptr;
      body_spot = nullptr;
   }

vertex_ptr_class::vertex_ptr_class(int n, vertex_class *v_ptr, 
                  body_node_class *b_ptr)        
   {
      vpnext = nullptr;
      val = n;
      graph_spot = v_ptr;
      body_spot = b_ptr;
   }


void vertex_ptr_class::assign_next(vertex_ptr_class *v_ptr)
 {
       vpnext = v_ptr;
 }

void vertex_ptr_class::assign_val(int n)
 {
       val = n;
 }
void vertex_ptr_class::assign_graphspot(vertex_class *v_ptr)
 {
       graph_spot = v_ptr;
 }
void vertex_ptr_class::assign_bodyspot(body_node_class *b_ptr)
 {
       body_spot = b_ptr;

 }


///////////////////////////////////////////////////

vertex_class  *vertex_ptr_class::get_graphspot()
 {
       return graph_spot;
 }

body_node_class   *vertex_ptr_class::get_bodyspot()
 {
       return body_spot;
 }



int vertex_ptr_class::get_value()
 {
       return val;
 }

vertex_ptr_class  *vertex_ptr_class::get_next_ptr()
 {
       return vpnext;
 }


/////////////////////////////////////////////////////
void vertex_ptr_class::output()
  {
       cout << "X X X X X X X X X X X X X X X X  \n";
       cout << "val is ...   "  << val << "\n";
       cout << "graph_spot is ...   "  << graph_spot << "\n";
       cout << "body_spot is.... " << body_spot << "\n";
       cout << "vpnext is ...   "  << vpnext << "\n";
       cout << "X X X X X X X X X X X X X X X X  \n";
  }

void vertex_ptr_class::clear()
{
}

