arc(0, 1) :- #4/5.
arc(0, 3) :- #17/20.
arc(0, 5) :- #17/20.
arc(0, 6) :- #17/20.
arc(0, 7) :- #17/20.
arc(1, 0) :- #19/20.
arc(1, 2) :- #9/10.
arc(1, 6) :- #17/20.
arc(2, 1) :- #19/20.
arc(2, 3) :- #17/20.
arc(2, 4) :- #17/20.
arc(2, 5) :- #1/1.
arc(2, 6) :- #17/20.
arc(3, 0) :- #17/20.
arc(3, 2) :- #9/10.
arc(3, 5) :- #1/1.
arc(3, 6) :- #9/10.
arc(4, 2) :- #4/5.
arc(4, 5) :- #1/1.
arc(4, 7) :- #9/10.
arc(5, 0) :- #19/20.
arc(5, 2) :- #19/20.
arc(5, 3) :- #17/20.
arc(5, 4) :- #9/10.
arc(5, 7) :- #17/20.
arc(6, 0) :- #1/1.
arc(6, 1) :- #19/20.
arc(6, 2) :- #17/20.
arc(6, 3) :- #17/20.
arc(7, 0) :- #4/5.
arc(7, 4) :- #19/20.
arc(7, 5) :- #1/1.
vertex(0) :- #11/20.
vertex(1) :- #11/20.
vertex(2) :- #7/10.
vertex(3) :- #3/5.
vertex(4) :- #1/2.
vertex(5) :- #13/20.
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

