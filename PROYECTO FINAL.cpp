#include<iostream>
#include<string>
#include<fstream>


using namespace std;

struct Orden {
	int NumeroC;
	int Codigo;
	string Descripcion;
	string Nombre;
	int Cantidad;
	float PrecioU;
	float Subtotal;
	float Iva;
	float Total;
};

Orden arreglo_Orden[100];
int contador = 0;
int contC = 0;
void Alta();
void Lista();
int validacion_de_enteros();
float validacion_de_decimales();
void borrado();
void archivo_escritura();
void archivo_lectura();

void main() {

	archivo_lectura();
	char opcion;
	do {
		system("CLS");
		cout << "Bienvenido a Simulacion de venta de videojuegos 2022" << endl;
		cout << "Que desea hacer hoy?" << endl;
		cout << "a) Alta de orden" << endl << "b) Lista de ordenes" << endl << "c) Borrar una orden " << endl << "d) salir" << endl;
		cin >> opcion;
		system("CLS");
		switch (opcion) {
		case 'a': Alta();
			break;
		case 'b': Lista();
			break;
		case 'c': borrado();
			break;
		case'd':
			break;

		}
	} while (opcion != 'd');
	archivo_escritura();
}

void Alta() {
	Orden nueva_orden;
	nueva_orden.NumeroC = contC;
	cout << "Alta de ordenes" << endl;
	bool validador = false;
	do {
		validador = false;
		cout << "ingrese el codigo de la orden" << endl;
		nueva_orden.Codigo = validacion_de_enteros();
		for (int i = 0; i <= contador; i++) {
			if (nueva_orden.Codigo == arreglo_Orden[i].Codigo) {
				cout << "error, el codigo esta repetido" << endl;
				validador = true;
				break;
			}

		}
	} while (!((nueva_orden.Codigo >= 10000) && (nueva_orden.Codigo <= 99999)) || validador);
	cout << "ingrese descripcion de la orden" << endl;
	cin.ignore();
	getline(cin, nueva_orden.Descripcion);
	cout << "ingrese nombre" << endl;

	getline(cin, nueva_orden.Nombre);
	cout << "establezca el numero a ordenar" << endl;
	nueva_orden.Cantidad = validacion_de_enteros();
	cout << "ingrese el precio unitario del producto a comprar" << endl;
	nueva_orden.PrecioU = validacion_de_decimales();
	nueva_orden.Subtotal = nueva_orden.PrecioU * nueva_orden.Cantidad;
	nueva_orden.Iva = nueva_orden.Subtotal * 0.16;
	nueva_orden.Total = nueva_orden.Iva + nueva_orden.Subtotal;
	arreglo_Orden[contador] = nueva_orden;
	contador++;
	contC++;

}

void Lista() {
	for (int i = 0; i < contador; i++) {
		cout << arreglo_Orden[i].NumeroC << endl;
		cout << arreglo_Orden[i].Codigo << endl;
		cout << arreglo_Orden[i].Descripcion << endl;
		cout << arreglo_Orden[i].Nombre << endl;
		cout << arreglo_Orden[i].Cantidad << endl;
		cout << arreglo_Orden[i].PrecioU << endl;
		cout << arreglo_Orden[i].Subtotal << endl;
		cout << arreglo_Orden[i].Iva << endl;
		cout << arreglo_Orden[i].Total << endl;
		cout << "----------------" << endl;
	}
	system("pause");

}

void borrado() {
	int codigo;
	int guardar = -1;
	cout << "Ingrese codigo de la orden a eliminar" << endl;
	do {
		codigo = validacion_de_enteros();
	} while (!((codigo >= 10000) && (codigo <= 99999)));

	for (int i = 0; i < contador; i++) {

		if (codigo == arreglo_Orden[i].Codigo) {
			guardar = i;
			break;
		}
	}
	if (guardar == -1) {
		cout << "codigo no existente" << endl;
		system("Pause");

	}
	else {
		for (int i = guardar; i < contador - 1; i++) {
			arreglo_Orden[i] = arreglo_Orden[i + 1];
		}
		contador--;
	}

}

int validacion_de_enteros() {
	int x;
	while (!(cin >> x) && (cin.peek() != EOF) || (cin.peek() != '\n')) {


		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

	}
	return x;

}

float validacion_de_decimales() {
	float x;
	while (!(cin >> x) && (cin.peek() != EOF) || (cin.peek() != '\n')) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return x;
}

void archivo_escritura() {
	ofstream archivo_ordenes("ordenes.txt");
	for (int x = 0; x < contador; x++) {
		archivo_ordenes << arreglo_Orden[x].NumeroC << endl;
		archivo_ordenes << arreglo_Orden[x].Codigo << endl;
		archivo_ordenes << arreglo_Orden[x].Descripcion << endl;
		archivo_ordenes << arreglo_Orden[x].Nombre << endl;
		archivo_ordenes << arreglo_Orden[x].Cantidad << endl;
		archivo_ordenes << arreglo_Orden[x].PrecioU << endl;
		archivo_ordenes << arreglo_Orden[x].Subtotal << endl;
		archivo_ordenes << arreglo_Orden[x].Iva << endl;
		archivo_ordenes << arreglo_Orden[x].Total << endl;
		archivo_ordenes << "------------" << endl;
	}
	archivo_ordenes.close();
}

void archivo_lectura() {
	ifstream archivo_ordenes("ordenes.txt");
	if (archivo_ordenes.is_open()) {
		while (archivo_ordenes.eof() != true) {
			archivo_ordenes >> arreglo_Orden[contador].NumeroC;
			archivo_ordenes >> arreglo_Orden[contador].Codigo;
			archivo_ordenes.ignore();
			getline(archivo_ordenes, arreglo_Orden[contador].Descripcion);
			getline(archivo_ordenes, arreglo_Orden[contador].Nombre);
			archivo_ordenes >> arreglo_Orden[contador].Cantidad;
			archivo_ordenes >> arreglo_Orden[contador].PrecioU;
			archivo_ordenes >> arreglo_Orden[contador].Subtotal;
			archivo_ordenes >> arreglo_Orden[contador].Iva;
			archivo_ordenes >> arreglo_Orden[contador].Total;

			string dummy;
			archivo_ordenes.ignore();
			getline(archivo_ordenes, dummy);

			contador++;
		}
		contador--;
		archivo_ordenes.close();
	}
}