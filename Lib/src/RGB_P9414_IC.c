

//#include <math.h>
#include <RGB_P9414_IC.h>


//#define RGBLedPin_Set   "BSET    L:0x5000,      #0x03         \n"
//#define RGBLedPin_ReSet   "BRES    L:0x5000,      #0x03         \n"
//#define delay_100us(); delay(115);


//const RGBColor_t RED = {0,255,0,0};
const RGBColor_t VIOLET = {0,200,0,80};
const RGBColor_t VIOLET_WHITE = {255,200,0,80};
const RGBColor_t RED7_BLUE_3 = {0,255,0,110};
#define CURRENT_C1_C2     8
#define NB_LEDS 61                 // so luong led dieu khien la 71 nhung thuc the chi dung 60 LED (5 m)
unsigned char LedsArray[NB_LEDS*4+CURRENT_C1_C2]; // khai bao mang voi so luong byte du lieu can dung de truyen data cho so led = so led x 4 (do 4 kenh mau)



unsigned int nbLedsBytes = NB_LEDS*4+CURRENT_C1_C2;  // so luong byte du lieu cua ledsArray
unsigned int effect1_cnt=0,effect4_cnt=0,foward_cnt=0,reverb_cnt=0,effect_5_cnt=0,effect_6_cnt=0,effect_7_cnt=0;
BitStatus Settup_status,mode_effect_save;
BitStatus Settup_status_11;
BitStatus Settup_status_10;
BitStatus Settup_status_8;
BitStatus Settup_status_3;
BitStatus Settup_status_2;
unsigned char mode_effect=1; 
unsigned char chedo_save; 
//extern unsigned char Time_out;
RGBColor_t      LEDTempSave;    
RGBColor_t      LEDTempSaveOff;
RGBColor_t      *LEDTemp1;
//RGB             *LEDTemp2;
//RGB              LEDTempSave2;


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
    vruc_Count = 0;           // dat lai gia tri dem
    LEDTempBeginPoint = (RGBColor_t *)(LedsArray+CURRENT_C1_C2);  // ep kieu LedArray sang con tro kieu RGBColor_t roi gan cho LEDTempBeginPoint
    LEDTempSave.W = 1;           // tat LED White
    LEDTempSave.R = 200 ; // lay gia tri random cho LED R
    LEDTempSave.G = 200;  // lay gia tri random cho LED G
    LEDTempSave.B = 200;  // lay gia tri random cho LED B
    *LEDTempBeginPoint = LEDTempSave;  // gan gia tri cua LEDTempSave vao con tro LEDTempBeginPoint
  }
  else
  {

    LEDTempBeginPoint = (RGBColor_t *)(LedsArray+CURRENT_C1_C2);  // ep kieu LedArray sang con tro kieu RGBColor_t roi gan cho LEDTempBeginPoint
    *LEDTempBeginPoint = LEDTempSaveOff;            // gan gia tri cua LEDTempSave vao con tro LEDTempBeginPoint
  }
  //if(Time_out>=)
    if(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5))    // doc gia tri nut an  PC5
    {
    while(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5));    //  doi toi khi nha nut an ra
    mode_effect=8;  // hieu ung =1
    }
}

void effect_7 (){
  Settup_status_11;
    effect1_cnt++; // hieu ung 1 counter

      for(int i=0;i<60;i++)
      { 
        if(i%2==0){
      rgb_SetColor(i,0,255,0,0);
        }
        else       rgb_SetColor(i,0,0,0,255);
      } 
              RGB_Show_LED(10); 
}




   
void effect_1 () 
{ 
  
  
    Settup_status_11;
    effect1_cnt++; // hieu ung 1 counter

      for(int i=0;i<60;i++)
      { 
      rgb_SetColor(i,0,0,0,255);
      } 
              RGB_Show_LED(5); 
  
 
}

