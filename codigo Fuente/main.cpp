#include <iostream>
#include "Individuo.h"
#include "util.h"
#include "AlgoritmoGenetico.h"
#include "Presentacion.h" 
#include "MotorInferencia.h"
#include <map>
#include <numeric>
#include "pruebas.h"

using namespace std;

double random_d(double min, double max)
{
	static default_random_engine generator(unsigned(time(nullptr)));
	uniform_real_distribution<double> distribution(min, max);
	return distribution(generator);
}



void crearBaseConocimiento(string opcion) {

	Presentacion presentacion;
	vector<vector<double>> matriz = presentacion.leerDatos(opcion + "/entrenamiento.csv");
	AlgoritmoGenetico a(60, 0.05, 0.5, 20, 80, 20, matriz);
	vector<Regla> r = a.ejecutar();
	string s;
	cout << "\nDesea guardar esta base de conocimiento (s/n): "; // s para indicar que sE cualquier otra letra para indicar no
	cin >> s;
	if (s == "s") {
		presentacion.generarBaseConocimiento1(opcion, r);
		presentacion.generarBaseConocimiento(opcion, r);
	}
	else {
		cout << "\No se guardo";
	}


}

void menu()
{
	string opcion;
	int opcion_1 = 0;
	map <string, double> resultados;
	Presentacion presentacion;
	string nombre;
	while (presentacion.getSesion()) {

		cout << "Calcular el precio de la accion de: \n\n";
		cout << "1) IBM\n";
		cout << "2) AMD\n";
		cout << "3) Microsoft\n";
		cout << "4) Apple\n";
		cout << "5) Amazon\n\n";
		cout << "0) Salir\n";
		cout << "Ingrese opcion:  ";

		cin >> opcion;

		if (opcion == "0") {
			bool sesion = false;
			presentacion.setSesion(sesion);
		}

		//if (opcion == "IBM" || opcion == "AMD" || opcion == "Microsoft" || opcion == "Apple" || opcion == "Amazon") {
		if (opcion == "1" || opcion == "2" || opcion == "3" || opcion == "4" || opcion == "5") {

			if (opcion == "1") { nombre = "IBM"; }
			if (opcion == "2") { nombre = "AMD"; }
			if (opcion == "3") { nombre = "Microsoft"; }
			if (opcion == "4") { nombre = "Apple"; }
			if (opcion == "5") { nombre = "Amazon"; }

			crearBaseConocimiento(nombre);
			cout << "\nnIngrese opcion de prediccion: \n\n";
			cout << "1) Mostrar En Pantalla\n";
			cout << "2) Generar Reporte\n";
			cin >> opcion_1;



			if (opcion_1 == 1) {

				resultados = presentacion.predecirPrecioAccionCompleto(nombre);
				presentacion.mostrarResultadoPantallaCompleto(resultados, nombre);
			}
			if (opcion_1 == 2) {
				resultados = presentacion.predecirPrecioAccionCompleto(nombre);
				presentacion.generarReporte(resultados, nombre);
			}
		}
		else {
			if (presentacion.getSesion()) {
				cout << "\n\nNo se realizo una prediccion\n\n\n";
				cout << "Posibles Errores:\n";
				cout << "No existe la accion\n";
				cout << "No esta disponible la prediccion\n";

			}

		}

	}
}


int main()
{
	//Probando Modulos
	//pruebaMotorInferencia();
	//probarMutacion();
	//probarPoblacionInicial();
	//probarSeleccion();
	//probarPresentacion();
	//probarGenetico();
	menu();
	return 0;
}