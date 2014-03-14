arc(0, 1) :- #59/60.
arc(0, 3) :- #49/60.
arc(0, 4) :- #49/60.
arc(0, 5) :- #17/20.
arc(0, 6) :- #14/15.
arc(1, 0) :- #5/6.
arc(1, 2) :- #29/30.
arc(1, 6) :- #4/5.
arc(2, 1) :- #19/20.
arc(2, 3) :- #29/30.
arc(2, 4) :- #9/10.
arc(2, 5) :- #14/15.
arc(2, 6) :- #19/20.
arc(3, 0) :- #14/15.
arc(3, 2) :- #4/5.
arc(3, 5) :- #29/30.
arc(3, 6) :- #1/1.
arc(4, 0) :- #5/6.
arc(4, 2) :- #29/30.
arc(4, 5) :- #53/60.
arc(5, 0) :- #29/30.
arc(5, 2) :- #13/15.
arc(5, 3) :- #11/12.
arc(5, 4) :- #49/60.
arc(6, 0) :- #17/20.
arc(6, 1) :- #9/10.
arc(6, 2) :- #5/6.
arc(6, 3) :- #11/12.
vertex(0) :- #1/2.
vertex(1) :- #7/12.
vertex(2) :- #8/15.
vertex(3) :- #7/12.
vertex(4) :- #19/30.
vertex(5) :- #19/30.
vertex(6) :- #31/60.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

