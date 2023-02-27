/**
 * @author 201st-Luka
 *
 * @brief   combinations header file
 * @brief   contains function prototypes
 */


#ifndef SIMULATORFORSPECTROSCOPICTERMS_COMBINATIONS_H
#define SIMULATORFORSPECTROSCOPICTERMS_COMBINATIONS_H


/**
 * @brief   compute the factorial of n
 *
 * @param   n is the parameter of the factorial
 *
 * @pre     n >= 0
 * @post    factorial becomes n!
 *
 * @return  n!
 */
unsigned long int factorial (unsigned int n);

/**
 * @brief   compute the number of combinations
 *
 * @param   k in (C^k)_l
 * @param   l in (C^k)_l
 *
 * @pre     k > 0
 * @pre     l > 0
 * @post    combinations_k_l becomes l! / (k! * (l - k)!)
 *
 * @return  l! / (k! * (l - k)!)
 */
unsigned int combinations_k_l (unsigned int k, unsigned int l);

/**
 * @brief   computes the possibilities for a combination
 *
 * wrapper of combinations_k_l
 *
 * @param   n -> k
 * @param   max_electrons -> l
 *
 * @pre     n > 0
 * @pre     max_electrons > 0
 * @post    combinations_k_max_electrons becomes max_electrons! / (n! * (max_electrons - n)!)
 *
 * @return  max_electrons! / (n! * (max_electrons - n)!)
 */
unsigned int possibilities_for_combination(unsigned int n, unsigned int max_electrons);

/**
 * @brief   creates the permutations (recursive)
 *
 * @param   result is a pointer to the array which is used to save the permutations
 * @param   perm is the current, incomplete permutation
 * @param   ones is the number of "1" that occur in the permutation
 * @param   length is the total length of the permutations
 * @param   i is the current index of the (incomplete) permutation
 * @param   result_len is the size of the result array
 *
 * @pre     result != NULL
 * @pre     ones <= length
 * @pre     i <= length
 * @pre     result_len != NULL
 * @post    /
 */
void permute(unsigned short *result, unsigned short perm, unsigned int ones, unsigned int length, unsigned int i, unsigned int *result_len);

/**
 * @brief   initialise the creation of a list permutation
 *
 * the combinations are saved in result
 *
 * @param   ones is the number of "1" that occur in the permutation
 * @param   length is the total length of the permutations
 * @param   result is a pointer to the array which is used to save the permutations
 *
 * @pre     result != NULL
 * @pre     ones <= length
 * @post    /
 */
void generate_permutation(unsigned int ones, unsigned int length, unsigned short *result);


#endif //SIMULATORFORSPECTROSCOPICTERMS_COMBINATIONS_H
