/* p7_1.c: A to D conversion of channel 0
* This program converts the analog input from channel 0 (PTE20)
* using software trigger continuously.
* Bits 10-8 are used to control the tri-color LEDs. LED code is
* copied from p2_7. Connect a potentiometer between 3.3V and
* ground. The wiper of the potentiometer is connected to PTE20.
* When the potentiometer is turned, the LEDs should change color.
*/
#include <MKL25Z4.h>
void ADC0_init(void);
int gear;
int angle;
int result1;
int result2;
int result3;
int result4;
int result5;
int resulta;
int Motor1;
int Motor2;
int Motor3;
int Motor4;
int Motor5;
void motor_gear1(void);
void motor_gear2(void);
void motor_gear3(void);
void motor_gear4(void);
void motor_gear5(void);
void configure_motors(void);
void Kanca_motor(void);
void get_gear(void);
void Sag_sol(void);
void eksende_dondur(void);
void Ileri_geri(void);	
void Kendi_etrafi(void);
void servo_angle(void);
int main (void)
{
configure_motors();
ADC0_init(); /* Configure ADC0 */
	
while (1) {
Sag_sol();
eksende_dondur();
Ileri_geri();	
Kendi_etrafi();
motor_gear1();
motor_gear2();
motor_gear3();
motor_gear4();
motor_gear5();
servo_angle();
	
}
}


void Ileri_geri(void){
ADC0->SC1[0] = 9; /* start conversion on channel 0 */
while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
result1 = ADC0->R[0]; /* read conversion result and clear COCO flag */
if (result1<1990){
Motor1=2;
Motor2=1;
}
else{ 
if(result1<2460){
Motor1=0;
Motor2=0;}
else {
Motor1=1;
Motor2=2;}
}
}



void Sag_sol(void){
ADC0->SC1[0] = 3; /* start conversion on channel 0 */
while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
result2 = ADC0->R[0]; /* read conversion result and clear COCO flag */
if (result2<1990){
Motor3=1;
Motor4=0;
}
else{ 
if(result2<2460){
Motor3=2;
Motor4=2;}
else {
Motor3=0;
Motor4=1;
}
}
}



void Kendi_etrafi(void){
ADC0->SC1[0] = 8; /* start conversion on channel 0 */
while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
result3 = ADC0->R[0]; /* read conversion result and clear COCO flag */
if (result2<1990){
Motor3=1;
Motor4=1;
Motor3=1;
Motor4=1;
}
else{ 
if(result2<2460){
Motor3=0;
Motor4=0;
Motor3=0;
Motor4=0;}
else {
Motor3=2;
Motor4=2;
Motor3=2;
Motor4=2;
}
}
}



void Kanca_motor(void){
ADC0->SC1[0] = 9; /* start conversion on channel 0 */
while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
result5 = ADC0->R[0]; /* read conversion result and clear COCO flag */
if (result5<1990){
Motor5=1;
}
else{ 
if(result5<2460){
Motor5=2;}
else {
Motor5=0;}
}
}

void ADC0_init(void)
{
SIM->SCGC5 |= 0x2000; /* clock to PORTE */
SIM->SCGC5 |= 0x400; /* clock to PORTE */
PORTE->PCR[20] = 0; /* PTE20 analog input */
PORTE->PCR[21] = 0; /* PTE21 analog input */
PORTB->PCR[0] = 0 ; /* PTB0 analog input */
PORTB->PCR[1] = 0 ; /* PTB1 analog input */
PORTB->PCR[3] = 0 ; /* PTB1 analog input */
SIM->SCGC6 |= 0x8000000; /* clock to ADC0 */
ADC0->SC2 &= ~0x40; /* software trigger */
/* clock div by 4, long sample time, single ended 12 bit, bus clock */
ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00;
}
//void configure_motors(void){
//SIM->SOPT2 |= 0x01000000; /* use MCGFLLCLK as timer counter clock */
//SIM->SCGC5 |= 0x2000; /* enable clock to Port E */
//SIM->SCGC5 |= 0x0200; /* enable clock to Port A */
//SIM->SCGC6 |= 0x04000000; /* enable clock to TPM2 */
//PORTA->PCR[1] = 0x100; /* PTA1 GPIO */
//PORTA->PCR[2] = 0x100; /* PTA2 GPIO */
//PTA->PDDR |= 0x06; /* make PTA1-2 as output pins */
//PORTE->PCR[22] = 0x0300; /* PTE22 used by TPM2 */
//PORTE->PCR[23] = 0x0300; /* PTE23 used by TPM2 */
//TPM2->SC = 0; /* disable timer */
//TPM2->CONTROLS[0].CnSC = 0x20 | 0x08; /* edge-aligned, pulse high */
//TPM2->CONTROLS[1].CnSC = 0x20 | 0x08; /* edge-aligned, pulse high */
//TPM2->MOD = 3276; /* Set up modulo register for 60 Hz */
//TPM2->SC = 0x0F; /* enable TPM2 with prescaler /128 */
//}

