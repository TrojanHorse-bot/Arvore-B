/* Dados Gerenciados: Cada registro deve incluir:
• Chave (ID): Inteira e única. - ok
• Atributos adicionais: Nome (string),  - ok
Data de criação (timestamp) - ok
e Valor (número decimal).
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ENTRY_AMOUNT 50000 /*Quantidade de itens a serem gerados*/

int main(){
    int qtd = ENTRY_AMOUNT;
    FILE *inputmess;
    time_t now;
    struct tm *local_time;
    int currentNum[ENTRY_AMOUNT];

  

    inputmess = fopen("./input/input.txt", "w");

    for (int i = 0; i < qtd; i++){
        currentNum[i] = random();

        /*Teste para ver se o número já não existe*/
            for (int j = 0; j < i; j++){
                if (currentNum[j] == currentNum[i]){
                    currentNum[i] = random();
                    j = 0;
                }
            }

        /* Tempo atual */
        time(&now);
        local_time = localtime(&now);

        fprintf(inputmess, "%d\nDEFAULTNAME_%d\n", i, i);
        fprintf(inputmess, "%02d:%02d:%02d\n",
        /*
            local_time->tm_year + 1900, /// Year since 1900
            local_time->tm_mon + 1,    /// Month [0-11] + 1
            local_time->tm_mday,       /// Day of the month
        */
            local_time->tm_hour,       /// Hour [0-23]
            local_time->tm_min,        /// Minutes [0-59]
            local_time->tm_sec);       /// Seconds [0-59]
        fprintf(inputmess, "%d\n\n", currentNum[i]);
    }


    fclose(inputmess);
    return 0;
}