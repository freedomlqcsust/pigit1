#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"

#define AD_Start_flag 	0x0001
#define uart_send_flag	0x0002


uint16_t system_sta;
//ALIENTEK ̽����STM32F407������ ʵ��4
//����ͨ��ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾
//���ߣ�����ԭ�� @ALIENTEK
__IO uint16_t a[4096];

int main(void)
{

//	u8 t;
//	u8 len;
	u16 i = 0;
	u16 times = 0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����ϵͳ�ж����ȼ�����2
	delay_init(168);																//��ʱ��ʼ��
	uart_init(115200);															//���ڳ�ʼ��������Ϊ115200
	LED_Init();		  																//��ʼ����LED���ӵ�Ӳ���ӿ�
	printf("\r\n���ڲ���\r\n");
	while (1)
	{
		if (USART_RX_STA & 0x8000)
		{
			USART_RX_STA = 0;
//			printf("\r\n���յ���ȷ������\r\n");
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
				LED0 = !LED0; //��˸LED,��ʾϵͳ��������.
			delay_ms(10);
		}
	}
}

