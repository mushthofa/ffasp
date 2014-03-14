arc(0, 1) :- #17/20.
arc(0, 2) :- #9/10.
arc(0, 3) :- #37/40.
arc(0, 5) :- #37/40.
arc(1, 0) :- #33/40.
arc(1, 2) :- #17/20.
arc(1, 4) :- #9/10.
arc(2, 0) :- #4/5.
arc(2, 1) :- #19/20.
arc(2, 4) :- #19/20.
arc(2, 5) :- #39/40.
arc(2, 7) :- #33/40.
arc(3, 0) :- #7/8.
arc(3, 5) :- #39/40.
arc(4, 1) :- #17/20.
arc(4, 2) :- #9/10.
arc(4, 6) :- #37/40.
arc(4, 7) :- #9/10.
arc(5, 0) :- #9/10.
arc(5, 2) :- #9/10.
arc(5, 3) :- #39/40.
arc(5, 7) :- #7/8.
arc(6, 4) :- #33/40.
arc(6, 7) :- #39/40.
arc(7, 2) :- #7/8.
arc(7, 4) :- #9/10.
arc(7, 5) :- #19/20.
arc(7, 6) :- #39/40.
vertex(0) :- #7/10.
vertex(1) :- #11/20.
vertex(2) :- #5/8.
vertex(3) :- #1/2.
vertex(4) :- #7/10.
vertex(5) :- #23/40.
vertex(6) :- #23/40.
vertex(7) :- #27/40.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

