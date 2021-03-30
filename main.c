#include <stdio.h>

#define QUEUE_SIZE  10

struct sQueueBlock
{
    int iQueue[QUEUE_SIZE];
    int iQueuePriority[QUEUE_SIZE];
    int iPosition;                       // указывает на текущую свободную позицию
    int iCounter;                        // указывает на количество элементов
} sQueue;

/*
 * при ошибке все функции возвращают -1
 * приотитет должен быть > 0. чем цифра больше, тем приоритет ниже
*/
void fQueueInit(void);
int  fQueuePut(int iNum, int iPriority);
int  fQueueGet(void);
void fQueueMove(int iPos);
int  fQueueSeek(int iPriority);

void fQueuePrint(void);


/*
 * работа со стеком
*/

#define STACK_SIZE  10

int iStackArray[STACK_SIZE];
int iStackCursor = 0;

int  fPushStack(int iNum);
int  fPopStack(void);
void fClearStack(void);

/*
 * предобразование числа
*/

void fDECToBIN(int iNum);

int main()
{


/*
    1. Описать очередь с приоритетным исключением
*/

    fQueueInit();

    // (число, приоритет)
    fQueuePut(1,1);
    fQueuePut(2,2);
    fQueuePut(3,3);
    fQueuePut(4,1);
    fQueuePut(5,2);
    fQueuePut(6,3);
    fQueuePut(7,1);
    fQueuePut(8,2);
    fQueuePut(9,3);
//    fQueuePut(10,4);

    fQueuePrint();

    printf("Getting queue: ");
    for(int i = 0; i < 5; i ++)
    {
        printf("%2d ", fQueueGet());
    }

    fQueuePut(100,1);

    printf("\n");

    fQueuePrint();


/*  проверка работы стека

    fClearStack();

    fPushStack(1);
    fPushStack(2);
    fPushStack(3);
    fPushStack(4);
    fPushStack(5);

    printf("Get Data from stack: ");
    for(int i = 0; i < 6; i ++)
    {
        printf("%2d, ",fPopStack());
    }
    printf("\n");

    fClearStack();
*/

/*
    2. Реализовать перевод из десятичной в двоичную систему счисления с использованием стека.
*/

    fDECToBIN(204); /*11001100b*/
    fDECToBIN(25);  /*11001b*/
    fDECToBIN(15);  /*1111b*/


    return 0;
}

// инициализация
void fQueueInit(void)
{
    for(int i = 0; i < QUEUE_SIZE; i ++)
    {
        sQueue.iQueuePriority[i] = 0;
        sQueue.iQueue[i] = 0;
    }

    sQueue.iCounter = 0;
    sQueue.iPosition = 0;
}

// добавить элемент в очередь. возвращает индекс в очереди
int fQueuePut(int iNum, int iPriority)
{
    int iIndex = -1;

    if(sQueue.iCounter == QUEUE_SIZE)
        return -1;

    iIndex = fQueueSeek(iPriority);
    if(iIndex == -1)
        return -1;

    sQueue.iQueue[iIndex] = iNum;
    sQueue.iQueuePriority[iIndex] = iPriority;
    sQueue.iCounter ++;

    return 1;
}

// возвращает элемент. с более высоким приоритетов отдаст раньше
int  fQueueGet(void)
{
    int iBuffer = -1;

    if(sQueue.iCounter == 0)
        return -1;


    iBuffer = sQueue.iQueue[--sQueue.iPosition];
    sQueue.iCounter --;
    sQueue.iQueuePriority[sQueue.iPosition] = 0;
    sQueue.iQueue[sQueue.iPosition] = 0;

    return iBuffer;
}

// сместить элементы (освободить место)
void fQueueMove(int iPos)
{
    if(sQueue.iQueuePriority[iPos] == 0)
        return;

    for(int i = sQueue.iPosition; i > iPos; i --)
    {
        sQueue.iQueuePriority[i] = sQueue.iQueuePriority[i -1];
        sQueue.iQueue[i] = sQueue.iQueue[i -1];
    }
}

// поиск места для вставки
int  fQueueSeek(int iPriority)
{
    if(sQueue.iCounter == QUEUE_SIZE)
        return -1;
    if(iPriority <= 0)
        return -1;

    for(int i = 0; i < QUEUE_SIZE; i ++)
    {
        if(sQueue.iQueuePriority[i] <= iPriority)
        {
            fQueueMove(i);
            sQueue.iPosition ++;
            return i;
        }
    }

    return -1;
}

// вывести очередь
void fQueuePrint(void)
{
    printf("Couter:%d, HeadPosition:%d ,", sQueue.iCounter, sQueue.iPosition);
    printf("{Element,Priority}: ");
    for(int i = 0; i < QUEUE_SIZE; i ++)
    {
        printf("{%d,%d}", sQueue.iQueue[i], sQueue.iQueuePriority[i]);
    }
    printf("\n");
}

// при удачном размещении возвращает пзицию в массиве
int fPushStack(int iNum)
{
    if(iStackCursor == STACK_SIZE)
        return -1;

    iStackArray[iStackCursor] = iNum;
    iStackCursor ++;

    return iStackCursor - 1;
}

int fPopStack(void)
{
    if(iStackCursor == 0)
        return -1;

    return iStackArray[--iStackCursor];
}

// очистка стека
void fClearStack(void)
{
    iStackCursor = 0;
    for(int i = 0; i < STACK_SIZE; i ++)
    {
        iStackArray[i] = 0;
    }
}

// преборазование числа из десятичного в двоичное
void fDECToBIN(int iNum)
{
    int iBuffer = iNum;
    int iSuccess = 1;

    fClearStack();

    do
    {
        fPushStack(iBuffer % 2);
        iBuffer = iBuffer / 2;
        if(iBuffer <= 1)
        {
            fPushStack(iBuffer);
            iSuccess = 0;
        }
    }
    while(iSuccess);

    printf("Result of convertation from %2d (DEC) to BIN is : ", iNum);
    while(1)
    {
        iBuffer = fPopStack();
        if(iBuffer == -1)
            break;

        printf("%d",iBuffer);
    }
    printf("\n");

}
