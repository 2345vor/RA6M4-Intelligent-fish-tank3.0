/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-25     Asus       the first version
 */
#ifndef _BMP180_SAMPLE_H_
#define _BMP180_SAMPLE_H_

void read_baro_entry(void);
unsigned char *bmp_read(void);
int rt_hw_bmp180_port(void);

#endif /* PACKAGES_BMP180_LATEST_BMP180_SAMPLE_H_ */
