syms s(t) w(n) a(n) b(n) p1 p2 f(x) nmax
% s(x) - საწყისი პერიოდული ფუნქცია
% a(n), b(n) - ფურიეს მწკრივების კოეფიციენტები
% p1, p2 - პერიოდის საწყისი და საბოლოო წერტილები
% f(x) - ფუნქციის მიახლოება
% nmax - წევრების მაქსიმალური რაოდენობა

s(t) = piecewise(t < 1, 7.5, 2.5);

p1 = 0;
p2 = 2;
p = p2 - p1;
nmax = 10;
w = 2*pi*n/p;

% General formulas
a(n) = 2/p*int(s(t)*cos(w*t), t, p1, p2);
b(n) = 2/p*int(s(t)*sin(w*t), t, p1, p2);

f(t) = limit(a(n), n, 0)/2 + symsum(a(n)*cos(w*t) + b(n)*sin(w*t), n, 1, nmax);
fplot(f(t))