#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
    int n;
    int k = 0;
    int f = 0;
    int t = 1;
    int l = 0;
    bool flag = false;
    bool prov = false;
    scanf_s("%d", &n);
    int* arr = (int*)malloc(n * n * sizeof(int));     //Создаем массив соразмерностью n*n (n^2)

    for (int i = 0; i < n; i++) {
        printf("%d:", i);

        for (int j = 0; j < n; j++) {
            scanf_s("%d", (arr + i * n + j));         //Создаем матрицу смежности, путем проверки каждого столбца и строки в массиве n*n
        }
    }
    printf("\n");

    for (int i = 0; i < n; i++) {                    //Считываем количество строк

        for (int j = 0; j < n; j++) {                //Считываем количество столбцов 

            if ((i == j) && (arr[i * n + j] != 0)) {    //проверка диагонали, чтобы убедиться, не будет ли в графе самосвязанных вершин
                prov = true;
            }

            if (arr[i * n + j] != arr[j * n + i]) {     //проверка симметричности относительно диагонали, чтобы убедиться, что гра будет неорентированным
                prov = true;
            }

            if ((arr[i * n + j] != 0) && (arr[i * n + j] != 1)) {      //проверка либо отсутвия ребра между вершинами, либо наличия лишь 1 таковой, т.к цикл простой
               
                prov = true;
            }

            if (arr[i * n + j] == 1) {      //проверка того, что из каждой вершины выходит ровно 2 ребра
                k++;
            }

            if (k > 2) {                   //Программа будет работать при условии, что каждая вершина будет именть минимум 2 ребра
                prov = true;
            }
        }
        k = 0;
    }

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if ((arr[k * n + j] == 1) && (j != t) && (flag == false)) {     //проверка обходом. Проверяем каждый элемент на связанность с другими следующими. 
                t = k;                                                      //Чтобы не проверять предыдущий элемент вводим новую переменную t, которая запоминает предыдущий
                k = j;                                                      //графа. Проверяем параллельно на простой цикл, еслиэто не так то flag==true
                flag = true;
            }
        }
        flag = false;

        if ((k == 0) && (i != n - 1)) {                                     //Если мы пришли к вершине, откуда вернулись, необходимо проверить остались ли еще непроверенные вершины
            prov = true;
        }

        if ((i == n - 1) && (k != 0)) {                                     //Проверяем, что мы пришли в начало отсчета
            prov = true;
        }
    }
    if (prov == false) {
        printf("Простой цикл");                                             //При невыполнении каких-либо условий выше выводим на экран "Непростой цикл" 
    }
    else
        printf("Непростой цикл");

 // визуализация //

    FILE* file;

    if ((file = fopen("Dot_file.txt", "w")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    fprintf(file, "graph G{\n");

    for (int i = 0; i < n; i++) {

        for (int j = 0; j <= i; j++) {

            if (arr[i * n + j] != 0) {

                for (int g = 0; g < arr[i * n + j]; g++) {
                    fprintf(file, "%d -- %d;\n", (i + 1), (j + 1));
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((arr[i * n + j]) == 0) {
                l++;
            }
        }
        if (l == n) {
            fprintf(file, "%d;\n", (i + 1));
        }
        l = 0;
    }
        
    fprintf(file, "}");
    fclose(file);
    system("dot C:\\Users\\User\\Desktop\\Алгоритмы\\MyHomework2V2\\Homework2\\Homework2\\Dot_file.txt -Tbmp -o Dot_file.bmp");
    system("rundll32 \"%ProgramFiles%\\Windows Photo Viewer\\PhotoViewer.dll\", ImageView_Fullscreen C:\\Users\\User\\Desktop\\Алгоритмы\\MyHomework2V2\\Homework2\\Homework2\\Dot_file.bmp");
    return (0);
}
