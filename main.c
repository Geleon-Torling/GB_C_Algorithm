/*

    1.) Написать программу, которая определяет, является ли введенная скобочная последовательность правильной.
    Примеры правильных скобочных выражений: (), ([])(), {}(), ([{}]), неправильных — )(, ())({), (, ])}), ([(]) для скобок вида [],(),{}.
    Входные данные: Указатель на массив char.
    Выходные данные: bool. True, если скобочная последовательность правильная, False если неправильная.
    Примеры:
    (2+(2*2)) - true
    {2/{5*(4+7)] - false

    2.) Создать функцию, копирующую односвязный список (без удаления первого списка).
    Входные данные: OneLinkList* from - начало списка с которого производится копирование, OneLinkList* to - начало списка в которое производится копирование
    Выходные данные: void

    3.) Реализуйте алгоритм, который определяет, отсортирован ли связный список.
    Входные данные: OneLinkList* lst - начало списка с которого производится проверка отсортированности
    Выходные данные: Bool
    Результатом работы должен стать один файл с кодом на языке С, содержащий функцию main и функции, соответствующие заданиям.

*/

#include <stdio.h>
#include <stdlib.h>


// тип bool
#define bool int
#define true 1
#define false 0


struct sStackNode
{
    struct sStackNode *pNext;
    char cData;
};

struct sStackNode *pStackHead   = 0;
int iStackSize  = 0;

int fPushStack(char cData);
char fPopStack(void);

void fDeleteStack(void);

bool fCheckBraces(char *pArray);

struct OneLinkList
{
    struct OneLinkList *pNext;
    int     iElement;
};

struct OneLinkList *pSecondList = 0;          // список для второго задания
struct OneLinkList *pSecondListCopy = 0;      // список для второго задания (копия)

int fListAdd(int iNum);
int fListGet(int *pNum);
int fListDelete(struct OneLinkList *pList);
void fListPrint(struct OneLinkList *pList);

void fListCopy(struct OneLinkList *from, struct OneLinkList* to);

int fListSortCheck(struct OneLinkList *pList);


int main()
{
/*
    1.) Написать программу, которая определяет, является ли введенная скобочная последовательность правильной.
    Примеры правильных скобочных выражений: (), ([])(), {}(), ([{}]), неправильных — )(, ())({), (, ])}), ([(]) для скобок вида [],(),{}.
    Входные данные: Указатель на массив char.
    Выходные данные: bool. True, если скобочная последовательность правильная, False если неправильная.
*/

    char cStringArray[] = "[2/{5*(4+7)}]";
//    char cStringArray[] = "[2/{5*(4+7})]";
    bool bResult = false;

    bResult = fCheckBraces(cStringArray);
    printf(cStringArray);
    printf("\nResult of checkin is : ");
    if(bResult == false)
        printf("not correct \n");
    else
        printf("correct \n");

    fDeleteStack();



/*
    2. Создать функцию, копирующую односвязный список (без удаления первого списка).
*/

    printf("Current List : ");
    fListPrint(pSecondList);

    fListAdd(1);
    fListAdd(2);
    fListAdd(3);
    fListAdd(4);
    fListAdd(5);
    fListAdd(6);
    fListAdd(7);
    fListAdd(8);
    fListAdd(9);
    fListAdd(10);

    printf("List after adding : ");
    fListPrint(pSecondList);

    pSecondListCopy = (struct OneLinkList*)malloc(sizeof(struct OneLinkList));

    fListCopy(pSecondList,pSecondListCopy);
    printf("Copy of List : ");
    fListPrint(pSecondListCopy);

    int iNum = 0;
    printf("Getting all number : ");
    while(fListGet(&iNum) == 1)
    {
        printf("%2d ",iNum);
    }
    printf("\n");
    printf("List after rmoving : ");
    fListPrint(pSecondList);
    printf("Copy of List after rmoving : ");
    fListPrint(pSecondListCopy);

    // освобождение памяти
    if(fListDelete(pSecondList) == 0)
    {
        printf("Release memory Error\n");
        return 0;
    }else
        pSecondList = 0;

    if(fListDelete(pSecondListCopy) == 0)
    {
        printf("Release memory Error\n");
        return 0;
    }else
        pSecondListCopy = 0;

/*
    3. Реализуйте алгоритм, который определяет, отсортирован ли связный список.
*/

    int iWay = 0;

    fListAdd(5);
    fListAdd(3);
    fListAdd(3);
    fListAdd(2);
    fListAdd(1);

    printf("List for cheking : ");
    fListPrint(pSecondList);

    // проверка на упорядоченность
    iWay = fListSortCheck(pSecondList);
    switch(iWay)
    {
    case 0:
        printf("Array is UNSORTED\n");
        break;
    case 1:
        printf("Array sorted in DISCENDING order.\n");
        break;
    case 2:
        printf("Array sorted in ASCENDING order.\n");
        break;
    case 3:
        printf("Array conteined IDENTICAL number\n");
        break;
    default:
        printf("unknown response\n");
        break;
    }

    // освобождение памяти
    if(fListDelete(pSecondList) == 0)
    {
        printf("Release memory Error\n");
        return 0;
    }else
        pSecondList = 0;

    return 0;
}

