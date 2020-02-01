#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
struct Datos;
struct Datos{
	string nombre, apellido, origen,destino,piso;
};
struct Nodo;
struct Nodo{
	Nodo *next, *prev;
	Datos info;
	string piso;
	Nodo(Datos A){//Constructor del nodo
		info.nombre=A.nombre;
		info.apellido=A.apellido;
		info.origen=A.origen;
		info.destino=A.destino;
		piso=A.destino;
	}	
	
};
class Lista;
class Lista{
	Nodo *first,*last;
	int size;
	public:
	Lista(){//Constructor de la lista
		first= NULL;
		last= NULL;
		size=0;
	}
	void InsertFront(Nodo A){//Inserta un elemento al principio de la lista;
		if(size!=0){
			A.next= first;
			A.prev= NULL;
			first->prev= &A;
			first=&A;
		}else{
			first=&A;
			last=&A;
		}
		size++;
	}
	void InsertBack(Nodo A){//Inserta un elemento al final de la lista;
		if(size!=0){
			last->next=&A;
			A.prev=last;
			last=&A;
		}else{
			first=&A;
			last=&A;
		}
		size++;
	}
	void erase(Nodo A){//Borra un element de la lista;
		A.prev->next=A.next;
		A.next->prev=A.prev;
		delete (&A);
		size --;
	}
};
int main(){
	int max,num,count=1;
	string PisoActual="PB";
	char symbol;
	Datos A;
	Lista Pisos=Lista();
	Lista Espera=Lista();
	Lista Ascensor=Lista();
	ifstream entrada;
	entrada.open("Entrada.in",ios::in);//Abre el archivo de lectura
	entrada>>max;
	while(!entrada.eof()){
		Datos A;
		entrada>>symbol;
		if(symbol=='+'){
			entrada>>num;
			for(int i=0;i<num;i++){
				cout<<i<<endl;
				entrada>>A.nombre>>A.apellido>>A.origen>>A.destino;
				cout<<"Lei"<<endl;
				Nodo aux= Nodo(A);
				cout<<"Declare el nodo";
				Espera.InsertBack(aux);
				cout<<"Meti el nodo en la lista";
				Pisos.InsertBack(aux);
				cout<<"Pisos";
			}
			count++;
		}
		else{
			MoverAscensor();
		}
	}
	return 0;
}
