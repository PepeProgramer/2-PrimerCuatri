#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <condition_variable>
#include "HoareMonitor.hpp"

using namespace std ;
using namespace HM ;

const int numero_clientes = 10;

template< int min, int max > int aleatorio(){
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

//funcion del barbero
void pelar(){
  chrono::milliseconds duracion_pelar( aleatorio<20,200>() );

   cout << "Barbero pela en: " << duracion_pelar.count() << " segundos" << endl;

  this_thread::sleep_for( duracion_pelar );

   cout << "Barbero termina de pelar al cliente " << endl;
}

//funcion de cliente
void espera_fuera(int cliente_n ){
  chrono::milliseconds duracion_esperar( aleatorio<20,200>() );

   cout << "El cliente " << cliente_n << " espera: " << duracion_esperar.count() << " segundos)" << endl;

  this_thread::sleep_for( duracion_esperar );

   cout << "El cliente " << cliente_n << " ha terminado de esperar" << endl;

}

class Barberia : public HoareMonitor{
private:
  int cliente_actual;
  bool pelando;
  CondVar
    cliente,
    pela;
public:
  //Construtor
  Barberia();
  //Barbero metodos
  void siguienteCliente();
  void finCliente();

  //Cliente metodos
  void cortarPelo(int);
};

Barberia::Barberia(){
  pelando = false;
  cliente = newCondVar();
  pela = newCondVar();
}

void Barberia::siguienteCliente(){
  if(!pelando)
    cliente.wait();
}

void Barberia::finCliente(){
  if(pelando)
    pela.wait();
  pelando = false;
  cliente.signal();
}

void Barberia::cortarPelo(int cliente_i){
  pelando = true;
  pela.signal();
}

void funcion_hebra_barbero( MRef<Barberia> monitor ){
  while(true){
    //Paso 1
    monitor->siguienteCliente();
    //Paso 2
    pelar();
    //Paso 3
    monitor->finCliente();
  }
}

void funcion_hebra_clientes( MRef<Barberia> monitor, int num_cliente ){
  while(true){
    //Pasos 1 y 2
    monitor->cortarPelo(num_cliente);
    //Paso 3
    espera_fuera(num_cliente);
  }
}

int main(int argc, char const *argv[]) {
  MRef<Barberia> monitor = Create<Barberia>() ;

  thread hebra_barbero ( funcion_hebra_barbero, monitor );
  thread hebras_clientes[numero_clientes]; //con numero_clientes declarada arriba  = 10;
  for(unsigned i = 0; i < numero_clientes; i++){
    hebras_clientes[i] = thread( funcion_hebra_clientes, monitor, i);
  }

  hebra_barbero.join() ;
  for( unsigned i = 0 ; i < numero_clientes ; i++ ){
           hebras_clientes[i].join() ;
  }
  return 0;
}
