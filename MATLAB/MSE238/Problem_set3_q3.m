%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%         Joshua See Yui Fung       1000590443                           %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clc;
clear all;
close all;
%% Part A
t = [-250,-200,-200,0,200,300];
c_p = [0.0163,0.318,0.699,0.870,0.941,1.04];
inter_t = 200;
extra_t = 400;

n = 3;
[p,s] = polyfit(t,c_p,n);

ti = -250:0.1:450;
cp_curve = polyval(p,ti);
inter_c = polyval(p,inter_t);
extra_c = polyval(p,extra_t);

polydata = polyval(p,t);
sstot = sum((c_p - mean(c_p)).^2);
ssres = sum((c_p - polydata).^2);
rsquared = 1 - (ssres / sstot);

figure(1);

hold on

plot(t,c_p,'ro');
plot(t,c_p,'b');
plot(ti,cp_curve,'k:');

plot(inter_t,inter_c,'g*');
plot(extra_t,extra_c,'k*');

legend('Data','Data','Fitted',...
    ['Interpolate:', num2str(inter_t)],['Extrapolate:', num2str(extra_t)]);
text(-200,2,['R^2 = ' ,num2str(rsquared)]);
xlabel('t');
ylabel('Cp');
title('3rd order polynomial, Interpolate & Extrapolate');

hold off

%% Part B 
t_exp = 0:0.5:5.5;
gamma = [1,0.994,0.990,0.985,0.979,0.977,0.972,0.969,0.967,0.960,0.956,0.952];
gamma_log = log(gamma);

t = 0:0.1:5.5;
n = 1;
p = polyfit(t_exp,gamma_log,n);

gamma_cal = p(1) * exp(p(2) * t);

figure(2);
hold on
plot(t,gamma_cal);
plot(t_exp,gamma,'o');
