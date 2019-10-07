#include <stdio.h>
#include <stdlib.h>
/* function declaration */
long long unsigned factorial(int n, int start);
int calculation(int n, int k);
int fibonacci (int n);
float notValidValues (float n, float d);

int main()
{
    int indexCounter, checkInput;
    float rowNumber, fibonacciIndex;
    //indexCounter is simply used to go through all the numbers in a specific pascal row
    //rowNumber and fibonacciIndex are going to be input by the user to specify which
    //row in the pascal triangle they want to output and which number in the Fibonacci sequence
    //they want respectively. They are floats as this way the user can input a decimal and the
    // program will be able to process it, in which case the program tests if the number input is
    // a float to return an error message if it is. If they are initialized as integers the program
    // will not be able to process the decimal point to return the error message.
    printf("input the row that you would like to output its values (start counting from 0): ");
    checkInput = scanf("%f", &rowNumber);       // scanf() is stored in a variable so it can be used to check if the values input
    if(notValidValues(checkInput, rowNumber))   // are numbers only. Once scanf("%f", &rowNumber) is called rowNumber will store the
    {                                           // number the user input as a float, so it id used as the second parameter.
        return 0;                               // if(notValidValues returns anything other than zero) then we know the values are not
    }                                           // suitable so return 0 to stop running main().
    printf("The row in Pascals triangle is: \n");
    for(indexCounter=0; indexCounter <= rowNumber; ++indexCounter) // to print the whole row calculation() is used until we reach the last index, so when
    {                                                              // when the index is the same as the rowNumber we know we hit the last index and we should stop
        printf("  %d  ", calculation(rowNumber, indexCounter));    // rowNumber is a float, but when it;s called by calculation it is changed into an int so
    }                                                              // we dont need to cast it.
    printf("\ninput the index number of the Fibonacci number you want (start counting from 0): ");
    checkInput = scanf("%f", &fibonacciIndex);
    if(notValidValues(checkInput, fibonacciIndex))// same check is used for the fibonacciIndex, as explained above.
    {
        return 0;
    }
    printf("%d \n", fibonacci(fibonacciIndex));
    return 0;
}


/*
*   Calculation takes 2 numbers and does the mathematical equivalent of aCb
*   e.g calculation(4, 4) returns 4C4 which is 1
*   it's useful to as it can return a specific number from the pascal triangle
*   given its index (k) and row (n)
*/
int calculation(int n, int k)
{
    if (n-k >= k)                                   // n!/(k!)(n-k)! is the equation used to solve nCk, where n>=k.
    {                                               // This means we can always cancel n! with something from the denominator
        return factorial(n, n-k+1)/factorial(k, 1); // if (n-k)>=k then we will completely cancel (n-k)! from n!. We will be left
    }                                               // with (n-k+1)*(n-k+2)*...n in the numerator. The denominator will be left with
    return factorial(n, k+1)/factorial((n-k), 1);   // k! as normal. The same idea applies if k>(n-k).
}

/*
 *  factorial() is used for calculation to simply do the factorial of any number
 *  e.g factorial(5, 1) will return 5!
 *  the second parameter is used so that if the method is used to multiply numbers
 *  less that "number" but starting from a given point rather than starting from 1.
 */
long long unsigned factorial(int number, int start)
{
    int i;
    long long unsigned answer = 1;
    for(i=start; i<=number; ++i)     //if n > zero then multiply all the numbers smaller than it starting from the given startt point
    {                                //until the number itself (inclusive) to get the factorial.
        answer *= i;                 //if its n=0 then it will skip the for loop and directly return answer which is 1.
    }
    return answer;

}

/*  Fibonacci() takes a number and that number is used as the index for the Fibonacci
*   sequence (starting from index = 0). That index is used to find the number it points
*   to in the sequence
*/
int fibonacci (int n)
{
    int k, answer = 0;                  //since the Fibonacci index number is the same as the number of elements
    for(k=0; n-k>=0 ; ++k)              //in the corresponding pascal row, we will call the calculation() function
    {                                   //for k (index in pascal row) and for n-k is the same as simply --n as we are
        answer+=calculation(n-k, k);    //decrementing n each time until n=k in which case if we increment k and
    }                                   //decrement n again we will go out of the pascal triangle.
    return answer;                      //each time calculation() is called it is added to answer.
}


/*  checkValues() is used in main to test that the user input something this code can work with
*   first the number input should not contain letters or signs, next the number should be positive
*   and finally the number cannot be greater than 12 (as then the factorial will out range even unsigned long!)
*/
float notValidValues (float n, float d)
{
    if ((int)n!=1)                          //the first parameter is the scanf() statement, scanf() returns
    {                                       // 1 if it can properly store the value i.e. it is a number
        printf("\nTHATS NOT A NUMBER!\n\n");// so if scanf() doesn't return 1 then the user input contains
        return 1;                           // letters or symbols that will cause an error.
    }
    else if (d<0)                           // if the scanf() function does work then it will store the input
    {                                       // in d. so now we can test that d is positive and that d is less
        printf("\nNO NEGATIVES!\n\n");      // than 35 and return the appropriate message to the user.
        return 1;                           // if any of these conditions are not correct return 1 to stop the
    }                                       // program. otherwise return 0 and continue the program normally
    else if (d>35)                          // as we can work with the input provided.
    {
        printf("\nSorry, any number larger than 35 will not work\n\n");
        return 1;
    }
    else if (d - (int)d != 0)               // if the float number is not same as it's int value i.e it doesn't after its
    {                                       // decimal point then we cannot work with this number so return an error message
        printf("\nNO DECIMALS JUST NATURAL NUMBERS PLZ\n\n");
        return 1;
    }
    return 0;
}
