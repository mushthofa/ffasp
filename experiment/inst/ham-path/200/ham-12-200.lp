arc(0, 1) :- #189/200.
arc(0, 2) :- #171/200.
arc(0, 3) :- #37/40.
arc(0, 5) :- #179/200.
arc(1, 0) :- #39/40.
arc(1, 2) :- #99/100.
arc(1, 4) :- #49/50.
arc(2, 0) :- #91/100.
arc(2, 1) :- #83/100.
arc(2, 4) :- #83/100.
arc(2, 5) :- #97/100.
arc(2, 6) :- #197/200.
arc(3, 0) :- #19/20.
arc(3, 5) :- #171/200.
arc(4, 1) :- #173/200.
arc(4, 2) :- #181/200.
arc(4, 6) :- #193/200.
arc(5, 0) :- #183/200.
arc(5, 2) :- #191/200.
arc(5, 3) :- #47/50.
arc(5, 6) :- #187/200.
arc(6, 2) :- #193/200.
arc(6, 4) :- #4/5.
arc(6, 5) :- #167/200.
vertex(0) :- #67/100.
vertex(1) :- #123/200.
vertex(2) :- #5/8.
vertex(3) :- #13/25.
vertex(4) :- #7/10.
vertex(5) :- #27/50.
vertex(6) :- #59/100.

arc(Y,X) :- arc(X,Y).

in(X,Y) :- arc(X,Y), not out(X,Y).
out(X,Y) :- arc(X,Y), not in(X,Y).

:- in(X,Y), in(X,Z), Y != Z.
:- in(X,Y), in(Z,Y), X != Z.

start(0).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).

:- vertex(X), not reached(X).

