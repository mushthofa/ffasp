arc(0, 2) :- #39/40.
arc(0, 3) :- #77/80.
arc(0, 4) :- #33/40.
arc(1, 2) :- #67/80.
arc(1, 5) :- #73/80.
arc(1, 6) :- #67/80.
arc(2, 0) :- #7/8.
arc(2, 1) :- #13/16.
arc(2, 3) :- #67/80.
arc(2, 4) :- #33/40.
arc(2, 6) :- #33/40.
arc(3, 0) :- #77/80.
arc(3, 2) :- #69/80.
arc(3, 5) :- #39/40.
arc(3, 6) :- #77/80.
arc(4, 0) :- #17/20.
arc(4, 2) :- #7/8.
arc(5, 1) :- #17/20.
arc(5, 3) :- #17/20.
arc(5, 6) :- #69/80.
arc(6, 1) :- #71/80.
arc(6, 2) :- #9/10.
arc(6, 3) :- #7/8.
arc(6, 5) :- #69/80.
vertex(0) :- #13/20.
vertex(1) :- #53/80.
vertex(2) :- #49/80.
vertex(3) :- #27/40.
vertex(4) :- #49/80.
vertex(5) :- #41/80.
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

