#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


struct BattingContent
{
    int score;
    int one;
    int two;
    int three;
    int four;
    int six;
};
struct BowllingContent
{
    int wickets;
    int balls;
    int overs;
    int runs_for_over;
};

struct PlayerInformations
{
    char name[20];
    char countryName[20];
    char talent[40];//bowler , batsman or wicket keeper
    char battingStatus[20]; //out or not out
    struct BattingContent bat;
    struct BowllingContent bowl;

} ;

struct CountryList {
    int players;
    int totalScore;
    int totalWickets;
    int totalOvers;
    int totalBalls;
    char countryName[40];

//}countryDetailsArray[100];
};
struct Data{
    struct PlayerInformations playersArray[100];
};
struct CountryInfo{
    struct CountryList countryDetailsArray[100];
};
struct PlayersBattingContent{
    struct PlayerInformations playersArray[100];
};
struct AllScoresAndDetailsOfCountry{
    struct CountryList countryDetailsArray[100];
};

struct Data playersData ;//getting the players data
struct CountryInfo countryData = {{0}};//getting the country data
struct PlayersBattingContent battingContent ;//getting the players batting content
struct AllScoresAndDetailsOfCountry fBCountry,secondBattingCountry;

int number_of_players =0,player=0;

int score=30,six_runs=3,four_runs=4,ball_faced=123;

int wickets =3,runs_of_overs =20,overs=3;
int i=0;

int array_index_count=0;
int teamOnePlayers =0,teamTwoPlayers=0;


//variables of add team fun
int countryCount=0,playerChoice = 0 ,countryAdd=0 ;

//variables of mange live scoreboard fun
int firstBattingCountry =0 ,firstBatsman =0,secondBatsman=0,firstBowler=0;
int adminSelectingCount=1;
int bowlersCount=0;
int bowlerOrder[20]={};

int login();//login function
void mainMenu();//main menu information list function
//validation functions
void StringCheckValidation(char *name);//checking numbers and special characters
void IntegerCheckValidation(char *num);//checking string and special characters

//main menu functions
void manageTeam();
void manageLiveScoreboard();
void manageScorboard();
void genarateScoreboardReport();

//manage team functions
void addTeam();
void viewPlayerRecords();
void deleteWholeRecord(int row,struct Data playerInfoData);

//mange live scoreboard functions
void setBattingOrder(int countryIndex);
void battingOrderPrint(int countryIndex);
void setBowlingOrder(int countryIndex);
void bowlingOrderPrint(int countryIndex);
void playersAndScoresUpdate(int firstBatsmanIndex,int secondBatsmanIndex,int firstBowlerIndex,int battingCountryIndex,int bowlingCountryIndex);
char *playerSelect(int index);
void selectBatsman(int batsman_index,int country_index);
void selectBowler(int bowler_index,int country_index);
void printLivesScoreboard(int firstBatsmanIndex,int secondBatsmanIndex,int firstBowlerIndex,int battingCountryIndex,int bowlingCountryIndex);
int getPlayerScore(int index);
//manage scoreboard functions

void manageScoreboardMenu();
void searchPlayer();
void addNewPlayer();
void updatePlayerInformation();
void deletePlayer();

//read data from file
void readData();
//extra functions
void getAllPlayers(int country_index); //get all players from selected country

void readData() {

    FILE *playersDataFile,*countryDataFile,*battingContentDataFile;

    struct Data getPlayersData;
    struct CountryInfo getCountryData;
    struct PlayersBattingContent getBattingContent ;

    int team_1 =0;
    int team_2 =0;

//    battingContentDataFile = fopen("playersBattingContent.dat","r");
//    if (battingContentDataFile == NULL) {
//        fprintf(stderr, "\nError to open the country data file\n");
//        exit (1);
//    }
//    while(fread(&getBattingContent, sizeof(struct Data), 1, battingContentDataFile))
//        fflush(stdin);
//
//    battingContent.playersArray[0].bat->score = getBattingContent.playersArray[0].bat->score;
//
//    fclose(battingContentDataFile);
//    fflush(stdin);
/////////////////////////////////////////////////////////////////////
    countryDataFile= fopen ("countryInfo.dat", "r");
    if (countryDataFile == NULL) {
        fprintf(stderr, "\nError to open the country data file\n");
        exit (1);
    }
    while(fread(&getCountryData, sizeof(struct Data), 1, countryDataFile))

        fflush(stdin);
        countryData.countryDetailsArray[0].players = getCountryData.countryDetailsArray[0].players;
        countryData.countryDetailsArray[1].players = getCountryData.countryDetailsArray[1].players;

        strcpy(countryData.countryDetailsArray[0].countryName,getCountryData.countryDetailsArray[0].countryName);
        strcpy(countryData.countryDetailsArray[1].countryName,getCountryData.countryDetailsArray[1].countryName);

    fclose(countryDataFile);
    fflush(stdin);

    playersDataFile= fopen ("playerInfo.dat", "r");
    if (playersDataFile == NULL) {
        fprintf(stderr, "\nError to open the player information file\n");
        exit (1);
    }
    while(fread(&getPlayersData, sizeof(struct Data), 1, playersDataFile))
        fflush(stdin);
        for (int j = 0; j <countryData.countryDetailsArray[0].players+countryData.countryDetailsArray[1].players ; j++) {
            strcpy(playersData.playersArray[j].name,getPlayersData.playersArray[j].name);
            strcpy(playersData.playersArray[j].countryName,getPlayersData.playersArray[j].countryName);
            strcpy(playersData.playersArray[j].talent,getPlayersData.playersArray[j].talent);
            strcpy(playersData.playersArray[j].battingStatus,getPlayersData.playersArray[j].battingStatus);
        }
    fclose(playersDataFile);
    fflush(stdin);

}
int main()
{
    readData();
    printf("\t\t \xFE %-20s [batsman]\t \n",playersData.playersArray[0].name);
    printf("\t\t \xFE %-20d [batsman]\t \n",countryData.countryDetailsArray[0].players);
    int results =0,choice =0;

//    results = login();
//    system("cls");
//    if(results == 1){

            while( choice != 5){
//                system("cls");
                printf("\n");
                mainMenu();
                printf("\n");
                printf("\tEnter your choice :");
                scanf("%d",&choice);


                if(choice ==1){
                    system("cls");
                    manageTeam();

                }else if(choice ==2){
                    system("cls");
                    manageLiveScoreboard();

                }else if(choice ==3){
//                    system("cls");
//                    manageScorboard();

                }else if(choice ==4){
//                    system("cls");
//                    genarateScoreboardReport();

                }else if(choice ==5){
                    break;
                }
                else{
                    printf("!!! input invalid");
                }
            }
//    }
    return 0;
}

