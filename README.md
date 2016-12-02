# fzy_syn: fzy_tab_syn, fzy_tab_dnf, fzy_dnf_tab, fzy_cmp_tab_dnf, fzy_gen_tab

Synthesis of fuzzy logic functions given by a choice table


Description:
------------

A fuzzy logic function (FLF) is introduced after Lofty Zadeh as a superposition of conjunction (&), disjunction (V) and negation (~) over independent variables which take values from [0,1]. A conjunction is defined as minimum, a disjunction as maximum, and a negation of variable x as 1-x. According to this definition an FLF takes a value of one of its arguments or a negation of an argument. 

To compare two FLFs, a choice table (CT) is build which contains values of a function for each variant of ordering arguments and their negations. A task of FLF synthesis on a given CT has been solved in [1]. It was shown that not each CT defines a single FLF though a CT can be partitioned in a few subdomains having corresponding FLFs.

For instance, the following choice table of two variables x1 and x2 gives functions f1 and f2:

+------------------+-----+-----+------+------+
|  Area            |  f1 |  f2 |  f2a |  f2b |
|------------------+-----+-----+------+------+
| x1<=x2<=~x2<=~x1 |  x2 |  x2 | ~x1  |  x2 *|
| x1<=~x2<=x2<=~x1 |  x2 | ~x1 | ~x1 *| ~x2  |
| ~x1<=x2<=~x2<=x1 | ~x2 |  x2 |  x2 *| ~x1  |
| ~x1<=~x2<=x2<=x1 | ~x2 | ~x2 | ~x2 *| ~x1  |
| x2<=x1<=~x1<=~x2 |  x1 |  x1 | ~x1  |  x1 *|
| x2<=~x1<=x1<=~x2 |  x1 | ~x1 | ~x1 *| ~x1  |
| ~x2<=x1<=~x1<=x2 | ~x1 | ~x2 | ~x1  | ~x2 *|
| ~x2<=~x1<=x1<=x2 | ~x1 | ~x1 | ~x1 *| ~x2  |
+------------------+-----+-----+------+------+

The fist function f1 is an FLF and can be specified as f1 = x1 & ~x2 V ~x1 & x2. 
The second function f2 is not an FLF. However, we can specify f2 with 2 FLFs: 
f1a = ~x1 V x1 & x2 & ~x2 valid on the areas 2,3,4,6,8 and 
f1b = x1 & ~x1 & ~x2 V ~x1 & x2 & ~x2 valid on the areas 1, 5, 7;
valid values are marked with "*" in the CT.

The fzy_syn toolbox contains the following tools:

fzy_tab_syn - partitioning a given choice table with a series of synthesised fuzzy logic functions (DNFs)

A repeating combination of fzy_tab_dnf and fzy_cmp_tab_dnf is implemented. In the general case, a DNF synthesised with fzy_tab_dnf satisfies only a part of the CT. Using fzy_cmp_tab_dnf, the CT is partitioned into two tables: the first table contains rows where DNF coincides with the source table; the second table contains rows where DNF does not coincide with the source table. Then the process is repeated with the difference table until it will be empty.

fzy_tab_dnf - synthesis of a fuzzy logic function (DNF) on a given choice table

On a given CT, it builds a DNF. The CT can be either complete or partial. A DNF is reduced with the application of the absorption law. It is possible that the obtained DNF be valid for a part of the table only. The corresponding test can be implemented with fzy_cmp_tab_dnf. 

fzy_dnf_tab - builds a choice table on a given fuzzy logic function (DNF)

On a given DNF of an FLF, it builds a complete CT. The CT contains n!2^n areas, where n is the number of FLF arguments.

fzy_cmp_tab_dnf - compares a choice table with a fuzzy logic function (DNF)

On the areas of a given CT, the function values are compared with the values computed according to a given DNF. The CT can be either complete or partial. Two tables are written: the first with the same values of function and the second with different values of function taken from the source table.

fzy_gen_tab - generates a random choice table for a given number of variables

It builds a complete CT with random values of function equal to arguments and negations of arguments. The CT contains n!2^n areas, where n is the number of FLF arguments.

No formal minimization of FLFs, for neither complete nor partial functions, has been implemented in the present toolbox.


Command line formats:
---------------------

>fzy_tab_syn tab_file result_files_prefix

>fzy_tab_dnf tab_file dnf_file

>fzy_dnf_tab dnf_file tab_file

>fzy_cmp_tab_dnf tab_file dnf_file comm_tab_file diff_tab_file

>fzy_gen_tab n tab_file [ rand_seed ]


Parameters:
-----------

n   		number of FLF arguments;

tab_file	a file which contains a CT either complete or partial;

dnf_file	a file which contains a DNF of an FLF;

comm_tab_file	rows of the source table where values of the functions coincide;

diff_tab_file	rows of the source table where values of the functions are different;

result_files_prefix	a prefix to create file names of subdomains using the following suffices: "-tab-<i>" - a subdomain, "-dnf-<i>" - its DNF.

rand_seed	an integer which is used as a seed to generate random values; on default the system time is used as a seed.


Formats of files:
-----------------

* A choice table file:

FZYTAB N
<a_i>   v_i
...
FZYTABEND [(M rows)]

