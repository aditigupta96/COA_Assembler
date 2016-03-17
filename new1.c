//ADITI (14UCS004)
//ANJALI AGRAWAL (14UCS013)
//YASH AGGARWAL (14UCC043)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct mnemonics{
char instn[7];
char opcode[40];
char type[4];
}*mne;

struct symbol{
char sym[10];
int address;
}*sb;

int sline=0;
int flag;
int symc = 0,countOpcodes=0;


int display(char * filename)
{
  FILE *f;
  char c;
  f = fopen(filename,"r");
  while(!feof(f))
    {
      fscanf(f,"%c",&c);	
      if(feof(f))
	break;
      printf("%c",c);
    }
  
  printf("\n\n----------------------------------------------------------------------------------\n\n");
  return 0;
}
int * decToBin(int n)
{
    int temp;
    int i;
    int *num;
    num=(int*)malloc(10*sizeof(int));
    for(i=0; i<8; i++)
    {
        num[i]=0;
    }
    i=7;
    temp = n;
    while(temp!=0)
    {
        num[i--]= temp % 2;
         temp = temp / 2;
    }
    return num;
}
char * printRegister(char * p)
{
    int i;
    char *re;
    for(i=0;i<countOpcodes;i++)
    {
      if(!strcmp(mne[i].instn,p))
      {
          re = mne[i].opcode;
          break;
      }
    }
    return re;
}

