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

const int NUM_FUMADORES = 3;

//-----------------------------------
// Variables compartidas
class Estanco : public HoareMonitor{
	private:
		int mostrador;
		CondVar cola_mostrador;
		CondVar cola_fumador [NUM_FUMADORES];
	public:
		void obtenerIngrediente(int i);
		void ponerIngrediente(int i);
		void esperarRecogidaIngrediente();
		Estanco();
};

Estanco::Estanco(){
	cola_mostrador=newCondVar();
	for(int i = 0; i < NUM_FUMADORES; i++){
		cola_fumador[i] = newCondVar();
	}
	mostrador= -1;
}

void Estanco::obtenerIngrediente(int i){

	if( mostrador != i )
		cola_fumador[i].wait();

	cout << ":Fumador " << i << " Retira el ingrediente del mostrador" << endl;
	mostrador = -1;
	cola_mostrador.signal();
}

void Estanco::ponerIngrediente(int i){

	cout << "::: Ingrediente " << i << " puesto en mostrador y espera" << endl;
	mostrador = i;
	cola_fumador[i].signal();
}

void Estanco::esperarRecogidaIngrediente(){

	if( mostrador > -1 )
		cola_mostrador.wait();
}

//-----------------------------------

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio(){
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

//----------------------------------------------------------------------
// función productora de ingredientes
int produceIngrediente(){
	chrono::milliseconds duracion_fabricar( aleatorio<20,200>() );
	this_thread::sleep_for( duracion_fabricar );
  return aleatorio<0,2>();
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero( MRef<Estanco> monitor ){
	int ingrediente;
	while( true ){
		ingrediente = produceIngrediente();
		monitor->ponerIngrediente(ingrediente);
		monitor->esperarRecogidaIngrediente();
	}
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar( int num_fumador ){
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
void  funcion_hebra_fumador( MRef<Estanco> monitor, int num_fumador ){
   while( true ){
		 monitor->obtenerIngrediente(num_fumador);
		 fumar(num_fumador);
   }
}

//----------------------------------------------------------------------

int main(){
	MRef<Estanco> monitor = Create<Estanco>();

  thread hebra_estanquero(funcion_hebra_estanquero,monitor);
	thread hebras_fumador[NUM_FUMADORES];

	for(int i = 0;  i < NUM_FUMADORES; i++){
		hebras_fumador[i] = thread(funcion_hebra_fumador, monitor, i);
	}

  hebra_estanquero.join();

	for(int i = 0;  i < NUM_FUMADORES; i++){
		hebras_fumador[i].join();
	}

  return 0;
}
