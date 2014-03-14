arc(0, 2) :- #97/100.
arc(0, 3) :- #24/25.
arc(0, 4) :- #33/40.
arc(1, 2) :- #167/200.
arc(1, 5) :- #91/100.
arc(1, 6) :- #167/200.
arc(2, 0) :- #22/25.
arc(2, 1) :- #163/200.
arc(2, 3) :- #167/200.
arc(2, 4) :- #83/100.
arc(2, 6) :- #33/40.
arc(3, 0) :- #193/200.
arc(3, 2) :- #43/50.
arc(3, 5) :- #49/50.
arc(3, 6) :- #24/25.
arc(4, 0) :- #171/200.
arc(4, 2) :- #7/8.
arc(5, 1) :- #171/200.
arc(5, 3) :- #17/20.
arc(5, 6) :- #43/50.
arc(6, 1) :- #89/100.
arc(6, 2) :- #181/200.
arc(6, 3) :- #7/8.
arc(6, 5) :- #87/100.
vertex(0) :- #129/200.
vertex(1) :- #33/50.
vertex(2) :- #61/100.
vertex(3) :- #27/40.
vertex(4) :- #61/100.
vertex(5) :- #103/200.
vertex(6) :- #109/200.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

