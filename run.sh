#            TQ  Procesadores DAG  
archivo_ventas="./DATA/sales_sim_final-v8-inv.txt"
archivo_productos="./DATA/products_sm_final.csv"
archivo_clientes="./DATA/clients_sm_final.csv"
archivo_segmentos="./DATA/producto_segmento_final.txt"
archivo_rubros="./DATA/producto_rubro_final.txt"
tipo_rec="2"

salida_ventas="salida_ventas_2.20-inv.dat"
salida_clientes="salida_clientes_2.20-inv.dat"
salida_productos="salida_productos_2.20-inv.dat"
salida_recomendacion="salida_recomendacion_2.20-inv.dat"

# time ./Simulador "./DATA/sales_sim_final-v8-inv.txt" "./DATA/products_sm_final.csv" "./DATA/clients_sm_final.csv" "salida_cliente2.dat" "salida_productos2.dat" "salida_ventas2.dat" "./DATA/producto_segmento_final.txt" "./DATA/producto_rubro_final.txt" 0 
time ./Simulador $archivo_ventas $archivo_productos $archivo_clientes $salida_clientes $salida_productos $salida_ventas $archivo_segmentos $archivo_rubros $tipo_rec $salida_recomendacion

