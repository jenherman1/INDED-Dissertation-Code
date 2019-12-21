#pragma once

/////////////////////////////////////////////////////////////////////////
//  utility1.h  contains non-class c++ functions 
/////////////////////////////////////////////////////////////////////////

void       show_run_stats();
void       show_bulk_run_stats();
void       get_user_data();
int        get_random_val(int upper_bound);
float      get_include_prob();
int        determine_program_source();
void       get_user_bulk_data();
void       get_percent_preassigned();
void       get_number_preassigned();
int        lub_t(int tval1, int tval2);
int        glb_t(int tval1, int tval2);
int        lub_k(int tval1, int tval2);
