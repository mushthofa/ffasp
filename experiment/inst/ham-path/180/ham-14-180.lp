arc(0, 1) :- #59/60.
arc(0, 3) :- #37/45.
arc(0, 4) :- #49/60.
arc(0, 5) :- #77/90.
arc(0, 6) :- #167/180.
arc(1, 0) :- #149/180.
arc(1, 2) :- #173/180.
arc(1, 6) :- #29/36.
arc(2, 1) :- #17/18.
arc(2, 3) :- #35/36.
arc(2, 4) :- #9/10.
arc(2, 5) :- #14/15.
arc(2, 6) :- #17/18.
arc(3, 0) :- #14/15.
arc(3, 2) :- #29/36.
arc(3, 5) :- #173/180.
arc(3, 6) :- #1/1.
arc(4, 0) :- #5/6.
arc(4, 2) :- #29/30.
arc(4, 5) :- #53/60.
arc(5, 0) :- #173/180.
arc(5, 2) :- #157/180.
arc(5, 3) :- #83/90.
arc(5, 4) :- #37/45.
arc(6, 0) :- #77/90.
arc(6, 1) :- #9/10.
arc(6, 2) :- #151/180.
arc(6, 3) :- #41/45.
vertex(0) :- #91/180.
vertex(1) :- #53/90.
vertex(2) :- #8/15.
vertex(3) :- #7/12.
vertex(4) :- #19/30.
vertex(5) :- #23/36.
vertex(6) :- #31/60.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

