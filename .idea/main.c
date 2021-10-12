#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>


struct BattingContent
{
    int score;
    int oneRunsCount;
    int twoRunsCount;
    int threeRunsCount;
    int fourRunsCount;
    int sixRunsCount;
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
    char countryName[40];
    int players;
    int totalScore;
    int totalWickets;
    int totalOvers;
    int totalBalls;
};

struct PlayersIndex{
    int currentPlayerIndex;
    int batsmanIndex;

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
struct PlayersBowlingContent{
    struct PlayerInformations playersArray[100];
};
struct AllScoresAndDetailsOfCountry{
    struct CountryList countryDetailsArray[100];
};
struct savingCurrentBatsmanIndex{
    struct PlayersIndex currentInd[20];
};
struct savingCurrentBowlerIndex{
    struct PlayersIndex currentInd[20];
};

struct Data playersData ;//getting the players data
struct CountryInfo getCountryInfo = {{0}};//getting the country data
struct AllScoresAndDetailsOfCountry getfirstBatCountryInfo;
struct PlayersBattingContent setFirstBattingCountryPlayers,getFirstBattingCountryPlayers;//getting the players batting content
struct PlayersBowlingContent setFirstBowlingCountryPlayers,getFirstBowlingCountryPlayers;//getting the players bowling content
struct savingCurrentBatsmanIndex getPlayerIndexNo;
struct savingCurrentBowlerIndex getBowlerIndexNo;


int number_of_players =0,player=0;

int score=30,six_runs=3,four_runs=4,ball_faced=123;

int wickets =3,runs_of_overs =20,overs=3;
int i=0;
int currentPlayerIndex=0,batsmanArrayIndexNo = 0 ,bowlerArrayIndexNo = 0,currentBowlerIndex=0;
int array_index_count=0;
int teamOnePlayers =0,teamTwoPlayers=0;

//variables of programme running count
int firstTeamProgrammeRunningCount = 0 , secondTeamProgrammeRunningCount = 0;
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
void choosingCountryForWriteToTheFile();

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

    FILE *playersDataFile,*countryDataFile,*fBatCountryAllScores,*fBatPlayersDetails ,*fBallPlayersDetails,*currentPlayerINDEX,*currentBowlerINDEX;

    struct Data getPlayersData;
    struct CountryInfo getCountryData;
    struct PlayersBattingContent getFirstBatCountryPlayers;
    struct PlayersBowlingContent getFirstBowlCountryPlayers;
    struct AllScoresAndDetailsOfCountry  getFirstBattingCountryInfo ;
    struct savingCurrentBatsmanIndex savIndex;
    struct savingCurrentBowlerIndex savBowlIndex;

    currentBowlerINDEX = fopen("currentBowlerINDEX.dat","r");
    if (currentBowlerINDEX == NULL) {
        printf("\nError to open the players bowling content file\n");
    }

    while(fread(&savBowlIndex, sizeof(struct savingCurrentBowlerIndex), 1, currentBowlerINDEX));
    fflush(stdin);

    getBowlerIndexNo.currentInd[0].currentPlayerIndex = savBowlIndex.currentInd[0].currentPlayerIndex;

    currentBowlerIndex = savBowlIndex.currentInd[0].currentPlayerIndex;

    fclose (currentBowlerINDEX);


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

    currentPlayerINDEX = fopen("currentPlayerINDEX.dat","r");
    if (currentPlayerINDEX == NULL) {
        printf("\nError to open the players batting content file\n");
    }

    while(fread(&savIndex, sizeof(struct savingCurrentBatsmanIndex), 1, currentPlayerINDEX));
    fflush(stdin);

    getPlayerIndexNo.currentInd[0].batsmanIndex = savIndex.currentInd[0].batsmanIndex;
    getPlayerIndexNo.currentInd[0].currentPlayerIndex = savIndex.currentInd[0].currentPlayerIndex;

    batsmanArrayIndexNo = savIndex.currentInd[0].currentPlayerIndex;
    currentPlayerIndex = savIndex.currentInd[0].batsmanIndex;

    fclose (currentPlayerINDEX);
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

    countryDataFile= fopen ("countryInfo.dat", "r");
    if (countryDataFile == NULL) {
        fprintf(stderr, "\nError to open the country data file\n");
        exit (1);
    }
    while(fread(&getCountryData, sizeof(struct Data), 1, countryDataFile))

        fflush(stdin);
    getCountryInfo.countryDetailsArray[0].players = getCountryData.countryDetailsArray[0].players;
    getCountryInfo.countryDetailsArray[1].players = getCountryData.countryDetailsArray[1].players;

    strcpy(getCountryInfo.countryDetailsArray[0].countryName,getCountryData.countryDetailsArray[0].countryName);
    strcpy(getCountryInfo.countryDetailsArray[1].countryName,getCountryData.countryDetailsArray[1].countryName);