int login()
{
    int inputPssword=0;
    char inputName[20]="";
    int stop =0;

    system("COLOR 03");
    while(stop != 1){
        printf("\t\tWelcome to cricket live score system\n\n");
        printf("\t\t\tSign In\n");
        printf("\tUser name(userName = admin):");
        scanf("%d",&inputName);
        printf("\tPassword (password = 1234):");
        scanf("%d",&inputPssword);

        if(inputPssword == 1234 && strcmp(inputName, "admin") == 0)
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
void mainMenu()
{
//    system("cls");
    system("COLOR 04");
    printf("\n\n\n");
    printf("\t\t [1]. Manage team\n");
    printf("\t\t [2]. Manage live scoreboard\n");
    printf("\t\t [3]. Manage scoreboard\n");
    printf("\t\t [4]. Generate scoreboard report\n");
    printf("\t\t [5]. Exit\n");

}
void manageTeamMenu()
{
    system("COLOR 0C");
    printf("\t\t [1]. Add team	\n");
    printf("\t\t [2]. Viewing player records\n");
    printf("\t\t [3]. Deleting player records\n");
    printf("\t\t [4]. Go to Menu\n");
}
void manageTeam()
{
    int choice=0;
        while( choice != 5){

        manageTeamMenu();
        printf("Enter your choice :");
        scanf("%d",&choice);

        if(choice ==1){
            system("cls");
            addTeam();
            system("cls");
        }else if(choice ==2){
            system("cls");
            viewPlayerRecords();
        }else if(choice ==3){
            system("cls");
            deletePlayer();
        }else if(choice ==4){
            system("cls");
             break;
        }
        else{
            printf("!!! input invalid");
        }
    }
}
void viewPlayerRecords()
{
    int firstCountry = 0,secondCountry = 1;
    getAllPlayers(0);//selecting team one
    printf("\n\n");
    if(countryData.countryDetailsArray[1].players >0){
        getAllPlayers(1);//selecting team two
    }
    printf("\n\n");

}
void getAllPlayers(int country_index)
{
    readData();
    printf("\t\t\tTeam %-20s  \n\n",countryData.countryDetailsArray[country_index].countryName);
    for(int rows =0;rows<countryData.countryDetailsArray[0].players+countryData.countryDetailsArray[1].players;rows++){
        if(strcmp(countryData.countryDetailsArray[country_index].countryName, playersData.playersArray[rows].countryName)==0){
            if(strcmp(playersData.playersArray[rows].talent, "batsman") ==0){
                printf("\t\t \xFE %-20s [batsman]\t \n",playersData.playersArray[rows].name);
            }else if(strcmp(playersData.playersArray[rows].talent, "bowler") ==0){
                printf("\t\t \xFE %-20s [bowler]\t \n",playersData.playersArray[rows].name);
            }else if(strcmp(playersData.playersArray[rows].talent, "wk") ==0){
                printf("\t\t \xFE %-20s [wk]\t \n",playersData.playersArray[rows].name);
            }
        }
    }

//    fclose (playerInfo);

}
void StringCheckValidation(char *name)
{
    int numDigitCount=0,strDigitCount=0,specialDigitCount=0;
    bool flag = true;
    int characterAsciiValue ;

    while(flag)
    {
        gets(name);
        for(int i = 0; i < strlen(name); i++){

            characterAsciiValue = (int)*(name+i);

            if(isalpha(name[i])){
                strDigitCount++;
            } else if(((characterAsciiValue >=0 && characterAsciiValue < 47)||(characterAsciiValue >= 58 && characterAsciiValue <= 64)||(characterAsciiValue >=91 && characterAsciiValue <= 96)||(characterAsciiValue >= 123) )){
                if( characterAsciiValue !=32){
                    specialDigitCount++;
                }
            }else{
                numDigitCount++;
            }
        }

        if(numDigitCount == 0 && strDigitCount > 0 && specialDigitCount == 0){

            flag = false;
            break;
        } else{
            printf("\n\t\tInvalid Input...! [Input Value has %d number%s include  , please type correctly]\n",numDigitCount,((numDigitCount>0)? "s" : ""));
            printf ( "\n\t\tEnter Again:- ");
        }
        strDigitCount =0;
        numDigitCount=0;
        specialDigitCount=0;
    }
}
void IntegerCheckValidation(char *num)
{
    int numDigitCount=0,strDigitCount=0,specialDigitCount=0;
    bool flag = true;
    int characterAsciiValue ;

    while(flag)
    {
        gets( num);
        for(int i = 0; i < strlen(num); i++){

            characterAsciiValue = (int)*(num+i);

            if(isalpha(num[i])){
                strDigitCount++;
            } else if(((characterAsciiValue >=0 && characterAsciiValue < 47)||(characterAsciiValue >= 58 && characterAsciiValue <= 64)||(characterAsciiValue >=91 && characterAsciiValue <= 96)||(characterAsciiValue >= 123) )){
                if( characterAsciiValue !=32){
                    specialDigitCount++;
                }
            }else{
                numDigitCount++;
            }
        }

        if(strDigitCount == 0 && numDigitCount > 0 && specialDigitCount == 0){

            flag = false;
            break;
        } else{
            printf("\n\t\tInvalid Input...! [Input Value has %d String character%s include  , please type correctly]\n",numDigitCount,((numDigitCount>0)? "s" : ""));
            printf ( "\n\t\tEnter Again:- ");
        }
        strDigitCount =0;
        numDigitCount=0;
        specialDigitCount=0;
    }
}
void addTeam(){

    struct PlayerInformations players[100];
    struct CountryList countries[100];
    struct Data data;
    struct CountryInfo countryData;

    if(countryCount !=2){

                printf(" \t\tTeam 0%d\t\n",countryCount+1);
                printf("How many players do you want to add? : ");
                scanf("%d",&number_of_players);

                for(i=teamOnePlayers;i<number_of_players+teamOnePlayers;i++){


                        if(countryAdd !=1){//one time add only one country
                            fflush(stdin);
                            printf("\n\tAdd Name Of The Country : ");
                                if(countryCount==0){
//                                    StringCheckValidation(countryDetailsArray[0].countryName);//can be input only string
                                    StringCheckValidation(countries[0].countryName);//can be input only string
                                    countries[0].players = number_of_players;

//                                    players[0].players = number_of_players;
                                    printf("c1    %d\n",countries[0].players);

                                }else if(countryCount==1){
//                                    StringCheckValidation(countryDetailsArray[1].countryName);//can be input only string
                                    StringCheckValidation(countries[1].countryName);//can be input only string
                                    countries[1].players = number_of_players;

//                                    players[1].players = number_of_players;
                                    printf("c2    %d\n",countries[1].players);

                                }
                            fflush(stdin);
                            countryAdd++;
                            countryCount++;
                        }
                        system("cls");
                        printf(" \t\tTeam %s\t\n\n",countries[countryCount-1].countryName);
                        printf("\tPlayer [%0d]\n",i+1);
                        printf("\n\tDo yo want add bowler or batter(choose 1 or 2)\n\n\t\t (01) Bowler\n\t\t (02) Batsman\n\t\t (03) Wicket keeper \t\n\t\t....");
                        scanf("%d",&playerChoice);

                        if(playerChoice == 1){
                            fflush(stdin);
                            printf("\n\t\tEnter Bowler Name : ");
//                            StringCheckValidation(playersArray[i].name);
                            StringCheckValidation(players[i].name);

                            fflush(stdin);

                            strcpy(players[i].talent,"bowler");//adding talent for bowler
                            strcpy(players[i].countryName,countries[countryCount-1].countryName);//adding the country



                        }else if(playerChoice ==2){
                            fflush(stdin);
                            printf("\n\t\tEnter Batsman Name : ");

                            StringCheckValidation(players[i].name);//can be input only string
                            fflush(stdin);

                            strcpy(players[i].talent,"batsman");//adding talent for batsman
                            fflush(stdin);
                            strcpy(players[i].countryName,countries[countryCount-1].countryName);//adding the country
                            fflush(stdin);
                        }else if(playerChoice ==3){
                            fflush(stdin);
                            printf("\n\t\tEnter Wicket keeper Name : ");

                            StringCheckValidation(players[i].name);//can be input only string
                            fflush(stdin);


                            strcpy(players[i].talent,"wk");//adding talent for wicket keeper
                            fflush(stdin);
                            strcpy(players[i].countryName,countries[countryCount-1].countryName);//adding the country
                            fflush(stdin);
                        }else{
                            printf("\n\t\tyour input isn't valid\n");

                        }


                    FILE *fp ,*cp;
                    fp= fopen ("playerInfo.dat", "w");
                    if (fp == NULL) {
                        fprintf(stderr, "\nError to open the player info file\n");
                        exit (1);
                    }

                    data.playersArray[i] = players[i];


                    fwrite (&data, sizeof(struct Data), 1, fp);
                    if(fwrite != 0){

                        printf("Contents to file written successfully !\n");
                    }
                    else{
                        printf("Error writing file !\n");
                    }
                    fclose (fp);

                            cp= fopen ("countryInfo.dat", "w");

                            if (cp == NULL) {
                                fprintf(stderr, "\nError to open the country info file\n");
                                exit (1);
                            }
                            if(countryCount-1 ==0){
                                countryData.countryDetailsArray[0] = countries[0];
                            }else if(countryCount-1 ==1){
                                countryData.countryDetailsArray[1] = countries[1];
                            }

                            fwrite (&countryData, sizeof(struct Data), 1, cp);
                            fclose (cp);

                }

                if(countryCount == 1){
                    teamOnePlayers += number_of_players;
                } else if(countryCount == 2){
                    teamTwoPlayers += number_of_players;
                }
        countryAdd=0;
    }else{
        printf("only two country for valid one match\n");
    }
}
void manageLiveScoreboard()
{
//    printLivesScoreboard(firstBatsman-1,secondBatsman-1,bowlerOrder[firstBowler-1 ],0,1);
//    if(countryCount > 1){
        int battingCountryIndex =0;
        int bowlingCountryIndex =0;

        printf("Enter first batting country (choose 1 or 2)\n\n (01) %s\n (02) %s\n \t",countryData.countryDetailsArray[0].countryName,countryData.countryDetailsArray[1].countryName);
        scanf("%d",&firstBattingCountry);
        fflush(stdin);
//        IntegerCheckValidation((char *) firstBattingCountry);
        fflush(stdin);

        if(firstBattingCountry == 1){

            battingCountryIndex = 0;
            bowlingCountryIndex =1;

            int first_batsman_index  = firstBatsman - 1 ;
            int second_batsman_index = secondBatsman-1 ;
            int first_bowler_index = firstBowler-1 ;

            setBattingOrder(0);
            setBowlingOrder(1);

//            printf(" \xda");
//            for(int k=0 ;k<40;k++){
//                printf("\xc4\xc4\xc4");
//            }
//            printf("\n");
//
//            printf(" \xb3 %-10s(%-3d - %d) | overs %-3d .%-2d  |  *%-15s %-4d  *%-15s %-4d  | %-15s|  %-1d - %-2d | %-2d |\n",
//                   "Sri Lanka"
//                    ,250,8
//                    ,45,4
//                    ,"Avishka fernando",105
//                    ,"Dushmantha chameera",15
//                    ,"Maharaj"
//                    ,3
//                    ,43
//                    ,13);
//
//
//            printf(" \xc0");
//            for(int k=0 ;k<40;k++){
//                printf("\xc4\xc4\xc4");
//            }
            printf("\n");
            system("cls");
            printLivesScoreboard(firstBatsman-1,secondBatsman-1,bowlerOrder[firstBowler-1 ],battingCountryIndex,bowlingCountryIndex);
            playersAndScoresUpdate( firstBatsman-1,secondBatsman-1,bowlerOrder[firstBowler-1 ],battingCountryIndex,bowlingCountryIndex);
//            playersAndScoresUpdate( firstBatsman-1,secondBatsman-1,bowlerOrder[firstBowler-1 ],battingCountryIndex,bowlingCountryIndex);
//            printLivesScoreboard(0,0,0,0,0);
        } else if(firstBattingCountry == 2){
            printf("Team two starting to the match");
        } else{
            printf("Input Invalid");
        }

//    }else{
//        printf("\tPLEASE ADD PLAYER INFORMATION !!!!\n\n");
//    }
}

void printLivesScoreboard(int firstBatsmanIndex,int secondBatsmanIndex,int firstBowlerIndex,int battingCountryIndex,int bowlingCountryIndex) {

    printf("\n ");
    printf("\xda");
    for (int k = 0; k < 40; k++) {
        printf("\xc4\xc4\xc4");
    }
    printf("\n");
//            printf(" \xb3 %-10s(%-3d - %d) | overs %-3d .%-2d  |  *%-15s %-4d  *%-15s %-4d  | e%-15s|  %-1d - %-2d | %-2d |\n"
            printf(" \xb3"
                   " %-10s"
                   "(%-3d - %d) "
                   "| overs %-3d .%-2d  "
                   "|  *%-15s "
                   "%-4d  "
                   "*%-15s "
                   "%-4d  "
                   "| %-15s"
                   "|  %-1d "
                   "- %-2d "
                   "| %-2d |\n"
                    ,countryData.countryDetailsArray[battingCountryIndex].countryName
                    ,countryData.countryDetailsArray[battingCountryIndex].totalScore,countryData.countryDetailsArray[battingCountryIndex].totalWickets
                    ,countryData.countryDetailsArray[battingCountryIndex].totalOvers,countryData.countryDetailsArray[battingCountryIndex].totalBalls
                    ,playerSelect(firstBatsmanIndex)
                    ,getPlayerScore(firstBatsmanIndex)
                    ,playerSelect(secondBatsmanIndex )
                    ,getPlayerScore(secondBatsmanIndex)
                    ,playersData.playersArray[firstBowlerIndex].name
                    ,playersData.playersArray[firstBowlerIndex].bowl.wickets
                    ,playersData.playersArray[firstBowlerIndex].bowl.runs_for_over
                    ,playersData.playersArray[firstBowlerIndex].bowl.balls);

    printf(" \xc0");
    for (int k = 0; k < 40; k++) {
        printf("\xc4\xc4\xc4");
    }
    printf("\n");
}
int getPlayerScore(int index)
{
    return playersData.playersArray[index].bat.score;

}
void setBattingOrder(int countryIndex)
{
    battingOrderPrint(countryIndex);

    printf("Enter your batting order (choose 1,2,3...) \n");
    printf("\n\t First batsman :");
    scanf("%d",&firstBatsman);
    printf("\n\t Second batsman :");
    scanf("%d",&secondBatsman);

}

void battingOrderPrint(int countryIndex)
{
    readData();
    printf("\n\n--------------Batting %s ----------------\n",countryData.countryDetailsArray[countryIndex].countryName);
    printf("---------------------------------------------\n");
    printf("| NO | player name    |  batsman or bowler | \n");

    for(int rows =0;rows<countryData.countryDetailsArray[0].players+countryData.countryDetailsArray[1].players;rows++){
        if(strcmp(countryData.countryDetailsArray[countryIndex].countryName, playersData.playersArray[rows].countryName)==0){
            if(strcmp(playersData.playersArray[rows].talent, "batsman") ==0){
                printf("| %d. | %-20s(batsman)\t|\n",rows+1,playersData.playersArray[rows].name);
            }else if(strcmp(playersData.playersArray[rows].talent, "bowler") ==0){
                printf("| %d. | %-20s(bowler)\t|\n",rows+1,playersData.playersArray[rows].name);
            }else if(strcmp(playersData.playersArray[rows].talent, "wk") ==0){
                printf("| %d. | %-20s(wk)\t|\n",rows+1,playersData.playersArray[rows].name);
            }else{
                printf("| %d. | %-20s(c)\t|\n",rows+1,playersData.playersArray[rows].name);
            }
        }
    }
}

void setBowlingOrder(int countryIndex)
{
    bowlingOrderPrint(countryIndex);
    printf("Enter your Bowler order (choose 1,2,3...) \n");
    printf("\n\t First bowler :");
    scanf("%d",&firstBowler);
}

void bowlingOrderPrint(int countryIndex)
{
    printf("\n\n--------------Bowling %s ----------------\n",countryData.countryDetailsArray[countryIndex].countryName);
    printf("---------------------------------------------\n");
    printf("| NO | Bowler name      | \n");

    for(int rows =0;rows<countryData.countryDetailsArray[0].players+countryData.countryDetailsArray[1].players;rows++){
         //bowler no list

        if(strcmp(countryData.countryDetailsArray[countryIndex].countryName, playersData.playersArray[rows].countryName)==0){

            if(strcmp(playersData.playersArray[rows].talent, "bowler")==0){

                //initialize bowler_order array above on the int main
                bowlerOrder[bowlersCount]=rows;//adding bowler from bowling team

//                printf("| %d. | %-20s\t|\n",i,playersArray[rows].name);
                printf("| %d. | %-20s\t|\n",bowlersCount+1,playersData.playersArray[rows].name);
                bowlersCount++;
            }

        }
    }
}

// selecting player
char *playerSelect(int index)
{
    return playersData.playersArray[index].name;
}
// selecting the next batsman or current batsman
void selectBatsman(int batsman_index,int country_index)
{
    int player_out_or_not=0;
    int n=0;

    struct PlayerInformations players[100];
    struct PlayersBattingContent addBattingContent;
    struct BattingContent bat,newBat;

    printf("player out or not out \n (01) yes\n (02) no\n"); //not out
    scanf("%d",&player_out_or_not);

    if(player_out_or_not == 1){
        strcpy(playersData.playersArray[batsman_index].battingStatus,"out");

        battingOrderPrint(country_index);                                       //batting order
        printf("Enter new batsman (choose 1,2,3...) \n");
        printf("\n\t new batsman :");
        scanf("%d",&firstBatsman);

    }else if(player_out_or_not ==2){

//            bat = (struct BattingContent*) malloc(n * sizeof(struct BattingContent));
//            scanf("%d",&(bat+batsman_index)->score);

            strcpy(playersData.playersArray[batsman_index].battingStatus,"notOut");
            printf("Add player total runs :");
            scanf("%d",&players[batsman_index].bat.score);
            printf("Add player one run :");
            scanf("%d",&playersData.playersArray[batsman_index].bat.one);
            printf("Add player two runs :");
            scanf("%d",&playersData.playersArray[batsman_index].bat.two);
            printf("Add player three runs :");
            scanf("%d",&playersData.playersArray[batsman_index].bat.three);
            printf("Add player six runs :");
            scanf("%d",&playersData.playersArray[batsman_index].bat.six);
            printf("Add player four runs :");
            scanf("%d",&playersData.playersArray[batsman_index].bat.four);
            fflush(stdin);
            fflush(stdin);

//            FILE *battingContentDataFile;
//
//            battingContentDataFile = fopen("playersCountryAllDetails.dat","r");
//            if (battingContentDataFile == NULL) {
//                fprintf(stderr, "\nError to open the country data file\n");
//                exit (1);
//            }
//            while(fread(&getBattingContent, sizeof(struct Data), 1, battingContentDataFile))
//                fflush(stdin);
//
//            battingContent.playersArray[0].bat.score = getBattingContent.playersArray[0].bat.score;
//
//            fclose(battingContentDataFile);
//            fflush(stdin);

    }else{
        printf("your input isn't valid");
    }

}
void writeCountryAllScoresAndWickets(int battingCountryIndex){

        FILE *fBattingCountry,*sBattingCountry;
        struct AllScoresAndDetailsOfCountry fBatCountry,sBatCountry;


        if(battingCountryIndex == 0){

            fBattingCountry = fopen("fBattingCountry.dat","w");
            if (fBattingCountry == NULL) {
                fprintf(stderr, "\nError to open the player batting content file\n");
                exit (1);
            }

            fBatCountry.countryDetailsArray[0].totalScore = countryData.countryDetailsArray[battingCountryIndex].totalScore;
            fBatCountry.countryDetailsArray[0].totalWickets = countryData.countryDetailsArray[battingCountryIndex].totalWickets;
            fBatCountry.countryDetailsArray[0].totalOvers = countryData.countryDetailsArray[battingCountryIndex].totalOvers;
            fBatCountry.countryDetailsArray[0].totalBalls = countryData.countryDetailsArray[battingCountryIndex].totalBalls;

            fwrite (&fBatCountry, sizeof(struct Data), 1, fBattingCountry);

            printf("Contents to file written successfully !\n");

            fclose (fBattingCountry);

        } else if(battingCountryIndex == 1){

            sBattingCountry = fopen("sBattingCountry.dat","w");
            if (fBattingCountry == NULL) {
                fprintf(stderr, "\nError to open the second batting country file\n");
                exit (1);
            }

        }



}

// selecting the next bowler or current bowler
void selectBowler(int bowler_index,int country_index)
{
    int value;

    int player_update_or_not=0;

    printf("Add new bowler or update current bowler \n (01) yes\n (02) no\n"); //not out
    scanf("%d",&player_update_or_not);

    if(player_update_or_not == 1){

        bowlingOrderPrint(country_index);                                       //batting order
        printf("Enter new bowler (choose 1,2,3...) \n");
        printf("\n\t new bowler :");
        scanf("%d",&bowler_index);

    }else if(player_update_or_not ==2){

        printf("Update bowler wickets :");
        scanf("%d",&playersData.playersArray[bowler_index].bowl.wickets);
        printf("Update bowler overs :");
        scanf("%d",&playersData.playersArray[bowler_index].bowl.overs);
        printf("Update bowler balls :");
        scanf("%d",&playersData.playersArray[bowler_index].bowl.balls);
        printf("Update per runs for over :");
        scanf("%d",&playersData.playersArray[bowler_index].bowl.runs_for_over);


    }else{
        printf("your input isn't valid");
    }
}
//update function of live scoreboard manage
void playersAndScoresUpdate(int firstBatsmanIndex,int secondBatsmanIndex,int firstBowlerIndex,int battingCountryIndex,int bowlingCountryIndex)
{
    int update_palyer_choice=0;
    int select_player=0;
    int exit =0;
    bool flag =true;

    printf("saved data : %d",countryData.countryDetailsArray[battingCountryIndex].totalScore);

    printf("\n\t\t\t Do you want to update live score board \n \t\t\t\t (01) yes\n \t\t\t\t (02) no\n");
    scanf("%d",&update_palyer_choice);

    if(update_palyer_choice ==1){

            while(flag)
            {

                printf("choose your option for update (1 ,2,3,4,5,6 or 7)\n");
                printf("(01) %s\n",playerSelect(firstBatsmanIndex));
                printf("(02) %s\n",playerSelect(secondBatsmanIndex));
                printf("(03) %s\n",playerSelect(firstBowlerIndex));
                printf("(04) Total score\n");
                printf("(05) Total wickets\n");
                printf("(06) Total overs\n");
                printf("(07) Total balls\n");

                scanf("%d",&select_player);
                if(select_player == 1){

                    selectBatsman(firstBatsmanIndex,battingCountryIndex);

                }else if(select_player == 2){

                    selectBatsman(secondBatsmanIndex,battingCountryIndex);

                }else if(select_player == 3){

                    selectBowler(firstBowlerIndex,bowlingCountryIndex);

                }else
                    if(select_player == 4){
                    printf("Update total score :");
                    scanf("%d",&countryData.countryDetailsArray[battingCountryIndex].totalScore);
                }else if(select_player == 5){
                    printf("Update total wickets :");
                    scanf("%d",&countryData.countryDetailsArray[battingCountryIndex].totalWickets);
                }else if(select_player == 6){
                    printf("Update total overs :");
                    scanf("%d",&countryData.countryDetailsArray[battingCountryIndex].totalOvers);
                }else if(select_player == 7){
                    printf("Update total balls :");
                    scanf("%d",&countryData.countryDetailsArray[battingCountryIndex].totalBalls);
                }
                else{
                    printf("your input isn't valid");
                }

                writeCountryAllScoresAndWickets( battingCountryIndex );// all scores and wickets write in the file

                printf("Do you want to exit?\n (01) yes\n (02) no\n");
                scanf("%d",&exit);

                if(exit==1){
                    flag=false;
                    break;
                }

            }

    }else if(update_palyer_choice ==2){
        system("cls");
    }else{
        printf("your input isn't valid");
    }
}
//void manageScorboard()
//{
//    system("COLOR 06");
//    int choice=0;
//
//    printf("\n\n--------------Batting %s ---------------------------------\n","sri lanka");
//    printf("--------------------------------------------------------------\n");
//    printf("| player name   | score  | 6 runs | 4 runs | ballfaced\n");
//    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","kusal perera",35,3,0,30);
//    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","Avishka fernando",12,2,0,8);
//    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","Dananjya De silva",1,0,3);
//    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","Kamindu mendis",10,1,6);
//    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","Dasun shanaka",18,3,0,14);
//    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","Wanindu hasaranga",12,2,0,8);
//    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","chamika karunarathne",20,2,2,9);
//    printf("| %-20s         | %-2d   | %-1d   | %-1d   | %-2d     \n","Bhanuka raapaksha",5,0,1,6);
//    printf("-----------------------------------------------------\n");
//
//    printf("\n\n");
//
//    printf("\n\n--------------Bowling %s---------------------------------\n","south africa");
//    printf("-------------------------------------------------------------\n");
//    printf("| Bowlers name   | wickets  |  overs | runs |\n");
//    printf("| %-10s          | %-2d     |  %-2d  | %-2d |\n","Rabada",2,6,20);
//    printf("| %-10s          | %-2d     |  %-2d  | %-2d |\n","Maharaj",1,8,30);
//    printf("| %-10s          | %-2d     |  %-2d  | %-2d |\n","shamsi",1,4,24);
//    printf("| %-10s          | %-2d     |  %-2d  | %-2d |\n","markram",2,2,36);
//    printf("-------------------------------------------------------------\n");
//
//    printf("\n\n");
//
//
//    while( choice != 5){
//
//        manageScoreboardMenu();
//        printf("Enter your choice :");
//        scanf("%d",&choice);
//
//        if(choice ==1){
//            system("cls");
//            searchPlayer();
//        }else if(choice ==2){
//            system("cls");
//            addNewPlayer();
//        }else if(choice ==3){
//            system("cls");
//            updatePlayerInformation();
//        }else if(choice ==4){
//            system("cls");
//            deletePlayer();
//        }else if(choice ==5){
//            system("cls");
//            break;
//        }
//        else{
//            printf("!!! input invalid");
//        }
//    }
//}
void genarateScoreboardReport()
{
    printf("\t\t Generating scoreboard report........!\n");
}
void manageScoreboardMenu()
{
    printf("\t\t 1.	Search player\n");
    printf("\t\t 2.	Add new player\n");
    printf("\t\t 3.	Update player informations\n");
    printf("\t\t 4.	Delete players\n");
    printf("\t\t 5.	Go to main menu\n");
}
void searchPlayer()
{
    char searchPlayerName[20] ="";

    system("COLOR 0A");

    fflush(stdin);
    printf("\tEnter Search Player Name :");
    StringCheckValidation(searchPlayerName);
    fflush(stdin);

    printf("player searching.......!\n");
}
void addNewPlayer()
{
    char newPlayer[20]="";
    system("COLOR 0A");

    fflush(stdin);
    printf("\tEnter New Player Name :");
    StringCheckValidation(newPlayer);
    fflush(stdin);

    printf("adding new player.......!\n");
}
void updatePlayerInformation()
{
    char playerName[20]="";
    char playerCountry[20]="";
    char newPlayerName[20]="";
    char newPlayerCountry[20]="";


    system("COLOR 0A");
    printf("\n\n");
    fflush(stdin);
    printf("\tEnter Update Player Country :");
    StringCheckValidation(playerCountry);
    fflush(stdin);
    printf("\tEnter Update Player Name :");
    fflush(stdin);
    StringCheckValidation(playerName);
    fflush(stdin);
    printf("\tEnter New player Name :");
    fflush(stdin);
    StringCheckValidation(newPlayerName);
    fflush(stdin);
    printf("\tEnter New country Name :");
    fflush(stdin);
    StringCheckValidation(newPlayerCountry);
    fflush(stdin);

    printf("updating player informations.....!\n");

}
void deletePlayer()
{
//    FILE *playerInfo,*countryInfo;
//
    printf("\t\t\tTeam %-20d  \n\n",teamTwoPlayers);
    printf("\t\t\tTeam %-20s  \n\n",playersData.playersArray[0].name);


//
//    playerInfo = fopen("playerInfo.dat","r");
//
//    if(playerInfo == NULL){
//        fprintf(stderr,"Error to open the country info file");
//        exit(1);
//    }
//
//    while (fread(&playerInfoData,sizeof (struct Data),1,playerInfo));
//    fflush(stdin);
//    fclose(playerInfo);
//    fflush(stdin);
//
//    countryInfo = fopen("countryInfo.dat","r");
//    if (countryInfo == NULL) {
//        fprintf(stderr, "\nError to open the country info file\n");
//        exit (1);
//    }
//    while(fread(&countryInfoData, sizeof(struct Data), 1, countryInfo))
//    fflush(stdin);
////    printf("\t\t\tTeam %-20d  \n\n",countryInfoData.countryDetailsArray[0].players);
//    fclose (countryInfo);
//    fflush(stdin);


    bool flag = true;
    bool deleteFlag = false;
    char name[20]="";
    char country[20]="";
    char choice[20]= "";
    char message[20]="";
    char deletePlayerName[20]="";


    system("COLOR 0A");
    printf("\n ***************************************\n");
    printf("\n \t\t\tPlayer Delete Management\n");
    printf("\n ***************************************\n");
    while (flag){

        printf("\n\n");
        printf("\t\t[*] Enter player country that you want to delete :");
        fflush(stdin);
        StringCheckValidation(country);//can be input only string
        fflush(stdin);
        printf("\t\t[*] Enter player name :");
        fflush(stdin);
        StringCheckValidation(name);//can be input only string
        fflush(stdin);

        printf("begining of for loop %s\n",country);
        printf("begining of for loop %s\n",name);
//        for (int row = 0; row < countryInfoData.countryDetailsArray[0].players+countryInfoData.countryDetailsArray[1].players ; row++) {
//
//            printf("begining of for loop %s\n",playerInfoData.playersArray[row].name);
//
//            if( strcmp(country, playerInfoData.playersArray[row].countryName) == 0 && strcmp(name, playerInfoData.playersArray[row].name) == 0){
//                printf("%s\n",playerInfoData.playersArray[row].countryName);
//
//                strcpy(message,"Input values are valid");
//                if(strcmp(country,playerInfoData.playersArray[row].countryName)==0){
//                    if(strcmp(name,playerInfoData.playersArray[row].name)==0){
//
//                        printf("%s\n",playerInfoData.playersArray[row].name);
//
//                        strcpy(deletePlayerName,playerInfoData.playersArray[row].name);
//                        deleteWholeRecord(row,playerInfoData);
//                        deleteFlag=true;//if player delete flag is true
//                    }
//                }
//                flag=false;
//                break;
//            }
//            else{
//                strcpy(message,"Invalid Name or Country");
//            }
//
//        }
//        printf("\n\n\t\t%s\n\n",message);

        if(deleteFlag){
            printf("\n\n\t\t%s Deleted......!\n\n",deletePlayerName);
        }

        printf("Do you want to delete again ? (y/n)");
        fflush(stdin);
        scanf("%s",&choice);
        fflush(stdin);

        if(strcmp(choice,"y")==0 || strcmp(choice,"Y")==0){
            flag=true;
            system("cls");
        } else if(strcmp(choice,"n")==0 || strcmp(choice,"N")==0){
            flag=false;
            system("cls");
            break;
        } else{
            printf("Invalid choice");
        }
    }
//    fclose (playerInfo);
}
//void deleteWholeRecord(int row,struct Data playerInfoData){
//
//    if(row < teamTwoPlayers+teamOnePlayers){
//        for (int j = row; j <teamTwoPlayers+teamOnePlayers ; j++) {
//
//            strcpy(playerInfoData.playersArray[j].countryName,playerInfoData.playersArray[j+1].countryName);
//            strcpy(playerInfoData.playersArray[j].name,playerInfoData.playersArray[j+1].name);
//            strcpy(playerInfoData.playersArray[j].talent,playerInfoData.playersArray[j+1].talent);
//            strcpy(playerInfoData.playersArray[j].battingStatus,playerInfoData.playersArray[j+1].battingStatus);
//            strcpy(playerInfoData.playersArray[j].battingStatus,playerInfoData.playersArray[j+1].battingStatus);
//            playerInfoData.playersArray[j].bat = playerInfoData.playersArray[j+1].bat;
//            playerInfoData.playersArray[j].bowl = playerInfoData.playersArray[j+1].bowl;
//
//        }
//    }
//    if(row == teamTwoPlayers+teamOnePlayers){
//        for (int j = row; j <teamTwoPlayers+teamOnePlayers ; j++) {
//
//            strcpy(playerInfoData.playersArray[j].countryName,NULL);
//            strcpy(playerInfoData.playersArray[j].name,NULL);
//            strcpy(playerInfoData.playersArray[j].talent,NULL);
//            strcpy(playerInfoData.playersArray[j].battingStatus,NULL);
//            strcpy(playerInfoData.playersArray[j].battingStatus,NULL);
//            playerInfoData.playersArray[j].bat = NULL;
//            playerInfoData.playersArray[j].bowl = NULL;
//        }
//    }
//}
