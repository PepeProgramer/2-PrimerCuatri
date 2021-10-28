#include <iostream>
#include <cassert>
#include <iomanip>
#include <mutex>
#include <vector>
#include <thread>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "HoareMonitor.hpp"

using namespace std;
using namespace HM;

//-----------------------------------
// Variables compartidas

mutex mutex_cout;

class Barberia : public HoareMonitor{
	private:
		CondVar barbero, silla;
		CondVar sala;
		bool sentado;
	public:
		Barberia();
		void cortarPelo(int i);
		void siguienteCliente();
		void finCliente();
};

Barberia::Barberia(){
	barbero = newCondVar();
	silla = newCondVar();
	sala = newCondVar();
	sentado = false;
}

void Barberia::siguienteCliente(){

	if( sala.empty() && silla.empty() ){
		cout << "Barbero duerme" << endl;
		barbero.wait();
	}else{
		cout << " --> Barbero llama al siguiente cliente " << endl;
		sala.signal();
	}

}

void Barberia::finCliente(){

	cout << "Barbero termina de pelar al cliente" << endl;
	silla.signal();
}

void Barberia::cortarPelo(int i){

	if( !barbero.empty() ){
		cout << "El cliente " << i << " despierta al barbero" << endl;

		if( sentado == false ){
			cout << "Cliente " << i << " se sienta en la silla" << endl;
		}
		barbero.signal();

	}else if( !silla.empty() || !sala.empty() ){
		sala.wait();
	}

	if( sentado == true ){
		cout << "Cliente " << i << " se sienta en la silla" << endl;
	}

	sentado = true;
	silla.wait();
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
// función que corta el pelo al cliente con espera
void cortarPeloCliente(){
	chrono::milliseconds pelar( 5000 );
	mutex_cout.lock();
	cout << "Empieza a cortar el pelo (" << pelar.count() << ")" << endl;
	mutex_cout.unlock();
	this_thread::sleep_for( pelar );
}

//----------------------------------------------------------------------
// función que espera fuera de la barberia
void esperarFueraBarberia(int num_cliente){
	chrono::milliseconds espera( aleatorio<20,200>() );
	mutex_cout.lock();
	cout << "El cliente " << num_cliente << " espera fuera (" << espera.count() << ")" << endl;
	mutex_cout.unlock();
	this_thread::sleep_for( espera );
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_barbero( MRef<Barberia> monitor ){
   while( true ){
		 monitor->siguienteCliente();
		 cortarPeloCliente();
		 monitor->finCliente();
   }
}

void  funcion_hebra_cliente( MRef<Barberia> monitor, int num_cliente ){
   while( true ){
		 monitor->cortarPelo(num_cliente);
		 esperarFueraBarberia(num_cliente);
   }
}

//----------------------------------------------------------------------

int main(){
	int num_clientes = 8;
	MRef<Barberia> monitor = Create<Barberia>();

	thread hebra_barbero(funcion_hebra_barbero,monitor);
	thread hebras_clientes [num_clientes];

	for(int i = 0; i < num_clientes; i++){
		hebras_clientes[i] = thread(funcion_hebra_cliente,monitor, i);
	}

	hebra_barbero.join();
	for(int i = 0; i < num_clientes; i++){
		hebras_clientes[i].join();

	}
    return 0;
}