    fclose(countryDataFile);
    fflush(stdin);

    /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//first bowling country details reading from the file

    fBallPlayersDetails = fopen("fBowlPlayersDetails.dat","r");
    if (fBallPlayersDetails == NULL) {
        printf("\nError to open the players bowling content file\n");
    }
    while(fread(&getFirstBowlCountryPlayers, sizeof(struct Data), 1, fBallPlayersDetails))

        fflush(stdin);

    for (int j = 0; j <= 2; ++j) {

        strcpy(getFirstBowlingCountryPlayers.playersArray[j].countryName,getFirstBowlCountryPlayers.playersArray[j].countryName);
        strcpy(getFirstBowlingCountryPlayers.playersArray[j].name,getFirstBowlCountryPlayers.playersArray[j].name);
        getFirstBowlingCountryPlayers.playersArray[j].bowl.runs_for_over = getFirstBowlCountryPlayers.playersArray[j].bowl.runs_for_over;
        getFirstBowlingCountryPlayers.playersArray[j].bowl.wickets= getFirstBowlCountryPlayers.playersArray[j].bowl.wickets;
        getFirstBowlingCountryPlayers.playersArray[j].bowl.overs = getFirstBowlCountryPlayers.playersArray[j].bowl.overs;
        getFirstBowlingCountryPlayers.playersArray[j].bowl.balls = getFirstBowlCountryPlayers.playersArray[j].bowl.balls;
    }

    fclose(fBallPlayersDetails);
    fflush(stdin);


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

    fBatPlayersDetails = fopen("fBatPlayersDetails.dat","r");
    if (fBatPlayersDetails == NULL) {
        printf("\nError to open the players batting content file\n");
    }
        while(fread(&getFirstBatCountryPlayers, sizeof(struct Data), 1, fBatPlayersDetails))

            fflush(stdin);

        for (int j = 0; j <= 2; ++j) {

            strcpy(getFirstBattingCountryPlayers.playersArray[j].countryName,getFirstBatCountryPlayers.playersArray[j].countryName);
            strcpy(getFirstBattingCountryPlayers.playersArray[j].name,getFirstBatCountryPlayers.playersArray[j].name);
            strcpy(getFirstBattingCountryPlayers.playersArray[j].battingStatus,getFirstBatCountryPlayers.playersArray[j].battingStatus);
            getFirstBattingCountryPlayers.playersArray[j].bat.score = getFirstBatCountryPlayers.playersArray[j].bat.score;
            getFirstBattingCountryPlayers.playersArray[j].bat.oneRunsCount = getFirstBatCountryPlayers.playersArray[j].bat.oneRunsCount;
            getFirstBattingCountryPlayers.playersArray[j].bat.twoRunsCount = getFirstBatCountryPlayers.playersArray[j].bat.twoRunsCount;
            getFirstBattingCountryPlayers.playersArray[j].bat.threeRunsCount = getFirstBatCountryPlayers.playersArray[j].bat.threeRunsCount;
            getFirstBattingCountryPlayers.playersArray[j].bat.fourRunsCount = getFirstBatCountryPlayers.playersArray[j].bat.fourRunsCount;
            getFirstBattingCountryPlayers.playersArray[j].bat.sixRunsCount = getFirstBatCountryPlayers.playersArray[j].bat.sixRunsCount;

        }

        fclose(fBatPlayersDetails);
        fflush(stdin);

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

        fBatCountryAllScores = fopen ("fBatCountryAllScores.dat", "r");
        if (fBatCountryAllScores == NULL) {
            fprintf(stderr, "\nError to open the players batting content file\n");
            exit (1);
        }
        while(fread(&getFirstBattingCountryInfo, sizeof(struct Data), 1, fBatCountryAllScores))

            fflush(stdin);

        for (int j = 0; j <=2; ++j) {
            strcpy(getfirstBatCountryInfo.countryDetailsArray[j].countryName,getFirstBattingCountryInfo.countryDetailsArray[j].countryName);
            getfirstBatCountryInfo.countryDetailsArray[j].players = getFirstBattingCountryInfo.countryDetailsArray[j].players;
            getfirstBatCountryInfo.countryDetailsArray[j].totalScore = getFirstBattingCountryInfo.countryDetailsArray[j].totalScore;
            getfirstBatCountryInfo.countryDetailsArray[j].totalWickets = getFirstBattingCountryInfo.countryDetailsArray[j].totalWickets;
            getfirstBatCountryInfo.countryDetailsArray[j].totalOvers = getFirstBattingCountryInfo.countryDetailsArray[j].totalOvers;
            getfirstBatCountryInfo.countryDetailsArray[j].totalBalls = getFirstBattingCountryInfo.countryDetailsArray[j].totalBalls;
        }

