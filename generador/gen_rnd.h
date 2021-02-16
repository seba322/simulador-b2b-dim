#ifndef GEN_H
#define GEN_H

#include "../glob.h"
#include "../auxiliar/Util.h"
#include "../Consumidor/Consumidor.h"

class Procesador;

class Gen_rnd : public process
{

  vector<string> tokens;
  list<string> historialVentas;
  map<string, handle<Consumidor> > consumidores;
  int tipoRecomendacion;

  UTIL *util;
  char archivo_trazas[2048];
  ifstream fin;
  double CTE;
  double *T_ini;

protected:
  void inner_body(void);

public:
  Gen_rnd(const string &name, char *_archivo_trazas, map<string, handle<Consumidor> > _consumidores, UTIL *_util,int _tipoRecomendacion) : process(name)
  {

    util = _util;
    consumidores = _consumidores;
    strcpy(archivo_trazas, _archivo_trazas);
    tipoRecomendacion= _tipoRecomendacion;
  }
};
#endif
