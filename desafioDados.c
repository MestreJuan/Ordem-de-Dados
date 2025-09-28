#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>

#define VETOR 100000

// Merge

void merge(int vetorFinal[], int inicio, int meio, int fim)
{
    int i, j, k;
    int esquerda = meio - inicio + 1;
    int direita = fim - meio;
    int *vetorEsquerdo, *vetorDireito;

    vetorEsquerdo = malloc(esquerda * sizeof(int)); 
    vetorDireito = malloc(direita * sizeof(int));

    for (i = 0; i < esquerda; i++)
    {
        vetorEsquerdo[i] = vetorFinal[inicio + i];
    }

    for (j = 0; j < direita; j++)
    {
        vetorDireito[j] = vetorFinal[meio + 1 + j];
    }

    i = 0; 
    j = 0; 
    k = inicio;

    while ( i < esquerda && j < direita)
    {
        if (vetorEsquerdo[i] <= vetorDireito[j])
        {
            vetorFinal[k] = vetorEsquerdo[i];
            i++;
        }
        else 
        {
            vetorFinal[k] = vetorDireito[j];
            j++;
        }

        k++;
    }

    while ( i < esquerda )
    {
        vetorFinal[k] = vetorEsquerdo[i];
        i++;
        k++;
    }

    while ( j < direita )
    {
        vetorFinal[k] = vetorDireito[j];
        j++;
        k++;
    }

    free(vetorDireito);
    free(vetorEsquerdo);
}

void mergeSort(int vetorFinal[], int inicio, int fim)
{
    int meio;

    if (inicio < fim)
    {
        meio = inicio + (fim - inicio) / 2;

        mergeSort(vetorFinal, inicio, meio);
        mergeSort(vetorFinal, meio + 1, fim);
        merge(vetorFinal, inicio, meio, fim);
    }
}


// cabou o merge

// Heap

void troca(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int pai(int i)
{
    return (i - 1) / 2;
}

int esquerdo(int i)
{
    return ( 2 * i + 1);
}

int direito(int i)
{
    return ( 2 * i + 2);
}

void criarHeap(int vetorFinal[])
{
    int i, atual;
    
    for ( i = 1; i < VETOR; i++)
    {
        atual = i;

        while (atual > 0 && vetorFinal[atual] > vetorFinal[pai(atual)])
        {
            troca(&vetorFinal[atual], &vetorFinal[pai(atual)]);
            atual = pai(atual);
        }
    }
}

void heapSort(int vetorFinal[])
{
    int i, atual, maiorFilho;

    criarHeap(vetorFinal);

    for ( i = VETOR - 1; i > 0; i--)
    {
        troca(&vetorFinal[0], &vetorFinal[i]);
        atual = 0;

        while (esquerdo(atual) < i)
        {
            maiorFilho = esquerdo(atual);
        
            if (direito(atual) < i && vetorFinal[direito(atual)] > vetorFinal[esquerdo(atual)])
            {
                maiorFilho = direito(atual);
            }

            if (vetorFinal[atual] < vetorFinal[maiorFilho])
            {
                troca(&vetorFinal[atual], &vetorFinal[maiorFilho]);
                atual = maiorFilho;
            }
            else
            {
                break;
            }
        }
    }
}

// cabou o heap

// Quick 

int divide(int vetorFinal[], int inicio, int fim)
{
    int i, pivo = vetorFinal[fim], maiores = inicio;
    
    for ( i = inicio; i < fim; i++ )
    {
        if (vetorFinal[i] <= pivo)
        {
            troca(&vetorFinal[i], &vetorFinal[maiores]);
            maiores++;
        }
    }

    troca(&vetorFinal[maiores], &vetorFinal[fim]);
    return maiores;
}

void quickSort(int vetorFinal[], int inicio, int fim)
{
    int pivoSeiLa;

    if (inicio < fim) 
    {
        pivoSeiLa = divide(vetorFinal, inicio, fim);
        quickSort(vetorFinal, inicio, pivoSeiLa - 1);
        quickSort(vetorFinal, pivoSeiLa + 1, fim);
    }
}

// vetores

void preencherVetor(int vetorZuado[])
{
    int i;
    srand(time(NULL));
    for (i = 0; i < VETOR; i++)
    {
        vetorZuado[i] = rand() % 100000;
    }
}

void copiarVetor(int vetorZuado[], int vetorFinal[])
{
    int i;
    for (i = 0; i < VETOR; i++)
    {
        vetorFinal[i] = vetorZuado[i];
    }
}

// cabou vetores

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int vetorZuado[VETOR], vetorFinal[VETOR];
    int inicio = 0, fim = VETOR - 1;
    clock_t inicioT, fimT; 
    double tempoTotal;

    preencherVetor(vetorZuado);
    copiarVetor(vetorZuado, vetorFinal);

    // merge de novo
    printf("\nComeçando por Merge Sort:\n");
    inicioT = clock(); 
    mergeSort(vetorFinal, inicio, fim);
    fimT = clock(); 
    tempoTotal = (double) (fimT - inicioT) / CLOCKS_PER_SEC;
    printf("Concluído\n");
    printf("Tempo de execução: %f segundos\n", tempoTotal);
    // cabou o merge de novo

    copiarVetor(vetorZuado, vetorFinal);

    // heap de novo
    printf("\nAgora o Heap:\n");
    inicioT = clock();
    heapSort(vetorFinal);
    fimT = clock(); 
    tempoTotal = (double) (fimT - inicioT) / CLOCKS_PER_SEC;
    printf("Concluído\n");
    printf("Tempo de execução: %f segundos\n", tempoTotal);
    // cabou o heap de novo

    copiarVetor(vetorZuado, vetorFinal);

    //quick de novo
    printf("\nPor último, o quick:\n");
    inicioT = clock();
    quickSort(vetorFinal, inicio, fim);
    fimT = clock();
    tempoTotal = (double) (fimT - inicioT) / CLOCKS_PER_SEC;
    printf("Concluído\n");
    printf("Tempo de execução: %f segundos\n", tempoTotal);
    // cabou o quick de novo

    getchar();
    
    

    return 0; 
}