#include "INDUC.H"

////////////////////////////////////////////////////////////////////////////
/// RANK ALGORITHM 7:  Rank Predicates by Coverage .. POS ONLY
/// ------------------------------------------------------------
///   For each predicate_log_class CUR_PREDLOG_OBJECT in BACKGROUND
///       For each positive example e+
///             If e+ is in CUR_PREDLOG_OBJECT mesh in any order,
///                      Rank(CUR_PREDLOG_OBJECT) ++
//////////////////////////////////////////////////////////////////////////////

void inductive_engine_class::rank_predicates_by_coverage_pos_only()
{
     constant_class        *example_cur_constant_ptr;
     constant_class        *cur_neighbor_c_ptr;
     atom_class            *cur_example_a_ptr;

     position_class        *example_cur_position_ptr;
     position_class        *cur_example_neighbor_position_ptr;
     position_class        *background_cur_position_ptr;
     predicate_log_class   *background_cur_predlog_ptr;
     int                    example_spot_number;
     int                    predlog_position_number;
     int                    num_total_predlog_positions;
     int                    chk_predlog_pos_number;
     int                    cur_predlog_spot;


                
        background_cur_predlog_ptr = get_first_background_predlog_ptr();

        while (background_cur_predlog_ptr != nullptr) {
             background_cur_predlog_ptr->mark_mesh_NOT_taken();

             // TRAVERSE POSITIVE EXAMPLE LIST TO UPDATE RANK
             cur_example_a_ptr = positive_examples->get_first_atom_ptr();        
             while (cur_example_a_ptr != nullptr) {

                if (background_cur_predlog_ptr->
                     is_member_of_mesh_any_order(cur_example_a_ptr)==1)
                          background_cur_predlog_ptr->increment_rank();
                cur_example_a_ptr = cur_example_a_ptr->get_next_ptr();          
             }// WHILE


             background_cur_predlog_ptr = background_cur_predlog_ptr->
                                get_next_ptr(); 
        } //WHILE there are more meshes in the BACK KNOW

} //RANK_PREDICATES_BY_COVERAGE_POS_ONLY




////////////////////////////////////////////////////////////////////////////
/// RANK ALGORITHM 8:  Rank Predicates by Coverage
/// -------------------------------------------------------
///   For each predicate_log_class CUR_PREDLOG_OBJECT in BACKGROUND
///       For each positive example e+
///             If e+ is in CUR_PREDLOG_OBJECT mesh in any order,
///                      Rank(CUR_PREDLOG_OBJECT) ++
///       For each negative example e- 
///             If e- is in CUR_PREDLOG_OBJECT mesh in any order,
///                      Rank(CUR_PREDLOG_OBJECT)--
//////////////////////////////////////////////////////////////////////////////

void inductive_engine_class::rank_predicates_by_coverage()
{
     constant_class        *example_cur_constant_ptr;
     constant_class        *cur_neighbor_c_ptr;
     atom_class            *cur_example_a_ptr;

     position_class        *example_cur_position_ptr;
     position_class        *cur_example_neighbor_position_ptr;
     position_class        *background_cur_position_ptr;
     predicate_log_class   *background_cur_predlog_ptr;
     int                    example_spot_number;
     int                    predlog_position_number;
     int                    num_total_predlog_positions;
     int                    chk_predlog_pos_number;
     int                    cur_predlog_spot;


                
        background_cur_predlog_ptr = get_first_background_predlog_ptr();

        while (background_cur_predlog_ptr != nullptr) {
             background_cur_predlog_ptr->mark_mesh_NOT_taken();

             // TRAVERSE POSITIVE EXAMPLE LIST TO UPDATE RANK
             cur_example_a_ptr = positive_examples->get_first_atom_ptr();        
             while (cur_example_a_ptr != nullptr) {

                if (background_cur_predlog_ptr->
                     is_member_of_mesh_any_order(cur_example_a_ptr)==1)
                          background_cur_predlog_ptr->increment_rank();
                cur_example_a_ptr = cur_example_a_ptr->get_next_ptr();          
             }// WHILE

             // TRAVERSE NEGATIVE EXAMPLE LIST TO UPDATE RANK
             cur_example_a_ptr = negative_examples->get_first_atom_ptr();        
             while (cur_example_a_ptr != nullptr) {

                if (background_cur_predlog_ptr->
                     is_member_of_mesh_any_order(cur_example_a_ptr)==1)
                          background_cur_predlog_ptr->decrement_rank();
                cur_example_a_ptr = cur_example_a_ptr->get_next_ptr();          
             }// WHILE


             background_cur_predlog_ptr = background_cur_predlog_ptr->
                                get_next_ptr(); 
        } //WHILE there are more meshes in the BACK KNOW

}  //RANK_PREDICATES_BY_COVERAGE

