#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
struct mnemonics{
char instn[7];
char opcode[40];
char type[4];
}*mne;

int reg[16];
int countOpcodes = 0;
int instc = 0;
int status,zero=0; 

int bin2dec(char* str) {
 int n = 0;
 int size = strlen(str) - 1;
        int i = 0;
 while ( *str != '\0' ) {
  if ( *str == '1' ) 
      n = n + pow(2, size - i );
  i++; 
  str++;
 }
 return n;
}
/*int decideReg(char * p)
{
	if(!strcmp(p,"00000000"))
		return 0;
	if(!strcmp(p,"00000001"))
		return 1;
	if(!strcmp(p,"00000010"))
		return 2;
	if(!strcmp(p,"00000011"))
		return 3;
	if(!strcmp(p,"00000100"))
		return 4;
	if(!strcmp(p,"00000101"))
		return 5;
	if(!strcmp(p,"00000110"))
		return 6;
	if(!strcmp(p,"00000111"))
		return 7;
	if(!strcmp(p,"00001000"))
		return 8;
	if(!strcmp(p,"00001001"))
		return 9;
	if(!strcmp(p,"00001010"))
		return 10;
	if(!strcmp(p,"00001011"))
		return 11;
	if(!strcmp(p,"00001100"))
		return 12;
	if(!strcmp(p,"00001101"))
		return 13;
	if(!strcmp(p,"00001110"))
		return 14;
	if(!strcmp(p,"00001111"))
		return 15;
}	*/
int Add(int x, int y)
{
    // Iterate till there is no carry  
    while (y != 0)
    {
        // carry now contains common set bits of x and y
        int carry = x & y;  
 
        // Sum of bits of x and y where at least one of the bits is not set
        x = x ^ y; 
 
        // Carry is shifted by one so that adding it to x gives the required sum
        y = carry << 1;
    }
    return x;
}
int subtract(int x, int y)
{
    // Iterate till there is no carry
    while (y != 0)
    {
        // borrow contains common set bits of y and unset
        // bits of x
        int borrow = (~x) & y;
 
        // Subtraction of bits of x and y where at least
        // one of the bits is not set
        x = x ^ y;
 
        // Borrow is shifted by one so that subtracting it from
        // x gives the required sum
        y = borrow << 1;
    }
    return x;
}

int multiply(int x, int y)
{
   /* 0  multiplied with anything gives 0 */
   if(y == 0)
     return 0;
 
   /* Add x one by one */
   if(y > 0 )
     return (x + multiply(x, y-1));
  
  /* the case where y is negative */
   if(y < 0 )
     return -multiply(x, -y);
}
 

int toInt(char * t)
{
	int i,num=0;
	for(i=0;i<8;i++)
	{
		num += pow((int)t[i],i);
	}
	return num;
}
char* compare(char *p, struct mnemonics * m)
{
	int i;
	for(i=0;i<countOpcodes;i++)
	{
		//printf("p -> %s\n",p );
		//printf("mne -> %s\n",m[i].opcode );
		if(!strcmp(p,m[i].opcode))
		{
			return m[i].instn;
		}
	}
	return "\0";
}

