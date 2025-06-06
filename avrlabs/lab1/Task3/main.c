#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SET_BIT(Reg,Bit) (Reg)|=(1<<(Bit));
#define CLR_BIT(Reg,Bit) (Reg)&=(~(1<<(Bit)));
#define TOGGLE_BIT(Reg,Bit) (Reg)^=(1<<(Bit)); 
#define GET_BIT(Reg,Bit) ((Reg>>Bit)&1)

int main(){	
	CLR_BIT(DDRA,PIN0);
	SET_BIT(PORTA,PIN0);
	
	SET_BIT(DDRC,PIN0);
	SET_BIT(DDRC,PIN1);
	SET_BIT(DDRC,PIN2);
	SET_BIT(DDRC,PIN3);

	int ans=0;
	PORTC=0x00;
	while(1){
		if(ans==15)ans=0;
		else
		if(GET_BIT(PINA,PIN0)==0){
			while(GET_BIT(PINA,PIN0)==0);
			ans++;
			PORTC=ans;
		}
		_delay_ms(50);
	}
	return 0;
}

