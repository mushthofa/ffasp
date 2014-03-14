FFASP
A finite-valued fuzzy answer set solver
(c) 2014 Mushthofa
Mushthofa.Mushthofa@UGent.be
==============================================================================
HOW TO BUILD 

1) Install Boost Libraries (>=1.55).
http://www.boost.org/
Make sure it can be found in your include path
e.g. : in '/usr/include/', /'usr/local/include/' etc.

2) Download 'clingo' (>=4.3.0) from the Potassco suite.
http://potassco.sourceforge.net/
Install it in your binary path, e.g. '/usr/bin/' or '/usr/local/bin/'
Make sure it can be called using the following command

$ clingo


3) Go to the 'build/release' directory in 'ffasp', and run

$ make

Compilation will proceed and an executable named 'ffasp' will be created.
Run with option '-h' to get usage information.

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



