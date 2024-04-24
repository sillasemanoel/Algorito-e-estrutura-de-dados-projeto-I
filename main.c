#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "estoque.h"

void menuConta()
{
    printf("\n-- Menu Conta --\n");
    printf("1. Exibir contas cadastradas\n");
    printf("2. Adicionar conta\n");
    printf("3. Remover conta\n");
    printf("4. Voltar\n");
}

void menuEstoque()
{
    printf("\n-- Menu Estoque --\n");
    printf("1. Listar estoque\n");
    printf("2. Adicionar item\n");
    printf("3. Remover item\n");
    printf("4. Valor do estoque\n");
    printf("5. Ordenar itens do estoque\n");
    printf("6. Imprimir estoque em arquivo\n");
    printf("7. Voltar\n");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    char email_cadastrado[80];
    char senha_cadastrada[80];
    char lista_emails[100][80];

    int num_emails = 0;

    while (1)
    {
        printf("\nBem vindo ao cadastro no sistema de estoque.\n");
        printf("Por favor, cadastre um email válido: ");
        fgets(email_cadastrado, 80, stdin);
        email_cadastrado[strcspn(email_cadastrado, "\n")] = '\0';

        if (strchr(email_cadastrado, '@') != NULL)
        {
            strcpy(lista_emails[num_emails], email_cadastrado);
            num_emails++;
            break;
        }
        else
        {
            printf("\nO email é inválido, ele deve conter '@' para ser um email válido.\n");
        }
    }

    printf("Por favor, cadastre sua senha: ");
    fgets(senha_cadastrada, 80, stdin);
    senha_cadastrada[strcspn(senha_cadastrada, "\n")] = '\0';

    printf("\nCadastro concluído, faça login para continuar.\n");

    ItemEstoque *estoque = NULL;

    while (1)
    {
        char email[80];
        char senha[80];

        printf("\nInsira seu email: ");
        fgets(email, 80, stdin);
        email[strcspn(email, "\n")] = '\0';
        printf("Insira sua senha: ");
        fgets(senha, 80, stdin);
        senha[strcspn(senha, "\n")] = '\0';

        if (strcasecmp(email, email_cadastrado) == 0 && strcmp(senha, senha_cadastrada) == 0)
        {
            printf("\nBem vindo ao Controle de Estoque RD.\n");

            int escolha;
            while (1)
            {
                printf("\n-- Menu Principal --\n");
                printf("1. Conta\n");
                printf("2. Estoque\n");
                printf("3. Logout\n");
                printf("\nEscolha uma opção: \n");
                scanf("%d", &escolha);

                switch (escolha)
                {
                case 1:
                    while (1)
                    {
                        menuConta();
                        printf("Escolha uma opção: ");
                        scanf("%d", &escolha);
                        switch (escolha)
                        {
                        case 1:
                            printf("\nContas cadastradas:\n");
                            for (int i = 0; i < num_emails; i++)
                            {
                                printf("%d. %s\n", i + 1, lista_emails[i]);
                            }
                            break;
                        case 2:
                            printf("\nInsira um novo email: ");
                            scanf("%s", lista_emails[num_emails]);
                            printf("Insira uma senha para o novo email: ");
                            scanf("%s", senha);
                            num_emails++;
                            printf("Nova conta adicionada.\n");
                            break;
                        case 3:
                            printf("\nEscolha a conta que será removida:\n");
                            for (int i = 0; i < num_emails; i++)
                            {
                                printf("%d. %s\n", i + 1, lista_emails[i]);
                            }
                            int escolha_email;
                            scanf("%d", &escolha_email);
                            if (escolha_email >= 1 && escolha_email <= num_emails)
                            {
                                for (int i = escolha_email - 1; i < num_emails - 1; i++)
                                {
                                    strcpy(lista_emails[i], lista_emails[i + 1]);
                                }
                                num_emails--;
                                printf("Conta removida.\n");
                            }
                            else
                            {
                                printf("Opção inexistente\n");
                            }
                            break;
                        case 4:
                            break;
                        default:
                            printf("Opção inexistente. Escolha uma opção disponível.\n");
                            break;
                        }
                        if (escolha == 4)
                            break;
                    }
                    break;
                case 2:
                    while (1)
                    {
                        menuEstoque();
                        printf("Escolha uma opção: ");
                        scanf("%d", &escolha);
                        switch (escolha)
                        {
                        case 1:
                            printf("\nEstoque atual:\n");
                            if (estoque == NULL)
                            {
                                printf("Estoque vazio.\n");
                            }
                            else
                            {
                                listarItensEstoque(estoque);
                            }
                            break;
                        case 2:
                            printf("\nAdicionar item ao estoque:\n");
                            char novo_nome[100];
                            int nova_quantidade;
                            float novo_valor;
                            printf("Nome do item: ");
                            scanf("%s", novo_nome);
                            printf("Quantidade do item: ");
                            scanf("%d", &nova_quantidade);
                            printf("Preço por unidade: ");
                            scanf("%f", &novo_valor);
                            adicionarItemEstoque(&estoque, novo_nome, nova_quantidade, novo_valor);
                            printf("Item adicionado ao estoque.\n");
                            break;
                        case 3:
                            printf("\nRemover item selecionado:\n");
                            if (estoque == NULL)
                            {
                                printf("Estoque vazio.\n");
                            }
                            else
                            {
                                char item_remover[100];
                                printf("Nome do item a ser removido: ");
                                scanf("%s", item_remover);
                                removerItemEstoque(&estoque, item_remover);
                            }
                            break;
                        case 4:
                            if (estoque == NULL)
                            {
                                printf("Estoque vazio.\n");
                            }
                            else
                            {
                                printf("Valor total do estoque: R$ %.2f\n", calcularValorTotalEstoque(estoque));
                            }
                            break;
                        case 5:
                            printf("\nOrdenar itens do estoque:\n");
                            if (estoque == NULL)
                            {
                                printf("Estoque vazio.\n");
                            }
                            else
                            {
                                ordenarItensEstoque(estoque);
                                printf("Itens do estoque ordenados com sucesso.\n");
                            }
                            break;
                        case 6:
                            printf("\nImprimir estoque em arquivo:\n");
                            if (estoque == NULL)
                            {
                                printf("Estoque vazio. Nada para imprimir.\n");
                            }
                            else
                            {
                                imprimirEstoqueArquivo(estoque);
                            }
                            break;
                        case 7:
                            break;
                        default:
                            printf("Opção inexistente. Escolha uma opção disponível.\n");
                            break;
                        }
                        if (escolha == 7)
                            break;
                    }
                    break;
                case 3:
                    printf("Até o próximo login.\n");
                    return 0;
                default:
                    printf("Opção inexistente. Escolha uma opção disponível.\n");
                    break;
                }
            }
            break;
        }
        else
        {
            printf("Email ou senha incorretos, tente novamente!\n");
        }
    }

    return 0;
}
