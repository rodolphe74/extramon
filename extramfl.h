#ifndef EXTRAMFL_H
#define EXTRAMFL_H



/* adresses extra moniteur TO8/9 */
#define EXTRA 0xEC0C
#define RESETW 01
#define FIN 65
#define PUFOUT 66


// operations unaires
#define INT 42
#define ABS 43
#define SQR 44
#define COS 47
#define SIN 48
#define TAN 49
#define ATN 68
#define FRCTYPE 50

// operations binaires
#define NEGGO 53
#define ADDGO 54
#define SUBGO 55
#define MULTGO 56
#define DIVGO 57


#define VALTYP 0x6105	/* Type de l accu (a 4) */
#define FACEXP 0x614E	/* Exposant binaire (de -128 a +127) */
#define FACHO 0x614F	/* mantisse 24bits, poids forts */
#define FACMO 0x6150	/* mantisse poids moyen */
#define FACLO 0x6151	/* mantisse poids faibles */
#define FACSGN 0x6156	/* signe de l'accumulateur */
#define DPWID 0x617A	/* nombre de chiffres apres la virgule */
#define FLDWID 0x617B	/* nombre de chiffres avant la virgule */
#define PUMASK 0x617C	/* Masque de sortie pour le formatage */

#define ARGEXP 0x6159	/* Exposant binaire (de -128 a +127) */
#define ARGHO 0x615A	/* mantisse 24bits, poids forts */
#define ARGMO 0x615B	/* mantisse poids moyen */
#define ARGLO 0x615C	/* mantisse poids faibles */
#define ARGSGN 0x6161	/* signe argument */


struct float_struct {
	unsigned char exp;
	unsigned char ho;
	unsigned char mo;
	unsigned char lo;
	unsigned char sgn;
	unsigned char valtyp;
};

extern static char static_buffer[16];
extern static struct float_struct static_float_temp;

void print_float(struct float_struct *fs);
void init_extra();
void fin(char *float_value, struct float_struct *fs);
char *pufout(struct float_struct *fs);
unsigned int to_unsigned_int(struct float_struct *fs);
unsigned int to_int(struct float_struct *fs);
void unary_op(struct float_struct *fac, struct float_struct *result, unsigned char op);
void binary_op(struct float_struct *fac, struct float_struct *arg, struct float_struct *result, unsigned char op);
char cmp(struct float_struct *fac, struct float_struct *arg);

#endif