void effect_2 ()
{ 


    Settup_status_11;
    effect1_cnt++; // hieu ung 1 counter

      for(int i=0;i<60;i++)
      { 
        rgb_SetColor(i,34,255,0,120); // 2 trang/15 do/7 xanh
      } 
      RGB_Show_LED(5); 

  
// Settup_status_11;
//    effect1_cnt++; // hieu ung 1 counter
//
//      for(int i=0;i<60;i++)
//      { 
//        if(i%2==0){
//      rgb_SetColor(i,0,200,0,80);
//        }
//        else       rgb_SetColor(i,255,200,0,80);
//      } 
//              RGB_Show_LED(5); 
}


void effect_3 ()
{
  
  Settup_status_11;
  effect1_cnt++; // hieu ung 1 counter

  for(int i=0;i<60;i++)
  { 
      rgb_SetColor(i,0,255,0,26);  // 10 do/ 1 xanh
  } 
  RGB_Show_LED(5); 
  
  
  
// Settup_status_11;
//    effect1_cnt++; // hieu ung 1 counter
//
//      for(int i=0;i<60;i++)
//      { 
//        if(i%2==0){
//      rgb_SetColor(i,0,255,0,0);
//        }
//        else       rgb_SetColor(i,0,0,0,255);
//      } 
//              RGB_Show_LED(5); 
}

u8     mode_8_cnt=1;
u8 j=0;

void effect_8 (unsigned char space)
{
   if(!Settup_status_8)     // settup du lieu cho lan dau 
  {
    for(unsigned char i=0;i<60;i++)
    {    
      if(i%space==0)  rgb_SetColor(i,1,255,0,0);
      else rgb_SetColor(i,0,0,0,0);
    }
    Settup_status_8=1;
  }
  j++;
  if(j>51)
  {
    j=0;
    mode_8_cnt++;
    if(mode_8_cnt>3) mode_8_cnt=1;
  }
  switch(mode_8_cnt)
  {
    case 1: 
    {
      for(unsigned char i=8;i<248;i++)
      { 
        if(LedsArray[i]==1) 
        {
          LedsArray[i+1] = 255-j*5;
          LedsArray[i+2] =j*5;
          LedsArray[i+3] =0;
        }
        
      }
      break;
    }
    case 2: 
    {
      for(unsigned char i=8;i<248;i++)
      { 
        if(LedsArray[i]==1) 
        {
          LedsArray[i+1] =0;
          LedsArray[i+2] =255-j*5;
          LedsArray[i+3] =j*5;
        }
      }
      break;
    }
    case 3: 
    {
      for(unsigned char i=8;i<248;i++)
      { 
        if(LedsArray[i]==1) 
        {
          LedsArray[i+1] = j*5;
          LedsArray[i+2] =0;
          LedsArray[i+3] =255-j*5;
        }
      }
      break;
    }
  }
  RGB_Shift_LED_forward(60,10);    
}
unsigned int effect8_cnt=0;
void effect_9 (unsigned char time )
{
    effect8_cnt++; // hieu ung 1 counter
     if(effect8_cnt<52) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)  // dat gia tri cua 60 led dau tien cung 1 mau roi gui data ra
      {
        rgb_SetColor(i,0,5*effect8_cnt,0,0);
      }
              RGB_Show_LED(time); 
    }
    else if(effect8_cnt<104)// 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,255-5*(effect8_cnt-52),0,0);
      } 
              RGB_Show_LED(time); 
    }
    else if(effect8_cnt<156)// 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,0,5*(effect8_cnt-104),0);
      } 
              RGB_Show_LED(time); 
    }
    else if(effect8_cnt<208) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,0,255-5*(effect8_cnt-156),0); 
      } 
              RGB_Show_LED(time); 
    }
    else if(effect8_cnt<260) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,0,0,5*(effect8_cnt-208));
      } 
              RGB_Show_LED(time); 
    }
    else if(effect8_cnt<312) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,0,0,255-5*(effect8_cnt-260));
      } 
              RGB_Show_LED(time); 
    }
    else if(effect8_cnt<364) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,5*(effect8_cnt-312),5*(effect8_cnt-312),0); 
      } 
              RGB_Show_LED(time); 
    }
    else if(effect8_cnt<416) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,255-5*(effect8_cnt-364),255-5*(effect8_cnt-364),0); 
      } 
              RGB_Show_LED(time); 
    }
    else if(effect8_cnt<468) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,0,5*(effect8_cnt-416),5*(effect8_cnt-416)); 
      } 
              RGB_Show_LED(time); 
    }
    else if(effect8_cnt<520) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,0,255-5*(effect8_cnt-468),255-5*(effect8_cnt-468)); 
      } 
              RGB_Show_LED(time); 
    }
    else if(effect8_cnt<572) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,5*(effect8_cnt-520),0,5*(effect8_cnt-520)); 
      } 
              RGB_Show_LED(time); 
    }
    else if(effect8_cnt<624) // 52 vong goi ham effect_1 ()
    {
      for(int i=0;i<60;i++)
      {
      rgb_SetColor(i,0,255-5*(effect8_cnt-572),0,255-5*(effect8_cnt-572)); 
      } 
              RGB_Show_LED(time); 
    }else  effect8_cnt=0;
}

