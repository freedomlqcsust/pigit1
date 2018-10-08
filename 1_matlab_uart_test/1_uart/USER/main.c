#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"

#define AD_Start_flag 	0x0001
#define uart_send_flag	0x0002


uint16_t system_sta;
//ALIENTEK 探索者STM32F407开发板 实验4
//串口通信实验 -库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司
//作者：正点原子 @ALIENTEK
__IO uint16_t a[4096];

int main(void)
{

//	u8 t;
//	u8 len;
	u16 i = 0;
	u16 times = 0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置系统中断优先级分组2
	delay_init(168);																//延时初始化
	uart_init(115200);															//串口初始化波特率为115200
	LED_Init();		  																//初始化与LED连接的硬件接口
	printf("\r\n串口测试\r\n");
	while (1)
	{
		if (USART_RX_STA & 0x8000)
		{
			USART_RX_STA = 0;
//			printf("\r\n接收到正确的命令\r\n");
			LED1 = ~LED1;
			system_sta |= AD_Start_flag;
		}
		else if (system_sta & AD_Start_flag)
		{
			system_sta &= ~AD_Start_flag;
			for (i = 0; i < 4096; i++)
			{
				a[i] = i;
			}
			system_sta |= uart_send_flag;
		}
		else if (system_sta & uart_send_flag)
		{
			system_sta &= ~uart_send_flag;
			for (i = 0; i < 4096; i++)
			{
				USART_SendData(UART4, a[i]);
				while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
				USART_SendData(UART4, a[i]>>8);
				while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
			}
		}
		else
		{
			times++;
			if (times % 30 == 0)
				LED0 = !LED0; //闪烁LED,提示系统正在运行.
			delay_ms(10);
		}
	}
}

