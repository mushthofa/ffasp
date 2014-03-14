arc(0, 1) :- #4/5.
arc(0, 3) :- #5/6.
arc(0, 5) :- #13/15.
arc(0, 6) :- #5/6.
arc(0, 7) :- #5/6.
arc(1, 0) :- #29/30.
arc(1, 2) :- #11/12.
arc(1, 6) :- #5/6.
arc(2, 1) :- #14/15.
arc(2, 3) :- #17/20.
arc(2, 4) :- #13/15.
arc(2, 5) :- #59/60.
arc(2, 6) :- #13/15.
arc(3, 0) :- #17/20.
arc(3, 2) :- #53/60.
arc(3, 5) :- #59/60.
arc(3, 6) :- #53/60.
arc(4, 2) :- #49/60.
arc(4, 5) :- #59/60.
arc(4, 7) :- #11/12.
arc(5, 0) :- #14/15.
arc(5, 2) :- #14/15.
arc(5, 3) :- #5/6.
arc(5, 4) :- #53/60.
arc(5, 7) :- #13/15.
arc(6, 0) :- #59/60.
arc(6, 1) :- #29/30.
arc(6, 2) :- #17/20.
arc(6, 3) :- #13/15.
arc(7, 0) :- #4/5.
arc(7, 4) :- #14/15.
arc(7, 5) :- #1/1.
vertex(0) :- #8/15.
vertex(1) :- #17/30.
vertex(2) :- #41/60.
vertex(3) :- #37/60.
vertex(4) :- #31/60.
vertex(5) :- #2/3.
vertex(6) :- #37/60.
vertex(7) :- #7/10.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

