/**
  ******************************************************************************
 
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h" // thu vien cua hang ST
#include <RGB_P9414_IC.h>  // thu vien  tu tao gianh cho IC P9414 de dieu khien LED RGB
//#include <iostm8s001j3.h>
/**
  * @addtogroup FLASH_ByteReadWriteOperation
  * @{
  */
//extern void effect_1 () ;
/* Private typedef -----------------------------------------------------------*/
#define ADD_OF_ModeADD 0x4200 // thanh ghi luu DIA CHI CUA THANH GHI LUU HIEU UNG HIEN TAI
//uint8_t Mode;
uint16_t NumRW;  // so lan doc ghi EEPROM va  bien dem 
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;
//extern unsigned char mode_effect;
uint16_t Time_out;
//unsigned char mode_effect_save1;  //  Cac hieu ung cua LED RGB
//extern unsigned char  Flash_Write;
#define INPUT_ZERO_PORT       (GPIOD)                // tan so dien luoi dau vao (2220V/50Hz) la PD6 de dieu khien cac hieu ung
#define INPUT_ZERO_PIN        (GPIO_PIN_6)           // tan so dien luoi dau vao (2220V/50Hz) la PD6 de dieu khien cac hieu ung

#define BUTTON_PORT           (GPIOC)                // nut an de dieu khien cac hieu ung la PC5
#define BUTTON_PIN            (GPIO_PIN_5)           // nut an de dieu khien cac hieu ung la PC5
#define RGB_OUTPUT_PORT       (GPIOA)                // chan dau ra dieu khien cac hieu ung la PA3
#define RGB_OUTPUT_PIN        (GPIO_PIN_3)           // chan dau ra dieu khien cac hieu ung la PA3
BitStatus change_mode;
unsigned char Effect_save;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/ 
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void UpdateMode(void);
void UpdateMode1(void);
void GPIO_Config(void);
//void time_out_mode(unsigned char mode);
static void CLK_Config(void); 
static void TIM2_Config(void);
void LED_MODE (unsigned char Mode);
//volatile unsigned long main_cycle=0;
extern unsigned char mode_effect;
void Zero_cnt();
/* Public functions ----------------------------------------------------------*/
 
//    uint8_t val = 0x00, val_comp = 0x00;
    uint16_t add = 0x00;
void main(void)
{ 

    CLK_Config(); // cau hinh CLOCK 
    TIM2_Config(); // cau hinh timer2 
    GPIO_Config();// cau hinh GPIO

        add = FLASH_ReadByte(ADD_OF_ModeADD) +0x4100;   // doc dia chi luu hieu ung hien tai
    mode_effect = FLASH_ReadByte(add);              // doc ra hieu ung hien tai tu dia chi vua doc
    // Effect_save=mode_effect;
    NumRW = FLASH_ReadByte((add+2)); 
    
    
    
    // check ham main xem khi rut dien ra cam lai thi da chay lai ham main chua
    Time_out=0;
    
    while(Time_out<100)
    {
      //LED_MODE (mode_effect);
      RGB_Clear_LED ();
//      RGB_C1_C2();
      rgb_SendArray();
      delay_100us();
      delay_100us();
      Time_out++;
     // time_out_mode(mode_effect);
    }
    //Time_out=0;
    UpdateMode();
    Effect_save=mode_effect;
    while (1)
    {
//       Time_out++;     
       LED_MODE (mode_effect);
       // effect_10();
      // effect_8(6);
         //effect_();
       if(Effect_save!=mode_effect) 
       {
         FLASH_Unlock(FLASH_MEMTYPE_DATA);                      // mo khoa EEPROM
         FLASH_EraseByte(add);             // xoa so lan ghi xoa EEPROM tai dia chi nay
         FLASH_ProgramByte(add,mode_effect-1);  // ghi gia tri cua hieu ung sau khi cong vao EEPROM   
        //    amount Write
        FLASH_EraseByte((add+2));             // xoa so lan ghi xoa EEPROM tai dia chi nay
        NumRW += 1;                           // tang so lan ghi xoa len 1
        FLASH_ProgramByte( (add+2) ,NumRW); // ghi so lan ghi xoa vao EEPROM
        Effect_save=mode_effect;
       }
    }
}

