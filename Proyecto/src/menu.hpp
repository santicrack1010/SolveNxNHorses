#ifndef __MENU_H__
#define __MENU_H__

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "funciones.hpp"

#define NO_CASILLAS_DISPONIBLES 0
#define MAX_SOLUCIONES 10 // Constante para llevar control de las impresiones

/*Menu*/

void menu() {
  int n, fila, columna;
  int numCaballos, totalCaballos[MAX_SOLUCIONES];
  int casillasDisponibles, MaxCaballos;

  std::vector<std::vector<char>> tablero;

  std::ofstream archivo("Caballos.txt");

  if (!archivo.is_open()) {
    std::cerr << "No se pudo abrir el archivo." << std::endl;
    return;
  }

  do {
    std::cout << "\n\tDame tamanio de tablero: ";
    std::cin >> n;
  } while (n < 2 || n > 20);

  std::streambuf *original_stdout = std::cout.rdbuf();
  std::cout.rdbuf(archivo.rdbuf());

  srand(time(NULL));
  tablero.resize(n, std::vector<char>(n));

  for (int j = 0; j < MAX_SOLUCIONES; j++) {
    numCaballos = 0;
    casillasDisponibles = n * n;
    fila = rand() % n;
    columna = rand() % n;
    std::cout << "(" << fila << "," << columna << ")" << std::endl;
    inicializarTablero(tablero, n);
    totalCaballos[j] = insertarCaballos(tablero, fila, columna, casillasDisponibles, numCaballos, n);
    imprimirTablero(tablero, n);
    std::cout << "\n\nEl numero maximo de caballos en esta solucion es de " << totalCaballos[j] << std::endl;
  }

  MaxCaballos = maximoCaballos(totalCaballos);
  std::cout << "\nEl numero maximo de caballos en un tablero de " << n << " x " << n << " sin atacarse es " << MaxCaballos << std::endl;

  std::cout << "\nEl numero maximo de soluciones posibles para un tablero de " << n << " x " << n << " es " << contarSolucionesConFilaInicial(tablero, n) << std::endl;

  std::cout.rdbuf(original_stdout);

  system("PAUSE");
}

#endif  // __MENU_H__