// добавить данные в стек
int fPushStack(char cData)
{
    struct sStackNode *pTemp = 0;

    if(pStackHead == 0)
    {
        pStackHead = (struct sStackNode*)malloc(sizeof(struct sStackNode));
        if(pStackHead == 0)
        {
            printf("Memory Allocation Error! \n");
            return 0;
        }
        pStackHead ->cData = cData;
        pStackHead ->pNext = 0;

        iStackSize ++;

        return 1;
    }

    pTemp = (struct sStackNode*)malloc(sizeof(struct sStackNode));
    if(pTemp == 0)
    {
        printf("Memory Allocation Error! \n");
        return 0;
    }
    pTemp ->cData = cData;
    pTemp ->pNext = pStackHead;

    pStackHead = pTemp;
    iStackSize ++;

    return 1;
}

// получить данные из стека
char fPopStack(void)
{
    char cBuffer;
    struct sStackNode *pTempNode = 0;

    if(pStackHead == 0)
        return 0;

    cBuffer = pStackHead ->cData;

    if(pStackHead ->pNext == 0)
    {
        free(pStackHead);
        pStackHead = 0;
        iStackSize --;
        return cBuffer;
    }

    pTempNode = pStackHead ->pNext;
    free(pStackHead);
    iStackSize --;
    pStackHead = pTempNode;

    return cBuffer;
}

// удалить стек
void fDeleteStack(void)
{
    struct sStackNode *pTemp = 0;
    struct sStackNode *pTemp1 = 0;

    if(pStackHead == 0)
        return;

    pTemp = pStackHead;
    do
    {
        pTemp1 = pTemp ->pNext;
        free(pTemp);
        pTemp = pTemp1;

    }while(pTemp != 0);

    pStackHead = 0;
    iStackSize = 0;

    return;
}

// проверка правильности расстановки скобок
bool fCheckBraces(char *pArray)
{
    int i = 0;
    char cTemp = 0;
    char cTemp2 = 0;
    int iBracesCounter = 0;

    while(pArray[i] != '\0')
    {
        cTemp = pArray[i];

        if((cTemp == '[') || (cTemp == '(') || (cTemp == '{'))
        {
            fPushStack(cTemp);
            iBracesCounter ++;
        }
        else if((cTemp == ']') || (cTemp == ')') || (cTemp == '}'))
        {
            cTemp2 = fPopStack();
            switch(cTemp2)
            {
            case '[':
                if(cTemp == ']')
                    iBracesCounter--;
                break;
            case '(':
                if(cTemp == ')')
                    iBracesCounter--;
                break;
            case '{':
                if(cTemp == '}')
                    iBracesCounter--;
                break;
            default:
                fDeleteStack();
                return false;
            }
        }

        i++;
    }

    if(iBracesCounter != false)
        return false;

    return true;
}


// добавить в список (вернет 0 если неудачно, иначе 1)
int fListAdd(int iNum)
{
    struct OneLinkList *pTemp = 0;

    pTemp = (struct OneLinkList*)malloc(sizeof(struct OneLinkList));
    if(pTemp == 0)
        return 0;

    pTemp ->pNext = 0;
    pTemp ->iElement = iNum;

    // если списка еще нет
    if(pSecondList == 0)
    {
        pSecondList = pTemp;
        return 1;
    }

    pTemp ->pNext = pSecondList;
    pSecondList = pTemp;

    return 1;
}

