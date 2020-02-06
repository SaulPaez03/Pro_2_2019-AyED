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
			size--;
		}else if(size!=1){
			first=first->next;
			size--;
		}else{
			first=NULL;
			size--;
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
	void EraseLast(){
		if(size!=1&&size!=0){
			size--;
			last->prev->next==NULL;
			last=last->prev;
		}
	}
};
bool Compare(Nodo *A, Nodo *B){
	string a=A->info.nombre+" "+A->info.apellido;
	string b=B->info.nombre+" "+B->info.apellido;
	return a<b;
}
Nodo *Priority(Lista &A){
	Nodo *aux1=A.first;
	Nodo *aux2;
	while(aux1!=NULL){
		if(aux1->next!=NULL){
			if(!Compare(aux2,aux1->next)){
				aux2=aux1->next;
			}
		}
		aux1=aux1->next;
	}
	cout<<&aux2;
	return aux2;
}
void Vaciar(string actual, Lista &Ascensor, ListaPisos &Pisos, int iter){
	Nodo *a=Ascensor.last;
	while(a!=NULL){
		if(a->info.destino==actual){
			cout<<Ascensor.last->info.nombre<<" "<<Ascensor.last->info.apellido<< " en "<<iter<<" intervalos."<<endl; 
			Ascensor.EraseLast();
			a=a->prev;
		}else{
			break;
		}
		
	}
}
void Subir(string &A){//Aumenta el piso actual.
	if(A=="PB"){
		A="1";
		return;
	}else if(A=="1"){
		A="2";
		return;
	}else if(A=="2"){
		A="3";
		return;
	}
}
void Bajar(string &A){//Decrementa el piso actual.
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
void LlenarAscensor(string piso, Lista &Ascensor, Lista &Espera,ListaPisos &Pisos, int max){//Mete elementos de la lista Espera a Ascensor segun el piso actual y la capacidad del ascensor.
	NodoPisos *a;
	NodoPisos *b=Pisos.first;
	if(piso=="PB"){
		while(Espera.size!=0&&Espera.first->info.origen==piso&&Ascensor.size<max){
			Ascensor.InsertBack(Espera.first);
			a=new NodoPisos(Espera.first->info.destino);
			Pisos.Enqueue(a);
			Espera.erase(Espera.first);
			cout<<"Entro alguien";
			
		}
	}else if(piso=="1"){
		while(Espera.size!=0&&Espera.last->info.origen==piso&&Ascensor.size<max){
			Ascensor.InsertBack(Espera.last);
			a=new NodoPisos(Espera.last->info.destino);
			Pisos.Enqueue(a);
			Espera.erase(Espera.last);
						cout<<"Entro alguien";
		}
	}else if(piso=="2"){
		if(Espera.size!=0&&Ascensor.size%2==0){
			while(Espera.first->info.origen==piso&&Ascensor.size<max){
				Ascensor.InsertBack(Espera.first);
				a=new NodoPisos(Espera.first->info.destino);
				Pisos.Enqueue(a);
				Espera.erase(Espera.first);			cout<<"Entro alguien";
			}
		}else{
			while(Espera.size!=0&&Espera.last->info.origen==piso&&Ascensor.size<max){
				Ascensor.InsertBack(Espera.last);
				a=new NodoPisos(Espera.last->info.destino);
				Pisos.Enqueue(a);
				Espera.erase(Espera.last);			cout<<"Entro alguien";
			}
		}
	}else{
		Nodo *aux1;
		aux1=Priority(Espera);cout<<"A ";
		while(Espera.size!=0&&aux1->info.origen==piso){
			Ascensor.InsertBack(aux1);cout<<"B ";
			a=new NodoPisos(aux1->info.destino);cout<<"C ";
			Pisos.Enqueue(a);cout<<"D ";
			Espera.erase(aux1);cout<<"E ";
			aux1=Priority(Espera); cout<<"F ";
		}
	}
}
void MoverAscensor(string &actual, Lista &Ascensor, Lista &Espera, ListaPisos &Pisos, int max, int &iter){//Funcion principal en la que se encuentran las llamadas a las demas funciones.
	while(Pisos.first!=NULL){
		Vaciar(actual,Ascensor,Pisos, iter);cout<<"Vacie ";
		LlenarAscensor(actual, Ascensor, Espera,Pisos, max);cout<<"Llene ";
		NodoPisos *b=Pisos.first;
		while(b!=NULL){
			if(b->piso==actual){
				Pisos.Erase(b);cout<<"Borre un piso ";
			}			
			b=b->next;
		}
		if(Pisos.first!=NULL){
			if(Conv(actual)<Conv(Pisos.first->piso)){
				Subir(actual);cout<<"Subi un piso ";
			}else{
				Bajar(actual);cout<<"Baje un piso";
			}
			iter++;cout<<iter<<endl;
		}
	}
	cout<<"sali";
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
