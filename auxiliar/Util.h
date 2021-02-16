#ifndef UTIL_H
#define UTIL_H

#include "../glob.h"

class UTIL
{
private:
  double suma;
  vector<string>::iterator itv;
  set<int> procs;
  vector<string> tokens;
  vector<string> terminos;
  string vacio;
  int P;
  int proc;
public:
  UTIL(int P1)
  {
    vacio=string(" ");
    P=P1;
  }

  ~UTIL()
  {
  }
  
  char* obtener_terminos( vector<string> t);

  void Tokenize(const string&,
                vector<string>&,
                const string&);
};

#endif
