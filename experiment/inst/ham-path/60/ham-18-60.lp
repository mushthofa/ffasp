arc(0, 2) :- #9/10.
arc(0, 3) :- #1/1.
arc(0, 4) :- #49/60.
arc(1, 2) :- #59/60.
arc(1, 5) :- #5/6.
arc(1, 6) :- #17/20.
arc(1, 7) :- #59/60.
arc(2, 0) :- #49/60.
arc(2, 1) :- #11/12.
arc(2, 3) :- #13/15.
arc(2, 4) :- #4/5.
arc(2, 7) :- #9/10.
arc(3, 0) :- #49/60.
arc(3, 2) :- #19/20.
arc(3, 5) :- #29/30.
arc(3, 7) :- #4/5.
arc(4, 0) :- #11/12.
arc(4, 2) :- #59/60.
arc(5, 1) :- #53/60.
arc(5, 3) :- #29/30.
arc(5, 6) :- #14/15.
arc(5, 7) :- #29/30.
arc(6, 1) :- #49/60.
arc(6, 5) :- #29/30.
arc(6, 7) :- #11/12.
arc(7, 1) :- #19/20.
arc(7, 2) :- #17/20.
arc(7, 3) :- #1/1.
arc(7, 5) :- #9/10.
arc(7, 6) :- #13/15.
vertex(0) :- #11/20.
vertex(1) :- #41/60.
vertex(2) :- #11/20.
vertex(3) :- #19/30.
vertex(4) :- #3/5.
vertex(5) :- #7/12.
vertex(6) :- #19/30.
vertex(7) :- #17/30.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

