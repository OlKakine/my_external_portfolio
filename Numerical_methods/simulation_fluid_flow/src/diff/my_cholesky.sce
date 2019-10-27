
function [A]=cholesky_fact(A)
n=size(A)(1)
//on copie A et modifie A "en place"
T=A
for i = 1:n
    A(1:i-1,i)=zeros(i-1,1)
        
    A(i,i)=sqrt(T(i,i)-sum(A(i,1:i-1)^2))

    for j = (i+1):n
        A(j,i)=(T(j,i)-sum(A(j,1:i-1).*A(i,1:i-1)))/A(i,i)
    end
end
endfunction

function [x]=up_sweep_cholesky(U,y)
    //U is a up triangle matrix
  [m,n]=size(U);
  if (m~=n) then
    print(%io(2), "error, not a square matrix");
  else
    x=zeros(1,n)
    for i = n:-1:1
        x(i)=(y(i)-sum(x(i+1:n).*U(i,i+1:n)))/U(i,i)
    end
  end
endfunction

function [y]=down_sweep_cholesky(L,b)
    //L is a low triangle matrix
  [m,n]=size(L);
  if (m~=n) then
    print(%io(2), "error, not a square matrix");
  else
    y=zeros(1,n)
    for i = 1:n
        y(i)=(b(i)-sum(y(1:i-1).*L(i,1:i-1)))/L(i,i)
    end
 end
endfunction

function [U]=my_cholesky(N,S)
T=cholesky_fact(N)
U=(up_sweep_cholesky(T',down_sweep_cholesky(T,S)))'
endfunction
