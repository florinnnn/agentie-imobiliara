typedef struct firma{
    char nume[211], strada[310], numar[300], telefon[101];
    long long int cod;
}firma;

void printFirma(firma df){
    fflush(stdin);
    printf("Nume firma: %s\n", df.nume);
    printf("Cod fiscal: %lli\n\n", df.cod);
    printf("Adresa: %s, %s\n", df.strada, df.numar);
    printf("Telefon: %s\n\n", df.telefon);
}
void option1(){
    system("cls");
    FILE *det_firma = fopen("data/detalii_firma.csv", "r");
    if(det_firma == NULL){
        perror("Unable to open the file");
        exit(1);
    }
    char line[1024];
    firma df;
    int row = 1;
    //parcurge fisierul si stocheaza in struct

    while(fgets(line, sizeof(line), det_firma)){
        char *token;
        int field = 0;
        token = strtok(line, ",");
        while(token != NULL){
            if(row == 1 && field == 1)
                strcpy(df.nume, token);
            
            else if(row == 2 && field == 1){
               df.cod = atoi(token); // Using atoi()
            }
            
            else if(row == 3 && field == 1)
                strcpy(df.strada, token);

            else if(row == 3 && field == 2)
                strcpy(df.numar, token);

            else if(row == 4 && field == 1)
                strcpy(df.telefon, token);
            
            field++;
            token = strtok(NULL, ",");
        }
        row++;
    }
    printFirma(df);

    fclose(det_firma);
    printf("Apasa orice pentru reintoarcere\n");
    getch();
    firstPage();
}