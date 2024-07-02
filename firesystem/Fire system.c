
#define F_CPU 8000000

#include "MemMap.h"
#include "util/delay.h"
#include "StdTypes.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "LCD_Cfg.h"
#include "KEYPAD_Int.h"
#include "ADC_Int.h" 

int main() {
    // Initialize peripherals
    DIO_Init();
    LCD_Init();
    KEYPAD_Init();
    ADC_Init(VREF_VCC, ADC_SCALER_64);

    // Variable declarations
    u16 temp, flag = 1, press, j = 0, k, from, to, opflag = 0, sflag = 0, num = 0, num1, hflag = 0, i = 0;
    u8 pass[] = {'0', '0', '0', '0'}, passenter[4] = {0};

    // Display initial message
    LCD_SetCursor(1, 2);
    LCD_WriteString("FIRE SYSTEM");
    _delay_ms(200);
    LCD_Clear();

    while (1) {
        // Read temperature and pressure
        temp = SENSOR_ReadTemp();
        press = ADC_ReadVolt(CH_7);

        // Normal mode
        if (temp <= 45 || temp < 50) {
            opflag = 0;
            DIO_WritePin(PINC0, LOW);
            LCD_SetCursor(0, 0);
            LCD_WriteNumber(temp);
            LCD_SetCursor(1, 5);
            LCD_WriteString("normal");
        }
        // Heat mode
        else if (temp > 50 && press <= 250 || opflag == 1) {
            DIO_WritePin(PINC0, HIGH);
            LCD_SetCursor(0, 12);
            LCD_WriteNumber(press);
            LCD_SetCursor(0, 0);
            LCD_WriteNumber(temp);
            LCD_SetCursor(1, 5);
            LCD_WriteString("HEAT  ");
        }
        // Fire mode
        else if (press >= 300 && opflag == 0) {
            DIO_WritePin(PINC1, HIGH);
            DIO_WritePin(PINC3, HIGH);
            LCD_SetCursor(1, 5);
            LCD_WriteString("FIRE");
            _delay_ms(100);
            LCD_Clear();
            LCD_SetCursor(0, 0);
            LCD_WriteString("password:");

            // Password entry
            while (i < 4) {
                num = KEYPAD_GETKEYS();
                if (num != NO_KEY) {
                    passenter[i] = num;
                    LCD_WriteChar(num);
                    i++;
                }
            }
            i = 0;
            flag = 1;
            for (j = 0; j < 4; j++) {
                if (pass[j] != passenter[j]) {
                    flag = 0;
                    break;
                }
            }

            // Check password
            if (flag == 1) {
                opflag = 1;
                LCD_Clear();
                DIO_WritePin(PINC1, LOW);
                DIO_WritePin(PINC3, LOW);
            } else {
                LCD_SetCursor(1, 0);
                LCD_WriteString("incorrect pass");
                _delay_ms(100);
            }
        }
        i = 0;
        j = 0;
    }
    return 0;
}                                                      	