void effect_10 ()
{ 
    if(!Settup_status_10)     // settup du lieu cho lan dau 
  {
      for(unsigned char i=0;i<60;i++)
    { 
      if(i%5==0) rgb_SetColor(i,0,0,0,0); 
      else if(i%4==0)    rgb_SetColor(i,0,230,0,0);       // do
      else if(i%3==0)    rgb_SetColor(i,0,0,255,0);    // xanh
      else if(i%2==0)    rgb_SetColor(i,0,200,200,20);    //  vang
      else               rgb_SetColor(i,0,180,180,180);   // trang
    }
    Settup_status_10=1;
  }
    RGB_Shift_LED_forward(60,30);
}
void effect_11 () 
{ 
  Settup_status_10=Settup_status_8=Settup_status_3=Settup_status_2=0;
  if(!Settup_status_11)
  {
    for(unsigned char i=0;i<60;i++)
    {
      if(i<10) 
      {
        rgb_SetColor(i,0,255,0,0);
      }
      else if(i<20) 
      {
        rgb_SetColor(i,0,0,255,0);
      }
      else if(i<30) 
      {
        rgb_SetColor(i,0,0,0,255);
      }
      else if(i<40) 
      {
        rgb_SetColor(i,0,255,0,0);
      }
      else if(i<50) 
      {
        rgb_SetColor(i,0,0,255,0);
      }
      else
      {
        rgb_SetColor(i,0,0,0,255);
      }
    } 
    //move_array(1);
    Settup_status_11=1;
  }
    RGB_Shift_LED_2_side(60,15);
 // RGB_Shift_LED_2_side(60,20);
}
//void effect_12 ()
//{
//
//}
void effect_4 ()
{
      for(int i=0;i<60;i++)
      { 
        rgb_SetColor(i,0,255,0,14); // 19 do/ 1 xanh
      } 
              RGB_Show_LED(5); 
}

 void effect_5 () //  day led
{
      for(int i=0;i<60;i++)
      { 
        rgb_SetColor(i,0,255,0,110);  // 7 do 3 xanh
      } 
              RGB_Show_LED(5); 
}

