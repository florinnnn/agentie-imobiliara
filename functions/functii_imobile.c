typedef struct imobil{
    char judet[100], oras[100], tip[100], vanz_inch[100];
    int pret, suprafata, nr_camere;
} imobil;

void print_imobile(imobil date_imobil[], int len){
    for(int i = 0; i < len; i++){
        printf("%d %s de %s la pretul %d | %d m^2 si %d camere | Judet: %s  Oras: %s\n", i+1, date_imobil[i].tip, date_imobil[i].vanz_inch, date_imobil[i].pret, date_imobil[i].suprafata, date_imobil[i].nr_camere, date_imobil[i].judet, date_imobil[i].oras);
    }
}

void adaugare_imobil(imobil date_imobil[], imobil im, int len){
    int i, added = 0;
    imobil tmp;
    if(strcmp(im.judet, date_imobil[len - 1].judet) > 0 || (strcmp(im.judet, date_imobil[len - 1].judet) == 0 && strcmp(im.oras, date_imobil[len - 1].oras) >= 0)){
        date_imobil[len] = im;
    }
    else{
        for(i = 0; i <= len; i++){
            if(added){
                im = date_imobil[i];
                date_imobil[i] = tmp;
                tmp = im;
            }
            else if(strcmp(im.judet, date_imobil[i].judet) < 0){
                tmp = date_imobil[i];
                date_imobil[i] = im;
                added = 1;
            }
            else if(strcmp(im.judet, date_imobil[i].judet) == 0 && strcmp(im.oras, date_imobil[i].oras) <= 0){
                tmp = date_imobil[i];
                date_imobil[i] = im;
                added = 1;
            }
        }
    }
    FILE *temp = fopen("data/temp.csv", "w");
    for(i = 0; i <= len; i++){
        fprintf(temp, "%s,%s,%s,%s,%d,%d,%d\n", date_imobil[i].judet, date_imobil[i].oras, date_imobil[i].tip, date_imobil[i].vanz_inch, date_imobil[i].pret, date_imobil[i].suprafata, date_imobil[i].nr_camere);
    }
    fclose(temp);
    remove("data/imobile.csv");
    rename("data/temp.csv", "data/imobile.csv");
}

void stergere_imobil(imobil date_imobil[], int len, int start_pos){
    for(start_pos; start_pos < len; start_pos++){
        date_imobil[start_pos] = date_imobil[start_pos + 1];
    }
    FILE *tmp = fopen("data/temp.csv", "w");
    if(len == 0){
        fclose(tmp);
        remove("data/imobile.csv");
        rename("data/temp.csv", "data/imobile.csv");
        return;
    }
    for(int i = 0; i < len; i++){
        fprintf(tmp, "%s,%s,%s,%s,%d,%d,%d\n", date_imobil[i].judet, date_imobil[i].oras, date_imobil[i].tip, date_imobil[i].vanz_inch, date_imobil[i].pret, date_imobil[i].suprafata, date_imobil[i].nr_camere);
    }
    fclose(tmp);
    remove("data/imobile.csv");
    rename("data/temp.csv", "data/imobile.csv");
}

void afisare_judet(imobil date_imobil[], char jud[], int len){
    int gasit = 0;
    for(int i = 0; i < len; i++){
        if(strcmp(date_imobil[i].judet, jud) == 0){
            gasit++;
            printf("%d %s de %s la pretul %d | %d m^2 si %d camere | Judet: %s  Oras: %s\n", gasit, date_imobil[i].tip, date_imobil[i].vanz_inch, date_imobil[i].pret, date_imobil[i].suprafata, date_imobil[i].nr_camere, date_imobil[i].judet, date_imobil[i].oras);
        }
    }
    if(!gasit){
        printf("Nu s-au gasit imobile in acel judet.\n");
    }
    printf("\nApasa orice pentru a te reintoarce. ");
    getch();
}

void afisare_oras(imobil date_imobil[], char oras[], int len){
    int gasit = 0;
    for(int i = 0; i < len; i++){
        if(strcmp(date_imobil[i].oras, oras) == 0){
            gasit++;
            printf("%d %s de %s la pretul %d | %d m^2 si %d camere | Judet: %s  Oras: %s\n", gasit, date_imobil[i].tip, date_imobil[i].vanz_inch, date_imobil[i].pret, date_imobil[i].suprafata, date_imobil[i].nr_camere, date_imobil[i].judet, date_imobil[i].oras);
        }
    }
    if(!gasit){
        printf("Nu s-au gasit imobile in acel oras.\n");
    }
    printf("\nApasa orice pentru a te reintoarce. ");
    getch();
}

void option4(){
    system("cls");
    FILE *imobile = fopen("data/imobile.csv", "r");
    if(imobile == NULL){
        perror("Unable to open the file!!");
        exit(1);
    }
    imobil date_imobil[100];
    char line[1024];
    int row = 0;
    while(fgets(line, sizeof(line), imobile)){
        char *token = strtok(line, ",");
        int field = -1;
        while(token != NULL){
            if (field == 0){
                strcpy(date_imobil[row].judet, token);
            }
            else if(field == 1){
                strcpy(date_imobil[row].oras, token);
            }
            else if(field == 2){
                strcpy(date_imobil[row].tip, token);
            }
            else if(field == 3){
                strcpy(date_imobil[row].vanz_inch, token);
            }
            else if(field == 4){
                date_imobil[row].pret = atoi(token);
            }
            else if(field == 5){
                date_imobil[row].suprafata = atoi(token);
            }
            else{
                date_imobil[row].nr_camere = atoi(token);
            }
            field++;
            token = strtok(NULL, ",");
        }
        row++;
    }
    fclose(imobile);
    print_imobile(date_imobil, row);
    int opt;
    printf("\n1 adaugare\n2 stergere\n3 afisare judet\n4 afisare oras\n5 back\n");
    scanf("%d", &opt);
    switch(opt){
        case 1:
            system("cls");
            imobil im;
            printf("Introduceti timpul imobilului: ");
            fflush(stdin);
            gets(im.tip);
            printf("Imobilul este de [vanzare/inchiriere]: ");
            fflush(stdin);
            gets(im.vanz_inch);
            printf("Pretul imobilului este: ");
            fflush(stdin);
            scanf("%d", &im.pret);
            printf("Suprafata imobilului este: ");
            scanf("%d", &im.suprafata);
            printf("Numarul de camere al imobilului este: ");
            scanf("%d", &im.nr_camere);
            fflush(stdin);
            printf("Judetul in care se afla imobilul este: ");
            gets(im.judet);
            fflush(stdin);
            printf("Orasul in care se afla imobilul este: ");
            gets(im.oras);
            fflush(stdin);
            adaugare_imobil(date_imobil, im, row);
            option4();
            break;
        case 2:
            system("cls");
            print_imobile(date_imobil, row);
            printf("\nIntroduceti indexul imobilului pe care doriti sa-l stergeti:\n");
            int index;
            scanf("%d", &index);
            stergere_imobil(date_imobil, row - 1, index - 1);
            option4();
            break;
        case 3:
            system("cls");
            char jud[100];
            printf("Introduceti judetul de unde vreti sa vedeti oferte: ");
            fflush(stdin);
            gets(jud);
            printf("\n");
            afisare_judet(date_imobil, jud, row);
            option4();
            break;
        case 4:
            system("cls");
            char oras[100];
            printf("Introduceti orasul de unde vreti sa vedeti ofertele: ");
            fflush(stdin);
            gets(oras);
            printf("\n");
            afisare_oras(date_imobil, oras, row);
            option4();
            break;
        case 5:
            firstPage();
            break;
        default:
            break;
    }
}