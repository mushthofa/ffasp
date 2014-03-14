arc(0, 1) :- #4/5.
arc(0, 3) :- #33/40.
arc(0, 5) :- #7/8.
arc(0, 6) :- #33/40.
arc(0, 7) :- #33/40.
arc(1, 0) :- #39/40.
arc(1, 2) :- #37/40.
arc(1, 6) :- #33/40.
arc(2, 1) :- #19/20.
arc(2, 3) :- #17/20.
arc(2, 4) :- #7/8.
arc(2, 5) :- #39/40.
arc(2, 6) :- #7/8.
arc(3, 0) :- #17/20.
arc(3, 2) :- #7/8.
arc(3, 5) :- #1/1.
arc(3, 6) :- #7/8.
arc(4, 2) :- #33/40.
arc(4, 5) :- #1/1.
arc(4, 7) :- #37/40.
arc(5, 0) :- #19/20.
arc(5, 2) :- #37/40.
arc(5, 3) :- #33/40.
arc(5, 4) :- #7/8.
arc(5, 7) :- #7/8.
arc(6, 0) :- #39/40.
arc(6, 1) :- #39/40.
arc(6, 2) :- #17/20.
arc(6, 3) :- #7/8.
arc(7, 0) :- #4/5.
arc(7, 4) :- #37/40.
arc(7, 5) :- #1/1.
vertex(0) :- #21/40.
vertex(1) :- #23/40.
vertex(2) :- #7/10.
vertex(3) :- #3/5.
vertex(4) :- #21/40.
vertex(5) :- #27/40.
vertex(6) :- #3/5.
vertex(7) :- #7/10.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

