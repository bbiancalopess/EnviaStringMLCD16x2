/*
Prog03a 
Elabore um programa que envie uma frase para a primeira
linha do MLCD
*/


#include "io430.h"


// Coloque aqui os seus defines.
#define RS BIT7         // O pino RS está conectado em P3.7
#define EN BIT6         // O pino Enable está conectado em P3.6
#define Fclk 750e3
#define _100us 100e-6*Fclk // Num pulsos de clk para delay de 100us
#define _2ms (int)(2e-3*Fclk) 
#define _250ms ( long int)(250e-3*Fclk) 
#define _5ms (int)(5e-3*Fclk) 

// Protótipo das funções
void Init_Display();
void Config_Display();
void EnviaComando(unsigned char Comando);
void EnviaDado(unsigned char Dado);
void Envia();
void EnviaString(unsigned char *string);
void Letra();



void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  // Inicializa o I/O ligado ao MLCD
  Init_Display(); 
  
  // Configura o MLCD para funcionamento básico
  Config_Display();
  
  // Envia um caractere par o MLC
  EnviaString("ARROZ DOCE");
  
  // Envia um comando para passar para a segunda linha
  EnviaComando(0xC0);
  
  // Envia um caractere par o MLC
   EnviaString("CAldo de cana");
   
 /* while (1)
  {
  
  // nosso programa
  
  
  }
  
*/  
}




/* Função inicializa I/O para o display
Barramento de dados P5.0 até P5.7
Pino RS P3.7
Pino En P3.6
*/
void Init_Display()
{
  P5SEL = 00;    // Configura 8 bits como I/O
  P5DIR = 0xFF;  // Configura 8 bits como saída
  
  P3SEL &= ~(EN+RS);  // Configura Bits 6 e 7 como I/O
  // A forma acima é a versão reduzida de: 
  // P3SEL = P3SEL & ~(BIT6+BIT7)
  P3DIR |= (EN+RS);  // Configura bits 6 e 7 com saída
}
/*
Inicializa o controladora do MLCD para o funcionamento
básico
Matriz 5x7, duas linhas ativas, cursor ligado
*/
void Config_Display()
{
__delay_cycles(_250ms);   // Delay de 250ms  
EnviaComando (0x38);
__delay_cycles(_5ms);   // Delay de 5ms
EnviaComando (0x0E);
EnviaComando (0x06);
EnviaComando (0x01);
__delay_cycles(_2ms);   // Delay de 2ms
}

// Função que envia um comando para o MLCD
// Neste caso o pino RS = 0
void EnviaComando(unsigned char Comando)
{
 P5OUT = Comando;
 P3OUT &= ~RS;  // Faz RS = 0
 Envia();
 }

// Função que envia um dado para o MLCD
// Neste caso o pino RS = 1
void EnviaDado(unsigned char Dado)
{
 P5OUT = Dado;
 P3OUT |= RS;  // Faz RS = 1
 Envia();
 }

// Gera o pulso de Enable
void Envia()
{
 P3OUT &= ~EN;  //Faz Enable = 0
 P3OUT |= EN;  //Faz Enable = 1 
 P3OUT &= ~EN;  //Faz Enable = 0
 __delay_cycles(_100us);  // Delay de 100us
}

// Envia uma frase
void EnviaString(unsigned char *string)
{
 while(*string)
 {
  EnviaDado(*string);
  string++;
 }


}

        

           