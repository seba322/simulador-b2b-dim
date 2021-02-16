#ifndef CON_H
#define CON_H

#include "../glob.h"

class Consumidor : public process
{
    string id_cliente;
    string id_segmento;
    string id_rubro;
    char salida_ventas[2048];
    char salida_recomendacion[2048];
    bool busy;

    list<Venta *> colaVentas;

    string ventasRealizadas;
    map<string, Producto *> *productos;
    map<string, Producto *> productosSegmento;
    map<string, Producto *> productosRubro;
    int compras;
    int nCompras;
    int nFallidas;

protected:
    void inner_body(void);

public:
    Consumidor(const string &name, string _id_cliente,
               string _id_segmento,
               string _id_rubro, map<string, Producto *> *_productos,
               map<string, Producto *> _productosSegmento, map<string, Producto *> _productosRubro,
               char *_salida_ventas,
               char *_salida_recomendacion) : process(name)
    {
        id_cliente = _id_cliente;
        id_segmento = _id_segmento;
        id_rubro = _id_rubro;
        compras = 0;
        busy = false;
        productos = _productos;
        productosSegmento = _productosSegmento;
        productosRubro = _productosRubro;
        nCompras = 0;
        ventasRealizadas = "";
        nFallidas = 0;
        strcpy(salida_ventas, _salida_ventas);
        strcpy(salida_recomendacion, _salida_recomendacion);
        
    }
    void Comprar(Venta *v);

    bool get_busy()
    {
        return busy;
    }
    void agregarCompra()
    {
        nCompras = nCompras + 1;
    }
    void agregarVenta(Venta *v)
    {

        colaVentas.push_back(v);
    }
    void agregarComprarNoEncontrada()
    {
        nFallidas = nFallidas + 1;
    }

    int GetVentasFallidas()
    {
        return nFallidas;
    }
    int GetNCompras()
    {
        return nCompras;
    }

    string getIdCliente()
    {
        return id_cliente;
    }
    string GetVentasRealizadas()
    {

        return ventasRealizadas;
    }
    void addHistory(string el)
    {
        ventasRealizadas += el;
    }

    // string GetProductoSimilar(string jerarquia, int cantidad)
    // {
    //     string jSuperior = jerarquia.substr(0, 8);
    //     cout << "1 " << endl;
    //     map<string, Producto *>::iterator itr;
    //     Producto *producto;
    //     list<Producto *> prodSelect;
    //     list<double> rankings;
    //     cout << "2 " << endl;
    //     for (itr = productos->begin(); itr != productos->end(); itr++)
    //     {
    //         producto = itr->second;
    //         double dist = 0.0;
    //         string subJerarquia = producto->GetJerarquia().substr(0, 8);
    //         if (subJerarquia == jSuperior && producto->GetStock() >= cantidad)
    //         {
    //             if (producto->GetJerarquia() == jerarquia)
    //             {
    //                 dist = 1;
    //             }
    //             prodSelect.push_back(producto);

    //             // FUNCION DE RANKING
    //             double rank = producto->GetPuntaje() * 0.30 + (1 / producto->GetPrecio()) * 0.30 + 0.5 * dist;
    //             cout << " similar: " + producto->GetId() + "rank: " + to_string(rank) << endl;
    //             rankings.push_back(rank);
    //         }
    //     }
    //     cout << "3 " << endl;
    //     if (rankings.size() == 0)
    //     {
    //         cout << "4 " << endl;
    //         return "-1";
    //     }

    //     double max = 0.0;
    //     int maxIndex = 0;
    //     int index = 0;
    //     for (list<double>::iterator i = rankings.begin();
    //          i != rankings.end();
    //          i++)
    //     {
    //         auto el = *i;
    //         cout << "el es: " + to_string(el) << endl;
    //         cout << "max es: " + to_string(max) << endl;
    //         if (el > max)
    //         {
    //             max = el;
    //             maxIndex = index;
    //         }
    //         index++;
    //     }

    //     auto prodItr = prodSelect.begin();
    //     advance(prodItr, maxIndex);

    //     auto finalP = *prodItr;
    //     return finalP->GetId();
    // }
    string GetProductoSimilar(string jerarquia, int cantidad,string idProducto);
    string GetProductoByRubro(string jerarquia, int cantidad,string idProducto);
    string GetProductoBySegmento(string jerarquia, int cantidad,string idProducto);
    // void printel()
    // {
    //     vector<string>::iterator it;

    //     for (it = ventasRealizadas.begin(); it != ventasRealizadas.end(); ++it)
    //     {
    //         auto v = (*it);
    //         cout << "escribiendo ventas3" << v << endl;
    //     }
    // }
};

#endif
