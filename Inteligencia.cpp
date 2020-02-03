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
		A->prev->next=A->next;
		A->next->prev=A->prev;
		delete (A);
		size --;
	}
	void EraseFirst(){
		if(size!=0&&size!=1){
			cout<<"A";
			Nodo *aux=first;
			first=first->next;
			cout<<"B";
			first->prev=NULL;
			cout<<aux->info.nombre;
			delete aux;
			cout<<"D";
		}if(size==1){
			cout<<"A";
			Nodo *aux=first;
			first=NULL;
			last=NULL;
			delete aux;
		}
		size--;
	}
	void EraseLast(){
		if(size!=0&&size!=1){
			Nodo *aux;
			aux=last;
			last=last->prev;
			last->next=NULL;
			delete aux;
		}else if(size==1){
			Nodo*aux=last;
			last=NULL;
			first=NULL;
			delete aux;
		}
		size--;
	}
};
Subir(string &A){//Aumenta el piso actual.
	if(A=="PB"){
		A="1";cout<<"Subi";
	}else if(A=="1"){
		A="2";cout<<"Subi";
	}else if(A=="2"){
		A="3";cout<<"Subi";
	}
}
Bajar(string &A){//Decrementa el piso actual.
	if(A=="1"){
		A="PB";cout<<"Baje";
	}else if(A=="2"){
		A="1";cout<<"Baje";
	}else if(A=="3"){
		A="2";cout<<"Baje";
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
bool Compare(Nodo A, Nodo B){
	string a=A.info.nombre+" "+A.info.apellido;
	string b=B.info.nombre+" "+B.info.apellido;
	return a<b;
}
void LlenarAscensor(string piso, Lista &Ascensor, Lista &Espera, int max){//Mete elementos de la lista Espera a Ascensor segun el piso actual y la capacidad del ascensor.
	if(piso=="PB"){
		while(Espera.size!=0&&Espera.first->info.origen==piso&&Ascensor.size<max){
			Ascensor.InsertBack(Espera.first);
			cout<<"Entra "<<Espera.first->info.nombre<<endl;
			cout<<Espera.size;
			Espera.EraseFirst();
		}
	}else if(piso=="1"){
		cout<<"1";
		while(Espera.last->info.origen==piso&&Ascensor.size<max){
			Ascensor.InsertBack(Espera.last);
			Espera.EraseLast();
			cout<<"Stack";
		}
	}else if(piso=="2"){
		cout<<"2";
		if(Ascensor.size%2==0){
			while(Espera.first->info.origen==piso&&Ascensor.size<max){
				Ascensor.InsertBack(Espera.first);
				Espera.EraseFirst();
				cout<<"Deque";
			}
		}else{
			while(Espera.last->info.origen==piso&&Ascensor.size<max){
				Ascensor.InsertBack(Espera.last);
				Espera.EraseLast();
				cout<<"Deque";
			}
		}
	}else{
		cout<<"3";
		while(Espera.first->info.origen==piso&&Ascensor.size<max){
			Nodo *aux1;
			Nodo *aux2;
			aux1=Espera.first;
			aux2=Espera.first;
			while(aux1!=Espera.last){
				Compare(*aux2,*aux2->next)?aux2=aux2:aux2=aux2->next;	
			}
			Ascensor.InsertBack(aux2);
			Espera.erase(aux2);
			delete(aux1,aux2);
			cout<<"OL";
			
		}	
	}
}
void MoverAscensor(string &actual, Lista &Ascensor, Lista &Espera, Lista &Pisos, int max, int &iter){//Funci[on principal en la que se encuentran las llamadas a las demas funciones.
	LlenarAscensor(actual, Ascensor, Espera, max);
	if(Conv(actual)<Conv(Pisos.first->info.origen)){
		cout<<"Compare pisos";
		while(actual!="3"){
			cout<<"Voya a llenar";
			LlenarAscensor(actual, Ascensor, Espera, max);
			cout<<"Llene subiendo";
			Subir(actual);
		}
	}else{
		while(actual!="PB"){
			LlenarAscensor(actual, Ascensor, Espera, max);
			cout<<"LLene bajando";
			Bajar(actual);
		}
	}
}
int main(){
	int max, iter=0;
	string PisoActual="PB";
	char symbol;
	Lista Pisos=Lista();
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
				Pisos.InsertBack(aux);
			}
		}
	/*	Nodo *p= Pisos.first;
		while(p!=Pisos.last->next){
			cout<<p->info.origen;
			p=p->next;
		}
		cout<<endl;*/
		MoverAscensor(PisoActual, Ascensor, Espera, Pisos, max, iter);
	}
	return 0;
}
