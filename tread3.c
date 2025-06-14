#include <unistd.h>      // Biblioteca para fork(), execlp(), getpid(), getppid()
#include <stdio.h>       // Biblioteca para printf(), perror()
#include <stdlib.h>      // Biblioteca para exit()
#include <sys/types.h>   // Define tipos como pid_t (usado em fork)

int main() {
    int pid;  // Variável que receberá o retorno do fork()

    // Mostra o PID do processo principal (pai)
    printf("MAIN: Olá, sou o processo %5d\n", getpid());

    // Cria um novo processo
    pid = fork();

    // Verifica se houve erro ao criar o processo filho
    if (pid < 0) {
        // Se fork() retornar valor negativo, houve erro
        perror("Erro ao criar processo filho");
        exit(1);  // Sai com código de erro
    }

    // Se fork() retornou um número positivo, este é o processo pai
    if (pid > 0) {
        // pid agora contém o PID do processo filho
        printf("Pai: processo filho PID=%5d criado com sucesso\n", pid);
    } else {
        // Se fork() retornou zero, estamos no processo filho
        printf("Filho: sou o processo %5d, filho de %5d\n", getpid(), getppid());

        // Executa o comando 'ls' que lista os arquivos e diretórios do diretório atual
        execlp("ls", "ls", NULL);

        // Se execlp falhar (não encontrar o comando, por exemplo), cai aqui
        perror("Erro ao executar ls");
        exit(1);  // Sai com erro
    }

    // Processo pai continua aqui (filho não continua porque execlp substitui o processo)
    return 0;
}

