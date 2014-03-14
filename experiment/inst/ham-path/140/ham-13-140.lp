arc(0, 2) :- #34/35.
arc(0, 3) :- #67/70.
arc(0, 4) :- #23/28.
arc(1, 2) :- #117/140.
arc(1, 5) :- #32/35.
arc(1, 6) :- #117/140.
arc(2, 0) :- #123/140.
arc(2, 1) :- #57/70.
arc(2, 3) :- #117/140.
arc(2, 4) :- #29/35.
arc(2, 6) :- #29/35.
arc(3, 0) :- #27/28.
arc(3, 2) :- #6/7.
arc(3, 5) :- #137/140.
arc(3, 6) :- #67/70.
arc(4, 0) :- #17/20.
arc(4, 2) :- #123/140.
arc(5, 1) :- #17/20.
arc(5, 3) :- #17/20.
arc(5, 6) :- #6/7.
arc(6, 1) :- #25/28.
arc(6, 2) :- #9/10.
arc(6, 3) :- #61/70.
arc(6, 5) :- #61/70.
vertex(0) :- #13/20.
vertex(1) :- #23/35.
vertex(2) :- #43/70.
vertex(3) :- #47/70.
vertex(4) :- #17/28.
vertex(5) :- #18/35.
vertex(6) :- #19/35.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

