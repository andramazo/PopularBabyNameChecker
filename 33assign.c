//Assignment 3 by Anushree Dave
//Calculating the popularity of baby names in 5 year periods from 1921 to 2010
#include<stdio.h>
#include<string.h>
#include<math.h>
struct NameRecord{
    char name[31];
    int year;
    int frequency;
   };
void allCaps(char s[]);
int getRawData(FILE *fp,struct NameRecord records[],int currSize);
void setYearTotals(struct NameRecord records[],int size,int yearRangeTotal[]);
void setNameYearTotals(char theName[],struct NameRecord records[],int size,int nameTotal[]);
void getPerHundredThousand(int nameTotal[],int yearRangeTotal[],double perHundredThousand[]);
void printData(double perHundredThousand[]);
double smallest(double perHundredThousand[]);
void calRange(double perHundredThousand[],double s,int p[]);
void graphperHundredThousand(double perHundredThousand[]);
int main()
  {
    char check,username[31];
    struct NameRecord records[150000];
    int currSize=0;
    int nameTotal[18],yearRangeTotal[18];
    double perHundredThousand[18];
    FILE *fp=NULL,*fp1=NULL;
    printf("\nWelcome to the Name Popularity Checker\n");
    printf("======================================\n");
    fp=fopen("femalebabynames.csv","r");
    fp1=fopen("malebabynames.csv","r");
    if(fp != NULL && fp1 !=NULL)
     { 
    	currSize=getRawData(fp,records,currSize);
    	currSize=getRawData(fp1,records,currSize);
	    do{
	        printf("Please enter a name :");    
	        scanf("%s%*c",username);
	        allCaps(username);
	        setYearTotals(records,currSize,yearRangeTotal);
	        setNameYearTotals(username,records,currSize,nameTotal);
        	getPerHundredThousand(nameTotal,yearRangeTotal,perHundredThousand);
        	printf("Number of Babies named %s per 100,000 births\n",username);
        	printf("%-50s","====================================================\n");
        	printData(perHundredThousand);
        	graphperHundredThousand(perHundredThousand);
        	printf("Do you wish to check another name (Y/N)? ");
        	scanf("%c%*c",&check);
      	      }while(check=='y' || check=='Y');
    	fclose(fp);
    	fclose(fp1);
     }
     else  printf("\nFailed to open file\n\n");
   return 0;
   }
//function capitalizes the name entered by the user
void allCaps(char s[])
   {
    int i;
    for(i=0;i<strlen(s);i++)
        s[i]=toupper(s[i]);
   }
//function reads a file and stores the data in the struct array
int getRawData(FILE *fp,struct NameRecord records[],int currSize)
   {
     int ch,i,j;
     while (fscanf(fp,"%d,%[^,],%d%*c" ,&records[currSize].year, records[currSize].name, &records[currSize].frequency) != EOF)
         {
                 ++currSize;
         } 
     return currSize;
   }
   
//function calculates th total population in a 5 year range
void setYearTotals(struct NameRecord records[],int size,int yearRangeTotal[])
   {
     int i,j,s=1921,e=1925;
     for(j=0;j<18;j++)
       { 
         yearRangeTotal[j]=0; 
         for(i=0;i<size;i++)
            if(records[i].year>=s && records[i].year<=e)
                 yearRangeTotal[j]=yearRangeTotal[j]+records[i].frequency;
         s+=5;
         e+=5;
       }
   }
//function calulates frequency of a given name in 5 year ranges
void setNameYearTotals(char theName[],struct NameRecord records[],int size,int nameTotal[])
   {
     int i,j,s=1921,e=1925;
     for(j=0;j<18;j++)
       {
         nameTotal[j]=0;
         for(i=0;i<size;i++)
           { 
             if(strcmp(theName,records[i].name)==0 && records[i].year>=s && records[i].year<=e)
                    nameTotal[j]=nameTotal[j]+records[i].frequency;
           }
         s+=5;
         e+=5;
       } 
   }
//function calculates frequency of a name per 100,000 childbirths
void getPerHundredThousand(int nameTotal[],int yearRangeTotal[],double perHundredThousand[])
   { 
     int i; 
     for(i=0;i<18;i++)
        perHundredThousand[i]=100000*(double)nameTotal[i]/yearRangeTotal[i];
   }
//function prints  frequency values of a given name in 5 year ranges
void printData(double perHundredThousand[])
   {
     int i,s=1921,e=1925;
     for(i=0;i<18;i++)
       {
          printf("%d - %d: %.2lf\n",s,e,perHundredThousand[i]);     
          s+=5;
          e+=5;
       }

   } 
//function that graphs out the frequency data for a name
void graphperHundredThousand(double perHundredThousand[])
  {

    int i,j,s=2006,e=2010;
    int  pArray[18];
    printf("\n\t\tGraph\n");
    for(i=1;i<=40;i++)
    printf("=");
    printf("\n\n");    
    //finding the smallest number in the array
    double small=smallest(perHundredThousand);
    //calculating range of graph bar and scaling it to fit the screen
    calRange(perHundredThousand,small,pArray);
    //printing the graph
    for(i=17;i>=0;i--)
       {
         printf("%d - %d|",s,e);  
         for(j=1;j<=pArray[i];j++)
              printf("*");
         printf("\n");
         s-=5;
         e-=5;
       }
    printf("\n");
   }
//function finds the  smallest number in array
double smallest(double perHundredThousand[])
   {
      int i;
      double small;
      //fixing the 1st value of small with the 1st non-zero number in the array.
      for(i=0;i<18;i++)
        {
          if(perHundredThousand[i]>=0.01)
           {
            small=perHundredThousand[i];
            break;
           }
        }
      //finding the smallest number
      for(i=0;i<18;i++)
        {
          if(perHundredThousand[i]<small && perHundredThousand[i] >0.01)
              small=perHundredThousand[i]; 
        }
      return small;
   }
//function calculates the range of graphs
void calRange(double perHundredThousand[],double s,int p[])
   {
    int i;
    double large=perHundredThousand[0];
    for(i=1;i<18;i++)
      if(perHundredThousand[i]>large)
          large=perHundredThousand[i];
    //Scaling the graph to 65 units long 
    for(i=0;i<18;i++)
         p[i]=ceil(perHundredThousand[i]/large*65);
   }