char * makestr(char * q, int i,int k)
{
	char * p;
	p = (char *)malloc(25*sizeof(char));
	int j,c=0;
	for(j=i;j<=k;j++)
	{
		//printf("%c", q[i]);
		p[c] = q[j];
		c++;
	}
	//p[c] = '\0';
	//printf("%s\n",p );
	return p;
}
void main()
{
     mne = (struct mnemonics *)malloc(sizeof(struct mnemonics)*100);
     FILE *input,*opcode;
     //char machine[40];
     char * opc,*temp,*machine,*temp1,*temp2,*temp3;
     int t1,t2,t3;
     char code[50][70];
     temp = (char *)malloc(10*sizeof(char));
     temp1 = (char *)malloc(10*sizeof(char));
     temp2 = (char *)malloc(10*sizeof(char));
     temp3 = (char *)malloc(10*sizeof(char));
     input = fopen("output.txt","r");


     opcode = fopen("opcodes.txt","r");
     if(opcode == NULL)
     { //
     	printf("error\n");
      //fprintf(error,"Error opening file. Please enter correct file name\n");
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
       int j = 0;
       while(!feof(input))
       {
       		fscanf(input,"%s",code[j]);
       		j++;
       		instc++;
       }
       j = 0;
       while(j<instc)
       {
       		machine = code[j];
       		opc = compare(machine,mne);
       		if(opc != "\0")
       		{
       			//printf("%s\n",opc);
       			if(!strcmp(opc,"START"))
       				printf("Program Starts\n");
       			else if(!strcmp(opc,"END"))
       				printf("Program Ends\n");
       		}
       		else
       		{
       			temp = makestr(machine,0,7);
       			//printf("%s\n", temp);
       			opc = compare(temp,mne);
       			if(opc != "\0")
       			{	
       				if(!strcmp(opc,"ADD"))
       				{
       					printf("%s\n",opc );
       					temp1 = makestr(machine,8,15);
       					temp2 = makestr(machine,16,23);
       					temp3 = makestr(machine,24,31);
       					
       					t1 = bin2dec(temp1);
       					t2 = bin2dec(temp2);
       					t3 = bin2dec(temp3);

       					reg[t1] = Add(reg[t2],reg[t3]);
       					if(reg[t1]==0)
       					zero=1;
       				}
       				if(!strcmp(opc,"SUB"))
       				{
       					printf("%s\n",opc );
       					temp1 = makestr(machine,8,15);
       					temp2 = makestr(machine,16,23);
       					temp3 = makestr(machine,24,31);

       					t1 = bin2dec(temp1);
       					t2 = bin2dec(temp2);
       					t3 = bin2dec(temp3);

       					reg[t1] = subtract(reg[t2],reg[t3]);
       					if(reg[t1]==0)
       					zero=1;
       				}
       				if(!strcmp(opc,"MUL"))
       				{
       					printf("%s\n",opc );
       					temp1 = makestr(machine,8,15);
       					temp2 = makestr(machine,16,23);
       					temp3 = makestr(machine,24,31);


       					t1 = bin2dec(temp1);
       					t2 = bin2dec(temp2);
       					t3 = bin2dec(temp3);

       					reg[t1] = multiply(reg[t2],reg[t3]);
       					if(reg[t1]==0)
       					zero=1;
       				}
       				if(!strcmp(opc,"DIV"))
       				{
       					printf("%s\n",opc );
       					temp1 = makestr(machine,8,15);
       					temp2 = makestr(machine,16,23);
       					temp3 = makestr(machine,24,31);

       					t1 = bin2dec(temp1);
       					t2 = bin2dec(temp2);
       					t3 = bin2dec(temp3);
       					if(reg[t3] != 0)
       						reg[t1] = reg[t2]/reg[t3];
       					else
       					{
       						printf("Invalid Operation\n");
       						exit(1);
       					}
       					if(reg[t1]==0)
       					zero=1;
       				}
       				if(!strcmp(opc,"SUBI"))
       				{
       					printf("%s\n",opc );
       					temp1 = makestr(machine,8,15);
       					temp2 = makestr(machine,16,23);
       					temp3 = makestr(machine,24,31);
       					t1 = bin2dec(temp1);
       					t2 = bin2dec(temp2);
       					t3 = bin2dec(temp3);
       					reg[t1] = reg[t2] - t3;
       					//printf("%d\n",reg[t1]);
       					if(reg[t1]==0)
       					zero=1;
       				}
       				if(!strcmp(opc,"MODI"))
       				{
       					printf("%s\n",opc );
       					temp1 = makestr(machine,8,15);
       					temp2 = makestr(machine,16,23);
       					temp3 = makestr(machine,24,31);
       					t1 = bin2dec(temp1);
       					t2 = bin2dec(temp2);
       					t3 = bin2dec(temp3);
       					reg[t1] = reg[t2] % t3;
       					//printf("%d\n",reg[t1]);
       					if(reg[t1]==0)
       					zero=1;
       				}
       				if(!strcmp(opc,"ADI"))
       				{
       					printf("%s\n",opc );
       					temp1 = makestr(machine,8,15);
       					temp2 = makestr(machine,16,23);
       					temp3 = makestr(machine,24,31);
       					t1 = bin2dec(temp1);
       					t2 = bin2dec(temp2);
       					t3 = bin2dec(temp3);
       					reg[t1] = reg[t2] + t3;
       					//printf("%d\n",reg[t1]);
       					if(reg[t1]==0)
       					zero=1;
       				}
       				if(!strcmp(opc,"SBI"))
       				{
       					printf("%s\n",opc );
       					temp1 = makestr(machine,8,15);
       					temp2 = makestr(machine,16,23);
       					temp3 = makestr(machine,24,31);
       					t1 = bin2dec(temp1);
       					t2 = bin2dec(temp2);
       					t3 = bin2dec(temp3);
       					reg[t1] = reg[t2] - t3;
       					//printf("%d\n",reg[t1]);
       					if(reg[t1]==0)
       					zero=1;
       				}
       				if(!strcmp(opc,"DVI"))
       				{
       					printf("%s\n",opc );
       					temp1 = makestr(machine,8,15);
       					temp2 = makestr(machine,16,23);
					temp3 = makestr(machine,24,31);
       					t1 = bin2dec(temp1);
       					t2 = bin2dec(temp2);
					t3 = bin2dec(temp3);
       					if(t3 != 0){
       						reg[t1] = reg[t2] / t3;
       						//printf("%df\n",reg[t1]);
       					}
       					else{
       							printf("Invalid Operation\n");
       						exit(1);
       					}
       					if(reg[t1]==0)
       					zero=1;
       					
       				}
       				if(!strcmp(opc,"MLI"))
       				{
       					printf("%s\n",opc );
       					temp1 = makestr(machine,8,15);
       					temp2 = makestr(machine,16,23);
       					temp3 = makestr(machine,24,31);
       					t1 = bin2dec(temp1);
       					t2 = bin2dec(temp2);
       					t3 = bin2dec(temp3);
       					reg[t1] = reg[t2] * t3;
       					if(reg[t1]==0)
       					zero=1;
       				}

       			}
       			else
       			{
       				//printf("Inside this\n" );
       				temp = makestr(machine,0,15);
       				opc = compare(temp,mne);
       				if(opc != "\0")
       				{
       					if(!strcmp(opc,"AND"))
       					{
       						printf("%s\n",opc );
       						temp2 = makestr(machine,16,23);
       						temp3 = makestr(machine,24,31);
       						t1 = bin2dec(temp2);
       						t2 = bin2dec(temp3);
       						reg[t1]=reg[t1] & reg[t2];
       						if(reg[t1]==0)
       						zero=1;
       					}
       					if(!strcmp(opc,"OR"))
       					{
       						printf("%s\n",opc );
       						temp2 = makestr(machine,16,23);
       						temp3 = makestr(machine,24,31);
       						t1 = bin2dec(temp2);
       						t2 = bin2dec(temp3);
       						reg[t1]=reg[t1] | reg[t2];
       						if(reg[t1]==0)
       						zero=1;
       					}
       					if(!strcmp(opc,"XOR"))
       					{
       						printf("%s\n",opc );
       						temp2 = makestr(machine,16,23);
       						temp3 = makestr(machine,24,31);
       						t1 = bin2dec(temp2);
       						t2 = bin2dec(temp3);
       						reg[t1]=reg[t1] ^ reg[t2];
       						if(reg[t1]==0)
       						zero=1;
       					}
       					if(!strcmp(opc,"MOV"))
       					{
       						printf("%s\n",opc );
       						temp2 = makestr(machine,16,23);
       						temp3 = makestr(machine,24,31);
       						t1 = bin2dec(temp2);
       						t2 = bin2dec(temp3);
       						reg[t1]=reg[t2];
       						if(reg[t1]==0)
       						zero=1;
       					}
       					if(!strcmp(opc,"MLI"))
       					{
       						printf("%s\n",opc );
       						temp2 = makestr(machine,16,23);
       						temp3 = makestr(machine,24,31);
       						t1 = bin2dec(temp2);
       						t2 = bin2dec(temp3);
       						reg[t1]=reg[t1]*t2;
       						if(reg[t1]==0)
       						zero=1;
       					}
       					if(!strcmp(opc,"CPI"))
       					{
       						printf("%s\n",opc );
       						temp2 = makestr(machine,16,23);
       						temp3 = makestr(machine,24,31);
       						t1 = bin2dec(temp2);
       						t2 = bin2dec(temp3);
       						if(reg[t1] == t2)
       							status = 0;
       						else if(reg[t1] > t2)
       							status = 1;
       						else	
       							status = -1;
       					}
       					if(!strcmp(opc,"EXCH"))
       					{
       						printf("%s\n",opc );
       						temp2 = makestr(machine,16,23);
       						temp3 = makestr(machine,24,31);
       						t1 = bin2dec(temp2);
       						t2 = bin2dec(temp3);
       						reg[t3]=reg[t1];
       						reg[t1]=reg[t2];
       						reg[t2]=reg[t3];
       					}
       					if(!strcmp(opc,"MVI"))
       					{
       						printf("%s\n",opc );
       						temp2 = makestr(machine,16,23);
       						temp3 = makestr(machine,24,31);
       						t1 = bin2dec(temp2);
       						t2 = bin2dec(temp3);
       						reg[t1] = t2;
       						printf("%d\n",reg[t1] );
       					}
       					if(!strcmp(opc,"CMP"))
       					{
       						printf("%s\n",opc );
       						temp2 = makestr(machine,16,23);
       						temp3 = makestr(machine,24,31);
       						t1 = bin2dec(temp2);
       						t2 = bin2dec(temp3);
       						if(reg[t1] == reg[t2])
						{
       							status = 0;
							zero=1;
						}
       						else if(reg[t1] > reg[t2])
       							status = 1;
		
       						else	
       							status = -1;
						
       					}
       					if(!strcmp(opc,"POW"))
       					{
       						printf("%s\n",opc );
       						temp2 = makestr(machine,16,23);
       						temp3 = makestr(machine,24,31);
       						t1 = bin2dec(temp2);
       						t2 = bin2dec(temp3);
       						reg[t1]=pow(reg[t1],reg[t2]);
       						if(reg[t1]==0)
       						zero=1;
       					}
       					if(!strcmp(opc,"MOD"))
       					{
       						printf("%s\n",opc );
       						temp2 = makestr(machine,16,23);
       						temp3 = makestr(machine,24,31);
       						t1 = bin2dec(temp2);
       						t2 = bin2dec(temp3);
       						reg[t1]=reg[t1]%reg[t2];
       						if(reg[t1]==0)
       						zero=1;
       					}
       					if(!strcmp(opc,"CMPI"))
       					{
       						printf("%s\n",opc );
       						temp2 = makestr(machine,16,23);
       						temp3 = makestr(machine,24,31);
       						t1 = bin2dec(temp2);
       						t2 = bin2dec(temp3);
       						if(reg[t1] == t2)
						{
       							status = 0;
							zero = 1;
						}
       						else if(reg[t1] > t2)
       							status = 1;
       						else	
       							status = -1;
       					}

       				}
       				else
       				{
       					temp = makestr(machine,0,23);
       					opc = compare(temp,mne);
       					if(opc != '\0')
       					{
       						if(!strcmp(opc,"INR"))
       						{	
       							printf("%s\n",opc );
       							temp3 = makestr(machine,24,31);
       							t1 = bin2dec(temp3);
       							reg[t1] += 1;
       						}
       						if(!strcmp(opc,"DCR"))
       						{	
       							printf("%s\n",opc );
       							temp3 = makestr(machine,24,31);
       							t1 = bin2dec(temp3);
       							reg[t1] -= 1;
       						}
       						if(!strcmp(opc,"NOT"))
       						{	
       							printf("%s\n",opc );
       							temp3 = makestr(machine,24,31);
       							t1= bin2dec(temp3);
       							reg[t1] = ~reg[t1];
       						}
       						
       						if(!strcmp(opc,"IN"))
       						{	
       							printf("%s\n",opc );
							printf("Enter number: \n");
       							temp3 = makestr(machine,24,31);
       							t1= bin2dec(temp3);
       							scanf("%d",&reg[t1]);
       						}
       						if(!strcmp(opc,"OUT"))
       						{	
       							printf("%s\n",opc );
       							temp3 = makestr(machine,24,31);
       							t1 = bin2dec(temp3);
       							printf("%d\n",reg[t1] );
       						}
       						if(!strcmp(opc,"JGE"))
       						{	
       							printf("%s\n",opc );
       							temp3 = makestr(machine,24,31);
       							if(status == 0 || status == 1)
       								j = t1-2;
       						}
       						if(!strcmp(opc,"JZ"))
       						{	
       							printf("%s\n",opc );
       							temp3 = makestr(machine,24,31);
       							t1= bin2dec(temp3);
       							if(status == 0)
       								j = t1-2;
       						}
       						if(!strcmp(opc,"JNZ"))
       						{	
       							printf("%s\n",opc );
       							temp3 = makestr(machine,24,31);
       							t1 = bin2dec(temp3);
       							if(status== 1 || status== -1)
       								j = t1-2;
       							
       						}
       						if(!strcmp(opc,"JL"))
       						{	
       							printf("%s\n",opc );
       							temp3 = makestr(machine,24,31);
       							t1 = bin2dec(temp3);
       							//printf("%d\n",status );
       							if(status == -1)
       								j = t1-2;
       						}
       						if(!strcmp(opc,"JUMP"))
       						{	
       							printf("%s\n",opc );
       							temp3 = makestr(machine,24,31);
       							t1 = bin2dec(temp3);
       							j = t1-2;
       						}

       					}
       				}

       			}
       		}
       		//printf("%s\n",machine );
       		j++;
		zero=0;
       }
       fclose(input);
       fclose(opcode);
}
