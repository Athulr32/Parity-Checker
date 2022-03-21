#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *binaryAddition(char *str1, char *str2)
{

    char *add = (char *)malloc(sizeof(char) * (strlen(str1)+2));
    int reminder = 0;
    for (int i = strlen(str1) + 2; i >= 0; i--)
    {

        if (i == strlen(str1) + 1)
        {
            add[i] = '\0';
        }
        else if (i == 0)
        {
            if (reminder == 1)
            {
                add[i] = '1';
            }
            else
            {
                add[i] = '0';
            }
        }
        else
        {
            int temp1 = (char)str1[i] - '0';
            int temp2 = (char)str2[i] - '0';
            if (temp1 + temp2 == 2)
            {
                if (reminder == 0)
                {
                    add[i] = '0';
                    reminder = 1;
                }
                else
                {
                    add[i] = '1';
                    reminder = 1;
                }
            }
            else if (temp1 + temp2 == 1)
            {
                if (reminder == 1)
                {
                    add[i] = '0';
                }
                else
                {
                   
                    add[i] = '0';
                }
            }
            else if (temp1 + temp2 == 0)
            {
                int res = reminder + 0;
                char eng[1];
                sprintf(eng, "%d", res);
                add[i] = eng[0];
                reminder = 0;
            }
        }
    }

    return add;
}

void genError(char *checkSum){

    printf("Created Error...\n");
    checkSum[1]='1';

}

int main()
{

    char data[100];
    int n;
    printf("Enter the Data to send:");
    scanf("%s", data);
    printf("Enter the value n for creating sub segment");
    scanf("%d", &n);

    int divide = strlen(data) / 2;

    char segment[n][divide];

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < divide; j++)
        {
         
            segment[i][j] = data[j];
            // printf("%d %c\n",j,segment[i][j]);
        }
    }
    
    char *check;
    char *add;
    for (int i = 0; i < n - 1; i++)
    {
        if (i == 0)
        {
          
            add = binaryAddition(segment[i], segment[i + 1]);
            check = add;
        }
        else
        {

            check = binaryAddition(segment[i + 1], add);
            
        }
    }

       
    //Generating checksum
    for(int i=0;i<strlen(check);i++){
        if(check[i]=='0'){
            check[i]='1';
        }
        else{
            check[i]='0';
        }
    }

    printf("Checksum is: %s\n",check); //Check sum

    // Receiver
    char *checkReceive;
    char *addReceive;
    for (int i = 0; i < n - 1; i++)
    {
        if (i == 0)
        {
          
            addReceive = binaryAddition(segment[i], segment[i + 1]);
            checkReceive = addReceive;
        }
        else
        {

            checkReceive = binaryAddition(segment[i + 1], add);
            
        }
    }
  
   char *receiverCheck = binaryAddition(checkReceive,check);
    genError(receiverCheck);
    int flag=0;
    for(int i=0;i<strlen(receiverCheck);i++){
        if(receiverCheck[i]=='1'){
            flag=1;
            printf("Error in the code");
            break;
        }
    }

    if(flag==0){
        printf("No error in the code");
    }

}

