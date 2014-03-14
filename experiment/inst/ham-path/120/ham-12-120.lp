arc(0, 1) :- #19/20.
arc(0, 2) :- #103/120.
arc(0, 3) :- #37/40.
arc(0, 5) :- #107/120.
arc(1, 0) :- #39/40.
arc(1, 2) :- #119/120.
arc(1, 4) :- #59/60.
arc(2, 0) :- #109/120.
arc(2, 1) :- #5/6.
arc(2, 4) :- #33/40.
arc(2, 5) :- #29/30.
arc(2, 6) :- #59/60.
arc(3, 0) :- #19/20.
arc(3, 5) :- #103/120.
arc(4, 1) :- #13/15.
arc(4, 2) :- #109/120.
arc(4, 6) :- #29/30.
arc(5, 0) :- #11/12.
arc(5, 2) :- #19/20.
arc(5, 3) :- #113/120.
arc(5, 6) :- #14/15.
arc(6, 2) :- #29/30.
arc(6, 4) :- #4/5.
arc(6, 5) :- #5/6.
vertex(0) :- #2/3.
vertex(1) :- #37/60.
vertex(2) :- #5/8.
vertex(3) :- #31/60.
vertex(4) :- #7/10.
vertex(5) :- #13/24.
vertex(6) :- #71/120.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

