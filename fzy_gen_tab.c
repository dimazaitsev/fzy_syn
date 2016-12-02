static char help[]= 
"Generates a random choice table for a given number of variables\n"
"USAGE: fzy_gen_tab n tab_file [ rand_seed ]\n"
"member.acm.org/~daze\n\n";

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fzy_fun.h"

int main(int argc, char *argv[])
{
	int n, seed, no_last_perm=1, no_last_num, i, j, z, r;
	FILE *f;
	time_t t;
	
	if(argc<3)
	{
		printf("%s", help);
		return 1;
	}
	
	n=atoi(argv[1]);
		
	f=fopen(argv[2],"w");
	if(f==NULL)
	{
		r=-2;
		CHK_ERR(r);
	}
	
	if(argc<4)
		seed = time(&t);
	else
		seed=atoi(argv[3]);
	srand(seed);
	
	fprintf(f,"%s %d\n",FZY_TAB_HEAD,n);
	
	int * a = malloc(n*sizeof(int));
	int * b = malloc(n*sizeof(int));
	int * c = malloc(2*n*sizeof(int));
	if(a==NULL||b==NULL||c==NULL)
	{
		r=-4;
		CHK_ERR(r);
	}
	
	for(i=0;i<n;i++) a[i]=i+1;
	j=0;
	
	while(no_last_perm)
	{
		for(i=0;i<n;i++) b[i]=0;
		
		no_last_num=1;
		while(no_last_num)
		{
			for(i=0;i<n;i++)
			{
				c[i]=(b[i])?-a[i]:a[i];
				c[2*n-1-i]=-c[i];
			} 
			
			j++;
			for(i=0;i<2*n;i++) fprintf(f,"%2d ",c[i]); 
			z=rand()%(2*n);
			z=(z<n)?z+1:n-z-1;
			fprintf(f,"   %2d\n", z);
			no_last_num=next_num(b,n);
		}
		no_last_perm=next_perm(a,n);
	}
	fprintf(f,"%s (%d rows)\n",FZY_TAB_TAIL,j);
	fclose(f);
	
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

