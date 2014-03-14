chosenColour(X,white) :- node(X), not chosenColour(X,black).
chosenColour(X,black) :- node(X), not chosenColour(X,white).

:- link(X,Y),  X<Y, chosenColour(X,C), chosenColour(Y,C).

