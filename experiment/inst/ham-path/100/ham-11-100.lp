arc(0, 2) :- #47/50.
arc(0, 3) :- #21/25.
arc(0, 4) :- #43/50.
arc(0, 5) :- #21/25.
arc(1, 2) :- #81/100.
arc(1, 4) :- #41/50.
arc(1, 5) :- #89/100.
arc(1, 6) :- #23/25.
arc(2, 0) :- #19/20.
arc(2, 1) :- #24/25.
arc(2, 4) :- #9/10.
arc(2, 5) :- #17/20.
arc(2, 6) :- #83/100.
arc(3, 0) :- #9/10.
arc(3, 4) :- #83/100.
arc(4, 0) :- #4/5.
arc(4, 1) :- #22/25.
arc(4, 2) :- #21/25.
arc(4, 3) :- #87/100.
arc(5, 0) :- #23/25.
arc(5, 1) :- #17/20.
arc(5, 2) :- #41/50.
arc(5, 6) :- #22/25.
arc(6, 1) :- #1/1.
arc(6, 2) :- #43/50.
arc(6, 5) :- #23/25.
vertex(0) :- #53/100.
vertex(1) :- #13/20.
vertex(2) :- #3/5.
vertex(3) :- #63/100.
vertex(4) :- #33/50.
vertex(5) :- #3/5.
vertex(6) :- #33/50.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

