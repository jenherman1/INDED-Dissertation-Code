#pragma once

//  Possible Body status values
#define  UNDETERMINED 0;
#define  ELIMINATED   1;
#define  ALL_TRUE     2;
#define  TOPPED       3;

//  Possible truth values
#define  BOTTOM       2;       // Numbered this way to also use FALSE as a
#define  FALSE        0;       // value for other Boolean variables
#define  TRUE         1;
#define  TOP          3;

#define  Bottom       2;       // Numbered this way to also use FALSE as a
#define  False        0;       // value for other Boolean variables
#define  True         1;
#define  Top          3;

#define Total         1;      // Represent Spanning Tree stati 
#define NonTotal      0;      //
#define NonTotalPos   2;      //
#define NonTotalNeg   3;      //
#define Conflict      4;      //



//  Possible distributions on rule instance generation 
#define  NODIST             0;       // Causes mechanical loop driven instantiation
#define  FIXED_MAX_BODY_LEN 1;       // Rule bodies contain at most this
                                     //     many subgoals
#define  FIXED_BODY_LEN     2;       // Rule bodies contain exactly this many
                                     //     subgoals
#define  CONSTANT_PROB      3;       // Every variable appears as a subgoal
                                     //      with this probability
                             
//  Value used by random number generator to normalize return value
//  from rand()
#define RANDOM_SCALE        65535.0;

#define RATIO_LIMIT         5.2;

const   int    STRING_LENGTH = 1024;
const   int    LONG_STRING_LENGTH = 2048;
const   int    EXTRA_LONG = 2096;

const   double  EQUAL_FACTOR = 0.05; // % below which two positions are deemed equal
const   double  DEFAULT_SUFF = 0.30;
const   double  DEFAULT_NEC  = 0.25;
const   int     DEFAULT_POS_ALGO = 2;
const   int     DEFAULT_PREDRANK_ALGO = 4;
const   double  DEFAULT_INCONSISTENCY_COEF = 0.25;


const   int    NUM_LINES_CLEARSCREEN = 25;
const   int    NUM_LINES_HALFSCREEN = 6;
//call is clear_screen(NUM_LINES_HALFSCREEN)

