arc(0, 1) :- #17/20.
arc(0, 2) :- #9/10.
arc(0, 3) :- #37/40.
arc(0, 5) :- #37/40.
arc(1, 0) :- #33/40.
arc(1, 2) :- #17/20.
arc(1, 4) :- #9/10.
arc(2, 0) :- #13/16.
arc(2, 1) :- #19/20.
arc(2, 4) :- #19/20.
arc(2, 5) :- #77/80.
arc(2, 7) :- #67/80.
arc(3, 0) :- #71/80.
arc(3, 5) :- #39/40.
arc(4, 1) :- #67/80.
arc(4, 2) :- #9/10.
arc(4, 6) :- #73/80.
arc(4, 7) :- #71/80.
arc(5, 0) :- #9/10.
arc(5, 2) :- #71/80.
arc(5, 3) :- #39/40.
arc(5, 7) :- #7/8.
arc(6, 4) :- #13/16.
arc(6, 7) :- #77/80.
arc(7, 2) :- #69/80.
arc(7, 4) :- #73/80.
arc(7, 5) :- #19/20.
arc(7, 6) :- #39/40.
vertex(0) :- #7/10.
vertex(1) :- #9/16.
vertex(2) :- #49/80.
vertex(3) :- #1/2.
vertex(4) :- #11/16.
vertex(5) :- #23/40.
vertex(6) :- #9/16.
vertex(7) :- #11/16.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

