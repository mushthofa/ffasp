arc(0, 2) :- #9/10.
arc(0, 3) :- #1/1.
arc(0, 4) :- #13/16.
arc(1, 2) :- #39/40.
arc(1, 5) :- #67/80.
arc(1, 6) :- #17/20.
arc(1, 7) :- #79/80.
arc(2, 0) :- #33/40.
arc(2, 1) :- #37/40.
arc(2, 3) :- #7/8.
arc(2, 4) :- #13/16.
arc(2, 7) :- #9/10.
arc(3, 0) :- #13/16.
arc(3, 2) :- #77/80.
arc(3, 5) :- #77/80.
arc(3, 7) :- #4/5.
arc(4, 0) :- #73/80.
arc(4, 2) :- #79/80.
arc(5, 1) :- #7/8.
arc(5, 3) :- #39/40.
arc(5, 6) :- #15/16.
arc(5, 7) :- #77/80.
arc(6, 1) :- #33/40.
arc(6, 5) :- #77/80.
arc(6, 7) :- #73/80.
arc(7, 1) :- #19/20.
arc(7, 2) :- #17/20.
arc(7, 3) :- #79/80.
arc(7, 5) :- #9/10.
arc(7, 6) :- #69/80.
vertex(0) :- #11/20.
vertex(1) :- #27/40.
vertex(2) :- #43/80.
vertex(3) :- #5/8.
vertex(4) :- #47/80.
vertex(5) :- #47/80.
vertex(6) :- #5/8.
vertex(7) :- #9/16.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

