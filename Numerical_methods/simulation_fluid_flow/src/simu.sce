
// Domain size and discretization
Lx = 1.0
Ly = 1.0
Nx = 128
Ny = 128
dx = Lx/Nx
dy = Ly/Ny
X = linspace(0.0, Lx*(Nx-1)/Nx, Nx)
Y = linspace(0.0, Ly*(Ny-1)/Ny, Ny)

// Simulation parameters
T     = 1.50
kappa    = 1e-4 //nu=kappa
rho   = 30.0
delta = 0.05


// Initialize vorticity
function [W] = init_vorticity(y,x)
if(y<=0.5) then
    W=2*%pi*delta*cos(2*%pi*x)-rho*(1-tanh(rho*(y-0.25))**2)
else
    W=2*%pi*delta*cos(2*%pi*x)+rho*(1-tanh(rho*(0.75-y))**2)
end
endfunction


// Plot and dump fields (at every steps of the simulation so that we can generate a video)
function plot_fields(W, Ux, Uy, iteration)
    fig = scf(0)
    clf()
    fig.color_map = [jetcolormap(64); whitecolormap(1)]
    fig.background = 65;
    cmm = [0,64]

    subplot(131)
    title("W(x,y)")
    colorbar(min(W), max(W), cmm)
    Sgrayplot(X, Y, W', colminmax=cmm)
    xlabel("x")
    ylabel("y")
    
    subplot(132)
    title("Ux(x,y)")
    colorbar(min(Ux), max(Ux), cmm)
    Sgrayplot(X, Y, Ux', colminmax=cmm)
    xlabel("x")
    ylabel("y")
    
    subplot(133)
    title("Uy(x,y)")
    colorbar(min(Uy), max(Uy), cmm)
    Sgrayplot(X, Y, Uy', colminmax=cmm)
    xlabel("x")
    ylabel("y")
        
    figname = sprintf("ite_%04d.png", iteration)
    xs2png(fig, figname)
endfunction


// Plot isocontours (only at t=0.80 and t=1.20)
function plot_isocontours(W, figname)
    if (t~=0.80) & (t~=1.20) then
        return
    end
    
    fig = scf(1)
    clf()
    contour2d(Y,X,W,-70:10:70)

    figname = sprintf("isocontours_%f.png", t)
    xs2png(fig, figname)
endfunction


function plot_fchamp(W, figname)
    if (t~=0.80) & (t~=1.20) then
        return
    end
    
    fig = scf(1)
    clf()
    //fchamp(poisson_curl_2d(W, Nx, Ny, Lx, Ly),X,Y)
    
    [Ux,Uy]=poisson_curl_2d(W,Nx,Ny,Lx,Ly)
function U=f(t,X)
	x=X(1)
    y=X(2)
	U=[Ux(x,y),Uy(x,y)]

endfunction
fchamp(f,0,1:5:Nx,1:5:Ny)
    
    figname = sprintf("fchamp_%f.png", t)
    
    xs2png(fig, figname)
endfunction


// Load the Poisson solver and the advection-diffusion solver
dir  = get_absolute_file_path("simu.sce")
file = dir+"poisson/poisson.sce" 
exec(file, -1)
file = dir+"diff/dif-conv-f.sce" 
exec(file, -1)

// Figure setup (fig0 = fields, fig1 = isocontours)
figure(0, "position", [0,0,1400,400])
figure(1, "position", [0,0,800,800])

// Initialize vorticity and loop untill final time using adaptive timestep
t = 0.0
ite = 0
W = feval(Y, X, init_vorticity)
while t<T
    [Ux,Uy]=poisson_curl_2d(W, Nx, Ny, Lx, Ly)
    dt=min(calcul_dt(Ux,dx),calcul_dt(Uy,dy));
    if (t<0.80) & (t+dt>0.80) then
        dt = 0.80-t
    elseif (t<1.20) & (t+dt>1.20) then
        dt = 1.20-t
    elseif (t+dt>T) then
        dt = T-t
    end
    
    printf("\niteration %i, from t=%f to t=%f", ite, t, t+dt)
    plot_fields(W,Ux,Uy,ite)
    plot_isocontours(W,t)
    plot_fchamp(W, t)
    
    W=solveur_2D(1,1,dt,Nx,Ny,kappa,W,Ux,Uy)
    
    ite=ite+1
    t=t+dt
end
plot_fields(W,Ux,Uy,ite)
plot_fchamp(W, t)
plot_isocontours(W,t)

printf("\nDone in %i iterations!\n", ite)
exit(0)
