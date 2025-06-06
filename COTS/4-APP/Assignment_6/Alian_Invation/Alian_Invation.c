#include "HCLCD_CFG.h"
#include "HCLCD.h"
#include <util/delay.h>

uint8_t Hamada1[8] = {0b01110, 0b01110, 0b00100, 0b10101, 0b01110, 0b00100, 0b01010, 0b10001};
uint8_t Hamada2[8] = {0b01110, 0b01110, 0b00101, 0b00110, 0b01100, 0b10100, 0b01010, 0b10000};
uint8_t Hamada3[8] = {0b00000, 0b00000, 0b11100, 0b11100, 0b01011, 0b01100, 0b01000, 0b10100};
uint8_t aship1[8] = {0b00000, 0b00000, 0b00011, 0b00100, 0b11000, 0b00100, 0b00011, 0b00000};
uint8_t aship2[8] = {0b00100, 0b01010, 0b10001, 0b00000, 0b00000, 0b00000, 0b11011, 0b00100};
uint8_t aship3[8] = {0b00000, 0b00000, 0b11000, 0b00100, 0b00011, 0b00100, 0b11000, 0b00000};
uint8_t Alien[8] = {0b11111, 0b10101, 0b11111, 0b11111, 0b01110, 0b01010, 0b11011, 0b00000};
uint8_t ship1[8] = {0b00000, 0b00100, 0b00000, 0b00100, 0b00100, 0b01010, 0b01010, 0b11111};
uint8_t ship2[8] = {0b00100, 0b00000, 0b00000, 0b00100, 0b00100, 0b01010, 0b01010, 0b11111};
uint8_t bomb[8] = {0b11011, 0b00111, 0b11100, 0b10101, 0b11011, 0b10110, 0b01011, 0b11010};
uint8_t bullet[8] = {0b00000, 0b00000, 0b000000, 0b00000, 0b00001, 0b00000, 0b00000, 0b00000};
uint8_t bell[8] = {0b00000, 0b00100, 0b01110, 0b01110, 0b01110, 0b11111, 0b00000, 0b00100};
uint8_t daship1[8] = {0b00000, 0b00010, 0b00101, 0b11000, 0b00100, 0b00011, 0b00000, 0b00000};
uint8_t daship2[8] = {0b00000, 0b00100, 0b01011, 0b10000, 0b00000, 0b01011, 0b10100, 0b00000};
uint8_t Hamada4[8] = {0b01110, 0b01110, 0b00100, 0b10111, 0b01100, 0b00100, 0b01010, 0b10010};
uint8_t Hamada5[8] = {0b01110, 0b01110, 0b00100, 0b11100, 0b00110, 0b00100, 0b01010, 0b01001};
uint8_t skull[8] = {0b00000, 0b01110, 0b10101, 0b11011, 0b01110, 0b01110, 0b00000, 0b00000};

