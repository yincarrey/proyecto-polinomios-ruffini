#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <regex>
#include <cmath>
#include "funciones.h"


vector<Monomio> vectorMonomios(vector<string> terminos) {
  vector<Monomio> monomios;

  for (size_t i = 0; i < terminos.size(); i++) {
    string termino = terminos[i];
    double coeficiente = 1;
    double grado = 0;
    size_t posx = termino.find('x');

    if (posx != string::npos) { // Si hay variable x

      size_t posExponente = termino.find('^');

      if (posExponente != string::npos) { // Si hay un exponente después de la variable x
        grado = stod(termino.substr(posExponente + 1));
        coeficiente = stod(termino.substr(0, posx));
      } 
    } else { // Si no hay variable x
      coeficiente = stod(termino);
      grado = 0;
    }
    
    Monomio monomio = {coeficiente, grado};
    monomios.push_back(monomio);
  }

  return monomios;
}

vector<Monomio> ordenarMonomiosPorGrado(vector<Monomio> monomios) {
    for (size_t i = 0; i < monomios.size(); i++) {
        for (size_t j = i + 1; j < monomios.size(); j++) {
            if (monomios[j].grado > monomios[i].grado) {
                swap(monomios[i], monomios[j]);
            }
        }
    }
    return monomios;
}

double MayorGrado(vector<Monomio> monomios) {
    return monomios[0].grado;
}

double coefMayorGrado(vector<Monomio> monomios) {
    return monomios[0].coeficiente;
}

double MenorGrado(vector<Monomio> polOriginal){
    double grado_menor = 999;
    for(size_t i=0; i<polOriginal.size();i++){
        if(polOriginal[i].grado < grado_menor)
            grado_menor = polOriginal[i].grado;
    }
    return grado_menor;
}

double terminoIndependiente(vector<Monomio> monomios) {
    for (size_t i = 0; i < monomios.size(); i++) {
        if (monomios[i].grado == 0) {
            return monomios[i].coeficiente;
        }
    }
    return 0; // Si no se encuentra el término independiente, se devuelve 0
}

bool ruffini_condicion(vector<Monomio> polOriginal){
    double 
        mayor_grado = MayorGrado(polOriginal),
        menor_grado = MenorGrado(polOriginal);
    if(menor_grado == 0 && mayor_grado > 1){
        return true;
    }
    return false;
    
}

vector<Monomio> ruffini(vector<Monomio> polOriginal, double potRaiz) {
    vector<Monomio> polNuevo;
    double resultado = polOriginal[0].coeficiente;
    Monomio nuevo_monom;
    for (size_t i = 1; i < polOriginal.size(); i++) {
        nuevo_monom.coeficiente = resultado;
        if (polOriginal[i-1].grado > 0) {
            nuevo_monom.grado = polOriginal[i-1].grado - 1;
            polNuevo.push_back(nuevo_monom);
        }
        resultado = potRaiz * resultado + polOriginal[i].coeficiente;
    }
    if (resultado != 0 || polNuevo.empty()) {
        if (polOriginal.back().grado == 0 && resultado > 0) {
            nuevo_monom.coeficiente = resultado;
            nuevo_monom.grado = 0;
            polNuevo.push_back(nuevo_monom);
        } else {
            nuevo_monom.coeficiente = resultado;
            nuevo_monom.grado = polOriginal.back().grado - 1;
            polNuevo.push_back(nuevo_monom);
        }
    }
    return ordenarMonomiosPorGrado(polNuevo);
}

vector<double> divisoresNegativos(vector<double> divsPositivos) {
    vector<double> divsTotales;
    if (divsPositivos.size() == 1 && divsPositivos[0] == 0) {
        return divsPositivos;
    } else {
        for (size_t i = 0; i < divsPositivos.size(); i++) {
            divsTotales.push_back(divsPositivos[i]);
            if (divsPositivos[i] != 0) {
                divsTotales.push_back(-divsPositivos[i]);
            }
        }
        return divsTotales;
    }
}

