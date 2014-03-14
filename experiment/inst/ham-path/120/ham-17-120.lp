arc(0, 1) :- #101/120.
arc(0, 2) :- #9/10.
arc(0, 3) :- #37/40.
arc(0, 5) :- #37/40.
arc(1, 0) :- #33/40.
arc(1, 2) :- #17/20.
arc(1, 4) :- #107/120.
arc(2, 0) :- #97/120.
arc(2, 1) :- #19/20.
arc(2, 4) :- #19/20.
arc(2, 5) :- #29/30.
arc(2, 7) :- #5/6.
arc(3, 0) :- #53/60.
arc(3, 5) :- #39/40.
arc(4, 1) :- #101/120.
arc(4, 2) :- #107/120.
arc(4, 6) :- #11/12.
arc(4, 7) :- #107/120.
arc(5, 0) :- #9/10.
arc(5, 2) :- #107/120.
arc(5, 3) :- #39/40.
arc(5, 7) :- #7/8.
arc(6, 4) :- #49/60.
arc(6, 7) :- #29/30.
arc(7, 2) :- #13/15.
arc(7, 4) :- #109/120.
arc(7, 5) :- #23/24.
arc(7, 6) :- #39/40.
vertex(0) :- #83/120.
vertex(1) :- #67/120.
vertex(2) :- #37/60.
vertex(3) :- #61/120.
vertex(4) :- #83/120.
vertex(5) :- #7/12.
vertex(6) :- #17/30.
vertex(7) :- #41/60.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

