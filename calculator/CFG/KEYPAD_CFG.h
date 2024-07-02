/*
 * KEYPAD_CFG.h
 *
 * Created: 4/28/2024 8:24:29 PM
 *  Author: LENOVO
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#define rows 4
#define cols 4

#ifdef KEYPAD_PRG

const u8 KeysArr[rows][cols]={ {'7','8','9','/'},
                         {'4','5','6','*'},
                         {'1','2','3','-'},
                         {'c','0','=','+'},
                       };
	#endif
					   
#define FIRST_OUTPUT PINB4
#define FIRST_INPUT  PIND2					   




#endif /* KEYPAD_CFG_H_ */