/*
 * combinatoric header file
 * contains function prototypes
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
 * compute the number of combinatoric
 * @precondition:   k, l > 0
 * @postcondition:  combinations_k_l becomes l! / (k! * (l - k)!)
 */
unsigned int combinations_k_l (unsigned int k, unsigned int l);

/*
 * computes the possibilities for a combination (wrapper of combinations_k_l)
 * @precondition:   n, max_electrons > 0
 * @postcondition:  combinations_k_max_electrons becomes max_electrons! / (n! * (max_electrons - n)!)
 */
unsigned int possibilities_for_combination(unsigned int n, unsigned int max_electrons);

/*
 * creates the permutations (recursive)
 * @precondition:   result != NULL, ones <= length, i <= length, result_len != NULL
 * @postcondition:  /
 */
void permute(unsigned short *result, unsigned short perm, unsigned int ones, unsigned int length, unsigned int i, unsigned int *result_len);

/*
 * initialise the creation of a list permutation
 * @precondition:   result != NULL, ones <= length
 * @postcondition:  the combinatoric are saved in result
 */
void generate_permutation(unsigned int ones, unsigned int length, unsigned short *result);


#endif //SIMULATORFORSPECTROSCOPICTERMS_COMBINATIONS_H
