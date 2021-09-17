# extramon
Use of Thomson TO8/TO9+ extramonitor from C code

Pour les personnes qui seraient intéressées par la compilation de programmes C sur des ordinateurs à base de processeur Motorola 6809, sachez qu'il existe un [compilateur](http://perso.b2b2c.ca/~sarrazip/dev/cmoc.html) capable de produire des binaires pour plusieurs ordinateurs 8 bits de l'époque, et notamment les machines Thomson MO/TO.
Ce compilateur ne gère qu'une partie de la libc et il n'est, par exemple, pas encore possible de faire du calculs sur des nombres réels sur les Thomson.

Il est tout de même possible d'utiliser les routines assembleurs du "moniteur" et de l'"extramoniteur" pour pallier à ces manques.
Pour la liste exhaustives des routines, lire ce [livre](https://github.com/rodolphe74/extramon/blob/main/to8.pdf)
