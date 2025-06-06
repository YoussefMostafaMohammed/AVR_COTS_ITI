#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SET_BIT(Reg,Bit) (Reg)|=(1<<(Bit));
#define CLR_BIT(Reg,Bit) (Reg)&=(~(1<<(Bit)));
#define TOGGLE_BIT(Reg,Bit) (Reg)^=(1<<(Bit)); 
#define GET_BIT(Reg,Bit) ((Reg>>Bit)&1)

int main(void){
	SET_BIT(DDRC,PIN0);
	while(1){	
			SET_BIT(PORTC,PIN0);
			_delay_ms(500);
			CLR_BIT(PORTC,PIN0);
			_delay_ms(500);
	}
	return 0;
}
