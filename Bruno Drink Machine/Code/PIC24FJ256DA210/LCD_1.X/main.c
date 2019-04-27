
// PIC24FJ256DA210 Configuration Bit Settings

// 'C' source line config statements

// CONFIG4

// CONFIG3
#pragma config WPFP = WPFP255           // Write Protection Flash Page Segment Boundary (Highest Page (same as page 170))
#pragma config SOSCSEL = SOSC           // Secondary Oscillator Power Mode Select (Secondary oscillator is in Default (high drive strength) Oscillator mode)
#pragma config WUTSEL = LEG             // Voltage Regulator Wake-up Time Select (Default regulator start-up time is used)
#pragma config ALTPMP = ALPMPDIS        // Alternate PMP Pin Mapping (EPMP pins are in default location mode)
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable (Segmented code protection is disabled)
#pragma config WPCFG = WPCFGDIS         // Write Protect Configuration Page Select (Last page (at the top of program memory) and Flash Configuration Words are not write-protected)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select (Protected code segment upper boundary is at the last page of program memory; the lower boundary is the code page specified by WPFP)

// CONFIG2
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator is disabled)
#pragma config IOL1WAY = ON             // IOLOCK One-Way Set Enable (The IOLOCK bit (OSCCON<6>) can be set once, provided the unlock sequence has been completed. Once set, the Peripheral Pin Select registers cannot be written to a second time.)
#pragma config OSCIOFNC = OFF           // OSCO Pin Configuration (OSCO/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Fail-Safe Clock Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCPLL           // Initial Oscillator Select (Fast RC Oscillator with Postscaler and PLL module (FRCPLL))
#pragma config PLL96MHZ = ON            // 96MHz PLL Startup Select (96 MHz PLL is enabled automatically on start-up)
#pragma config PLLDIV = DIV2            // 96 MHz PLL Prescaler Select (Oscillator input is divided by 2 (8 MHz input))
#pragma config IESO = ON                // Internal External Switchover (IESO mode (Two-Speed Start-up) is enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config ALTVREF = ALTVREDIS      // Alternate VREF location Enable (VREF is on a default pin (VREF+ on RA9 and VREF- on RA10))
#pragma config WINDIS = OFF             // Windowed WDT (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer (Watchdog Timer is disabled)
#pragma config ICS = PGx1               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
#pragma config GWRP = OFF               // General Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = ON              // JTAG Port Enable (JTAG port is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

// PORTB defines
#define LED1    0x0010
#define LED2    0x0020
#define LED3    0x0040
#define LED4    0x0080
#define TS_YU   0x0004
#define TS_YD   0x0200
#define TS_XR   0x0008
#define TS_XL   0x0100

// PORTA defines
#define LCD_BKL 0x8000



void LCD_Init(void);


void Generic_Delay(void) {
    unsigned char Repeat;
    unsigned short Count;
    for (Repeat=0; Repeat <5; Repeat++)
    for (Count=0; Count<50000; Count++) {asm("NOP");}
} // end Generic_Delay()

void Show_LED_Byte(unsigned char Byte) {
    PORTB |= Byte&0xF0; // set some bits
    PORTB &= Byte&0xF0; // clear some bits
    Generic_Delay();
    PORTB |= (Byte&0x0F)*16; // set some bits
    PORTB &= (Byte&0x0F)*16; // clear some bits
    Generic_Delay();
    Generic_Delay();
} // end Show_LED_Byte


void main(void) {
    TRISA &= ~(LCD_BKL); // make LCD backlight an output
    TRISB &= ~(LED1|LED2|LED3|LED4); // make data LEDs outputs
    ANSB |= (TS_YU|TS_YD|TS_XL|TS_XR); // make touch screen bits analog input
    ANSB &= ~(LED1|LED2|LED3|LED4); // make data LEDs digital output

    PORTA |= (LCD_BKL); // backlight on
//    PORTA &= ~(LCD_BKL); // backlight off

    PORTB |= (LED2|LED4);
    PORTB &= ~(LED1|LED3);
    while(1) {
    //    PORTB ^= (LED1|LED2|LED3|LED4);
    //    Generic_Delay();
        Show_LED_Byte(0x01);
        Show_LED_Byte(0x24);
        Show_LED_Byte(0x89);
        Show_LED_Byte(0xAC);
        Show_LED_Byte(0xDE);
        Show_LED_Byte(0xF0);
        Generic_Delay();
    }
}






void LCD_Init(void){
    // initialize LCD (leaving backlight off for now)

    // module enabled, CMD watermark=4, 16 bits/pixel
    G1CON1 = 0b1000010010000000; // 0b1-0.00100.100.-----
    // 16bit width (TFT mode), no delays, test pattern? (10=bars, 00=normal)
    G1CON2 = 0b1000001010000001;// 0b10.00.--.10.100.--.001
    // 
    G1CON3 = 0b; // 0b------
} // end LCD_Init    
    
    
    