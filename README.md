# Quiz #3: Análisis de Algoritmos

## Merge Sort — $O(n \log n)$
![Gráfica Merge Sort](img/mergesort_benchmark.png)

* **Análisis comparativo**: Las pruebas siguen una linea muy similar a la teoria. Cuando el arreglo se hace 10 veces más grande (de 100 000 a 1 000 000 datos), el tiempo pasa de unos 10 ms a unos 112 ms; es decir, tarda un poco más de 10 veces, lo cual es esperado según la literatura con $O(n \log n)$.

---

## Búsqueda Binaria — $O(\log n)$
![Gráfica Búsqueda Binaria](img/busqueda_binaria_benchmark.png)

* **Análisis comparativo**: La gráfica muestra un incremento rápido al inicio y una posterior nivelación. Aunque el tamaño del arreglo creció 1 000 veces (de 1 000 a 1 000 000 de elementos), el tiempo apenas pasó de 51 ns a 157 ns (solo se triplicó). Esto prueba de cumple con la teoría de $O(\log n)$.