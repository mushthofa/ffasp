arc(0, 2) :- #1/1.
arc(0, 4) :- #1/1.
arc(0, 6) :- #1/1.
arc(1, 3) :- #9/10.
arc(1, 5) :- #4/5.
arc(1, 6) :- #17/20.
arc(2, 0) :- #1/1.
arc(2, 3) :- #9/10.
arc(2, 4) :- #4/5.
arc(2, 5) :- #17/20.
arc(2, 6) :- #4/5.
arc(3, 1) :- #1/1.
arc(3, 2) :- #9/10.
arc(3, 5) :- #9/10.
arc(3, 6) :- #17/20.
arc(4, 0) :- #9/10.
arc(4, 2) :- #4/5.
arc(4, 5) :- #17/20.
arc(5, 1) :- #17/20.
arc(5, 2) :- #17/20.
arc(5, 3) :- #17/20.
arc(5, 4) :- #17/20.
arc(6, 0) :- #4/5.
arc(6, 1) :- #9/10.
arc(6, 2) :- #19/20.
arc(6, 3) :- #9/10.
vertex(0) :- #1/2.
vertex(1) :- #13/20.
vertex(2) :- #13/20.
vertex(3) :- #1/2.
vertex(4) :- #11/20.
vertex(5) :- #11/20.
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

