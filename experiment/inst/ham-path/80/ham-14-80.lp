arc(0, 1) :- #79/80.
arc(0, 3) :- #33/40.
arc(0, 4) :- #33/40.
arc(0, 5) :- #69/80.
arc(0, 6) :- #37/40.
arc(1, 0) :- #33/40.
arc(1, 2) :- #77/80.
arc(1, 6) :- #13/16.
arc(2, 1) :- #15/16.
arc(2, 3) :- #39/40.
arc(2, 4) :- #9/10.
arc(2, 5) :- #15/16.
arc(2, 6) :- #19/20.
arc(3, 0) :- #15/16.
arc(3, 2) :- #13/16.
arc(3, 5) :- #77/80.
arc(3, 6) :- #1/1.
arc(4, 0) :- #33/40.
arc(4, 2) :- #77/80.
arc(4, 5) :- #71/80.
arc(5, 0) :- #77/80.
arc(5, 2) :- #7/8.
arc(5, 3) :- #37/40.
arc(5, 4) :- #33/40.
arc(6, 0) :- #17/20.
arc(6, 1) :- #9/10.
arc(6, 2) :- #67/80.
arc(6, 3) :- #73/80.
vertex(0) :- #1/2.
vertex(1) :- #47/80.
vertex(2) :- #43/80.
vertex(3) :- #47/80.
vertex(4) :- #51/80.
vertex(5) :- #51/80.
vertex(6) :- #41/80.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

