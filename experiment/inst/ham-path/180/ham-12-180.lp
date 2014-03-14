arc(0, 1) :- #17/18.
arc(0, 2) :- #77/90.
arc(0, 3) :- #83/90.
arc(0, 5) :- #161/180.
arc(1, 0) :- #44/45.
arc(1, 2) :- #89/90.
arc(1, 4) :- #59/60.
arc(2, 0) :- #41/45.
arc(2, 1) :- #149/180.
arc(2, 4) :- #149/180.
arc(2, 5) :- #35/36.
arc(2, 6) :- #59/60.
arc(3, 0) :- #19/20.
arc(3, 5) :- #77/90.
arc(4, 1) :- #13/15.
arc(4, 2) :- #163/180.
arc(4, 6) :- #29/30.
arc(5, 0) :- #11/12.
arc(5, 2) :- #43/45.
arc(5, 3) :- #169/180.
arc(5, 6) :- #14/15.
arc(6, 2) :- #29/30.
arc(6, 4) :- #4/5.
arc(6, 5) :- #5/6.
vertex(0) :- #2/3.
vertex(1) :- #37/60.
vertex(2) :- #113/180.
vertex(3) :- #47/90.
vertex(4) :- #7/10.
vertex(5) :- #49/90.
vertex(6) :- #53/90.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

