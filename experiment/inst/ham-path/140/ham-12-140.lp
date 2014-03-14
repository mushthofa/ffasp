arc(0, 1) :- #19/20.
arc(0, 2) :- #6/7.
arc(0, 3) :- #129/140.
arc(0, 5) :- #25/28.
arc(1, 0) :- #137/140.
arc(1, 2) :- #139/140.
arc(1, 4) :- #137/140.
arc(2, 0) :- #32/35.
arc(2, 1) :- #29/35.
arc(2, 4) :- #29/35.
arc(2, 5) :- #34/35.
arc(2, 6) :- #69/70.
arc(3, 0) :- #19/20.
arc(3, 5) :- #6/7.
arc(4, 1) :- #121/140.
arc(4, 2) :- #127/140.
arc(4, 6) :- #27/28.
arc(5, 0) :- #32/35.
arc(5, 2) :- #67/70.
arc(5, 3) :- #131/140.
arc(5, 6) :- #131/140.
arc(6, 2) :- #27/28.
arc(6, 4) :- #4/5.
arc(6, 5) :- #117/140.
vertex(0) :- #47/70.
vertex(1) :- #43/70.
vertex(2) :- #22/35.
vertex(3) :- #73/140.
vertex(4) :- #7/10.
vertex(5) :- #19/35.
vertex(6) :- #41/70.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