static void CLK_Config(void)
{
    /* Initialization of the clock */
    /* Clock divider to HSI/1==> 16Mhz */  
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); // clock  divide  1
    
    /* Configure the HSI prescaler to the optimal value */
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); // init high speed internal clock 16MHz
}
static void TIM2_Config(void)
{
  /* 
     + Bo chia tan timer2 la 16MHz/16384 = 976.5625 (~977)  Hz
     + Bhoi gian dem 1 xung la 1/976.5625 = 1.024 ms
     + Chu ki la (4+1)*1.024= 5.12 ms
  */
  /* Time base configuration */
  TIM2_TimeBaseInit(TIM2_PRESCALER_16384,1999);  // cau hinh timer 2 voi cac thong so nhuw tren 
 // TIM5_Ti
  /* Clear TIM4 update flag */
  TIM2_ClearFlag(TIM2_FLAG_UPDATE);  //  xoa co ngat timer 2 sau khi ham ngat duoc goi
  /* Enable update interrupt */
  TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE); // bat ngat timer 2
  
  /* enable interrupts */
  enableInterrupts();// bat ngat timer 2
  /* Enable TIM4 */
  TIM2_Cmd(ENABLE); // bat timer 2
  
  
}
//void time_out_mode(unsigned char Mode)
//{
//  if (Mode==1) Time_out+=140;
//  else if(Mode==3||Mode==2) Time_out+=30;
//  //else if(Mode==6) Time_out+=40;
//  else  Time_out+=20;
//}
void LED_MODE (unsigned char Mode)
{
      if(Mode>5)  Mode = mode_effect=1;  
      switch(Mode)
      {
        case 1:  { effect_1(); break;}
        case 2:  { effect_2(); break;}
        case 3:  { effect_3(); break;}
        case 4:  { effect_4(); break;}
        case 5:  { effect_5(); break;}
        case 6:  { effect_6(); break;}
        case 7:  { effect_7(); break;}
        case 8:  { effect_8(6); break;}
        case 9:  { effect_9(5); break;}
        case 10: { effect_10(); break;}
        case 11: { effect_11(); break;}
      }
}

void UpdateMode1(void) // ham cap nhat hieu ung hien tai vao EEPROM
{
      /* Define FLASH programming time */
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);  //cau hinh EEPROM
      /* Unlock Data memory */
    FLASH_Unlock(FLASH_MEMTYPE_DATA);                      // mo khoa EEPROM
    
    // ADD_OF_ModeADD = 0x4200 
    add = FLASH_ReadByte(ADD_OF_ModeADD) +0x4100;          //doc ra dia chi thanh ghi chua hieu ung hien tai
 
    if(add == 0x4100)                                      // dung cho lan dau khi add  = 0                                    
    {
      FLASH_EraseByte(ADD_OF_ModeADD);                    // xoa du lieu tai dia chi ADD_OF_ModeADD
      FLASH_ProgramByte( ADD_OF_ModeADD , 0x97);          // ghi gia tri 0x97 vao dia chi ADD_OF_ModeADD
      add = FLASH_ReadByte(ADD_OF_ModeADD) +0x4100;       // lay ra dia chi = 0x97+4100 =4197                                                           // chu y: vong if nay chi dung cho lan dau tien khi EEPROM chua duoc ghi lan nao
    }
    
   // mode_effect = FLASH_ReadByte(add);                   // doc EEPROM de lay ra hieu ung da duoc luu
   // NumRW = FLASH_ReadByte((add+2));                     //  doc ra so lan ghi xoa EEPROM tai dia chi nay
//    Program complement value (of previous read byte) at previous address
    FLASH_EraseByte(add);   // xoa dia chi EEPROM
      unsigned char save_mode;
    save_mode=mode_effect-1;      // tang hieu ung 
    if(save_mode > 11)   // neu hieu ung vuot qua 7 thi xoa hieu ung
    {
      save_mode =1;
    }
        if(save_mode < 1)   // neu hieu ung vuot qua 7 thi xoa hieu ung
    {
      save_mode =11;
    }
    //mode_effect_save1=mode_effect;
    FLASH_ProgramByte(add,save_mode);  // ghi gia tri cua hieu ung sau khi cong vao EEPROM
    
 //    amount Write
    FLASH_EraseByte((add+2));             // xoa so lan ghi xoa EEPROM tai dia chi nay
    NumRW += 1;                           // tang so lan ghi xoa len 1
    FLASH_ProgramByte( (add+2) , NumRW); // ghi so lan ghi xoa vao EEPROM
    //mode_effect = FLASH_ReadByte(add);   // doc ra hieu ung vua duoc ghi
    NumRW = FLASH_ReadByte((add+2));   //  doc ra so lan doc ghi 
    if(NumRW >=9000)                   // n
    {
      
        FLASH_EraseByte(ADD_OF_ModeADD);               // ADD of Mode_ADD
        FLASH_ProgramByte( ADD_OF_ModeADD , add-4);    // next 4 byte (2 stack 16 bit)
    }
    FLASH_Lock(FLASH_MEMTYPE_DATA);  // khoa  EEPROM  lai
    
}

