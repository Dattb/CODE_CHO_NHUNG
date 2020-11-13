

#include <math.h>
#include <RGB_P9414_IC.h>


//#define RGBLedPin_Set   "BSET    L:0x5000,      #0x03         \n"
//#define RGBLedPin_ReSet   "BRES    L:0x5000,      #0x03         \n"
//#define delay_100us(); delay(115);


const RGBColor_t RED = {0,255,0,0};
const RGBColor_t GREEN = {0,0,255,0};
const RGBColor_t BLUE = {0,0,0,255};
const RGBColor_t BLACK = {0,0,0,0};
const RGBColor_t WHITE = {0,255,255,255};

#define NB_LEDS 71                 // so luong led dieu khien la 71 nhung thuc the chi dung 60 LED (5 m)
unsigned char LedsArray[NB_LEDS*4]; // khai bao mang voi so luong byte du lieu can dung de truyen data cho so led = so led x 4 (do 4 kenh mau)
unsigned int nbLedsBytes = NB_LEDS*4;  // so luong byte du lieu cua ledsArray
unsigned int effect1_cnt=0,effect4_cnt=0,foward_cnt=0,reverb_cnt=0,effect_5_cnt=0,effect_6_cnt=0,effect_7_cnt=0;
unsigned char  Settup_status,mode_effect_save;
unsigned char mode_effect=1; 
unsigned char chedo_save; 
extern unsigned char Time_out;
RGBColor_t      LEDTempSave;    
RGBColor_t      LEDTempSaveOff;
RGBColor_t      *LEDTemp1;
RGBColor_t      *LEDTemp2;


RGBColor_t      *LEDTempLastPoint;
RGBColor_t      *LEDTempBeginPoint;
RGBColor_t      *LEDTempRunPoint;
RGBColor_t      *LEDTempEndPoint;
unsigned char   CheckDone = 0;
unsigned char   vruc_Count;
unsigned char mode_save;
inline void ShowLED (void) // ham nay de show led trong effect 7
{
  RGB_Show_LED_mode_7(10); // gui data ra chan PA3 10 lan 
  vruc_Count++;           // tang gia tri dem
  if(vruc_Count >= 6)     // neu gia tri dem >6
  {      
    if(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5))      // doc gia tri nut an  PC5
    {
    while(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5));  //  doi toi khi nha nut an ra
    mode_effect=1;  // hieu ung =1
    }
    vruc_Count = 0;           // dat lai gia tri dem
    LEDTempBeginPoint = (RGBColor_t *)(LedsArray);  // ep kieu LedArray sang con tro kieu RGBColor_t roi gan cho LEDTempBeginPoint
    LEDTempSave.W = 1;           // tat LED White
    LEDTempSave.R = rand()%254 + 1;  // lay gia tri random cho LED R
    LEDTempSave.G = rand()%254 + 1;  // lay gia tri random cho LED G
    LEDTempSave.B = rand()%254 + 1;  // lay gia tri random cho LED B
    *LEDTempBeginPoint = LEDTempSave;  // gan gia tri cua LEDTempSave vao con tro LEDTempBeginPoint
  }
  else
  {
        if(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5))    // doc gia tri nut an  PC5
    {
    while(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5));    //  doi toi khi nha nut an ra
    mode_effect=1;  // hieu ung =1
    }
    LEDTempBeginPoint = (RGBColor_t *)(LedsArray);  // ep kieu LedArray sang con tro kieu RGBColor_t roi gan cho LEDTempBeginPoint
    *LEDTempBeginPoint = LEDTempSaveOff;            // gan gia tri cua LEDTempSave vao con tro LEDTempBeginPoint
  }
  //if(Time_out>=)
}

