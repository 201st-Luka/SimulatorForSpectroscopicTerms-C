//
// Created by luka on 08.12.22.
//

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
void permute(short *subResult, unsigned int numberOnes, unsigned int length, unsigned int index, unsigned int *resultIndex, short result[][length]) {
    if (numberOnes <= 0) {
        memcpy(&(result[(*resultIndex)++]), subResult, length * sizeof(short));
    }
    else if (index < length) {
        subResult[index] = 1;
        permute(subResult, numberOnes - 1, length, index + 1, resultIndex, result);
        subResult[index] = 0;
        permute(subResult, numberOnes, length, index + 1, resultIndex, result);
    }
}

void generate_permutation(unsigned int numberOnes, unsigned int length, short result[][length]) {
    short subResult[length];
    unsigned int resultIndex = 0;
    memset(subResult, 0, length * sizeof(short));
    permute(subResult, numberOnes, length, 0, &resultIndex, result);
}