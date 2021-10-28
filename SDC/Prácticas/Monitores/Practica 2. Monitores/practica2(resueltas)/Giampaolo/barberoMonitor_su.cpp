//BarberoMonitorSU

#include <iostream>
#include <iomanip>
#include <random>
#include "HoareMonitor.hpp"

using namespace std ;
using namespace HM ;

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

int numClientes=3;
mutex mtx;

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}


void CortarPeloACliente(  )
{
   mtx.lock();

   chrono::milliseconds espera_corte( aleatorio<20,200>() );

   cout << " espera cortar (" << espera_corte.count() << " milisegundos)" << endl;

   this_thread::sleep_for( espera_corte );

   mtx.unlock();
}

void EsperaFueraBarberia(int num_cliente )
{
   mtx.lock();

   chrono::milliseconds espera_fuera( aleatorio<20,200>() );

   cout << "El cliente " << num_cliente;
   cout  << " espera fuera (" << espera_fuera.count() << " milisegundos)" << endl;

   this_thread::sleep_for( espera_fuera );

   mtx.unlock();
}


class Barberia : public HoareMonitor
{
   private:
      bool barbiereAddormentato;
      CondVar addormentato, sala, fineTaglio;
   public:
      Barberia();
      void cortarPelo();
      void siguienteCliente();
      void finCliente();
} ;
// -----------------------------------------------------------------------------

Barberia::Barberia(){
   barbiereAddormentato=true;
   addormentato = newCondVar();
   sala = newCondVar();
   fineTaglio = newCondVar();
}

void Barberia::cortarPelo(){
   if(barbiereAddormentato == true){
      cout <<"El barbero esta despierto"<<endl;
      addormentato.signal();
   }
   sala.wait();
   fineTaglio.wait();
   cout <<"sala e finetaglio vann"<<endl;
 }

void Barberia::siguienteCliente(){
   if(sala.empty()){
      cout << "El barbero se duerme" << endl;
      barbiereAddormentato = true;
      addormentato.wait();

      barbiereAddormentato=false;
      cout<<"Barbero se ha despertado"<<endl;
   }
   cout<<"Barbero comienza a cortar el cabello"<<endl;


 }

void Barberia::finCliente(){
   cout<<"El barbero ha terminado de pelar al cliente"<<endl;
   sala.signal();
   fineTaglio.signal();
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

void funzioneCliente( MRef<Barberia> monitor, int i)
{
   while( true ){
      monitor->cortarPelo();
      EsperaFueraBarberia(i);
   }

}

void funzioneBarbiere(MRef<Barberia> monitor){
   while(true){
      monitor->siguienteCliente();
      CortarPeloACliente();
      monitor->finCliente();
   }
}


// *****************************************************************************

int main()
{

   int numClienti=3;

   MRef<Barberia> monitor = Create<Barberia>();

   thread processo_barbiere;
   processo_barbiere = thread( funzioneBarbiere, monitor);

   thread processo_cliente[numClienti];
   for( unsigned i = 0 ; i < numClienti ; i++ )
      processo_cliente[i] = thread( funzioneCliente, monitor, i);

   for( unsigned i = 0 ; i < numClienti ; i++ )
      processo_cliente[i].join();
}
