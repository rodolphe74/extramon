# extramon
Use of Thomson TO8/TO9+ extramonitor from C code

Pour les personnes qui seraient intéressées par la compilation de programmes C sur des ordinateurs à base de processeur Motorola 6809, sachez qu'il existe un [compilateur](http://perso.b2b2c.ca/~sarrazip/dev/cmoc.html) capable de produire des binaires pour plusieurs ordinateurs 8 bits de l'époque, et notamment les machines Thomson MO/TO.
Ce compilateur ne gère qu'une partie de la libc et il n'est, par exemple, pas encore possible de faire du calculs sur des nombres réels sur les Thomson.

Il est tout de même possible d'utiliser les routines assembleurs du "moniteur" et de l'"extramoniteur" pour pallier à ces manques.
Pour la liste exhaustives des routines, lire ce [livre](https://github.com/rodolphe74/extramon/blob/main/to8.pdf)

Dans le présent projet, les routines mathématiques sur les flottants (cf page 263) ont été reprise en C dans les fichiers extramfl.h et extramfl.c.

```
void print_float(struct float_struct *fs);
void init_extra();
void fin(char *float_value, struct float_struct *fs);
char *pufout(struct float_struct *fs);
unsigned int to_unsigned_int(struct float_struct *fs);
unsigned int to_int(struct float_struct *fs);
void unary_op(struct float_struct *fac, struct float_struct *result, unsigned char op);
void binary_op(struct float_struct *fac, struct float_struct *arg, struct float_struct *result, unsigned char op);
char cmp(struct float_struct *fac, struct float_struct *arg);
```
