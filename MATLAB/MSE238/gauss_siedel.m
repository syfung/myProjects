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

A = OA; 
B = OB;

ans_x = OA\OB

n = length (OA(:,1));
m = length (OA(1,:));

if m ~= n
    error('Worng Size');
end

x = zeros (1,n);

for k = 1 : 20
    for i = 1 : n
        diff_B_Ax (i) = B (i);
        for j = 1 : n
            if j ~= i
                diff_B_Ax (i) = diff_B_Ax (i) - A (i,j) * x (j);
            end
        end
        x (i) = diff_B_Ax (i) / A (i,i)
    end
end

