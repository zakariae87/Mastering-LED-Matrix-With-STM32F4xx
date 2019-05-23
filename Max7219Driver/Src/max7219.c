/**
  ******************************************************************************
  * @file           : max7219.c
  * @brief          : Driver for MAXIM 7219
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 Zakariae BOUKARAI
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

/* Private variables ---------------------------------------------------------*/
uint8_t const disp1ay[38][8]={
{0x18,0x24,0x42,0x42,0x42,0x42,0x24,0x18},              //0
{0x10,0x30,0x50,0x10,0x10,0x10,0x10,0x7c},              //1
{0x7E,0x2,0x2,0x7E,0x40,0x40,0x40,0x7E},                //2
{0x3E,0x2,0x2,0x3E,0x2,0x2,0x3E,0x0},                   //3
{0x8,0x18,0x28,0x48,0xFE,0x8,0x8,0x8},                  //4
{0x3C,0x20,0x20,0x3C,0x4,0x4,0x3C,0x0},                 //5
{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x0},               //6
{0x3E,0x22,0x4,0x8,0x8,0x8,0x8,0x8},                    //7
{0x0,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},               //8
{0x3E,0x22,0x22,0x3E,0x2,0x2,0x2,0x3E},                 //9
{0x18,0x24,0x42,0x42,0x7E,0x42,0x42,0x42},              //A
{0x7C,0x42,0x42,0x7C,0x42,0x42,0x42,0x7C},              //B
{0x3C,0x40,0x40,0x40,0x40,0x40,0x40,0x3C},              //C
{0x7C,0x22,0x22,0x22,0x22,0x22,0x22,0x7C},              //D
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},              //E
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},              //F
{0x3C,0x40,0x40,0x40,0x4c,0x44,0x44,0x3C},              //G
{0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},              //H
{0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0xFF},              //I
{0x3C,0x8,0x8,0x8,0x8,0x8,0x48,0x30},                   //J
{0x0,0x24,0x28,0x30,0x20,0x30,0x28,0x24},               //K
{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},              //L
{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},              //M
{0x81,0xC1,0xA1,0x91,0x89,0x85,0x83,0x81},              //N
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},              //O
{0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},              //P
{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},              //Q
{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},              //R
{0x3F,0x40,0x40,0x3C,0x02,0x02,0x02,0xFC},              //S
{0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0x18},              //T
{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},              //U
{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},              //V
{0x0,0x49,0x49,0x49,0x49,0x2A,0x1C,0x0},                //W
{0x0,0x41,0x22,0x14,0x8,0x14,0x22,0x41},                //X
{0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},                   //Y
{0x00,0x7F,0x2,0x4,0x8,0x10,0x20,0x7F},                 //Z
{0x24,0x5B,0x99,0x81,0x42,0x24,0x18,0x00},              //Heart EMOJI
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},              //Space  
};


/**
  * @brief  This function perform writin byte.
  * @param  Byte to be written .
  * @retval None
  */
void WriteByteToMax7219(uint8_t byte)
{
  for (int i =0; i<8; i++)
  {
    HAL_GPIO_WritePin(GPIOA, CLK_Pin, GPIO_PIN_RESET);             // pull the clock pin low
    HAL_GPIO_WritePin(GPIOA, DIN_Pin, (byte&0x80));                // write the MSB bit to the data pin
    byte = byte<<1;                                                // shift left
    HAL_GPIO_WritePin (GPIOA, CLK_Pin, GPIO_PIN_SET);              // pull the clock pin HIGH
  }
}

/**
  * @brief  This function perform writin byte value.
  * @param  Data to be written for a griven Adress .
  * @retval None
  */
void WriteDataToMaximFromAdress (uint8_t address, uint8_t data)
{
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);  // pull the CS pin LOW
  WriteByteToMax7219(address);
  WriteByteToMax7219(data); 
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);  // pull the CS pin HIGH
}


/**
  * @brief  This function initilize Maxim 7219.
  * @param  None .
  * @retval None
  */

void Max7219Init(void)
{
  WriteDataToMaximFromAdress(0x09, 0x00);       //  no decoding
  WriteDataToMaximFromAdress(0x0A, 0x03);       //  brightness intensity
  WriteDataToMaximFromAdress(0x0B, 0x07);       //  scan limit = 8 LEDs
  WriteDataToMaximFromAdress(0x0C, 0x01);       //  power down =0,normal mode = 1
  WriteDataToMaximFromAdress(0x0F, 0x00);       //  no test display
}


/**
  * @brief  This function perform writing String value.
  * @param  String to be written .
  * @retval None
  */
void WriteStringToMax7219(uint8_t *str)
{
  while (*str)
  {
    for(int i=1; i<9; i++)
    {
      WriteDataToMaximFromAdress(i,disp1ay[(*str - 55)][i-1]);
    }
    *str++;
    HAL_Delay (1000);
  }
  
}

/**
  * @brief  This function display charctere.
  * @param  None.
  * @retval None
  */
void DisplayArray(void)
{
  for(int j=0; j<38; j++)
  {
    for(int i=1; i<9; i++)
    {
      WriteDataToMaximFromAdress(i,disp1ay[j][i-1]);
    }
    HAL_Delay (1000);
  } 
}



