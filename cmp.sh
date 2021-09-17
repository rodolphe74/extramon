# binaire en $A000 pour thomson TO
cmoc.exe -c -O2 --thomto -I ../../cmoc-0.1.71/src -I ../../cmoc-0.1.71/src/stdlib/ -L ../../cmoc-0.1.71/src/stdlib/ extramfl.c -lcmoc-crt-thm
cmoc.exe -c -O2 --thomto -I ../../cmoc-0.1.71/src -I ../../cmoc-0.1.71/src/stdlib/ -L ../../cmoc-0.1.71/src/stdlib/ extramgr.c -lcmoc-crt-thm
cmoc.exe -O2 --thomto -I ../../cmoc-0.1.71/src -I ../../cmoc-0.1.71/src/stdlib/ -L ../../cmoc-0.1.71/src/stdlib/ fl.c -lcmoc-crt-thm extramfl.o
cmoc.exe -O2 --thomto -I ../../cmoc-0.1.71/src -I ../../cmoc-0.1.71/src/stdlib/ -L ../../cmoc-0.1.71/src/stdlib/ gr.c -lcmoc-crt-thm extramgr.o
cmoc.exe -O2 --thomto -I ../../cmoc-0.1.71/src -I ../../cmoc-0.1.71/src/stdlib/ -L ../../cmoc-0.1.71/src/stdlib/ hypoc.c -lcmoc-crt-thm extramgr.o extramfl.o

# cmoc.exe -S -O2 --thomto -I ../../cmoc-0.1.71/src -I ../../cmoc-0.1.71/src/stdlib/ -L ../../cmoc-0.1.71/src/stdlib/ extramfl.c -lcmoc-crt-thm
# cmoc.exe -S -O2 --thomto -I ../../cmoc-0.1.71/src -I ../../cmoc-0.1.71/src/stdlib/ -L ../../cmoc-0.1.71/src/stdlib/ extramgr.c -lcmoc-crt-thm
