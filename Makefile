# Toolbox for synthesis of fuzzy logic functions given by a choice table
# fzy_syn: fzy_tab_syn, fzy_tab_dnf, fzy_dnf_tab, fzy_cmp_tab_dnf, fzy_gen_tab

CC=gcc

all: fzy_tab_syn fzy_tab_dnf fzy_dnf_tab fzy_cmp_tab_dnf fzy_gen_tab

clean: 
	${RM} -f *.o fzy_tab_syn fzy_tab_dnf fzy_dnf_tab fzy_cmp_tab_dnf fzy_gen_tab

fzy_tab_syn: fzy_tab_syn.c fzy_fun.o fzy_fun.h
	$(CC) fzy_tab_syn.c fzy_fun.o -o fzy_tab_syn

fzy_tab_dnf: fzy_tab_dnf.c fzy_fun.o fzy_fun.h
	$(CC) fzy_tab_dnf.c fzy_fun.o -o fzy_tab_dnf

fzy_dnf_tab: fzy_dnf_tab.c fzy_fun.o fzy_fun.h
	$(CC) fzy_dnf_tab.c fzy_fun.o -o fzy_dnf_tab

fzy_cmp_tab_dnf: fzy_cmp_tab_dnf.c fzy_fun.o fzy_fun.h
	$(CC) fzy_cmp_tab_dnf.c fzy_fun.o -o fzy_cmp_tab_dnf

fzy_gen_tab: fzy_gen_tab.c fzy_fun.o fzy_fun.h
	$(CC) fzy_gen_tab.c fzy_fun.o -o fzy_gen_tab

fzy_fun.o: fzy_fun.c fzy_fun.h
	$(CC) -c fzy_fun.c

