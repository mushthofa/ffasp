arc(0, 1) :- #19/20.
arc(0, 2) :- #43/50.
arc(0, 3) :- #23/25.
arc(0, 5) :- #89/100.
arc(1, 0) :- #49/50.
arc(1, 2) :- #99/100.
arc(1, 4) :- #49/50.
arc(2, 0) :- #91/100.
arc(2, 1) :- #83/100.
arc(2, 4) :- #83/100.
arc(2, 5) :- #97/100.
arc(2, 6) :- #49/50.
arc(3, 0) :- #19/20.
arc(3, 5) :- #43/50.
arc(4, 1) :- #87/100.
arc(4, 2) :- #91/100.
arc(4, 6) :- #24/25.
arc(5, 0) :- #91/100.
arc(5, 2) :- #19/20.
arc(5, 3) :- #47/50.
arc(5, 6) :- #93/100.
arc(6, 2) :- #97/100.
arc(6, 4) :- #4/5.
arc(6, 5) :- #21/25.
vertex(0) :- #67/100.
vertex(1) :- #61/100.
vertex(2) :- #63/100.
vertex(3) :- #13/25.
vertex(4) :- #7/10.
vertex(5) :- #27/50.
vertex(6) :- #59/100.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

