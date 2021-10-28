#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <condition_variable>
#include "HoareMonitor.hpp.hpp"

using namespace std ;
using namespace HM ;

const int TAM = 3;

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

//Funcion que simula fumar con un retardo
void Fumar(int num_fumador ){
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   this_thread::sleep_for( duracion_fumar );

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
}

int ProducirIngrediente(){
  chrono::milliseconds duracion_producir( aleatorio<20,200>() );
  this_thread::sleep_for( duracion_producir );

  int ingre = aleatorio<0,2>();
  cout << "Ingrediente " << ingre << " producido" << endl;

  return ingre;
}

class Estanco : public HoareMonitor{
private:
  int ingrediente_actual;
  CondVar         // colas condicion:
    vacio,
    ingrediente;
public:
  Estanco();
  void ObtenerIngrediente(int);
  void ponerIngrediente(int);
  void esperarRecogidaIngrediente();
};

Estanco::Estanco(){
  ingrediente_actual = -1;
  vacio = newCondVar();
  ingrediente = newCondVar();
}

void Estanco::ObtenerIngrediente(int i){
  while( ingrediente_actual != -1){
    cout << "Fumador " << ingrediente_actual << " retira su ingrediente" << endl;
    ingrediente_actual = -1;
  }
  vacio.signal();
}

void Estanco::ponerIngrediente(int i){
  while(ingrediente_actual == -1)
    vacio.wait();
  ingrediente_actual = i;
  cout << "Ingrediente " << ingrediente_actual << " puesto en el mostrador" << endl;
  ingrediente.signal();
}

void Estanco::esperarRecogidaIngrediente(){
  ingrediente.wait();
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero
void funcion_hebra_estanquero( MRef<Estanco> monitor ){
  while(true){
    int ingrediente = ProducirIngrediente();
    monitor->ponerIngrediente(ingrediente);}
    monitor->esperarRecogidaIngrediente();
  }
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( MRef<Estanco> monitor, int num_fumador ){
   while( true ){
     monitor->ObtenerIngrediente(num_fumador);
     Fumar(num_fumador);
   }
}

//----------------------------------------------------------------------

int main(){
  MRef<Estanco> monitor = Create<Estanco>() ;

  thread hebra_estanquero ( funcion_hebra_estanquero, monitor );
  thread hebras_fumadores[TAM]; //  TAM = 3
  for(unsigned i = 0; i < TAM; i++){
    hebras_fumadores[i] = thread( funcion_hebra_fumador, monitor, i );
  }

  hebra_estanquero.join() ;
  for( unsigned i = 0 ; i < TAM ; i++ ){
           hebras_fumadores[i].join() ;
  }

}
