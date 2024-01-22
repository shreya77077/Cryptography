#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

int plain=65;
int cipher=90;
typedef struct{
    char key;
    int pos;
}charPos;

void swap(char* a, char* b) 
{ 
    char temp = *a; 
    *a = *b; 
    *b = temp; 
} 

int partition(char* str, int low, int high) 
{ 
    char pivot = str[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) { 
        if (str[j] <= pivot) { 
            i++; 
                  
            swap(&str[i], &str[j]); 
                                    
        } 
    } 
    swap(&str[i + 1], 
         &str[high]);  
    return i + 1; 
}

void quickSort(char* str, int low, int high) 
{ 
    if (low < high) { 
        int pivotIndex = partition(str, low, high);                 
        quickSort(str, low, pivotIndex - 1);
        quickSort(str, pivotIndex + 1, high); 
    } 
} 

int encoder(char* key){
    int keyLength=strlen(key);
    char sortedKey[keyLength];
    strcpy(sortedKey,key);
    int posC[keyLength];
    quickSort(sortedKey,0,keyLength-1);
    charPos Table[keyLength];
    for(int i=0;i<keyLength;i++){
        Table[i].key=sortedKey[i];
        Table[i].pos=i+1;
    }
    for(int i=0;i<keyLength;i++){
        for(int j=0;j<keyLength;j++){
            if(key[i]==Table[j].key){
                posC[i]=Table[j].pos;
            }
        }
    }
    char path1[4096];
    char path2[4096];
    printf("\nEnter the  name for plain text file\n");
    gets(path1);
    FILE *plain=fopen(path1,"r+");
    char str[100][keyLength];
    char dStrM[100][keyLength];
    if(plain==NULL){printf("Plaintext file doesn't exist;");return 0;}
    int i=0,j=0;
    for(char c=fgetc(plain);c!=EOF;c=fgetc(plain)){
        if(!((c>=97&&c<=122)||c==32)){continue;}
        str[i][j]=c;
        if(j==keyLength-1){
            i++;
        }
        j=(j+1)%keyLength;
    }
    printf("%s",str);
    for(int k=0;k<i;k++){
        for(int l=0;l<keyLength;l++){
            dStrM[k][l]=str[k][posC[l]-1];
        }
    }
    fclose(plain);
    char dStr[i*keyLength];
    printf("%s",dStr);
    strcpy(dStr,dStrM);
    printf("\nEnter the  name for cipher text file\n");
    gets(path2);
    FILE *cipher=fopen(path2,"w");
    if(cipher==NULL){printf("Ciphertext file doesn't exist;");return 0;}
    fprintf(cipher,dStr);
    fclose(cipher);
    return 1;
}

int decoder(char* key){
    int keyLength=strlen(key);
    char sortedKey[keyLength];
    strcpy(sortedKey,key);
    int posC[keyLength];
    quickSort(sortedKey,0,keyLength-1);
    charPos Table[keyLength];
    for(int i=0;i<keyLength;i++){
        Table[i].key=sortedKey[i];
        Table[i].pos=i+1;
    }
    for(int i=0;i<keyLength;i++){
        for(int j=0;j<keyLength;j++){
            if(key[i]==Table[j].key){
                posC[i]=Table[j].pos;
            }
        }
        printf("%d",posC[i]);
    }
    char path1[4096];
    char path2[4096];
    printf("\nEnter the  name for cipher text file\n");
    gets(path1);
    FILE *cipher=fopen(path1,"r+");
    char str[100][keyLength];
    char dStrM[100][keyLength];
    if(cipher==NULL){printf("ciphertext file doesn't exist;");return 0;}
    int i=0,j=0;
    for(char c=fgetc(cipher);c!=EOF;c=fgetc(cipher)){
        if(!((c>=97&&c<=122)||c==32)){continue;}
        str[i][j]=c;
        printf("%c",str[i][j]);
        if(j==keyLength-1){
            i++;
        }
        j=(j+1)%keyLength;
    }
    printf("%d %d",i,j);
    printf("\n\n");
    for(int k=0;k<i;k++){
        for(int l=0;l<keyLength;l++){
            dStrM[k][posC[l]-1]=str[k][l];
        }
    }
    fclose(cipher);
    char dStr[i*keyLength];
    strcpy(dStr,dStrM);
    printf("%s",dStr);
    printf("\nEnter the  name for plain text file\n");
    gets(path2);
    FILE *plain=fopen(path2,"w");
    if(plain==NULL){printf("Plaintext file doesn't exist;");return 0;}
    fprintf(plain,dStr);
    fclose(plain);
    return 1;
}

void main(){
    char key[]="HACK";
    encoder(key);
}