"FZYTAB" - label of the table file beginning;
N - number of arguments;
M - number of table rows;
"FZYTABEND" - label of the table file end;
<a_i> - the current area (1<=i<=M);
v_i - the function value on the current area;

<a_i>: j_1 j_2 ... j_2N

where -N<=j_k<0, 0<j_k<=N, 1<=k<=2N;
j_k defines k-th item in the list <a_i> which equals to x_{j_k} if j_k>0 and equals to the negation ~x_{|j_k|} if j_k<0.

An example of the choice table file (f1_tab.txt) for the function f1:

FZYTAB 2
 1  2 -2 -1     2
 1 -2  2 -1     2
-1  2 -2  1    -2
-1 -2  2  1    -2
 2  1 -1 -2     1
 2 -1  1 -2     1
-2  1 -1  2    -1
-2 -1  1  2    -1
FZYTABEND (8 rows)

* A DNF file:

FZYDNF N
<c_i>
...
FZYDNFEND [(L conjuncts)]

"FZYDNF" - label of the DNF file beginning;
N - number of arguments;
L - number of conjuncts;
"FZYDNFEND" - label of the DNF file end;
<c_i> - the current conjunct (1<=i<=L);

<c_i>: j_1 j_2 ... j_{m_i}

where -N<=j_k<0, 0<j_k<=N, 1<=k<=m_i;
m_i - the number of items (variables and negations of variables) in the current conjunct <c_i>; j_k defines k-th item in the list <a_i> which equals to x_{j_k} if j_k>0 and equals to the negation ~x_{|j_k|} if j_k<0.

An example of the DNF file (f1_dnf.txt) for the function f1:

FZYDNF 2
1 -2
-1 2
FZYDNFEND (2 conjuncts)


Examples of command lines:
--------------------------

Source data: create file f1_dnf.txt specifying DNF of f1 by hand in a text editor.

>fzy_dnf_tab f1_dnf.txt f1_tab.txt

- creates a CT of f1 on its DNF file f1_dnf.txt and saves the resulting CT in file f1_tab.txt.

Check visually that it coincides with the table file shown above.

Source data: create file f2_tab.txt specifying CT of f2 by hand in a text editor.

>fzy_tab_dnf f2_tab.txt f2a_dnf.txt

- synthesize a DNF file f2_dnf.txt on the CT file f2_tab.txt

The obtained DNF file f2a_dnf.txt follows:

FZYDNF 2
-1 
2 -2 1 
FZYDNFEND (2 conjuncts)

>fzy_cmp_tab_dnf f2_tab.txt f2a_dnf.txt f2_tab_comm.txt f2_tab_diff.txt

- compares a function given by CT file f2_tab.txt with an FLF given by DNF file f2_dnf.txt; writes the coinciding rows to the file f2_tab_comm.txt; writes the different rows to the file f2_tab_diff.txt with the function values according to the source CT file (f2_tab.txt).

The obtained difference file f2_tab_diff.txt follows:

FZYTAB 2
 1  2 -2 -1     2
 2  1 -1 -2     1
-2  1 -1  2    -2
FZYTABEND (3 rows)

It is not empty; consequently f2 is not an FLF.

The obtained coinciding part of the CT represented with the file f2_tab_comm.txt follows:

FZYTAB 2
 1 -2  2 -1    -1
-1  2 -2  1     2
-1 -2  2  1    -2
 2 -1  1 -2    -1
-2 -1  1  2    -1
FZYTABEND (5 rows)

In fact it contains the rows where the function f2a specified with f2a_dnf.txt represents the source function f2.

Then we can synthesize a DNF for the difference file with

>fzy_tab_dnf f2_tab_diff.txt f2b.txt

to obtain the second DNF file f2b.txt to cover the source CT of f2:

FZYDNF 2
2 -2 -1 
1 -1 -2 
FZYDNFEND (2 conjuncts)

However, it is more convenient to use fzy_tab_syn which partitions the source CT automatically:

>fzy_tab_syn f2_tab.txt f2_syn

- partitions the source CT f2_tab.txt into subdomains and synthesizes an FLF represented with a DNF for each subdomain.

The following files are created: f2_syn-tab-0.txt, f2_syn-dnf-0.txt and 
f2_syn-tab-1.txt, f2_syn-dnf-1.txt specifying the obtained partitioning.

File f2_syn-tab-0.txt coincides with the above f2_tab_comm.txt and
f2_syn-dnf-0.txt coincides with the above f2a_dnf.txt
File f2_syn-tab-1.txt coincides with the above f2_tab_diff.txt and
f2_syn-dnf-1.txt coincides with the above f2b_dnf.txt

To try the toolbox on big random data we use fzy_gen_tab to create random CTs of specified number of arguments. 

>fzy_gen_tab 6 F3_6_rand_tab.txt

- creates a CT of a function of 6 arguments with random values.


References:
-----------

1. Zaitsev D.A., Sarbei V.G., Sleptsov A.I., Synthesis of continuous-valued logic functions defined in tabular form, Cybernetics and Systems Analysis, Volume 34, Number 2 (1998), 190-195, DOI: 10.1007/BF02742068

---------------------------
http://member.acm.org/~daze
---------------------------