vector<double> divisores(double coef) {
    vector<double> divs;
    coef = abs(coef);
    if(coef == 0){
        divs.push_back(0);
        return divs;
    }else{
        for(double i=1; i<=coef; i++) {
            if(abs(fmod(coef, i)) < 1e-9) {
                divs.push_back(i);
            }
        }
        return divisoresNegativos(divs);
    }
}

vector<double> eliminarDuplicados(vector<double> divisiones) {
    vector<double> resultadosUnicos;
    for (size_t i = 0; i < divisiones.size(); i++) {
        bool duplicado = false;
        for (size_t j = i + 1; j < divisiones.size(); j++) {
            if (divisiones[i] == divisiones[j]) {
                duplicado = true;
                break;
            }
        }
        if (!duplicado) {
            resultadosUnicos.push_back(divisiones[i]);
        }
    }
    return resultadosUnicos;
}

vector<double> divisiones(vector<double> divIndep, vector<double> divMayor){
    vector<double> resultados;
    for(size_t i=0; i<divIndep.size(); i++){
        for(size_t j=0; j<divMayor.size(); j++){
            double res = (double)divIndep[i] / (double)divMayor[j];
            resultados.push_back(res);
        }
    }
    return eliminarDuplicados(resultados);
}

vector<Monomio> Factorizar(vector<Monomio> polOriginal){
    vector<Monomio> polFactorizado;
    double grado_menor = MenorGrado(polOriginal);
    for(size_t i=0;i<polOriginal.size();i++){
        if(grado_menor == 0) {
            polFactorizado = polOriginal;
            break;
        }
        Monomio nuevo_monom = polOriginal[i];
        nuevo_monom.grado -= grado_menor;
        polFactorizado.push_back(nuevo_monom);
    }
    return polFactorizado;
}

// La ecuación lineal tiene la forma a*x + b = 0, donde a es el coeficiente
// del monomio de grado 1 y b es el coeficiente del monomio independiente.
double ecuacionLineal(vector<Monomio> polinomio) {
    double a = 0.0;
    double b = 0.0;
    for (size_t i = 0; i < polinomio.size(); i++) {
        if (polinomio[i].grado == 1) {
            a = polinomio[i].coeficiente;
        } else if (polinomio[i].grado == 0) {
            b = polinomio[i].coeficiente;
        }
    }
    return -b / a;
}

void ecuacionCuadratica(vector<Monomio> polinomio) {
    double a = 0, b = 0, c = 0;
    for (size_t i = 0; i < polinomio.size(); i++) {
        if (polinomio[i].grado == 2) {
            a = polinomio[i].coeficiente;
        } else if (polinomio[i].grado == 1) {
            b = polinomio[i].coeficiente;
        } else if (polinomio[i].grado == 0) {
            c = polinomio[i].coeficiente;
        }
    }
    double discriminante = b * b - 4 * a * c;
    if (discriminante > 0) {
        double x1 = (-b + sqrt(discriminante)) / (2 * a);
        double x2 = (-b - sqrt(discriminante)) / (2 * a);
        cout 
            << "Raiz #" << " x: " << x1 << endl
            << "Raiz #" << " x: " << x2 << endl;
    } else if (discriminante == 0) {
        double x = -b / (2 * a);
        cout 
            << "Raiz #" << " x: " << x << endl
            << "Raiz #" << " x: " << x << endl;
    } else {
        double parteReal = -b / (2 * a);
        double parteImaginaria = sqrt(-discriminante) / (2 * a);
        cout 
            << "Raiz #" << " x: " << parteReal << " + " << parteImaginaria << "i" << endl
            << "Raiz #" << " x: " << parteReal << " - " << parteImaginaria << "i" << endl;
    }
}

