arc(0, 2) :- #1/1.
arc(0, 4) :- #59/60.
arc(0, 6) :- #59/60.
arc(1, 3) :- #9/10.
arc(1, 5) :- #49/60.
arc(1, 6) :- #5/6.
arc(2, 0) :- #59/60.
arc(2, 3) :- #53/60.
arc(2, 4) :- #4/5.
arc(2, 5) :- #17/20.
arc(2, 6) :- #49/60.
arc(3, 1) :- #59/60.
arc(3, 2) :- #9/10.
arc(3, 5) :- #53/60.
arc(3, 6) :- #5/6.
arc(4, 0) :- #53/60.
arc(4, 2) :- #49/60.
arc(4, 5) :- #5/6.
arc(5, 1) :- #5/6.
arc(5, 2) :- #5/6.
arc(5, 3) :- #17/20.
arc(5, 4) :- #5/6.
arc(6, 0) :- #49/60.
arc(6, 1) :- #9/10.
arc(6, 2) :- #29/30.
arc(6, 3) :- #53/60.
vertex(0) :- #1/2.
vertex(1) :- #2/3.
vertex(2) :- #2/3.
vertex(3) :- #31/60.
vertex(4) :- #8/15.
vertex(5) :- #11/20.
vertex(6) :- #2/3.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

