arc(0, 2) :- #35/36.
arc(0, 3) :- #43/45.
arc(0, 4) :- #37/45.
arc(1, 2) :- #5/6.
arc(1, 5) :- #41/45.
arc(1, 6) :- #151/180.
arc(2, 0) :- #79/90.
arc(2, 1) :- #49/60.
arc(2, 3) :- #151/180.
arc(2, 4) :- #5/6.
arc(2, 6) :- #149/180.
arc(3, 0) :- #29/30.
arc(3, 2) :- #31/36.
arc(3, 5) :- #59/60.
arc(3, 6) :- #173/180.
arc(4, 0) :- #77/90.
arc(4, 2) :- #79/90.
arc(5, 1) :- #77/90.
arc(5, 3) :- #17/20.
arc(5, 6) :- #77/90.
arc(6, 1) :- #8/9.
arc(6, 2) :- #163/180.
arc(6, 3) :- #157/180.
arc(6, 5) :- #13/15.
vertex(0) :- #29/45.
vertex(1) :- #59/90.
vertex(2) :- #11/18.
vertex(3) :- #121/180.
vertex(4) :- #11/18.
vertex(5) :- #23/45.
vertex(6) :- #49/90.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