        fclose(fBatCountryAllScores);
        fflush(stdin);
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//    countryDataFile= fopen ("countryInfo.dat", "r");
//    if (countryDataFile == NULL) {
//        fprintf(stderr, "\nError to open the country data file\n");
//        exit (1);
//    }
//    while(fread(&getCountryData, sizeof(struct Data), 1, countryDataFile))
//
//        fflush(stdin);
//        getCountryInfo.countryDetailsArray[0].players = getCountryData.countryDetailsArray[0].players;
//        getCountryInfo.countryDetailsArray[1].players = getCountryData.countryDetailsArray[1].players;
//
//        strcpy(getCountryInfo.countryDetailsArray[0].countryName,getCountryData.countryDetailsArray[0].countryName);
//        strcpy(getCountryInfo.countryDetailsArray[1].countryName,getCountryData.countryDetailsArray[1].countryName);
//
//    fclose(countryDataFile);
//    fflush(stdin);

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

    playersDataFile= fopen ("playerInfo.dat", "r");
    if (playersDataFile == NULL) {
        fprintf(stderr, "\nError to open the player information file\n");
        exit (1);
    }
    while(fread(&getPlayersData, sizeof(struct Data), 1, playersDataFile))
        fflush(stdin);
        for (int j = 0; j <getCountryInfo.countryDetailsArray[0].players+getCountryInfo.countryDetailsArray[1].players ; j++) {
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
//    printf("\ncurrent player index : %d\n",getPlayerIndexNo.currentInd[0].currentPlayerIndex);
//    printf("\ncurrent batsman  index : %d\n",getPlayerIndexNo.currentInd[0].batsmanIndex);
//    printf("\ncurrent bowler index : %d\n", getBowlerIndexNo.currentInd[0].currentPlayerIndex);
//    printf("\ncurrent batsman  index : %d\n",getPlayerIndexNo.currentInd[0].batsmanIndex);

//    printf("\t\t \xFE country name %-20s \t \n",getfirstBatCountryInfo.countryDetailsArray[0].countryName);
//    printf("\t\t \xFE total players %-20d \t \n",getfirstBatCountryInfo.countryDetailsArray[0].players);
//    printf("\t\t \xFE total scores %-20d \t \n",getfirstBatCountryInfo.countryDetailsArray[0].totalScore);
//    printf("\t\t \xFE total wickets %-20d \t \n",getfirstBatCountryInfo.countryDetailsArray[0].totalWickets);
//    printf("\t\t \xFE total overs %-20d \t \n",getfirstBatCountryInfo.countryDetailsArray[0].totalOvers);
//    printf("\t\t \xFE total balls %-20d \t \n",getfirstBatCountryInfo.countryDetailsArray[0].totalBalls);

//    printf("\n\n");
//    for (int j = 0; j <4 ; ++j) {
//        printf("\t\t \xFE country name \t %-20s  \n",getFirstBattingCountryPlayers.playersArray[j].countryName);
//        printf("\t\t \xFE player name \t %-20s  \n",getFirstBattingCountryPlayers.playersArray[j].name);
//        printf("\t\t \xFE batting status \t %-20s  \n",getFirstBattingCountryPlayers.playersArray[j].battingStatus);
//        printf("\t\t \xFE total scores \t %-20d \t\t \n",getFirstBattingCountryPlayers.playersArray[j].bat.score);
//        printf("\t\t \xFE total one \t %-20d \t\t \n",getFirstBattingCountryPlayers.playersArray[j].bat.oneRunsCount);
//        printf("\t\t \xFE total two \t %-20d \t\t \n",getFirstBattingCountryPlayers.playersArray[j].bat.twoRunsCount);
//        printf("\t\t \xFE total three \t %-20d \t\t \n",getFirstBattingCountryPlayers.playersArray[j].bat.threeRunsCount);
//        printf("\t\t \xFE total four \t %-20d \t\t \n",getFirstBattingCountryPlayers.playersArray[j].bat.fourRunsCount);
//        printf("\t\t \xFE total six \t %-20d \t\t \n",getFirstBattingCountryPlayers.playersArray[j].bat.sixRunsCount);
//        printf("\n\n");
//    }
//    printf("\n\n");
//    for (int j = 0; j <4 ; ++j) {
//        printf("\t\t \xFE country name \t %-20s  \n",getFirstBowlingCountryPlayers.playersArray[j].countryName);
//        printf("\t\t \xFE player name \t %-20s  \n",getFirstBowlingCountryPlayers.playersArray[j].name);
//        printf("\t\t \xFE balls \t %-20d \t\t \n",getFirstBowlingCountryPlayers.playersArray[j].bowl.balls);
//        printf("\t\t \xFE runs for over \t %-20d \t\t \n",getFirstBowlingCountryPlayers.playersArray[j].bowl.runs_for_over);
//        printf("\t\t \xFE wickets \t %-20d \t\t \n",getFirstBowlingCountryPlayers.playersArray[j].bowl.wickets);
//        printf("\t\t \xFE overs \t %-20d \t\t \n",getFirstBowlingCountryPlayers.playersArray[j].bowl.overs);
//        printf("\n\n");
//    }

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
//    system("COLOR 04");
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
    if(getCountryInfo.countryDetailsArray[1].players >0){
        getAllPlayers(1);//selecting team two
    }
    printf("\n\n");

}
void getAllPlayers(int country_index)
{
    readData();
    printf("\t\t\tTeam %-20s  \n\n",getCountryInfo.countryDetailsArray[country_index].countryName);
    for(int rows =0;rows<getCountryInfo.countryDetailsArray[0].players+getCountryInfo.countryDetailsArray[1].players;rows++){
        if(strcmp(getCountryInfo.countryDetailsArray[country_index].countryName, playersData.playersArray[rows].countryName)==0){
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
    struct CountryInfo countryInfo;

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
                                countryInfo.countryDetailsArray[0] = countries[0];
                            }else if(countryCount-1 ==1){
                                countryInfo.countryDetailsArray[1] = countries[1];
                            }

                            fwrite (&countryInfo, sizeof(struct Data), 1, cp);
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
    system("COLOR 06");
//    printLivesScoreboard(firstBatsman-1,secondBatsman-1,bowlerOrder[firstBowler-1 ],0,1);
    if(countryCount > 1){
        int battingCountryIndex =0;
        int bowlingCountryIndex =0;

        printf("Enter first batting country (choose 1 or 2)\n\n (01) %s\n (02) %s\n \t",getCountryInfo.countryDetailsArray[0].countryName,getCountryInfo.countryDetailsArray[1].countryName);
        scanf("%d",&firstBattingCountry);
        fflush(stdin);


        if(firstBattingCountry == 1){

            battingCountryIndex = 0;
            bowlingCountryIndex =1;

            if(firstTeamProgrammeRunningCount ==0){

                setBattingOrder(0);//set batting order
                setBowlingOrder(1);//set bowling order

                firstTeamProgrammeRunningCount ++;
            }


            printf("\n");
            system("cls");

            printLivesScoreboard(firstBatsman-1,secondBatsman-1,bowlerOrder[firstBowler-1 ],battingCountryIndex,bowlingCountryIndex);
            playersAndScoresUpdate( firstBatsman-1,secondBatsman-1,bowlerOrder[firstBowler-1 ],battingCountryIndex,bowlingCountryIndex);

        } else if(firstBattingCountry == 2){
            battingCountryIndex = 1;
            bowlingCountryIndex =0;

            if(secondTeamProgrammeRunningCount ==0){

                setBattingOrder(0);//set batting order
                setBowlingOrder(1);//set bowling order

                secondTeamProgrammeRunningCount ++;
            }

            printf("\n");
            system("cls");

            printLivesScoreboard(firstBatsman-1,secondBatsman-1,bowlerOrder[firstBowler-1 ],battingCountryIndex,bowlingCountryIndex);
            playersAndScoresUpdate( firstBatsman-1,secondBatsman-1,bowlerOrder[firstBowler-1 ],battingCountryIndex,bowlingCountryIndex);
        } else{
            printf("Input Invalid");
        }

    }else{
        printf("\t !!!! YOU CAN'T UPDATE MATCH LIVE SCORE-BOARD PLEASE ADD TWO TEAM PLAYERS !!!!\n\n");
    }
}

void printLivesScoreboard(int firstBatsmanIndex,int secondBatsmanIndex,int firstBowlerIndex,int battingCountryIndex,int bowlingCountryIndex) {

    system("cls");
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
                    ,getfirstBatCountryInfo.countryDetailsArray[battingCountryIndex].countryName
                    ,getfirstBatCountryInfo.countryDetailsArray[battingCountryIndex].totalScore,getfirstBatCountryInfo.countryDetailsArray[battingCountryIndex].totalWickets
                    ,getfirstBatCountryInfo.countryDetailsArray[battingCountryIndex].totalOvers,getfirstBatCountryInfo.countryDetailsArray[battingCountryIndex].totalBalls
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
    return getFirstBattingCountryPlayers.playersArray[index].bat.score;

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
    printf("\n\n--------------Batting %s ----------------\n",getCountryInfo.countryDetailsArray[countryIndex].countryName);
    printf("---------------------------------------------\n");
    printf("| NO | player name    |  batsman or bowler | \n");

    for(int rows =0;rows<getCountryInfo.countryDetailsArray[0].players+getCountryInfo.countryDetailsArray[1].players;rows++){
        if(strcmp(getCountryInfo.countryDetailsArray[countryIndex].countryName, playersData.playersArray[rows].countryName)==0){
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
    printf("\n\n--------------Bowling %s ----------------\n",getCountryInfo.countryDetailsArray[countryIndex].countryName);
    printf("---------------------------------------------\n");
    printf("| NO | Bowler name      | \n");

    for(int rows =0;rows<getCountryInfo.countryDetailsArray[0].players+getCountryInfo.countryDetailsArray[1].players;rows++){
         //bowler no list

        if(strcmp(getCountryInfo.countryDetailsArray[countryIndex].countryName, playersData.playersArray[rows].countryName)==0){

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
//    printf("\t\t \xFE total scores %-20s \t \n",playersData.playersArray[batsman_index].name);

    printf("\n\n\t\t832 line current index : %d \n",batsmanArrayIndexNo);

    int player_out_or_not = 0,chooseOption = 0,Stop = 0;
//    bool flag = true;
    bool playerIncludeOrNot = false;

    struct PlayerInformations players[100];
    struct PlayersBattingContent addBattingContent;
    struct savingCurrentBatsmanIndex savIndex;

    printf("\n\n");
    printf("\t\t player out or not out \n\t\t  (01) yes\n\t\t  (02) no .....");
    scanf("%d",&player_out_or_not);

    if(player_out_or_not == 1){
        strcpy(setFirstBattingCountryPlayers.playersArray[batsman_index].battingStatus,"out");

        battingOrderPrint(country_index);                                       //batting order
        printf("Enter new batsman (choose 1,2,3...) \n");
        printf("\n\t new batsman :");
        scanf("%d",&firstBatsman);

        printLivesScoreboard(firstBatsman-1,secondBatsman-1,bowlerOrder[firstBowler-1 ],0,1);

    }else if(player_out_or_not ==2){

        strcpy(setFirstBattingCountryPlayers.playersArray[batsman_index].battingStatus,"notOut"); // batsman status
        strcpy(setFirstBattingCountryPlayers.playersArray[batsman_index].name,playersData.playersArray[batsman_index].name);
        strcpy(setFirstBattingCountryPlayers.playersArray[batsman_index].countryName,playersData.playersArray[batsman_index].countryName);
        while(Stop !=1){

            printf("\n\n");
            printf("\t\t \xFE  Add One Run [Press num 1]\n");
            printf("\t\t \xFE  Add Two Runs [Press num 2]\n");
            printf("\t\t \xFE  Add Three Runs [Press num 3]\n");
            printf("\t\t \xFE  Add Four Runs [Press num 4]\n");
            printf("\t\t \xFE  Add Six Runs [Press num 6]\n");
            printf("\t\t ..... ");

            scanf("%d",&chooseOption);

            switch (chooseOption) {
                case 1:
                    setFirstBattingCountryPlayers.playersArray[batsman_index].bat.oneRunsCount +=1;
                    setFirstBattingCountryPlayers.playersArray[batsman_index].bat.score += 1;
                    break;
                case 2:
                    setFirstBattingCountryPlayers.playersArray[batsman_index].bat.twoRunsCount +=1;
                    setFirstBattingCountryPlayers.playersArray[batsman_index].bat.score += 2;
                    break;
                case 3:
                    setFirstBattingCountryPlayers.playersArray[batsman_index].bat.threeRunsCount +=1;
                    setFirstBattingCountryPlayers.playersArray[batsman_index].bat.score += 3;
                    break;
                case 4:
                    setFirstBattingCountryPlayers.playersArray[batsman_index].bat.fourRunsCount +=1;
                    setFirstBattingCountryPlayers.playersArray[batsman_index].bat.score += 4;
                    break;
                case 6:
                    setFirstBattingCountryPlayers.playersArray[batsman_index].bat.sixRunsCount +=1;
                    setFirstBattingCountryPlayers.playersArray[batsman_index].bat.score += 6;
                    break;
                default:
                    printf("your input isn't valid");
                    break;

            }
//

            printf("\t\t \xFE total scores %-20d \t \n",setFirstBattingCountryPlayers.playersArray[0].bat.score);



            printf("\n\t\t Do you want to go back?\n\t\t (01) yes\n\t\t (02) no ....");
            scanf("%d",&Stop);
            fflush(stdin);
        }

        FILE *fBatPlayersDetails,*sBatPlayersDetails ,*currentPlayerINDEX;

        switch (country_index) {
            case 0:
                fBatPlayersDetails = fopen("fBatPlayersDetails.dat","w");
                if (fBatPlayersDetails == NULL) {
                    printf("\nError to open the players batting content file\n");

                }

                printf("\n\n\t\t 927 current index : %d = %d  \n",currentPlayerIndex,batsman_index);

                if(batsmanArrayIndexNo == 0){

                        addBattingContent.playersArray[batsmanArrayIndexNo] = setFirstBattingCountryPlayers.playersArray[batsman_index];
                        batsmanArrayIndexNo++;
                }else if (batsmanArrayIndexNo > 0){

                    //player check in the file
                    for (int k = 0; k < batsmanArrayIndexNo ; k++) {
                        if(strcmp(getFirstBattingCountryPlayers.playersArray[k].name,playerSelect(batsman_index)) == 0){

                            playerIncludeOrNot = true;

                            printf("player in the file");

                        }
                    }


                    if(playerIncludeOrNot){


                            for (int k = 0; k < batsmanArrayIndexNo ; k++) {

                                if(strcmp(getFirstBattingCountryPlayers.playersArray[k].name,playerSelect(batsman_index)) == 0){

                                    addBattingContent.playersArray[k] = setFirstBattingCountryPlayers.playersArray[batsman_index];

                                } else{
                                    addBattingContent.playersArray[k] = getFirstBattingCountryPlayers.playersArray[k];
                                }

                            }

                    } else{

                            for (int j = 0; j < batsmanArrayIndexNo ; j++) {

                                addBattingContent.playersArray[j] = getFirstBattingCountryPlayers.playersArray[j];

                            }
                                addBattingContent.playersArray[batsmanArrayIndexNo] = setFirstBattingCountryPlayers.playersArray[batsman_index];
                        batsmanArrayIndexNo++;

                    }

                }


                printf("\n\n\t\t 931 current index : %d \n",batsmanArrayIndexNo);


                fwrite (&addBattingContent, sizeof(struct Data), 1, fBatPlayersDetails);
                fflush(fBatPlayersDetails);
                printf("\n\n\t\tContents to file written successfully !\n");
                fclose (fBatPlayersDetails);

                currentPlayerINDEX = fopen("currentPlayerINDEX.dat","w");
                if (currentPlayerINDEX == NULL) {
                    printf("\nError to open the players batting content file\n");
                }

                savIndex.currentInd[0].batsmanIndex = batsman_index;
                savIndex.currentInd[0].currentPlayerIndex = batsmanArrayIndexNo;

                fwrite (&savIndex, sizeof(struct savingCurrentBatsmanIndex), 1, currentPlayerINDEX);
                fflush(currentPlayerINDEX);
                printf("\n\n\t\tcurrent player index written successfully !\n");
                fclose (currentPlayerINDEX);

                break;
            case 1:

                sBatPlayersDetails = fopen("sBatPlayersDetails.dat","w");
                if (sBatPlayersDetails == NULL) {
                    printf("\nError to open the players batting content file\n");
                }

                addBattingContent.playersArray[batsman_index] = playersData.playersArray[batsman_index];

                fwrite (&addBattingContent, sizeof(struct AllScoresAndDetailsOfCountry), 1, sBatPlayersDetails);
                fflush(sBatPlayersDetails);
                printf("\n\n\t\tContents to file written successfully !\n");
                fclose (sBatPlayersDetails);
                break;
        }



    }else{
        printf("your input isn't valid");
    }

}
//void choosingCountryForWriteToTheFile(){
//
//        FILE *battingCountryAllScores;
//        struct AllScoresAndDetailsOfCountry batCountry;
//
//
//
//        battingCountryAllScores = fopen("BattingCountryAllScores.dat","w");
//        if (battingCountryAllScores == NULL) {
//            printf("\nError to  open the players batting content file\n");
//            exit (1);
//        }
//
//        sleep(5);
//
//        for (int j = 0; j <= 2; ++j) {
//            batCountry.countryDetailsArray[j].players = setCountryData.countryDetailsArray[j].players;
//            strcpy(batCountry.countryDetailsArray[j].countryName,setCountryData.countryDetailsArray[j].countryName);
//            batCountry.countryDetailsArray[j].totalScore = setCountryData.countryDetailsArray[j].totalScore;
//            batCountry.countryDetailsArray[j].totalWickets = setCountryData.countryDetailsArray[j].totalWickets;
//            batCountry.countryDetailsArray[j].totalOvers = setCountryData.countryDetailsArray[j].totalOvers;
//            batCountry.countryDetailsArray[j].totalBalls = setCountryData.countryDetailsArray[j].totalBalls;
//        }
//
//
//        fwrite (&batCountry, sizeof(struct Data), 1, battingCountryAllScores);
//        fflush(battingCountryAllScores);
//        printf("\n\n\t\tContents to file written successfully !\n");
//        fclose (battingCountryAllScores);
//
//
//
//}

// selecting the next bowler or current bowler
void selectBowler(int bowler_index,int country_index)
{
    int flag = 0 ,choice = 0;
    int player_update_or_not=0;
    bool bowlerInArrayOrNot;


    struct PlayersBowlingContent addBowlingContent;
    struct savingCurrentBowlerIndex savIndex ;

    printf("\t\t Add new bowler or update current bowler \n\t\t  (01) yes\n\t\t  (02) no"); //not out
    scanf("%d",&player_update_or_not);

    if(player_update_or_not == 1){

        bowlingOrderPrint(country_index);                                       //batting order
        printf("\t\t Enter new bowler (choose 1,2,3...) \n");
        printf("\n\t new bowler :");
        scanf("%d",&bowler_index);

    }else if(player_update_or_not ==2){

        strcpy(setFirstBowlingCountryPlayers.playersArray[bowler_index].name,playersData.playersArray[bowler_index].name);
        strcpy(setFirstBowlingCountryPlayers.playersArray[bowler_index].countryName,playersData.playersArray[bowler_index].countryName);

        while(flag != 1){

            printf("\n\n");
            printf("\t\t \xFE  Add bowler wickets [Press num 1]\n");
            printf("\t\t \xFE  Add bowler overs [Press num 2]\n");
            printf("\t\t \xFE  Add bowler balls [Press num 3]\n");
            printf("\t\t \xFE  Add per runs for over [Press num 4]\n");
            printf("\t\t ..... ");
//            printf("\n");

            scanf("%d",&choice);

            switch (choice) {
                case 1:
                    printf("\t\t Update bowler wickets :");
                    scanf("%d",&setFirstBowlingCountryPlayers.playersArray[bowler_index].bowl.wickets);
                    break;
                case 2:
                    printf("\t\t Update bowler overs :");
                    scanf("%d",&setFirstBowlingCountryPlayers.playersArray[bowler_index].bowl.overs);
                    break;
                case 3:
                    printf("\t\t Update bowler balls :");
                    scanf("%d",&setFirstBowlingCountryPlayers.playersArray[bowler_index].bowl.balls);
                    break;

                case 4:
                    printf("\t\t Update per runs for over :");
                    scanf("%d",&setFirstBowlingCountryPlayers.playersArray[bowler_index].bowl.runs_for_over);
                    break;

            }


            printf("\n\t\t Do you want to go back?\n\t\t (01) yes\n\t\t (02) no ....");
            scanf("%d",&flag);
            fflush(stdin);


        }
        printf("\t\t country index :%d\n",country_index);


        FILE *fBowlPlayersDetails,*sBowlPlayersDetails,*currentBowlerINDEX ;

        switch (country_index) {
            case 1:
                fBowlPlayersDetails = fopen("fBowlPlayersDetails.dat", "w");

                if (fBowlPlayersDetails == NULL) {
                    printf("\nError to open the players bowling content file\n");

                }

                if (bowlerArrayIndexNo == 0) {

                    addBowlingContent.playersArray[bowlerArrayIndexNo] = setFirstBowlingCountryPlayers.playersArray[bowler_index];
                    bowlerArrayIndexNo++;
                } else if (bowlerArrayIndexNo > 0) {

                    //player check in the file
                    for (int k = 0; k < bowlerArrayIndexNo; k++) {
                        if (strcmp(getFirstBowlingCountryPlayers.playersArray[k].name, playerSelect(bowler_index)) ==0) {

                            bowlerInArrayOrNot = true;

                            printf("player in the file");
                        }
                    }

                    if (bowlerInArrayOrNot) {

                        for (int k = 0; k < bowlerArrayIndexNo; k++) {

                            if (strcmp(getFirstBattingCountryPlayers.playersArray[k].name,
                                       playerSelect(bowler_index)) == 0) {

                                addBowlingContent.playersArray[k] = setFirstBowlingCountryPlayers.playersArray[bowler_index];

                            } else {
                                addBowlingContent.playersArray[k] = getFirstBowlingCountryPlayers.playersArray[k];
                            }
                        }

                    }else {

                        for (int j = 0; j < bowlerArrayIndexNo; j++) {

                            addBowlingContent.playersArray[j] = getFirstBowlingCountryPlayers.playersArray[j];

                        }
                        addBowlingContent.playersArray[bowlerArrayIndexNo] = setFirstBowlingCountryPlayers.playersArray[bowler_index];
                        bowlerArrayIndexNo++;
                    }
                }


                printf("\n\n\t\t 931 current index : %d \n", bowlerArrayIndexNo);


                fwrite(&addBowlingContent, sizeof(struct Data), 1, fBowlPlayersDetails);
                fflush(fBowlPlayersDetails);
                printf("\n\n\t\tContents to file written successfully !\n");
                fclose(fBowlPlayersDetails);

                currentBowlerINDEX = fopen("currentBowlerINDEX.dat", "w");
                if (currentBowlerINDEX == NULL) {
                    printf("\nError to open the players batting content file\n");
                }

                savIndex.currentInd[0].currentPlayerIndex = bowlerArrayIndexNo;

                fwrite(&savIndex, sizeof(struct savingCurrentBowlerIndex), 1, currentBowlerINDEX);
                fflush(currentBowlerINDEX);
                printf("\n\n\t\tcurrent player index written successfully !\n");
                fclose(currentBowlerINDEX);

                break;
            case 0:
                break;

        }

    }else{
        printf("your input isn't valid");
    }
}
//update function of live scoreboard manage
void playersAndScoresUpdate(int firstBatsmanIndex,int secondBatsmanIndex,int firstBowlerIndex,int battingCountryIndex,int bowlingCountryIndex)
{
    struct CountryList country[100];
    struct AllScoresAndDetailsOfCountry countryInfo;

    int update_palyer_choice=0;
    int select_player=0;
    int exit = 0;
    bool flag =true;

    printf("\n\t\t Do you want to update live score board \n \t\t\t\t (01) yes\n \t\t\t\t (02) no .....");
    scanf("%d",&update_palyer_choice);




    switch (update_palyer_choice) {
        case 1:

            while(flag)
            {
                printf("fBatsman index from update fun :%d == %d",firstBatsmanIndex,firstBatsman-1);
                printf("\n");
                printf("\t\t Choose Your Option For Update (1 ,2,3,4,5,6 or 7)\n\n");

//                printf("\t\t\t (01) %s\n",playerSelect(firstBatsmanIndex));
//                printf("\t\t\t (02) %s\n",playerSelect(secondBatsmanIndex));
//                printf("\t\t\t (03) %s\n",playerSelect(firstBowlerIndex));

                printf("\t\t\t (01) %s\n",playerSelect(firstBatsman-1));
                printf("\t\t\t (02) %s\n",playerSelect(secondBatsman-1));
                printf("\t\t\t (03) %s\n",playerSelect(bowlerOrder[firstBowler-1 ]));
                printf("\t\t\t (04) Total score\n");
                printf("\t\t\t (05) Total wickets\n");
                printf("\t\t\t (06) Total overs\n");
                printf("\t\t\t (07) Total balls .....");
                scanf("%d",&select_player);

                printf("\n");
                switch (select_player) {
                    case 1:
                        selectBatsman(firstBatsmanIndex,battingCountryIndex);
                        break;
                    case 2:
                        selectBatsman(secondBatsmanIndex,battingCountryIndex);
                        break;
                    case 3:
                        selectBowler(firstBowlerIndex,bowlingCountryIndex);
                        break;
                    case 4:
                        printf("\t\t\t Update total score : ");
                        scanf("%d",&country[battingCountryIndex].totalScore);
                        break;
                    case 5:
                        printf("\t\t\t Update total wickets  :");
                        scanf("%d",&country[battingCountryIndex].totalWickets);
                        break;
                    case 6:
                        printf("\t\t\t Update total overs : ");
                        scanf("%d",&country[battingCountryIndex].totalOvers);
                        break;
                    case 7:
                        printf("\t\t\t Update total balls : ");
                        scanf("%d",&country[battingCountryIndex].totalBalls);
                        break;
                    default: printf("\t\t\t your input isn't valid");
                        break;
                }

//                choosingCountryForWriteToTheFile( battingCountryIndex );// all scores and wickets write in the file

                printf("\n\t\t\tDo you want to exit?\n\t\t\t (01) yes\n\t\t\t (02) no .... ");
                scanf("%d",&exit);

                if(exit==1){
                    flag=false;
                    break;
                }

            }
                country[battingCountryIndex].players = getCountryInfo.countryDetailsArray[battingCountryIndex].players;
                strcpy(country[battingCountryIndex].countryName,getCountryInfo.countryDetailsArray[battingCountryIndex].countryName);

                FILE *fBatCountryAllScores,*sBatCountryAllScores;

                switch (battingCountryIndex) {
                    case 0:
                        fBatCountryAllScores = fopen("fBatCountryAllScores.dat","w");
                        if (fBatCountryAllScores == NULL) {
                            printf("\nError to open the players batting content file\n");
                        }

                        countryInfo.countryDetailsArray[battingCountryIndex] = country[battingCountryIndex];

                        fwrite (&countryInfo, sizeof(struct AllScoresAndDetailsOfCountry), 1, fBatCountryAllScores);
                        fflush(fBatCountryAllScores);
                        printf("\n\n\t\tContents to file written successfully !\n");
                        fclose (fBatCountryAllScores);
                        break;
                    case 1:

                        sBatCountryAllScores = fopen("sBatCountryAllScores.dat","w");
                        if (sBatCountryAllScores == NULL) {
                            printf("\nError to open the players batting content file\n");
                        }

                        countryInfo.countryDetailsArray[battingCountryIndex] = country[battingCountryIndex];

                        fwrite (&countryInfo, sizeof(struct AllScoresAndDetailsOfCountry), 1, sBatCountryAllScores);
                        fflush(sBatCountryAllScores);
                        printf("\n\n\t\tContents to file written successfully !\n");
                        fclose (sBatCountryAllScores);
                        break;
                }

            break;
        case 2:
            system("cls");
            break;
        default:
            printf("your input isn't valid");
            break;
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
