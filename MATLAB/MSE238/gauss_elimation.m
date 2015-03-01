clc;
clear all;
close all;
format compact;

a= 1/sqrt(2);

% OA = [4,-1,1;
%       -1,2,-2;
%       1,-2,4];
%   
% OB = [12;-1;5];

OA=[0 1 0 0 0 -1 0 0 0 0 0 0 0;
    0 0 1 0 0 0 0 0 0 0 0 0 0;
    a 0 0 -1 -a 0 0 0 0 0 0 0 0;
    a 0 1 0 a 0 0 0 0 0 0 0 0;
    0 0 0 1 0 0 0 -1 0 0 0 0 0;
    0 0 0 0 0 0 1 0 0 0 0 0 0;
    0 0 0 0 a 1 0 0 -a -1 0 0 0;
    0 0 0 0 a 0 1 0 a 0 0 0 0;
    0 0 0 0 0 0 0 0 0 1 0 0 -1;
    0 0 0 0 0 0 0 0 0 0 1 0 0;
    0 0 0 0 0 0 0 1 a 0 0 -a 0;
    0 0 0 0 0 0 0 0 a 0 1 a 0;
    0 0 0 0 0 0 0 0 0 0 0 a 1];

OB=[0 10 0 0 0 0 0 15 0 20 0 0 0]';

fprintf ('By MATLAB:\n');
x_ans = OA\OB;
disp (x_ans);

A = OA; 
B = OB;

Upper = zeros(size(A));
Upper_B = zeros (size(B));

n = length(A(:,1));
m = length(A(1,:));

for columns = 1:m
    Ind = find(A(:,columns));  
    for rows = 2:length (Ind)
        lambda = A(Ind(1),columns) / A(Ind(rows),columns);
        A(Ind(rows),:) = A(Ind(1),:) - (lambda .* A(Ind(rows),:));
        B(Ind(rows)) = B(Ind(1)) - (lambda .* B(Ind(rows)));
    end
    Upper(columns,:) = A (Ind(1),:);
    Upper_B(columns) = B (Ind(1));
    A(Ind(1),:) = zeros(1,m);
    B(Ind(1)) = zeros(1);
end

% Back subsitution
x = zeros(size(Upper_B));

for k = n:-1:1
    x(k) = (Upper_B(k) - Upper(k,k+1:n) * x(k+1:n)) / Upper (k,k);
end

fprintf('x:\n');
disp (x');
