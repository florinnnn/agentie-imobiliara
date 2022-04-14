#include "functii_angajati.c"
#include "functii_firma.c"
#include "functii_clienti.c"
#include "functii_imobile.c"
#include "inchidere.c"

void firstPage();

void secondPage(int option){
    switch (option)
    {
    case 1:
        option1();
        break;
    case 2:
        option2();
        break;
    case 3:
        option3();
        break;
    case 4:
        option4();
        break;
    case 0:
        option5();
        break;
    default:
        break;
    }
    
}
void menu(){
    printf("1 Detalii firma \n2 Detalii angajati \n3 Detalii clienti\n4 Imobile disponibile\n0 Iesire\n");
}
void firstPage(){
    system("cls");
    menu();
    int option;
    scanf("%d", &option);
    while(option < 0 || option > 4){
        menu();
        scanf("%d", &option);
    }
    secondPage(option);
}