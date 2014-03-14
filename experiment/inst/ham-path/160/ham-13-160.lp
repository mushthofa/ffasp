arc(0, 2) :- #31/32.
arc(0, 3) :- #153/160.
arc(0, 4) :- #33/40.
arc(1, 2) :- #67/80.
arc(1, 5) :- #73/80.
arc(1, 6) :- #67/80.
arc(2, 0) :- #7/8.
arc(2, 1) :- #131/160.
arc(2, 3) :- #67/80.
arc(2, 4) :- #133/160.
arc(2, 6) :- #33/40.
arc(3, 0) :- #31/32.
arc(3, 2) :- #69/80.
arc(3, 5) :- #157/160.
arc(3, 6) :- #153/160.
arc(4, 0) :- #17/20.
arc(4, 2) :- #7/8.
arc(5, 1) :- #17/20.
arc(5, 3) :- #17/20.
arc(5, 6) :- #137/160.
arc(6, 1) :- #143/160.
arc(6, 2) :- #9/10.
arc(6, 3) :- #7/8.
arc(6, 5) :- #139/160.
vertex(0) :- #13/20.
vertex(1) :- #21/32.
vertex(2) :- #49/80.
vertex(3) :- #27/40.
vertex(4) :- #97/160.
vertex(5) :- #41/80.
vertex(6) :- #87/160.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

