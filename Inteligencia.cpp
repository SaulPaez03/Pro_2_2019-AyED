#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
struct Persona{
	string nombre, apellido, origen,destino;
};
struct Nodo{// Declaracion del nodo que contiene la informacion de las personas;
	Persona info;
	Nodo *next, *prev;
	Nodo(Persona A){//Constructor del nodo;
		info.nombre = A.nombre;
		info.apellido = A.apellido;
		info.destino = A.destino;
		info.origen= A.origen;
	}

};
struct NodoPiso{//Declaracion del nodod que contiene las solicitudes de movimiento del ascensor;
	string piso;
	NodoPiso *next,*prev;
	NodoPiso(string A){//Constructor del nodo;
		piso=A;
		next=NULL;
		prev=NULL;
	}
};
template <class T>
 class Lista{//Implementacion de la lista, utilizando T como template para que funcione con ambos tipos de nodo.
	public:
	T *first, *last;
	int size;
	Lista(){
		first= NULL;
		last= NULL;
		size=0;
	}
	void InsertFront(T *A){//Inserta un elemento al principio de la lista;
		if(size!=0){
			A->next= first;
			A->prev= NULL;
			first->prev= A;
			first=A;
		}else{
			first=A;
			last=A;
		}
		size++;
	}
	void InsertBack(T *A){//Inserta un elemento al final de la lista;
		if(size!=0){
			last->next=A;
			A->prev=last;
			last=A;
		}else{
			first=A;
			last=A;
		}
		size++;
	}
	void erase(T *A){//Borra un element de la lista;
		A->prev->next=A->next;
		A->next->prev=A->prev;
		delete (A);
		size --;
	}
	
};

int main() {
	int max,num,count=1;
	char symbol;
	Persona *A;
	A= new Persona;
	Lista<NodoPiso> Pisos=Lista<NodoPiso>();
	Lista<Nodo> Espera=Lista<Nodo>();
	Lista<Nodo> Ascensor=
	Nodo *aux;
	NodoPiso *aux1;
	ifstream entrada;
	entrada.open("Entrada.in",ios::in);
	entrada>>max;
	while(!entrada.eof()){
		Persona A;
		entrada>>symbol;
		if(symbol=='+'){
			entrada>>num;
			for(int i=0;i<num;i++){
				entrada>>A.nombre>>A.apellido>>A.origen>>A.destino;
				aux= new Nodo(A);
				Espera.InsertBack(aux);
				aux1=new NodoPiso(A.origen);
				Pisos.InsertBack(aux1);
			}
			count++;
		}
	}
	return 0;
}