void effect_6 () 
{
  
   // for(unsigned char i=0;i<60;i++)
    if(effect_6_cnt<60)   // hien thi led duoi dan dan roi tat dan dan
    {
      rgb_SetColor(0,0,0,255,0);
      rgb_SetColor(effect_6_cnt,0,effect_6_cnt*4,255-effect_6_cnt*4,0);
      RGB_Show_LED(3);
    }
    else if(effect_6_cnt<120)
    {
      rgb_SetColor(0,0,0,0,0);
      rgb_SetColor((effect_6_cnt-60),0,0,0,0);
      RGB_Show_LED(10);
    }
    else if(effect_6_cnt<180)
    {
      rgb_SetColor(0,0,255,0,0);
      rgb_SetColor((effect_6_cnt-120),0,255-(effect_6_cnt-120)*4,0,(effect_6_cnt-120)*4);
      RGB_Show_LED(3); 
    }
    else if(effect_6_cnt<240)
    {
        rgb_SetColor(0,0,0,0,0);
        rgb_SetColor((effect_6_cnt-180),0,0,0,0);
        RGB_Show_LED(10);
    }
    else if(effect_6_cnt<300)
    {
      rgb_SetColor(0,0,0,0,255);
      rgb_SetColor((effect_6_cnt-240),0,0,(effect_6_cnt-240)*4,255-(effect_6_cnt-240)*4);
      RGB_Show_LED(3);
    }
    else if(effect_6_cnt<360)
    {
        rgb_SetColor(0,0,0,0,0);
        rgb_SetColor((effect_6_cnt-300),0,0,0,0);
        RGB_Show_LED(10); 
    }
    else effect_6_cnt=0;
      effect_6_cnt++;
    
}
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
//void rgb_SendColors(RGBColor_t Color) 
//{
//  LedsArray[0] = Color.W;
//  LedsArray[1] = Color.R;
//  LedsArray[2] = Color.G;
//  LedsArray[3] = Color.B;
//  rgb_SendArray();
//  delay_100us();//minimal delay for reset to restart 
//}


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
    LedsArray[0]= LedsArray[1]= LedsArray[2]= LedsArray[3]= 0x07;
    LedsArray[4]= LedsArray[5]= LedsArray[6]= LedsArray[7]= 0xf8;
  LedsArray[LedId*4+CURRENT_C1_C2] = W;
  LedsArray[LedId*4+1+CURRENT_C1_C2] = R;
  LedsArray[LedId*4+2+CURRENT_C1_C2] = G;
  LedsArray[LedId*4+3+CURRENT_C1_C2] = B;
}

//void RGB_set_side_and_color(unsigned char LedId, unsigned char R, unsigned char G, unsigned char B,BitStatus side)
//{ 
//  if(side)
//  {
//    LedsArray_forward[LedId*4] = 0;
//    LedsArray_forward[LedId*4+1] = R;
//    LedsArray_forward[LedId*4+2] = G;
//    LedsArray_forward[LedId*4+3] = B;
//  }
//  else 
//  {
//    LedsArray_reverb[LedId*4] = 0;
//    LedsArray_reverb[LedId*4+1] = R;
//    LedsArray_reverb[LedId*4+2] = G;
//    LedsArray_reverb[LedId*4+3] = B;
//  }
//}

/* 
  rgb_SetColors(RGBColor_t Color):
  ham su dung kieu cau truc (Struct)  de gui 1 mau cu the khi duoc pha
  tu R,G,B (trong project khong su dung led W nhung led W van duoc cau 
  hinh cho truong hop can thiet) khac voi rgb_SendColors thi ham nay gui duoc nhieu led */
