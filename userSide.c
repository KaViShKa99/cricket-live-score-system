#include <stdio.h>
#include <stdlib.h>

int login();
void viewLiveScoreboard();
void viewScoreboard();

int main()
{
    int results =0,choice =0;

    results = login();

    if(results == 1){
            while( choice != 5){

                mainMenu();
                printf("Enter your choice :");
                scanf("%d",&choice);

                if(choice ==1){
                    system("cls");
                    viewLiveScoreboard();

                }else if(choice ==2){
                    system("cls");
                    viewScoreboard();

                }else if(choice ==3){
                    system("cls");
                    break;

                }
                else{
                    printf("!!! input invalid");
                }
            }
    }
    return 0;
}
void mainMenu()
{
    printf("\t\t 1. View live scoreboard\n");
    printf("\t\t 2.	View scoreboard\n");
    printf("\t\t 3.	Exit\n");

}
int login()
{
    int inputPssword=0;
    char inputName[20]="";
    int stop =0;

    while(stop != 1){
        printf("\t\tWelcome to cricket live score system\n\n");
        printf("\t\t\tSign In\n");
        printf("\tUser name(userName=user):");
        scanf("%s",&inputName);
        printf("\tPassword (password=1234):");
        scanf("%d",&inputPssword);
        if(inputPssword == 1234 && strcmp(inputName, "user") == 0)
        {
            stop =1;
        }else{
            system("cls");
            printf("\t\t!!invalid password or username\n\n");
            stop=0;
        }
    }
    return stop;
}
void viewLiveScoreboard()
{
    printf(" \xda");
                    for(int k=0 ;k<40;k++){
                        printf("\xc4\xc4\xc4");
                    }
                    printf("\n");

                    printf(" \xb3 %-10s(%-3d - %d) | overs %-3d .%-2d  |  *%-15s %-4d  *%-15s %-4d  | %-15s|  %-1d - %-2d | %-2d |\n",
                           "Sri Lanka"
                           ,250,8
                           ,45,4
                           ,"Avishka fernando",105
                           ,"Dushmantha chameera",15
                           ,"Maharaj"
                           ,3
                           ,43
                           ,13);


                    printf(" \xc0");
                     for(int k=0 ;k<40;k++){
                        printf("\xc4\xc4\xc4");
                    }
                    printf("\n");
}
void viewScoreboard()
{
    printf("\n\n--------------Batting %s ---------------------------------\n","sri lanka");
    printf("--------------------------------------------------------------\n");
    printf("| player name   | score  | 6 runs | 4 runs | ballfaced\n");
    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","kusal perera",35,3,0,30);
    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","Avishka fernando",12,2,0,8);
    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","Dananjya De silva",1,0,3);
    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","Kamindu mendis",10,1,6);
    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","Dasun shanaka",18,3,0,14);
    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","Wanindu hasaranga",12,2,0,8);
    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","chamika karunarathne",20,2,2,9);
    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","Bhanuka raapaksha",5,0,1,6);
    printf("-----------------------------------------------------\n");

    printf("\n\n");

    printf("\n\n--------------Bowling %s---------------------------------\n","south africa");
    printf("-------------------------------------------------------------\n");
    printf("| Bowlers name   | wickets  |  overs | runs |\n");
    printf("| %-10s          | %-2d     |  %-2d  | %-2d |\n","Rabada",2,6,20);
    printf("| %-10s          | %-2d     |  %-2d  | %-2d |\n","Maharaj",1,8,30);
    printf("| %-10s          | %-2d     |  %-2d  | %-2d |\n","shamsi",1,4,24);
    printf("| %-10s          | %-2d     |  %-2d  | %-2d |\n","markram",2,2,36);
    printf("-------------------------------------------------------------\n");
}
