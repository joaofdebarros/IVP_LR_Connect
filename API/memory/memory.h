/*
 * memory.h
 *
 *  Created on: 7 de out. de 2025
 *      Author: joao.victor
 */

#ifndef API_MEMORY_MEMORY_H_
#define API_MEMORY_MEMORY_H_

#define STATUSBYTE_MEMORY_KEY     0
#define SENSIBILITY_MEMORY_KEY    1
#define TXPOWER_MEMORY_KEY        2
#define STATUSOP_MEMORY_KEY       3
#define STATUSCENTRAL_MEMORY_KEY  10
#define ID_PARTITION_MEMORY_KEY   5

void memory_write(uint32_t key, uint8_t *value, uint8_t len);
void memory_read(uint32_t key, void *buffer);
void memory_erase(uint32_t key);

#endif /* API_MEMORY_MEMORY_H_ */
