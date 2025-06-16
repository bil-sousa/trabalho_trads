#include <unistd.h>      // fork(), execlp(), getpid(), getppid()
#include <stdio.h>       // printf(), scanf()
#include <stdlib.h>      // exit(), EXIT_FAILURE
#include <sys/types.h>   // pid_t
#include <sys/wait.h>    // wait()

int main() {
    int retval, n;

    printf("Digite o número de filhos a serem criados: ");
    scanf("%d", &n);

    printf("\nOlá, sou o processo %5d\n", getpid());

    for (int i = 0; i < n; i++) {
        printf("\n--- Criando filho %d ---\n", i);  // Separação visual

        retval = fork();

        if (retval < 0) {
            perror("Erro ao criar processo");
            exit(EXIT_FAILURE);
        }

        if (retval == 0) {
            // Filho
            printf("[%d] -> sou %5d, filho de %5d\n", i, getpid(), getppid());
            printf("Filho %d executando 'ps -f':\n", i);
            execlp("ps", "ps", "-f", NULL);

            // Se execlp falhar
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // Pai: espera o filho terminar e continua o laço
            wait(NULL);
        }
    }

    printf("\nPai (PID = %d) terminou de criar os %d filhos.\n", getpid(), n);
    return 0;
}

