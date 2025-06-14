#include <unistd.h>      // Contém funções como fork(), execlp(), getpid(), getppid()
#include <stdio.h>       // Para printf() e scanf()
#include <stdlib.h>      // Para exit() e EXIT_FAILURE
#include <sys/types.h>   // Define tipos como pid_t
#include <sys/wait.h>    // Para wait()

int main() {
    int retval, n;  // retval: retorno do fork(); n: número de filhos a serem criados

    printf("Digite o número de filhos a serem criados: ");
    scanf("%d", &n);  // Lê do usuário o número de filhos desejado

    printf("Ola, sou o processo %5d\n", getpid());  // Imprime o PID do processo pai

    for (int i = 0; i < n; i++) {        // Loop para criar n filhos
        retval = fork();                 // Cria um novo processo
        if (retval < 0) {
            // Erro ao criar processo
            perror("Erro ao criar processo");
            exit(EXIT_FAILURE);         // Encerra o programa com código de erro
        }

        if (retval == 0) {
            // Código executado somente pelo processo filho
            printf("[%d]-> sou %5d, filho de %5d\n", i, getpid(), getppid());

            // Filho executa o comando 'ps -f'
            printf("Filho %d executando 'ps -f':\n", i);
            execlp("ps", "ps", "-f", NULL);  // Substitui o processo atual por 'ps -f'

            // Se execlp falhar, mostra erro e encerra
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // Código executado somente pelo pai
            wait(NULL);  // Espera o filho terminar

            printf("Pai (PID = %d) após criação do filho %d executando 'ps -f':\n", getpid(), i);
            execlp("ps", "ps", "-f", NULL);  // Substitui o processo pai por 'ps -f'

            // Se execlp falhar, mostra erro e encerra
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }
    return 0;  // Fim do programa (só será alcançado se nenhum execlp for executado com sucesso)
}


