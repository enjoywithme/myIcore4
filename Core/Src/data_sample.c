#include "data_sample.h"
#include "main.h"
#include "lwip/err.h"
#include "lwip/pbuf.h"
#include <stdio.h>
#include "udp_echoclient.h"

#define SPI_BUFFER_SIZE 	12
#define SPI_BUFFER_N	    60
#define	AD_SYNC_GPIO GPIOD
#define	AD_SYNC_GPIO_PIN	GPIO_PIN_8
#define	SEND_LINES_LIMIT
uint8_t ads1274_irq_disable_counter = 0;

uint8_t ad_start_flag = 1; //AD启动标志
uint8_t ad_start_status = 0;

uint8_t spi_recv_data[SPI_BUFFER_SIZE] = { 0,1,2,3,4,5,6,7,8,9,10,11 }; //接收缓冲
uint8_t spi_send_data[SPI_BUFFER_SIZE] = { 0 };

struct pbuf *pbuf1;
struct pbuf *pbuf2;
struct pbuf *p;
uint8_t spi_ready = 0;

uint8_t buffer_recv_index = 0; //当前接收缓冲指针
uint8_t buffer_send_index = 0; //当前发送缓冲指针
uint8_t buffer_flip = 0; //缓冲指针翻篇
uint8_t buffer_overflow = 0;


static void Fill_pbuf_with_dummy_data(struct pbuf * p);



void ADS1274_Send_Data(void)
{
	if(ad_start_status==0)
		return;

	if(buffer_flip==1)
		{
		//Fill_pbuf_with_dummy_data(pbuf1);
		udp_echoclient_Send(pbuf1);
		}
	else
		{
		//Fill_pbuf_with_dummy_data(pbuf2); //这行非常影响发送速度，但是必须得有，udp_send后pbuf会增加头部信息导致数据变化
		udp_echoclient_Send(pbuf2);
		}

	spi_ready=0;

}


static void Fill_pbuf_with_dummy_data(struct pbuf * p)
{
	uint8_t n;
	for(n=0;n<SPI_BUFFER_N;n++)
		pbuf_take_at(p,spi_recv_data,SPI_BUFFER_SIZE,n * SPI_BUFFER_SIZE);

	p->len = SPI_BUFFER_SIZE * SPI_BUFFER_N;
	p->tot_len = p->len;
}

void ADS1274_Start(void) {

	if(ad_start_status == 1) return;

	buffer_recv_index = 0;
	buffer_send_index = 0;
	buffer_flip = 0;
	buffer_overflow = 0;

	spi_ready = 0;



	if(pbuf1==NULL)
	{
		pbuf1 = pbuf_alloc(PBUF_TRANSPORT,SPI_BUFFER_SIZE * SPI_BUFFER_N, PBUF_POOL);
		if(pbuf1==NULL)
		{
			printf("Failed to allocate pbuf1\r\n");
			goto error_exit;
		}
		Fill_pbuf_with_dummy_data(pbuf1);
		pbuf_ref(pbuf1);
	}



	if(pbuf2==NULL)
	{
		pbuf2 = pbuf_alloc(PBUF_TRANSPORT,SPI_BUFFER_SIZE * SPI_BUFFER_N, PBUF_POOL);
		if(pbuf2==NULL)
		{
			printf("Failed to allocate pbuf1\r\n");
			goto error_exit;
		}
		Fill_pbuf_with_dummy_data(pbuf2);
		pbuf_ref(pbuf2);
	}

	//HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	printf("START\r\n");
	//HAL_GPIO_WritePin(AD_SYNC_GPIO, AD_SYNC_GPIO_PIN, GPIO_PIN_SET);//拉低禁止转换，拉高开始转换
	ad_start_status = 1;
	return;

	error_exit:
		printf("Unable to start.\r\n");
}

static void ADS1274_Stop(void) {

	if(ad_start_status==0) return;

	printf("STOP\r\n");
	ad_start_status = 0;
}

void ADS1274_run(void) {
	if (ad_start_flag == 0)
		ADS1274_Stop();
	else
		ADS1274_Start();
}






void ADS1274_Init(void) {


}

