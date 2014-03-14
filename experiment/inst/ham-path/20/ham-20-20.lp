arc(0, 2) :- #19/20.
arc(0, 4) :- #17/20.
arc(0, 6) :- #1/1.
arc(0, 7) :- #17/20.
arc(1, 3) :- #9/10.
arc(1, 5) :- #17/20.
arc(1, 6) :- #9/10.
arc(2, 0) :- #4/5.
arc(2, 3) :- #17/20.
arc(2, 6) :- #19/20.
arc(2, 7) :- #19/20.
arc(3, 1) :- #9/10.
arc(3, 2) :- #9/10.
arc(3, 5) :- #1/1.
arc(3, 6) :- #9/10.
arc(3, 7) :- #19/20.
arc(4, 0) :- #9/10.
arc(4, 5) :- #9/10.
arc(4, 7) :- #19/20.
arc(5, 1) :- #17/20.
arc(5, 3) :- #19/20.
arc(5, 4) :- #17/20.
arc(5, 7) :- #9/10.
arc(6, 0) :- #19/20.
arc(6, 1) :- #1/1.
arc(6, 2) :- #9/10.
arc(6, 3) :- #17/20.
arc(7, 0) :- #1/1.
arc(7, 2) :- #19/20.
arc(7, 3) :- #17/20.
arc(7, 4) :- #17/20.
arc(7, 5) :- #19/20.
vertex(0) :- #11/20.
vertex(1) :- #1/2.
vertex(2) :- #7/10.
vertex(3) :- #3/5.
vertex(4) :- #7/10.
vertex(5) :- #3/5.
vertex(6) :- #7/10.
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

