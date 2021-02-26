/**/

#include "auxiliar/Util.h"
#include "glob.h"
#include "generador/gen_rnd.h"

class sistema : public process
{
private:
  double simLen;
  char nombre[128];

  UTIL *util;

  // //Numero de Nodos
  // int nodos;

  // //Consultas
  // int TQ, enviadas, TotalC;

  //Comandos a ejecutar (DAG)
  char archivo_ventas[2048];
  char archivo_productos[2048];
  char archivo_clientes[2048];
  char salida_clientes[2048];
  char salida_productos[2048];
  char salida_ventas[2048];
  char archivo_segmentos[2048];
  char archivo_rubros[2048];
  int tipoRec;
  char salida_recomendacion[2048];
  // //Queries

  //Generador de tasa dellegada
  handle<Gen_rnd> generador;

  //Estadisticas
  int TC;

public:
  sistema(const string &_name,
          double _sl,
          char *_archivo_ventas,
          char *_archivo_productos,
          char *_archivo_clientes,
          char *_salida_clientes,
          char *_salida_productos,
          char *_salida_ventas,
          char *_archivo_segmentos,
          char *_archivo_rubros,
          int _tipoRec,
          char *_salida_recomendacion) : process(_name)
  {
    simLen = _sl;

    strcpy(archivo_ventas, _archivo_ventas);
    strcpy(archivo_productos, _archivo_productos);
    strcpy(archivo_clientes, _archivo_clientes);
    strcpy(salida_clientes, _salida_clientes);
    strcpy(salida_productos, _salida_productos);
    strcpy(salida_ventas, _salida_ventas);
    strcpy(archivo_segmentos, _archivo_segmentos);
    strcpy(archivo_rubros, _archivo_rubros);
    tipoRec = _tipoRec;
    strcpy(salida_recomendacion, _salida_recomendacion);
  }

public:
protected:
  void inner_body(void);
};

/***************************************************************/
/***************************************************************/

