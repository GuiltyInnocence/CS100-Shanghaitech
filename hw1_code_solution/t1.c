#include <stdio.h>
#include <math.h>
int main()
{
    int numTotalStudents, numSatisfied;
    double satisfiedRatio;
    printf("How many students went to the new dining hall?\n");
    scanf("%d", &numTotalStudents);
    printf("How many of them are satisfied?\n");
    scanf("%d", &numSatisfied);
    satisfiedRatio = (double)numSatisfied / (double)numTotalStudents;
// Prints different messages according to the ratio!
    if(satisfiedRatio - 0.5 < 0.000001 && satisfiedRatio - 0.5 > -0.000001)
    {
        printf("Exactly half of the students are satisfied!\n");
    }
    else if(satisfiedRatio > 0.5)
    {
        printf("More students are satisfied! :)\n");
    }
    else if(satisfiedRatio < 0.5)
    {
        printf("More students are unsatisfied! :(\n");
    }
    else // In case if it divides by zero
    {
        printf("No one went to the dining hall?\n");
    }
    return 0;
}