// получить из списка (возврат через указатель)(вернет 0 если неудачно, иначе 1)
int fListGet(int *pNum)
{
    struct OneLinkList *pTemp = 0;

    if(pNum == 0)
        return 0;
    if(pSecondList == 0)
        return 0;

    // если список состоит из одного элемента
    if(pSecondList ->pNext == 0)
    {
        *pNum = pSecondList ->iElement;
        fListDelete(pSecondList);
        pSecondList = 0;
        return 1;
    }

    // получаем предпоследний элемент
    pTemp = pSecondList;
    while(pTemp ->pNext ->pNext != 0)
    {
        pTemp = pTemp ->pNext;
    }
    *pNum = pTemp ->pNext ->iElement;
    fListDelete(pTemp ->pNext);
    pTemp ->pNext = 0;

    return 1;
}

// удалить список (вернет 0 если неудачно, иначе 1)
int fListDelete(struct OneLinkList *pList)
{
    struct OneLinkList *pTemp = 0;
    struct OneLinkList *pTemp1 = 0;

    if(pList == 0)
        return 1;

    pTemp = pList;
    do
    {
        pTemp1 = pTemp ->pNext;
        free(pTemp);
        pTemp = pTemp1;

    }while(pTemp != 0);

    return 1;
}

// вывести список
void fListPrint(struct OneLinkList *pList)
{
    struct OneLinkList *pTemp = 0;

    if(pList == 0)
    {
        printf("{List is Empty}\n");
        return;
    }

    pTemp = pList;
    printf("{");
    do
    {
        printf("%2d ",pTemp ->iElement);
        pTemp = pTemp ->pNext;
    } while(pTemp != 0);
    printf("}\n");
}

// копируем список
void fListCopy(struct OneLinkList* from, struct OneLinkList* to)
{
    if(from == 0)
        return;
    if (to == 0)
        return;

    //Копируем первый элемент
    to ->pNext = 0;
    to ->iElement = from ->iElement;

    // если список был из одного элемента, то выходим...
    if (from->pNext == 0)
        return;

    // далее копируем все что осталось.
    while(from ->pNext != 0)
    {
        to ->pNext = (struct OneLinkList*)malloc(sizeof(struct OneLinkList));
        if(to ->pNext == 0)
        {
            return;
        }
        from = from->pNext;
        to = to ->pNext;
        to ->pNext = 0;
        to ->iElement = from ->iElement;
    }
}

// проверка списка на упорядоченность (0 - не отсортировано, 1 - отсортирован по убыванию, 2 - отсортирован по возрастанию, 3 - все значения одинаковые)
int fListSortCheck(struct OneLinkList *pList)
{
    int iWay        = 0;    // флаг направления
    int iCurrentWay = 0;    // флаг направления
    struct OneLinkList *pCursor = 0;

    if(pList == 0)
        return 0;
    if(pList ->pNext == 0) /*список из одного элемента считаем отсортированым*/
        return 1;

    pCursor = pList;
    while(pCursor ->pNext != 0)
    {
        iCurrentWay = pCursor ->iElement - pCursor ->pNext ->iElement;

        if(iCurrentWay > 0)
        {
            if(iWay == 0)   /*попался первый элемент, который больше предидущего*/
            {
                iWay = 1;
                pCursor = pCursor ->pNext;
                continue;
            }
            if(iWay < 1)    /*измение направления, массив не отсортирован*/
                return 0;
        }
        else if(iCurrentWay < 0)
        {
            if(iWay == 0)   /*попался первый элемент, который меньше предидущего*/
            {
                iWay = -1;
                pCursor = pCursor ->pNext;
                continue;
            }
            if(iWay > 1)    /*измение направления, массив не отсортирован*/
                return 0;
        }

        pCursor = pCursor ->pNext;
    }

    if(iWay > 0)        /*отсортирован по убыванию*/
        return 1;
    else if(iWay < 0)   /*отсортирован по возорстанию*/
        return 2;
    else return 3;
}