void effect_7 (){
  chedo_save=mode_effect;   // luu lai gia tri cua hieu ung
  
  CheckDone = 0;    // kiem tra da gui het data cua hieu ung chua
    for(unsigned char i=0;i<10;i++)   // dat mau cau vong cho chuoi RGB
  { 
//    if(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5))
//    {
//    while(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5));
//    mode_effect=1;
//    }
    rgb_SetColor(i,0,255,i*25,0);
    rgb_SetColor(i+10,0,255-i*25,255,0);
    rgb_SetColor(i+20,0,0,255,i*25);
    rgb_SetColor(i+30,0,0,255-i*25,255);
    rgb_SetColor(i+40,0,i*25,0,255);
    rgb_SetColor(i+50,0,255,0,255-i*25);
    
  } 
   
  LEDTempEndPoint  = (RGBColor_t *)(LedsArray + 240);
  LEDTempLastPoint = (RGBColor_t *)(LedsArray + 236);
  
  while(!CheckDone){  // kiem tra neu chua truyen xong 
      if(chedo_save==mode_effect) // kiem tra neu hieu ung bi thay doi
      {
        if(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5)) // kiem tra nut an PC5
        {
          while(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5)); // neu van giu nut
          mode_effect=1;  // hieu ung =1
        }
    LEDTempBeginPoint = (RGBColor_t *)(LedsArray);
    while(!(*LEDTempLastPoint).W){
      LEDTempRunPoint = LEDTempLastPoint;
      while(LEDTempBeginPoint != LEDTempRunPoint){
        *(LEDTempRunPoint) = *(LEDTempRunPoint-1);
        LEDTempRunPoint--;
        if(Time_out>=200) break;
      }
      delay(1000);
      ShowLED();
      if(Time_out>=200) break;
    }
    
    LEDTempLastPoint--;
    
    
    if(LEDTempBeginPoint == LEDTempLastPoint){
      CheckDone = 1;
    }
  }else break;
  if(Time_out>=200) break;
  }
  
  
}




   
void effect_1 () 
{
    effect1_cnt++; // hieu ung 1 counter
     if(effect1_cnt<52) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)  // dat gia tri cua 60 led dau tien cung 1 mau roi gui data ra
      {
        rgb_SetColor(i,0,255,effect1_cnt*5,0);
      }
              RGB_Show_LED(40); 
    }
    // for(int j=0;j<52;j++)
    else if(effect1_cnt<104)// 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,255-5*(effect1_cnt-52),255,0);
      } 
              RGB_Show_LED(40); 
    }
    //    for(int j=0;j<52;j++)
    else if(effect1_cnt<156)// 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,0,255,5*(effect1_cnt-104));
      } 
              RGB_Show_LED(40); 
    }
    else if(effect1_cnt<208) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,0,255-5*(effect1_cnt-156),255); 
      } 
              RGB_Show_LED(40); 
    }
    else if(effect1_cnt<260) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,5*(effect1_cnt-208),0,255);
      } 
              RGB_Show_LED(40); 
    }
    else if(effect1_cnt<312) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,255,0,255-5*(effect1_cnt-260));
      } 
              RGB_Show_LED(40); 
    } else  effect1_cnt=0;
}
void effect_2 ()
{ 
   if(!Settup_status)  // settup du lieu cho lan dau 
   {
      for(unsigned char i=0;i<10;i++)
      { 
      rgb_SetColor(i,0,255,i*25,0);
      rgb_SetColor(i+10,0,255-i*25,255,0);
      rgb_SetColor(i+20,0,0,255,i*25);
      rgb_SetColor(i+30,0,0,255-i*25,255);
      rgb_SetColor(i+40,0,i*25,0,255);
      rgb_SetColor(i+50,0,255,0,255-i*25);
      } 
      Settup_status=1;
   }
   RGB_Shift_LED_forward(60,10); // tu du lieu settup ben tren dich tung led (4 byte) trong mang LedsArray theo chieu thuan
}


void effect_3 ()
{
  if(!Settup_status)     // settup du lieu cho lan dau 
  {
    for(unsigned char i=0;i<5;i++)
    { 
      rgb_SetColor(i,0,255,i*50,0);
      rgb_SetColor(i+5,0,0,0,0);
      rgb_SetColor(i+10,0,255-i*50,255,0);
      rgb_SetColor(i+15,0,0,0,0);
      rgb_SetColor(i+20,0,0,255,i*50);
      rgb_SetColor(i+25,0,0,0,0);
      rgb_SetColor(i+30,0,0,255-i*50,255);
      rgb_SetColor(i+35,0,0,0,0);
      rgb_SetColor(i+40,0,i*50,0,255);
      rgb_SetColor(i+45,0,0,0,0);
      rgb_SetColor(i+50,0,255,0,255-i*50);
      rgb_SetColor(i+55,0,0,0,0);
    } 
    Settup_status=1;
  }
  RGB_Shift_LED_forward(60,10);        // tu du lieu settup ben tren dich tung led (4 byte) trong mang LedsArray theo chieu thuan
}

