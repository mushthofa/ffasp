arc(0, 1) :- #49/50.
arc(0, 3) :- #41/50.
arc(0, 4) :- #41/50.
arc(0, 5) :- #43/50.
arc(0, 6) :- #93/100.
arc(1, 0) :- #83/100.
arc(1, 2) :- #24/25.
arc(1, 6) :- #81/100.
arc(2, 1) :- #47/50.
arc(2, 3) :- #97/100.
arc(2, 4) :- #9/10.
arc(2, 5) :- #47/50.
arc(2, 6) :- #19/20.
arc(3, 0) :- #93/100.
arc(3, 2) :- #81/100.
arc(3, 5) :- #24/25.
arc(3, 6) :- #1/1.
arc(4, 0) :- #83/100.
arc(4, 2) :- #97/100.
arc(4, 5) :- #22/25.
arc(5, 0) :- #24/25.
arc(5, 2) :- #87/100.
arc(5, 3) :- #23/25.
arc(5, 4) :- #41/50.
arc(6, 0) :- #17/20.
arc(6, 1) :- #9/10.
arc(6, 2) :- #21/25.
arc(6, 3) :- #91/100.
vertex(0) :- #1/2.
vertex(1) :- #59/100.
vertex(2) :- #53/100.
vertex(3) :- #29/50.
vertex(4) :- #16/25.
vertex(5) :- #16/25.
vertex(6) :- #13/25.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

