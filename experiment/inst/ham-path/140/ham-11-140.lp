arc(0, 2) :- #33/35.
arc(0, 3) :- #59/70.
arc(0, 4) :- #121/140.
arc(0, 5) :- #59/70.
arc(1, 2) :- #113/140.
arc(1, 4) :- #23/28.
arc(1, 5) :- #25/28.
arc(1, 6) :- #32/35.
arc(2, 0) :- #33/35.
arc(2, 1) :- #27/28.
arc(2, 4) :- #9/10.
arc(2, 5) :- #17/20.
arc(2, 6) :- #29/35.
arc(3, 0) :- #9/10.
arc(3, 4) :- #29/35.
arc(4, 0) :- #113/140.
arc(4, 1) :- #123/140.
arc(4, 2) :- #117/140.
arc(4, 3) :- #61/70.
arc(5, 0) :- #129/140.
arc(5, 1) :- #17/20.
arc(5, 2) :- #23/28.
arc(5, 6) :- #123/140.
arc(6, 1) :- #1/1.
arc(6, 2) :- #121/140.
arc(6, 5) :- #129/140.
vertex(0) :- #37/70.
vertex(1) :- #13/20.
vertex(2) :- #17/28.
vertex(3) :- #89/140.
vertex(4) :- #23/35.
vertex(5) :- #3/5.
vertex(6) :- #23/35.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

