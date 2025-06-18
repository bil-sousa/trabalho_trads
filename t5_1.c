#include <unistd.h>     // Para fork(), getpid(), getppid(), sleep()
#include <stdio.h>      // Para printf(), scanf()
#include <stdlib.h>     // Para exit(), rand()
#include <sys/types.h>  // Para tipos como pid_t
#include <sys/wait.h>   // Para wait()
#include <time.h>       // Para srand() e rand()

int main() {
    int retval, n;

    // Solicita ao usuário o número de filhos
    printf("Digite o número de filhos a serem criados: ");
    scanf("%d", &n);

    // Semente para gerar tempos aleatórios diferentes
    srand(time(NULL));

    // PID do processo pai
    printf("Processo pai: %5d\n", getpid());

    // Loop para criar N filhos
    for (int i = 0; i < n; i++) {
        retval = fork();  // Cria um novo processo filho

        if (retval < 0) {
            perror("Erro ao criar processo");
            exit(1);
        }

        if (retval == 0) {
            // Código do processo filho
            printf("[Filho %d] PID: %5d | Pai: %5d\n", i, getpid(), getppid());

            // Cada filho realiza uma "tarefa": dormir entre 1 e 5 segundos
            int tempo = rand() % 5 + 1;
            printf("[Filho %d] Realizando tarefa por %d segundos...\n", i, tempo);
            sleep(tempo);
            printf("[Filho %d] Finalizei minha tarefa.\n", i);
            exit(0); // Filho encerra após a tarefa
        }

        // O pai NÃO espera os filhos — eles executam em paralelo
    }

    // O pai pode fazer outra coisa ou encerrar imediatamente
    printf("Processo pai terminou sua parte. Filhos continuam sozinhos.\n");

    // Para fins de visualização, o pai pode aguardar um tempo
    sleep(6);  // Garante que filhos terminem antes do fim da main (opcional)

    return 0;
}
