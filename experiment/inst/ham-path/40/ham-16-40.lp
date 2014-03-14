arc(0, 2) :- #19/20.
arc(0, 3) :- #39/40.
arc(0, 4) :- #17/20.
arc(0, 5) :- #17/20.
arc(1, 2) :- #17/20.
arc(1, 4) :- #1/1.
arc(1, 5) :- #17/20.
arc(1, 6) :- #33/40.
arc(1, 7) :- #17/20.
arc(2, 0) :- #1/1.
arc(2, 1) :- #7/8.
arc(2, 4) :- #9/10.
arc(2, 5) :- #9/10.
arc(2, 6) :- #37/40.
arc(3, 0) :- #4/5.
arc(3, 4) :- #9/10.
arc(3, 7) :- #17/20.
arc(4, 0) :- #1/1.
arc(4, 1) :- #37/40.
arc(4, 2) :- #4/5.
arc(4, 3) :- #39/40.
arc(4, 7) :- #37/40.
arc(5, 0) :- #19/20.
arc(5, 1) :- #9/10.
arc(5, 2) :- #17/20.
arc(5, 6) :- #9/10.
arc(5, 7) :- #7/8.
arc(6, 1) :- #19/20.
arc(6, 2) :- #7/8.
arc(6, 5) :- #19/20.
arc(7, 1) :- #39/40.
arc(7, 3) :- #39/40.
arc(7, 4) :- #7/8.
arc(7, 5) :- #9/10.
vertex(0) :- #11/20.
vertex(1) :- #21/40.
vertex(2) :- #3/5.
vertex(3) :- #3/5.
vertex(4) :- #23/40.
vertex(5) :- #27/40.
vertex(6) :- #7/10.
vertex(7) :- #5/8.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

