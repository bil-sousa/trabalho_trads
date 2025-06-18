#include <unistd.h>      // Para fork(), getpid(), getppid(), sleep()
#include <stdio.h>       // Para printf(), scanf()
#include <stdlib.h>      // Para exit()
#include <sys/types.h>   // Para tipos como pid_t
#include <sys/wait.h>    // Para wait()
#include <time.h>        // Para srand() e rand()

int main() {
    int n;

    // Solicita o número de filhos
    printf("Digite o número de filhos a serem criados: ");
    scanf("%d", &n);

    // Semente para aleatoriedade
    srand(time(NULL));

    printf("Processo pai: %5d\n", getpid());

    // Cria os processos filhos
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Erro ao criar processo");
            exit(1);
        }

        if (pid == 0) {
            // Código do filho
            int resultado = rand() % 100; // Simula um "cálculo"
            printf("[Filho %d] PID: %5d fez um cálculo e obteve: %d\n",
                   i, getpid(), resultado);
            sleep(1); // Simula tempo de processamento
            exit(resultado % 256); // Retorno limitado a 0-255
        }
        // Código do pai continua no loop
    }

    // Pai espera os filhos
    for (int i = 0; i < n; i++) {
        int status;
        pid_t pid_terminado = wait(&status);

        if (WIFEXITED(status)) {
            int valor = WEXITSTATUS(status);
            printf("Pai: Filho PID %5d terminou e retornou: %d\n", pid_terminado, valor);
        } else {
            printf("Pai: Filho PID %5d terminou de forma anormal.\n", pid_terminado);
        }
    }

    printf("Pai: todos os filhos terminaram.\n");
    return 0;
}
