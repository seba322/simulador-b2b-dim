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
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <unistd.h>
#include <ios>



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
  int stockInicial;
  int nReposicion;

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
    nReposicion=0;
    stockInicial=_stock;
  }
  void SetStock(int val)
  {
    // cout << "DISMINUYENDO STOCK DE2  " + id_producto+" con sotck "+to_string(stock) + "  A " + to_string(stock-val) << endl;
    // if (val > 0)
    // {

    // }
    // else
    // {
    //   stock = 0;
    // }
      stock = stock-val;
      // cout << "Stock actual modificado"+ to_string(stock) << endl;
  }
  void ResetStock(){
    nReposicion=nReposicion+1;
    stock=stockInicial+(stockInicial*(nReposicion/100));
    // cout << "Aumentando n reposicion de "+ jerarquia+" "+to_string(nReposicion) << endl;
  }

  int GetReposicion(){
    return nReposicion;

  }

  int GetStock()
  {
    // cout << "Stock actual"+ to_string(stock) << endl;
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
