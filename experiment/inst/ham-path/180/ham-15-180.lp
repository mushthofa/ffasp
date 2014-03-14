arc(0, 2) :- #179/180.
arc(0, 4) :- #44/45.
arc(0, 6) :- #89/90.
arc(1, 3) :- #163/180.
arc(1, 5) :- #73/90.
arc(1, 6) :- #151/180.
arc(2, 0) :- #44/45.
arc(2, 3) :- #53/60.
arc(2, 4) :- #29/36.
arc(2, 5) :- #17/20.
arc(2, 6) :- #49/60.
arc(3, 1) :- #89/90.
arc(3, 2) :- #9/10.
arc(3, 5) :- #79/90.
arc(3, 6) :- #5/6.
arc(4, 0) :- #79/90.
arc(4, 2) :- #37/45.
arc(4, 5) :- #151/180.
arc(5, 1) :- #5/6.
arc(5, 2) :- #5/6.
arc(5, 3) :- #17/20.
arc(5, 4) :- #149/180.
arc(6, 0) :- #73/90.
arc(6, 1) :- #163/180.
arc(6, 2) :- #35/36.
arc(6, 3) :- #53/60.
vertex(0) :- #91/180.
vertex(1) :- #2/3.
vertex(2) :- #2/3.
vertex(3) :- #31/60.
vertex(4) :- #8/15.
vertex(5) :- #11/20.
vertex(6) :- #121/180.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

