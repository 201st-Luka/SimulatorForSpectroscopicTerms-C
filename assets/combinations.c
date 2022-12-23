/*
 * combinations file
 * contains the implementations of the functions
 */

#include <string.h>
#include <assert.h>

#include "combinations.h"


unsigned long int factorial (unsigned int n) {
    long int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

unsigned int combinations_k_l (unsigned int k, unsigned int l) {
    return (factorial(l) / (factorial(k) * factorial(l - k)));
}

unsigned int possibilities_for_combination(unsigned int n, unsigned int max_electrons) {
    return combinations_k_l(n, max_electrons);
}

void permute(unsigned short *result, unsigned short perm, unsigned int ones, unsigned int length, unsigned int i, unsigned int *result_len) {
    assert(result != NULL && ones <= length && i <= length && result_len != NULL);
    if (ones <= 0) {
        result[*result_len] = perm << (length - i);
        (*result_len)++;
    } else if (i < length) {
        permute(result, (perm << 1) + 1, ones - 1, length, i + 1, result_len);
        if ((length - i) > ones) permute(result, perm << 1, ones, length, i + 1, result_len);
    }
}

void generate_permutation(unsigned int ones, unsigned int length, unsigned short *result) {
    assert(result != NULL && ones <= length);
    unsigned int result_len = 0;
    permute(result, 0, ones, length, 0, &result_len);
}
