#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <string.h>

////////////////////////////////////////////

int input3 = 0;
int mainChoice=0;
int subChoice=0;


void mainMenu();

void readStructureType(int *input,int num,int range);
void readColumnType();

//////////////////////////////////////////
//void readStructureType(int *input, int *input2);
//void readColumnType(int *input2);
int selectInputUnit();
void getTheDimensions(int structType, int columnType, double *length, double *width, double *heightORthickness, double *diameter);
void convertTheDimensionsTometer(int inputUnit, double length, double width, double heightORthickness, double diameter, double *convertedHeight, double *convertedlength, double *convertedWidth, double *convertedDiameter);
void calculateWetAndDryVolume(int structType ,int columnType, double length, double width, double heightORthickness, double diameter, double *wetVolume, double *dryVolume);
int outputUnitforinformationTable();
int selectTheConcreteGrade();
void calculateMaterialVolume(double dryVolume, int concreteGrade, double *cementVolume, double *sandVolume, double *coarseAggregateVolume );
int readTruckType();
void calculateAmountOfWater(double cementVolume, int concreteGrade, double *numberOfCementBags, double *amountOfWater);
void convertVolumesToOutputUnit(int outputUnit, double cementVolume, double sandVolume, double coarseAggregateVolume, double *outputCementVolume,double *outputSandVolume,double *outputCoarseAggergateVolume);
void materialAmountInTrucks(int truckType, double sandVolume, double coarseAggregateVolume, double *numberOfSandTrucks, double *numberOfCoarseAggregateTrucks);

int main()
{
//    int structType = 0;
//    int inputUnit = 0;
//    int columnType = 0;
//    double length = 0.0;
//    double width = 0.0;
//    double heightORthickness = 0.0;
//    double diameter = 0.0;
//    double convertedHeight = 0.0;
//    double convertedlength = 0.0;
//    double convertedWidth = 0.0;
//    double convertedDiameter = 0.0;
//    double wetVolume = 0.0;
//    double dryVolume = 0.0;
//    int outputUnit = 0;
//    int concreteGrade = 0;
//    double cementVolume = 0.0;
//    double sandVolume = 0.0;
//    double coarseAggregateVolume = 0.0;
//    int truckType = 0;
//    int numberOfCementBags = 0;
//    double amountOfWater = 0.0;
//    double outputCementVolume = 0.0;
//    double outputSandVolume = 0.0;
//    double outputCoarseAggergateVolume = 0.0;
//    int numberOfSandTrucks = 0;
//    int numberOfCoarseAggregateTrucks = 0;


      mainMenu();

//    readStructureType(&structType, &columnType);

//    printf("\nStructer Type = %d Column Type = %d", structType, columnType);
//    inputUnit = selectInputUnit();
//    printf("\nInput Unit = %d\n", inputUnit);

//    getTheDimensions(structType,columnType,&length,&width,&heightORthickness,&diameter);
//    convertTheDimensionsTometer(inputUnit,length,heightORthickness,width,diameter,&convertedHeight,&convertedlength,&convertedWidth,&convertedDiameter);
//    calculateWetAndDryVolume(structType,columnType,convertedlength,convertedWidth,convertedHeight,convertedDiameter,&wetVolume,&dryVolume);
//    concreteGrade = selectTheConcreteGrade();
//    calculateMaterialVolume(dryVolume,concreteGrade,&cementVolume,&sandVolume,&coarseAggregateVolume);
//    //printf(" %d %lf %lf %lf",  concreteGrade, cementVolume, sandVolume, coarseAggregateVolume);
//    calculateAmountOfWater(cementVolume, concreteGrade, &numberOfCementBags, &amountOfWater);
//    outputUnit = outputUnitforinformationTable();
//    convertVolumesToOutputUnit(outputUnit, cementVolume, sandVolume, coarseAggregateVolume, &outputCementVolume, &outputSandVolume, &outputCoarseAggergateVolume);
//    truckType = readTruckType();
//    materialAmountInTrucks(truckType, sandVolume, coarseAggregateVolume, &numberOfSandTrucks, &numberOfCoarseAggregateTrucks);





    return 0;
}



