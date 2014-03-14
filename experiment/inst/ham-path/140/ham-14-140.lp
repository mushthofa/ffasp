arc(0, 1) :- #69/70.
arc(0, 3) :- #23/28.
arc(0, 4) :- #23/28.
arc(0, 5) :- #6/7.
arc(0, 6) :- #13/14.
arc(1, 0) :- #29/35.
arc(1, 2) :- #27/28.
arc(1, 6) :- #113/140.
arc(2, 1) :- #33/35.
arc(2, 3) :- #34/35.
arc(2, 4) :- #9/10.
arc(2, 5) :- #131/140.
arc(2, 6) :- #33/35.
arc(3, 0) :- #131/140.
arc(3, 2) :- #113/140.
arc(3, 5) :- #67/70.
arc(3, 6) :- #1/1.
arc(4, 0) :- #29/35.
arc(4, 2) :- #27/28.
arc(4, 5) :- #123/140.
arc(5, 0) :- #27/28.
arc(5, 2) :- #61/70.
arc(5, 3) :- #129/140.
arc(5, 4) :- #23/28.
arc(6, 0) :- #17/20.
arc(6, 1) :- #9/10.
arc(6, 2) :- #117/140.
arc(6, 3) :- #32/35.
vertex(0) :- #1/2.
vertex(1) :- #41/70.
vertex(2) :- #37/70.
vertex(3) :- #41/70.
vertex(4) :- #89/140.
vertex(5) :- #9/14.
vertex(6) :- #18/35.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

