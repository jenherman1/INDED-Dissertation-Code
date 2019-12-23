#pragma once

#include <iostream>

using namespace std;

template <class T> 
class list_class
    {

 protected:
      int    num_entries;
      T      *first;
      T      *last;

 public:
////////////////////////////////////////////////////////////////////
//   CONSTRUCTORS
////////////////////////////////////////////////////////////////////
   list_class() 
      {
       num_entries = 0;
       first = nullptr;
       last = nullptr;
       } 


   list_class(T *first_node_ptr)
   {
       first = first_node_ptr;
       last = first_node_ptr;
       num_entries = 1;
   }

void initialize()
   {
       first = nullptr;
       last = nullptr;
       num_entries = 0;
   }

////////////////////////////////////////////////////////////////////
//  OUTPUT ROUTINES 
////////////////////////////////////////////////////////////////////
void print()
   {
        T *p_ptr;
        
        cout << "List has " << num_entries << ":\n";
        p_ptr = first;
        while (p_ptr != nullptr)  {
             p_ptr->output();
             p_ptr = p_ptr->get_next_ptr();
        } // WHILE
      cout << "-------------------------------------------------------- \n";
      cout  << "\n";
   }  // PRINT


////////////////////////////////////////////////////////////////////////
//    Frees storage dynamic storage associated with list.
////////////////////////////////////////////////////////////////////////



void cleanup()
{
    T *p_ptr, *q_ptr;

        if (first == nullptr)
             return;

        p_ptr = (first->get_next_ptr());
        q_ptr = first;

        while (p_ptr != nullptr) {
             q_ptr->clear();
             delete q_ptr;
             num_entries--;
             q_ptr = p_ptr;
             p_ptr = (p_ptr->get_next_ptr());
        } // WHILE

            q_ptr->clear();
            delete q_ptr;
            num_entries--;
            first = nullptr;
} //CLEANUP
       


//////////////////////////////////////////////////////////////////////
//     ADDS A NODE INDICATED BY INCOMING PNTR PARM TO END OF THE LIST
//////////////////////////////////////////////////////////////////////


void add_ptr(T *node_ptr)
   {
        num_entries++;

        if (first==nullptr){
            first = node_ptr;
            last = node_ptr; 
        } // IF
        else {
            last->assign_next(node_ptr);
            last = node_ptr;

        } // ELSE
   } // ADD


////////////////////////////////////////////////////////////////////
//  ADDS A NODE WITH HOUSING THE INPUT PARM VAL TO THE END OF LIST 
////////////////////////////////////////////////////////////////////


void add_val(int add_value)
   {
        T *p_ptr;
        p_ptr = new T(add_value);
        p_ptr->output();
        add_ptr(p_ptr);
   }
        
/////////////////////////////////////////////////////////////////
//    REMOVES ALL NODES WITH THE SPECIFIED VALUE FROM THE LIST
/////////////////////////////////////////////////////////////////

void remove_node(int remove_val)
   {
    T *p_ptr, *q_ptr;

        if (first == nullptr)
             return;
        
     
      // ELIMINATE ALL INSTANCES OF THE VALUE FROM THE PREFIX OF THE LIST
        while ((first != nullptr) && (first->get_value() == remove_val)) {
             first = first->get_next_ptr();
             num_entries--;
        }  //WHILE

      // ELIMINATE THE VALUE FROM THE LIST AND ITS SUFFIX 
          p_ptr = first->get_next_ptr();
          q_ptr = first;
          while (p_ptr != nullptr)  {
                if (p_ptr->get_value() == remove_val) {
                      if (p_ptr == last) 
                          last = q_ptr;
                      q_ptr->assign_next( p_ptr->get_next_ptr());
                      num_entries--;
                 } // IF
                 else {
                     q_ptr = p_ptr;
                 } // ELSE

                 p_ptr = p_ptr->get_next_ptr();
           } //WHILE          
   }  // REMOVE_NODE 


//////////////////////////////////////////////////////////////////
//   REMOVES THE ONE NODE SPECIFIED BY INCOMING POINTER PARM
/////////////////////////////////////////////////////////////////

void remove_node(T *remove_ptr)
   {
    T *p_ptr, *q_ptr;

        if (first == nullptr)
             return;

        p_ptr = first->get_next_ptr();
        q_ptr = first;
        while (p_ptr != nullptr) {
           if (p_ptr == remove_ptr) {
               if (p_ptr == last)
                    last = q_ptr;
               q_ptr->assign_next(p_ptr->get_next_ptr());
               num_entries--;
               delete(p_ptr);
           } //IF
           else
               q_ptr = p_ptr;
           
           p_ptr = q_ptr->get_next_ptr();
        }  //WHILE
   } //REMOVE_NODE

////////////////////////////////////////////////////////////////////
/// Dequeues first element off of list.
///////////////////////////////////////////////////////////////////
T *dequeue()
{
    T    *p_ptr;

    if (first == nullptr)
        return nullptr;
    else {
        p_ptr = first;
        first = first->get_next_ptr();
        num_entries--;
        return p_ptr;

    } // ELSE
} // Dequeue

////////////////////////////////////////////////////////////////////
/// Inserts an element on the head of the list...Top of Stack
///////////////////////////////////////////////////////////////////

void push(T *node_ptr)
   {
        num_entries++;

        node_ptr->assign_next(first);
        if (first==nullptr){
            first = node_ptr;
            last = node_ptr; 
        } // IF
        else {
            first = node_ptr;
        } // ELSE
    } // Push



////////////////////////////////////////////////////////////////////
/// Pops first element off the Top of list/stack.
///////////////////////////////////////////////////////////////////
T *pop()
{
    T    *p_ptr;

    if (first == nullptr)
        return nullptr;
    else {
        p_ptr = first;
        first = first->get_next_ptr();
        num_entries--;
        return p_ptr;

    } // ELSE
} // POP 

/////////////////////////////////////////////////////////////////////
///  Returns a pointer to the Top of Stack...does not change stack
/////////////////////////////////////////////////////////////////////
T *stack_top()
{
   return first;
}


////////////////////////////////////////////////////////////////////
//  RETURNS A PNTR TO THE FIRST,LAST, AND iTH  ELEMENTS OF THE LIST
////////////////////////////////////////////////////////////////////
T *get_first()
  {
       return first ;
   }

T *get_last()
   {
       return last ;
   }

T *get_ith(int i)
   {
     int j = 1;
     T *p_ptr;

     p_ptr = first;
  
     while ((p_ptr != nullptr) && (j < i)) {
           p_ptr = p_ptr->get_next_ptr();
           j++;
     } // WHILE

     return p_ptr ;
   } // GET_ITH




////////////////////////////////////////////////////////////////////
//  RETURNS LENGTH OF THE LIST
////////////////////////////////////////////////////////////////////
int get_length()
   {
       return num_entries;
   }


//////////////////////////////////////////////////////////////////////
//  RETURNS A POINTER TO THE FIRST NODE CONTAINING INPUT PARM find_val
//////////////////////////////////////////////////////////////////////
T  *find_val_ptr(int find_val)
  {
         T *p_ptr, *q_ptr;
          p_ptr = first;
          while ((p_ptr != nullptr) && ((p_ptr->get_value()) != find_val))
                 p_ptr = p_ptr->get_next_ptr();
          if (p_ptr==nullptr)
              return nullptr;
          else      
               return p_ptr;
   } 

///////////////////////////////////////////////////////////////////////////
//  Search the list for find_val.  If it exists, the pointer is returned.
//  If not, a node is created with find_val, the that pointer is returned.
///////////////////////////////////////////////////////////////////////////

T  *find_add_val_ptr(int find_val)
  {
         T *p_ptr, *q_ptr;
            int  temp;

            p_ptr = first;

        while ((p_ptr != nullptr) && ((p_ptr->get_value()) != find_val))
        {
            p_ptr = p_ptr->get_next_ptr();
        }  // WHILE

        if (p_ptr==nullptr) {
              p_ptr = new T(find_val);
              add_ptr(p_ptr);
        } // IF
        
        return p_ptr;
   } // FIND_ADD_VAL_PTR

void set_first(T *p_ptr)
{
   first = p_ptr;
}


void set_last(T *p_ptr)
{
    last = p_ptr;
}

void set_num_entries(int num)
{
   num_entries = num;
}


int get_num_entries()
{
   return num_entries;
}


}; // LIST_CLASS TEMPLATE
