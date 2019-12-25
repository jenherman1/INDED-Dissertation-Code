#pragma once

#include <fstream>

#include "CONST.H"
#include "FULL.H"
#include "LIST.CC"
#include "POS.H"
#include "VERTPTR.H"

int        produce_hash_val(char instr[LONG_STRING_LENGTH], int instr_len);
char       *read_rule(std::istream& fin, char readstr[EXTRA_LONG]);
void        show_rule(std::ostream& fout, char instr2[EXTRA_LONG]);
void        extract_atom_strings(const char extensional_rule[EXTRA_LONG],
                                 list_class<fullstring_class>  *flist );    
char       *upper_string(char instr[STRING_LENGTH]);

void        clear_screen(int num_blank_lines);
void        display_menu();
int         equal_positions(position_class *source_pos_ptr,
                            position_class *dest_pos_ptr);

static int                                Distribution;
static int                                Body_Length;
static int                                Max_Negative_Subgoals;
static int                                Num_Variables;
static int                                Intensional_Rule_Count = 0;
static float                              Rule_to_Var_Ratio;
static int                                Num_Rules;
static float                              Var_Prob;
static float                              Neg_Subgoal_Prob;
static int                                Source;
static std::fstream                            InputFile, OutputFile;
static int                                Num_Trials;
static float                              Ratio_Change_Increment;
static float                              Bodiless_Percent;
static int                                Num_Bodiless_Rules;
static float                              Preassign_True_Percent;
static float                              Preassign_False_Percent;
static int                                Num_Preassign_True;
static int                                Num_Preassign_False;
static int                                Current_Postorder_Val;
static list_class<vertex_ptr_class>       Q, Stack;
static int                                my_exit_status = 0;

static double                             SUFFICIENCY_STOP_CRITEREON =
                                         DEFAULT_SUFF;
static double                             NECESSITY_STOP_CRITEREON =
                                         DEFAULT_NEC;
