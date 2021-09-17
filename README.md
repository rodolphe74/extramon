# extramon
Use of Thomson TO8/TO9+ extramonitor from C code

Pour les personnes qui seraient intéressées par la compilation de programmes C sur des ordinateurs à base de processeur Motorola 6809, sachez qu'il existe un [compilateur](http://perso.b2b2c.ca/~sarrazip/dev/cmoc.html) capable de produire des binaires pour plusieurs ordinateurs 8 bits de l'époque, et notamment les machines Thomson MO/TO.
Ce compilateur ne gère qu'une partie de la libc et il n'est par exemple pas encore possible de faire du calculs sur des nombres réels sur les Thomson.

Il est tout de même possible d'utiliser les routines assembleurs du "moniteur" et de l'"extramoniteur" Thomson pour pallier à ces manques.
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

# exemple
[hypoc.c](hypoc.c) est un exemple de graphisme utilisant des calculs flottants. Il s'agit d'un [hypocycloïde](https://fr.wikipedia.org/wiki/Hypocyclo%C3%AFde).
Le principe est de calculer les coordonnées X et Y d'une figure géometrique à l'aide de formules savantes.

# compilation
Sont nécessaires :
* le compilateur cmoc (sur windows, il se compile facilement avec [msys2](https://www.msys2.org/))
* sapfs.exe (un utilitaire permettant de copier les binaires MO/TO dans un fichier SAP équivalent à une disquette thomson)

le script de compilation C sur MSYS (adapter éventuellement le chemin vers cmoc)
```shell
# binaire en $A000 pour thomson TO
cmoc.exe -c -O2 --thomto -I ../../cmoc-0.1.71/src -I ../../cmoc-0.1.71/src/stdlib/ -L ../../cmoc-0.1.71/src/stdlib/ extramfl.c -lcmoc-crt-thm
cmoc.exe -c -O2 --thomto -I ../../cmoc-0.1.71/src -I ../../cmoc-0.1.71/src/stdlib/ -L ../../cmoc-0.1.71/src/stdlib/ extramgr.c -lcmoc-crt-thm
cmoc.exe -O2 --thomto -I ../../cmoc-0.1.71/src -I ../../cmoc-0.1.71/src/stdlib/ -L ../../cmoc-0.1.71/src/stdlib/ fl.c -lcmoc-crt-thm extramfl.o
cmoc.exe -O2 --thomto -I ../../cmoc-0.1.71/src -I ../../cmoc-0.1.71/src/stdlib/ -L ../../cmoc-0.1.71/src/stdlib/ gr.c -lcmoc-crt-thm extramgr.o
cmoc.exe -O2 --thomto -I ../../cmoc-0.1.71/src -I ../../cmoc-0.1.71/src/stdlib/ -L ../../cmoc-0.1.71/src/stdlib/ hypoc.c -lcmoc-crt-thm extramgr.o extramfl.o
```

le script de création du fichier sap à partir des binaires produits:
```shell
sapfs.exe -c extramfl.sap
sapfs.exe -a extramfl.sap fl.bin
sapfs.exe -a extramfl.sap gr.bin
sapfs.exe -a extramfl.sap hypoc.bin
```
