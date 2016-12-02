// common functions to work with fuzzy logic

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

char *err_msg[]={ "when openning file", "wrong file format", "no memory", "different number of arguments in table and DNF" };
#define ERR_MSG_DECL

#include "fzy_fun.h"

void SwallowSpace(char *str, int *i )
{
  
  while( ( str[(*i)]==' ' || str[(*i)]==0xa || str[(*i)]==0xd || str[(*i)]==0x9 ) && str[(*i)]!='\0'  ) (*i)++;

} /* SwallowSpace */

int IsSpace( char *str, int i )
{
   
  if( str[i]==' ' || str[i]==0xa || str[i]==0xd || str[i]==0x9 || str[i]=='\0' )
    return( 1 );
  else
    return( 0 );
  
} /* IsSpace */

int read_dnf(char * fname, struct fzy_dnf * d)
{
	FILE *f = fopen(fname,"r");
	char buf[MAX_BUF_SIZE], bb[20];
	int n,m,len,i,j,go,i1,k;
	int *wa;
	struct cnj ** ppre;
	struct cnj * c;
	char ch;
	
	if(f==NULL) return -2;
	fscanf(f,"%s %d\n",bb,&n);
	if(strcmp(bb,FZY_DNF_HEAD)!=0) return -3;
	d->n=n;
	m=0;
	ppre=&(d->c);
	
	wa=malloc(2*n*sizeof(int));
	if(wa==NULL) return -4;
	
	while(!feof(f))
	{
		fgets(buf,MAX_BUF_SIZE,f);
		if(feof(f)) return -3;
		ch=buf[strlen(FZY_DNF_TAIL)];
		buf[strlen(FZY_DNF_TAIL)]='\0';
		if(strcmp(buf,FZY_DNF_TAIL)==0) break;
		buf[strlen(FZY_DNF_TAIL)]=ch;
		len=strlen(buf)-1; i=0;
		go=1;
		k=0;
		
		while(go&&i<len)
		{
			SwallowSpace( buf, &i );
        	if( i==len ) go=0;
        	
        	i1=i;
        	
        	while( ! IsSpace(buf, i) && i<len )i++;
        	
        	buf[i]='\0';
        	
        	wa[k++]=atoi(buf+i1);
        	i=i1=i+1;
		}
		m++;
		// asort(wa,k);
		
        c = malloc(sizeof(struct cnj));
        if(c==NULL) return -4;
        c->k=k;
        c->a=malloc(k*sizeof(int));
        if((c->a)==NULL) return -4;
        for(j=0;j<k;j++)c->a[j]=wa[j];
        c->nxc=NULL;
        
        (*ppre)=c;
        ppre=&(c->nxc);
        	
	} // while feof(f)
	
	d->m=m;
	fclose(f);
	return 0;
} // end read_dnf

int write_dnf(char * fname, struct fzy_dnf * d)
{
	FILE *f = fopen(fname,"w");
	struct cnj * c=d->c;
	int j,m=0;
	
	if(f==NULL) return -2;
	fprintf(f,"%s %d\n",FZY_DNF_HEAD,d->n);
	
	while(c)
	{
		for(j=0;j<c->k;j++)
		  fprintf(f,"%d ",c->a[j]);
		fprintf(f,"\n");
		c=c->nxc;
		m++;
	}
	
	fprintf(f,"%s (%d conjuncts)\n",FZY_DNF_TAIL,m);
	fclose(f);
} // end write_dnf

int next_num(int *b, int n)
{
	int i=n-1, go=1;
	
	while(go)
	{
		if(b[i]==0) 
		{
			b[i]=1;
			go=0;
		}
		else
		{
			b[i]=0;
			if(--i<0) return 0;
		}
	}
	return 1;
} // next_2num

int next_perm(int *a, int n)
{
	int i, go=1, first=1, j, jm, ax;
	
	for(i=n-2;i>=0 && go;i--) 
	{
		if(a[i]<a[i+1])
		{
		  go=0;
		  break;
	    }
	}
	if(go)return 0;
	
	// minimum among greater than a[i]
	for(j=i+1;j<n;j++)
	{
		if(a[j]>a[i]) 
		{
			if(first)
			{
			  jm = j; first=0;
			}
			else if(a[j]<a[jm]) jm=j;
		}
	}
	ax=a[i];a[i]=a[jm];a[jm]=ax;
	
    for(j=1;j<=(n-i)/2;j++)
	{
		ax=a[i+j];a[i+j]=a[n-j];a[n-j]=ax;
	}
	return 1;
} // next_perm

int find(int k, int *a, int n)
{
	int i, found=0;
	
	for(i=0;i<n;i++)
	  if(a[i]==k)
	  {
	  	found=1;
	  	break;
	  }
	i=(found)?i:-1;
	return i;
}

