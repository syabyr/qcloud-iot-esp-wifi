

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//#include "qcloud_iot_export.h"
#include "qcloud_iot_export_log.h"

#include "driver/uart.h"
#include "esp_base64.h"

#include "pms5003.h"

uint8_t *data=NULL;

void uart0_rx_intr_handler(void *para)
{
	Log_i("--------onrecv-------");
}

void pms5003_init()
{
	data = (uint8_t *) malloc(BUF_SIZE);
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL);

    
    uart_intr_config_t uart_intr;
    uart_intr.intr_enable_mask = UART_FRAME_ERR | UART_BUFFER_FULL;
    uart_intr.rxfifo_full_thresh = 10;  //FIFO 深度
    uart_intr.rx_timeout_thresh = 10;
    //uart_intr_config(UART_NUM_0, &uart_intr);
    //uart_isr_register(UART_NUM_0,uart0_rx_intr_handler, NULL);

    //uart_enable_rx_intr(UART_NUM_0);
    
}

int get_data(uint8_t *rdata,int nLen)
{
	    int len = uart_read_bytes(UART_NUM_0, data, BUF_SIZE, 20 / portTICK_RATE_MS);
        // Write data back to the UART
        if(32 ==len)
        {
        	//Log_i("read byte:%d:%s",len,data);

        	int nFinalLen = esp_base64_encode((const void *)data, len, rdata,nLen);
        	if(nFinalLen >=nLen)
        	{
        		Log_i("error base64");
        		return 0;
        	}

        	return nFinalLen;
        }
        return 0;
        //uart_write_bytes(UART_NUM_0, (const char *) data, len);

        
}