void sistema::inner_body(void)
{

  //funciones de soporte
  remove("ventas.dat");
  util = new UTIL(0);
  cout << "5.1 " << endl;
  map<string, handle<Consumidor>> consumidores;
  ifstream fin;
  string linea;
  vector<string> tokens;
  cout << "5.2 " << endl;
  map<string, Producto *> productos;

  // crear estructura de productos de archivo de productos
  // fin.open("./DATA/products_sm_final.csv");
  fin.open(archivo_productos);

  if (!fin)
  { // file couldn't be opened
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  while (getline(fin, linea))
  {
    // cout << "Linea " << linea << endl;
    tokens.clear();
    util->Tokenize(linea, tokens, ",");

    string idProducto = tokens[0].c_str();

    string jerarquia = tokens[1].c_str();

    int cantidadProductos = atoi(tokens[2].c_str());

    double puntaje = atof(tokens[3].c_str());
    int precio = atoi(tokens[4].c_str());

    Producto *p = new Producto(idProducto, jerarquia, cantidadProductos, puntaje, precio);

    auto el = pair<string, Producto *>(idProducto, p);
    productos.insert(el);
  }
  fin.close();

  // Segmentos
  map<string, map<string, Producto *>> segmentos;

  // crear estructura de productos de archivo de productos
  fin.open(archivo_segmentos);

  if (!fin)
  { // file couldn't be opened
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  while (getline(fin, linea))
  {
    // cout << "LineaS: " << linea << endl;
    tokens.clear();
    util->Tokenize(linea, tokens, " ");
    string idSegmento = tokens[0].c_str();
    cout << " Agregando Segmento: " + idSegmento << endl;
    vector<string>::iterator it = tokens.begin();
    map<string, Producto *> currentProduct;

    for (it++; it != tokens.end(); it++)
    {
      auto currentProd = *it;
      vector<string> productVector;
      util->Tokenize(currentProd, productVector, ",");
      double puntaje = atof(productVector[2].c_str());
      // cout << productVector[0].c_str() << endl;
      Producto *p = new Producto(productVector[0].c_str(), productVector[2].c_str(), puntaje, 0, 0);
      auto el = pair<string, Producto *>(productVector[0].c_str(), p);

      currentProduct.insert(el);
    }

    auto elProd = pair<string, map<string, Producto *>>(idSegmento, currentProduct);
    segmentos.insert(elProd);
  }
  fin.close();

  //rubros

  map<string, map<string, Producto *>> rubros;

  // crear estructura de productos de archivo de productos
  fin.open(archivo_rubros);

  if (!fin)
  { // file couldn't be opened
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  while (getline(fin, linea))
  {
    // cout << "LineaR: " << linea << endl;
    tokens.clear();
    util->Tokenize(linea, tokens, " ");
    string idRubro = tokens[0].c_str();
    cout << " Agregando Rubro: " + idRubro << endl;
    vector<string>::iterator it = tokens.begin();
    map<string, Producto *> currentProduct;

    for (it++; it != tokens.end(); it++)
    {
      auto currentProd = *it;
      vector<string> productVector;
      util->Tokenize(currentProd, productVector, ",");
      double puntaje = atof(productVector[1].c_str());
      //  cout << "Comienza SIMULACION: "+ productVector[2] << endl;
      Producto *p = new Producto(productVector[0].c_str(), productVector[2].c_str(), puntaje, 0, 0);
      p->GetJerarquia();
      auto el = pair<string, Producto *>(productVector[0].c_str(), p);
      // cout << el.second->GetJerarquia() + el.first   << endl;
      currentProduct.insert(el);
    }

    auto elProd = pair<string, map<string, Producto *>>(idRubro, currentProduct);
    rubros.insert(elProd);
  }
  fin.close();

  // crear estructura de clientes de estructura de clientes
  cout << "5.3 " << endl;
  // fin.open("./DATA/clients_sm_final.csv");
  fin.open(archivo_clientes);
  while (getline(fin, linea))
  {
    tokens.clear();
    util->Tokenize(linea, tokens, ",");
    string idCliente = tokens[0].c_str();
    string idSegmento = tokens[1].c_str();
    string idRubro = tokens[2].c_str();

    // se lee estructura de prodctos por segmento y rubro de ese cliente
    // cout << "Buscnado Segmento: " + idSegmento << endl;
    map<string, Producto *>::iterator itr;
    map<string, Producto *> prodSegmentos = segmentos.find(idSegmento)->second;
    // cout << "5.3.1 " + idSegmento<< endl;
    // for (itr = prodSegmentos.begin(); itr != prodSegmentos.end(); itr++)
    // {
    //   cout << "P: " + itr->first + " " + itr->second->GetId() << endl;
    // }
    // auto ell = prodSegmentos.begin()->second;
    // cout << "Buscnado Rubro: " + idRubro << endl;
    map<string, Producto *> prodRubro = rubros.find(idRubro)->second;
    // cout << "5.3.2 " << endl;
    handle<Consumidor> c = new Consumidor("CLIENTE_" + idCliente, idCliente, idSegmento, idRubro, &productos, prodSegmentos, prodRubro, salida_ventas, salida_recomendacion);
    auto el = pair<string, handle<Consumidor>>(idCliente, c);
    // cout << "Insertando:  " + (*el.second)->getIdCliente() +"inicio "+ (*consumidores.begin()->second)->getIdCliente()+ " tamaño: "+to_string(consumidores.size()) << endl;
    // (*el.second)->getIdCliente();

    consumidores.insert(el);
    c->activate();
  }

  fin.close();
  // exit(1);
  cout << "5.4 " << endl;
  /*Generador de consutas*/
  //Se define tipo de recomendador
  int tipoRecomendacion = tipoRec;
  generador = new Gen_rnd("GENERADOR", archivo_ventas, consumidores, util, tipoRecomendacion);
  cout << "5.5 " << endl;
  generador->activate();
  cout << "5.6 " << endl;
  /*Nodos*/
  /******************************* Procesadores ************************************/
  /*El primer nodo es el Broker*/

  //-----------------------------------------------------------
  cout << "Comienza SIMULACION " << endl; //fflush(stdout);
  //-----------------------------------------------------------
  //-----------------------------------------------------------
  hold(simLen); // Se detiene hasta que se cumpla el tiempo de simulacion
  //-----------------------------------------------------------
  cout << "FINZALIDA " << endl;
  fflush(stdout);
  // cout << "escribiendo ventas" << endl;
  // //-----------------------------------------------------------
  // /******************************* ESTADISTICAS ****************************/
  // cout << "escribiendo ventas" << endl;
  ofstream outdata;
  // cout << "escribiendo ventas" << endl;
  // outdata.open("productos.dat");
  outdata.open(salida_productos);
  if (!outdata)
  { // file couldn't be opened
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  // cout << "escribiendo ventas 1 " << endl;
  // map<string, handle<Consumidor> *>::iterator itr;
  // cout << "escribiendo ventas" << endl;
  int totalCompras = 0;
  int nProd = 0;
  map<string, Producto *>::iterator itr;
  for (itr = productos.begin(); itr != productos.end(); itr++)
  {
    auto p = itr->second;
    string linea = p->GetId() + "," + p->GetJerarquia() + "," + to_string(p->GetStock()) + "," + to_string(p->GetVentas())+","+to_string(p->GetReposicion());
    totalCompras += p->GetVentas();
    nProd += 1;
    outdata << linea << endl;
  }
  // cout << "total de ventas: " + to_string(totalCompras) + " " + to_string(nProd) << endl;
  outdata.close();

  // // cout << "escribiendo ventas" << endl;
  ofstream outdataClient;
  // // cout << "escribiendo ventas" << endl;
  // outdataClient.open("consumidor.dat");
  outdataClient.open(salida_clientes);
  if (!outdataClient)
  { // file couldn't be opened
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  // // cout << "escribiendo ventas 1 " << endl;
  // // map<string, handle<Consumidor> *>::iterator itr;
  // // cout << "escribiendo ventas" << endl;
  // auto itr;

  for (auto itr = consumidores.begin(); itr != consumidores.end(); itr++)
  {
    auto c = itr->second;
    string linea = itr->first + "," + to_string((itr->second)->GetNCompras()) + "," + to_string((itr->second)->GetVentasFallidas());

    outdataClient << linea << endl;
  }
  outdataClient.close();

  // //   cout << "escribiendo ventas2 " << endl;
  // //   auto c = itr->second;
  // //   cout << "escribiendo ventas2,1 " << (*c)->getIdCliente() << (*c)->getNCompras() << endl;
  // //   outdata << (*c)->getVentasRealizadas() << endl;
  //   // std::list<Venta *> ventas;
  //   // (*c)->printel();
  //   //    auto ventas = (*c)->getVentasRealizadas();
  //   //   cout << "escribiendo ventas2,2 " << endl;
  //   //  vector<string>::iterator it;
  //   //   cout << "escribiendo ventas3" << endl;
  //   //   for (it = ventas.begin(); it !=  ventas.end(); ++it)
  //   //   {
  //   //     auto v = (*it);
  //   //     // map<string, int>::iterator itrv;
  //   //     // string linea = (*it)->id_compra + " " + (*it)->id_cliente + " " + (*it)->fecha + " " + to_string((*it)->cantidadProductos) + " ";
  //   //     // for (itrv = v.begin(); itrv != v.end(); itrv++)
  //   //     // {
  //   //     //   linea += itrv->first + " ";
  //   //     //   linea += to_string(itrv->second) + " ";
  //   //     // }
  //   //     // linea += "\n";
  //   //     outdata << v << endl;
  //   //   }
  // }
  // outdata.close();

  end_simulation();
}

/***************************************************************/
/***************************************************************/

/***************************************************************/
void process_mem_usage(double& vm_usage, double& resident_set)
{
   using std::ios_base;
   using std::ifstream;
   using std::string;

   vm_usage     = 0.0;
   resident_set = 0.0;

   // 'file' stat seems to give the most reliable results
   //
   ifstream stat_stream("/proc/self/stat",ios_base::in);

   // dummy vars for leading entries in stat that we don't care about
   //
   string pid, comm, state, ppid, pgrp, session, tty_nr;
   string tpgid, flags, minflt, cminflt, majflt, cmajflt;
   string utime, stime, cutime, cstime, priority, nice;
   string O, itrealvalue, starttime;

   // the two fields we want
   //
   unsigned long vsize;
   long rss;

   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
               >> utime >> stime >> cutime >> cstime >> priority >> nice
               >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

   stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
   vm_usage     = vsize / 1024.0;
   resident_set = rss * page_size_kb;
}
/***************************************************************/

int main(int argc, char *argv[])
{
  auto t1 = std::chrono::high_resolution_clock::now();

  //ASSERT( argc==7 );
  cout << "1 " << endl;
  //Creacion de archivos
  char archivo_ventas[2048];
  char archivo_productos[2048];
  char archivo_clientes[2048];
  char salida_clientes[2048];
  char salida_productos[2048];
  char salida_ventas[2048];
  char archivo_segmentos[2048];
  char archivo_rubros[2048];
  char salida_recomendacion[2048];
  int tipoRec;
  // //Queries
  // int TQ = atoi(argv[1]); //Total consulats a procesar en cada nodo

  // //Rcache
  // int nodos = atoi(argv[2]);
  //DAG
  strcpy(archivo_ventas, argv[1]);
  strcpy(archivo_productos, argv[2]);
  strcpy(archivo_clientes, argv[3]);
  strcpy(salida_clientes, argv[4]);
  strcpy(salida_productos, argv[5]);
  strcpy(salida_ventas, argv[6]);
  strcpy(archivo_segmentos, argv[7]);
  strcpy(archivo_rubros, argv[8]);
  tipoRec = atoi(argv[9]);
  strcpy(salida_recomendacion, argv[10]);

  cout << archivo_ventas << endl;
  cout << archivo_productos << endl;
  cout << archivo_clientes << endl;
  cout << salida_clientes << endl;
  cout << salida_productos << endl;
  cout << salida_ventas << endl;
  cout << archivo_segmentos << endl;
  cout << archivo_rubros << endl;
  cout << to_string(tipoRec) << endl;
  cout << salida_recomendacion << endl;
  //------------------------------------------------------

  simulation::instance()->begin_simulation(new sqsDll());
  cout << "3" << endl;

  handle<sistema> system(new sistema("System main", 10000000e100,
                                     archivo_ventas, archivo_productos, archivo_clientes, salida_clientes, salida_productos, salida_ventas, archivo_segmentos, archivo_rubros, tipoRec, salida_recomendacion));

  cout << "4 " << endl;
  system->activate();
  cout << "5 " << endl;

  simulation::instance()->run();
  cout << "6 " << endl;

  simulation::instance()->end_simulation();
  auto t2 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

cout << "Tiempo:" << endl;
  std::cout << duration/1000;

  double vm, rss;
   process_mem_usage(vm, rss);
   cout << "VM: " << vm << "; RSS: " << rss << endl;

  //------------------------------------------------------

  //cout <<endl<< "done!" << endl;

  return 0;
}
