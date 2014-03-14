arc(0, 2) :- #97/100.
arc(0, 3) :- #24/25.
arc(0, 4) :- #41/50.
arc(1, 2) :- #21/25.
arc(1, 5) :- #91/100.
arc(1, 6) :- #21/25.
arc(2, 0) :- #22/25.
arc(2, 1) :- #41/50.
arc(2, 3) :- #21/25.
arc(2, 4) :- #83/100.
arc(2, 6) :- #83/100.
arc(3, 0) :- #97/100.
arc(3, 2) :- #43/50.
arc(3, 5) :- #49/50.
arc(3, 6) :- #24/25.
arc(4, 0) :- #17/20.
arc(4, 2) :- #22/25.
arc(5, 1) :- #17/20.
arc(5, 3) :- #17/20.
arc(5, 6) :- #43/50.
arc(6, 1) :- #89/100.
arc(6, 2) :- #9/10.
arc(6, 3) :- #87/100.
arc(6, 5) :- #87/100.
vertex(0) :- #13/20.
vertex(1) :- #33/50.
vertex(2) :- #61/100.
vertex(3) :- #67/100.
vertex(4) :- #61/100.
vertex(5) :- #51/100.
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