void configure_motors(void){
SIM->SOPT2 |= 0x01000000; /* use MCGFLLCLK as timer counter clock */
SIM->SCGC5 |= 0x1000; /* clock to PORTE */
SIM->SCGC5 |= 0x2000; /* enable clock to Port E */
SIM->SCGC5 |= 0x0200; /* enable clock to Port A */
SIM->SCGC6 |= 0x01000000; /* enable clock to TPM2 */
	
PORTA->PCR[1] = 0x100; /* PTA1 GPIO */
PORTA->PCR[2] = 0x100; /* PTA2 GPIO */
PORTA->PCR[12] = 0x100; /* PTA1 GPIO */
PORTA->PCR[13] = 0x100; /* PTA2 GPIO */

PORTE->PCR[0] = 0x100; /* PTA1 GPIO */
PORTE->PCR[1] = 0x100; /* PTA2 GPIO */
PORTE->PCR[2] = 0x100; /* PTA1 GPIO */
PORTE->PCR[3] = 0x100; /* PTA2 GPIO */
PORTE->PCR[4] = 0x100; /* PTA1 GPIO */
PORTE->PCR[5] = 0x100; /* PTA2 GPIO */

PORTA->PCR[4] = 0x300; /* PTA1 GPIO */
PORTD->PCR[0] = 0x400; /* PTA2 GPIO */

PORTE->PCR[29] = 0x300; /* PTA1 GPIO */
PORTA->PCR[05] = 0x300; /* PTA2 GPIO */
PORTC->PCR[03] = 0x400; /* PTA1 GPIO */
PORTD->PCR[02] = 0x400; /* PTA2 GPIO */

PTE->PDDR |= 0x3F; /* make PTE0-1-2-3-4-5 as output pins */
PTA->PDDR |= 0x3006; /* make PTA12-13 as output pins */

TPM0->SC = 0; /* disable timer */
TPM0->CONTROLS[0].CnSC = 0x20 | 0x08; /* edge-aligned, pulse high */
TPM0->CONTROLS[1].CnSC = 0x20 | 0x08; /* edge-aligned, pulse high */
TPM0->CONTROLS[2].CnSC = 0x20 | 0x08; /* edge-aligned, pulse high */
TPM0->MOD = 3276; /* Set up modulo register for 60 Hz */
TPM0->SC = 0x0F; /* enable TPM2 with prescaler /128 */
}

void motor_gear5(void){
if (Motor5==2){
PTA->PSOR = 0x04;
PTA->PCOR = 0x02;
TPM0->CONTROLS[2].CnV = 1638; /* Set up channel value for 50% dutycycle */}
else {
if (Motor5==0){TPM0->CONTROLS[2].CnV = 0;}
else{
PTA->PSOR = 0x02;
PTA->PCOR = 0x04;
TPM0->CONTROLS[2].CnV = 1638;} /* Set up channel value for 50% dutycycle */
}
}

void motor_gear4(void){
if (Motor4==2){
PTA->PSOR = 0x2000;
PTA->PCOR = 0x1000;
TPM0->CONTROLS[2].CnV = 1638; /* Set up channel value for 50% dutycycle */}
else {
if (Motor4==0){
PTA->PCOR = 0x2000;
PTA->PCOR = 0x1000;
}
else{
PTA->PSOR = 0x2000;
PTA->PCOR = 0x1000;
TPM0->CONTROLS[2].CnV = 1638;} /* Set up channel value for 50% dutycycle */
}
}

void motor_gear3(void){
if (Motor3==2){
PTE->PSOR = 0x10;
PTE->PCOR = 0x20;
TPM0->CONTROLS[1].CnV = 1638; /* Set up channel value for 50% dutycycle */}
else {
if (Motor3==0){
PTE->PCOR = 0x10;
PTE->PCOR = 0x20;}
else{
PTA->PSOR = 0x20;
PTA->PCOR = 0x10;
TPM0->CONTROLS[1].CnV = 1638;} /* Set up channel value for 50% dutycycle */
}
}

void motor_gear2(void){
if (Motor2==2){
PTE->PSOR = 0x04;
PTE->PCOR = 0x08;
TPM0->CONTROLS[2].CnV = 1638; /* Set up channel value for 50% dutycycle */}
else {
if (Motor2==0){
PTE->PCOR = 0x08;
PTE->PCOR = 0x04;
}
else{
PTE->PSOR = 0x08;
PTE->PCOR = 0x04;
TPM0->CONTROLS[2].CnV = 1638;} /* Set up channel value for 50% dutycycle */
}
}


void motor_gear1(void){
if (Motor1==2){
PTE->PSOR = 0x01;
PTE->PCOR = 0x02;
TPM0->CONTROLS[2].CnV = 1638; /* Set up channel value for 50% dutycycle */}
else {
if (Motor1==0){
PTE->PCOR = 0x01;
PTE->PCOR = 0x02;
}
else{
PTE->PSOR = 0x02;
PTE->PCOR = 0x01;
TPM0->CONTROLS[2].CnV = 1638;} /* Set up channel value for 50% dutycycle */
}
}




void servo_angle(void){
ADC0->SC1[0] = 12; /* start conversion on channel 0 */
while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
result5 = ADC0->R[0]; /* read conversion result and clear COCO flag */
if (result5<1990){
TPM0->CONTROLS[1].CnV = 248;
}
else{ 
TPM0->CONTROLS[1].CnV = 0; /* Set up channel value for dutycycle */}
}