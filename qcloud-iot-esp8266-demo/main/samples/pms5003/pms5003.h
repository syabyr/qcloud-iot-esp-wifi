#ifndef __PMS5003_H__
#define __PMS5003_H__


#define BUF_SIZE (256)

void pms5003_init();
int get_data(uint8_t *rdata,int nLen);

#endif