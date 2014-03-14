arc(0, 1) :- #38/45.
arc(0, 2) :- #9/10.
arc(0, 3) :- #167/180.
arc(0, 5) :- #167/180.
arc(1, 0) :- #149/180.
arc(1, 2) :- #17/20.
arc(1, 4) :- #161/180.
arc(2, 0) :- #73/90.
arc(2, 1) :- #17/18.
arc(2, 4) :- #17/18.
arc(2, 5) :- #29/30.
arc(2, 7) :- #5/6.
arc(3, 0) :- #53/60.
arc(3, 5) :- #35/36.
arc(4, 1) :- #151/180.
arc(4, 2) :- #161/180.
arc(4, 6) :- #11/12.
arc(4, 7) :- #161/180.
arc(5, 0) :- #9/10.
arc(5, 2) :- #8/9.
arc(5, 3) :- #44/45.
arc(5, 7) :- #157/180.
arc(6, 4) :- #49/60.
arc(6, 7) :- #29/30.
arc(7, 2) :- #13/15.
arc(7, 4) :- #163/180.
arc(7, 5) :- #43/45.
arc(7, 6) :- #44/45.
vertex(0) :- #25/36.
vertex(1) :- #101/180.
vertex(2) :- #37/60.
vertex(3) :- #91/180.
vertex(4) :- #31/45.
vertex(5) :- #26/45.
vertex(6) :- #17/30.
vertex(7) :- #41/60.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