int findSymbol(char * p)
{
    int i;
    int re;
    for(i=0;i<symc;i++)
    {
      if(!strcmp(sb[i].sym,p))
      {
          re = sb[i].address;
          break;
      }
    }
    return re;
}
void main()
{
     char inputfile[30],str[20],ch,str1[10],ch1;
     int line=0,i=0,no_of_label=0,instlen=0,j,start=0,end=0,*num,con=0,sflag=0,dec[10];

     char * s;
     
     mne = (struct mnemonics *)malloc(sizeof(struct mnemonics)*100);
     sb =  (struct symbol *)malloc(sizeof(struct symbol)*20);
     
     FILE *input,*opcode,*symbol,*output,*error;   
     
     symbol = fopen("symbol.txt","w");
     //error = fopen("error.txt","w");
     output = fopen("output.txt","w");
     
     printf("Enter the input file name: ");
     scanf("%s",inputfile);
     input = fopen(inputfile,"r");
     if(input == NULL)
     { 
       fprintf(error,"Error opening file. Please enter correct file name\n");
       exit(0);
     }
     
     opcode = fopen("opcodes.txt","r");
     if(opcode == NULL)
     { printf("fdf\n");
      fprintf(error,"Error opening file. Please enter correct file name\n");
      exit(0);
     }
     
      while(!feof(opcode))
       {       
                fscanf(opcode,"%s",mne[countOpcodes].instn);
               	//printf("%s",mne[countOpcodes].instn);
                fscanf(opcode,"%s",mne[countOpcodes].opcode);
	       	//printf("\t%s\n",mne[countOpcodes].opcode);
                fscanf(opcode,"%s",mne[countOpcodes].type);
            //    printf("\t%s\n",mne[countOpcodes].type);
                countOpcodes++;        
       }
       
    int c=0;
    char inp;
    char opc[100];
    int ilc = 0;
    int * bin;
    /***********************************************************************************************/
printf("Label:\n");

   // char line1 [ 128 ]; /* or other suitable maximum line size */
    while ( fgets ( opc, sizeof opc, input ) != NULL ) /* read a line */
    {
         //printf("%d\n",count );
         //count++;
         //printf("%s\n",opc );
       //  fputs ( line, stdout ); /* write the line */

       int l=0;

       while(opc[l+1]!='\0')
       {
        //  printf("%c",opc[l] );
          if(opc[l]==':')   //Its a label
       {
          // printf("Label");
           int i;
           for(i=0;i<l;i++)
            sb[symc].sym[i] = opc[i];
            sb[symc].sym[i] = '\0';
            sb[symc].address = ilc + 1;
           
           symc++;
           
       }
       l++;
     }
      // printf("%d\n",strlen(opc) );
      // printf("\n");
     /*if(opc[l-1]==':')   //Its a label
       {
          // printf("Label");
           int i;
           for(i=0;i<l;i++)
            sb[symc].sym[i] = opc[i];
            sb[symc].sym[i] = '\0';
            sb[symc].address = ilc + 1;
           
           symc++;
       }*/
               ilc += 1;
    }
      fclose ( input );
//    do
//    {
//       inp=fscanf(input,"%s",opc);
      /* printf("WORD SCANNED IS %s  ",op);*/
            /*check if opcode or label*/
/*       int l=0;
       while(opc[l+1]!='\0')
       {
           l++;
       }
       if(opc[l]==':')   //Its a label
       {
           //printf("Label");
           int i;
           for(i=0;i<l;i++)
                sb[symc].sym[i] = opc[i];
            sb[symc].sym[i] = '\0';
            sb[symc].address = ilc + 1;
           
           symc++;
       }
               ilc += 1;
   }while(inp!=EOF);
   fclose(input); */
   input = fopen(inputfile,"r");
   for(i=0;i<symc;i++)
   {
        printf("%s %d\n",sb[i].sym,sb[i].address);
        //printf("%d\n",sb[i].address);
   }
  
   do
    {
      char ad[50],ad1[50],ad2[50];
      int cons,cons1;
       inp=fscanf(input,"%s",opc);
      /* printf("WORD SCANNED IS %s  ",op);*/
            /*check if opcode or label*/
       int l=0;
       while(opc[l+1]!='\0')
       {
           l++;
       }
       if(opc[l]==':')   //Its a label
       {
          fprintf(output,"\n");// do nothing     
       }

       else{

          for (c = 0; c < countOpcodes; c++)
          {
            char * ty = mne[c].type;
            //printf("%s\n",ty );
            if(!strcmp(opc,mne[c].instn)){
              //printf("%s\n",opc );
              fprintf(output,"%s",mne[c].opcode);

              if(!strcmp("n",ty))
              {
                fprintf(output,"\n");
              }
              if(!strcmp(mne[c].type,"o"))
              {
                char * r;
                inp = fscanf(input,"%s",ad);
              //  printf("%s\n",ad );
                //printf("%s\n",printRegister(ad) );
                r = printRegister(ad);
                fprintf(output,"%s\n",r);
              }
              if(!strcmp(mne[c].type,"oi"))
              {
                inp = fscanf(input,"%s",ad);
                bin = decToBin(findSymbol(ad));
                for(i=0;i<8;i++)
                  fprintf(output, "%d",bin[i]);
                fprintf(output,"\n");
              }
              if(!strcmp(mne[c].type,"ti"))
              {
                inp = fscanf(input,"%s",ad);
                inp = fscanf(input,"%d",&cons);
                fprintf(output,"%s",printRegister(ad));
                bin = decToBin(cons);
                for(i=0;i<8;i++)
                  fprintf(output, "%d",bin[i]);
                fprintf(output,"\n");
              }
              if(!strcmp(mne[c].type,"t"))
              {
                inp = fscanf(input,"%s",ad);
                inp = fscanf(input,"%s",ad1);
                fprintf(output,"%s",printRegister(ad));
                fprintf(output,"%s",printRegister(ad1));
                fprintf(output,"\n");
              }
              if(!strcmp(mne[c].type,"d"))
              {
                inp = fscanf(input,"%s",ad);
                inp = fscanf(input,"%s",ad1);
                inp = fscanf(input,"%d",&cons1);
                fprintf(output,"%s",printRegister(ad));
                fprintf(output,"%s",printRegister(ad1));
                bin = decToBin(cons1);
                for(i=0;i<8;i++)
                  fprintf(output, "%d",bin[i]);
                fprintf(output,"\n");
              }
              if(!strcmp(mne[c].type,"r"))
              {
                inp = fscanf(input,"%s",ad);
                inp = fscanf(input,"%s",ad1);
                inp = fscanf(input,"%s",ad2);
                fprintf(output,"%s",printRegister(ad));
                fprintf(output,"%s",printRegister(ad1));
                fprintf(output,"%s",printRegister(ad2));
                fprintf(output,"\n");
              }
            }
          }
       }
   }while(inp!=EOF);
   int k;
int * de;

for(k=0;k<symc;k++)
{
  fprintf(symbol,"%s ",sb[k].sym);
  de = decToBin(sb[k].address);
    for(i=0;i<8;i++)
                  fprintf(symbol, "%d",de[i]);
  fprintf(symbol,"\n");
}


fclose(symbol);
fclose(output);
int choice;
           while(1){
     printf("\nPlease choose:\n\t1-view output in terminal\n\t2-view symbol output\n\t3-view instuction-opcode table\n\t4-Exit\n");
    scanf("%d",&choice);
      switch(choice)
      {
      case 1:
	printf("\n\n------------------------------output-------------------------------------\n\n");
	display("output.txt");
	break;
      case 2:
	printf("\n\n------------------------------SYMBOL TABLE---------------------------------------\n\n");
	display("symbol.txt");
	break;
      case 3:
	printf("\n\n------------------------------INSTRUCTION-OPCODE---------------------------------------\n\n");
	display("opcodes.txt");
	break;
      case 4:
	exit(0);
      default:
	printf("Wrong choice, please enter a correct choice\n");
      }
  }

}
