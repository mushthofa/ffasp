arc(0, 2) :- #19/20.
arc(0, 3) :- #5/6.
arc(0, 4) :- #13/15.
arc(0, 5) :- #5/6.
arc(1, 2) :- #4/5.
arc(1, 4) :- #49/60.
arc(1, 5) :- #53/60.
arc(1, 6) :- #11/12.
arc(2, 0) :- #19/20.
arc(2, 1) :- #29/30.
arc(2, 4) :- #9/10.
arc(2, 5) :- #17/20.
arc(2, 6) :- #5/6.
arc(3, 0) :- #9/10.
arc(3, 4) :- #5/6.
arc(4, 0) :- #4/5.
arc(4, 1) :- #53/60.
arc(4, 2) :- #5/6.
arc(4, 3) :- #13/15.
arc(5, 0) :- #11/12.
arc(5, 1) :- #17/20.
arc(5, 2) :- #49/60.
arc(5, 6) :- #53/60.
arc(6, 1) :- #1/1.
arc(6, 2) :- #13/15.
arc(6, 5) :- #11/12.
vertex(0) :- #8/15.
vertex(1) :- #13/20.
vertex(2) :- #3/5.
vertex(3) :- #19/30.
vertex(4) :- #13/20.
vertex(5) :- #3/5.
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

