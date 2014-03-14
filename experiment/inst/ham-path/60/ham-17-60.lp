arc(0, 1) :- #17/20.
arc(0, 2) :- #9/10.
arc(0, 3) :- #14/15.
arc(0, 5) :- #14/15.
arc(1, 0) :- #5/6.
arc(1, 2) :- #17/20.
arc(1, 4) :- #9/10.
arc(2, 0) :- #49/60.
arc(2, 1) :- #19/20.
arc(2, 4) :- #19/20.
arc(2, 5) :- #29/30.
arc(2, 7) :- #5/6.
arc(3, 0) :- #53/60.
arc(3, 5) :- #29/30.
arc(4, 1) :- #5/6.
arc(4, 2) :- #9/10.
arc(4, 6) :- #11/12.
arc(4, 7) :- #9/10.
arc(5, 0) :- #9/10.
arc(5, 2) :- #53/60.
arc(5, 3) :- #59/60.
arc(5, 7) :- #13/15.
arc(6, 4) :- #49/60.
arc(6, 7) :- #29/30.
arc(7, 2) :- #13/15.
arc(7, 4) :- #9/10.
arc(7, 5) :- #19/20.
arc(7, 6) :- #59/60.
vertex(0) :- #7/10.
vertex(1) :- #17/30.
vertex(2) :- #37/60.
vertex(3) :- #1/2.
vertex(4) :- #41/60.
vertex(5) :- #7/12.
vertex(6) :- #17/30.
vertex(7) :- #41/60.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

