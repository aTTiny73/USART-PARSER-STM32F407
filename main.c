#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include <string.h>

// commandParameters structure used to store all the command parameters
struct commandParameters
{
	char param1[5]; //pbtn,led,help
	char param2[5]; // s(set), b(blink), p(pwm)
	char param3[5]; // N(led num)
	char param4[128]; // S(0,1), O(ms), D(0-100)
	char param5[128]; // P(ms)
};

void parseCommand(char*,struct commandParameters*);

int main(void)
{
    initUSART2(USART2_BAUDRATE_115200);
	enIrqUSART2();
    initSYSTIM();

    struct commandParameters commandParams={0};

    while(1){

        if(dataReady == '1'){
			parseCommand(g_usart2_buffer,&commandParams);
			printUSART2("\n");
	  		dataReady = '0';
            printUSART2(" Param1: %s \n",commandParams.param1);
            printUSART2(" Param2: %s \n",commandParams.param2);
            printUSART2(" Param3: %s \n",commandParams.param3);
            printUSART2(" Param4: %s \n",commandParams.param4);
            printUSART2(" Param5: %s \n",commandParams.param5);
        }else{
            
            //Main code
            delay_ms(50);
        }
    }


}

void parseCommand(char* buffer,struct commandParameters* commandParams){
	char *slice = strtok(buffer, " ");
	int i = 0;
	while(slice != NULL){

        ++i;
		if(i==6){
			break;
		}
		
		if (i==1){
		  	strcpy(commandParams->param1,slice);
			commandParams->param1[4]='\0';
			if(strcmp(commandParams->param1,"pbtn")!=0 && strcmp(commandParams->param1,"led")!=0 && strcmp(commandParams->param1,"help")!=0 && strcmp(commandParams->param1,"map1")!=0 && strcmp(commandParams->param1,"mapb")!=0){
				printUSART2("Invalid command\n");
				break;
			}
		}else if(i==2){
			if(strcmp(slice,"s")!=0 && strcmp(slice,"b")!=0 && strcmp(slice,"p")!=0){
				if(strcmp(commandParams->param1,"led")==0){
					printUSART2("Invalid command\n");
					break;
				}
			}
		  	strcpy(commandParams->param2,slice);
			commandParams->param2[4]='\0';
		}else if(i==3){
			if(strcmp(slice,"0")!=0 && strcmp(slice,"1")!=0 && strcmp(slice,"2")!=0 && strcmp(slice,"3")!=0){
				printUSART2("Invalid led number\n");
				break;
			}
		  	strcpy(commandParams->param3,slice);
			commandParams->param3[4]='\0';
		}else if(i==4){
		  	strcpy(commandParams->param4,slice);
			commandParams->param4[127]='\0';
		}else if(i==5){
		  	strcpy(commandParams->param5,slice);
			commandParams->param5[127]='\0';
		} 
		slice = strtok(NULL, " ");
	}
  //buffer not valid after strtok needs to be cleared
  strcpy(buffer, "");
}