#include <iostream>
#include <cmath>
#include "Random64.h"

int main(){

  const double L  = 10.0; // unidad de longitud
  const double A0 = 10.0; // unidad de concentracion
  const long   N  = 100000000; // numero de realizaciones
  const unsigned long long semilla = 1;

  const double lam = L/10;
  //varianzas
  const double sd_d = std::sqrt(10*L);    
  const double sd_a = std::sqrt(10*A0);   

  Crandom ran(semilla);

  double suma = 0, suma2 = 0;
  long validos = 0;

  for(long k = 0; k < N; k++){
    double d  = ran.gauss(L,  sd_d);
    double a0 = ran.gauss(A0, sd_a);
    if(d <= 0 || a0 <= A0/2) continue; //sólo podemos tomar los valores positivos para evaluar el logaritmo. 
    double xd = (lam/d)*std::log(2*a0/A0);
    if(xd >= 1) continue;                   // x<d
    suma  += xd;
    suma2 += xd*xd;
    validos++;
  }

  double media = suma/validos;
  double varianza = (suma2/validos - media*media)*validos/(validos - 1);

  std::cout << "fraccion valida: " << (double)validos/N << "\n";
  std::cout << "media    : " << media << "\n";
  std::cout << "varianza : " << varianza << "\n";
  std::cout << "ruido (CV) : " << sqrt(varianza)/media << "\n";
  return 0;
}