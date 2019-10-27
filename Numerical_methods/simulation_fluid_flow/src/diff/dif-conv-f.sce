
function dt=calcul_dt(u,dx)
  dt=dx/max(abs(u));
endfunction

function vort_s=solveur_1D(vort_p,u,N,const)
    vort_s=umfpack(N,'\',init_M(u,const)*vort_p)
endfunction

function N=init_N(kappa,Nx,Nx2dNt)
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

function M=init_M(u,const)
    [Nx,Nt,Nxd2Nt,Nx2d2Nt2,Nx2dNt2]=const([1:5])
    M=zeros(Nx,Nx)
for i = 2:Nx-1
    c=u(i)
    M(i,i-1:i+1)=[c*Nxd2Nt+c^2*Nx2d2Nt2, 1-c^2*Nx2dNt2, -c*Nxd2Nt+c^2*Nx2d2Nt2]
end
c=u(Nx)
M(Nx,Nx-1:Nx)=[c*Nxd2Nt+c^2*Nx2d2Nt2, 1-c^2*Nx2dNt2]
M(Nx,1)=-c*Nxd2Nt+c^2*Nx2d2Nt2
c=u(1)
M(1,1:2)=[1-c^2*Nx2dNt2, -c*Nxd2Nt+c^2*Nx2d2Nt2]
M(1,Nx)=c*Nxd2Nt+c^2*Nx2d2Nt2
endfunction

function phi=solveur_2D(nb_iter,Tf,dt,Nx,Ny,kappa,phi,cx,cy)
    
Nt=floor(Tf/dt);
    
    //on initialise toutes les constantes servants au calculs de N et M
Nt2=Nt^2;
Nx2=Nx^2;
Nxd2Nt=Nx/(2*Nt);
Nx2dNt=Nx2/Nt;
Nx2dNt2=Nx2/Nt2;
Nx2d2Nt2=Nx2dNt2/2;

Nt2=Nt^2;
Ny2=Ny^2;
Nyd2Nt=Ny/(2*Nt);
Ny2dNt=Ny2/Nt;
Ny2dNt2=Ny2/Nt2;
Ny2d2Nt2=Ny2dNt2/2;

constx=list(Nx,Nt,Nxd2Nt,Nx2d2Nt2,Nx2dNt2);
consty=list(Ny,Nt,Nyd2Nt,Ny2d2Nt2,Ny2dNt2);

N_x=sparse(init_N(kappa,Nx,Nx2dNt))
N_y=sparse(init_N(kappa,Ny,Ny2dNt))
    
for k=1:nb_iter
        // pour chaque colonne de phi, on applique le solveur_1D défini dans dif-conv-f.sce
    phi_p=phi
    for i=1:Nx
        vort_p=phi_p(1:Ny,i)
        u=cy(1:Ny,i)
        N=N_y
        phi(1:Ny,i)=solveur_1D(vort_p,u,N,consty)
    end
    // pour chaque ligne de phi, on applique le solveur_1D
    phi_p=phi
    for i=1:Ny
        vort_p=phi_p(i,1:Nx)'
        u=cx(i,1:Nx)
        N=N_x
        phi(i,1:Nx)=solveur_1D(vort_p,u,N,constx)'
    end
end
endfunction

