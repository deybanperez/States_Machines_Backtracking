#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>

using namespace std;
/*
	Automata de pila no Deterministico, que dada una cadena la evalua y dice si es acepta o no, usando backtracking.
 */

bool Encontrado=false;


class NodosAdyacentes //Esta clase representa los posibles estados a los que puede saltar un estado actual de llegarle un símbolo
{
	public:
		//Atributos
		int Nombre;//Nombre del estado
		char Transicion;//Símbolo de transición
		char TopePila;
		string Apilar; 
		//Metodos
		NodosAdyacentes()//constructor que inicializa la clase on valores que nunca se podrán alcanzar
		{
			Nombre=0;
			Transicion=' ';
		}
		NodosAdyacentes(int Name,char Trans,string Api,char TopPila)//Constructor que establece valores a los atributos.
		{
			Nombre=Name;
			Transicion=Trans;
			Apilar=Api;
			TopePila=TopPila;
			
		}

};

class Nodos//Clase que representa los estados de la máquina
{
	public:
		//Atributos
		int Nombre;//Nombre del estado
		bool Final;//Indica si el estado es final
		list<NodosAdyacentes> Adyacentes;//Lista de posibles estados de llegada
		//Metodos
		Nodos()//Constructor sin parámetros que establece valores inalcanzables
		{
			Nombre=0;
			Final=false;
			Adyacentes=list<NodosAdyacentes>();
		}
		Nodos(int Nom,bool Fin)//Constructor parametrizado que establece valores otorgados para los atributos de la clase
		{
			Nombre=Nom;
			Final=Fin;
			Adyacentes=list<NodosAdyacentes>();
		}
};

class Grafo//Clase Grafo que tendrá una lista de nodos/estados asociados al grafo
{
	public:
		//Atributos
		int NumNodos;//Numero de estados de la máquina
		list<Nodos> Estados;//Lista de estados de la máquina
		queue<string> Pruebas;//Cola de las cadenas de prueba de la máquina
		stack<char> Pila;
		//Metodos
		Grafo()//Constructor sin parámetros que establece valores inalcanzables
		{
			NumNodos=0;
			Estados= list<Nodos>();
			Pruebas= queue<string>();
			Pila= stack<char>();
			Pila.push('Z');
		}

		void AgregarGrafo(int NumEstados,int NumTer,int NumRe,int NumPruebas);//Pérmite agregar un grafo a la clase
		void VerificarCadena(stack<char> P,int Estado, string Palabra,int idP);//Verifica si las cadenas de la cola de pruebas pertenecen o no al lenguaje
		void Apilar(stack<char> &Pila,string Palabra);

};

void Grafo::AgregarGrafo(int NumEstados,int NumTer,int NumRe,int NumPruebas)
{
	int Finales=0, Origen=0,Destino=0;//Definición de variables a leer
	char Transicion=' ', TopePila=' ';//Definición de variables a leer
	string Cadenas,APila;//Definicion de variables a leer

	list<Nodos>::iterator it;//Apuntador a objetos de la clase nodo
	list<NodosAdyacentes>::iterator it2;//Apuntador a objetos de la clase NodosAdyacentes
	
	NumNodos=NumEstados;//Transfiero el parametro a la clase

	for(int i=1;i<=NumNodos;i++)
	{
		Estados.push_back(Nodos(i,false));//creo el numero de nodos que son pasados por parametros
	}

	for(int i=1;i<=NumTer;i++)
	{
		it=Estados.begin();//Inicializo el apuntador it al principio de la lista de estados
		cin>>Finales;//lee valor del estado terminal

		for(int i=1;i<Finales;i++)//mueve el apuntador it hasta el estado correspondiente
			it++;

		it->Final=true;//asigna verdad al atributo final del estado al que apunta
	}
	
	for(int i=0;i<NumRe;i++)//lee las producciones
	{
		it=Estados.begin();//coloca el apuntador it al principio de la lista de los estados
		cin>>Origen;//lee el origen
		cin>>Destino;//lee el destino
		cin>>Transicion;//lee la transicion
		cin>>TopePila;//lee lo que deberia ir en el tope de la pila para la transicion
		cin>>APila;//Lee lo que se deberia apilar si se cumple con la transicion

		for(int i=1;i<Origen;i++)//Desplaza el apuntador hasta el estado correspondiente
			it++;

		it->Adyacentes.push_back(NodosAdyacentes(Destino,Transicion,APila,TopePila));//Coloca un nodoadyacente en la lista de adyacentes del nodo
	}
	
	for(int i=1;i<=NumPruebas;i++)//lee las cadenas de prueba y las coloca en una cola de strings
	{
		cin>>Cadenas;

		Cadenas=Cadenas+"_";

		Pruebas.push(Cadenas);
	}
}