void effect_4 ()
{  
  effect4_cnt++;    // Hieu ung 4 counter
    //for(unsigned char i=0;i<63;i++)
  if(effect4_cnt<63)  // vua dich led vua gui du lieu ra
    {    
      rgb_SetColor(effect4_cnt,0,255,255-effect4_cnt*4,0);
      RGB_Show_LED(7);
    }
   // for(unsigned char i=0;i<63;i++)
  else if(effect4_cnt<126)
    {
      rgb_SetColor(effect4_cnt-63,0,255,0,(effect4_cnt-63)*4);
      RGB_Show_LED(7);
    }
    
   // for(unsigned char i=0;i<63;i++) 
  else if(effect4_cnt<189)
    {
      rgb_SetColor((effect4_cnt-126),0,255-(effect4_cnt-126)*4,0,255);
      RGB_Show_LED(7);
    }
   // for(unsigned char i=0;i<63;i++) 
  else if(effect4_cnt<252)
    {
      rgb_SetColor((effect4_cnt-189),0,0,(effect4_cnt-189)*4,255);
      RGB_Show_LED(7);
    }
    
   // for(unsigned char i=0;i<60;i++)
  else if(effect4_cnt<315)
    {
      rgb_SetColor((effect4_cnt-252),0,0,255,255-(effect4_cnt-252)*4);
      RGB_Show_LED(7);
    }
    //for(unsigned char i=0;i<60;i++)
  else if(effect4_cnt<378)
    {
      rgb_SetColor((effect4_cnt-315),0,(effect4_cnt-315)*4,255,0);
      RGB_Show_LED(7);
    }
}

 void effect_5 () //  day led
{   mode_effect_save=mode_effect;
    RGB_Clear_LED(); //  xoa het LED
    for(unsigned char i=0;i<30;i++) // dich led roi gui ra
    rgb_SetColor(i,0,255,0,0);  //dat 30 led mau do
    RGB_effect_5_forward(30,10);

    RGB_Clear_LED();
    for(unsigned char i=0;i<31;i++) // ...
    rgb_SetColor(60-i,0,0,255,0);
    RGB_effect_5_reverb(30,10); 

    RGB_Clear_LED();
    for(unsigned char i=0;i<30;i++)
    rgb_SetColor(i,0,0,0,255);   
    RGB_effect_5_forward(30,10);

    RGB_Clear_LED();
    for(unsigned char i=0;i<31;i++)
    rgb_SetColor(60-i,0,130,130,0);
    RGB_effect_5_reverb(30,10);

    RGB_Clear_LED();
    for(unsigned char i=0;i<30;i++)
    rgb_SetColor(i,0,0,130,130); 
    RGB_effect_5_forward(30,10);

    RGB_Clear_LED();
    for(unsigned char i=0;i<31;i++)
    rgb_SetColor(60-i,0,130,0,130);    
    RGB_effect_5_reverb(30,10);
}

