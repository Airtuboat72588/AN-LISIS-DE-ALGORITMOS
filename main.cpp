#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>

// Implementación de Merge Sort
void mezclar(std::vector<int>& arreglo, int izquierda, int medio, int derecha) {
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arreglo[izquierda + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arreglo[medio + 1 + j];

    int i = 0, j = 0, k = izquierda;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arreglo[k++] = L[i++];
        } else {
            arreglo[k++] = R[j++];
        }
    }

    while (i < n1) arreglo[k++] = L[i++];
    while (j < n2) arreglo[k++] = R[j++];
}

void ordenarPorMezcla(std::vector<int>& arreglo, int izquierda, int derecha) {
    if (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        ordenarPorMezcla(arreglo, izquierda, medio);
        ordenarPorMezcla(arreglo, medio + 1, derecha);
        mezclar(arreglo, izquierda, medio, derecha);
    }
}

//Búsqueda Binaria
int busquedaBinaria(const std::vector<int>& arreglo, int clave) {
    int izquierda = 0;
    int derecha = static_cast<int>(arreglo.size()) - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (arreglo[medio] == clave) {
            return medio;
        }
        if (arreglo[medio] < clave) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    return -1;
}

//Números aleatorios
std::vector<int> generarDatosAleatorios(size_t tamano, int valorMin, int valorMax) {
    static std::mt19937 generador(1337);
    std::uniform_int_distribution<int> distribucion(valorMin, valorMax);

    std::vector<int> datos(tamano);
    for (size_t i = 0; i < tamano; ++i) {
        datos[i] = distribucion(generador);
    }
    return datos;
}

int main() {
    //Tamaños de prueba (N)
    std::vector<int> tamanos = {
        1000, 5000, 10000, 25000, 50000, 
        100000, 200000, 400000, 800000, 1000000
    };

    const int repeticionesMezcla = 5;
    const int repeticionesBusqueda = 50000; // Requiere más repeticiones por ser en nanosegundos

    std::ofstream archivoSalida("resultados_benchmark.csv");
    if (!archivoSalida.is_open()) {
        std::cerr << "Error al abrir el archivo de salida.\n";
        return 1;
    }

    archivoSalida << "N,Tiempo_Mergesort_ms,Tiempo_BusquedaBinaria_ns\n";
    std::cout << "Iniciando benchmark...\n";

    for (int n : tamanos) {
        //Benchmark Mergesort
        double tiempoTotalMezcla = 0.0;
        for (int r = 0; r < repeticionesMezcla; ++r) {
            std::vector<int> muestra = generarDatosAleatorios(n, 0, 10000000);
            
            auto inicio = std::chrono::high_resolution_clock::now();
            ordenarPorMezcla(muestra, 0, n - 1);
            auto fin = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> duracion = fin - inicio;
            tiempoTotalMezcla += duracion.count();
        }
        double promedioMezclaMs = tiempoTotalMezcla / repeticionesMezcla;

        //Benchmark Búsqueda Binaria
        std::vector<int> datosOrdenados = generarDatosAleatorios(n, 0, 10000000);
        std::sort(datosOrdenados.begin(), datosOrdenados.end());

        //Test con claves existentes y no existentes
        std::mt19937 genClaves(42);
        std::uniform_int_distribution<int> distClaves(0, 10000000);

        auto inicioBB = std::chrono::high_resolution_clock::now();
        for (int r = 0; r < repeticionesBusqueda; ++r) {
            int clave = distClaves(genClaves);
            volatile int indice = busquedaBinaria(datosOrdenados, clave);
            (void)indice;
        }
        auto finBB = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::nano> duracionBB = finBB - inicioBB;
        double promedioBusquedaNs = duracionBB.count() / repeticionesBusqueda;

        // Salida en CSV y consola
        archivoSalida << n << "," << promedioMezclaMs << "," << promedioBusquedaNs << "\n";
        std::cout << "N = " << n 
                << " | Mergesort: " << promedioMezclaMs << " ms"
                << " | Búsqueda Binaria: " << promedioBusquedaNs << " ns\n";
    }

    archivoSalida.close();
    std::cout << "Benchmark finalizado. Resultados exportados a 'resultados_benchmark.csv'.\n";

    return 0;
}