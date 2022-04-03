void firstPage();

typedef struct angajat{
    char nume[251], sediu[151];
}angajat;

void print_angajati(angajat angajati[], int row){
    for(int i = 0; i < row; i++){
        printf("%d. Nume: %s | Sediu: %s\n", i + 1, angajati[i].nume, angajati[i].sediu);
    }
}

void adaugare_angajat(angajat date_angajat[], angajat a, int len){
    int i, added = 0;
    angajat tmp;
    if(strcmp(a.nume, date_angajat[len - 1].nume) > 0){
        date_angajat[len] = a;
    }
    else{
        for(i = 0; i <= len + 1; i++){
            if(added){
                a = date_angajat[i];
                date_angajat[i] = tmp;
                tmp = a;
            }
            else if(strcmp(a.nume, date_angajat[i].nume) < 0){
                tmp = date_angajat[i];
                date_angajat[i] = a;
                added = 1;
            }
        }
    }
    FILE *temp = fopen("data/temp.csv", "w");
    
    fprintf(temp, "%s,%s", date_angajat[0].nume, date_angajat[0].sediu);

    for(int i = 1; i <= len; i++){
        fprintf(temp,"%s,%s", date_angajat[i].nume, date_angajat[i].sediu);
    }
    fclose(temp);
    remove("data/angajati_sedii.csv");
    rename("data/temp.csv", "data/angajati_sedii.csv");
}

void sterge_angajat(angajat s[], int len, int start_pos){
    for(start_pos; start_pos < len; start_pos++){
        s[start_pos] = s[start_pos + 1];
    }
    FILE *tmp = fopen("data/temp.csv", "w");
    if(len == 0){
        //fprintf(tmp, "");
        fclose(tmp);
        remove("data/angajati_sedii.csv");
        rename("data/temp.csv", "data/angajati_sedii.csv");
        return;
    }
    fprintf(tmp, "%s,%s", s[0].nume, s[0].sediu);
    for(int i = 1; i < len; i++){
        fprintf(tmp,"%s,%s", s[i].nume, s[i].sediu);
    }
    fclose(tmp);
    remove("data/angajati_sedii.csv");
    rename("data/temp.csv", "data/angajati_sedii.csv");
}

void option2(){
    system("cls");
    FILE *ang_sed = fopen("data/angajati_sedii.csv", "r");
    if(ang_sed == NULL){
        perror("Unable to open the file");
        exit(1);
    }
    angajat date_angajat[100];
    char line[1024];
    int row = 0;
    while(fgets(line, sizeof(line), ang_sed)){
        char *token;
        int field = 0;
        token = strtok(line, ",");

        while(token != NULL){
            if(field == 0){
                strcpy(date_angajat[row].nume, token);
            }
            else 
                strcpy(date_angajat[row].sediu, token);
            field++;
            token = strtok(NULL, ",");
        }
        row++;
    }
    fclose(ang_sed);
    if(strcmp(date_angajat[0].nume, "") == 0){
        printf("\nNu exista angajati!\n");
    }
    else{
        print_angajati(date_angajat, row);
    }
    
    int option;
    printf("\n1 adaugare\n2 stergere\n3 back\n"); 
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        system("cls");
        angajat a;
        printf("Introduceti numele: ");
        fflush(stdin);
        gets(a.nume);
        printf("\nIntroduceti sediul: ");
        fflush(stdin);
        gets(a.sediu);
        strcat(a.sediu, "\n");
        adaugare_angajat(date_angajat, a, row);
        printf("\n");
        option2();
        break;
    case 2:
        system("cls");
        printf("Introduceti indexul angajatului pe care doriti sa-l stergeti\n");
        int i;
        scanf("%d", &i);
        sterge_angajat(date_angajat, row - 1, i - 1);
        printf("\n");
        option2();
        break;
    case 3:
        firstPage();
        break;
    default:
        break;
    }
}