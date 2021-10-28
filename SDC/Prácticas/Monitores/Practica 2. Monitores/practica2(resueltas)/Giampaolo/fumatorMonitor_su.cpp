#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iomanip>
#include "HoareMonitor.hpp"


using namespace std ;
using namespace HM ;

int numFumadores=3;
int numero=0;

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

mutex mtx;


class Estanquero : public HoareMonitor
{

   private:
      int ingrediente;

      bool ingredienteNelTavolo, finitoFumare;

      mutex mioMutex;

      CondVar produci, fuma[3];

  public:
    Estanquero();
    int obtenerIngrediente(int i);
    void ponerIngrediente(int ingr);
    void esperarRecogidaIngrediente();
};

Estanquero::Estanquero(){
   ingrediente=0;
   ingredienteNelTavolo=false, finitoFumare=false;

   produci = newCondVar();
   fuma[0] = newCondVar();
   fuma[1] = newCondVar();
   fuma[2] = newCondVar();

}


int Estanquero::obtenerIngrediente(int i){
   if(finitoFumare == true){
      produci.signal();
   }

   if(ingredienteNelTavolo == false){
      fuma[i].wait();
   }
   int ingr = ingrediente;
   ingredienteNelTavolo=false;
   return ingr;
}

void Estanquero::ponerIngrediente(int ingr){
   if(ingredienteNelTavolo == true){
      produci.wait();
   }
      ingrediente = ingr;
      ingredienteNelTavolo = true;
      fuma[ingr].signal();

}

void Estanquero::esperarRecogidaIngrediente(){
   finitoFumare=true;
   produci.wait();
   finitoFumare=false;
}

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

void fumar( int num_fumador ){

   mtx.lock();

   chrono::milliseconds duracion_fumar( aleatorio<200,500>() );


    cout << "Fumador " << num_fumador << "  :"
         << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;


    mtx.unlock();
}

int ProducirIngrediente(){
  int ingrediente;
  mtx.lock();
  ingrediente = aleatorio<0,2>();
  mtx.unlock();
  return ingrediente;
}


//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador


void funzione_processo_estanquero( MRef<Estanquero> monitor )
{
while(true){
   int ingr = ProducirIngrediente();
   monitor->ponerIngrediente( ingr );
   monitor->esperarRecogidaIngrediente();
   }
}

void  funzione_processo_fumador( MRef<Estanquero> monitor, int i )
{
  while(true){
    int ingrediente = monitor->obtenerIngrediente(i);
    fumar(ingrediente);
  }
}


//----------------------------------------------------------------------


int main()
{

   MRef<Estanquero> monitor = Create<Estanquero>();

   thread processo_estanquero;
   thread processo_fumador[numFumadores];

   processo_estanquero = thread( funzione_processo_estanquero, monitor);

   for(int i=0; i<numFumadores; i++){
      processo_fumador[i] = thread(funzione_processo_fumador, monitor, i);
   }

   for(int i=0; i<numFumadores; i++){
      processo_fumador[i].join();
   }

   processo_estanquero.join();

   return 0;

}
