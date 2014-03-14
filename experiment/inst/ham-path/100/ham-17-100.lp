arc(0, 1) :- #21/25.
arc(0, 2) :- #9/10.
arc(0, 3) :- #93/100.
arc(0, 5) :- #93/100.
arc(1, 0) :- #83/100.
arc(1, 2) :- #17/20.
arc(1, 4) :- #9/10.
arc(2, 0) :- #81/100.
arc(2, 1) :- #19/20.
arc(2, 4) :- #19/20.
arc(2, 5) :- #97/100.
arc(2, 7) :- #83/100.
arc(3, 0) :- #22/25.
arc(3, 5) :- #97/100.
arc(4, 1) :- #21/25.
arc(4, 2) :- #89/100.
arc(4, 6) :- #23/25.
arc(4, 7) :- #89/100.
arc(5, 0) :- #9/10.
arc(5, 2) :- #89/100.
arc(5, 3) :- #49/50.
arc(5, 7) :- #87/100.
arc(6, 4) :- #41/50.
arc(6, 7) :- #97/100.
arc(7, 2) :- #43/50.
arc(7, 4) :- #91/100.
arc(7, 5) :- #24/25.
arc(7, 6) :- #49/50.
vertex(0) :- #69/100.
vertex(1) :- #14/25.
vertex(2) :- #61/100.
vertex(3) :- #51/100.
vertex(4) :- #69/100.
vertex(5) :- #29/50.
vertex(6) :- #57/100.
vertex(7) :- #17/25.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

