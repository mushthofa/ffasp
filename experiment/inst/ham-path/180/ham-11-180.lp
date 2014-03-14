arc(0, 2) :- #17/18.
arc(0, 3) :- #151/180.
arc(0, 4) :- #31/36.
arc(0, 5) :- #151/180.
arc(1, 2) :- #29/36.
arc(1, 4) :- #37/45.
arc(1, 5) :- #8/9.
arc(1, 6) :- #11/12.
arc(2, 0) :- #17/18.
arc(2, 1) :- #173/180.
arc(2, 4) :- #9/10.
arc(2, 5) :- #38/45.
arc(2, 6) :- #149/180.
arc(3, 0) :- #163/180.
arc(3, 4) :- #149/180.
arc(4, 0) :- #29/36.
arc(4, 1) :- #79/90.
arc(4, 2) :- #151/180.
arc(4, 3) :- #157/180.
arc(5, 0) :- #83/90.
arc(5, 1) :- #17/20.
arc(5, 2) :- #37/45.
arc(5, 6) :- #79/90.
arc(6, 1) :- #1/1.
arc(6, 2) :- #31/36.
arc(6, 5) :- #11/12.
vertex(0) :- #19/36.
vertex(1) :- #13/20.
vertex(2) :- #109/180.
vertex(3) :- #19/30.
vertex(4) :- #59/90.
vertex(5) :- #3/5.
vertex(6) :- #119/180.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

