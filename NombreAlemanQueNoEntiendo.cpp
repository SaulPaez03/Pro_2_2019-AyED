#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
struct Datos{
	string nombre, apellido, origen,destino;
	void operator =(Datos A){
		nombre=A.nombre;
		apellido=A.apellido;
		origen=A.origen;
		destino=A.destino;
	} 
	bool operator>(Datos A){
		string a=nombre+" "+apellido;
		string b=A.nombre+" "+A.apellido;
		return a>b;
	}
};
template <typename t>
	struct Nodo{
		t info;
		Nodo *next, *prev;
		Nodo(t A){
			info=A;
		}	
	};
template <typename t>
class Lista{
	int size;
	Nodo<t> *first, *last;
	public:
	bool 
	IsEmpty(){
		return size==0;
	}
	Lista(){
			size=0;
			first=NULL;
			last=NULL;
		}
	void InsertBack(Nodo<t> *A){//Inserta un elemento al final de la lista;
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
	void InsertFront(Nodo<t> *A){//Inserta un elemento al principio de la lista; 
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
	void erase(Nodo<t> *A){//Borra un element de la lista;
		if(A!=first&&A!=last){
			A->prev->next=A->next;
			A->next->prev=A->prev;
			delete (A);
			size --;
		}else if(A==first&&size!=1){
			first=A->next;
			first->prev=NULL;
			A->next==NULL;
			size--;
		}else if(A==last&&size!=1){
			last=A->prev;
			last->next==NULL;
			A->prev==NULL;
			size--;
		}else{
			first=NULL;
			last=NULL;
			size--;
		}
	}
	Nodo<t> *GetFirst(){
		return first;
	}
	Nodo<t> *GetLast(){
		return last;
	}
	t *get(Nodo<t> *A){
		return &A->info;
	}
	Nodo<t> *next(Nodo<t>*A){
		return A->next;
	}
	int Size(){
		return size;
	}
	void Size(int A){
		size=A;
	}
	void First(Nodo<t> *A){
		first=A;
	}
	void Last(Nodo<t> *A){
		last=A;
	}
	bool InList(t A){
		Nodo<t> *B=GetFirst();
		for(int i=0;i<Size();i++){
			if(B->info==A){
				return true;
			}
			B=next(B);
		}
		return false;
	}
};
template <typename t>
class Queue: public Lista<t>{
	public:
	Queue(){
		this->Size(0);
		this->First(NULL);
		this->Last(NULL);
	}
	void Enqueue(Nodo<t> *A){
		this->InsertBack(A);
	}
	void Dequeue(){
		this->erase(this->GetFirst());
	}
	t Head(){
		get(this->First());
	}
};
template <typename t>
class Stack: public Lista<t>{
	public:
	Stack(){
		this->Size(0);
		this->First(NULL);
		this->Last(NULL);
	}
	void Push(Nodo<t> *A){
		this->InsertBack(A);
	}
	void Pop(){
		this->erase(this->GetLast());
	}
	t *Top(){
		return this->get(this->Last());
	}
};
template <typename t>
class Deque: public Lista<t>{
	public:
	Deque(){
		this->Size(0);
		this->First(NULL);
		this->Last(NULL);
	}
	void PushFront(Nodo<t> *A){
		InsertBack(A);
	}
	void EraseFront(){
		this->erase(this->GetFirst());
	}
	t Head(){
		get(this->First());
	}
	void PushBack(Nodo<t> *A){
		this->InsertBack(A);
	}
	void Pop(){
		this->erase(this->GetLast());
	}
	t tail(){
		return get(this->Last());
	}

};
template <typename t>
class PriorityQueue: public Queue<t>{
	public:
	PriorityQueue(){
		this->Size(0);
		this->First(NULL);
		this->Last(NULL);
	}
	void Priority(Nodo<t> *A){
		Nodo<t> *aux= this->GetFirst();
		Nodo<t> *menor=A;
		while(aux!=NULL){
			this->get(menor)<this->get(aux)?menor=menor:menor=aux;
			aux=this->next(aux);
		}
		if(menor!=A){
			A->next=menor->next;
			A->prev=menor;
			menor->next->prev=A;
			menor->next=A;
		}else{
			this->Enqueue(A);
		}
	}
	void insert(Nodo<t> *A, Nodo<t>*B){
		B->next=A->next;
		B->prev=A;
		A->next->prev=B;
		A->next=B;
	}
};
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
void Vaciar(string actual, Stack<Datos> &Ascensor, Queue<string> &Pisos, int iter){
	Nodo<Datos> *a=Ascensor.GetLast();
	while(a!=NULL){
		if(a->info.destino==actual){
			Datos A=a->info;
			cout<<A.nombre<<" "<<A.apellido<< " en "<<iter<<" intervalos."<<endl; 
			Ascensor.Pop();
			a=Ascensor.GetLast();
		}else{
			break;
		}		
	}
}
void LlenarAscensor(string &actual, Stack<Datos> &Ascensor,Queue<Datos> &PB,Stack<Datos> &P1, Deque<Datos> &P2, PriorityQueue<Datos> &P3, Queue<string> &Pisos, int max){
	if(actual=="PB"){
		while(Ascensor.Size()<max&&PB.IsEmpty()==false){
			Ascensor.Push(PB.GetFirst());
			Datos A=*PB.get(PB.GetFirst());
			Nodo<string> *B=new Nodo<string>(A.destino);
			if(!Pisos.InList(A.destino)){
				Pisos.Enqueue(B);
			}
			PB.Dequeue();
		}
	}else if(actual=="1"){
		while(Ascensor.Size()<max&&!P1.IsEmpty()){
			Ascensor.Push(P1.GetLast());
			Datos A=*P1.get(P1.GetLast());
			Nodo<string> *B=new Nodo<string>(A.destino);
			if(!Pisos.InList(A.destino)){
				Pisos.Enqueue(B);
			}
			P1.Pop();
		}
	}else if(actual=="2"){
		while(Ascensor.Size()<max&&!P2.IsEmpty()){
			if(P2.Size()%2==0){
				Ascensor.Push(P2.GetFirst());
				Datos A=*P2.get(P2.GetFirst());
				Nodo<string> *B=new Nodo<string>(A.destino);
				if(!Pisos.InList(A.destino)){
					Pisos.Enqueue(B);
				}
				P2.EraseFront();
			}else{
				Ascensor.Push(P2.GetLast());
				Datos A=*P2.get(P2.GetLast());
				Nodo<string> *B=new Nodo<string>(A.destino);
				if(!Pisos.InList(A.destino)){
					Pisos.Enqueue(B);
				}
				P2.Pop();
			}
		}
	}else if(actual=="3"){
		while(Ascensor.Size()<max&&!P3.IsEmpty()){
			Ascensor.Push(P3.GetFirst());
			Datos A=*P3.get(P3.GetFirst());
			Nodo<string> *B= new Nodo<string>(A.destino);
			if(!Pisos.InList(A.destino)){
				Pisos.Enqueue(B);
			};
			P3.Dequeue();
		}
	}
}
Queue<string> ActualizarPiso(string actual,Queue<string> Pisos, Queue<Datos> PB, Stack<Datos> P1, Deque<Datos>P2,PriorityQueue<Datos>P3){
	if(actual=="PB"){cout<<"A ";
		for(int i=0;i<Pisos.Size();i++){
			if(*Pisos.get(Pisos.GetFirst())==actual){
				cout<<"B ";
				if(!PB.IsEmpty()){
					cout<<"C ";
					Pisos.Enqueue(Pisos.GetFirst());
				cout<<"D ";
				}
			}
			Pisos.Dequeue();
		}
	}else if(actual=="1"){
		for(int i=0;i<Pisos.Size();i++){
			if(*Pisos.get(Pisos.GetFirst())==actual){
				if(!P1.IsEmpty()){
					Pisos.Enqueue(Pisos.GetFirst());
				}
			}
			Pisos.Dequeue();
		}
	}else if(actual=="2"){
		for(int i=0;i<Pisos.Size();i++){
			if(*Pisos.get(Pisos.GetFirst())==actual){
				if(!P2.IsEmpty()){
					Pisos.Enqueue(Pisos.GetFirst());
				}
			}
			Pisos.Dequeue();
		}
	}else{
		for(int i=0;i<Pisos.Size();i++){
			if(*Pisos.get(Pisos.GetFirst())==actual){
				if(!P3.IsEmpty()){
					Pisos.Enqueue(Pisos.GetFirst());
				}
			}
			Pisos.Dequeue();
		}
	}
}
void MoverAscensor(string &actual, Stack<Datos> &Ascensor, Queue<string> &Pisos,Queue<Datos> &PB,Stack<Datos> &P1,Deque<Datos> &P2,PriorityQueue<Datos> &P3, int max, int &iter){//Funcion principal en la que se encuentran las llamadas a las demas funciones.
	while(!Pisos.IsEmpty()){
//		cout<<iter<<" iteraciones."<<endl;
//		cout<<actual<<" "<<*Pisos.get(Pisos.GetFirst())<<endl;
		Vaciar(actual,Ascensor,Pisos, iter);
		LlenarAscensor(actual, Ascensor,PB,P1,P2,P3,Pisos, max);
		Nodo<string> *b=Pisos.GetFirst();
		Pisos=ActualizarPiso(actual,Pisos,PB,P1,P2,P3);
		if(!Pisos.IsEmpty()){
			if(Conv(actual)<Conv(*Pisos.get(Pisos.GetFirst() ) ) ){
				Subir(actual);
			}else{
				Bajar(actual);
			}
			iter++;
		}
	}
//	cout<<"Se acaba el intervalo"<<endl;

}
int main(){
	int max, iter=1;
	string PisoActual="PB";
	char symbol;
	Stack<Datos> P1=Stack<Datos>();
	Stack<Datos> Ascensor=Stack<Datos>();
	Queue<Datos> PB=Queue<Datos>();
	Deque<Datos> P2=Deque<Datos>();
	Queue<string> Pisos=Queue<string>();
	PriorityQueue<Datos> P3=PriorityQueue<Datos>();
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
				Nodo<Datos> *aux=new Nodo<Datos>(A);
				if(A.origen=="PB"){
					PB.Enqueue(aux);
				}else if(A.origen=="1"){
					P1.Push(aux);
				}else if(A.origen=="2"){
					P2.PushBack(aux);
				}else if(A.origen=="3"){
					P3.Priority(aux);
				}
				Nodo<string> *piso= new Nodo<string>(A.origen);
				if(!Pisos.InList(A.origen)){
					Pisos.Enqueue(piso);
				}
			}
		}
		MoverAscensor(PisoActual, Ascensor, Pisos,PB, P1,P2,P3, max, iter);
	}
	return 0;
}

