#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

char username[50], password[50];
char cwd[PATH_MAX];

void show_login()
{
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/data/Users.csv");
    FILE *users_list = fopen(cwd, "r");
    long file_length = ftell(users_list);
    char *buffer = malloc(file_length);
    char line[PATH_MAX]; 
    int line_counter = 0;
    int is_authorized = 0;
    printf("\bLogin\n");
    printf("Nome do usuário: ");
    fgets(username, sizeof(username), stdin);
    printf("Senha: ");
    fgets(password, sizeof(password), stdin);
    if (users_list)
    {
        // if (buffer)
        // {
        //     while (fgets(line, sizeof(line), users_list) != NULL)
        //     {
        //         if(){
                    
        //         }
        //         line_counter++;
        //     }
        // }
    }
    else
    {
        printf("Erro! O arquivo Users.csv não foi encontrado\n");
        exit(1);
    }
    fclose(users_list);
}

int main()
{
    show_login();
    return 0;
}
