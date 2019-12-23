project(INDED)

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

SET(SRC_LIST
        ATOM.cpp
        CONCLASS.cpp
        INDUC.cpp
        MAIN.cpp
        PREDLOG.cpp
        UTILITY.cpp
        BACK.cpp
        #EEEKS.cpp  # contains duplicate implementations of
                    # inductive_engine_class::rank_predicates_by_coverage_pos_only()
                    # and
                    # inductive_engine_class::rank_predicates_by_coverage()
        INTRULE.cpp
        LITERAL.cpp
        NODE.cpp
        PREDSYM.cpp
        VARIABLE.cpp
        BODY.cpp
        EXAMPSET.cpp
        INTSET.cpp
        LOGIC_PR.cpp
        POS.cpp
        RULE.cpp
        VERTEX.cpp
        CONAPP.cpp
        FULL.cpp
        KB.cpp
        LPCONS.CC       # source file that basically acts like a header file
        PREDEXP.cpp
        SPANTREE.cpp
        VERTPTR.cpp
        LIST.CC         # source file that basically acts like a header file
)

SET(CMAKE_INCLUDE_CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(${CMAKE_INCLUDE_CURRENT_DIR})

include_directories(${CMAKE_INCLUDE_CURRENT_DIR})

add_executable(${PROJECT_NAME} MAIN.cpp ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_directories(${PROJECT_NAME} BEFORE PUBLIC ${CMAKE_INCLUDE_CURRENT_DIR})
