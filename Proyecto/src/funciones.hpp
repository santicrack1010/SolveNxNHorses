#ifndef __FUNCIONES_H__
#define __FUNCIONES_H__

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#define NO_CASILLAS_DISPONIBLES 0
#define MAX_SOLUCIONES 10  // Constante para llevar control de las impresiones

int totalSoluciones = 0;  // Variable goblal que lleva control de las soluciones

// Funcion encargada de inicializar el tablero donde se trabajara
// Recibe el tablero creado y el n para el tamanio
void inicializarTablero(std::vector<std::vector<char>> &tablero, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      tablero[i][j] = '0';  // Todas las casillas se inicializan con un 0
    }
  }
}

// Funcion que valida los movimientos disponibles
// Retorna la cantidad de casillas disponobles despues de los movimientos
int verificarMovimientos(std::vector<std::vector<char>> &tablero, int fila, int columna, int casillasDisponibles, int n) {
  int eliminadas = casillasDisponibles - 1;  // Contador de casillas eliminadas
  int movimientos[8][2] = {
      {2, 1},  {2, -1}, {-2, 1}, {-2, -1}, {1, 2},
      {1, -2}, {-1, 2}, {-1, -2}};  // Movimientos posibles para el caballo

  for (int i = 0; i < 8; i++) {
    int nuevaFila = fila + movimientos[i][0];
    int nuevaColumna = columna + movimientos[i][1];

    // Verifica si la nueva posición está dentro del tablero y es una casilla vacía
    if (nuevaFila >= 0 && nuevaFila < n && nuevaColumna >= 0 &&
        nuevaColumna < n && tablero[nuevaFila][nuevaColumna] == '0') {
      tablero[nuevaFila][nuevaColumna] = 'x';  // Marca la casilla como visitada por el caballo
      eliminadas--;
    }
  }

  return eliminadas;  // Devuelve la cantidad de casillas disponibles después de los movimientos del caballo
}

// Función encargada de insertar los caballos en el tablero
// Retorna el número total de caballos insertados en el tablero
int insertarCaballos(std::vector<std::vector<char>> &tablero, int fila, int columna, int casillasDisponibles, int numCaballos, int n) {
  // Verifica si hay suficientes casillas disponibles para insertar más caballos.
  if (casillasDisponibles > NO_CASILLAS_DISPONIBLES) {
    // Verifica si la posición actual en el tablero está vacía ('0').
    if (tablero[fila][columna] == '0') {
      // Coloca un caballo en la posición actual y actualiza las casillas disponibles.
      tablero[fila][columna] = 'C';
      casillasDisponibles = verificarMovimientos(tablero, fila, columna, casillasDisponibles, n);
      numCaballos++;  // Incrementa el contador de caballos insertados.
      
      // Genera nuevas posiciones aleatorias para la siguiente inserción.
      fila = rand() % n;
      columna = rand() % n;
      
      // Llamada recursiva para insertar más caballos.
      return insertarCaballos(tablero, fila, columna, casillasDisponibles, numCaballos, n);
    } else {
      // Si la posición actual no está vacía, genera nuevas posiciones aleatorias.
      fila = rand() % n;
      columna = rand() % n;
      
      // Llamada recursiva para intentar insertar un caballo en la nueva posición.
      return insertarCaballos(tablero, fila, columna, casillasDisponibles, numCaballos, n);
    }
  } else {
    // Si no hay suficientes casillas disponibles, retorna el número total de caballos insertados.
    return numCaballos;
  }
}

// Funcion dedicada a imprimir el tablero
void imprimirTablero(std::vector<std::vector<char>> &tablero, int n) {
  for (int i = 0; i < n; i++) {
    std::cout << std::endl;
    for (int j = 0; j < n; j++) {
      std::cout << "[" << tablero[i][j] << "]";
    }
  }
  std::cout << std::endl;
}

// Funcion encargada de encontrar la mayor cantidad de caballos que pueden caber en el tablero
int maximoCaballos(int totalCaballos[]) {
  int Maximo = totalCaballos[0];  // Inicializa el máximo con el primer valor del array.

  // Itera a través del array desde el segundo elemento.
  for (int i = 1; i < MAX_SOLUCIONES; i++) {
    // Compara el valor actual con el máximo actual.
    if (totalCaballos[i] > Maximo) {
      Maximo = totalCaballos[i];  // Actualiza el máximo si se encuentra un valor mayor.
    }
  }

  return Maximo;  // Retorna el valor máximo encontrado en el array.
}

// Funcion recursiva para solucionar el problema pro backtracking
void backtracking(std::vector<std::vector<char>> &tablero, std::vector<std::vector<bool>> &visitados, int fila, int n) {
  // Caso base: si legamos a la ultima fila, hemos encontrado una solucion
  if (fila == n) {
    totalSoluciones++;
    return;
  }

  // Recorremos todas las columnas de la fila actual
  for (int columna = 0; columna < n; columna++) {
    // Verifica si la posicion actual no ha sido visitada
    if (!visitados[fila][columna]) {
      // Marca la posición como visitada y coloca un caballo en el tablero
      visitados[fila][columna] = true;
      tablero[fila][columna] = 'C';  // 'C' representa la posición del caballo

      // Llamada recursiva para explorar las posiciones en la siguiente fila
      backtracking(tablero, visitados, fila + 1, n);

      // Deshace los cambios despues de la llamda recursiva
      tablero[fila][columna] = '0';
      visitados[fila][columna] = false;
    }
  }
}

// Funcion para contar la cantidad maxima de soluciones
// Retorna la cantidad de soluciones maximas para el tablero
int contarSolucionesConFilaInicial(std::vector<std::vector<char>> &tablero, int n) {
  std::vector<std::vector<bool>> visitados(n, std::vector<bool>(n, false));  // Crea un tablero de posiciones visitadas

  backtracking(tablero, visitados, 0, n);  // Se aplica el algoritmo de backtracking al tablero creado
  return totalSoluciones;
}

#endif  // __FUNCIONES_H__