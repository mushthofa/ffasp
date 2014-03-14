arc(0, 1) :- #19/20.
arc(0, 2) :- #17/20.
arc(0, 3) :- #37/40.
arc(0, 5) :- #9/10.
arc(1, 0) :- #39/40.
arc(1, 2) :- #79/80.
arc(1, 4) :- #79/80.
arc(2, 0) :- #73/80.
arc(2, 1) :- #33/40.
arc(2, 4) :- #33/40.
arc(2, 5) :- #39/40.
arc(2, 6) :- #79/80.
arc(3, 0) :- #19/20.
arc(3, 5) :- #69/80.
arc(4, 1) :- #69/80.
arc(4, 2) :- #73/80.
arc(4, 6) :- #77/80.
arc(5, 0) :- #73/80.
arc(5, 2) :- #19/20.
arc(5, 3) :- #15/16.
arc(5, 6) :- #15/16.
arc(6, 2) :- #77/80.
arc(6, 4) :- #4/5.
arc(6, 5) :- #67/80.
vertex(0) :- #27/40.
vertex(1) :- #49/80.
vertex(2) :- #5/8.
vertex(3) :- #21/40.
vertex(4) :- #7/10.
vertex(5) :- #43/80.
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

