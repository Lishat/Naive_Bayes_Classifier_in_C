#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Max Min functions
#define MIN(a, b) a<b?a:b
#define MAX(a, b) a>b?a:b
//fixed size and dimensions
#define trainsize 6670
#define testsize 3333
#define dimensions 193
//classifier function
void Bayes(int trainingset[][dimensions], int testingset[][dimensions], double Probability[][192][5])
{
    double classCounter[10];
    int error = 0;
    int i, j, k;
    //initializing Class counter
    for(i = 0; i <= 9; i++)
    {
        classCounter[i] = 0.000000;
    }
    //initializing Probability counter
    for(i = 0; i <= 9; i++)
    {
        for(j = 0; j <= 191; j++)
        {
            for(k = 0; k <= 4; k++)
            {
                Probability[i][j][k] = 0.000000;
            }
        }
    }
    //finding out count of value of each feature with respect to class
    for(i = 0; i < trainsize; i++)
    {
        classCounter[trainingset[i][192]] = classCounter[trainingset[i][192]]+1.000000;
        for(j = 0; j < dimensions-1; j++)
        {
            Probability[trainingset[i][192]][j][trainingset[i][j]] = Probability[trainingset[i][192]][j][trainingset[i][j]] + 1.000000;
        }
    }
    //dividing for probability and applying log on it
    for(i = 0; i <= 9; i++)
    {
        for(j = 0; j <= 191; j++)
        {
            for(k = 0; k <= 4; k++)
            {
                Probability[i][j][k] = (double)Probability[i][j][k]/(double)classCounter[i];
                Probability[i][j][k] = log(Probability[i][j][k]);
            }
        }
    }
    //testing
    for(i = 0; i < testsize; i++)
    {
        double solution[10];
        //initializing probability that it belongs to each class
        for(j = 0; j < 10; j++)
        {
            solution[j] = 0.000000;
        }
        //finding out probability for each class based on it's features
        printf("\nSOLUTION SET FOR TEST NO.%d:\n", i+1);
        for(k = 0; k < 10; k++)
        {
            for(j = 0; j < dimensions-1; j++)
            {
                solution[k]  = solution[k] + Probability[k][j][testingset[i][j]];
            }
            printf("%d:%lf\n", k, solution[k]);
        }
        //finding out class having max probability
        int maxindex = 0; 
        double maxcount = solution[0];
        for(k = 0; k < 10; k++)
        {
            if(maxcount <= solution[k])
            {
                maxcount = solution[k];
                maxindex = k;
            }
        }
        //adding to error if class doesn't match
        if(maxindex != testingset[i][192])
        {
            error++;
        }
        printf("GAINED CLASS:%d ACTUAL CLASS:%d\n", maxindex, testingset[i][192]);
    }
    printf("WRONGLY CLASSIFIED: %d CORRECTLY CLASSIFIED: %d\nACCURACY:%lf%%\n", error, testsize-error, (1 - (float)error/testsize)*100);
}

int main()
{
    double Probability[10][192][5];
    int trainingset[trainsize][dimensions];
    FILE *train = fopen("pp_tra.dat", "r");
    int testingset[testsize][dimensions];
    FILE *test = fopen("pp_tes.dat", "r");
    int temp[dimensions],i = 0, j = 0;
    //train file scanning
    while(i < trainsize)
    {
        j = 0;
        while(j < dimensions)
        {
            fscanf(train, "%d", &trainingset[i][j]);
            j++;
        }
        i++;
    }
    fclose(train);
    i = 0;
    //test file scanning
    while(i < testsize)
    {
        j = 0;
        while(j < dimensions)
        {
            fscanf(test, "%d", &testingset[i][j]);
            j++;
        }
        i++;
    }
    fclose(test);
    //Calling classifier function
    Bayes(trainingset, testingset, Probability);
    return 0;
}