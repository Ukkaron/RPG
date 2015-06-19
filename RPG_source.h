#include <stdlib.h>
#include <time.h>

class cell
{
    public: bool pit = 0;
    public: bool rock = 0;
};

//  Функция генерации уровня. Принимает указатель на массив клеток и размер массива. Внутри случайным образом генерируется
// препятствия общим количеством room_size / 2. Препятствия могут быть 2-х типов. Яма и скала. Вид препятствия определяется случайным образом.
// Препятствия не генерируется в четырех левых верхних клетках никогда, для устранения случая полной блокировки выхода игроком.
// Начало координат в верхнем левом углу.
void room_generator (int n, cell platformsp[][n]) // Ошибка "use of parameter 'n' outside function body"
{
    int i;
    int x, y; // Переменные координаты
    bool dice; // Переменная кубика
    for(i=0; i<(n/2); i++)
    {
        x = rand() % (n-2) + 2;
        y = rand() % (n-2) + 2;
        dice = rand() % 2;
        if (dice = 1)
           platforms[x][y].pit = 1;
        else
           platforms[x][y].rock = 1;
    }
}