vector<Monomio> rellenarPolinomio(vector<Monomio> polOriginal){
    Monomio monomioFaltante;
    polOriginal = ordenarMonomiosPorGrado(polOriginal);
    for (double i = 0; i < polOriginal.size()-1; i++) {
        if (polOriginal[i].grado - polOriginal[i+1].grado > 1) {
            monomioFaltante.grado = polOriginal[i].grado - 1;
            monomioFaltante.coeficiente = 0;
            polOriginal.insert(polOriginal.begin()+i+1, monomioFaltante);
        }  
    }
    return ordenarMonomiosPorGrado(polOriginal);
}

string arreglarPolinomio(string polinomio) {
    // Agregar "^1" a "x" cuando no tiene exponente
  size_t found = polinomio.find("x");
  while (found != string::npos) {
    if (found + 1 >= polinomio.length() || (polinomio[found + 1] != '^' && !isdigit(polinomio[found + 1]))) {
        polinomio.insert(found + 1, "^1");
    }
    found = polinomio.find("x", found + 1);
  }

    string polinomioArreglado;
    double n = polinomio.size();
    for (double i = 0; i < n; i++) {
        if (polinomio[i] == 'x') {
            if (i == 0 || polinomio[i-1] == '+' || polinomio[i-1] == '-') {
                polinomioArreglado += '1';
            }
            polinomioArreglado += polinomio[i];
        }
        else {
            polinomioArreglado += polinomio[i];
        }
    }
    return polinomioArreglado;
}

// Convierte el polinomio ingresado a una forma en concreto ej: x^2 + x + 1 -> 1x^2+1x^1+1
string estandarizarPolinomio(string polinomio) {
  // Convertir todo a minúsculas
  for (size_t i = 0; i < polinomio.length(); i++) {
    polinomio[i] = tolower(polinomio[i]);
  }

  // Eliminar espacios en blanco
  size_t i = 0;
  while (i < polinomio.length()) {
    if (isspace(polinomio[i])) {
      polinomio.erase(i, 1);
    } else {
      i++;
    }
  }

  return arreglarPolinomio(polinomio);
}

vector<string> separarTerminos(string polinomio) {
  vector<string> terminos;
  string termino = "";

  // Agregar signo positivo en el primer término si es necesario
  if (polinomio[0] != '-' && polinomio[0] != '+') {
    polinomio = "+" + polinomio;
  }

  // Separar términos por signo +
  for (size_t i = 0; i < polinomio.length(); i++) {
    if (polinomio[i] == '+' || polinomio[i] == '-') {
      // Agregar término al vector
      if (termino != "") {
        terminos.push_back(termino);
      }

      // Crear nuevo término
      termino = polinomio[i];
    } else {
      termino += polinomio[i];
    }
  }

  // Agregar último término al vector
  if (termino != "") {
    terminos.push_back(termino);
  }

  // Eliminar signos positivos en cada término
  for (size_t i = 0; i < terminos.size(); i++) {
    if (terminos[i][0] == '+') {
      terminos[i].erase(0, 1);
    }
  }

  return terminos;
}

//Verifica que el polinomio se cumpla con los estandar establecidos. coef enteros, variable x, grados en enteros de 64bits 
bool validarPolinomio(string polinomio) {

  vector<regex> formatos = {
    regex ("^([-+]?[1-9]\\d*x\\^[1-9]{1,19})([-+][1-9]\\d*x\\^[1-9]{1,19})*([-+][1-9]\\d*)"), //termino constante esta al final
    regex ("^([-+]?[1-9]\\d*x\\^[1-9]{1,19}|(-?[1-9]\\d*))([-+][1-9]\\d*x\\^[1-9]{1,19})+"), //termino constante esta al inicio
    regex ("^([-+]?[1-9]\\d*x\\^[1-9]{1,19})([-+][1-9]\\d*x\\^[1-9]{1,19})*([-+][1-9]\\d*)([-+][1-9]\\d*x\\^[1-9]{1,19})*") //termino constante esta al medio
  };

  for (size_t i = 0; i < formatos.size(); i++) {
    if (regex_match(polinomio, formatos[i])) {
      return true;
    }
  }
  return false;
}
