#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;

//**********************************************************************
// variables compartidas
const int num_items = 40,   // número de items
	       tam_vec   = 10;   // tamaño del buffer
//bufer
unsigned int vec[tam_vec] = {0};

unsigned  cont_prod[num_items] = {0}, // contadores de verificación: producidos
          cont_cons[num_items] = {0}; // cont}adores de verificación: consumidos

unsigned int primera_libre = 0; //administracion del espacio vec, mediante tecnica LIFO

Semaphore libres = tam_vec; //numero de entrada libres(tam_vec + #L - #E)
Semaphore ocupadas = 0; //numero de entradas ocupadas(#E-#L)
Semaphore exclusion = 1; //EN LIFO HAY QUE GARANTIZAR LA EM

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

//******************Antes****************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

int producir_dato(){
   static int contador = 0;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "producido: " << contador << endl << flush ;

   cont_prod[contador] ++ ;
   return contador++ ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato ){
   assert( dato < num_items ); //sale del programa si no cumple esta condicion
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl ;

}


//----------------------------------------------------------------------

void test_contadores(){
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------

void  funcion_hebra_productora(  ){
   for( unsigned i = 0 ; i < num_items ; i++ )
	 {
      int dato = producir_dato() ;
			sem_wait( libres );
			sem_wait(exclusion);
			vec[primera_libre] = dato;
			primera_libre++;
			cout << "Escrito en buffer: " << vec[primera_libre-1] << endl;
			sem_signal(exclusion);
			sem_signal( ocupadas );
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
		  sem_wait( ocupadas );
			sem_wait( exclusion );
      int b = vec[primera_libre-1];
			primera_libre--;
			cout << "                     leido en buffer: " << b << endl;
			sem_signal( exclusion );
    	sem_signal (libres );
      consumir_dato( b ) ;
    }
}
//----------------------------------------------------------------------

int main()
{
   cout << "--------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución LIFO)." << endl
        << "--------------------------------------------------------" << endl
        << flush ;

   thread hebra_productora ( funcion_hebra_productora ),
          hebra_consumidora( funcion_hebra_consumidora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;

   test_contadores();
	 cout << "\nfin" << endl;
}