void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void mainMenu(){

//    int inputUnit =0;

    printf("Select your structure type from menu below.Use menu numbers to choose \n");
    printf("\t\t 1. Non- structural\n");
    printf("\t\t 2. Slab\n");
    printf("\t\t 3. Beam\n");
    printf("\t\t 4. Column\n");
    printf("\t\t 5. Foundation\n");

    readStructureType(&input3, 0,5);

    if(input3 == 1 || input3 == 2 || input3 == 3 || input3 == 5)
    {
        selectInputUnit();
    } else{
        readColumnType();

    }
}

void readStructureType(int *input,int num,int range)
{

        char choice[64];

         while(*input == 0)
        {
            printf("\nEnter your choice : ");
            fgets(choice, 63, stdin);

            if(strlen(choice) < 2){
                printf("Invalid Input");
                continue;
            }

            if(sscanf(choice, "%d", input) !=  1)
            {
                *input = 0;
                printf("\nInvalid Input");
                continue;
            }
            if(*input < 0 || *input > range) {
                *input = 0;
                printf("\nInvalid Input");
                continue;
            }
        }
         if(num == 0){
             mainChoice = input3;
         }else if(num == 1){
             subChoice = input3;
         }

    input3 = 0;
}


void  readColumnType()
{
    printf("Select your Column type from menu below.Use menu numbers to choose \n");
    printf("\t\t 1. Rectangle type\n");
    printf("\t\t 2. Square type\n");
    printf("\t\t 3. Circular type\n");

    readStructureType(&input3, 1,3);
    selectInputUnit();

    printf("\t\t main choice : %d\n",mainChoice);
    printf("\t\t sub choice : %d\n",subChoice);

}


int selectInputUnit()
{

    int inputUnit = 0;
    printf("\n\nSelect the unit your going to enter values.Use menu numbers to choose\n");

    printf("\n\t\t 1. Meter\n");
    printf("\t\t 2. Foot\n");
    printf("\t\t 3. Inch\n");

    printf("\n\tYour answer :  ");
    scanf("%d", &inputUnit);



    return inputUnit;
}

void getTheDimensions(int structType, int columnType, double *length, double *width, double *heightORthickness, double *diameter)
{

    if(structType == 4 && columnType == 3)
    {
        printf("\nEnter the diameter of the column");
        scanf("%lf", diameter);
        printf("Enter the height of the column");
        scanf("%lf", heightORthickness);

    }
    else
    {
        printf("\nEnter the length of your desired structure Type : ");
        scanf("%lf", length);
        printf("Enter the width of your desired structure Type : ");
        scanf("%lf", width);
        printf("Enter the height or thickness of your desired structure Type : ");
        scanf("%lf", heightORthickness);
    }
   printf("\nLength = %f Width = %f Height = %f", *length, *width, *heightORthickness);

}

void convertTheDimensionsTometer(int inputUnit, double length, double width, double heightORthickness, double diameter, double *convertedHeight, double *convertedlength, double *convertedWidth, double *convertedDiameter)
{

    if(inputUnit == 2)
    {
        *convertedHeight = heightORthickness * 0.305;
        *convertedlength = length * 0.305;
        *convertedWidth = width * 0.305;
        *convertedDiameter = diameter * 0.305;

    }

    else if(inputUnit == 3)
    {
        *convertedHeight = heightORthickness * 0.0254;
        *convertedlength = length * 0.0254;
        *convertedWidth = width * 0.0254;
        *convertedDiameter = diameter * 0.0254;
    }

    else
    {
        *convertedHeight = heightORthickness;
        *convertedlength = length;
        *convertedWidth = width;
        *convertedDiameter = diameter;
    }

    printf("\nconvertedHeight = %lf convertedlength = %lf convertedWidth = %lf\n ", *convertedHeight, *convertedlength, *convertedWidth);
}

void calculateWetAndDryVolume(int structType ,int columnType, double convertedLength, double convertedWidth, double convertedHeightORthickness, double convertedDiameter, double *wetVolume, double *dryVolume)
{

    if(structType == 4 && columnType == 3)
    {
        *wetVolume = (3.14 * convertedDiameter * convertedDiameter)/4;
    }
    else
    {
        *wetVolume = convertedLength * convertedWidth * convertedHeightORthickness;
    }
    *dryVolume = 1.57 *  (*wetVolume);

    printf("\n\nWet concrete Volume = %lf\n", *wetVolume);
    printf("Dry concrete Volume = %lf\n", *dryVolume);

}



