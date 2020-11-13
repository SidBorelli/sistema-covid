#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <locale.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define INPUT_MAX_LENGTH 50

char username[INPUT_MAX_LENGTH], password[INPUT_MAX_LENGTH];
int username_match = 0;
int password_match = 0;
int is_authorized = 0;
char cwd[PATH_MAX];
typedef struct
{
    char name[50];
    char document[50];
    char phone[50];
    char address[50];
    char birthdate[50];
    char email[50];
    char diagnosticDate[50];
    char comorbidities[50];
} Ocurrence;

char *remove_line_break(char *value)
{
    char *new_value;
    for (int counter = 0; value < strlen(value); counter++)
    {
        if (value[counter] != '\n')
        {
            new_value[counter] = value[counter];
        }
    }
    return new_value;
}

int is_valid_comorbity(char *value)
{
}

void get_risk_cases()
{
    clear();
    char *ocurrences_data_column;
    int risk_cases_counter;
    verify_if_is_authorized();
    get_header();
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/data/Ocurrences.csv");
    FILE *ocurrences_list = fopen(cwd, "r");
    char line[PATH_MAX];
    if (sizeof(ocurrences_list) <= 1)
    {
        printf(ANSI_COLOR_CYAN "\nLista de Registros: " ANSI_COLOR_RESET "\n\n");
        int line_counter = 0;
        while (fgets(line, sizeof(line), ocurrences_list) != NULL)
        {
            if (line_counter == 0)
            {
                line_counter++;
                continue;
            }
            if (line_counter < 10)
            {
                printf(ANSI_COLOR_CYAN "\nId: %d - " ANSI_COLOR_RESET, line_counter);
            }
            else
            {
                printf(ANSI_COLOR_CYAN "\nId:%d - " ANSI_COLOR_RESET, line_counter);
            }
            int ocurrences_column_counter = 1;
            ocurrences_data_column = strtok(line, ",");
            while (ocurrences_data_column != NULL)
            {
                if (ocurrences_column_counter == 8 && is_valid_comorbity(ocurrences_data_column))
                {
                }
            }
            line_counter++;
        }
    }
    pause_system();
    show_menu();
}

void show_login()
{
    typedef struct
    {
        char *user;
        char *password;
    } * user;
    char *user_data_column;
    user *user_data;
    ;
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/data/Users.csv");
    FILE *users_list = fopen(cwd, "r");
    long file_length = ftell(users_list);
    char *buffer = malloc(file_length);
    char line[PATH_MAX];
    int line_counter = 0;

    printf(ANSI_COLOR_RED "Login" ANSI_COLOR_RESET "\n");
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
        is_authorized = 1;
        pause_system();
    }
    else
    {
        printf("Usuário não autorizado!\n");
        pause_system();
        exit(1);
    }
}

void insert_new_record()
{
    Ocurrence new_record;
    clear();
    get_header();
    printf("\nInserindo um novo caso de COVID-19\n");
    char comorbity_option[3];
    printf("Nome Completo: ");
    fgets(&new_record.name, sizeof(new_record.name), stdin);
    printf("CPF: ");
    fgets(&new_record.document, sizeof(new_record.document), stdin);
    printf("Telefone: ");
    fgets(&new_record.phone, sizeof(new_record.phone), stdin);
    printf("Endereço: ");
    fgets(&new_record.address, sizeof(new_record.address), stdin);
    printf("Data de Nascimento (dd/mm/yyyy): ");
    fgets(&new_record.birthdate, sizeof(new_record.birthdate), stdin);
    printf("E-mail: ");
    fgets(&new_record.email, sizeof(new_record.email), stdin);
    printf("Data de Diagnóstico (dd/mm/yyyy): ");
    fgets(&new_record.diagnosticDate, sizeof(new_record.diagnosticDate), stdin);
    printf("Comorbidade (1- Diabetes, 2 - Obesidade, 3 - Hipertensão, 4 - Tuberculose, 5 - Outros):");
    fgets(&comorbity_option, sizeof(comorbity_option), stdin);
    switch (comorbity_option[0])
    {
    case '1':
        strcpy(new_record.comorbidities, "Diabetes");
        break;
    case '2':
        strcpy(new_record.comorbidities, "Obesidade");
        break;
    case '3':
        strcpy(new_record.comorbidities, "Hipertensão");
        break;
    case '4':
        strcpy(new_record.comorbidities, "Tuberculose");
        break;
    default:
        strcpy(new_record.comorbidities, 'Outros');
        break;
    }

    strcpy(new_record.name, strtok(new_record.name, "\n"));
    strcpy(new_record.address, strtok(new_record.address, "\n"));
    strcpy(new_record.phone, strtok(new_record.phone, "\n"));
    strcpy(new_record.birthdate, strtok(new_record.birthdate, "\n"));
    strcpy(new_record.diagnosticDate, strtok(new_record.diagnosticDate, "\n"));
    strcpy(new_record.document, strtok(new_record.document, "\n"));
    strcpy(new_record.email, strtok(new_record.email, "\n"));

    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/data/Ocurrences.csv");
    FILE *ocurrences_file = fopen(cwd, "a");
    fprintf(ocurrences_file, "\n%s,%s,%s,%s,%s,%s,%s,%s", new_record.name, new_record.phone, new_record.document, new_record.address, new_record.birthdate, new_record.email, new_record.diagnosticDate, new_record.comorbidities);
    fclose(ocurrences_file);
    printf(ANSI_COLOR_GREEN "Novo Registro inserido com sucesso!" ANSI_COLOR_RESET);
    pause_system();
    show_menu();
}

