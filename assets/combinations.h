//
// Created by luka on 08.12.22.
//

#ifndef SIMULATORFORSPECTROSCOPICTERMS_COMBINATIONS_H
#define SIMULATORFORSPECTROSCOPICTERMS_COMBINATIONS_H


/*
 * compute the factorial of n
 * input:   unsigned int n
 * output:  unsigned long int result
 */
unsigned long int factorial (unsigned int n);

/*
 * compute the number of combinations
 * input:   unsigned int k, unsigned int l
 * output:  unsigned int
 */
unsigned int combinations_k_l (unsigned int k, unsigned int l);

/*
 * computes the possibilities for a combination
 * input:   unsigned int n, unsigned int orbital
 * output:  unsigned int
 */
unsigned int possibilities_for_combination(unsigned int n, unsigned int max_electrons);

/*
 * permutes 2 numbers in the array (recursive)
 * input:   short *subResult, unsigned int numberOnes, unsigned int length, unsigned int index, unsigned int *resultIndex, short result[][length]
 * output:  the result gets new values in the recursive call chain, no output
 */
void permute(short *subResult, unsigned int numberOnes, unsigned int length, unsigned int index, unsigned int *resultIndex, short result[][length]);

/*
 * initialise the creation of a list permutation
 * input:   unsigned int numberOnes, unsigned int length, short result[][length]
 * output:  the result array gets updated, no output
 */
void generate_permutation(unsigned int numberOnes, unsigned int length, short result[][length]);


#endif //SIMULATORFORSPECTROSCOPICTERMS_COMBINATIONS_H
