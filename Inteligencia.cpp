#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
struct Persona{
	string Nombre, Apellido, Origen, Destino;
};
struct NodoP{
	Persona Info;
	Nodo *Next, *Prev;
	Nodo(Persona A){
		Info.Nombre = A.Nombre;
		Info.Apellido = A.Apellido;
		Info.Destino = A.Destino;
		Info.Origen= A.Origen;
	}
	
};
class ListaP{
	NodoP *Begin;
	
};

int main() {
	int Max,num;
	char symbol;
	Persona A;
	ifstream Entrada;
	Entrada.open("Entrada.in",ios::in);
	Entrada>>Max;
	while(!entrada.eof()){
		cin>>symbol;
		if(symbol=='+'){
			Entrada<<num;
			for(int i=0;i<num;i++){
				Entrada>>A.Nombre>>A.Apellido>>A.Origen>>A.Destino;
			}
		}
	}
	return 0;
}
