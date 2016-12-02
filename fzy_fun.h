// headers for common functions to work with fuzzy logic

#define MAX_BUF_SIZE 2014
#define FZY_TAB_HEAD "FZYTAB"
#define FZY_TAB_TAIL "FZYTABEND"
#define FZY_DNF_HEAD "FZYDNF"
#define FZY_DNF_TAIL "FZYDNFEND"

#define TOFF(n,i) ((i)*(2*n+1))

#define ERR_NUM 4
#define ERR_MSG_OFFS -2
#define CHK_ERR(r) {if(r<0){printf("*** error: %s\n",err_msg[-r+ERR_MSG_OFFS]); return -r;}}

#ifndef ERR_MSG_DECL
extern char *err_msg[ERR_NUM];
#define ERR_MSG_DECL
#endif

struct cnj {
	int k;
	int * a;
	struct cnj * nxc;
};

struct fzy_dnf {
	int n;
	int m;
	struct cnj * c;
};

void SwallowSpace(char *str, int *i );

int IsSpace( char *str, int i );

int read_dnf(char * fname, struct fzy_dnf * d);

int write_dnf(char * fname, struct fzy_dnf * d);

int next_num(int *b, int n);

int next_perm(int *a, int n);

int find(int k, int *a, int n);

int calc_dnf(int *v, struct fzy_dnf *d);

long int tab_len(int n);

#define TOFF(n,i) ((i)*(2*n+1))

int read_tab(char * fname, int ** ppt, long int *l, int *pn);

int create_dnf(int * t, long int l, struct fzy_dnf * d);

void minimize_dnf(struct fzy_dnf * d);

void prn_trow(FILE* ft, int *v, int n, int f);

// end of feaders for common functions to work with fuzzy logic

/*
The MIT License (MIT)

Copyright (c) 2015 Dmitry Zaitsev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

