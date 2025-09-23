syms x;
format long;

y = int(exp(x - 1), x, 0, 1);
y_ = 1 - exp(-1);
disp([0, double(y), double(y_)]);

for n = 1:20
    y = int(x^n * exp(x - 1), x, 0, 1);
    y_ = 1 - n * y_;
    disp([n, double(y), double(y_), abs(double(y) - double(y_))]);
end