void option5(){
    system("cls");
    char yesno[1];
    printf("Esti sigur ca vrei sa iesi? [y/n] ");
    scanf("%s", yesno);
    if(!strcmp(yesno, "n")){
        firstPage();
    }
    else 
        system("cls");
}