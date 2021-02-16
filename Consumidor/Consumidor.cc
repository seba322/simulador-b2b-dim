#include "Consumidor.h"

void Consumidor::inner_body()
{
   Venta *v;
   while (1)
   {

      // cout << "consumidor "+id_cliente << endl;

      if (colaVentas.empty())
         passivate();

      ASSERT(!colaVentas.empty());

      v = colaVentas.front();
      colaVentas.pop_front();

      busy = true;
      Comprar(v);

      busy = false;

   } //while()
}

string Consumidor::GetProductoSimilar(string jerarquia, int cantidad, string idProducto)
{
   string jSuperior = jerarquia.substr(0, 8);
   // cout << "1 " << endl;
   map<string, Producto *>::iterator itr;
   Producto *producto;
   list<Producto *> prodSelect;
   list<double> rankings;
   // cout << "2 " << endl;
   for (itr = productos->begin(); itr != productos->end(); itr++)
   {
      producto = itr->second;
      double dist = 0.0;
      string subJerarquia = producto->GetJerarquia().substr(0, 8);
      if (subJerarquia == jSuperior && producto->GetStock() >= cantidad && idProducto != producto->GetId())
      {
         if (producto->GetJerarquia() == jerarquia)
         {
            dist = 1;
         }
         prodSelect.push_back(producto);

         // FUNCION DE RANKING
         double rank = producto->GetPuntaje() * 0.30 + (1 / producto->GetPrecio()) * 0.30 + 0.5 * dist;
         // cout << " similar: " + producto->GetId() + "rank: " + to_string(rank) << endl;
         rankings.push_back(rank);
      }
   }
   // cout << "3 " << endl;
   if (rankings.size() == 0)
   {
      // cout << "4 " << endl;
      return "-1";
   }

   double max = 0.0;
   int maxIndex = 0;
   int index = 0;
   for (list<double>::iterator i = rankings.begin();
        i != rankings.end();
        i++)
   {
      auto el = *i;
      // cout << "el es: " + to_string(el) << endl;
      // cout << "max es: " + to_string(max) << endl;
      if (el > max)
      {
         max = el;
         maxIndex = index;
      }
      index++;
   }

   auto prodItr = prodSelect.begin();
   advance(prodItr, maxIndex);

   auto finalP = *prodItr;
   return finalP->GetId();
}

string Consumidor::GetProductoBySegmento(string jerarquia, int cantidad, string idProducto)
{
   string jSuperior = jerarquia.substr(0, 8);
   map<string, Producto *>::iterator itr;
   // Producto *producto;
   list<Producto *> prodSelect;
   list<double> rankings;
   for (itr = productosSegmento.begin(); itr != productosSegmento.end(); itr++)
   {
      // cout << "2 "+ itr->first << endl;
      auto producto = itr->second;
      double dist = 0.0;
      //  cout << "2.1 "+ producto->GetId() << endl;

      string subJerarquia = producto->GetJerarquia().substr(0, 8);
      //  cout << "2.3 " << endl;
      int currentStock = productos->find(producto->GetId())->second->GetStock();
      //  cout << "2.4 " << endl;
      if (subJerarquia == jSuperior && currentStock >= cantidad && idProducto != producto->GetId())
      {
         //  cout << "2.5 " << endl;
         if (producto->GetJerarquia() == jerarquia)
         {
            dist = 1;
         }
         prodSelect.push_back(producto);
         //  cout << "2.6 " << endl;

         // FUNCION DE RANKING
         double rank = producto->GetPuntaje();
         // cout << " similar: " + producto->GetId() + "rank: " + to_string(rank) << endl;
         rankings.push_back(rank);
      }
   }
   // cout << "3 " << endl;
   if (rankings.size() == 0)
   {
      // cout << "4 " << endl;
      return "-1";
   }

   double max = 0.0;
   int maxIndex = 0;
   int index = 0;
   for (list<double>::iterator i = rankings.begin();
        i != rankings.end();
        i++)
   {
      auto el = *i;
      // cout << "el es: " + to_string(el) << endl;
      // cout << "max es: " + to_string(max) << endl;
      if (el > max)
      {
         max = el;
         maxIndex = index;
      }
      index++;
   }

   auto prodItr = prodSelect.begin();
   advance(prodItr, maxIndex);

   auto finalP = *prodItr;
   return finalP->GetId();
}

string Consumidor::GetProductoByRubro(string jerarquia, int cantidad, string idProducto)
{
   string jSuperior = jerarquia.substr(0, 8);
   map<string, Producto *>::iterator itr;
   Producto *producto;
   list<Producto *> prodSelect;
   list<double> rankings;
   // cout << "2 " << endl;
   for (itr = productosRubro.begin(); itr != productosRubro.end(); itr++)
   {
      producto = itr->second;
      double dist = 0.0;
      string subJerarquia = producto->GetJerarquia().substr(0, 8);
      int currentStock = productos->find(producto->GetId())->second->GetStock();
      if (subJerarquia == jSuperior && currentStock >= cantidad && idProducto != producto->GetId())
      {
         if (producto->GetJerarquia() == jerarquia)
         {
            dist = 1;
         }
         prodSelect.push_back(producto);

         // FUNCION DE RANKING
         double rank = producto->GetPuntaje();
         // cout << " similar: " + producto->GetId() + "rank: " + to_string(rank) << endl;
         rankings.push_back(rank);
      }
   }
   // cout << "3 " << endl;
   if (rankings.size() == 0)
   {
      // cout << "4 " << endl;
      return "-1";
   }

   double max = 0.0;
   int maxIndex = 0;
   int index = 0;
   for (list<double>::iterator i = rankings.begin();
        i != rankings.end();
        i++)
   {
      auto el = *i;
      // cout << "el es: " + to_string(el) << endl;
      // cout << "max es: " + to_string(max) << endl;
      if (el > max)
      {
         max = el;
         maxIndex = index;
      }
      index++;
   }

   auto prodItr = prodSelect.begin();
   advance(prodItr, maxIndex);

   auto finalP = *prodItr;
   return finalP->GetId();
}

