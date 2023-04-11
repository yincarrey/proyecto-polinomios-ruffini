#ifndef TALLER_POLINOMIOSS_FUNCIONES_H
#define TALLER_POLINOMIOSS_FUNCIONES_H

#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
#include <vector>
#include <regex>

using namespace std;

struct Monomio {
    double coeficiente; // Coeficiente del monomio
    double grado; // Grado del monomio
};

vector<Monomio> vectorMonomios(vector<string> terminos);

vector<Monomio> ordenarMonomiosPorGrado(vector<Monomio> monomios);

double MayorGrado(vector<Monomio> monomios);

double coefMayorGrado(vector<Monomio> monomios);

double MenorGrado(vector<Monomio> polOriginal);

double terminoIndependiente(vector<Monomio> monomios);

bool ruffini_condicion(vector<Monomio> polOriginal);

vector<Monomio> ruffini(vector<Monomio> polinomio, double raiz);

vector<double> divisoresNegativos(vector<double> divsPositivos);

vector<double> divisores(double coef);

vector<double> eliminarDuplicados(vector<double> divisiones);

vector<double> divisiones(vector<double> divIndep, vector<double> divMayor);

vector<Monomio> Factorizar(vector<Monomio> polOriginal);

double ecuacionLineal(vector<Monomio> polinomio);

void ecuacionCuadratica(vector<Monomio> polinomio);

vector<Monomio> rellenarPolinomio(vector<Monomio> polOriginal);

string arreglarPolinomio(string polinomio);

string estandarizarPolinomio(string polinomio);

vector<string> separarTerminos(string polinomio);

bool validarPolinomio(string polinomio);

#endif //TALLER_POLINOMIOSS_FUNCIONES_H