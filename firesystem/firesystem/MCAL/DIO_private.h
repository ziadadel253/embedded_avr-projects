#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

extern const DIO_Status_t PinsStatusArr[TOTAL_PINS];

static void DIO_InitPin(DIO_Pin_t pin, DIO_Status_t status);

#endif /* DIO_PRIVATE_H_ */