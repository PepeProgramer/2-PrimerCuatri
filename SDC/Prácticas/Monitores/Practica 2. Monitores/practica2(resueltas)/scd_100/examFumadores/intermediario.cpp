#include <iostream>
#include <cassert>
#include <iomanip>
#include <thread>
#include <mutex>
#include <vector>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "HoareMonitor.hpp"

using namespace std;
using namespace HM;

//-----------------------------------
// Variables compartidas
class Estanco : public HoareMonitor
{
	private:
		int mostrador, vitrina;/*EXAMEN*/
		int producido10, producido11, producido12, consumido10, consumido11, consumido12;/*EXAMEN*/
		CondVar cola_mostrador, intermediario, cola_vitrina;/*EXAMEN*/
		CondVar cola_fumador [3];
	public:
		void obtenerIngrediente(int i);
		void ponerIngrediente(int i);
		void esperarRecogidaIngredienteMostrador();/*EXAMEN*/
		void obternerIngredientePonerVitrina();/*EXAMEN*/
		void esperarRecogidaIngredienteVitrina();/*EXAMEN*/
		Estanco();
};

Estanco::Estanco(){
	cola_mostrador=newCondVar();/*EXAMEN*/
	intermediario=newCondVar();/*EXAMEN*/
	cola_vitrina=newCondVar();/*EXAMEN*/
	cola_fumador[0]=newCondVar();
	cola_fumador[1]=newCondVar();
	cola_fumador[2]=newCondVar();
	mostrador=-1;
	vitrina=-1;/*EXAMEN*/
	producido10=0;/*EXAMEN*/
	producido11=0;/*EXAMEN*/
	producido12=0;/*EXAMEN*/
	consumido10=0;/*EXAMEN*/
	consumido11=0;/*EXAMEN*/
	consumido12=0;/*EXAMEN*/
}

void Estanco::obtenerIngrediente(int i){

	if( vitrina != i )/*EXAMEN*/
		cola_fumador[i].wait();

	if( vitrina == 0 )/*EXAMEN*/
		consumido10++;/*EXAMEN*/
	else if( vitrina == 1 )/*EXAMEN*/
		consumido11++;/*EXAMEN*/
	else/*EXAMEN*/
		consumido12++;/*EXAMEN*/
		

	cout << ":Fumador " << i << " Retira el ingrediente de la vitrina" << endl;
	vitrina = -1;/*EXAMEN*/
	cola_vitrina.signal();/*EXAMEN*/
}

void Estanco::ponerIngrediente(int i){
		
	cout << "::: Ingrediente " << i << " puesto en mostrador y espera" << endl;
	mostrador=i;

	if( i == 10 )/*EXAMEN*/
		producido10++;/*EXAMEN*/
	else if( i == 11 )/*EXAMEN*/
		producido11++;/*EXAMEN*/
	else/*EXAMEN*/
		producido12++;/*EXAMEN*/

	cout << "--- Materiales ---" << endl;/*EXAMEN*/
	cout << " Elemento ... Consumidos ... Producidos " << endl;/*EXAMEN*/
	cout << " 0 ... " << consumido10 << " ... " << producido10 << endl;/*EXAMEN*/
	cout << " 1 ... " << consumido11 << " ... " << producido11 << endl;/*EXAMEN*/
	cout << " 2 ... " << consumido12 << " ... " << producido12 << endl;/*EXAMEN*/

	intermediario.signal();/*EXAMEN*/
}

void Estanco::esperarRecogidaIngredienteMostrador(){

	if( mostrador > -1 )
		cola_mostrador.wait();
}

void Estanco::obternerIngredientePonerVitrina(){/*EXAMEN*/
	
	int elemento;/*EXAMEN*/

	if( mostrador == -1 )/*EXAMEN*/
		intermediario.wait();/*EXAMEN*/

	vitrina = mostrador - 10;/*EXAMEN*/
	mostrador = -1;/*EXAMEN*/
	cout << "::Intermediario transforma el elemento " << (vitrina+10) << " en el emento " << vitrina <<" y lo pone en la vitrina" << endl;/*EXAMEN*/
	cola_mostrador.signal();/*EXAMEN*/

}

void Estanco::esperarRecogidaIngredienteVitrina(){/*EXAMEN*/

	cola_fumador[vitrina].signal();/*EXAMEN*/

	if( vitrina > -1 )/*EXAMEN*/
		cola_vitrina.wait();/*EXAMEN*/
}

//-----------------------------------

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

//----------------------------------------------------------------------
// función productora de ingredientes
int produceIngrediente(){
	chrono::milliseconds duracion_fabricar( aleatorio<20,200>() );
	this_thread::sleep_for( duracion_fabricar );
  	return aleatorio<10,12>();
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero( MRef<Estanco> monitor )
{
	int ingrediente;
	while( true ){
		ingrediente = produceIngrediente();
		monitor->ponerIngrediente(ingrediente);
		monitor->esperarRecogidaIngredienteMostrador();
	}
}

//----------------------------------------------------------------------
// función que ejecuta la hebra intermediario

void funcion_hebra_intermediario( MRef<Estanco> monitor )/*EXAMEN*/
{

	while( true ){/*EXAMEN*/
		monitor->obternerIngredientePonerVitrina();/*EXAMEN*/
		monitor->esperarRecogidaIngredienteVitrina();/*EXAMEN*/
	}
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar( int num_fumador )
{
	int val;
	if( num_fumador == 0 )
		val = 2000;
	if( num_fumador == 1 )
		val = 3000;
	if( num_fumador == 2 )
		val = 5000;

   	// calcular milisegundos aleatorios de duración de la acción de fumar)
   	chrono::milliseconds duracion_fumar( val );


	cout << "Fumador " << num_fumador << "  :" << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

  	 // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   	this_thread::sleep_for( duracion_fumar );
   
    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( MRef<Estanco> monitor, int num_fumador )
{
   while( true )
   {
	monitor->obtenerIngrediente(num_fumador);
	fumar(num_fumador);
   }
}

//----------------------------------------------------------------------

int main()
{
	
	MRef<Estanco> monitor = Create<Estanco>();
	
	
  thread hebra_estanquero(funcion_hebra_estanquero,monitor),
	 hebra_intermerdiario(funcion_hebra_intermediario,monitor),/*EXAMEN*/
         hebra_f0 (funcion_hebra_fumador,monitor,0),
         hebra_f1 (funcion_hebra_fumador,monitor,1),
         hebra_f2 (funcion_hebra_fumador,monitor,2);

  hebra_estanquero.join();
  hebra_intermerdiario.join();/*EXAMEN*/
  hebra_f0.join();
  hebra_f1.join();
  hebra_f2.join();
  
  return 0;
}
