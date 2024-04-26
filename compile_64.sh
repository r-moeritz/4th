rm -f *.o
gcc -Wall -fpic -DOS_LINUX -DSYSTEM_64 -c quattro_parser.c quattro_vm.c quattro_istruzioni.c utils.c quattro_debug.c quattro_istruzioni_aritmetiche.c quattro_istruzioni_flow.c quattro_istruzioni_mem.c quattro_istruzioni_stack.c quattro_istruzioni_definition.c quattro_istruzioni_ffi.c quattro_istruzioni_wordlist.c quattro_istruzioni_repl.c

rm -f lib4th.so
gcc -shared -o lib4th.so *.o

gcc -o forthconsole -Wall -DOS_LINUX forthconsole.c -L. -Wl,-rpath=. -l4th -ldl
gcc -o forthc -Wall -DOS_LINUX forthc.c -L. -Wl,-rpath=. -l4th -ldl
