int        produce_hash_val(char instr[LONG_STRING_LENGTH], int instr_len);
char       *read_rule(istream& fin,
                   char readstr[EXTRA_LONG]);
void        show_rule(ostream& fout, char instr2[EXTRA_LONG]);       
void        extract_atom_strings(const char extensional_rule[EXTRA_LONG],
                                 list_class<fullstring_class>  *flist );    
char       *upper_string(char instr[STRING_LENGTH]);

void        clear_screen(int num_blank_lines);
void        display_menu();
int         equal_positions(position_class *source_pos_ptr,
                            position_class *dest_pos_ptr);
