#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 50

using namespace std;

int changes_counter;
int count_4;
int count_5;
bool found_0 = true;
int wall_counter;
int w, v; // Counter
int y, x;
int arr[5][N][N] = {};
int i, j, k; // MORE COUNTERS, FOR COUNTER'S GOD !!!

void grider(int y1, int x1, int k) // Заполнитель
{

    if(arr[4][y1][x1+1] == 0)
    {
        arr[4][y1][x1+1] = k;
        grider(y1, x1+1, k);
    }
    if(arr[4][y1+1][x1] == 0)
    {
        arr[4][y1+1][x1] = k;
        grider(y1+1, x1, k);
    }
    if(arr[4][y1][x1-1] == 0)
    {
        arr[4][y1][x1-1] = k;
        grider(y1, x1-1, k);
    }
    if(arr[4][y1-1][x1] == 0)
    {
        arr[4][y1-1][x1] = k;
        grider(y1-1, x1, k);
    }
}

int main()
{
    srand(time(NULL));

    for(i=0; i<N; i++) // Генератор : этап первый
    {
        for(j=0; j<N; j++)
        {
            y = rand() % 100 + 1;
            if(y >= 56)
                arr[0][i][j] = 1;
        }
    }

    for(i=0; i<N; i++)
        arr[0][i][0] = 1;

    for(i=0; i<N; i++)
        arr[0][i][N-1] = 1;

    for(i=0; i<N; i++)
        arr[0][0][i] = 1;

    for(i=0; i<N; i++)
        arr[0][N-1][i] = 1;

    for(k=0; k<4; k++) // Генератор : этап 2-5
    {

        for(i=0; i<N; i++)
            arr[k][i][0] = 1;

        for(i=0; i<N; i++)
            arr[k][i][N-1] = 1;

        for(i=0; i<N; i++)
            arr[k][0][i] = 1;

        for(i=0; i<N; i++)
            arr[k][N-1][i] = 1;

        for(i=1; i<N-1; i++)
            for(j=1; j<N-1; j++)
            {
                wall_counter = 0;
                for(w=-1; w<2; w++)
                    for(v=-1; v<2; v++)
                    {
                        if(arr[k][i+w][j+v] == 1)
                            wall_counter++;
                    }
                if(wall_counter >= 5)
                    arr[k+1][i][j] = 1;
                else
                    arr[k+1][i][j] = 0;
            }

            for(i=0; i<N; i++)
                arr[k+1][i][0] = 1;

            for(i=0; i<N; i++)
                arr[k+1][i][N-1] = 1;

            for(i=0; i<N; i++)
                arr[k+1][0][i] = 1;

            for(i=0; i<N; i++)
                arr[k+1][N-1][i] = 1;

    }

    for(i=0; i<N; i++) // Вывод
            {
                for(j=0; j<N; j++)
                {
                    cout << arr[4][i][j];
                }
                cout << endl;
            }

    while(found_0 == true) // Очищение верхней части
    {
        found_0 = false;

        for(i=0; i<N; i++)
        {
            for(j=0; j<N; j++)
            {
                if(arr[4][i][j] == 0)
                {
                    arr[4][i][j] = 4;
                    found_0 = true;
                }
                if(found_0 == true)
                    break;
            }
            if(found_0 == true)
                break;
        }

        grider(i, j, 4);

        found_0 = false;

        for(i=0; i<N; i++)
        {
            for(j=0; j<N; j++)
            {
                if(arr[4][i][j] == 0)
                {
                    arr[4][i][j] = 5;
                    found_0 = true;
                }
                if(found_0 == true)
                    break;
            }
            if(found_0 == true)
                break;
        }

        grider(i, j, 5);

        for(i=0; i<N; i++)
            {
                for(j=0; j<N; j++)
                {
                    if(arr[4][i][j] == 4)
                        count_4++;
                    if(arr[4][i][j] == 5)
                        count_5++;
                }
            }

        if(count_4 > count_5)
            for(i=0; i<N; i++)
            {
                for(j=0; j<N; j++)
                {
                    if(arr[4][i][j] == 5)
                        arr[4][i][j] = 1;
                    if(arr[4][i][j] == 4)
                        arr[4][i][j] = 0;
                }
            }
        else
            for(i=0; i<N; i++)
            {
                for(j=0; j<N; j++)
                {
                    if(arr[4][i][j] == 4)
                        arr[4][i][j] = 1;
                    if(arr[4][i][j] == 5)
                        arr[4][i][j] = 0;
                }
            }
    }

    printf("\n\n\n");

    for(i=0; i<N; i++)
        {
            for(j=0; j<N; j++)
            {
                printf("%d", arr[4][i][j]);
            }
            printf("\n");
        }
}