void effect_6 () 
{    effect_6_cnt++;
   // for(unsigned char i=0;i<60;i++)
    if(effect_6_cnt<60)   // hien thi led duoi dan dan roi tat dan dan
    {
      rgb_SetColor(effect_6_cnt,0,effect_6_cnt*4,255-effect_6_cnt*4,0);
      RGB_Show_LED(3);
    }
    else if(effect_6_cnt<120)
    {
      rgb_SetColor((effect_6_cnt-60),0,0,0,0);
      RGB_Show_LED(15);
    }
    else if(effect_6_cnt<180)
    { 
      rgb_SetColor((effect_6_cnt-120),0,(effect_6_cnt-120)*4,255-(effect_6_cnt-120)*4,0);
      RGB_Show_LED(3);
    }
    else if(effect_6_cnt<240)
    {
        rgb_SetColor((effect_6_cnt-180),0,0,0,0);
        RGB_Show_LED(15);
    }
    else if(effect_6_cnt<300)
    {
      rgb_SetColor((effect_6_cnt-240),0,255-(effect_6_cnt-240)*4,0,(effect_6_cnt-240)*4);
      RGB_Show_LED(3); 
    }
    else if(effect_6_cnt<360)
    {
        rgb_SetColor((effect_6_cnt-300),0,0,0,0);
        RGB_Show_LED(15);
    }
    else if(effect_6_cnt<420)
    {
      rgb_SetColor((effect_6_cnt-360),0,0,(effect_6_cnt-360)*4,255-(effect_6_cnt-360)*4);
      RGB_Show_LED(3);
    }
    else if(effect_6_cnt<480)
    {
        rgb_SetColor((effect_6_cnt-420),0,0,0,0);
        RGB_Show_LED(15); 
    }
    else if(effect_6_cnt>=480) effect_6_cnt=0;
    
}
void delay_asm() {}  // ham dung de tao khoang delay 
/* 
 void RGB_C1_C2 (): ham de dat dong dien on dinh cho chuoi lED RGB bao gom  C1 32  va bit C2 32 bit (nguoc lai voi C1)
 tang giam gia tri C1 se lam tang giam dong dien on dinh xuat ra cac LED W,R,G,B*/
inline void RGB_C1_C2 ()  
{
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");

asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();

asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();

asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();

asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();

asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");

asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");

asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");delay_asm();asm("NOP");asm("NOP");  ///////////////////////////////////// bit 1
asm("BSET    L:0x5000,      #0x03         \n");delay_asm();
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
asm("BRES    L:0x5000,      #0x03         \n");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");////////////////// bit 0
asm("BSET    L:0x5000,      #0x03         \n"); delay_asm();asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");

}
inline void nop (){}


