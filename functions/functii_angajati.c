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

void modificare_angajat(angajat ang[], int len, int i){
    system("cls");
    angajat new_ang;
    printf("Introduceti noul nume: ");
    fflush(stdin);
    gets(new_ang.nume);
    printf("Introduceti noul sediu: ");
    fflush(stdin);
    gets(new_ang.sediu);
    strcat(new_ang.sediu, "\n");
    ang[i] = new_ang;
    FILE *temp = fopen("data/temp.csv", "w");
    fprintf(temp, "%s,%s", ang[0].nume, ang[0].sediu);

    for(int i = 1; i <= len; i++){
        fprintf(temp,"%s,%s", ang[i].nume, ang[i].sediu);
    }


    fclose(temp);
    remove("data/angajati_sedii.csv");
    rename("data/temp.csv", "data/angajati_sedii.csv");
}

void afisare_oferte_angajat(angajat ang, int i){
    system("cls");
    printf("Angajatul %s de la sediul %s are repartizate urmatoarele imobile: \n\n", ang.nume, ang.sediu);
    
    FILE *imobile = fopen("data/imobile.csv", "r");
    if(imobile == NULL){
        perror("Eroare");
        exit(1);
    }
    char line[1024];
    int contor = 0;
    while(fgets(line, sizeof(line), imobile)){
        char *token = strtok(line, ",");
        int field = -1;
        char date_imobil[200], oras[200], judet[200];

        while(token != NULL){
            int si = 0;
            if(field == -1){
                si = atoi(token);
                field = 0;
                if(si == i){
                    token = strtok(NULL, ",");
                    contor++;
                    continue;
                }
                break;
            }
            
            if(field == 0){
                strcpy(judet, token);
            }
            else if(field == 1){
                strcpy(oras, token);
            }
            else if(field == 2){
                strcpy(date_imobil, token);
                printf("\t%s de", date_imobil);
            }
            else if(field == 3){
                strcpy(date_imobil, token);
                printf(" %s la pretul ", date_imobil);
            }
            else if(field == 4){
                si = atoi(token);
                printf("%d | ", si);
            }
            else if(field == 5){
                si = atoi(token);
                printf("%d m^2 si ", si);
            }
            else{
                si = atoi(token);
                printf("%d camere | Judet: %s Oras: %s\n\n", si, judet, oras);
            }
            field++;
            token = strtok(NULL, ",");
        }
    }
    fclose(imobile);
    if(contor == 0){
        printf("\nAngajatul selectat nu are nici o oferta repartizata!\n");
    }
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
    printf("\n1 Adaugare angajat\n2 Stergere angajat\n3 Modificare angajat\n4 Oferte repartizate\n5 Inapoi\n"); 
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
        print_angajati(date_angajat, row);
        printf("Introduceti indexul angajatului pe care doriti sa-l stergeti (0 - cancel)\nIn cazul in care introduceti un index mai mare decat indexul ultimului angajat, se va sterge ultimul\nla fel si la primul angajat");
        int i;
        scanf("%d", &i);
        if(i == 0){
            option2();
            break;
        }
        sterge_angajat(date_angajat, row - 1, i - 1);
        printf("\n");
        option2();
        break;
    case 3:
        system("cls");
        print_angajati(date_angajat, row);
        printf("Introduceti indexul angajatului pe care doriti sa-l modificati (0 - cancel)");
        int index;
        scanf("%d", &index);
        if(index == 0){
            option2();
            break;
        }
        modificare_angajat(date_angajat, row - 1, index - 1);

        option2();
        break;
    case 4:
        system("cls");
        print_angajati(date_angajat, row);
        printf("\nIntroduceti indexul angajatului: ");
        int ind;
        scanf("%d", &ind);
        if(ind > row || ind < 1){
            printf("\nAngajatul nu exista!\n");
        }
        else
            afisare_oferte_angajat(date_angajat[ind-1], ind);
        printf("Pentru a te reintoarce la meniul de angajati apasa orice ");
        getch();
        option2();
        break;
    
    case 5:
        firstPage();
        break;
    default:
        break;
    }
}