#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
struct Datos{
	string nombre, apellido, origen,destino,piso;
};
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
class Lista{
	public:
	Nodo *first,*last;
	int size;
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
	Nodo First(){
		return *first;
	}
	Nodo Last(){
		return *last;
	}
};
int Conv(string A){
	if(A=="PB"){
		return 0;
	}else if(A=="1"){
		return 1;
	}else if(A=="2"){
		return 2;
	}else{
		return 3;
	}
}
void LlenarAscensor(string piso, Lista Ascensor, Lista Espera, int max){	
	if(piso=="PB"){
		while(Espera.first->info.origen==piso&&Ascensor.size<max){
			Ascensor.InsertBack(*Espera.first);
			Espera.erase(*Espera.first);
		}
	}else if(piso=="1"){
		while(Espera.last->info.origen==piso&&Ascensor.size<max){
			Ascensor.InsertBack(*Espera.last);
			Espera.erase(*Espera.last);
		}
	}else if(piso=="2"){
		if(Ascensor.size%2==0){
			while(Espera.first->info.origen==piso&&Ascensor.size<max){
				Ascensor.InsertBack(*Espera.first);
				Espera.erase(*Espera.first);
			}
		}else{
			while(Espera.last->info.origen==piso&&Ascensor.size<max){
				Ascensor.InsertBack(*Espera.last);
				Espera.erase(*Espera.last);
			}
		}
	}else{
		
	}
}
void MoverAscensor(string actual, Lista Ascensor, Lista Espera, Lista Pisos, int max, int &iter){
	while(actual!=Pisos.first->piso){
		LlenarAscensor(actual, Ascensor, Espera, max);
		if(Conv(actual)>Conv(Pisos.first->piso)){
			//Bajar(actual);
		}
		else{
			//Subir(actual);
		}
	}
}
int main(){
	int max,num, iter=0;
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
				entrada>>A.nombre>>A.apellido>>A.origen>>A.destino;
				Nodo aux= Nodo(A);
				Espera.InsertBack(aux);
				Pisos.InsertBack(aux);
			}
		}
		else{
			MoverAscensor(PisoActual, Ascensor, Espera, Pisos, max, iter);
		}
	}
	return 0;
}
