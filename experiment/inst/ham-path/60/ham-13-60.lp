arc(0, 2) :- #29/30.
arc(0, 3) :- #19/20.
arc(0, 4) :- #49/60.
arc(1, 2) :- #5/6.
arc(1, 5) :- #11/12.
arc(1, 6) :- #5/6.
arc(2, 0) :- #53/60.
arc(2, 1) :- #49/60.
arc(2, 3) :- #5/6.
arc(2, 4) :- #5/6.
arc(2, 6) :- #5/6.
arc(3, 0) :- #29/30.
arc(3, 2) :- #13/15.
arc(3, 5) :- #59/60.
arc(3, 6) :- #29/30.
arc(4, 0) :- #17/20.
arc(4, 2) :- #53/60.
arc(5, 1) :- #17/20.
arc(5, 3) :- #17/20.
arc(5, 6) :- #17/20.
arc(6, 1) :- #53/60.
arc(6, 2) :- #9/10.
arc(6, 3) :- #13/15.
arc(6, 5) :- #13/15.
vertex(0) :- #13/20.
vertex(1) :- #13/20.
vertex(2) :- #37/60.
vertex(3) :- #2/3.
vertex(4) :- #37/60.
vertex(5) :- #31/60.
vertex(6) :- #11/20.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

