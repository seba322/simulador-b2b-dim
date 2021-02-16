#ifndef GLOBAL_H
#define GLOBAL_H

//#include "/homes/rscheihi/carlos/SIMULADOR/libcppsim-0.2.1/src/cppsim.hh"
#include "../../src/cppsim.hh"
#include "../../src/rng.hh"
#include "../../src/sqsPrio.hh"
#include <iostream>
#include <map>
#include <sstream>
#include <set>
#include <vector>
#include <list>
#include <assert.h>
#include <fstream>
#include <string>
#include <limits>
#include <queue>
#include <math.h>
#include <algorithm>

using namespace std;

#define MAX_BUFFER 2048

#define ASSERT(x) assert(x)

/****************/
//SERVICIOS
#define USER 500
#define END_QUERY 501
#define IS 502
#define MERGE 503

#define PROC 601
#define BROKER 602

//--DEBUGING
#define DEBUG

#ifdef DEBUG
#define dout cout
#else
#define dout \
  if (false) \
  cout
#endif

//---------------------------------------------------
//---------------------------------------------------

class Venta
{
public:
  string id_compra;
  string id_cliente;
  string fecha;
  int tipoRecomendacion;
  int cantidadProductos;

  map<string, int> productos;

  Venta(string _id_compra, string _id_cliente, string _fecha, int _cantidadProductos, map<string, int> _productos, int _tipoRecomendacion)
  {
    id_compra = _id_compra;
    id_cliente = _id_cliente;
    fecha = _fecha;
    cantidadProductos = _cantidadProductos;
    productos = _productos;
    tipoRecomendacion = _tipoRecomendacion;
  }
};

class Producto
{
  string id_producto;
  string jerarquia;
  double puntaje;
  int stock;
  int precio;
  int ventas;

protected:
  void inner_body(void);

public:
  Producto(
      string _id_producto,
      string _jerarquia, int _stock, double _puntaje, int _precio)
  {
    id_producto = _id_producto;
    jerarquia = _jerarquia;
    stock = _stock;
    puntaje = _puntaje;
    precio = _precio;
    ventas = 0;
  }
  void SetStock(int val)
  {
    // cout << "DISMINUYENDO STOCK DE2  " + id_producto + " A " + to_string(val) << endl;
    if (val > 0)
    {

      stock = val;
    }
    else
    {
      stock = 0;
    }
  }

  int GetStock()
  {
    return stock;
  }

  int GetPrecio()
  {
    return precio;
  }
  double GetPuntaje()
  {
    return puntaje;
  }
  string GetId()
  {
    return id_producto;
  }

  string GetJerarquia()
  {
    return jerarquia;
  }

  int GetVentas(){
    return ventas;
  }

  void agregarVenta(int cantidad)
  {
    ventas+=cantidad;
  }

 
};
//---------------------------------------------------

#endif
