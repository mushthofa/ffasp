arc(0, 2) :- #9/10.
arc(0, 3) :- #1/1.
arc(0, 4) :- #4/5.
arc(1, 2) :- #39/40.
arc(1, 5) :- #17/20.
arc(1, 6) :- #17/20.
arc(1, 7) :- #39/40.
arc(2, 0) :- #33/40.
arc(2, 1) :- #37/40.
arc(2, 3) :- #7/8.
arc(2, 4) :- #4/5.
arc(2, 7) :- #9/10.
arc(3, 0) :- #4/5.
arc(3, 2) :- #19/20.
arc(3, 5) :- #39/40.
arc(3, 7) :- #4/5.
arc(4, 0) :- #9/10.
arc(4, 2) :- #1/1.
arc(5, 1) :- #7/8.
arc(5, 3) :- #39/40.
arc(5, 6) :- #19/20.
arc(5, 7) :- #19/20.
arc(6, 1) :- #33/40.
arc(6, 5) :- #39/40.
arc(6, 7) :- #9/10.
arc(7, 1) :- #19/20.
arc(7, 2) :- #17/20.
arc(7, 3) :- #1/1.
arc(7, 5) :- #9/10.
arc(7, 6) :- #7/8.
vertex(0) :- #11/20.
vertex(1) :- #27/40.
vertex(2) :- #11/20.
vertex(3) :- #5/8.
vertex(4) :- #3/5.
vertex(5) :- #3/5.
vertex(6) :- #5/8.
vertex(7) :- #11/20.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

