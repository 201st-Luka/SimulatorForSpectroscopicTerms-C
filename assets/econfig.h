/*
 * econfig header file
 * contains macros and function prototypes
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
#define BracketSpace "\u02FD"

/*
 * Orbital struct
 * 4 bytes
 */
typedef struct {
    short spinUp;
    short spinDown;
} Orbital;

/*
 * ElectronConfig struct
 * 76 bytes
 */
typedef struct {
    Orbital sOrbital;
    Orbital pOrbital[3];
    Orbital dOrbital[5];
    Orbital fOrbital[7];
    short ml;
    float ms;
    unsigned short group;
} ElectronConfig;


/*
 * enumerates over the electronConfig array to fill in the values
 * @precondition:   s_possibilities, p_possibilities, d_possibilities, f_possibilities, number_of_electrons != NULL
 *                  and number_of_electrons is valid
 * @postcondition:  combinations are saved in s_possibilities, p_possibilities, d_possibilities, f_possibilities
 */
void permutation_creation(short s_possibilities[][S], short p_possibilities[][P], short d_possibilities[][D], short f_possibilities[][F],
                          const unsigned short *number_of_electrons);
/*
 * prints out the right arrow for the orbital
 * @precondition:   /
 * @postcondition:  /
 */
void printArrow(short spinUp, short spinDown);

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
 * @precondition:   electronConfig != NULL, s_possibilities, p_possibilities, d_possibilities, f_possibilities
 *                  have the right values
 *                  and possibilities_s, possibilities_p, possibilities_d, possibilities_f > 0
 * @postcondition:  electronConfig gets the right pointer values and ms, ml are calculated
 */
void econfig_manipulation(ElectronConfig *electronConfig,
                          unsigned int possibilities_f, unsigned int possibilities_d, unsigned int possibilities_p, unsigned int possibilities_s,
                          short s_possibilities[][S], short p_possibilities[][P], short d_possibilities[][D], short f_possibilities[][F]);

/*
 * builds the groups for the electronConfig
 * @precondition:   electronConfig and groups != NULL, ec_array_len and group_array_len > 0
 * @postcondition:  groups gets values, electronConfig[x].group is updated
 */
//void buildGroups(ElectronConfig *electronConfig, unsigned int ec_array_len, Group *groups, unsigned int group_array_len);


#endif //SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H
