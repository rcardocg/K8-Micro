#include "stm32f3xx.h"                  // Device header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "USART.h"

// no borrar
uint8_t n;
uint8_t cmd_ready;

// no borrar
char uart_data;
char rx_data[64];

//VARIABLES GLOBALES
char tx_buffer[64];

// PROTOTIPOS
void terminal(char *cmd);
void RD(void);
void RM(char **tokens);
void PrintRD(uint32_t *regs, uint8_t index);
void MD(char **tokens);
extern void RMASM(uint8_t numReg, uint32_t newData);
extern void RDASM(uint32_t *regs);
extern void MDASM(uint32_t start, uint32_t end);


// DEFINICIONES
#define REG_SP 13
#define REG_LR 14
#define REG_PC 15
#define MD_START 0x20000000
#define MD_END   0x20000100

int main(void){
	
	USART2_Init();
	
	USART2_String("         Proyecto Final Microprocesadores 2025       \n\r");
	USART2_String("              Programa Monitor - Entrega 1           \n\r");
	USART2_String("                      Julio Fajardo                  \n\r\n\r");
	USART2_String(">> ");
	
	while(1){
		if(cmd_ready){
		  //Su codigo va aqui
			terminal(rx_data);
			cmd_ready = 0;
			USART2_String("\r\n>>");
			// Su codigo termina aqui
			cmd_ready = 0;
			USART2_String("\n\r>> ");
		}
	}
}

void terminal(char *cmd){
    char *tokens[10];
    int i = 0;

    char *token = strtok(cmd, " ");
    while(token != NULL && i < 10){
        tokens[i++] = token;
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL; // terminar array con NULL

    if(tokens[0] == NULL)
        return;

    if(strcmp(tokens[0], "RD") == 0){
        RD();
    } else if(strcmp(tokens[0], "hola") == 0){
        USART2_String("Hola");
    } else if(strcmp(tokens[0], "RM") == 0){
        RM(tokens);
    } else if(strcmp(tokens[0], "MD")==0){
				MD(tokens);
		}else if(strcmp(tokens[0], "h")==0){
			USART2_String("Comados de este proyecto: \r\n");
			USART2_String("RD \r\n");
			USART2_String("RM R{X} data  \r\n");
			USART2_String("MD [start] [end] \r\n");
			USART2_String("MM addr data [size] \r\n");
			USART2_String("BF start end data [size] \r\n");
			USART2_String("RUN addr \r\n");
			USART2_String("CALL addr \r\n ");
		}	else {
			USART2_String("Verificar sintaxis del comando, para detalles escribir: h \n\r");
    }
}

/*---------------------REGISTER DISPLAY---------------*/
void RD(void){
	uint32_t regs[16];
	RDASM(regs);
	PrintRD(regs, 0);
}

void PrintRD(uint32_t *regs, uint8_t index){
	  if(index > 15) return;
    if(index <= 12){
        sprintf(tx_buffer, "R%u = 0x%08X\r\n", index, regs[index]);
    } else if(index == REG_SP){
        sprintf(tx_buffer, "SP = 0x%08X\r\n", regs[index]);
    } else if(index == REG_LR){
        sprintf(tx_buffer, "LR = 0x%08X\r\n", regs[index]);
    } else if(index == REG_PC){
        sprintf(tx_buffer, "PC = 0x%08X\r\n", regs[index]);
    }

    USART2_String(tx_buffer);
    PrintRD(regs, index + 1);
}

/*---------------------REGISTER MODIFY---------------*/
void RM(char **tokens){
	if(tokens[1]==NULL||tokens[2]==NULL){
		USART2_String("Verificar sintaxis del comando: RM R{X} data \n\r");
		return;
	}
	char *registro = tokens[1];
	if(registro[0] == 'R'){
		registro++;
	}
	uint8_t numRegistro = atoi(registro);
	uint32_t dataInput = strtol(tokens[2], NULL, 16);
	
	// para no modificar el sp, lr o sp
	if(numRegistro>=0 && numRegistro<=12){
		RMASM(numRegistro, dataInput);
		sprintf(tx_buffer, "R%u = 0x%08X\r\n", numRegistro, dataInput);
		USART2_String(tx_buffer);
	} else {
		USART2_String("Estas editando SP, LR o PC, solo se puede editar R0-R12 \n\r");
	}
}

/*---------------------MEMORY DISPLAY---------------*/

void MD(char **tokens){
    uint32_t start, end;

    if(tokens[1]==NULL || tokens[2]==NULL){
        USART2_String("Default: SRAM 0x20000000 - 0x20000100)\r\n");
        start = MD_START;
        end   = MD_END;
    } else{
        start = strtol(tokens[1], NULL, 16);
        end   = strtol(tokens[2], NULL, 16);
				if(start > end){
            uint32_t tmp = start;
            start = end;
            end = tmp;
            USART2_String("Error de sintaxis, se intercambiaron start y end \r\n");
        }
    }

    // Iterar directamente memoria
    for(uint32_t addr = start; addr < end; addr += 4){
        uint32_t word = *((uint32_t*)addr);
        sprintf(tx_buffer, "0x%08X: 0x%08X\r\n", addr, word);
        USART2_String(tx_buffer);
    }
}


// no borrar
void USART2_IRQHandler(void){
	if(USART2->ISR & USART_ISR_RXNE){		
		uart_data = USART2->RDR;
		if(uart_data != '\r'){ 
			rx_data[n] = USART2->RDR;
			n++;	
			cmd_ready = 0;
		} else {
			rx_data[n] = '\0';
			n = 0;
			cmd_ready = 1;
		}
	}
}


/*----------------------------------Ricardo Caballeros 19001133------------------------------*/

