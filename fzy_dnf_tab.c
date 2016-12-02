static char help[]= 
"Builds a choice table on a given fuzzy logic function (DNF)\n"
"USAGE: fzy_dnf_tab dnf_file tab_file\n"
"member.acm.org/~daze\n\n";

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

#include "fzy_fun.h"

int main(int argc, char *argv[]) {
	struct fzy_dnf * d = malloc(sizeof(struct fzy_dnf));
	int r,n,f;
	int no_last_perm=1, no_last_num,i,j;
	int *a, *b, *c;
	FILE *ft;
	
	if(argc<3)
	{
		printf("%s", help);
		return 1;
	}
	
	d->n=0; d->m=0; d->c=NULL;
	r=read_dnf(argv[1],d);
    CHK_ERR(r)
	
	ft=fopen(argv[2],"w");
	if(ft==NULL)
    {
    	r=-2;
    	CHK_ERR(r);
	}
	
	// allocate tuples
	n=d->n;
	a = malloc(n*sizeof(int));		// first half, variable numbers
	b = malloc(n*sizeof(int));		// first half, signs
	c = malloc(2*n*sizeof(int));	// full tuple
	if(a==NULL||b==NULL||c==NULL)
	{
		r=-4;
		CHK_ERR(r);
	}
	for(i=0;i<n;i++) a[i]=i+1;
	j=0;
	
	fprintf(ft,"%s %d\n",FZY_TAB_HEAD,n);
	
	while(no_last_perm)
	{
		for(i=0;i<n;i++) b[i]=0;
		
		no_last_num=1;
		while(no_last_num)
		{
			// insert signs from b
			// mirror the first half of the tuple with negation
			for(i=0;i<n;i++)
			{
				c[i]=(b[i])?-a[i]:a[i];
				c[2*n-1-i]=-c[i];
			} 
			
			j++;
			for(i=0;i<2*n;i++) fprintf(ft,"%2d ",c[i]); 
			
			f=calc_dnf(c,d);
			fprintf(ft,"   %2d\n",f);
			
			no_last_num=next_num(b,n);
		}
		no_last_perm=next_perm(a,n);
	}
	fprintf(ft,"%s (%d rows)\n",FZY_TAB_TAIL,j);
	fclose(ft);
	
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

