%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                 Problem Set 3                                          %
%            Joshua Fung 1000590443                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Question 1, 


% Matrix Inversion
x_mi = A\B;
disp(x_mi);

% Gauss Elimination
M = [A,B]; [numRows,numColumns] = size(A);
for j=1:numRows-1
    if A(j,j) == 0      %Begin pivoting
        for k = j+1:numRows       %if pivoting is required, search in the rows
            if A(k,j) ~= 0  %below for a row with nonzero pivot element
                A1=A(j,:);
                A(j,:)=A(k,:); 
                A(k,:)=A1;
                break
            end
        end
    end    % End pivoting
    for i = j+1:numRows
        A(i,j:numColumns)=A(i,j:numColumns)-A(i,j)/A(j,j)*A(j,j:numColumns);
    end
end
x = zeros(numRows,1);
x(numRows)= A(numRows,numColumns)/A(numRows,numRows);
for i = numRows-1:-1:1
    x(i)=(A(i,numColumns)-A(i,i+1:numRows)*x(i+1:numRows))/A(i,i);
end
