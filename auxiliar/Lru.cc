#include "Util.h"
#include "Lru.h"

bool LRU::hit( string key )
{
  if( cache.empty( ) )
    return false;

  if( cache.count( key ) == 0 )
    return false;
  else
    return true;
}

//---------------------------------------------------
void LRU::insert( string key, int tam )
{
  if ( cache.count( key )!= 0 )
   {
      update( key );   
      return;  
   } 
  //verificar que no este
  ASSERT( cache.count( key ) == 0 );

  if( !this->queda_espacio( tam ) )
  {
    this->generar_espacio( tam );
  }

  //poner en cache nuevo nodo
  ptr = new Nodo( TS, key, tam );
  cola_prioridad.push( ptr );
  
  libre -= tam;

  //enlazar
  cache[key] = ptr;

  //aumentar timestamp
  TS++;
}

//---------------------------------------------------

void LRU::update( string key )
{
  //marcar la entrada
  cache[key]->marca = false;
  int tam = cache[key]->tam;

  //agregar una nueva
  ptr = new Nodo( TS , key, tam );
  cola_prioridad.push( ptr );

  //datos
  cache[key] = ptr;

  //aumentar timestamp
  TS++;
}

//---------------------------------------------------

bool LRU::queda_espacio( int tam )
{
  if( libre >= tam )
    return true;
  return false;
}

//---------------------------------------------------

void LRU::generar_espacio( int tam )
{
  do
  {
    ptr = cola_prioridad.top( );
    while( ptr->marca == false )
    {
      cola_prioridad.pop( );
      delete ptr;
      ptr = cola_prioridad.top( );
    }
    cola_prioridad.pop( );
 
    libre += ptr->tam;
  
    cache.erase( ptr->key );
 
    delete ptr;
  }while ( libre < tam );
}

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

