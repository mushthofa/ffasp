arc(0, 2) :- #37/40.
arc(0, 4) :- #17/20.
arc(0, 6) :- #39/40.
arc(0, 7) :- #7/8.
arc(1, 3) :- #7/8.
arc(1, 5) :- #33/40.
arc(1, 6) :- #7/8.
arc(2, 0) :- #33/40.
arc(2, 3) :- #33/40.
arc(2, 6) :- #19/20.
arc(2, 7) :- #39/40.
arc(3, 1) :- #7/8.
arc(3, 2) :- #7/8.
arc(3, 5) :- #39/40.
arc(3, 6) :- #37/40.
arc(3, 7) :- #39/40.
arc(4, 0) :- #9/10.
arc(4, 5) :- #9/10.
arc(4, 7) :- #19/20.
arc(5, 1) :- #33/40.
arc(5, 3) :- #37/40.
arc(5, 4) :- #7/8.
arc(5, 7) :- #9/10.
arc(6, 0) :- #19/20.
arc(6, 1) :- #39/40.
arc(6, 2) :- #7/8.
arc(6, 3) :- #33/40.
arc(7, 0) :- #39/40.
arc(7, 2) :- #19/20.
arc(7, 3) :- #17/20.
arc(7, 4) :- #17/20.
arc(7, 5) :- #39/40.
vertex(0) :- #21/40.
vertex(1) :- #1/2.
vertex(2) :- #27/40.
vertex(3) :- #5/8.
vertex(4) :- #27/40.
vertex(5) :- #23/40.
vertex(6) :- #27/40.
vertex(7) :- #1/2.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