int main()
{
  HCLCD_enuInit();
  while (1)
  {
    HCLCD_enuGotoRowColumn(0, 1,LCD_ONE);
    HCLCD_enuWriteString("< Space War >",LCD_ONE);
    _delay_ms(1000);
    HCLCD_enuGotoRowColumn(0, 3,LCD_ONE);
    HCLCD_enuWriteString("Air forces",LCD_ONE);
    HCLCD_enuGotoRowColumn(1, 4,LCD_ONE);
    HCLCD_enuWriteString(" Attack !",LCD_ONE);
    _delay_ms(1000);

    HCLCD_enuStoreSpecialChar(ship1, 0,LCD_ONE);
    HCLCD_enuStoreSpecialChar(ship2, 1,LCD_ONE);
    HCLCD_enuStoreSpecialChar(aship1, 2,LCD_ONE);
    HCLCD_enuStoreSpecialChar(aship2, 3,LCD_ONE);
    HCLCD_enuStoreSpecialChar(aship3, 4,LCD_ONE);
    HCLCD_enuStoreSpecialChar(bell, 5,LCD_ONE);
    HCLCD_enuStoreSpecialChar(daship1, 6,LCD_ONE);
    HCLCD_enuStoreSpecialChar(daship2, 7,LCD_ONE);

    int i = 0, flag = 0;
    for (int j = 0; j < 35; j++)
    {
    HCLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);
      if (j <= 10)
        HCLCD_enuDisplaySpecialChar(5,0,19,LCD_ONE);
      if ((j / 14) % 2 == 0)
      {
        HCLCD_enuDisplaySpecialChar(2,0,i%14,LCD_ONE);
        HCLCD_enuDisplaySpecialChar(3,0,(i%14)+1,LCD_ONE);
        HCLCD_enuDisplaySpecialChar(4,0,(i%14)+2,LCD_ONE);
        if (i >= 2 || flag)
        {
            HCLCD_enuDisplaySpecialChar(i%2,1,(i%14)+1,LCD_ONE);
          flag = 1;
        }
        i++;
      }
      else if ((j / 14) % 2 == 1)
      {
        i--;
        HCLCD_enuDisplaySpecialChar(2,0,(i%14),LCD_ONE);
        HCLCD_enuDisplaySpecialChar(3,0,(i%14)+1,LCD_ONE);
        HCLCD_enuDisplaySpecialChar(4,0,(i%14)+2,LCD_ONE);
        if (i >= 2 || flag)
            HCLCD_enuDisplaySpecialChar(i%2,1,(i%14)+1,LCD_ONE);
      }
      _delay_ms(200);
    }
    HCLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);
    HCLCD_enuDisplaySpecialChar(6,1,i%14,LCD_ONE);
    HCLCD_enuDisplaySpecialChar(7,1,(i%14)+1,LCD_ONE);
    HCLCD_enuDisplaySpecialChar(4,1,(i%14)+2,LCD_ONE);
    HCLCD_enuDisplaySpecialChar(0,1,(i%14)+1,LCD_ONE);
    _delay_ms(750);

    HCLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);
    HCLCD_enuStoreSpecialChar(Hamada1, 0,LCD_ONE);
    HCLCD_enuStoreSpecialChar(Hamada2, 1,LCD_ONE);
    HCLCD_enuStoreSpecialChar(Hamada3, 2,LCD_ONE);
    HCLCD_enuStoreSpecialChar(bullet, 3,LCD_ONE);
    HCLCD_enuStoreSpecialChar(Alien, 4,LCD_ONE);
    HCLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);

    HCLCD_enuGotoRowColumn(0, 0,LCD_ONE);
    HCLCD_enuWriteString(">They Landed,Sir",LCD_ONE);
    _delay_ms(1000);
    HCLCD_enuGotoRowColumn(0, 0,LCD_ONE);
    HCLCD_enuWriteString("Soldiers, attack!",LCD_ONE);
    _delay_ms(1000);

    i = 0;
    for (; i < 25; i++)
    {
        HCLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);
      
      if(i >= 8){
        flag=0;
      }else{
        HCLCD_enuDisplaySpecialChar(5,0,19,LCD_ONE);
      }
      if (i <= 4){
        HCLCD_enuDisplaySpecialChar(4,1,15-(i%5),LCD_ONE);
      }
      else{
        HCLCD_enuDisplaySpecialChar(4,1,11,LCD_ONE); 
        }
      if (i == 1){
        HCLCD_enuDisplaySpecialChar(0,1,i-1,LCD_ONE);
        }
      else if (i == 2 || i == 3){
        HCLCD_enuDisplaySpecialChar(1,1,i-1,LCD_ONE);
        }
      else if (i >= 4){
        HCLCD_enuDisplaySpecialChar(2,1,3,LCD_ONE);
        }
      if (i > 4){
        HCLCD_enuDisplaySpecialChar(3,1,(i%6)+5,LCD_ONE);
        }
      _delay_ms(250);
    }
    HCLCD_enuStoreSpecialChar(skull,4,LCD_ONE);
    HCLCD_enuDisplaySpecialChar(4,1,11,LCD_ONE);
    _delay_ms(1000);
    HCLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);
    HCLCD_enuStoreSpecialChar(Hamada4,1,LCD_ONE);
    HCLCD_enuStoreSpecialChar(Hamada4,2,LCD_ONE);
    HCLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);
    HCLCD_enuGotoRowColumn(0,7,LCD_ONE);
    HCLCD_enuWriteString("gg Ez",LCD_ONE);
    _delay_ms(1000);
    i = 0;
    for (; i < 25; i++)
    {
      HCLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);
      HCLCD_enuGotoRowColumn(0,3,LCD_ONE);
      HCLCD_enuWriteString(" We Won <3 ",LCD_ONE);
      HCLCD_enuDisplaySpecialChar(i%3,1,i,LCD_ONE);
      _delay_ms(300);
    }
      HCLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);
  }
}


