#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Para usleep()

#define SIZE 15

void initMaze(char maze[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = '#';
        }
    }
}

void printMaze(char maze[SIZE][SIZE]) {
    printf("\033[2J"); // Limpia la pantalla
    printf("\033[H");  // Posiciona el cursor en la esquina superior izquierda
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

void carveMaze(char maze[SIZE][SIZE], int x, int y) {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int order[4] = {0, 1, 2, 3};

    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = order[i];
        order[i] = order[r];
        order[r] = temp;
    }

    for (int i = 0; i < 4; i++) {
        int dx = directions[order[i]][0];
        int dy = directions[order[i]][1];
        int nx = x + dx * 2;
        int ny = y + dy * 2;

        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && maze[ny][nx] == '#') {
            maze[ny][nx] = ' ';
            maze[ny - dy][nx - dx] = ' ';
            carveMaze(maze, nx, ny);
        }
    }
}

int findPath(char maze[SIZE][SIZE], int x, int y, int *steps) {
    // Marca el camino con *
    if (maze[y][x] == 'S') {
        printf("¡Llegaste a la salida!\n");
        return 1;
    } else if (maze[y][x] == ' ') {
        maze[y][x] = '*'; // Marca el camino recorrido con *
        (*steps)++;
        printMaze(maze); // Imprime el laberinto después de cada movimiento
        usleep(300000); // Pequeño retraso para visualizar el movimiento
        
        // Revisa en las cuatro direcciones posibles
        if (findPath(maze, x + 1, y, steps) ||
            findPath(maze, x - 1, y, steps) ||
            findPath(maze, x, y + 1, steps) ||
            findPath(maze, x, y - 1, steps)) {
            return 1;
        }
        
        // Si ninguna dirección lleva a la salida, marca como visitado sin salida
        maze[y][x] = '#';
        (*steps)--;
        
        usleep(300000); // Pequeño retraso para visualizar el movimiento
    }
    return 0;
}

int main() {
    char maze[SIZE][SIZE];

    initMaze(maze);

    maze[0][1] = 'E'; // Entrada 
    maze[SIZE - 1][SIZE - 2] = 'S'; // Salida 

    maze[1][1] = ' '; // Inicializa el punto de partida para el algoritmo
    
    srand(time(NULL));

    carveMaze(maze, 1, 1);

    int steps = 0;
    printf("Laberinto inicial:\n");
    printMaze(maze);


    findPath(maze, 1, 1, &steps);

    
    printMaze(maze);
    printf("\n");

    printf("Laberinto resuelto con %d pasos:\n", steps);

    return 0;
}