//void rgb_SetColors(unsigned char LedId,RGBColor_t Color)
//{
//  LedsArray[LedId*4] = Color.W;
//  LedsArray[LedId*4] = Color.R;
//  LedsArray[LedId*4+1] = Color.G;
//  LedsArray[LedId*4+2] = Color.B;
//}
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
      LedsArray[243-j*4+CURRENT_C1_C2]= LedsArray[239-j*4+CURRENT_C1_C2];
      LedsArray[242-j*4+CURRENT_C1_C2]= LedsArray[238-j*4+CURRENT_C1_C2];
      LedsArray[241-j*4+CURRENT_C1_C2]= LedsArray[237-j*4+CURRENT_C1_C2];
      LedsArray[240-j*4+CURRENT_C1_C2]= LedsArray[236-j*4+CURRENT_C1_C2];
    }
    LedsArray[3+CURRENT_C1_C2] =  LedsArray[243+CURRENT_C1_C2];
    LedsArray[2+CURRENT_C1_C2] =  LedsArray[242+CURRENT_C1_C2];
    LedsArray[1+CURRENT_C1_C2] =  LedsArray[241+CURRENT_C1_C2];
    LedsArray[0+CURRENT_C1_C2] =  LedsArray[240+CURRENT_C1_C2];
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
//void RGB_Shift_LED_reverb (unsigned char LED_Shift,unsigned char time)
//{
//  reverb_cnt++;
//  if(reverb_cnt<LED_Shift)
//  {
//    LEDTemp1 = (RGBColor_t *)(LedsArray);
//    LEDTempSave = *LEDTemp1;
//    for(unsigned char i = 0; i < 60; i++){
//      *LEDTemp1 = *(LEDTemp1+1);
//      LEDTemp1++;
//    }
//    *LEDTemp1 = LEDTempSave;
//    RGB_Show_LED(time); 
//  }
//  else
//  {
//    reverb_cnt=0;
//    Settup_status=0;
//  }
//}

 // ham dich led 2 chieu 


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
      LedsArray[243-j*4+CURRENT_C1_C2]= LedsArray[239-j*4+CURRENT_C1_C2];
      LedsArray[242-j*4+CURRENT_C1_C2]= LedsArray[238-j*4+CURRENT_C1_C2];
      LedsArray[241-j*4+CURRENT_C1_C2]= LedsArray[237-j*4+CURRENT_C1_C2];
      LedsArray[240-j*4+CURRENT_C1_C2]= LedsArray[236-j*4+CURRENT_C1_C2];
    }
    LedsArray[3+CURRENT_C1_C2] =  LedsArray[243+CURRENT_C1_C2];
    LedsArray[2+CURRENT_C1_C2] =  LedsArray[242+CURRENT_C1_C2];
    LedsArray[1+CURRENT_C1_C2] =  LedsArray[241+CURRENT_C1_C2];
    LedsArray[0+CURRENT_C1_C2] =  LedsArray[240+CURRENT_C1_C2];
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
      
      LEDTemp1 = (RGBColor_t *)(LedsArray+8);
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
//    RGB_C1_C2();
    rgb_SendArray();
    delay_100us();
    delay_100us();
    if(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5))
    {
      while(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5));
      mode_effect++;
      break;
      
    }
    //if(Time_out>=200) break;
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
    //RGB_C1_C2();
    rgb_SendArray();
    delay_100us();
    delay_100us();
    if(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5))
    {
      while(!GPIO_ReadInputPin(GPIOC,GPIO_PIN_5));
      mode_effect=8;
      break;
    }
  }  

}

void RGB_Shift_LED_2_side (unsigned char LED_Shift,unsigned char time)
{
  for(unsigned char i=0;i<LED_Shift;i++)
  {
    LedsArray[242+CURRENT_C1_C2] = LedsArray[2+CURRENT_C1_C2];
    for(unsigned char j=0;j<60;j++)
    {
      //LedsArray[243-j*4+CURRENT_C1_C2]= LedsArray[239-j*4+CURRENT_C1_C2];
     // LedsArray[242-j*4+CURRENT_C1_C2]= LedsArray[238-j*4+CURRENT_C1_C2];
      LedsArray[j*4+2+CURRENT_C1_C2] =  LedsArray[j*4+6+CURRENT_C1_C2];
      LedsArray[241-j*4+CURRENT_C1_C2]= LedsArray[237-j*4+CURRENT_C1_C2];
     // LedsArray[240-j*4+CURRENT_C1_C2]= LedsArray[236-j*4+CURRENT_C1_C2];
    }
    //LedsArray[3+CURRENT_C1_C2] =  LedsArray[243+CURRENT_C1_C2];
    // LedsArray[j*4+2+CURRENT_C1_C2] =  LedsArray[j*4+6+CURRENT_C1_C2];
    LedsArray[1+CURRENT_C1_C2] =  LedsArray[241+CURRENT_C1_C2];
    // LedsArray[0+CURRENT_C1_C2] =  LedsArray[240+CURRENT_C1_C2];
    RGB_Show_LED(time);
    if(mode_effect_save!=mode_effect) break;
  }
}
