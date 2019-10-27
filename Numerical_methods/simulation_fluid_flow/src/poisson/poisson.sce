
// Retourne la fréquence d'échantillonage de la transformée de Fourier discrète
function [freqs]=fftfreq(N, L)
    if (modulo(N,2)==0) then
        freq1=linspace(0,N/2-1,N/2)
        freq2=linspace(-N/2,-1,N/2)
    else
        freq1=linspace(0,(N-1)/2,(N+1)/2)
        freq2=linspace(-(N-1)/2,-1,(N-1)/2)
    end
    freqs=cat(2,freq1,freq2)
    freqs=(2*%i*%pi/L)*freqs
endfunction


// Résolution de l'équation de Poisson en dimension 2 en utilisant la FFT
//    laplacien(psi) = f
// Entrée: f de taille (Ny,Nx) sur un domaine de taille (Ly,Lx)
// Sortie: psi, solution de l'équation
function [psi]=poisson_2d(f, Nx, Ny, Lx, Ly)
    kx = fftfreq(Nx,Lx)
    ky = fftfreq(Ny,Ly)
    psi_hat = zeros(Ny,Nx)
    f_hat = fft(f, "nonsymmetric")
    for p=1:Ny
        for q=1:Nx
            if (p+q > 2) then
                psi_hat(p,q) = f_hat(p,q)/(kx(q)**2+ky(p)**2)
            end
        end
    end
    psi = real(ifft(psi_hat, "nonsymmetric"))
endfunction

// Résolution de l'équation de Poisson avec rot en dimension 2 en utilisant la FFT
//    laplacien(Ux) = -dW/dy
//    laplacien(Uy) = +dW/dx
// Entrée: champs de vorticité W de taille (Ny,Nx) sur un domaine de taille (Ly,Lx)
// Sortie: Ux et Uy, vitesses solution des équations
function [Ux,Uy]=poisson_curl_2d(W, Nx, Ny, Lx, Ly)
    // TODO: Calculer Ux et Uy à partir de la vorticité par FFT avec l'option 'nonsymmetric'
    kx = fftfreq(Nx,Lx)
    ky = fftfreq(Ny,Ly)
    ux_hat = zeros(Ny,Nx)
    uy_hat = zeros(Ny,Nx)
    w_hat = fft(W, "nonsymmetric")
    for p=1:Ny
        for q=1:Nx
            ks_carre=kx(q)**2+ky(p)**2
            if ks_carre ~= 0 then
                ux_hat(p,q) =- w_hat(p,q)/ks_carre*ky(p)
                uy_hat(p,q)=w_hat(p,q)/ks_carre*kx(q)
                
            end
        end
    end
    Ux = real(ifft(ux_hat, "nonsymmetric"))
    Uy = real(ifft(uy_hat, "nonsymmetric"))
endfunction

