
// Initialise W(x,y)
function [w]=init_field(y,x)
    w=8*%pi**2*cos(2*%pi*x)*cos(2*%pi*y)
endfunction


// Solution de référence du problème laplacien(ux(x,y)) = -(dw/dy)(x,y)
function [refx]=solution_field_x(y,x)
    refx=-2*%pi*cos(2*%pi*x)*sin(2*%pi*y)
endfunction

// Solution de référence du problème laplacien(uy(x,y)) = (dw/dx)(x,y)
function [refy]=solution_field_y(y,x)
    refy=2*%pi*sin(2*%pi*x)*cos(2*%pi*y)
endfunction

function plot_error(W, Refx, Refy, Ux, Uy, Errx, Erry)  
    fig = gcf()
    
    X = linspace(0.0, Lx*(Nx-1)/Nx, Nx)
    Y = linspace(0.0, Ly*(Ny-1)/Ny, Ny)
    
    subplot(7,1,1)
    plot3d(Y,X,W)
    
    subplot(7,1,2)
    plot3d(Y,X,Refx)
    subplot(7,1,3)
    plot3d(Y,X,Ux)
    subplot(7,1,4)
    plot3d(Y,X,Errx)
    
    subplot(7,1,5)
    plot3d(Y,X,Refy)
    subplot(7,1,6)
    plot3d(Y,X,Uy)
    subplot(7,1,7)
    plot3d(Y,X,Erry)
//    
    xs2png(fig, "poisson_curl_error.png")
endfunction


// Fonction de test pour le solveur de Poisson
function test_poisson_curl(Lx, Ly, Nx, Ny)
    printf("::Testing poisson operator::")
    printf("\n  Domain size:    [%0.2f, %0.2f]", Lx, Ly)
    printf("\n  Discretization: [%i, %i]", Nx, Ny)
    
    // X[i] = i*dx avec dx = Lx/Nx et i=0..Nx-1
    // Y[i] = j*dy avec dy = Ly/Ny et j=0..Ny-1
    X = linspace(0.0, Lx*(Nx-1)/Nx, Nx)
    Y = linspace(0.0, Ly*(Ny-1)/Ny, Ny)
    
    printf("\n\n  Initializing field F(x,y).")
    W   = feval(Y, X, init_field)
    
    printf("\n  Initializing reference solution Ref(x,y).")
    Refx = feval(Y, X, solution_field_x)
    Refy = feval(Y, X, solution_field_y)

    dir  = get_absolute_file_path("test_poisson_curl.sce")
    file = dir+"poisson.sce" 
    printf("\n\n  Loading poisson_curl_2d function from file %s%s%s.", char(39), file, char(39))
    exec(file, -1)

    printf("\n\n  Computing Poisson solution Ux(x,y) and Uy(x,y).")
    [Ux,Uy] = poisson_curl_2d(W, Nx, Ny, Lx, Ly)

    printf("\n  Computing errors |Ux-Refx|(x,y) and |Uy-Refy|(x,y).")
    Errx = abs(Ux-Refx)
    Erry = abs(Uy-Refy)
    
    file = pwd()+"/poisson_curl_error.png"
    printf("\n\n  Plotting everything to %s%s%s.", char(39), file, char(39))
    plot_error(W, Refx, Refy, Ux,Uy, Errx, Erry)
    
    printf("\n\n")
    mErrx = max(Errx)
    mErry= max(Erry)
    mErr= max(mErrx,mErry)
    max_error = 1e-12
      
    if (mErr > max_error) then
        printf("  Maximal error is %.10ef, TEST FAILURE (max_error=%.10ef).\n", mErr, max_error)
        exit(1)
    else
        printf("  Maximal error for both Ux and Uy is only %.10ef, TEST SUCCESS.\n", mErr)
        exit(0)
    end
endfunction


// Taille du domaine
Lx = 1.0
Ly = 1.0

// Discretisation du domaine
Nx = 64
Ny = 32

test_poisson_curl(Lx, Ly, Nx, Ny)
