a(0) :- not a(n*10).
a(X+1) :- a(X), X < n*10.