int calc_dnf(int *v, struct fzy_dnf *d)
{
	struct cnj * c=d->c;
	int j,i, cval, icval, idval=-1;
	
	while(c)
	{
		for(i=0;i<2*d->n;i++)
		  if(find(v[i],c->a,c->k)>=0) 
		  {
		  	cval = v[i];
		  	break;
		  }
		
		icval = find(cval, v, 2*d->n);
		idval=(idval==-1)?icval : ((idval>icval)?idval:icval);
		c=c->nxc;
	}
	
	return v[idval];
} // calc_dnf

long int tab_len(int n)
{ 
  long int l=1L;
  int i;
  
  for(i=1;i<=n;i++) l*=2;
  for(i=2;i<=n;i++) l*=n;
  
  return l;
} // tab_len

int read_tab(char * fname, int ** ppt, long int *l, int *pn) 
{
	FILE *f=fopen(fname,"r");
	char buf[MAX_BUF_SIZE], bb[20];
	long lt, m=0L;
	int n,len,i,j,go,i1,k;
	int *trow;
	char ch;
	
	if(f==NULL) return -2;
	fscanf(f,"%s %d\n",bb,&n);
	if(strcmp(bb,FZY_TAB_HEAD)!=0) return -3;
	*pn=n;
	
	lt=tab_len(n);
	*ppt=malloc(lt*(2*n+1)*sizeof(int));
	if(*ppt==NULL) return -4;
	
	while(!feof(f)&&m<lt)
	{
		fgets(buf,MAX_BUF_SIZE,f);
		if(feof(f)) return -3;
		ch=buf[strlen(FZY_TAB_TAIL)];
		buf[strlen(FZY_TAB_TAIL)]='\0';
		if(strcmp(buf,FZY_TAB_TAIL)==0) break;
		buf[strlen(FZY_TAB_TAIL)]=ch;
		len=strlen(buf)-1; i=0;
		go=1;
		k=0;
		
		trow=*ppt+TOFF(n,m);
		while(go&&i<len&&k<2*n+1)
		{
			SwallowSpace( buf, &i );
        		if( i>=len ) go=0; else	
			{
        			i1=i;
        	
        			while( ! IsSpace(buf, i) && i<len )i++;
        	
        			buf[i]='\0';
        	
        			trow[k++]=atoi(buf+i1);
        			i=i1=i+1;
			}
		}
		m++;
        	
	} // while feof(f)
	
	fclose(f);
	*l=m;
	
} // read_tab

int create_dnf(int * t, long int l, struct fzy_dnf * d)
{
	int n=d->n,i,j,ii;
	struct cnj ** ppre=&(d->c);;
	struct cnj * c;
	int *trow;
	
	for(i=0;i<l;i++)
	{
		c = malloc(sizeof(struct cnj));
		if(c==NULL) return -4;
		c->nxc=NULL;
		
		trow=t+TOFF(n,i);
		
		j=find(trow[2*n],trow,2*n);
		c->k=((2*n)-j);
		c->a=malloc((c->k)*sizeof(int));
		if((c->a)==NULL) return -4;
		for(ii=0;ii<c->k;ii++) c->a[ii]=trow[j+ii];
		
		(*ppre)=c;
        ppre=&(c->nxc);
	}
	d->m=l;
	
	return 0;
} // create_dnf

void minimize_dnf(struct fzy_dnf * d)
{
	struct cnj * c1=d->c, *c2, *c2pre, *nxc;
	int i, found;
	
	//sort_dnf_len(d);
	
	while(c1)
	{
		c2=d->c;
		c2pre=NULL;
		while(c2)
		{
			if(c1==c2) 
			{
				c2pre=c2;
				c2=c2->nxc;
			}
			else if(c1->k<=c2->k)
			{
				found=1;
				for(i=0;i<c1->k;i++)
					if(find(c1->a[i],c2->a,c2->k)<0)
					{
						found=0;
						break;
					}
				if(found)
				{
					nxc=c2->nxc;
					free(c2);
					if(c2pre!=NULL)
					{
						c2pre->nxc=nxc;
						c2=nxc;
					}
					else
					{
						d->c=nxc;
						c2=nxc;
					}
					
				}
				else
				{
					c2pre=c2;
					c2=c2->nxc;
				}
			}
			else
			{
				c2pre=c2;
				c2=c2->nxc;
			}
			
		}
		
		c1=c1->nxc;
	}
	
} // minimize_dnf

void prn_trow(FILE *ft, int *v, int n, int f)
{
	int i;
	
	for(i=0;i<2*n;i++) 
	  fprintf(ft,"%2d ",v[i]); 
	fprintf(ft,"   %2d\n",f);
} // prn_trow


// end of common functions to work with fuzzy logic

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

