/*
 * combinations header file
 * contains prototypes of functions
 */

#ifndef SIMULATORFORSPECTROSCOPICTERMS_COMBINATIONS_H
#define SIMULATORFORSPECTROSCOPICTERMS_COMBINATIONS_H


/*
 * compute the factorial of n
 * @precondition:   n >= 0
 * @postcondition:  factorial becomes n!
 */
unsigned long int factorial (unsigned int n);

/*
 * compute the number of combinations
 * @precondition:   k, l > 0
 * @postcondition:  combinations_k_l becomes l! / (k! * (l - k)!)
 */
unsigned int combinations_k_l (unsigned int k, unsigned int l);

/*
 * computes the possibilities for a combination (wrapper of combinations_k_l)
 * @precondition:   k, l > 0
 * @postcondition:  combinations_k_l becomes l! / (k! * (l - k)!)
 */
unsigned int possibilities_for_combination(unsigned int n, unsigned int max_electrons);

/*
 * permutes 2 numbers in the array (recursive)
 * @precondition:   subResult != NULL, numberOnes <= length, index > 0, resultIndex != NULL, result != NULL
 * @postcondition:  /
 */
void permute(short *subResult, unsigned int numberOnes, unsigned int length, unsigned int index, unsigned int *resultIndex, short result[][length]);

/*
 * initialise the creation of a list permutation
 * @precondition:   numberOnes <= length, result != NULL
 * @postcondition:  the combinations are saved in result
 */
void generate_permutation(unsigned int numberOnes, unsigned int length, short result[][length]);


#endif //SIMULATORFORSPECTROSCOPICTERMS_COMBINATIONS_H
