#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <locale.h>

char username[50], password[50];
int username_match = 0;
int password_match = 0;
int is_authorized = 0;
char cwd[PATH_MAX];
void show_login()
{
    typedef struct
    {
        char *user;
        char *password;
    } * user;
    char *user_data_column;
    user *user_data;

    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/data/Users.csv");

    FILE *users_list = fopen(cwd, "r");
    long file_length = ftell(users_list);
    char *buffer = malloc(file_length);
    char line[PATH_MAX];
    int line_counter = 0;

    printf("\bLogin\n");
    printf("Nome do usuário: ");
    fgets(username, sizeof(username), stdin);
    printf("Senha: ");
    fgets(password, sizeof(password), stdin);
    if (users_list)
    {
        if (buffer)
        {
            while (fgets(line, sizeof(line), users_list) != NULL)
            {
                if (line_counter == 0)
                {
                    line_counter++;

                    continue;
                }
                user_data_column = strtok(line, ",");
                int current_column = 1;

                while (user_data_column != NULL)
                {
                    if (current_column == 1)
                    {
                        for (int typed_username_index = 0; typed_username_index < strlen(user_data_column); typed_username_index++)
                        {
                            if (username[typed_username_index] == user_data_column[typed_username_index])
                            {
                                username_match = 1;
                            }
                            else
                            {
                                username_match = 0;
                                break;
                            }
                        }
                    }
                    else if (current_column == 2)
                    {
                        for (int typed_password_index = 0; typed_password_index < strlen(user_data_column); typed_password_index++)
                        {
                            if (password[typed_password_index] == user_data_column[typed_password_index])
                            {
                                password_match = 1;
                            }
                            else
                            {
                                password_match = 0;
                                break;
                            }
                        }
                    }
                    current_column++;
                    user_data_column = strtok(NULL, ",");
                }
            }
        }
    }
    else
    {
        printf("Erro! O arquivo Users.csv não foi encontrado\n");
        exit(1);
    }
    fclose(users_list);
    if (username_match == 1 && password_match == 1)
    {
        printf("Usuário autenticado\n");
#ifdef WIN32
        system("pause");
#else
        system("read -p \"Pressione enter para sair...\" saindo");
#endif
        exit(1);
    }
    else
    {
        printf("Usuário não autorizado! Login ou senha incorretos\n");
#ifdef WIN32
        system("pause");
#else
        system("read -p \"Pressione enter para sair....\" saindo");
#endif
        exit(1);
    }
}

void show_menu()
{
    if (is_authorized == 0)
    {
        printf("Usuário não autorizado!\n");
#ifdef WIN32
        system("pause");
#else
        system("read -p \"Pressione enter para sair....\" saindo");
#endif
        exit(1);
    }
}

void show_menu()
{
    verify_if_is_authorized();
}

int main()
{
    show_login();
    show_menu();
    return 0;
}