/*
  rgb_SendArray() : + HAM QUAN TRONG
                    + ham nay co tac dung gui 8 bit data ra chan OUTPUT bang ngon ngu assembly de tang toc do chuyen data
                      vi toc do xu ly bang ngon ngu C khong the dap ung duoc cho ICP 9414
                    + khi truyen vao ham ma?ng nbLedsBytes[] hay LedsArray [] ham se gui tat ca cac byte (8 bit) trong mang 
                      bang assembly ra chan OUTPUT , o day OUTPUT la PA3                   
*/
void rgb_SendArray() 
{
   unsigned char int_state = __get_interrupt_state();
    __disable_interrupt();
  asm(
        "lb_intiLoop:                          \n"
        "LDW      X,             #0xFFFF       \n"// set -1 in X, so that first inc gets 0, as inc has to be in the beginning of the loop
        "LDW      Y,             L:nbLedsBytes \n"//2
        "lb_begin_loop:                        \n"
//---------------------------------------------------------------
//--------------- bit 0 -----------------------------------------
        "INCW    X                           \n"// L t+2
        "lb_start_bit0:                      \n"//
        "LD      A,           (L:LedsArray,X)\n"//
        RGBLedPin_ReSet
        "AND     A,             #0x80        \n"// H t2
        "JREQ    L:lb_bit0_Send_0            \n"// H0 t3 t4 : 2 jump to Zero, 1 Stay in One + next nop
        "lb_bit0_Send_1:                     \n"//------Send 1 : 800ns High, 450ns Low (12,8) 750ns,500ns
        "nop                                 \n"// H1 t5
        "nop                                 \n"// H1 t6
        "nop                                 \n"// H1 t7
        "nop                                 \n"// H1 t8
        "nop                                 \n"// H1 t9
        "nop                                 \n"// H1 t10
        "nop                                 \n"// H1 t11
        "nop                                 \n"// H1 t12
         RGBLedPin_Set                         // L0 t1

        "nop                                 \n"// L1 t2
        "JRA     L:lb_start_bit1             \n"// L1 JRA:2 t4 
                                                // L1 NextBitTest:4  t8
        "lb_bit0_Send_0:                     \n"//------Send 0 : 400ns High, 850ns Low (7,13) 375ns,875ns
                                                // H0 t4
        "nop                                 \n"// L0 t1
        "nop                                 \n"// L0 t1
         RGBLedPin_Set                         // L1 t1
        "nop                                 \n"// L0 t1
        "nop                                 \n"// L0 t2
        "nop                                 \n"// L0 t3
        "nop                                 \n"// L0 t4
        "nop                                 \n"// L0 t5
        "nop                                 \n"// L0 t6
        "nop                                 \n"// L0 t7
        "nop                                 \n"// L0 t8
                                                //NextBitTest:4+SP = 5. L t13
//--------------- bit 1 -----------------------------------------
        "lb_start_bit1:                      \n"//
        "LD      A,           (L:LedsArray,X)\n"//1
        "AND     A,             #0x40        \n"//1
        "JREQ    L:lb_bit1_Send_0            \n"//2 jump to Zero, 1 Stay in One + next nop
        "lb_bit1_Send_1:                     \n"
        "nop                                 \n"//1 to have send0 send1 equality
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        "nop                                 \n"// H t7
        "nop                                 \n"// H t8
        "nop                                 \n"// H t9
        "nop                                 \n"// H t10
        "nop                                 \n"// H t11
        "nop                                 \n"// H t12
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t2
        "JRA     L:lb_start_bit2             \n"// L JRA:2 t4 
                                                // L NextBitTest:4  t8
        "lb_bit1_Send_0:                     \n"//------Send 0 : 400ns High, 850ns Low (6,14) 375ns,875ns
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t1
        "nop                                 \n"// L t2
        "nop                                 \n"// L t3
        "nop                                 \n"// L t4
        "nop                                 \n"// L t5
        "nop                                 \n"// L t6
        "nop                                 \n"// L t7
        "nop                                 \n"// L t8
        "nop                                 \n"// L t9
                                                //NextBitTest:4+SP = 5. L t14
//--------------- bit 2 -----------------------------------------
        "lb_start_bit2:                      \n"//
        "LD      A,           (L:LedsArray,X)\n"//1
        "AND     A,             #0x20        \n"//1
        "JREQ    L:lb_bit2_Send_0            \n"//2 jump to Zero, 1 Stay in One + next nop
        "lb_bit2_Send_1:                     \n"
        "nop                                 \n"//1 to have send0 send1 equality
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        "nop                                 \n"// H t7
        "nop                                 \n"// H t8
        "nop                                 \n"// H t9
        "nop                                 \n"// H t10
        "nop                                 \n"// H t11
        "nop                                 \n"// H t12
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t2
        "JRA     L:lb_start_bit3             \n"// L JRA:2 t4 
                                                // L NextBitTest:4  t8
        "lb_bit2_Send_0:                     \n"//------Send 0 : 400ns High, 850ns Low (6,14) 375ns,875ns
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t1
        "nop                                 \n"// L t2
        "nop                                 \n"// L t3
        "nop                                 \n"// L t4
        "nop                                 \n"// L t5
        "nop                                 \n"// L t6
        "nop                                 \n"// L t7
        "nop                                 \n"// L t8
        "nop                                 \n"// L t9
                                                //NextBitTest:4+SP = 5. L t14
//--------------- bit 3 -----------------------------------------
        "lb_start_bit3:                      \n"//
        "LD      A,           (L:LedsArray,X)\n"//1
        "AND     A,             #0x10        \n"//1
        "JREQ    L:lb_bit3_Send_0            \n"//2 jump to Zero, 1 Stay in One + next nop
        "lb_bit3_Send_1:                     \n"
        "nop                                 \n"//1 to have send0 send1 equality
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        "nop                                 \n"// H t7
        "nop                                 \n"// H t8
        "nop                                 \n"// H t9
        "nop                                 \n"// H t10
        "nop                                 \n"// H t11
        "nop                                 \n"// H t12
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t2
        "JRA     L:lb_start_bit4             \n"// L JRA:2 t4 
                                                // L NextBitTest:4  t8
        "lb_bit3_Send_0:                     \n"//------Send 0 : 400ns High, 850ns Low (6,14) 375ns,875ns
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t1
        "nop                                 \n"// L t2
        "nop                                 \n"// L t3
        "nop                                 \n"// L t4
        "nop                                 \n"// L t5
        "nop                                 \n"// L t6
        "nop                                 \n"// L t7
        "nop                                 \n"// L t8
        "nop                                 \n"// L t9
                                                //NextBitTest:4+SP = 5. L t14
//--------------- bit 4 -----------------------------------------
        "lb_start_bit4:                      \n"//
        "LD      A,           (L:LedsArray,X)\n"//1
        "AND     A,             #0x08        \n"//1
        "JREQ    L:lb_bit4_Send_0            \n"//2 jump to Zero, 1 Stay in One + next nop
        "lb_bit4_Send_1:                     \n"
        "nop                                 \n"//1 to have send0 send1 equality
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        "nop                                 \n"// H t7
        "nop                                 \n"// H t8
        "nop                                 \n"// H t9
        "nop                                 \n"// H t10
        "nop                                 \n"// H t11
        "nop                                 \n"// H t12
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t2
        "JRA     L:lb_start_bit5             \n"// L JRA:2 t4 
                                                // L NextBitTest:4  t8
        "lb_bit4_Send_0:                     \n"//------Send 0 : 400ns High, 850ns Low (6,14) 375ns,875ns
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t1
        "nop                                 \n"// L t2
        "nop                                 \n"// L t3
        "nop                                 \n"// L t4
        "nop                                 \n"// L t5
        "nop                                 \n"// L t6
        "nop                                 \n"// L t7
        "nop                                 \n"// L t8
        "nop                                 \n"// L t9
                                                //NextBitTest:4+SP = 5. L t14
//--------------- bit 5 -----------------------------------------
        "lb_start_bit5:                      \n"//
        "LD      A,           (L:LedsArray,X)\n"//1
        "AND     A,             #0x04        \n"//1
        "JREQ    L:lb_bit5_Send_0            \n"//2 jump to Zero, 1 Stay in One + next nop
        "lb_bit5_Send_1:                     \n"
        "nop                                 \n"//1 to have send0 send1 equality
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        "nop                                 \n"// H t7
        "nop                                 \n"// H t8
        "nop                                 \n"// H t9
        "nop                                 \n"// H t10
        "nop                                 \n"// H t11
        "nop                                 \n"// H t12
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t2
        "JRA     L:lb_start_bit6             \n"// L JRA:2 t4 
                                                // L NextBitTest:4  t8
        "lb_bit5_Send_0:                     \n"//------Send 0 : 400ns High, 850ns Low (6,14) 375ns,875ns
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t1
        "nop                                 \n"// L t2
        "nop                                 \n"// L t3
        "nop                                 \n"// L t4
        "nop                                 \n"// L t5
        "nop                                 \n"// L t6
        "nop                                 \n"// L t7
        "nop                                 \n"// L t8
        "nop                                 \n"// L t9
                                                //NextBitTest:4+SP = 5. L t14
//--------------- bit 6 -----------------------------------------
        "lb_start_bit6:                      \n"//
        "LD      A,           (L:LedsArray,X)\n"//1
        "AND     A,             #0x02        \n"//1
        "JREQ    L:lb_bit6_Send_0            \n"//2 jump to Zero, 1 Stay in One + next nop
        "lb_bit6_Send_1:                     \n"
        "nop                                 \n"//1 to have send0 send1 equality
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        "nop                                 \n"// H t7
        "nop                                 \n"// H t8
        "nop                                 \n"// H t9
        "nop                                 \n"// H t10
        "nop                                 \n"// H t11
        "nop                                 \n"// H t12
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t2
        "JRA     L:lb_start_bit7             \n"// L JRA:2 t4 
                                                // L NextBitTest:4  t8
        "lb_bit6_Send_0:                     \n"//------Send 0 : 400ns High, 850ns Low (6,14) 375ns,875ns
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t1
        "nop                                 \n"// L t2
        "nop                                 \n"// L t3
        "nop                                 \n"// L t4
        "nop                                 \n"// L t5
        "nop                                 \n"// L t6
        "nop                                 \n"// L t7
        "nop                                 \n"// L t8
        "nop                                 \n"// L t9
                                                //NextBitTest:4+SP = 5. L t14
//--------------- bit 7 -----------------------------------------
        "lb_start_bit7:                      \n"//
        "LD      A,           (L:LedsArray,X)\n"//1
        "AND     A,             #0x01        \n"//1
        "JREQ    L:lb_bit7_Send_0            \n"//2 jump to Zero, 1 Stay in One + next nop
        "lb_bit7_Send_1:                     \n"
        "nop                                 \n"//1 to have send0 send1 equality
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        "nop                                 \n"// H t7
        "nop                                 \n"// H t8
        "nop                                 \n"// H t9
        "nop                                 \n"// H t10
        "nop                                 \n"// H t11
        "nop                                 \n"// H t12
        RGBLedPin_Set                         // L t1
        "DECW    Y                           \n"//2
        "JREQ    L:lb_exit                   \n"//1 on loop, 2 jmp to exit
        "JP      L:lb_begin_loop             \n"//5
                                                // 
        "lb_bit7_Send_0:                     \n"//------Send 0 : 400ns High, 850ns Low (6,14) 375ns,875ns
        RGBLedPin_ReSet                           // H t1
        "nop                                 \n"// H t2
        "nop                                 \n"// H t3
        "nop                                 \n"// H t4
        "nop                                 \n"// H t5
        "nop                                 \n"// H t6
        RGBLedPin_Set                         // L t1
        "nop                                 \n"// L t1
        "nop                                 \n"// L t2
        "nop                                 \n"// L t3
        "nop                                 \n"// L t4
        "nop                                 \n"// L t5
        "nop                                 \n"// L t6
                                                // L DECW 2, JREQ 1, 2 = 5 =>   t14
//--------------------------------------------------------
//--------------------------------------------------------
        "DECW    Y                           \n"//2
        "JREQ    L:lb_exit                   \n"//1 on loop, 2 jmp to exit
        "JP      L:lb_begin_loop             \n"//5
        "lb_exit:nop");
  
    __set_interrupt_state(int_state);
}
/* 
  rgb_SendColors(RGBColor_t Color):
  ham su dung kieu cau truc (Struct)  de gui 1 mau cu the khi duoc pha
  tu R,G,B (trong project khong su dung led W nhung led W van duoc cau 
  hinh cho truong hop can thiet)*/
