setrd, 2008
===========

Simplest top-down parser.
Reads the giving text definition of sets and produce a structural (C abstract
data types) representation of the input, checking for correct syntax in the process.

``` c
O = {}  
A = { 1, 2, 3 }  
B = { a, O, b, A }
C = {<a,1>, <b, 2>, <c,3>}
T = { {}, {t1, t2}, t3 }
```
powered by tools = {unix, c, gcc, glibc, gdb, emacs}
