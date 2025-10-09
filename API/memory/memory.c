/*
 * memory.c
 *
 *  Created on: 7 de out. de 2025
 *      Author: joao.victor
 */

#include "nvm3.h"
#include "nvm3_hal_flash.h"
#include "nvm3_default.h"

// Buffer for reading from NVM3
static char buffer[100];

// Use the default nvm3 handle from nvm3_default.h
#define NVM3_DEFAULT_HANDLE nvm3_defaultHandle

void memory_write(uint32_t key, uint8_t *value, uint8_t len){
  sl_status_t status;

  status = nvm3_writeData(nvm3_defaultHandle, key, value, len);

  if (status != ECODE_NVM3_OK) {
      printf("Erro");
      return;
  }
}

void memory_read(uint32_t key, void *buffer){
  uint32_t type;
  size_t len;
  sl_status_t status;

  if (key > 10) {
      return;
  }

  status = nvm3_getObjectInfo(nvm3_defaultHandle, key, &type, &len);
  if (status != NVM3_OBJECTTYPE_DATA || type != NVM3_OBJECTTYPE_DATA) {
      printf("Key does not contain data object\r\n");
      return;
  }

  status = nvm3_readData(nvm3_defaultHandle, key, buffer, len);
  if (ECODE_NVM3_OK == status) {
      printf("Read data from key %lu:\r\n", key);
      printf("%s\r\n", buffer);
  } else {
      printf("Error reading data from key %lu\r\n", key);
  }
}

void memory_erase(uint32_t key){
  if (key > 10) {
      return;
  }

  if (ECODE_NVM3_OK == nvm3_deleteObject(nvm3_defaultHandle, key)) {
      printf("Deleted data at key %lu\r\n", key);
  } else {
      printf("Error deleting key\r\n");
  }
}

