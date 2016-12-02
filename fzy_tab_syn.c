static char help[]= 
"Synthesis of fuzzy logic functions (DNFs) on a given choice table\n"
"The table is partitioned with a series of fuzzy logic functions\n"
"USAGE: fzy_tab_dnf tab_file result_files_prefix\n"
"member.acm.org/~daze\n\n";

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

#include "fzy_fun.h"

int main(int argc, char *argv[]) {
	struct fzy_dnf * d = malloc(sizeof(struct fzy_dnf));
	int * t,r,i1,i2,n,m=0,*v,i,first,f;
	long int l,k;
	char fname[256];
	FILE *ft1, *ft2;
	
	if(argc<3)
	{
		printf("%s", help);
		return 1;
	}
	
	do {
		
		// synthesize a DNF on a table
		
		r=read_tab((m)?fname:argv[1],&t,&l,&n);
		CHK_ERR(r);
		d->n=n;
		d->m=l;
		
		sprintf(fname,"%s-dnf-%d",argv[2],m);
		r=create_dnf(t,l,d);
		CHK_ERR(r);
		minimize_dnf(d);
		r=write_dnf(fname,d);
		CHK_ERR(r);
		
		// create a table on DNF and compare it with the source table
		
		sprintf(fname,"%s-tab-%d",argv[2],m);
		ft1=fopen(fname,"w");
		sprintf(fname,"%s-tab-%d",argv[2],m+1);
		ft2=fopen(fname,"w");
		if(ft1==NULL || ft2==NULL)
		{
			r=-2;
			CHK_ERR(r);
		}
		k=0;
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
		m++;
	} while(k);
	
	remove(fname);
	
	return 0;
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

