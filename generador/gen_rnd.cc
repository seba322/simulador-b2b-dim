#include "gen_rnd.h"

void Gen_rnd::inner_body()
{

  string linea, terminos;
  handle<Consumidor> *c;

  cout << "Archivo Trazas: " << archivo_trazas << " - ventas" << endl;
  // fin.open("./DATA/sales_sim_final-v8-inv.txt");
   fin.open(archivo_trazas);
  Venta *v;

  //La primera linea se tira si se usa el Log de Yahoo

  while (1)
  {
    if (!getline(fin, linea))
      passivate();

    // cout << "Linea " << linea << endl;
  // cout << "asadadsadd"<< endl;
    //cout<<"Linea "<<linea<<endl;

    // historialVentas.push_back(linea);
    tokens.clear();
    util->Tokenize(linea, tokens, " ");
    // cout << "Linea 1" << endl;

    string idCompra = tokens[0].c_str();
    string idCliente = tokens[1].c_str();
    string fecha = tokens[2].c_str();
    // cout << "Linea 2" << endl;
    int cantidadProductos = atoi(tokens[3].c_str());
    map<string, int> productos;
    // cout << "Linea 3" << endl;
    for (int i = 4; i < (4 + cantidadProductos * 2); i += 2)
    {
      productos.insert(pair<string, int>(tokens[i].c_str(), atoi(tokens[i + 1].c_str())));
    }

    //  cout << "Linea 4" << idCompra << endl;
    v = new Venta(idCompra, idCliente, fecha, cantidadProductos, productos,tipoRecomendacion);
    auto el = consumidores.find(idCliente);
    // cout << "Linea 5" << endl;
    c = &(el->second);
    // cout << "Linea 6 " << idCliente+" "+ (*c)->getIdCliente() << endl;
    (*c)->agregarVenta(v);
    // cout << "Linea 7" << endl;
    if ((*c)->idle() && !(*c)->get_busy())
      (*c)->activateAfter(current());
    // cout << "Linea 8" << endl;
  }
}