void UpdateMode(void) // ham cap nhat hieu ung hien tai vao EEPROM
{
      /* Define FLASH programming time */
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);  //cau hinh EEPROM
      /* Unlock Data memory */
    FLASH_Unlock(FLASH_MEMTYPE_DATA);                      // mo khoa EEPROM
    
    // ADD_OF_ModeADD = 0x4200 
    add = FLASH_ReadByte(ADD_OF_ModeADD) +0x4100;          //doc ra dia chi thanh ghi chua hieu ung hien tai
 
    if(add == 0x4100)                                      // dung cho lan dau khi add  = 0                                    
    {
      FLASH_EraseByte(ADD_OF_ModeADD);                    // xoa du lieu tai dia chi ADD_OF_ModeADD
      FLASH_ProgramByte( ADD_OF_ModeADD , 0x97);          // ghi gia tri 0x97 vao dia chi ADD_OF_ModeADD
      add = FLASH_ReadByte(ADD_OF_ModeADD) +0x4100;       // lay ra dia chi = 0x97+4100 =4197 
                                                          // chu y: vong if nay chi dung cho lan dau tien khi EEPROM chua duoc ghi lan nao
    }
    
    mode_effect = FLASH_ReadByte(add);                   // doc EEPROM de lay ra hieu ung da duoc luu
    NumRW = FLASH_ReadByte((add+2));                     //  doc ra so lan ghi xoa EEPROM tai dia chi nay
//    Program complement value (of previous read byte) at previous address
    FLASH_EraseByte(add);   // xoa dia chi EEPROM
    mode_effect += 1;      // tang hieu ung 
    if(mode_effect > 11)   // neu hieu ung vuot qua 7 thi xoa hieu ung
    {
      mode_effect =1;
    }
    //mode_effect_save1=mode_effect;
    FLASH_ProgramByte( add , mode_effect );  // ghi gia tri cua hieu ung sau khi cong vao EEPROM
    
 //    amount Write
    FLASH_EraseByte((add+2));             // xoa so lan ghi xoa EEPROM tai dia chi nay
    NumRW += 1;                           // tang so lan ghi xoa len 1
    FLASH_ProgramByte( (add+2) , NumRW); // ghi so lan ghi xoa vao EEPROM
    mode_effect = FLASH_ReadByte(add);   // doc ra hieu ung vua duoc ghi
    NumRW = FLASH_ReadByte((add+2));   //  doc ra so lan doc ghi 
    if(NumRW >=9000)                   // n
    {
      
        FLASH_EraseByte(ADD_OF_ModeADD);               // ADD of Mode_ADD
        FLASH_ProgramByte( ADD_OF_ModeADD , add-4);    // next 4 byte (2 stack 16 bit)
    }
    FLASH_Lock(FLASH_MEMTYPE_DATA);  // khoa  EEPROM  lai
    
}

void GPIO_Config(void)
{
  GPIO_DeInit(INPUT_ZERO_PORT);                                  // DeInit  truoc khi khoi tao
  GPIO_Init(INPUT_ZERO_PORT, INPUT_ZERO_PIN, GPIO_MODE_IN_FL_NO_IT);// input zero Pin (PD6) input pull up, no interrupt
  
  GPIO_DeInit(BUTTON_PORT);                                      // DeInit  truoc khi khoi tao
  GPIO_Init(BUTTON_PORT,BUTTON_PIN,GPIO_MODE_IN_PU_NO_IT);       // khoi tao nut an de chuyen doi cac mode sang cua den RGB
  
  GPIO_DeInit(RGB_OUTPUT_PORT);                                  // DeInit  truoc khi khoi tao
  GPIO_Init(RGB_OUTPUT_PORT,RGB_OUTPUT_PIN,GPIO_MODE_OUT_PP_HIGH_FAST); // khoi tao chan RGB data out put de dieu khien chuoi LED RGB
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/