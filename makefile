shell : main.o compare.o ls.o prompt.o function.o read.o bg_fg.o redir.o piping.o
			gcc main.o compare.o ls.o prompt.o function.o read.o bg_fg.o redir.o piping.o -I.

main.o : main.c headers.h
			gcc -c main.c -I.
compare.o : compare.c headers.h
			gcc -c compare.c -I.
ls.o : ls.c headers.h
			gcc -c ls.c -I.
prompt.o : prompt.c headers.h
			gcc -c prompt.c -I.
function.o : function.c headers.h
				gcc -c function.c -I.
read.o : read.c headers.h
			gcc -c read.c -I.
redir.o : redir.c headers.h
			gcc -c redir.c -I.
piping.o : piping.c headers.h
			gcc -c piping.c -I. 
bg_fg.o : bg_fg.c headers.h
			gcc -c bg_fg.c -I.


