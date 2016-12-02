static char help[]= 
"Synthesis of a fuzzy logic function (DNF) on a given choice table\n"
"USAGE: fzy_tab_dnf tab_file dnf_file\n"
"member.acm.org/~daze\n\n";

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

#include "fzy_fun.h"

int main(int argc, char *argv[]) {
	struct fzy_dnf * d = malloc(sizeof(struct fzy_dnf));
	int * t,r,i1,i2,n;
	long int l;
	
	if(argc<3)
	{
		printf("%s", help);
		return 1;
	}
	
	if(d==NULL)
	{
		r=-4;
		CHK_ERR(r);
	}

	r=read_tab(argv[1],&t,&l,&n);
	CHK_ERR(r);
//printf("tab read\n");
	d->n=n;
	d->m=l;
	  
	r=create_dnf(t,l,d);
	CHK_ERR(r);
//printf("dnf created\n");	
	minimize_dnf(d);
//printf("dnf minimized\n");		
	r=write_dnf(argv[2],d);
	CHK_ERR(r);
	
	return 0;
}

/*
The MIT License (MIT)

Copyright (c) 2016 Dmitry Zaitsev

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

