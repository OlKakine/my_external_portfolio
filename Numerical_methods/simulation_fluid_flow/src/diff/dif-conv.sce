Nx=200;
Nt=200;
kappa=0.01;
exec("my_cholesky.sce")
mode(-1)

function y=phi_0(Nx)
    y=zeros(Nx,1)
    i=1
    xi=0
    
    while xi<0.25
        xi=xi+dx
        i=i+1
    end
    
    while xi<0.375
        y(i)=2*(xi-0.25)
        xi=xi+dx
        i=i+1
    end
    
    while xi<0.5
        y(i)=2*(0.5-xi)
        xi=xi+dx
        i=i+1
    end
endfunction

function y=conv(x)
y=0.4*(x-0.25)
endfunction

function N=init_N()
    N=zeros(Nx,Nx)
    Ncoeffs=[-kappa*Nx2dNt,1+2*kappa*Nx2dNt,-kappa*Nx2dNt]
for i = 2:Nx-1
    N(i,i-1:i+1)=Ncoeffs
end
N(Nx,Nx-1:Nx)=Ncoeffs(1:2)
N(Nx,1)=Ncoeffs(3)
N(1,1:2)=Ncoeffs(2:3)
N(1,Nx)=Ncoeffs(1)
endfunction

function M=init_M()
    M=zeros(Nx,Nx)
for i = 2:Nx-1
    c=conv((i-1)*dx)
    M(i,i-1:i+1)=[c*Nxd2Nt+c^2*Nx2d2Nt2, 1-c^2*Nx2dNt2, -c*Nxd2Nt+c^2*Nx2d2Nt2]
end
c=conv((Nx-1)*dx)
M(Nx,Nx-1:Nx)=[c*Nxd2Nt+c^2*Nx2d2Nt2, 1-c^2*Nx2dNt2]
M(Nx,1)=-c*Nxd2Nt+c^2*Nx2d2Nt2
c=conv(0)
M(1,1:2)=[1-c^2*Nx2dNt2, -c*Nxd2Nt+c^2*Nx2d2Nt2]
M(1,Nx)=c*Nxd2Nt+c^2*Nx2d2Nt2
endfunction

N=zeros(Nx,Nx)
M=zeros(Nx,Nx)

//constantes permettant d'accélérer les itérations
Nt2=Nt^2;
Nx2=Nx^2;
Nxd2Nt=Nx/(2*Nt)
Nx2dNt=Nx2/Nt
Nx2dNt2=Nx2/Nt2
Nx2d2Nt2=Nx2dNt2/2
dx=1/Nx

N=init_N()
M=init_M()
phi_i=phi_0(Nx)
phi=phi_i
maillage=dx*(0:Nx-1)

//on fait les Nt itérations pour calculer l'évolution de phi
fin=Nt;
for i=1:fin
    phi=my_cholesky(N,M*phi);
end
scf;
plot(maillage,[phi_i phi]);
