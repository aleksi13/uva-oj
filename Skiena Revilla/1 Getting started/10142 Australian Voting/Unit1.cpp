//---------------------------------------------------------------------------
#include <iostream>
#include <string.h>
#include <stdlib.h>

bool eliminated[100];
int ballotsNumber = 0;

bool moreThanHalf(int * array, int arraySize)
{
    for (int i=1; i<=arraySize; i++)
    {
        if (eliminated[i]) continue;
        if ( array[i] > (double) (ballotsNumber / 2) )
        {
            for (int j=1; j<=arraySize; j++)
            {
                if ( array[j] > (double) (ballotsNumber / 2) ) eliminated[j] = false;
                                                          else eliminated[j] = true;
            }
            return true;
        }
    }
    return false;
}

bool tied(int * array, int arraySize)
{
    int position = 1;
    while ( eliminated[ position ] )
    {
        position++;
    }
    int sample = array[position];
    for (int i=1; i<=arraySize; i++)
    {
        if (eliminated[i]) continue;
        if ( array[i]!=sample ) return false;
    }
    return true;
}

int findMinimum(int * array, int arraySize)
{
    int position = 1;
    while ( eliminated[ position ] )
    {
        position++;
    }
    int minimum = array[position];
    for (int i=1; i<=arraySize; i++)
    {
        if (eliminated[i]) continue;
        if (array[i]<minimum) minimum = array[i];
    }
    return minimum;    
}

int main()
{
    using namespace std;
    int testsNumber = 0;
    cin >> testsNumber;

    for (int tests=0; tests<testsNumber; tests++)
    {
        int candidatesNumber = 0;
        cin >> candidatesNumber;
        cin.ignore(1);
        
        char candidatesNames[100][100];
        int i;
        for (i=0; i<candidatesNumber; i++) cin.getline(candidatesNames[i+1], 100);

        int ballots[2000][100];
        char ballot[1000];
        ballotsNumber = 0;
        while ( true )
        {
            if (!cin.getline(ballot, 1000)) break;
            if (strlen(ballot)==0) break;
            ballots[ballotsNumber+1][1] = atoi(strtok(ballot, " "));
            ballots[ballotsNumber+1][0] = ballots[ballotsNumber+1][1];
            for (i=1; i<candidatesNumber; i++) ballots[ballotsNumber+1][i+1] = atoi(strtok(NULL, " "));
            ballotsNumber++;
        }

        int votes[100];
        for (i=0; i<100; i++) votes[i] = 0;
        for (i=1; i<=ballotsNumber; i++) votes[ ballots[i][0] ]++;
        for (i=0; i<100; i++) eliminated[i] = false;

        while ( !(moreThanHalf(votes, candidatesNumber) ||
                          tied(votes, candidatesNumber) ) )
        {
            int minimum = findMinimum(votes, candidatesNumber);

            for (i=1; i<=candidatesNumber; i++)
                if ( votes[i] == minimum ) eliminated[i] = true;

            for (i=1; i<=ballotsNumber; i++)
            {
                if ( eliminated[ ballots[i][0] ] )
                {
                    int position = 2;
                    while ( eliminated[ ballots[i][position] ] )
                    {
                        position++;
                    }
                    votes[ ballots[i][position] ]++;
                    votes[ ballots[i][0] ]--;
                    ballots[i][0] = ballots[i][position];
                }
            }
        }
        
        for (i=1; i<=candidatesNumber; i++) if ( !eliminated[i] ) cout << candidatesNames[i] << endl;
        if ( tests<testsNumber-1 ) cout << endl;
    }
    return 0;
}
//---------------------------------------------------------------------------
 
