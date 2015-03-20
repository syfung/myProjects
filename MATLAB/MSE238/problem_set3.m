%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                 Problem Set 3                                          %
%            Joshua Fung 1000590443                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Question 1, 
clc;
clear all;
close all;
format compact;

OA = [80,-50,-30,0;
      -50,100,-10,-25;
      -30,-10,65,-20;
      0,-25,-20,100];
  
OB = [-120,0,0,0]';

A = OA;
B = OB;

[n,m] = size(A);
if m ~= n
    error('Worng Size');
end

%% Matrix Inversion
fprintf('Slove by MATLAB\n');
x_mi = A\B;
disp(x_mi');

%% Gauss Elimination
fprintf('Slove by gauss elimination\n');
upper = zeros(size(A));
upper_B = zeros (size(B));

for columns = 1:m
    ind = find(A(:,columns));  
    for rows = 2:length (ind)
        lambda = A(ind(1),columns) / A(ind(rows),columns);
        A(ind(rows),:) = A(ind(1),:) - (lambda .* A(ind(rows),:));
        B(ind(rows)) = B(ind(1)) - (lambda .* B(ind(rows)));
    end
    upper(columns,:) = A (ind(1),:);
    upper_B(columns) = B (ind(1));
    A(ind(1),:) = zeros(1,m);
    B(ind(1)) = zeros(1);
end

% Back subsitution
x_ge = zeros(size(upper_B));

for k = n:-1:1
    x_ge(k) = (upper_B(k) - upper(k,k+1:n) * x_ge(k+1:n)) / upper(k,k);
end
disp(x_ge')

%% Gauss-Siedel
fprintf('Slove by gauss siedel\n');
x_gs = zeros (1,n);
diff_B_Ax = zeros(size(OB));

for k = 1 : 30
    for i = 1 : n
        diff_B_Ax (i) = OB (i);
        for j = 1 : n
            if j ~= i
                diff_B_Ax (i) = diff_B_Ax (i) - OA (i,j) * x_gs (j);
            end
        end
        x_gs (i) = diff_B_Ax (i) / OA (i,i);
    end
end

disp(x_gs);

%% MATLAB Eigenvalues Eigenvectors
[eigenVec, eigenVal] = eig(OA);

fprintf('MATLAB Eigenvalues\n');
disp(eigenVal);
fprintf('MATLAB Eigenvectors\n');
disp(eigenVec);

%% QR Factorization
A_qr = OA;
for i = 1:50
    [q,R] = qr(A_qr);
    A_qr = R * q;
end
fprintf('QR factorization\n')
disp(A_qr)

%% Question 2, Newtoon-Raphson method

gamma = 5/3;
eta = @(t2_t1) ((log(t2_t1) - (1-((t2_t1)^-1)))/(log(t2_t1)+(1-((t2_t1)^-1))/(gamma-1)));

etaAt30 = @(t2_t1) eta(t2_t1) - 0.3;

% % The equation of the dirivitive of eta is found with MATLAB sysmbolic tool
% % box
% syms x
% diffeq = char(diff(etaAt30(x)));

diffEtaAt30 = @(t2_t1) (1/t2_t1 - 1/t2_t1^2)/(log(t2_t1) - 3/(2*t2_t1) + 3/2)...
   - ((1/t2_t1 + 3/(2*t2_t1^2))*(log(t2_t1) + 1/t2_t1 - 1))/(log(t2_t1) - 3/(2*t2_t1) + 3/2)^2;

t2_t1_ans = 4;

for i = 1:20
    t2_t1_ans = t2_t1_ans - ((etaAt30(t2_t1_ans)) / diffEtaAt30(t2_t1_ans));
end

fprintf('T2/T1 where eta = 0.3:');
disp(t2_t1_ans);

