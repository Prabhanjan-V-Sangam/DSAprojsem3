#include <stdio.h>
#include <stdlib.h>

#define  MAX_VERTICES 26  // Assuming the vertices are represented by characters 'A' to 'Z'
#define INF 999
 int numVertices;
 int matrix[ MAX_VERTICES][ MAX_VERTICES]={0};
int matrixB[ MAX_VERTICES][ MAX_VERTICES];
int arraypath[MAX_VERTICES];
int charToIndex(char vertex) {
    return vertex - 'A';
}


char intToChar(int number) {
    if (number >= 1 && number <= 26) {
        return 'A' + number - 1;
    } else {
        // Handle the case where the number is out of range
        return '\0'; // You can return some default value or handle it differently based on your requirements
    }
}

void floydsAlgorithm(int matrix[ MAX_VERTICES][ MAX_VERTICES], int numVertices) {
    // Applying Floyd's Algorithm to update the matrix
    for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (matrix[i][k] != INF && matrix[k][j] != INF && matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }
}


void shortestPath(int matrix[ MAX_VERTICES][ MAX_VERTICES], int numVertices, int startVertex, int endVertex) {

    printf("%d %d\n",startVertex,endVertex);

    if (startVertex >= numVertices ||  endVertex >= numVertices) {
        printf("Invalid vertices.\n");
        return;
    }

    if (matrix[startVertex][endVertex] == INF) {
        printf("There is no path from %c to %c.\n", startVertex, endVertex);
        return;
    }

    printf("Shortest path from %c to %c: %c", startVertex, endVertex, startVertex);
   printf("%d\n",matrix[startVertex][endVertex]);
    printf("\n");
}


void orginalFloyd(){
 printf("\nprint matrix[][]\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (matrix[i][j] == INF) {
                printf("INF\t");
            } else {
                printf("%d\t", matrix[i][j]);
            }
        }
        printf("\n");
    }
}


void printFloyd(){
 printf("\nprinting after Floyds algo\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (matrix[i][j] == INF) {
                printf("INF\t");
            } else {
                printf("%d\t", matrix[i][j]);
            }
        }
        printf("\n");
    }
}


void bellmanFordAlgorithm(int matrix[ MAX_VERTICES][ MAX_VERTICES], int numVertices, char sourceVertex) {
    int sourceIndex = sourceVertex - 'A';

    int distance[ MAX_VERTICES];
    int predecessor[ MAX_VERTICES];

    // Initialize distance and predecessor arrays
    for (int i = 0; i < numVertices; i++) {
        distance[i] = INF;
        predecessor[i] = -1;
    }

    distance[sourceIndex] = 0;

    // Relax edges repeatedly
    for (int k = 0; k < numVertices - 1; k++) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (matrix[i][j] != INF && distance[i] != INF && distance[i] + matrix[i][j] < distance[j]) {
                    distance[j] = distance[i] + matrix[i][j];
                    predecessor[j] = i;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (matrix[i][j] != INF && distance[i] != INF && distance[i] + matrix[i][j] < distance[j]) {
                printf("Graph contains a negative weight cycle.\n");
                return;
            }
        }
    }
     printf("Shortest paths from %c using Bellman-Ford Algorithm:\n", sourceVertex);
    for (int i = 0; i < numVertices; i++) {
        printf("To %c: Distance = %d\tPath = %c", i + 'A', distance[i], sourceVertex);
        int predecessorIndex = i;
        while (predecessor[predecessorIndex] != -1) {
            printf(" <- %c", predecessor[predecessorIndex] + 'A');
            predecessorIndex = predecessor[predecessorIndex];
        }
        printf("\n");
    }

}


void copy(int source[MAX_VERTICES][MAX_VERTICES], int destination[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

void Managefile()
{
    FILE* file = fopen("plan_text.txt", "r");
    if (file == NULL) {
        perror("Error opening the file");

    }

    fscanf(file, "%d", &numVertices);

    // Ensure the number of vertices is within the allowed range
    if (numVertices < 0 || numVertices > MAX_VERTICES) {
        printf("Invalid number of vertices in the input file.\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Initialize the matrix with large values (representing infinity)
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            matrix[i][j] = (i == j) ? 0 : INF;
        }
    }

    char start, end;
    int weight;

    // Read edge data from the file and update the matrix
    while (fscanf(file, " %c %c %d", &start, &end, &weight) == 3) {
        // Assuming the file contains a character, a character, and an integer per line
        int startIndex = charToIndex(start);
        int endIndex = charToIndex(end);

        if (startIndex >= 0 && startIndex < numVertices && endIndex >= 0 && endIndex < numVertices) {
            matrix[startIndex][endIndex] = weight;
        } else {
            printf("Invalid vertices in the input file.\n");
            fclose(file);
            return EXIT_FAILURE;
        }
    }


    // Close the file after reading
    fclose(file);

}

void printmatrix(int a[MAX_VERTICES][MAX_VERTICES])
{
   printf("\n:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (a[i][j] == INF) {
                printf("INF\t");
            } else {
                printf("%d\t", a[i][j]);
            }
        }
        printf("\n");
    }
}


void Floys2Algo(int matrix[MAX_VERTICES][MAX_VERTICES], int numVertices, int arraypath[MAX_VERTICES], int c, int d) {
    int m = 0;
    // Applying Floyd's Algorithm to update the matrix
    for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (matrix[i][k] != INF && matrix[k][j] != INF && matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    if (c== i && d == j) {
                        arraypath[m] = k;
                        printf("%d \n",k);
                        m++;
                    }
                }
            }
        }
    }
}



int main() {
/////1.///////////////////////////////////////////////////////////////////////
    // manage  file
     Managefile();
     copy(matrix, matrixB);
    // Display the original matrix (optional)
printmatrix(matrix);
// Display the copied matrix
printmatrix(matrixB);


    // Apply Floyd's Algorithm to update the matrix
    floydsAlgorithm(matrix, numVertices);

    // Display the updated matrix
   printFloyd();
    char a,b;

    printf("Tell me form where u want to travel to what place\n");
    scanf("%c%c%c",&a,&b);
    int c = a - 'A' ;
    int d = b - 'A' ;

    shortestPath(matrix, numVertices,c ,d );


     printf("Tell me the place of incident detection\n");
    scanf(" %c %c", &a, &b);
     int x = a - 'A' ;
     int y = b - 'A' ;
printf("Lolo \n %d %d \n",c,d);
    // Copy matrix
    copy(matrixB, matrix);


    matrix[x][y] = INF;

    // Print matrix after incident detection
    printmatrix(matrix);

    // Apply Floyd's Algorithm after incident detection
    floydsAlgorithm(matrix, numVertices);
// Display the updated matrix
    printFloyd(matrix);



printf("Tell me the place of u want shortest lpath\n");
    scanf("%c%c",&b,&a);
 bellmanFordAlgorithm(matrix, numVertices, a);

 //////2.Determine the direction of flow of vehicle//////////////////////////////////////
  printf("Tell me form where u want to travel to what place to find the vehicle direction\n");
    scanf("%c%c",&a,&b);
    int  m = a - 'A' ;
     int n = b - 'A' ;
    copy(matrixB, matrix);
   //use belman ford shit
    char f;
    printf("\n%c -> ", a);
    for (int i = 0; i < numVertices && arraypath[i] != INF; i++) {
        c = arraypath[i] + 1;  // Adding 1 to convert back to character
        printf(" %c -> ", c + 'A' - 1);  // Convert index back to character
    }
    printf(" %c\n", b);

    return 0;
}
