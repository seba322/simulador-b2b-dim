/* Implementa cache con politica LRU. */

#ifndef LRU_H
#define LRU_H

#include "../glob.h"

class UTIL;

class LRU
{
private:
  UTIL *util;

  //--cache misma
  map<string/*key*/,Nodo* /*ptr*/> cache;
  int *NC;
  int libre; 

  priority_queue< Nodo*, vector<Nodo*>, Compara > cola_prioridad;
  int TS;

  //--parametros
  int *P;

  //--temporales
  Nodo *ptr;
  unsigned int prio;
  vector<string> v;
  vector<string>::iterator itv;

public:
  LRU( int *_nc,
       UTIL *_util,
       int *_p )
  {
    NC   = _nc;
    P    = _p;
    util = _util;
    TS   = 0;
    libre = *_nc;
  }

  ~LRU( )
  {
    cache.clear( );
    //limpiar cola
  }
  
  //Retorna la cantidad de entradas disponibles en la cache
  int getNC()
  {
    return *NC;
  }
  bool hit( string/*key*/ );
  void insert( string/*key*/, int/*tam*/ );
  void update( string/*key*/ );
  bool queda_espacio( int/*tam*/ );
  void generar_espacio( int/*tam*/ );
  void getSize( )
  {
    cout << "cache.size()=" << cache.size( ) << endl;
  }
};


//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------


#endif
