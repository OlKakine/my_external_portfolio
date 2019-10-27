Nx=100;
Ny=100;
Lx=1;
Ly=1;
Tf=0.5;
kappa=0.01;

//permet de ne pas afficher les sorties des fonctions
mode(-1)

function u=conv(y,x)
   alpha=1;
   beta=1;
   u=beta*[cos(alpha)*x-sin(alpha)*y,sin(alpha)*x+cos(alpha)*y];
endfunction

function z=phi_0(y,x)
  p_0=[0.5 0.3];
  r_0=0.2;
 if (x-p_0(1))**2+(y-p_0(2))**2>r_0**2 then
    z=0;
  else
    z=1-((x-p_0(1))**2+(y-p_0(2))**2)/r_0**2;
  end
endfunction

exec("dif-conv-2D.sce")

nb_iter=Nt
phi=solveur_2D(nb_iter,Tf,dt,Nx,Ny,kappa,phi,cx,cy)

maillage_x=linspace(0,(Nx-1)/Nx*Lx,Nx)';
maillage_y=linspace(0,(Ny-1)/Ny*Ly,Ny)';

subplot(2,1,1)
plot3d(maillage_y,maillage_x,phi_i)
subplot(2,1,2)
plot3d(maillage_y,maillage_x,phi)
