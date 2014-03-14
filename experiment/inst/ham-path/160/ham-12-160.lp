arc(0, 1) :- #19/20.
arc(0, 2) :- #137/160.
arc(0, 3) :- #37/40.
arc(0, 5) :- #143/160.
arc(1, 0) :- #39/40.
arc(1, 2) :- #159/160.
arc(1, 4) :- #157/160.
arc(2, 0) :- #73/80.
arc(2, 1) :- #133/160.
arc(2, 4) :- #33/40.
arc(2, 5) :- #31/32.
arc(2, 6) :- #157/160.
arc(3, 0) :- #19/20.
arc(3, 5) :- #137/160.
arc(4, 1) :- #69/80.
arc(4, 2) :- #29/32.
arc(4, 6) :- #77/80.
arc(5, 0) :- #73/80.
arc(5, 2) :- #153/160.
arc(5, 3) :- #15/16.
arc(5, 6) :- #149/160.
arc(6, 2) :- #31/32.
arc(6, 4) :- #4/5.
arc(6, 5) :- #67/80.
vertex(0) :- #107/160.
vertex(1) :- #49/80.
vertex(2) :- #5/8.
vertex(3) :- #83/160.
vertex(4) :- #7/10.
vertex(5) :- #87/160.
vertex(6) :- #47/80.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

