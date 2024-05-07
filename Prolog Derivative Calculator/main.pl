/*
module load swi-prolog
swipl -s main.pl
*/

%eval(E - Arithmetic Expression, V - Result)
eval(X, X) :- number(X).
eval(X^Y, R) :- eval(X, X1), eval(Y, Y1), R is X1^Y1.
eval(X*Y, R) :- eval(X, X1), eval(Y, Y1), R is X1*Y1.
eval(X/Y, R) :- eval(X, X1), eval(Y, Y1), R is X1/Y1.
eval(X+Y, R) :- eval(X, X1), eval(Y, Y1), R is X1+Y1.
eval(X-Y, R) :- eval(X, X1), eval(Y, Y1), R is X1-Y1.


%simplify(E - Arithmetic Expression, S - Simplified Expression)
simplify(C, C) :- atomic(C) ; number(C).
simplify(X^Y, C) :- number(X), number(Y), eval(X^Y, C).
simplify(X*Y, C) :- number(X), number(Y), eval(X*Y, C).
simplify(X/Y, C) :- number(X), number(Y), eval(X/Y, C).
simplify(X+Y, C) :- number(X), number(Y), eval(X+Y, C).
simplify(X-Y, C) :- number(X), number(Y), eval(X-Y, C).
simplify(X^Y, R) :- simplify(X, X1), simplify(Y, Y1), simplify2(X1^Y1, R).
simplify(X*Y, R) :- simplify(X, X1), simplify(Y, Y1), simplify2(X1*Y1, R).
simplify(X/Y, R) :- simplify(X, X1), simplify(Y, Y1), simplify2(X1/Y1, R).
simplify(X+Y, R) :- simplify(X, X1), simplify(Y, Y1), simplify2(X1+Y1, R).
simplify(X-Y, R) :- simplify(X, X1), simplify(Y, Y1), simplify2(X1-Y1, R).

simplify2(C, C) :- atomic(C) ; number(C).
simplify2(X*Y^Z/A, R) :- number(Z), NEXP is Z-1, NEXP =:= 1, number(X), atom(Y), Y == A, R = X*Y.
simplify2(X*Y^Z/A, R) :- number(Z), NEXP is Z-1, number(X), atom(Y), Y == A, R = X*Y^NEXP.

simplify2(X^Y, C) :- number(X), number(Y), eval(X^Y, C).
simplify2(X*Y, C) :- number(X), number(Y), eval(X*Y, C).
simplify2(X/Y, C) :- number(X), number(Y), eval(X/Y, C).
simplify2(X+Y, C) :- number(X), number(Y), eval(X+Y, C).
simplify2(X-Y, C) :- number(X), number(Y), eval(X-Y, C).

simplify2(X^Y, R) :- simplify2(X, X1), simplify2(Y, Y1), R = X1^Y1.
simplify2(X^Y+0, R) :-number(Y), atom(X), R = X^Y.

simplify2(X*Y*Z, R) :-number(Y), atom(X),atom(Z), R = Y*X^2.
simplify2(X*X, R) :- atom(X), R = 2*X.

simplify2(X*Y, R) :- atom(X), Y =:= 1, R = X.
simplify2(X*Y, R) :- atom(Y), X =:= 1, R = Y.
simplify2(X*Y, R) :- simplify2(X, X1), simplify2(Y, Y1), R = X1*Y1.


simplify2(X/Y, R) :- simplify2(X, X1), simplify2(Y, Y1), R = X1/Y1.

simplify2(X+Y, R) :- number(Y), Y =:= 0, R = X.
simplify2(X+Y, R) :- number(X), X =:= 0, R = Y.

simplify2(X+Y, R) :- simplify2(X, X1), simplify2(Y, Y1), R = X1+Y1.

simplify2(X-Y, R) :- number(Y), Y =:= 0, R = X.
simplify2(X-Y, R) :- number(X), X =:= 0, R = Y.
simplify2(X-Y, R) :- simplify2(X, X1), simplify2(Y, Y1), R = X1-Y1.

%deriv(E - Arithmetic Expression, D - Derivative of Expression)
deriv(X, R) :- simplify(X, Y), deriv2(Y, R).

deriv2(A, B) :- number(A), B is 0.
deriv2(A, B) :- atomic(A), B is 1.

deriv2(X^Y, R) :- number(Y), Y \= 2, atomic(X), NEXP is Y-1, R = Y*X^NEXP.
deriv2(X^Y, R) :- number(Y), atomic(Y), Y =:= 2, R = Y*X.

deriv2(X*Y, R) :- number(X), atomic(Y), R is X.
deriv2(X*Y, R) :- number(Y), atomic(X), R is Y.

deriv2(X*Y^2, R) :- number(X), atom(Y), NX is X*2, R = NX*Y.
deriv2(X*Y^Z, R) :- number(Z), number(X), atom(Y), NX is X*Z, NZ is Z-1, R = NX*Y^NZ.

deriv2(A+X/Y, R) :-  atom(Y), deriv(A, DA), R = DA-1/Y^2.
deriv2(A+X/Y^Z, R) :- number(Z), NZ is Z + 1, NX is Z*X, deriv(A, DA), R = DA-NX/Y^NZ.

deriv2(A-X/Y, R) :-  atom(Y), deriv(A, DA), R = DA+1/Y^2.
deriv2(A-X/Y^Z, R) :- number(Z), NZ is Z + 1, NX is Z*X, deriv(A, DA), R = DA+NX/Y^NZ.

deriv2(X/Y, R) :- simplify(X, X2), simplify(Y, Y2), deriv2(X2, DX), deriv2(Y2, DY), TR = DX/DY, simplify(TR, R).
deriv2(X+Y, R) :- simplify(X, X2), simplify(Y, Y2), deriv2(X2, DX), deriv2(Y2, DY), TR = DX+DY, simplify(TR, R).
deriv2(X-Y, R) :- simplify(X, X2), simplify(Y, Y2), deriv2(X2, DX), deriv2(Y2, DY), TR = DX-DY, simplify(TR, R).


%party_seating(L - List of Facts)
party_seating(L) :- L = [gabi,benjamin,ghita,brandon,georgia,bobby,grace,bruce,gigi,bill].

deriv(4*x^5+1/6x^2, R).
