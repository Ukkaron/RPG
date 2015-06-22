#include <stdlib.h>
#include <time.h>

enum EntityTypes { HERO, MONSTER, NONE };

class cell
{
    public: bool pit = 0;
    public: bool rock = 0;
    public: struct tEntity
    {
        EntityTypes Type;
        int EntityID;
    } EntityType;
};

//  Функция генерации уровня. Принимает указатель на массив клеток и размер массива. Внутри случайным образом генерируется
// препятствия общим количеством room_size / 2. Препятствия могут быть 2-х типов. Яма и скала. Вид препятствия определяется случайным образом.
// Препятствия не генерируется в четырех левых верхних клетках никогда, для устранения случая полной блокировки выхода игроком.
// Начало координат в верхнем левом углу.
void room_generator (cell *ptr, int n)
{
    int i;
    int x, y; // Переменные координаты
    bool dice; // Переменная кубика
    for(i=0; i<(n*0.75); i++)
    {
        x = rand() % (n-2) + 2;
        y = rand() % (n-2) + 2;
        dice = rand() % 2;
        if(dice == 1)
            (*(ptr + y*x + x)).pit = 1;
        else
            (*(ptr + y*x + x)).rock = 1;
    }
    for(i = 0; i < 4; i++)
    {
        do
        {
            x = rand() % n;
            y = rand() % n;

        }while((*(ptr + y*x + x)).pit == true || (*(ptr + y*x + x)).rock == true || (*(ptr + y*x + x)).EntityType.Type != NONE);
        (*(ptr + y*x + x)).EntityType.Type = MONSTER;
        (*(ptr + y*x + x)).EntityType.EntityID = i + 1;
    }
}