void Consumidor::Comprar(Venta *v)
{
   string linea = v->id_compra + " " + v->id_cliente + " " + v->fecha + " ";
   string lineaAux = "";
   map<string, int>::iterator itr;
   Producto *producto;
   int cantidadCompras = 0;

   for (itr = v->productos.begin(); itr != v->productos.end(); itr++)
   {
      string idProducto = itr->first;
      int cantidad = itr->second;
      auto p = productos->find(idProducto);
      producto = p->second;
      int stockActual = producto->GetStock();
      // cout << "Buscando producto "+ idProducto << endl;
      // cout << "stockActual " + to_string(stockActual) << endl;
      //  cout << "se cae1 " + to_string(stockActual)+ " --"+to_string(cantidad) << endl;
      if (producto->GetStock() < cantidad)
      {
         // cout << "ENTRO ACA "+ to_string(v->tipoRecomendacion)<< endl;
         string idSimilar = "-1";
         if (v->tipoRecomendacion == 2)
         {

            idSimilar = GetProductoByRubro(producto->GetJerarquia(), cantidad, idProducto);
         }
         else if (v->tipoRecomendacion == 1)
         {

            idSimilar = GetProductoBySegmento(producto->GetJerarquia(), cantidad, idProducto);
         }
         else
         {

            idSimilar = GetProductoSimilar(producto->GetJerarquia(), cantidad, idProducto);
         }
         // cout << "obtenido similar " + idSimilar << endl;
         if (idSimilar != "-1")
         {
            //  cout << "ENTRO ACA2 "+ idSimilar<< endl;
            auto pSim = productos->find(idSimilar);
            auto productoSim = pSim->second;
            //  cout << "DISMINUYENDO STOCK DE  " +idSimilar+ "/"+to_string(productoSim->GetStock())+" A "+to_string(productoSim->GetStock()-cantidad) << endl;
            if ((productoSim->GetStock() - cantidad) >= 0)
            {
               productoSim->SetStock(productoSim->GetStock() - cantidad);
               productoSim->agregarVenta(cantidad);
               lineaAux += " " + idSimilar + " ";
               lineaAux += to_string(itr->second);
               cantidadCompras++;

               // cout << "escribiendo archivo"<< endl;

               std::ofstream outdataLog;
               outdataLog.open(salida_recomendacion, std::ios::out | std::ios::app);
               if (!outdataLog)
               { // file couldn't be opened
                  cerr << "Error: file could not be opened" << endl;
                  exit(1);
               }
               string isEqual = "0";

               if (producto->GetJerarquia() == productoSim->GetJerarquia())
               {
                  isEqual = "2";
               }
               else if (producto->GetJerarquia().substr(0, 8) == productoSim->GetJerarquia().substr(0, 8))
               {
                  isEqual = "1";
               }

               outdataLog << to_string(v->tipoRecomendacion) + "," + producto->GetId() + "," + producto->GetJerarquia() + "," + productoSim->GetId() + "," + productoSim->GetJerarquia() + "," + isEqual << endl;

               outdataLog.close();
            }
            else
            {
               agregarComprarNoEncontrada();
            }
         }
         else
         {

            agregarComprarNoEncontrada();
            std::ofstream outdataLog;
            outdataLog.open(salida_recomendacion, std::ios::out | std::ios::app);
            if (!outdataLog)
            { // file couldn't be opened
               cerr << "Error: file could not be opened" << endl;
               exit(1);
            }
            outdataLog << to_string(v->tipoRecomendacion) + "," + producto->GetId() + "," + producto->GetJerarquia() + "," + "-1" + "," + "-1" + "," + "-1" << endl;

            outdataLog.close();
            // cerr << "No hay stock ni item parecido" << endl;
         }
      }
      else
      {
         // cout << "se cae " + to_string(stockActual-cantidad) << endl;
         //  cout << "DISMINUYENDO STOCK DE  " +idProducto+ "/"+to_string(stockActual)+" A "+to_string(stockActual-cantidad) << endl;

         producto->SetStock(producto->GetStock() - cantidad);
         producto->agregarVenta(cantidad);
         cantidadCompras++;
         lineaAux += " " + itr->first + " ";
         lineaAux += to_string(itr->second);
      }
   }

   std::ofstream outdata;

   outdata.open(salida_ventas, std::ios::out | std::ios::app);
   if (!outdata)
   { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
   if (cantidadCompras > 0)
   {

      outdata << linea + to_string(cantidadCompras) + lineaAux << endl;
   }
   // addHistory(linea + "\n");
   agregarCompra();
   outdata.close();
}
