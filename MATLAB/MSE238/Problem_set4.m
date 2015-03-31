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

Q1_v = figure;
hold on
plot(the,dx_dthe_2pc(the), 'r');
plot(the(1:end-1),dx_dthe, 'k--');

% Accelration Four Point Forward & MATLAB diff
d2x_dthe2_4pf = @(the) (f_the(the) - (2 * f_the(the + h)) + f_the(the + (2 * h))) ./ (h^2);
% MATLAB diff()
d2x_dthe2 = diff(dx_dthe) ./ h;

Q1_a = figure;
hold on 
plot(the, d2x_dthe2_4pf(the), 'r');
plot(the(1:end-2), d2x_dthe2, 'k--');

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

% Q2a = figure
% plot(x,val(1,x))

Q2a = figure;
hold on
plot((1 * a):(0.1 * a):(10 * a),inte_tra);
plot((1 * a):(0.1 * a):(10 * a),inte_sim);
plot((1 * a):(0.1 * a):(10 * a),inte_gauss);
title 'Displacement with radius r'
legend('Trapezoidal','Simpsons rule','gauss')
xlabel('r');
ylabel('Displacment')
% Part b
f_m = @(x,f) x .* exp(-(x .* (f + 1) ./ 2).^2) ./ 2;
erf = @(x) (2/sqrt(pi)) .* (0.3478548 .* f_m(x,-0.86113631) + 0.6521452 * f_m(x,-0.33998104) + 0.6521452...
    .* f_m(x, 0.33998104) + 0.3478548 .* f_m(x, 0.86113631));

Q2b = figure; 
hold on
ezplot(erf,[-2,2])

fprintf('Gauss erf -1: %6.6d, 2: %6.6d\n',erf(-1),erf(2));

erf_m = @(x) (2/sqrt(pi))*quad(@(t)(exp(-t.^2)), 0, x);
disp(['MATLAB erf -1: ', num2str(erf_m(-1)),', 2: ' num2str(erf_m(2))]);

% Part c
disp (['Part c: ', num2str(dblquad(@(x,y)sin(pi .* x), 0,1,0,1))])
disp(' ');
%% Question 3
syms x sym_r y

disp('Question 3, symbolic');

% Q1
f_q1 = R * (cos(x) + sqrt((2.5 ^ 2) - (sin(x) .^ 2)))
dfq1_dx = diff(f_q1,x)
d2fq1_dx2 = diff(dfq1_dx, x)

% figure(Q1_v)
ezplot(dfq1_dx,[0,2*pi], Q1_v)
hold on 
legend('Two Point Central','MATLAB diff()','symbolic');
title('Q1 Velocity wrt theta');
xlabel('theta');
ylabel('dx/dtheta');

% figure(Q1_a)
ezplot(d2fq1_dx2,[0,2*pi], Q1_a)
hold on
legend('Four Point Forawrd','MATLAB diff()');
title('Q1 Accelration wrt theta');
xlabel('theta');
ylabel('dx2/d2theta');

% Q2-a
w0 = int((cos(x).^2) ./ sqrt((a/a).^2 - sin(x).^2), 0, pi / 2)
int_fq2a = w0 * int((cos(x).^2) ./ sqrt((sym_r/a).^2 - sin(x).^2), x, 0, (pi / 2)-h)

% Q2-b
f_q2b = (2 / sqrt(pi)) * int(exp(-x^2),0,x)

% figure(Q2b)
ezplot(f_q2b,[-2,2], Q2b)
legend('erf Gauss','erf symbolic');
title('Erf');
xlabel('x');
ylabel('erf(x)');

% Q2-c
f_q2c = sin(pi * x);
int_fq2c = int(f_q2c, x, 0, y);
int_int_fq2c = int(int_fq2c, y, 0, 1)

print(Q1_v,'-dpng','-r150','Question1_velocity_josh.png');
print(Q1_a,'-dpng','-r150','Question1_acceleration_josh.png');
print(Q2a,'-dpng','-r150','Question2_displacement_josh.png');
print(Q2b,'-dpng','-r150','Question2_erf_josh.png');