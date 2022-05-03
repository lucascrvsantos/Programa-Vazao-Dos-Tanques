/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *  Alunos : Lucas Carvalho ; Anthony Mantoani         *
 *  Data : 26/04/2022                                  *
 *  Série : 1° Série EAI                               *
 *  Título : Simulador de controle de Tanques          *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*******************************************************
*                                                      *
*   Este programa faz o controle do enchimento de      *
*   dois tanques (A e B), por meio de quatro sensores  *
*   (S0, S1, S2 e S3), uma bomba e duas válvulas (V0   *
*   e V1).                                             *
*                                                      *
*******************************************************/


#include <stdio.h>
#include <stdlib.h>



int sensor0, sensor1, sensor2, sensor3, valvula0, bomba, valvula1;



int main()
{
    // Condições iniciais do programa :
    sensor0 = sensor1 = sensor2 = sensor3 = valvula0 = valvula1 = bomba = 0;
    // Gráfico do sistema :
    printf("    * * Controle dos Tanques * *   \n\n");
    printf("    V0                             \n");
    printf(">==>^<==++     ++========++        \n");
    printf("        ||     ||        ||        \n");
    printf("        \\/     ||        \\/        \n");
    printf("   S1-|-   |   ||   S3-|-   |      \n");
    printf("      |    |   ||      |    |      \n");
    printf("      | TA |   ||      | TB |      \n");
    printf("      |    |   ||      |    |      \n");
    printf("   S0-|-   |   ||   S2-|-   |      \n");
    printf("      +----+   ||      +----+      \n");
    printf("        ||     ||        ||  V1    \n");
    printf("        ++==@==++        ++=>^<==> \n");
    printf("            B                      \n\n");

    inicio: // Inicio do Programa

    printf("Indique o estado do sensor :\n");
    printf(" O sensor S0 esta ativo ? \n  1 - Sim \n  0 - Nao \n  "); // Leitura do estado do sensor 0 : verifica se o tanque A está vazio .
    scanf("%d", &sensor0);

    if (sensor0 == 1) // Leitura do estado do sensor 0 : verifica se há algum líquido no tanque A.
    {
        // Caso houver, será feita a leitura do sensor 1.
        goto sensor1;
    }
    else
    {
        // Caso não, A vávula V0 deve ser aberta para encher o tanque A.
        valvula0 = 1;
        printf("\nEstado do Sistema A :\n");
        printf(" Valvula V0 : ABERTA\n");
        printf(" Tanque  TA : ENCHENDO\n\n");
        // Volta a conferir a leitura do sensor 0.
        goto inicio;
    }

    sensor1:
    // Leitura do estado do sensor 1 : Verifica se o Tanque A está cheio.
    printf(" O sensor S1 esta ativo ? \n  1 - sim \n  0 - nao \n  ");
    scanf("%d", &sensor1);
    if (sensor1 == 0)
    {
    // Se não estiver cheio, a válvula V0 pode continuar aberta
        printf("\nEstado do Sistema A :\n");
        printf(" Valvula VO : ABERTA\n");
        printf(" Tanque  TA : ENCHENDO\n\n");
    // Volta a ler o estado do sensor 1.
        goto sensor1;
    }
    else
    {
    // Caso estiver, a válvula V0 deve ser fechada e a leitura dos sensores do tanque A pode ser iniciada.
        valvula0 = 0;
        printf("\nEstado do Sistema A :\n");
        printf(" Valvula VO : FECHADA\n");
        printf(" Tanque  TA : CHEIO\n\n");
    }

    sensor3:
    // Leitura do estado do sensor 3 : verifica se o tanque B está cheio .
    printf(" O sensor S3 esta ativo ? \n  1 - Sim \n  0 - Nao \n  ");
    scanf("%d", &sensor3);
    if (sensor3 == 0)
    {
    // Caso não estiver, a válvula v1 é fechada e a bomba é ligada para encher o B.
        valvula1 = 0;
        bomba = 1;
        printf("\nEstado do Sistema B :\n");
        printf(" Valvula V1 : FECHADA\n");
        printf(" Bomba : LIGADA\n");
        printf(" Tanque  TB : ENCHENDO\n\n");

    // Enquanto o tanque B está enchendo, é feito a leitura do sensor S0 para conferir se ainda há líquido no tanque A para ser bombeado.
        printf(" O sensor S0 esta ativo ? \n  1 - Sim \n  0 - Nao \n  ");
        scanf("%d", &sensor0);
        if (sensor0 == 0)
        {
    // Se o tanque A estiver vazio, a válvula V0 é aberta e a bomba é desligada.
            valvula0 = 1;
            bomba = 0;
            printf("\nEstado do Sistema :\n");
            printf(" Tanque TA : VAZIO\n");
            printf(" Bomba : FECHADA\n");
            printf(" Valvula V0 : ABERTA\n");
            printf(" Tanque TA : ENCHENDO\n\n");
    // O programa volta a conferir o estado dos sensores do tanque A, até que esteja cheio.
            goto inicio;
        }
        else
        {
    // Caso haja líquido no tanque A, o processo do bombeamento para o tanque B pode continuar.
            goto sensor3;
        }
    }
    else
    // Se o tanque B estiver cheio, a bomba deve ser desligada (ou continuar desligada) e a válvula V1 deve ser aberta, para esvaziar o tanque.
    {
        valvula1 = 1;
        bomba: 0;
        printf("\nEstado do Sistema B :\n");
        printf(" Valvula V1 : ABERTA\n");
        printf(" Bomba : DESLIGADA\n");
        printf(" Tanque  TB : ESVAZIANDO\n\n");
    }

    sensor2:
    // Leitura do estado do sensor 2 : verifica se o tanque B está vazio.
    printf(" O sensor S2 esta ativo ? \n  1 - Sim \n  0 - Nao \n  ");
    scanf("%d", &sensor2);
    if (sensor2 == 1)
    // Como o tanque está sendo esvaziado, caso haja líquido, a válvula V1 deve continuar aberta e a bomba desligada.
    {
        bomba = 0;
        valvula1 = 1;
        printf("\nEstado do Sistema B :\n");
        printf(" Valvula V1 : ABERTA\n");
        printf(" Bomba : DESLIGADA\n");
        printf(" Tanque  TB : ESVAZIANDO\n\n");
        goto sensor2;
    }
    else
    {
    // Caso o tanque estiver vazio, a válvula V1 deve ser fechada e o programa volta a conferir o estado do tanque A.
        bomba = 0;
        valvula1 = 0;
        printf("\nEstado do Sistema B :\n");
        printf(" Valvula V1 : FECHADA\n");
        printf(" Bomba : DESLIGADA\n");
        printf(" Tanque  TB : VAZIO\n\n");
    }
    printf("\n\n");

    // Retorna ao estado do tanque A
    goto inicio;
    return 0;
}
