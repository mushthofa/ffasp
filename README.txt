FFASP
A finite-valued fuzzy answer set solver
(c) 2014 Mushthofa
Mushthofa.Mushthofa (AT) UGent.be
==============================================================================

HOW TO BUILD 
-------------
System requirements:
*NIX system (Linux, FreeBSD, MacOS X) with GCC>=4.7 and CMake>=2.8
Might compile on Windows (with Cygwin), but never tested.

1) Install Boost Libraries (>=1.55).
http://www.boost.org/
Make sure it can be found in your include path
e.g. : in '/usr/include/', /'usr/local/include/' etc.

2) Download 'clingo' (>=4.3.0) from the Potassco suite.
http://potassco.sourceforge.net/
Install it in your binary path, e.g. '/usr/bin/' or '/usr/local/bin/'
Make sure it can be called using the following command

$ clingo


3) Run the following commands in the directory ffasp :

$ mkdir build
$ cd build
$ cmake ../
$ make

Compilation will proceed and an executable named 'ffasp' will be created.

USAGE
-----------------

Run with option '-h' to get the usage information.

$ ./ffasp -h

USAGE: 	./ffasp [options] [<input-file>]

E.g.: 	./ffasp --maxk=200 -c program.lp

Options are:
--maxk=<n> 	= find k-answer sets up to k=<n> (default <n>=100).
--maxt=<t> 	= stop after computation exceeds <t> seconds, approximately (default <t>=600 s).
--trans=<k> 	= only perform translation with k=<k> and print the result to <STDOUT>.
--rnd=<d> 	= only perform rewriting of the program and rounding the constants 
		  in the program to rational numbers with denominator=<d>.
-c/--check 	= only check for satisfiability/consistency, no answer set is printed.
-h/--help  	= show this help and exit.

If no <input-file> is given, input is read from <STDIN>

INPUT LANGUAGE
----------------

- A term is either a constant symbol ([a-z][(A-Z)|(0-9)]*) or a quoted string or an integer.
e.g. : abc123, "Hello World", 2012.

- A variable is symbol which starts with either a capital, or the character '_' (anonymous variables).
e.g. : X, VAR1, _

- A regular atom is an expression of the form 'p(T1, T2, ..., Tn)', where p is the atom name (symbol) 
and T1..Tn are its arguments, which are either a term or a variable.
e.g. : a, p(0), connect(X, Y, 1)

- A constant atom is an expression of the form '#a/b' or '#c' where a and b are integers such that 0<b<=a 
and c is a rational number from [0,1] written in decimal format. If the value of a/b or c is outside of [0,1], 
it will be converted to 0 or 1 accordingly.
e.g. : #2/5, #0.35

- A literal is either an atom 'a' or a constant atom #c

- A comparison predicate is an expression of the form
T1 op T2
where T1 and T2 are either variables or terms and op is one of the operators {=, !=, >, <, >=, <=}.
e.g. : X<Y, VAR_1>=0

- A body literal is either a positive literal 'l', or a NAF-literal 'not l', where l is a regular atom, or a comparison predicate.
e.g. : not edge(1,3).

- A fact is an expression of the form
a :- #c.
where a is a regular atom and #c is a constant atom. 
The special fact
a.
is a shorthand for
a :- #1.

- A constraint is an expression of the form
#c :- a.
The special constraint
:- a.
is a shorthand for
#0 :- a.

- A rule is an expression of the form
a1 op_1 a2 op_1 ... op_1 an :- b1 op_2 b2 op_2 ... op_2 bm.
where a1,...,an are literals and b1, b2, ..., bm are body literals, 
while each of op_1 and op_2 is one of the Lukasiewicz operators:
* = T-norm (alias: ',')
+ = T-conorm (alias: '|')
& = max
^ = min
E.g. : 
a+b :- c * not d * #0.2.
p(X,Y)^r(Y) :- q(X)*s(Y)*X>Y.
t :- t+t.

- Rules must be safe, i.e. each variable appearing in a rule must also appear in one of the positive body literals.
Rules such as:
p(X,Y) :- q(X)+not r(Y). 
q(X) :- p(X), X>Y.	
are not safe.

- Comparison predicates can only be used in the body of a rule in conjunction with the operator *, i.e. rules such as
p(X,Y) :- q(X,Y)+X>Y.
are not allowed.

- Only one fact/constraint/rule is allowed per line of input.

EXAMPLES
---------------
1) Run 'ffasp'

$ ./ffasp
% Reading from <STDIN> (finish with Ctrl-D) %

Type in the following program and end with 'Ctrl-D':
a :- not b.
b :- not a.
#0.4 :- a.
#0.9 :- b.
<Ctrl-D>
{a[0.1], b[0.9]}
Satisfiable.

2) Run ffasp with the following program

$ ./ffasp
% Reading from <STDIN> (finish with Ctrl-D) %
a+b.      
#0.2 :- a.
#0.3 :- b.
No k-answer set is found until k = 100 and time = 2 s


3) Write the following program:
a1 :- not a1.
a2 + a2 :- a1.
a3 + a3 :- a2.
a4 + a4 :- a3.
a5 + a5 :- a4.
and save it to a file named 'test.lp'
This program has only one answer set, which is 
{a1[1/2], a2[1/4], a3[1/8], a4[1/16], a5[1/32]}

Run ffasp on the program:

$ ./ffasp test.lp
{a1[0.5], a2[0.25], a3[0.125], a4[0.0625], a5[0.03125]}
Satisfiable.

Now run while setting the maximum value of k to 30
$./ffasp --maxk=30 test.lp
No k-answer set is found until k = 30 and time = 2 s



