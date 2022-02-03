#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *strrev(char *str)
{
      char *p1,*p2;

      if (!str || !*str){
        return str;
      }
            
      for (p1=str,p2=str+strlen(str)-1;p2>p1;++p1,--p2)
      {
            *p1^=*p2;
            *p2^=*p1;
            *p1^=*p2;
      }
      return str;
}



int *convertToAscii(char *word){
  int *ascii = malloc(sizeof(int)*strlen(word));

  for(int i=0;i<strlen(word);i++){
    ascii[i]=(int)word[i];

  }

  return ascii;
}




char **decToBin(int *ascii,int size){

  char **binary = malloc(sizeof(char*)*(size+2));
  char binaryTemp[10];
  char tempBin[20];

  for(int i=0;i<size+2;i++){
    binary[i]=malloc(sizeof(char)*9);
  }

  for(int i=0;i<size;i++){
    
    int temp=ascii[i];
      int rem;
      int j=0;
      while(temp>0)
      {
           rem=temp%2;
        temp=temp/2;
        sprintf(binaryTemp,"%d",rem); //Converting it into a string
          tempBin[j]=*(binaryTemp);  // 
        
        j++;
      }
      
  //Reversing the binary to get the original binary

      strrev(tempBin);
      tempBin[j]='\0';
     strcpy(binary[i],tempBin);
  
  }


  return binary;

}

void parityGenerator(char **binary,int *size){


    // Generating Parity for Row
  for(int i=0;i<*size;i++){
      int one=0;
      char *temp=binary[i];
      for(int i=0;i<strlen(temp);i++){
          if(temp[i]=='1'){
           one++;
          }
      }
    
      if(one%2==0){
          char arr1[]={'0'};
          strcat(binary[i],arr1);
       
      }
      else{
        char arr2[]={'1'};
        strcat(binary[i],arr2);

      }
  }

  //Generating Parity for Column
  char *col = malloc(sizeof(char)*8);
  int one;
  int zero;
    for(int i=0;i<8;i++){
        one=0;
        zero=0;
      for(int j=0;j<*size;j++){

        if(binary[j][i]=='1'){
          one++;
        }
      

      }
      if(one%2==0 || one==0){
        col[i]='0';
       
      }
      else{
        col[i]='1';
  
      }
      
    }
    strcpy(binary[*size],col);
    *size++;
}


void parityChecker(char **binary,int size){

    int check=0;
    printf("\nChecking the Parity....\n");
    printf("\n");
    for(int i=0;i<size;i++){
        int one=0;
      char *temp = binary[i];
      for(int i=0;i<strlen(temp);i++){
        if(temp[i]=='1'){
            one++;
        }
      }

      if(one%2==0){
        printf("%dth bit is correct\n",i+1);
      }
      else{
          check=1;
        printf("%dth bit got some error\n",i+1);
      }
    }

  if(check==1){
    printf("Since some error occured Please re-transmit the message\n");
  }
  else{
    printf("The reciever recieved the exact message\n");
  }
}


void simulatingError(char **binary,int size){
    printf("Simulated Some error in the Parity\n");
   char **error = malloc(sizeof(char*)*size);
  for(int i=0;i<size;i++){
   error[i]=malloc(sizeof(char)*8);
  }

  int count=0;
  for(int i=0;i<size;i++){
    char *temp= binary[i];
      if(temp[3]=='0' && count<3){
        temp[3]='1';
        count++;
      }

    strcpy(error[i],temp);

  } 

    //Checking the parity of this Error data
    parityChecker(error,size);
}




void simulatingError(char **binary,int size);
void parityGenerator(char **binary,int *size);
char **decToBin(int *ascii,int size);
int *convertToAscii(char *word);

int main(){

  char word[100];
  scanf("%[^\t\n]s",word);
  int *ascii,size;
  char **binary;
  size = strlen(word);

  //Converting the entered string into ASCII
  ascii= convertToAscii(word);

  //Converting the ASCII to Binary
  binary=decToBin(ascii,size);

  //Generating the Parity
  parityGenerator(binary,&size);

  
  //Checking Parity
  // parityChecker(binary,size);

  //Creating Some error in the entered data
  simulatingError(binary,size);

}
