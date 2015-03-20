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
plot(ti,cp_curve,'k--');

plot(inter_t,inter_c,'g*');
plot(extra_t,extra_c,'k^');

legend('Data','Data','Fitted',...
    ['Interpolate:', num2str(inter_t)],['Extrapolate:', num2str(extra_t)]);
text(-200,2,['R^2 = ' ,num2str(rsquared)]);
xlabel('t');
ylabel('Cp');
title('3rd order polynomial, Interpolate & Extrapolate');

hold off

%% Part B 
n = 1;
t_exp = 0:0.5:5.5;
gamma = [1,0.994,0.990,0.985,0.979,0.977,0.972,0.969,0.967,0.960,0.956,0.952];
gamma_log = log(gamma);

p = polyfit(t_exp,gamma_log,n);

% Or coding the linear least square fit
b_1 = ((n * sum(t_exp .* gamma_log)) - (sum(t_exp) * sum(gamma_log))) /...
    ((n * sum(t_exp.^2)) - sum(t_exp)^2);
b_2 = (sum(gamma_log) - (b_1 * sum(t_exp))) / n;

gamma_log_eq = @(n_b,a_log,t) n_b * t + a_log;

t = 0:0.1:5.5;
gamma_log_cal = gamma_log_eq(b_1,b_2,t);
gamma_log_cal_poly = gamma_log_eq(p(1),p(2),t);

t_half = log(2) / -p(1);

figure(2);
hold on
plot(t,exp(gamma_log_cal),'g--');
plot(t,exp(gamma_log_cal_poly),'k:');
plot(t_exp,gamma,'bo');
text(1,0.96, ['Half life:' , num2str(t_half)]);
xlabel('Time');
ylabel('Expermental value');
legend('Linear Least Square fit','Polyfit degree 1','Expermental value');
title('Radioactive Decay');

print(1,'-dpng','-r100', 'Q3_part_a_josh.png');
print(2,'-dpng','-r100', 'Q3_part_b_josh.png');
