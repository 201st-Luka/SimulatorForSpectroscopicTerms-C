//
// Created by luka on 08.12.22.
//

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
    float ms, ml;
} ElectronConfig;


/*
 * enumerates over the electronConfig array to fill in the values
 * input:   unsigned int possibilities_f, unsigned int possibilities_d, unsigned int possibilities_p, unsigned int possibilities_s,
 *          short s_possibilities[][S], short p_possibilities[][P], short d_possibilities[][D], short f_possibilities[][F],
 *          const unsigned short number_of_electrons[4]
 * output:  electronConfig is a pointer, so no object has to be returned
 */
void permutation_creation(short s_possibilities[][S], short p_possibilities[][P], short d_possibilities[][D], short f_possibilities[][F],
                          const unsigned short *number_of_electrons);
/*
 * prints out the right arrow for the orbital
 * input:   const short *spinUp, const short *spinDown
 * output:  no output, print arrow in console
 */
void printArrow(const short *spinUp, const short *spinDown);

/*
 * prints out the values of an ElectronConfig element
 * input:   ElectronConfig *electronConfig
 * output:  no output, printf in console
 */
void print_econfig_element(ElectronConfig *electronConfig);

/*
 * prints out every single element of the electronConfig array
 * input:   ElectronConfig electronConfig[], unsigned int array_len
 * output:  printed in the console
 */
void print_econfig(ElectronConfig *electronConfig, unsigned int array_len);

/*
 * set the pointer of the ElectronConfig array to the created permutations
 * input:   ElectronConfig electronConfig[],
 *          unsigned int possibilities_f, unsigned int possibilities_d, unsigned int possibilities_p, unsigned int possibilities_s,
 *          short s_possibilities[][S], short p_possibilities[][P], short d_possibilities[][D], short f_possibilities[][F]
 * output:  the ElectronConfig array gets updated, no output
 */
void econfig_pointers(ElectronConfig *electronConfig,
                      unsigned int possibilities_f, unsigned int possibilities_d, unsigned int possibilities_p, unsigned int possibilities_s,
                      short s_possibilities[][S], short p_possibilities[][P], short d_possibilities[][D], short f_possibilities[][F]);


#endif //SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H