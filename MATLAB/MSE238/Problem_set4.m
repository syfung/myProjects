%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                 Problem Set 4                                          %
%            Joshua Fung 1000590443                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clc; clear all; close all; format compact;
%% Question 1
R = 1; h = 0.001; 
the = 0:h:2*pi;
f_the = @(the) R * (cos(the) + sqrt((2.5 ^ 2) - (sin(the) .^ 2)));

% Velocity Two point central & MATLAB diff
dx_dthe_2pc = @(the) ((f_the(the+h)) - (f_the(the-h))) ./ (2 * h);
% MATLAB diff()
dx_dthe = diff(f_the(the)) ./ h;

figure
hold on
plot(the,dx_dthe_2pc(the), 'r');
plot(the(1:end-1),dx_dthe, 'k--');
legend('Two Point Central','MATLAB diff()');
title('Q1 Velocity wrt theta');
xlabel('theta');
ylabel('dx/dtheta');

% Accelration Four Point Forward & MATLAB diff
dx2_d2the_4pf = @(the) (f_the(the) - (2 * f_the(the + h)) + f_the(the + (2 * h))) ./ (h^2);
% MATLAB diff()
dx2_d2the = diff(dx_dthe) ./ h;

figure
hold on 
plot(the, dx2_d2the_4pf(the), 'r');
plot(the(1:end-2), dx2_d2the, 'k--');
legend('Four Point Forawrd','MATLAB diff()');
title('Q1 Accelration wrt theta');
xlabel('theta');
ylabel('dx2/d2theta');

%% Question 2
a = 1;
h = pi / 180;
lower = 0;
upper = pi / 2;
x = lower:h:upper;

val = @(r,v) ((cos(v).^2) ./ sqrt((r/a).^2 - sin(v).^2));
v = val(1,x);
w0_tra = h * (v(1) + v(end-1)) / 2 + h * sum(v(2:end-2));
w0_sim = h * (v(1) + 4 * sum(v(2:2:end-2)) + 2 * sum(v(3:2:end-2)) + v(end-1)) / 3;
w0_gauss = quad(@(v)((cos(v).^2) ./ sqrt((1).^2 - sin(v).^2)),lower,upper-h);
i = 1;
for r = (1 * a):(0.1 * a):(10 * a);
    v = val(r,x);
    inte_tra(i) = w0_tra * (h * (v(1) + v(end-1)) / 2 + h * sum(v(2:end-2)));
    inte_sim(i) = w0_sim * h * (v(1) + 4 * sum(v(2:2:end-2)) + 2 * sum(v(3:2:end-2)) + v(end-1)) / 3;
    
    quad_val = @(v) ((cos(v).^2) ./ sqrt((r/a).^2 - sin(v).^2));
    inte_gauss(i) = w0_gauss * quad(quad_val,lower,upper-h);
    i = i + 1;
end

figure
plot(x,val(1,x))

figure 
hold on
plot((1 * a):(0.1 * a):(10 * a),inte_tra);
plot((1 * a):(0.1 * a):(10 * a),inte_sim);
plot((1 * a):(0.1 * a):(10 * a),inte_gauss);
title 'Displacement with radius r'
legend('Trapezoidal','Simpsons rule','gauss')

% Part b
f_m = @(x,f) x .* exp(-(x .* (f + 1) ./ 2).^2) ./ 2;
erf = @(x) (2/sqrt(pi)) .* (0.3478548 .* f_m(x,-0.86113631) + 0.6521452 * f_m(x,-0.33998104) + 0.6521452...
    .* f_m(x, 0.33998104) + 0.3478548 .* f_m(x, 0.86113631));

fprintf('Gauss erf -1: %6.6d, 2: %6.6d\n',erf(-1),erf(2));

erf_m = @(x) (2/sqrt(pi))*quad(@(t)(exp(-t.^2)), 0, x);
disp(['MATLAB erf -1: ', num2str(erf_m(-1)),', 2: ' num2str(erf_m(2))]);

% Part c
dblquad(@(x,y)sin(pi .* x), 0,1,0,1)

