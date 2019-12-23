# INDED-Dissertation-Code
C++ code implementing a Non-monotonic Knowledge base serving an Inductive Logic Prog. ML system

# Installation
```
cmake CMakeLists.txt
make -Bj16
```

After installation, `./INDED` to launch `INDED` executable.

# Example

`./INDED`

```
Enter input file name of the EDB:
>SOAP.EDB

Enter input file name of the IDB:
>SOAP.IDB

       *********************************************************** 
       *                                                         * 
       *     N  -- Nonmonotonic Update of Pos or Neg FACT        * 
       *                                                         * 
       *     R  -- Add an INTENSIONAL RULE to IDB                * 
       *                                                         * 
       *     S  -- Compute Current STATE of Knowledge Base       * 
       *                                                         * 
       *     F  -- Create a FILE of current STATE                * 
       *                                                         * 
       *     G  -- Create a FILE of current GOUND INSTANTIATION  * 
       *                                                         * 
       *     I  -- Create a FILE of current INTENSIONAL RULES    * 
       *                                                         * 
       *     L  -- Learn a TARGET PREDICATE using Induction      * 
       *                                                         * 
       *     Q  -- QUIT                                          * 
       *                                                         * 
       *********************************************************** 
Enter menu choice for operation.  Enter 'Q' to quit.
>L

Enter input file name of the POSITIVE EXAMPLE Set:
>SOAP.POS

Enter input file name of the NEGATIVE EXAMPLE Set:
>SOAP.NEG

--------------------------------------------------------------------- 
 Enter Example Set Inconsistency Coefficient...
          (Max coefficient of tuples appearing in both E+ and E-) 
--------------------------------------------------------------------- 
>0.5

--------------------------------------------------------------------- 
 Choose Predicate Ranking Technique :  
      1 -- Simple Set Membership (Positives only..E+) 
      2 -- Simple Set Membership (Positives and Negatives ..E+ U E- 
      3 -- Greedy Set Membership (Positives only..E+) 
      4 -- Greedy Set Membership (Positives and Negatives ..E+ U E- 
      5 -- Spot Position Membership (Positives only..E+) 
      6 -- Spot Position Membership (Positives and Negatives ..E+ U E- 
      7 -- Example Neighbor Membership Single(Positives only..E+) 
      8 -- Example Neighbor Membership Single(Positives and Negatives ..E+ U E- 
      9 -- Example Neighbor Membership (Positives only..E+) 
     10 -- Example Neighbor Membership (Positives and Negatives ..E+ U E- 
--------------------------------------------------------------------- 
>10

--------------------------------------------------------------------- 
 Choose POSITION Ranking Technique :  
      1 -- Greedy Set Membership (Positives only..E+) 
      2 -- Greedy Set Membership (Positives and Negatives ..E+ U E- 
--------------------------------------------------------------------- 
>1

--------------------------------------------------------------------- 
 Enter Sufficiency Stopping Critereon...
          (Num Pos examples Covered / Total Num Pos examples 
--------------------------------------------------------------------- 
>0.5

--------------------------------------------------------------------- 
 Enter Necessity Stopping Critereon...
          (Num Neg examples Covered / Total Num Neg examples 
--------------------------------------------------------------------- 
>0.7

superior_soap(A) <-- ~max_amount_surfactant(A) . 
@@@@@@@@@@@@@@@@@@@@@@
Is this rule acceptable? (Y/N)
>N

--------------------------------------------------------------------- 
 Choose Predicate Ranking Technique :  
      1 -- Simple Set Membership (Positives only..E+) 
      2 -- Simple Set Membership (Positives and Negatives ..E+ U E- 
      3 -- Greedy Set Membership (Positives only..E+) 
      4 -- Greedy Set Membership (Positives and Negatives ..E+ U E- 
      5 -- Spot Position Membership (Positives only..E+) 
      6 -- Spot Position Membership (Positives and Negatives ..E+ U E- 
      7 -- Example Neighbor Membership Single(Positives only..E+) 
      8 -- Example Neighbor Membership Single(Positives and Negatives ..E+ U E- 
      9 -- Example Neighbor Membership (Positives only..E+) 
     10 -- Example Neighbor Membership (Positives and Negatives ..E+ U E- 
--------------------------------------------------------------------- 
>3

--------------------------------------------------------------------- 
 Choose POSITION Ranking Technique :  
      1 -- Greedy Set Membership (Positives only..E+) 
      2 -- Greedy Set Membership (Positives and Negatives ..E+ U E- 
--------------------------------------------------------------------- 
>1

--------------------------------------------------------------------- 
 Enter Sufficiency Stopping Critereon...
          (Num Pos examples Covered / Total Num Pos examples 
--------------------------------------------------------------------- 
>0.8

--------------------------------------------------------------------- 
 Enter Necessity Stopping Critereon...
          (Num Neg examples Covered / Total Num Neg examples 
--------------------------------------------------------------------- 
>0.0

superior_soap(A) <-- ~max_amount_surfactant(A) . 
@@@@@@@@@@@@@@@@@@@@@@
Is this rule acceptable? (Y/N)
>Y

Press 'c' to continue..

       *********************************************************** 
       *                                                         * 
       *     N  -- Nonmonotonic Update of Pos or Neg FACT        * 
       *                                                         * 
       *     R  -- Add an INTENSIONAL RULE to IDB                * 
       *                                                         * 
       *     S  -- Compute Current STATE of Knowledge Base       * 
       *                                                         * 
       *     F  -- Create a FILE of current STATE                * 
       *                                                         * 
       *     G  -- Create a FILE of current GOUND INSTANTIATION  * 
       *                                                         * 
       *     I  -- Create a FILE of current INTENSIONAL RULES    * 
       *                                                         * 
       *     L  -- Learn a TARGET PREDICATE using Induction      * 
       *                                                         * 
       *     Q  -- QUIT                                          * 
       *                                                         * 
       *********************************************************** 

>F
Enter new background file name.
>soap_example_background_file.txt

       *********************************************************** 
       *                                                         * 
       *     N  -- Nonmonotonic Update of Pos or Neg FACT        * 
       *                                                         * 
       *     R  -- Add an INTENSIONAL RULE to IDB                * 
       *                                                         * 
       *     S  -- Compute Current STATE of Knowledge Base       * 
       *                                                         * 
       *     F  -- Create a FILE of current STATE                * 
       *                                                         * 
       *     G  -- Create a FILE of current GOUND INSTANTIATION  * 
       *                                                         * 
       *     I  -- Create a FILE of current INTENSIONAL RULES    * 
       *                                                         * 
       *     L  -- Learn a TARGET PREDICATE using Induction      * 
       *                                                         * 
       *     Q  -- QUIT                                          * 
       *                                                         * 
       ***********************************************************
>Q
All Processes Successfully Completed! Quitting.
```