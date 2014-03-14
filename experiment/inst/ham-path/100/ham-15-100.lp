arc(0, 2) :- #1/1.
arc(0, 4) :- #49/50.
arc(0, 6) :- #99/100.
arc(1, 3) :- #91/100.
arc(1, 5) :- #81/100.
arc(1, 6) :- #21/25.
arc(2, 0) :- #49/50.
arc(2, 3) :- #89/100.
arc(2, 4) :- #4/5.
arc(2, 5) :- #17/20.
arc(2, 6) :- #41/50.
arc(3, 1) :- #99/100.
arc(3, 2) :- #9/10.
arc(3, 5) :- #22/25.
arc(3, 6) :- #83/100.
arc(4, 0) :- #22/25.
arc(4, 2) :- #41/50.
arc(4, 5) :- #21/25.
arc(5, 1) :- #83/100.
arc(5, 2) :- #21/25.
arc(5, 3) :- #17/20.
arc(5, 4) :- #83/100.
arc(6, 0) :- #81/100.
arc(6, 1) :- #91/100.
arc(6, 2) :- #97/100.
arc(6, 3) :- #22/25.
vertex(0) :- #1/2.
vertex(1) :- #67/100.
vertex(2) :- #67/100.
vertex(3) :- #51/100.
vertex(4) :- #27/50.
vertex(5) :- #11/20.
vertex(6) :- #67/100.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

