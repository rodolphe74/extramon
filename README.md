# extramon
Use of Thomson TO8/TO9+ extramonitor from C code

Pour les personnes qui seraient intéressées par la compilation de programmes C sur des ordinateurs à base de processeur Motorola 6809, sachez qu'il existe un [compilateur](http://perso.b2b2c.ca/~sarrazip/dev/cmoc.html) capable de produire des binaires pour plusieurs ordinateurs 8 bits de l'époque, et notamment les machines Thomson MO/TO.
Ce compilateur ne gère qu'une partie de la libc et il n'est, par exemple, pas encore possible de faire du calculs sur des nombres réels sur les Thomson.

Il est tout de même possible d'utiliser les routines assembleurs du "moniteur" et de l'"extramoniteur" pour pallier à ces manques.
Pour la liste exhaustives des routines, lire ce [livre](https://github.com/rodolphe74/extramon/blob/main/to8.pdf)

Dans le présent projet, les routines mathématiques sur les flottants (cf page 263) ont été reprise en C dans les fichiers extramfl.h et extramfl.c.

```c
void print_float(struct float_struct *fs); /* affiche les 5 octets représentant le flottant */
void init_extra(); /* initialisation de l'extramoniteur */
void fin(char *float_value, struct float_struct *fs); /* conversion chaine de car vers struct flottant */
char *pufout(struct float_struct *fs); /* conversion struct flottant vers chaine de car */
unsigned int to_unsigned_int(struct float_struct *fs); /* conversion flottant en entier non signé */
unsigned int to_int(struct float_struct *fs); /* conversion flottant en entier signé */
void unary_op(struct float_struct *fac, struct float_struct *result, unsigned char op); /* operation unaire */
void binary_op(struct float_struct *fac, struct float_struct *arg, struct float_struct *result, unsigned char op); /* operation binaire */
char cmp(struct float_struct *fac, struct float_struct *arg); /* comparaison de 2 flottants */
```

Ces fonctions s'utilisent par exemple ainsi :

```c
#include <cmoc.h>
#include "extramfl.h"


int main(void)
{
  char value[] = "3.14156265";
  struct float_struct fl_value;
  
  fin(value, &fl_result); /* création de la struct float a partir de la chaine */
  print_float(&fl_result); /* affichage interne */
  char *result = pufout(&fl_result_c); /* conversion */
	printf(">%s<%c%c", result, 10, 13); /* affichage string */
  binary_op(&fl_value, &fl_value, &fl_value, ADDGO); /* value = value + value */
  unary_op(&fl_value, &value, NEGGO); /* value = -value */
  return 0;
}
```