void rgb_SendColors(RGBColor_t Color) 
{
  LedsArray[0] = Color.W;
  LedsArray[1] = Color.R;
  LedsArray[2] = Color.G;
  LedsArray[3] = Color.B;
  rgb_SendArray();
  delay_100us();//minimal delay for reset to restart 
}


/*
   delay(unsigned int n): 
   ham tao delay
*/
void delay(unsigned int n)
{
    while (n-- > 0);
}


/*
   rgb_SetColor(unsigned char LedId,unsigned char W, unsigned char R, unsigned char G, unsigned char B):
   ham se gui ra mau  khi pha R,G,B (255^3 mau) (trong project khong su dung led W nhung led W van duoc 
   cau hinh cho truong hop can thiet)
*/
void rgb_SetColor(unsigned char LedId,unsigned char W, unsigned char R, unsigned char G, unsigned char B)
{
  LedsArray[LedId*4] = W;
  LedsArray[LedId*4+1] = R;
  LedsArray[LedId*4+2] = G;
  LedsArray[LedId*4+3] = B;
}

/* 
  rgb_SetColors(RGBColor_t Color):
  ham su dung kieu cau truc (Struct)  de gui 1 mau cu the khi duoc pha
  tu R,G,B (trong project khong su dung led W nhung led W van duoc cau 
  hinh cho truong hop can thiet) khac voi rgb_SendColors thi ham nay gui duoc nhieu led */
