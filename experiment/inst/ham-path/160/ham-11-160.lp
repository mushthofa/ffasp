arc(0, 2) :- #151/160.
arc(0, 3) :- #67/80.
arc(0, 4) :- #69/80.
arc(0, 5) :- #27/32.
arc(1, 2) :- #129/160.
arc(1, 4) :- #33/40.
arc(1, 5) :- #143/160.
arc(1, 6) :- #147/160.
arc(2, 0) :- #151/160.
arc(2, 1) :- #77/80.
arc(2, 4) :- #9/10.
arc(2, 5) :- #17/20.
arc(2, 6) :- #133/160.
arc(3, 0) :- #9/10.
arc(3, 4) :- #33/40.
arc(4, 0) :- #129/160.
arc(4, 1) :- #7/8.
arc(4, 2) :- #67/80.
arc(4, 3) :- #139/160.
arc(5, 0) :- #147/160.
arc(5, 1) :- #17/20.
arc(5, 2) :- #33/40.
arc(5, 6) :- #7/8.
arc(6, 1) :- #1/1.
arc(6, 2) :- #69/80.
arc(6, 5) :- #147/160.
vertex(0) :- #21/40.
vertex(1) :- #13/20.
vertex(2) :- #97/160.
vertex(3) :- #101/160.
vertex(4) :- #21/32.
vertex(5) :- #3/5.
vertex(6) :- #53/80.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

