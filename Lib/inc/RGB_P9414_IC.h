

//#include <iostm8s001j3.h>
//#include <iostm8s003f3.h>
//#include <intrinsics.h>
#include <math.h>
#include <stm8s.h>



#define RGBLedPin_Set   "BSET    L:0x5000,      #0x03         \n"
#define RGBLedPin_ReSet   "BRES    L:0x5000,      #0x03         \n"
#define delay_100us(); delay(115);

typedef struct
{ 
  unsigned char W;
  unsigned char R;
  unsigned char G;
  unsigned char B;
}RGBColor_t;



//
//void GPIO_Config(void);
//void Clock_Config(void);
void ShowLED (void);
void RGB_C1_C2 ();
void effect_1 () ;
void effect_2 () ;
void effect_3 () ;
void effect_4 () ;
void effect_5 () ;
void effect_6 () ;
void effect_7 () ;
void effect_8 () ;
void effect_9 () ;
void effect_10 () ;
void delay_asm();
void RGB_Shift_LED_reverb (unsigned char LED_Shift,unsigned char time);
void RGB_Shift_LED_forward (unsigned char LED_Shift,unsigned char time);
void RGB_effect_5_forward (unsigned char LED_Shift,unsigned char time);
void RGB_effect_5_reverb (unsigned char LED_Shift,unsigned char time);
void RGB_Show_LED(unsigned char time);
void RGB_Clear_LED ();
void rgb_SendArray();
void nop ();
void rgb_SendColors(RGBColor_t Color);
void delay(unsigned int n);
void rgb_SetColors(unsigned char LedId,RGBColor_t Color);
void rgb_SetColor(unsigned char LedId,unsigned char W, unsigned char R, unsigned char G, unsigned char B);
void RGB_Show_LED_mode_7(unsigned char time);


