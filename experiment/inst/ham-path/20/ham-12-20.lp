arc(0, 1) :- #19/20.
arc(0, 2) :- #17/20.
arc(0, 3) :- #9/10.
arc(0, 5) :- #9/10.
arc(1, 0) :- #1/1.
arc(1, 2) :- #1/1.
arc(1, 4) :- #1/1.
arc(2, 0) :- #9/10.
arc(2, 1) :- #17/20.
arc(2, 4) :- #17/20.
arc(2, 5) :- #19/20.
arc(2, 6) :- #1/1.
arc(3, 0) :- #19/20.
arc(3, 5) :- #17/20.
arc(4, 1) :- #17/20.
arc(4, 2) :- #9/10.
arc(4, 6) :- #19/20.
arc(5, 0) :- #9/10.
arc(5, 2) :- #19/20.
arc(5, 3) :- #19/20.
arc(5, 6) :- #19/20.
arc(6, 2) :- #19/20.
arc(6, 4) :- #4/5.
arc(6, 5) :- #17/20.
vertex(0) :- #13/20.
vertex(1) :- #3/5.
vertex(2) :- #13/20.
vertex(3) :- #1/2.
vertex(4) :- #7/10.
vertex(5) :- #11/20.
vertex(6) :- #3/5.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

