#include <stdio.h>
#include <REG52.H> //keil библиотека
sbit CS_SHDN =P1^0;
sbit DOUT = P1^1;
sbit CLK = P1^2;
unsigned int bRunning;
int стеж
void delay(void)
{
    unsigned char del = 10;
    while(del != 0) del-;
}
float getConv(void) //преобразование аналогового сигнала --> цифровой для передачи данных между stm32 и ev3
{
    int countOfBits = 15;
    unsigned int binResult = 0;
    P1 = 0x0FA;
    CS_SHDN = 1;
    CLK = 1;
    delay();
    CS_SHDN=0;
    do
    {
        /* code */
        CLK=0;
        delay();
        CLK=1;
        binResult = binResult<<1;
        binResult |= DOUT;
        countOfBits--;
    } while (/* condition */ countOfBits>0);
    CS_SHDN=1;
    binResult &=0x0FFF;
    return 4.78/4096 * binResult; //преобразование числа и возвращение
}
void t2isr(void) interrupt 5 using 1
{
    TF2 = 0;
    cnt-;
    if(cnt==0)
    {
        cnt=330;
        bRunning=1;
    }
}
    extern void t2init(void);
    void main(void)
    {
        float total;
        char buf[32];
        int bytes;
        bRunning = 0;
        SCON = 0x50;
        TH1 = 0xF3;
        PCON |= 0x80;
        TMOD |= 0x20;
        TR1 = 1;
        TI = 1;
        cnt = 330;
        t2init();
        while(1)
        {
            if(bRunning==1)
            {
                total = getConv();
                bRunning=0;
             }
        }
    }

}