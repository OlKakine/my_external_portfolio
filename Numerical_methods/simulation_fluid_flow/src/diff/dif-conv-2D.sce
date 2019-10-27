dx=Lx/Nx;
dy=Ly/Ny;

//exec("dif-conv-f.sce")

dir  = get_absolute_file_path("dif-conv-2D.sce")
file = dir+"dif-conv-f.sce" 
exec(file, -1)

cx=zeros(Ny,Nx); //composante x de la vitesse de convection
cy=zeros(Ny,Nx); //composante y de la vitesse de convection

phi=zeros(Ny,Nx);   //fonction à calculer
phi_i=zeros(Ny,Nx); //condition initiale

//on initialise phi et les matrices cx et cy
//en utilisant conv et phi_0 definis dans test-2D.sce
function [cx,cy,phi_i]=init_cs_phi_i()
for i=1:Ny
    for j=1:Nx
        c=conv((i-1)*dy,(j-1)*dx)
        cx(i,j)=c(1)
        cy(i,j)=c(2)
        phi_i(i,j)=phi_0((i-1)*dy,(j-1)*dx)
    end
end
endfunction
[cx,cy,phi_i]=init_cs_phi_i();
phi=phi_i;

    //on initialise dt et donc Nt pour être sur de la convergence
dt=min(calcul_dt(cx,dx),calcul_dt(cy,dy));
Nt=floor(Tf/dt);




