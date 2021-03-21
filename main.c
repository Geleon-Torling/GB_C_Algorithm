#include <stdio.h>
#include <string.h>
#include <math.h>


#define _REVERSE_       /*включаем ветку с реверсированием массива. если эта ветка не определена, то будет ветка через инвертирование*/


void fBubbleSort(int *pArray, int iArraySize);
void fTPK(void);

void fPrintArrayI(int *pArray, int iArraySizeX, int iArraySizeY);
void fPrintArrayF(float *pArray, int iArraySizeX, int iArraySizeY);


inline int fTPKCalculate(float fX);
int fTPKReverse(float *pArray, int iSize);
int fTPKInvert(float *pArray, int iSize);

int main()
{
/*
    1. Реализовать пузырьковую сортировку двумерного массива например, массив
    1,9,2
    5,7,6
    4,3,8
    должен на выходе стать
    1,2,3
    4,5,6
    7,8,9
*/
    int aiArray[3][4] = {{1,9,2,10},{5,7,6,11},{4,3,8,12}};

    printf("Current Array Before Sorting:\n");
    fPrintArrayI((int*)aiArray,3,4);
    fBubbleSort((int*)aiArray,3*4);
    printf("\nCurrent Array After Sorting:\n");
    fPrintArrayI((int*)aiArray,3,4);
    printf("\n");

/*
    2. Описать подробную блок-схему алгоритма Трабба-Прадо-Кнута
    1 - запросить у пользователя 11 чисел и записать их в последовательность П
    2 - инвертировать последовательность П
    3 - для каждого элемента последовательности П произвести вычисление по формуле sqrt(fabs(Х)) + 5 * pow(Х, 3)
            и если результат вычислений превышает 400 - проинформировать пользователя.

    3. Реализовать алгоритм Трабба-Прадо-Кнута в коде на языке С
*/

    fTPK();

    return 0;
}

void fBubbleSort(int *pArray,int iArraySize)
{
    if(iArraySize <= 1)
        return;

    int iRight  = iArraySize;
    int iBuffer;

    for(int i = 0; i < iRight - 1; i ++)
    {
        if(pArray[i] > pArray[i+1])
        {
            iBuffer = pArray[i];
            pArray[i] = pArray[i+1];
            pArray[i+1] = iBuffer;
        }
        if(i == iRight - 2) // сдвигаем краницу и перезапускаем цикл
        {
            i = -1; // при переходе цикл увеличит занчение на 1, и таким образом получим нулевой индекс
            iRight --;
        }
    }
}

// Вспомогательная функция вывода массива на экран (версия для int)
void fPrintArrayI(int *pArray, int iArraySizeX, int iArraySizeY)
{
    int j = 1;

    for(int i = 0; i < iArraySizeX * iArraySizeY; i ++)
    {
        printf(" %3d ",pArray[i]);

        if(j == iArraySizeY)
        {
            printf("\n");
            j = 0;
        }
        j ++;
    }
}

// реализация математической части
int fTPKCalculate(float fX)
{
    float fRes;

    fRes = sqrt(fabs(fX)) + 5 * pow(fX, 3);

    return fRes;
}

// Вспомогательная функция вывода массива на экран (версия для float)
void fPrintArrayF(float *pArray, int iArraySizeX, int iArraySizeY)
{
    int j = 1;

    for(int i = 0; i < iArraySizeX * iArraySizeY; i ++)
    {
        printf(" %3f ",pArray[i]);

        if(j == iArraySizeY)
        {
            printf("\n");
            j = 0;
        }
        j ++;
    }
}

#ifdef _REVERSE_
// реверсирует массив
int fTPKReverse(float *pArray, int iSize)
{
    float *fTemp;
    int j = iSize - 1;

    if(iSize < 2)
        return 0;

    if(pArray == 0)
        return 0;

    // подготовка временного массива
    fTemp = (float*)malloc(sizeof(float)*iSize);

    if(fTemp == 0)
        return 0;

    // реверсируем массив
    for(int i = 0; i < iSize; i ++)
    {
        fTemp[i] = pArray[j];
        j --;
    }

    memcpy((void*)pArray,(void*)fTemp,sizeof(float)*iSize);

    return 1;
}
#else
// инвертирует значения в масиве
// так как побитовая операция инвертирования не может применятся к числам с точкой, все числа будут преобразованы к типу int
int fTPKInvert(float *pArray, int iSize)
{
    int iTemp;

    if(iSize < 2)
        return 0;

    if(pArray == 0)
        return 0;

    for(int i = 0; i < iSize; i ++)
    {
        iTemp = pArray[i];
        iTemp = ~iTemp;
        pArray[i] = iTemp;
    }

    return 1;
}
#endif

// реализация алгоритма Трабба-Прадо-Кнута
void fTPK(void)
{
    float afArray[11];

    printf("trabb-pardo-knuth algorithm.\n");
    printf("Please enter 11 numbers:\n");

    for(int i = 0; i < 11; i ++)
    {
        printf("%2d : ", i + 1);
        scanf("%f",&afArray[i]);
    }
    printf("\n");

    printf("You are enter the following numbers: \n");
    fPrintArrayF(afArray,1,11);

/*
    в задаче говрится что необходимо инвертировать последовательность.
    такую формулировку можно опнимать как инвертирование и реверсирование
    (в интернете в описании этого алгоритма речь идет всегда о реверсировании послеовательности.
    ради спортивного интереса базача будет решена двумя способами - с инветированием каждого элемента,
    а так же с рверсированием массива
*/

    // готовим временыые массивы
    float afTempArray[11];
    memcpy((void*)afTempArray,(void*)afArray,sizeof(float)*11);

#ifdef _REVERSE_    /*решение через реверсирование массива */
    if(fTPKReverse(afTempArray,11) == 0)
    {
        printf("memory allocation error\n");
        return;
    }
    printf("After Reversing: \n");
#else               /*решение через инвертирвоание массива */
    if(fTPKInvert(afTempArray,11) == 0)
    {
        printf("memory allocation error\n");
        return;
    }
    printf("After Inverting: \n");
#endif


    // ваведем массив в текущей версии
    fPrintArrayF(afTempArray,1,11);

    float fTemp;

    for(int i = 0; i < 11; i ++)
    {
        fTemp = fTPKCalculate(afTempArray[i]);
        if(fTemp > 400)
        {
            printf("Number %4f after calculat is %4f , and larger than 400 \n", afArray[i], fTemp);
        }
    }
}
