#include <stm32f10x.h>
#include <FreeRTOS.h>
#include <task.h>
#include <SerialPort>
SerialPort1 serial;
class Led {
public:
	Led()
	{
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);
		GPIO_Init(GPIOA, & GPIO_InitStruct);
	}
	void operator=(int8_t value)
	{
		BitAction BitVal;
		uint16_t GPIO_Pin;
		switch(this->n)
		{
		case 0:
			GPIO_Pin = GPIO_Pin_0;
		break;
		case 1:
			GPIO_Pin = GPIO_Pin_1;
		break;
		case 2:
			GPIO_Pin = GPIO_Pin_2;
		break;
		}
		(value>0)?BitVal = Bit_SET:Bit_RESET;
		GPIO_WriteBit(GPIOA, GPIO_Pin, BitVal);
	}
	Led &operator[](int8_t n)
	{
		this->n = n;
		return *this;
	}
protected:
	int8_t n;
};
Led led;
void led_task(void *p)
{
	int i = (int)p;
	i--;
	while(1)
	{
		serial<<"i="<<i<<"\r\n";
		led[i] = 0;
		vTaskDelay(10);
		led[i] = 1;
		vTaskDelay(10);
	}
}
int main()
{
	for(int i=1; i<4; i++)
	{
		xTaskCreate(led_task,
				NULL,
				50,
				(int*)i,
				i,
				NULL);
	}
	vTaskStartScheduler();
}
