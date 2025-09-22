/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Microprocesadores 2017
 * Entrega 2
 * USART Tester
 * Oct-04-2017
 * USART.h
 */
 
#ifndef USART_H_
#define USART_H_

#include <stdint.h>

void USART2_Init(void);
void USART2_Send(uint8_t c);
void USART2_String(char * string);

#endif /* USART_H_ */
