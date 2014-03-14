arc(0, 2) :- #14/15.
arc(0, 4) :- #17/20.
arc(0, 6) :- #59/60.
arc(0, 7) :- #13/15.
arc(1, 3) :- #53/60.
arc(1, 5) :- #5/6.
arc(1, 6) :- #53/60.
arc(2, 0) :- #49/60.
arc(2, 3) :- #5/6.
arc(2, 6) :- #19/20.
arc(2, 7) :- #29/30.
arc(3, 1) :- #53/60.
arc(3, 2) :- #53/60.
arc(3, 5) :- #59/60.
arc(3, 6) :- #11/12.
arc(3, 7) :- #29/30.
arc(4, 0) :- #11/12.
arc(4, 5) :- #9/10.
arc(4, 7) :- #19/20.
arc(5, 1) :- #5/6.
arc(5, 3) :- #14/15.
arc(5, 4) :- #13/15.
arc(5, 7) :- #9/10.
arc(6, 0) :- #14/15.
arc(6, 1) :- #59/60.
arc(6, 2) :- #53/60.
arc(6, 3) :- #5/6.
arc(7, 0) :- #59/60.
arc(7, 2) :- #19/20.
arc(7, 3) :- #17/20.
arc(7, 4) :- #13/15.
arc(7, 5) :- #29/30.
vertex(0) :- #8/15.
vertex(1) :- #1/2.
vertex(2) :- #41/60.
vertex(3) :- #37/60.
vertex(4) :- #41/60.
vertex(5) :- #7/12.
vertex(6) :- #41/60.
vertex(7) :- #1/2.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

