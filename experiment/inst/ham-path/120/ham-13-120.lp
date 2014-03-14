arc(0, 2) :- #29/30.
arc(0, 3) :- #23/24.
arc(0, 4) :- #33/40.
arc(1, 2) :- #5/6.
arc(1, 5) :- #109/120.
arc(1, 6) :- #5/6.
arc(2, 0) :- #7/8.
arc(2, 1) :- #49/60.
arc(2, 3) :- #5/6.
arc(2, 4) :- #5/6.
arc(2, 6) :- #33/40.
arc(3, 0) :- #29/30.
arc(3, 2) :- #103/120.
arc(3, 5) :- #59/60.
arc(3, 6) :- #23/24.
arc(4, 0) :- #17/20.
arc(4, 2) :- #7/8.
arc(5, 1) :- #17/20.
arc(5, 3) :- #17/20.
arc(5, 6) :- #103/120.
arc(6, 1) :- #107/120.
arc(6, 2) :- #9/10.
arc(6, 3) :- #7/8.
arc(6, 5) :- #13/15.
vertex(0) :- #13/20.
vertex(1) :- #79/120.
vertex(2) :- #73/120.
vertex(3) :- #27/40.
vertex(4) :- #73/120.
vertex(5) :- #31/60.
vertex(6) :- #13/24.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