void clear()
{
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause_system()
{
#ifdef WIN32
    system("pause");
#else
    system("read -p \"Pressione enter para sair...\" saindo");
#endif
}

void verify_if_is_authorized()
{
    if (is_authorized == 0)
    {
        pause_system();
        exit(1);
    }
}

void get_header()
{
    printf(ANSI_COLOR_BLUE "Ferramenta de Monitoramento de Casos de COVID-19" ANSI_COLOR_RESET "\n");

    for (int vertical_line_counter = 0; vertical_line_counter < 30; vertical_line_counter++)
    {
        printf(ANSI_COLOR_BLUE "\u2500");
    }
    printf(ANSI_COLOR_RESET, "\n");
}

void get_all_records()
{
    clear();
    char *ocurrences_data_column;
    verify_if_is_authorized();
    get_header();
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/data/Ocurrences.csv");
    FILE *ocurrences_list = fopen(cwd, "r");
    char line[PATH_MAX];
    if (sizeof(ocurrences_list) <= 1)
    {
        printf(ANSI_COLOR_RED "\nNenhum registro cadastrado" ANSI_COLOR_RESET "\n\n");
    }
    else
    {
        printf(ANSI_COLOR_CYAN "\nLista de Registros: " ANSI_COLOR_RESET "\n\n");
        int line_counter = 0;
        while (fgets(line, sizeof(line), ocurrences_list) != NULL)
        {
            if (line_counter == 0)
            {
                line_counter++;
                continue;
            }
            if (line_counter < 10)
            {
                printf(ANSI_COLOR_CYAN "\nId: %d - " ANSI_COLOR_RESET, line_counter);
            }
            else
            {
                printf(ANSI_COLOR_CYAN "\nId:%d - " ANSI_COLOR_RESET, line_counter);
            }
            int ocurrences_column_counter = 1;
            ocurrences_data_column = strtok(line, ",");
            while (ocurrences_data_column != NULL)
            {
                printf("%s  | ", ocurrences_data_column);
                ocurrences_data_column = strtok(NULL, ",\n");
                ocurrences_column_counter++;
            }
            line_counter++;
        }
    }
    pause_system();
    show_menu();
}

void show_confirmation_exit()
{
    char repile[1];
    printf("\nConfirmação:\n");
    printf("Tem certeza que deseja sair? (s/n): ");
    scanf(" %c", &repile);
    if (repile[0] == 'n')
    {
        show_menu();
    }
    else
    {
        clear();
        printf("\nAté logo!\n");
        exit(1);
    }
}
void show_menu()
{
    clear();
    char selected_option[PATH_MAX];
    verify_if_is_authorized();
    get_header();
    get_risk_cases();
    printf(ANSI_COLOR_YELLOW "\nOpções:" ANSI_COLOR_RESET "\n\n");
    printf(ANSI_COLOR_YELLOW "  1 - Ver todos os registros" ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW "  2 - Ver casos de risco" ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW "  3 - Inserir novo caso" ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW "  0 - Sair" ANSI_COLOR_RESET "\n");
    printf("\n\nSelecione o número de uma opção do menu: ");
    fgets(selected_option, sizeof(selected_option), stdin);
    if (selected_option[0] == '1')
    {
        get_all_records();
    }
    else if (selected_option[0] == '3')
    {
        insert_new_record();
    }
    else if (selected_option[0] == '0')
    {
        show_confirmation_exit();
    }
    else
    {
        printf("Opção inválida!");
        pause();
        show_menu();
    }
}

int main()
{
    show_login();
    show_menu();
    return 0;
}
