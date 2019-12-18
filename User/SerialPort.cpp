#include "SerialPort"
SerialPort& SerialPort::operator<<(const char ch)
{
	this->write(ch);
	return (*this);
}
SerialPort& SerialPort::operator<<(const char *str)
{
	while(*str)
	{
		this->operator<<(*str);
		str++;
	}
	return (*this);
}
SerialPort& SerialPort::operator<<(const int num)
{
	if(num > 0)
	{
		this->operator<<((unsigned long long)num);
	}else if(num == 0)
	{
		this->operator<<('0');
	}else
	{
		this->operator<<('-');
		this->operator<<(-num);
	}
	return (*this);
}
SerialPort& SerialPort::operator<<(const unsigned int num)
{
	const unsigned long long n = num;
	this->operator<<(n);
	return (*this);
}
SerialPort& SerialPort::operator<<(const long num)
{
	if(num > 0)
	{
		this->operator<<((unsigned long long)num);
	}else if(num == 0)
	{
		this->operator<<('0');
	}else
	{
		this->operator<<('-');
		this->operator<<(-num);
	}
	return (*this);
}
SerialPort& SerialPort::operator<<(const unsigned long num)
{
	const unsigned long long n = num;
	this->operator<<(n);
	return (*this);
}
SerialPort& SerialPort::operator<<(const long long num)
{
	if(num > 0)
	{
		this->operator<<((unsigned long long)num);
	}else if(num == 0)
	{
		this->operator<<('0');
	}else
	{
		this->operator<<('-');
		this->operator<<(-num);
	}
	return (*this);
}
SerialPort& SerialPort::operator<<(const unsigned long long num)
{
	unsigned long long n1, n2, i;
	char arr[20]={0};
	n1 = num;
	i = 19;
	if(n1 == 0)
	{
		this->operator<<('0');
	}
	while(n1)
	{
		n2 = n1%10;
		n1 /= 10;
		arr[--i] = n2+'0';
	}
	this->operator<<(arr+i);
	return (*this);
}
SerialPort& SerialPort::operator<<(const float num)
{
	double n = num;
	this->operator<<(n);
	return (*this);
}
SerialPort& SerialPort::operator<<(const double num)
{
	double n, m, zero = 0.000001;
	unsigned long long a;
	char arr[20];
	int i=0;
	n = num;
	if(num < 0)
	{
		this->operator<<('-');
		n = -num;
	}else if(num < zero)
	{
		this->operator<<('0');
	}
	a = (unsigned long long)n;
	m = n - a;
	this->operator<<(a)<<('.');
	if(m > zero)
	{
		while(m > zero)
		{
			m *= 10;
			arr[i] = (int)m;
			m -= arr[i];
			arr[i] += '0';
			i++;
		}
		if(i == 0)
			this->operator<<('0');
		else
		{
			arr[i] = 0;
			this->operator<<(arr);
		}
	}else
	{
		this->operator<<('0');
	}
	return (*this);
}

void SerialPort1::usartConfig()
{
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE);
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate		   = 115200;
	USART_InitStruct.USART_WordLength	   = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits		   = USART_StopBits_1;
	USART_InitStruct.USART_Parity		   = USART_Parity_No;
	USART_InitStruct.USART_Mode		   = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStruct);
	USART_Cmd(USART1, ENABLE);
}
void SerialPort1::pinConfig()
{
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin 	 = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed 	 = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode	 = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_10;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
SerialPort& SerialPort1::write(const char ch)
{
	USART_SendData(USART1, ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
	return (*this);
}
SerialPort1::SerialPort1()
{
	pinConfig();
	usartConfig();
}
