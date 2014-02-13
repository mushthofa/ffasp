a1 :- not c3.
a2 :- not c2.
a3 :- not c1.
b1 :- not c3.
b2 :- not c2.
b3 :- not c1.

c1 :- a1.
c1 :- b1.
c2 :- a2.
c2 :- a1, b1.
c2 :- b2.
c3 :- a3.
c3 :- a2, b1.
c3 :- a1, b2.
c3 :- b3.

a1 :- a2.
a2 :- a3.

b1 :- b2.
b2 :- b3.

c1 :- c2.
c2 :- c3.