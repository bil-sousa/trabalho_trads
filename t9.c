#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <pthread.h>

#define N 1000
#define RODADAS 20

int vetor[N];

// Gera vetor aleatório
void gerar_vetor(int v[]) {
    for (int i = 0; i < N; i++)
        v[i] = rand() % 10000;
}

// Bubble Sort
void bubble_sort(int v[]) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                int tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
    }
}

// ------------------ Threads ------------------

void* thread_sort(void* arg) {
    int* v = (int*)arg;
    bubble_sort(v);
    return NULL;
}

double testar_threads() {
    double total = 0.0;
    for (int i = 0; i < RODADAS; i++) {
        int v[N];
        gerar_vetor(v);

        pthread_t tid;
        clock_t start = clock();

        pthread_create(&tid, NULL, thread_sort, v);
        pthread_join(tid, NULL);

        clock_t end = clock();
        total += (double)(end - start) / CLOCKS_PER_SEC;
    }
    return total / RODADAS;
}

// ------------------ Processos ------------------

double testar_processos() {
    double total = 0.0;
    for (int i = 0; i < RODADAS; i++) {
        int v[N];
        gerar_vetor(v);

        clock_t start = clock();

        pid_t pid = fork();
        if (pid == 0) {
            // Filho
            bubble_sort(v);
            exit(0);
        } else {
            // Pai
            wait(NULL);
            clock_t end = clock();
            total += (double)(end - start) / CLOCKS_PER_SEC;
        }
    }
    return total / RODADAS;
}

int main() {
    srand(time(NULL));
    
    double tempo_threads = testar_threads();
    double tempo_processos = testar_processos();

    printf("\nTempo médio com Threads:   %.6f segundos\n", tempo_threads);
    printf("Tempo médio com Processos: %.6f segundos\n", tempo_processos);

    return 0;
}
/*codigo adaptdo para medir o tempo médio de execução
 usando fork() (processos) e pthread (threads).*/