void Grafo::Apilar(stack<char> &Pila,string Palabra)
{
	if(Palabra=="_")
	{
		Pila.pop();
	}else
	{
		int i=0;

		Pila.pop();

		for(i=Palabra.size()-1;i>=0;i--)
		{
			Pila.push(Palabra[i]);

		}
	}

}



void Grafo::VerificarCadena(stack<char> P,int Estado, string Palabra,int idP)
{	
	if(idP<Palabra.size())					//Si el contador de la palabra es menor que el tamño e la palabra
	{
		stack<char> Aux = stack<char>();	//Pila auxiliar para descargar la pila pasada por parametro
		Aux=P;
		list<Nodos>::iterator it1,it3;		//iteradores a Nodos
		list<NodosAdyacentes>::iterator it2;	//Iteradores a Nodos Adyacentes
	
		it1=Estados.begin();		//Inicializacion de It1

		for(int i=1;i<Estado;i++)	//Se Coloca el iterador en el estado correspondiente
			it1++;

		it2=it1->Adyacentes.begin();	//Se inicializa el iterador e estados adyacentes

		it3=Estados.begin();			//Se incializa un iterador auxiliar

		int i=0;						//Contador
		while(i<it1->Adyacentes.size() && !Encontrado)//Mientars ele stado tega ams estados adyacentes, y no haya encontrado solucion
		{			
			if((it2->Transicion == Palabra[idP]) && (P.top() == it2->TopePila))	//Si el caracter de la palara conincide con la trnsiion del estado adyacente y el tope de la pila conincide con el topde de la pila del estado adyacente
			{			
				Apilar(P,it2->Apilar);	//Apilo algo

				for(int j=1;j<it2->Nombre;j++)	//Con el iterador auxiliar em uevo al estado al que voy
					it3++;
	
				if(it3->Final && ((idP+1)==Palabra.size()))	//Reviso si ese estaod es final y si ya he evaludado toda la cadena
				{
					if(P.top()=='Z')	//Si el tope de la pila es una Z
					{
						Encontrado=true;	//Marco ncontrado 
						break;		//Me salgo del backtracking
					}

				}else
				{
					VerificarCadena(P,it2->Nombre,Palabra,idP+1);//Recursividad
				}

				P=Aux;//Devuelvo el valor d ela pila
			}

			i++;//Aumento el contador
			it2++;//Aumento el iterador de estados adyacentes
		}
	}
}


int main()
{
	int T,N,F,M,S;
	Grafo A= Grafo();

	list<Nodos>:: iterator it1;
	list<NodosAdyacentes>:: iterator it2;

	cin>>T;

	for(int i=0;i<T;i++)
	{
		A= Grafo();
		cin>>N>>F>>M>>S;
		A.AgregarGrafo(N,F,M,S);

		for(int j=0;j<S;j++)
		{
			A.VerificarCadena(A.Pila,1,A.Pruebas.front(),0);

			if(Encontrado)
				cout<<"Y"<<endl;
			else
				cout<<"N"<<endl;

			A.Pruebas.pop();

			Encontrado=false;
		}

	}

	return 0;
}