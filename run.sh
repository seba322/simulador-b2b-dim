#            TQ  Procesadores DAG  
archivo_ventas="./SALIDA/sales_sim_final-1000-100.txt"
archivo_productos="./SALIDA/products_sm_final.csv"
archivo_clientes="./SALIDA/clients_sm_final.csv"
archivo_segmentos="./SALIDA/producto_segmento_final-1000.txt"
archivo_rubros="./SALIDA/producto_rubro_final-1000.txt"
tipo_rec="0"

salida_ventas="./SALIDA0/salida_ventas_u-4.dat"
salida_clientes="./SALIDA0/salida_clientes_u-4.dat"
salida_productos="./SALIDA0/salida_productos_u-4.dat"
salida_recomendacion="./SALIDA0/salida_recomendacion_pr1-1.dat"
log_recomendacion="./rankpr1-1.csv"
price_w="1.0"
popularity_w="1.0"
category_w="1.0"

# time ./Simulador "./DATA/sales_sim_final-v8-inv.txt" "./DATA/products_sm_final.csv" "./DATA/clients_sm_final.csv" "salida_cliente2.dat" "salida_productos2.dat" "salida_ventas2.dat" "./DATA/producto_segmento_final.txt" "./DATA/producto_rubro_final.txt" 0 
time ./Simulador $archivo_ventas $archivo_productos $archivo_clientes $salida_clientes $salida_productos $salida_ventas $archivo_segmentos $archivo_rubros $tipo_rec $salida_recomendacion $log_recomendacion $popularity_w $category_w $price_w

