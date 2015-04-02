## Introduction ##
Fuzzy Answer Set Programming (FASP) is an extension of Answer Set Programming ([ASP](http://en.wikipedia.org/wiki/Answer_set_programming)), one of the popular programming paradigms used in Artificial Intelligence ([AI](http://en.wikipedia.org/wiki/Artificial_intelligence)) and Knowledge Representation and Reasoning ([KR](http://en.wikipedia.org/wiki/Knowledge_representation_and_reasoning)) for declarative problem-solving.

FASP extends classical ASP by allowing propositions to have a _fuzzy_ truth value. This
[paper](http://www.cwi.ugent.be/martine/papers/volledig/mblondeel2012a.pdf) provides an introduction to FASP.

`ffasp` is an implementation of a FASP solver which finds finite-valued answer-sets of fuzzy answer set programs using transformation to classical ASP, and calls an external ASP solver (e.g., [clingo](http://potassco.sourceforge.net/)) to compute the answer sets.
Currently, only fuzzy answer set programs under \Lukasiewicz semantics are supported (see, e.g., this [paper](http://tinf2.vub.ac.be/~marjon/Onderzoek/Papers/Complexity_FASP.pdf) for a discussion on this semantics).

This project implements the FASP solver as described in this paper:

Mushthofa, Mushthofa, Steven Schockaert, and Martine De Cock. "A finite-valued solver for disjunctive fuzzy answer set programs." Proceedings of the 21st European Conference on Artificial Intelligence, to appear. 2014.
([PDF](http://cwds.uw.edu/sites/default/files/publications/mushthofa2014a.pdf))
## How to Get it ##

To get the source, use SVN as follows:

```
$ svn checkout http://ffasp.googlecode.com/svn/ ffasp
```

Instructions to compile and run `ffasp` can be read in README.txt.

The source code and binaries for Mac OS X (64-bit) and Linux (32-bit)
can also be downloaded from the following link:

[Downloads](https://drive.google.com/folderview?id=0B5MJ6NQUtACDN040UmFjaHp4a2M&usp=sharing)
(**Warning**: may be outdated, use SVN to check out the **latest** version!)

The link also provides the test instances for benchmarking `ffasp`