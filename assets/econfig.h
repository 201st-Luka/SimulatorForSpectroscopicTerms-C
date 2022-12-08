/*
 * econfig header file
 * contains macros and prototypes of functions
 */

#ifndef SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H
#define SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H


// colors
#define ColorRed "\e[31m"
#define ColorGreen "\e[32m"
#define ColorYellow "\e[33m"
#define ColorBlue "\e[34m"
#define ColorMagenta "\e[35m"
#define ColorCyan "\e[36m"
#define ColorWhite "\e[0;37m"

// text styles
#define UnderlineColorWhite "\e[4;37m"
#define TextReset "\e[0m"

// orbitals
#define S 2
#define P 6
#define D 10
#define F 14

// harpoon arrows
#define ArrowSpinUp "\u21bf"
#define ArrowSpinDown "\u21c2"
#define ArrowSpinBoth "\u296e"


typedef struct {
    short *spinUp;
    short *spinDown;
} Orbital;

typedef struct {
    Orbital sOrbital;
    Orbital pOrbital[3];
    Orbital dOrbital[5];
    Orbital fOrbital[7];
    float ms;
    int ml;
} ElectronConfig;


/*
 * enumerates over the electronConfig array to fill in the values
 * @precondition:   s_possibilities, p_possibilities, d_possibilities, f_possibilities are initialised arrays and number_of_electrons is valid
 * @postcondition:  combinations are saved in s_possibilities, p_possibilities, d_possibilities, f_possibilities
 */
void permutation_creation(short s_possibilities[][S], short p_possibilities[][P], short d_possibilities[][D], short f_possibilities[][F],
                          const unsigned short *number_of_electrons);
/*
 * prints out the right arrow for the orbital
 * @precondition:   spinUp and spinDown != NULL
 * @postcondition:  /
 */
void printArrow(const short *spinUp, const short *spinDown);

/*
 * prints out the values of an ElectronConfig element
 * @precondition:   electronConfig != NULL
 * @postcondition:  /
 */
void print_econfig_element(ElectronConfig *electronConfig);

/*
 * prints out every single element of the electronConfig array
 * @precondition:   electronConfig != NULL and array_len > 0
 * @postcondition:  /
 */
void print_econfig(ElectronConfig *electronConfig, unsigned int array_len);

/*
 * set the pointer of the ElectronConfig array to the created permutations
 * @precondition:   electronConfig != NULL, s_possibilities, p_possibilities, d_possibilities, f_possibilities have the right values
 *                  and possibilities_s, possibilities_p, possibilities_d, possibilities_f > 0
 * @postcondition:  electronConfig gets the right pointer values and ms, ml are calculated
 */
void econfig_manipulation(ElectronConfig *electronConfig,
                          unsigned int possibilities_f, unsigned int possibilities_d, unsigned int possibilities_p, unsigned int possibilities_s,
                          short s_possibilities[][S], short p_possibilities[][P], short d_possibilities[][D], short f_possibilities[][F]);


#endif //SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H
