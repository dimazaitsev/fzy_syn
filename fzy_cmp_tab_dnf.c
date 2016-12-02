static char help[]=
"Compares a choice table with a fuzzy logic function (DNF)\n"
"USAGE: fzy_cmp_tab_dnf tab_file dnf_file comm_tab_file diff_tab_file\n"
"member.acm.org/~daze\n\n";

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

#include "fzy_fun.h"

int main(int argc, char *argv[]) {
	struct fzy_dnf * d = malloc(sizeof(struct fzy_dnf));
	int * t, *v, r, i,n,f,first=1;
	long int l, k=0L;
	FILE *ft1, *ft2;
	
	if(argc<5)
	{
		printf("%s", help);
		return 1;
	}
	
	r=read_tab(argv[1],&t,&l,&n);
	CHK_ERR(r);
	
	d->n=0; d->m=0; d->c=NULL;
	r=read_dnf(argv[2], d);
	CHK_ERR(r);
	
	if(n!=d->n)
	{
		r=-5;
		CHK_ERR(r);
	}
	
	ft1=fopen(argv[3],"w");
	ft2=fopen(argv[4],"w");
	if(ft1==NULL || ft2==NULL)
	{
		r=-2;
		CHK_ERR(r);
	}
	
	fprintf(ft1,"%s %d\n",FZY_TAB_HEAD,n);
	fprintf(ft2,"%s %d\n",FZY_TAB_HEAD,n);
	
	for(i=0;i<l;i++)
	{
		v=t+TOFF(n,i);
		f = calc_dnf(v, d);
		if(f==v[2*n])
		{
			prn_trow(ft1,v,n,v[2*n]);
		}
		else
		{
			prn_trow(ft2,v,n,v[2*n]);
			k++;
		}
	}
	
	fprintf(ft2,"%s (%ld rows)\n",FZY_TAB_TAIL,k);
	fprintf(ft1,"%s (%ld rows)\n",FZY_TAB_TAIL,l-k);
	
	fclose(ft1);
	fclose(ft2);
		
	return (k)?6:0;
}

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

