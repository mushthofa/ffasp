arc(0, 1) :- #39/40.
arc(0, 3) :- #33/40.
arc(0, 4) :- #33/40.
arc(0, 5) :- #17/20.
arc(0, 6) :- #37/40.
arc(1, 0) :- #33/40.
arc(1, 2) :- #19/20.
arc(1, 6) :- #4/5.
arc(2, 1) :- #19/20.
arc(2, 3) :- #39/40.
arc(2, 4) :- #9/10.
arc(2, 5) :- #37/40.
arc(2, 6) :- #19/20.
arc(3, 0) :- #37/40.
arc(3, 2) :- #4/5.
arc(3, 5) :- #19/20.
arc(3, 6) :- #1/1.
arc(4, 0) :- #33/40.
arc(4, 2) :- #39/40.
arc(4, 5) :- #7/8.
arc(5, 0) :- #39/40.
arc(5, 2) :- #7/8.
arc(5, 3) :- #37/40.
arc(5, 4) :- #33/40.
arc(6, 0) :- #17/20.
arc(6, 1) :- #9/10.
arc(6, 2) :- #17/20.
arc(6, 3) :- #9/10.
vertex(0) :- #1/2.
vertex(1) :- #23/40.
vertex(2) :- #21/40.
vertex(3) :- #23/40.
vertex(4) :- #5/8.
vertex(5) :- #13/20.
vertex(6) :- #21/40.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