int selectTheConcreteGrade()
{
    int concreteGrade;

    printf("\t\t\t\n\nSelect your grade for mix materials\n");

    printf("\t\t 1. G15\n");
    printf("\t\t 2. G20\n");
    printf("\t\t 3. G25\n");

    printf("\n\tYour answer :  ");
    scanf("%d", &concreteGrade);

    return concreteGrade;
}

void calculateMaterialVolume(double dryVolume, int concreteGrade, double *cementVolume, double *sandVolume, double *coarseAggregateVolume)
{

    if(concreteGrade == 1){
        *cementVolume = dryVolume *(0.1);
        *sandVolume = dryVolume * (0.3);
        *coarseAggregateVolume = dryVolume * (0.6);
    }
    else if(concreteGrade == 2){
        *cementVolume = dryVolume * 0.1428;
        *sandVolume = dryVolume * 0.2857;
        *coarseAggregateVolume = dryVolume * 0.5714;
    }
    else{
        *cementVolume = dryVolume * 0.18;
        *sandVolume = dryVolume * 0.27;
        *coarseAggregateVolume = dryVolume * 0.54;

    }

    printf("cementVolume = %lf\nsandVolume = %lf\ncoarseAggregateVolume = %lf", *cementVolume, *sandVolume, *coarseAggregateVolume);

}


void calculateAmountOfWater(double cementVolume, int concreteGrade, double *numberOfCementBags, double *amountOfWater)
{
    double MassOfCement;
    MassOfCement = 1440 * cementVolume;
    *numberOfCementBags =  (MassOfCement/50.0);
    *numberOfCementBags = ceil(*numberOfCementBags);


    if(concreteGrade == 1)
    {
      *amountOfWater  = *numberOfCementBags * 34;
    }
    else if(concreteGrade == 2)
    {
      *amountOfWater  = *numberOfCementBags * 32;
    }
    else
    {
      *amountOfWater  = *numberOfCementBags * 30;
    }

    printf("\n\n\ncement bags = %f \n amount of water = %f", *numberOfCementBags, *amountOfWater);
}


int outputUnitforinformationTable()
{
    int outputUnit;

    printf("\nSelect the output Unit for information Table\n");

    printf("\n\t\t 1. Cubic Meter\n");
    printf("\t\t 2. Cubic Feet\n");

    printf("\n\tYour answer :  ");
    scanf("%d", &outputUnit);

    return outputUnit;
}

int readTruckType()
{
    int truckType = 0;
    printf("\n\t\t 1. 100 cube feet Truck \n");
    printf("\t\t 2. 350 cube feet Truck\n");
    printf("Select your truck type : ");
    scanf("%d", &truckType);

    return truckType;
}


void convertVolumesToOutputUnit(int outputUnit, double cementVolume, double sandVolume, double coarseAggregateVolume, double *outputCementVolume,double *outputSandVolume,double *outputCoarseAggergateVolume)
{

    if(outputUnit==2)
    {
        *outputCementVolume = cementVolume * 35.315;
        *outputSandVolume = sandVolume * 35.315;
        *outputCoarseAggergateVolume = coarseAggregateVolume * 35.315;

    }
    else
    {
        *outputCementVolume = cementVolume ;
        *outputSandVolume = sandVolume ;
        *outputCoarseAggergateVolume = coarseAggregateVolume ;

    }

    printf("\nOutput Cement Volume = %f Output Sand Volume = %f Output Coarse aggregate = %f\n", *outputCementVolume, *outputSandVolume, *outputCoarseAggergateVolume);
}


 void materialAmountInTrucks(int truckType, double sandVolume, double coarseAggregateVolume, double *numberOfSandTrucks, double *numberOfCoarseAggregateTrucks)
 {

     if(truckType == 1)
     {
         *numberOfSandTrucks = sandVolume/ 2.832;
         *numberOfSandTrucks = ceil(*numberOfSandTrucks);

         *numberOfCoarseAggregateTrucks = coarseAggregateVolume/2.832;
         *numberOfCoarseAggregateTrucks = ceil(*numberOfCoarseAggregateTrucks);
     }
     else
     {
         *numberOfSandTrucks = sandVolume/ 9.9109;
         *numberOfSandTrucks = ceil(*numberOfSandTrucks);

         *numberOfCoarseAggregateTrucks = coarseAggregateVolume/9.9109;
         *numberOfCoarseAggregateTrucks = ceil(*numberOfCoarseAggregateTrucks);
     }

     printf("\n%f\n%f", *numberOfCoarseAggregateTrucks, *numberOfSandTrucks);
 }




