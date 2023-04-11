#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
#include <vector>
#include <regex>
#include "funciones.h"

using namespace std;

int main(int argc, char const *argv[]) {
  
  string polinomio = argv[1];
  polinomio = estandarizarPolinomio(polinomio);

  cout 
      << endl << "Ejecutando "<< argv[0] <<endl 
      << "Numero de parametros por terminal: " << argc <<endl;


  if (validarPolinomio(polinomio)) {

      cout 
        << endl << "El polinomio ingresado es valido" << endl
        << endl << polinomio << endl << endl;
        vector<string> terminos = separarTerminos(polinomio);
        vector<Monomio> monomios = vectorMonomios(terminos);
        monomios = rellenarPolinomio(monomios);
        double mayorGrado = MayorGrado(monomios);
        double coefMGrado = coefMayorGrado(monomios);
        double menorGrado = MenorGrado(monomios);
        double terminoInd = terminoIndependiente(monomios);
        /* for (size_t i = 0; i < monomios.size(); i++) {
          Monomio monomio = monomios[i];
          cout 
            << "Monomio " << i 
            << ": coef = " << monomio.coeficiente 
            << "; grado = " << monomio.grado << endl;
        } */
        vector <double> divisoresMayor = divisores(coefMGrado);
        vector <double> divisoresTerm = divisores(terminoInd);
        vector <double> potRaices = divisiones(divisoresTerm, divisoresMayor);
        vector<double> resultados;

        if(menorGrado >= 1){
            monomios = Factorizar(monomios);
            mayorGrado = MayorGrado(monomios);
            coefMGrado = coefMayorGrado(monomios);
            menorGrado = MenorGrado(monomios);
            terminoInd = terminoIndependiente(monomios);
            resultados.push_back(0);
        }
        if (mayorGrado == 1){
            resultados.push_back(ecuacionLineal(monomios));
            for (size_t i = 0; i < resultados.size(); i++) {
                cout << "Raiz #" << " x: " << resultados[i] << endl;
            }
            
        } else if(mayorGrado == 2){
            if (resultados.size() != 0)
            {
                for (size_t i = 0; i < resultados.size(); i++) {
                    cout << "Raiz #" << " x: " << resultados[i] << endl;
                }
            }
            ecuacionCuadratica(monomios);

        } else{
            if(ruffini_condicion(monomios)){
                for (size_t i = 0; i < potRaices.size(); i++) {
                    if (ruffini(monomios, potRaices[i])[0].grado != monomios[0].grado) {
                        resultados.push_back(potRaices[i]);
                        monomios = ruffini(monomios, potRaices[i]);
                        if(MayorGrado(monomios) == 2){
                            ecuacionCuadratica(monomios);
                            break;
                        }
                    }   
                }
                for (size_t i = 0; i < resultados.size(); i++){
                    cout << "Raiz #" << " x: " << resultados[i] << endl;
                }
                cout <<endl;
            }else
            {
                cout << "no se cumple la condicion" <<endl;
            }
        }
    } else {
        cout << "El polinomio ingresado no es valido" << endl;
    }
    
    system("pause");
    system("cls");
    return 0;
}