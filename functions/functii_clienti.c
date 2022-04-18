typedef struct client{
    char nume[251], tip[50], perioada[100];
}client;

void printClienti(client date_clienti[], int row){
    for(int i = 0; i < row; i++){
        printf("%d Nume: %s | Tip: %s | ", i + 1, date_clienti[i].nume, date_clienti[i].tip);
        if(!strcmp(date_clienti[i].perioada, "nu\n")){
            printf("Nu are contract\n\n");
        }
        else{
            printf("Perioada: %s\n", date_clienti[i].perioada);
        }
    }
}

void adaugare_client(client date_client[], client c, int len){
    int i, added = 0;
    client tmp;
    if(strcmp(c.nume, date_client[len - 1].nume) > 0){
        date_client[len] = c;
    }
    else{
        for(i = 0; i <= len + 1; i++){
            if(added){
                c = date_client[i];
                date_client[i] = tmp;
                tmp = c;
            }
            else if(strcmp(c.nume, date_client[i].nume) < 0){
                tmp = date_client[i];
                date_client[i] = c;
                added = 1;
            }
        }
    }
    FILE *temp = fopen("data/temp.csv", "w");
    
    fprintf(temp, "%s,%s,", date_client[0].nume, date_client[0].tip);
    if(!strcmp(date_client[0].perioada, "nu are contract\n"))
        fprintf(temp, "nu\n");
    else{
        fprintf(temp, "%s", date_client[0].perioada);
    }
    for(i = 1; i <= len; i++){
        fprintf(temp,"%s,%s,", date_client[i].nume, date_client[i].tip);
        if(!strcmp(date_client[i].perioada, "nu are contract\n"))
            fprintf(temp, "nu\n");
        else
            fprintf(temp, "%s", date_client[i].perioada);
    }
    fclose(temp);
    remove("data/clienti.csv");
    rename("data/temp.csv", "data/clienti.csv");
}

void sterge_client(client date_client[], int len, int start_pos){
    for(start_pos; start_pos < len; start_pos++){
        date_client[start_pos] = date_client[start_pos + 1];
    }
    FILE *tmp = fopen("data/temp.csv", "w");
    if(len == 0){
        fprintf(tmp, "");
        fclose(tmp);
        remove("data/clienti.csv");
        rename("data/temp.csv", "data/clienti.csv");
        return;
    }
    fprintf(tmp, "%s,%s,%s", date_client[0].nume, date_client[0].tip, date_client[0].perioada);
    for(int i = 1; i < len; i++){
        fprintf(tmp,"%s,%s,%s", date_client[i].nume, date_client[i].tip, date_client[i].perioada);
    }
    fclose(tmp);
    remove("data/clienti.csv");
    rename("data/temp.csv", "data/clienti.csv");
}

void option3(){
    system("cls");
    FILE *clienti = fopen("data/clienti.csv", "r");
    if(clienti == NULL){
        perror("Unable to open the file");
        exit(1);
    }
    client date_clienti[100];
    char line[1024];
    int row = 0;
    while(fgets(line, sizeof(line), clienti)){
        char *token;
        int field = 0;

        token = strtok(line, ",");

        while(token != NULL){
            if(field == 0){
                strcpy(date_clienti[row].nume, token);
            }
            else if(field == 1){
                strcpy(date_clienti[row].tip, token);
            }
            else{
                strcpy(date_clienti[row].perioada, token);
            }

            field++;
            token = strtok(NULL, ",");
        }
        row++;
    }
    fclose(clienti);

    printClienti(date_clienti, row);
    
    int opt;
    printf("1 Adaugare client\n2 Stergere client\n3 Inapoi\n");
    scanf("%d", &opt);
    switch (opt)
    {
    case 1:
        system("cls");
        client c;
        printf("Introduceti numele clientului: ");
        fflush(stdin);
        gets(c.nume);
        printf("Introduceti tipul clientului (fizic/firma): ");
        fflush(stdin);
        gets(c.tip);
        fflush(stdin);
        printf("Introduceti perioada contractului (nedeterminat/perioada/nu are contract): ");
        gets(c.perioada);
        strcat(c.perioada, "\n");
        fflush(stdin);
        adaugare_client(date_clienti, c, row);
        option3();
        break;
    
    case 2:
        system("cls");
        printClienti(date_clienti, row);
        printf("Introduceti indexul clientului pe care doriti sa-l stergeti (0 - cancel)\nIn cazul in care introduceti un index mai mare decat indexul ultimului client, se va sterge ultimul\nla fel si cu primul client\n");
        int i;
        scanf("%d", &i);
        if(i == 0){
            option3();
            break;
        }
        i--;
        sterge_client(date_clienti, row - 1, i);
        option3();
        break;

    case 3:
        firstPage();
        break;
    default:
        break;
    }
}