arc(0, 2) :- #19/20.
arc(0, 3) :- #17/20.
arc(0, 4) :- #7/8.
arc(0, 5) :- #17/20.
arc(1, 2) :- #4/5.
arc(1, 4) :- #33/40.
arc(1, 5) :- #9/10.
arc(1, 6) :- #37/40.
arc(2, 0) :- #19/20.
arc(2, 1) :- #39/40.
arc(2, 4) :- #9/10.
arc(2, 5) :- #17/20.
arc(2, 6) :- #33/40.
arc(3, 0) :- #9/10.
arc(3, 4) :- #33/40.
arc(4, 0) :- #4/5.
arc(4, 1) :- #7/8.
arc(4, 2) :- #17/20.
arc(4, 3) :- #7/8.
arc(5, 0) :- #37/40.
arc(5, 1) :- #17/20.
arc(5, 2) :- #33/40.
arc(5, 6) :- #7/8.
arc(6, 1) :- #1/1.
arc(6, 2) :- #17/20.
arc(6, 5) :- #37/40.
vertex(0) :- #21/40.
vertex(1) :- #13/20.
vertex(2) :- #3/5.
vertex(3) :- #5/8.
vertex(4) :- #13/20.
vertex(5) :- #3/5.
vertex(6) :- #13/20.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