void rgb_SetColors(unsigned char LedId,RGBColor_t Color)
{
  LedsArray[LedId*4] = Color.W;
  LedsArray[LedId*4] = Color.R;
  LedsArray[LedId*4+1] = Color.G;
  LedsArray[LedId*4+2] = Color.B;
}
 /*
   RGB_Shift_LED_forward (unsigned char LED_Shift,unsigned char time):
   ham dich led thuan
*/
void RGB_Shift_LED_forward (unsigned char LED_Shift,unsigned char time)
{ 
  foward_cnt++;
    //for(unsigned char i=0;i<LED_Shift;i++)
  if(foward_cnt<LED_Shift)
  {
    for(unsigned char j=0;j<60;j++)
    {
      LedsArray[243-j*4]= LedsArray[239-j*4];
      LedsArray[242-j*4]= LedsArray[238-j*4];
      LedsArray[241-j*4]= LedsArray[237-j*4];
      LedsArray[240-j*4]= LedsArray[236-j*4];
    }
    LedsArray[3] =  LedsArray[243];
    LedsArray[2] =  LedsArray[242];
    LedsArray[1] =  LedsArray[241];
    LedsArray[0] =  LedsArray[240];
    RGB_Show_LED(time); 
  }
  else 
  {
    foward_cnt=0;
    Settup_status=0;
  }
}

 /*
   RGB_Shift_LED_forward (unsigned char LED_Shift,unsigned char time):
   ham dich led nguoc
*/
void RGB_Shift_LED_reverb (unsigned char LED_Shift,unsigned char time)
{
  reverb_cnt++;
  if(reverb_cnt<LED_Shift)
  {
    LEDTemp1 = (RGBColor_t *)(LedsArray);
    LEDTempSave = *LEDTemp1;
    for(unsigned char i = 0; i < 60; i++){
      *LEDTemp1 = *(LEDTemp1+1);
      LEDTemp1++;
    }
    *LEDTemp1 = LEDTempSave;
    RGB_Show_LED(time); 
  }
  else
  {
    reverb_cnt=0;
    Settup_status=0;
  }
}
 /*
   RGB_Shift_LED_forward (unsigned char LED_Shift,unsigned char time):
   ham dich led thuan cua hieu ung 5
*/
void RGB_effect_5_forward (unsigned char LED_Shift,unsigned char time)
{ 
  for(unsigned char i=0;i<LED_Shift;i++)
  {
    for(unsigned char j=0;j<60;j++)
    {
      LedsArray[243-j*4]= LedsArray[239-j*4];
      LedsArray[242-j*4]= LedsArray[238-j*4];
      LedsArray[241-j*4]= LedsArray[237-j*4];
      LedsArray[240-j*4]= LedsArray[236-j*4];
    }
    LedsArray[3] =  LedsArray[243];
    LedsArray[2] =  LedsArray[242];
    LedsArray[1] =  LedsArray[241];
    LedsArray[0] =  LedsArray[240];
    RGB_Show_LED(time);
    if(mode_effect_save!=mode_effect) break;
  }

}
 /*
   RGB_Shift_LED_forward (unsigned char LED_Shift,unsigned char time):
   ham dich led nguoc cua hieu ung 5
*/
void RGB_effect_5_reverb (unsigned char LED_Shift,unsigned char time)
{
  if(mode_effect_save==mode_effect)
  {
    for(unsigned char i=0;i<LED_Shift;i++)
    {
      LEDTemp1 = (RGBColor_t *)(LedsArray);
      LEDTempSave = *LEDTemp1;
      for(unsigned char i = 0; i < 60; i++){
        *LEDTemp1 = *(LEDTemp1+1);
        LEDTemp1++;
      }
      *LEDTemp1 = LEDTempSave;
      RGB_Show_LED(time); 
      if(mode_effect_save!=mode_effect) break;
    }
  }
}
/*
  RGB_Clear_LED ():
  ham co tac dung tat toan bo chuoi RGB
*/

void RGB_Clear_LED ()
{
  for(unsigned char i=0;i<60;i++)
  { 
   rgb_SetColor(i,0,0,0,0);
  }
}
/*
  RGB_Show_LED(unsigned char time): 
  sau khi dat gia tri cua cac led cho mang LedsArray [] 
  ham nay se gui data ra OUTPUT
*/
void RGB_Show_LED(unsigned char time)
{
  while(time--)
  {
    RGB_C1_C2();
    rgb_SendArray();
    delay_100us();
    delay_100us();
    if(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5))
    {
      while(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5));
      mode_effect++;
      
    }
    if(Time_out>=200) break;
  }  
}
/*
  RGB_Show_LED_mode_7(unsigned char time): 
  sau khi dat gia tri cua cac led cho mang LedsArray [] 
  ham nay se gui data cua hieu ung 7 ra OUTPUT
*/
void RGB_Show_LED_mode_7(unsigned char time)
{
  while(time--)
  {
    RGB_C1_C2();
    rgb_SendArray();
    delay_100us();
    delay_100us();
    if(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5))
    {
      while(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5));
      mode_effect=1;
    }
  }  

}
