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
	Nodo(Datos A){//Constructor del nodo
		info.nombre=A.nombre;
		info.apellido=A.apellido;
		info.origen=A.origen;
		info.destino=A.destino;
		next=NULL;
		prev=NULL;
	}	
	
};
struct NodoPisos{
	string piso;
	NodoPisos *next;
	NodoPisos(string A){
		piso=A;
		next=NULL;
	}
};
class ListaPisos{
	public:
	NodoPisos *first;
	int size;
	Enqueue(NodoPisos *A){
		if(size==0){
			first=A;
		}else{
			first->next=A;
		}
		size++;
	}
	ListaPisos(){
		first=NULL;
		size=0;
	}
	void Dequeue(){
		if(size!=0){
			NodoPisos *p=first;
			first=first->next;
			delete(p);
			size--;
		}
	}
	void Erase(NodoPisos*a){
		if(a!=first){
			NodoPisos *aux=first;
			while(aux->next!=a&&aux!=NULL){
				aux=aux->next;
			}
			aux->next=a->next;
		}else{
			first=first->next;
		}
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
	void InsertFront(Nodo *A){//Inserta un elemento al principio de la lista;
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
	void InsertBack(Nodo *A){//Inserta un elemento al final de la lista;
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
	void erase(Nodo *A){//Borra un element de la lista;
		if(A!=first&&A!=last){
			A->prev->next=A->next;
			A->next->prev=A->prev;
			delete (A);
			size --;
		}else if(A==first){
			first=A->next;
			first->prev=NULL;
			A->next==NULL;
			size--;
		}else{
			last=A->prev;
			last->next==NULL;
			A->prev==NULL;
			size--;
		}
	}
};
void Vaciar(string actual, Lista &Ascensor, ListaPisos &Pisos, int iter){
	Nodo *a=Ascensor.last;
	NodoPisos *b=Pisos.first;
	while(a!=NULL){
		if(a->info.destino==actual){
			cout<<a->info.nombre<<" "<<a->info.apellido<< " en "<<iter<<" intervalos."<<endl; 
			Ascensor.erase(a);
		}
		if(a->prev!=NULL){
			a=a->prev;
		}else{
			break;
		}
	}
	while(b!=NULL){
		if(b->piso==actual){
			Pisos.Erase(b);
		}			
		b=b->next;
	}
}
Subir(string &A){//Aumenta el piso actual.
	if(A=="PB"){
		A="1";
	}else if(A=="1"){
		A="2";
	}else if(A=="2"){
		A="3";
	}
}
Bajar(string &A){//Decrementa el piso actual.
	if(A=="1"){
		A="PB";
	}else if(A=="2"){
		A="1";
	}else if(A=="3"){
		A="2";
	}
}
int Conv(string A){//Convierte los pisos a su representacion en enteros para poder compararlos.
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
bool Compare(Nodo *A, Nodo *B){
	string a=A->info.nombre+" "+A->info.apellido;
	string b=B->info.nombre+" "+B->info.apellido;
	return a<b;
}
void LlenarAscensor(string piso, Lista &Ascensor, Lista &Espera,ListaPisos &Pisos, int max){//Mete elementos de la lista Espera a Ascensor segun el piso actual y la capacidad del ascensor.
	NodoPisos *a;
	NodoPisos *b=Pisos.first;
	if(piso=="PB"){
		while(Espera.size!=0&&Espera.first->info.origen==piso&&Ascensor.size<max){
			Ascensor.InsertBack(Espera.first);
			a=new NodoPisos(Espera.first->info.destino);
			Pisos.Enqueue(a);
			Espera.erase(Espera.first);
			
		}
	}else if(piso=="1"){
		while(Espera.last->info.origen==piso&&Ascensor.size<max){
			Ascensor.InsertBack(Espera.last);
			a=new NodoPisos(Espera.last->info.destino);
			Pisos.Enqueue(a);
			Espera.erase(Espera.last);
		}
	}else if(piso=="2"){
		if(Ascensor.size%2==0){
			while(Espera.first->info.origen==piso&&Ascensor.size<max){
				Ascensor.InsertBack(Espera.first);
				a=new NodoPisos(Espera.first->info.destino);
				Pisos.Enqueue(a);
				Espera.erase(Espera.first);
			}
		}else{
			while(Espera.last->info.origen==piso&&Ascensor.size<max){
				Ascensor.InsertBack(Espera.last);
				a=new NodoPisos(Espera.last->info.destino);
				Pisos.Enqueue(a);
				Espera.erase(Espera.last);
			}
		}
	}else{
			Nodo *aux1=Espera.first;
			Nodo *aux2;
			while(aux1!=Espera.last){
				Compare(aux1,aux1->next)?aux2=aux1:aux2=aux1->next;
				aux1=aux1->next;
			if(aux2->info.origen==piso&&Ascensor.size<max){
				Ascensor.InsertBack(aux2);
				a=new NodoPisos(aux2->info.destino);
				Pisos.Enqueue(a);
				Espera.erase(aux2);
			}
		}	
	}
	while(b!=NULL){
		if(b->piso==piso){
			Pisos.Erase(b);
		}
		b=b->next;
	}
}
void MoverAscensor(string &actual, Lista &Ascensor, Lista &Espera, ListaPisos &Pisos, int max, int &iter){//Funci[on principal en la que se encuentran las llamadas a las demas funciones.
	int count=0;
	while(count<2){
		cout<<actual<<" "<<Pisos.first->piso<<endl;
			Vaciar(actual,Ascensor,Pisos, iter);
			LlenarAscensor(actual, Ascensor, Espera,Pisos, max);
		if(Conv(actual)<=Conv(Pisos.first->piso)){
			Subir(actual);
		}else{
			Bajar(actual);
		}
		count++;
		iter++;
	}
}
int main(){
	int max, iter=1;
	string PisoActual="PB";
	char symbol;
	ListaPisos Pisos=ListaPisos();
	Lista Espera=Lista();
	Lista Ascensor=Lista();
	ifstream entrada;
	entrada.open("Entrada.in",ios::in);//Abre el archivo de lectura
	entrada>>max;
	while(!entrada.eof()){
		entrada>>symbol;
		if(symbol=='+'){
			int num;
			entrada>>num;
			for(int i=0;i<num;i++){
				Datos A;
				entrada>>A.nombre>>A.apellido>>A.origen>>A.destino;
				Nodo *aux=new Nodo(A);
				Espera.InsertBack(aux);
				NodoPisos *aux2= new NodoPisos(A.origen);
				Pisos.Enqueue(aux2);
			}
		}
		MoverAscensor(PisoActual, Ascensor, Espera, Pisos, max, iter);
	}
	return 0;
}
