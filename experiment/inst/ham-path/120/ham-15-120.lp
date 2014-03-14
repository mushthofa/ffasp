arc(0, 2) :- #1/1.
arc(0, 4) :- #39/40.
arc(0, 6) :- #119/120.
arc(1, 3) :- #109/120.
arc(1, 5) :- #97/120.
arc(1, 6) :- #101/120.
arc(2, 0) :- #39/40.
arc(2, 3) :- #53/60.
arc(2, 4) :- #4/5.
arc(2, 5) :- #17/20.
arc(2, 6) :- #49/60.
arc(3, 1) :- #119/120.
arc(3, 2) :- #9/10.
arc(3, 5) :- #53/60.
arc(3, 6) :- #5/6.
arc(4, 0) :- #7/8.
arc(4, 2) :- #33/40.
arc(4, 5) :- #101/120.
arc(5, 1) :- #5/6.
arc(5, 2) :- #5/6.
arc(5, 3) :- #17/20.
arc(5, 4) :- #33/40.
arc(6, 0) :- #97/120.
arc(6, 1) :- #109/120.
arc(6, 2) :- #39/40.
arc(6, 3) :- #53/60.
vertex(0) :- #1/2.
vertex(1) :- #2/3.
vertex(2) :- #2/3.
vertex(3) :- #31/60.
vertex(4) :- #8/15.
vertex(5) :- #11/20.
vertex(6) :- #27/40.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

