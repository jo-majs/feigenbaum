# feigenbaum
The program approximates the Feigenbaum constant using two different functions.  
For numbers in range [0,1] let's take a function x -> f(x) where f(x)=A*x*(1-x) or f(x) = A/4*sin(pi*x). For small enough values of A, iterating this function x -> f(x) -> f(f(x)) -> f(f(f(x))) -> ... results in a series converging to a limit whose value is the solution to x = f(x).  
Fow greater values of A, the series asymptotically oscillates between two values - there's a cycle of length 2. For even greater values of A, there emerge cycles of length 4, 8, 16...   
If A(1), A(2), A(3), A(4)... (A(n) - are the values for which there is a transition from cycle of length 2^n to a cycle of length 2^(n+1), then the limit to which the ratio (A(n+2) - A(n+1))/(A(n+1) - A(n)) converges is the Feigenbaum constant, for both of the proposed functions.

More info:
https://www.youtube.com/watch?v=ovJcsL7vyrk

https://en.wikipedia.org/wiki/Feigenbaum_constants#The_first_constant
