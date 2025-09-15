/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.c
  * @brief   This file provides code for the configuration
  *          of the SPI instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */
#include "main.h"
#include <stdio.h>

// UDP 
#define UDP_SOCKET 0
#define SOCK_UDPS  0

#define SOCK_DOWN       1
#define SOCK_CAN		2
#define SOCK_VOC		3
#define SOCK_REC		4

//#define PORT_UDPS       6633
#define DEST_IP         "192.168.1.100"
//#define DEST_PORT       6633
#define DEST_PORT	5011

//#define DEST_DOWN_PORT		6637
//#define DEST_DOWN_PORT		6633
//#define DEST_DOWN_PORT		6637
#define DEST_DOWN_PORT		5011

uint8_t GROUP_IP[4] = {234,2,3,4};
uint8_t GROUP2_IP[4] = {234,2,3,5};

uint8_t addrDHAR[6] = {1,0,0x5E,2,3,4};
uint8_t addrDHAR2[6] = {1,0,0x5E,2,3,5};

extern SPI_HandleTypeDef hspi4;


/* USER CODE END 0 */

SPI_HandleTypeDef hspi4;

/* SPI4 init function */
void MX_SPI4_Init(void)
{

  /* USER CODE BEGIN SPI4_Init 0 */

  /* USER CODE END SPI4_Init 0 */

  /* USER CODE BEGIN SPI4_Init 1 */

  /* USER CODE END SPI4_Init 1 */
  hspi4.Instance = SPI4;
  hspi4.Init.Mode = SPI_MODE_MASTER;
  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi4.Init.NSS = SPI_NSS_SOFT;
  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi4.Init.CRCPolynomial = 0x0;
  hspi4.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi4.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi4.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi4.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi4.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi4.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi4.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi4.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi4.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi4.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI4_Init 2 */

  /* USER CODE END SPI4_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(spiHandle->Instance==SPI4)
  {
  /* USER CODE BEGIN SPI4_MspInit 0 */

  /* USER CODE END SPI4_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI4;
    PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* SPI4 clock enable */
    __HAL_RCC_SPI4_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**SPI4 GPIO Configuration
    PE2     ------> SPI4_SCK
    PE5     ------> SPI4_MISO
    PE6     ------> SPI4_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI4_MspInit 1 */

  /* USER CODE END SPI4_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI4)
  {
  /* USER CODE BEGIN SPI4_MspDeInit 0 */

  /* USER CODE END SPI4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI4_CLK_DISABLE();

    /**SPI4 GPIO Configuration
    PE2     ------> SPI4_SCK
    PE5     ------> SPI4_MISO
    PE6     ------> SPI4_MOSI
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_6);

  /* USER CODE BEGIN SPI4_MspDeInit 1 */

  /* USER CODE END SPI4_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

//uint8_t SPIReadWrite(uint8_t data){
//	//wait till FIFO has a free slot
//	while((hspi4.Instance->SR & SPI_FLAG_TXE) != SPI_FLAG_TXE);  //
//
//	// Transmit data by writing to the Data Register (DR)
//	*(__IO uint8_t*)&hspi4.Instance->TXDR=data;
//
//	//now wait till data arrives
//	while((hspi4.Instance->SR & SPI_FLAG_RXNE) != SPI_FLAG_RXNE);
//
//	// Read and return the received data from the Data Register (DR)
//	return(*(__IO uint8_t*)&hspi4.Instance->RXDR);
//}
uint8_t SPIReadWrite(uint8_t data){
    HAL_StatusTypeDef status;
    uint8_t rxByte = 0;

    // HAL_SPI_Transmit: 한 바이트를 보내고
    status = HAL_SPI_Transmit(&hspi4, &data, 1, 10);
    if (status != HAL_OK) {
        // 에러 처리
        return 0; // 또는 에러 코드로 반환
    }

    // HAL_SPI_Receive: 같은 트랜잭션에서 응답 바이트를 받기
    status = HAL_SPI_Receive(&hspi4, &rxByte, 1, 100);
    if (status != HAL_OK) {
        // 에러 처리
        return 0; // 또는 에러 코드로 반환
    }

    return rxByte;
}

void wizchip_select(void){
	HAL_GPIO_WritePin(SPI4_NSS_GPIO_Port, SPI4_NSS_Pin, GPIO_PIN_RESET);
}

void wizchip_deselect(void){
	HAL_GPIO_WritePin(SPI4_NSS_GPIO_Port, SPI4_NSS_Pin, GPIO_PIN_SET);
}

uint8_t wizchip_read(){
	uint8_t rb;
	rb = SPIReadWrite(0x00);
	return rb;
}

void wizchip_write(uint8_t wb){
	SPIReadWrite(wb);
}

void wizchip_readburst(uint8_t* pBuf, uint16_t len){
	for(uint16_t i=0;i<len;i++){
		*pBuf=SPIReadWrite(0x00);
		pBuf++;
	}
}

void wizchip_writeburst(uint8_t* pBuf, uint16_t len){
	for(uint16_t i=0;i<len;i++){
		SPIReadWrite(*pBuf);
		pBuf++;
	}
}

void W5500IOInit(){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOE_CLK_ENABLE();

	GPIO_InitStruct.Pin = SPI4_NSS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(SPI4_NSS_GPIO_Port, &GPIO_InitStruct);

}

void W5500Init(void){
	uint8_t memsize[2][8] = {{2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2}};
//	wizchip_init(txsize, rxsize);

	HAL_GPIO_WritePin(SPI4_NSS_GPIO_Port, SPI4_NSS_Pin, GPIO_PIN_SET); // CS High by default

	HAL_Delay(500);
//	vTaskDelay(pdMS_TO_TICKS(500)); // freeRTOS Delay

	reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
	reg_wizchip_spi_cbfunc(wizchip_read, wizchip_write);
	reg_wizchip_spiburst_cbfunc(wizchip_readburst, wizchip_writeburst);


	// WIZChip Initialize
	if (ctlwizchip(CW_INIT_WIZCHIP, (void*) memsize) == -1){
		printf("WIZCHIP Initialized fail. \r\n");
		while(1);
	}
	printf("WIZCHIP Initialized success. \r\n");

}


void Net_Conf()
{
	uint8_t tmpstr[6];
//	int ret;

	wiz_NetInfo gSetWIZNETINFO = {
		{ 02, 01, 02, 00, 01, 04 },             		// Mac address
//        { 01, 00, 0x5e, 01, 01, IP_ADDR3 },             	// Mac address
		{ 192, 168, 0, 234 },               // IP address
//        { 255, 255, 255, 0},                              // Subnet mask
		{ 255, 255, 255, 0},                                    // Subnet mask
		{ 192, 168, 0, 1},                       // Gateway
		{ 8, 8, 8, 0},                                      // DNS Server
	};

	wiz_NetInfo gWIZNETINFO;

	ctlwizchip(CW_GET_ID,(void*)tmpstr);
	ctlnetwork(CN_SET_NETINFO, (void*) &gSetWIZNETINFO);
	ctlnetwork(CN_GET_NETINFO, (void*)&gWIZNETINFO);
}

void MutiIP_set(void){

	setSn_DIPR(SOCK_UDPS,GROUP2_IP);	//GROUP2_IP : Multicast IP Setting
    setSn_DHAR(SOCK_UDPS,addrDHAR2);
    setSn_DPORT(SOCK_UDPS,DEST_DOWN_PORT);
    socket(SOCK_UDPS,Sn_MR_UDP,DEST_DOWN_PORT,SF_IGMP_VER2 | Sn_MR_MULTI);

//	// F/W download
//	setSn_DIPR(SOCK_DOWN,GROUP2_IP);				// addrDIPR);
//	setSn_DHAR(SOCK_DOWN,addrDHAR2);
//	setSn_DPORT(SOCK_DOWN,DEST_DOWN_PORT);
//	socket(SOCK_DOWN,Sn_MR_UDP,DEST_DOWN_PORT,SF_IGMP_VER2 | Sn_MR_MULTI);
//
//	// 
//	setSn_DIPR(SOCK_VOC,GROUP2_IP);				// addrDIPR);
//	setSn_DHAR(SOCK_VOC,addrDHAR2);
//	setSn_DPORT(SOCK_VOC,DEST_VOC_PORT);
//	socket(SOCK_VOC,Sn_MR_UDP,DEST_VOC_PORT,SF_IGMP_VER2 | Sn_MR_MULTI);
//
//	// V0224 
//	setSn_DIPR(SOCK_REC,GROUP2_IP);				// addrDIPR);
//	setSn_DHAR(SOCK_REC,addrDHAR2);
//	setSn_DPORT(SOCK_REC,DEST_REC_PORT);
//	socket(SOCK_REC,Sn_MR_UDP,DEST_VOC_PORT,SF_IGMP_VER2 | Sn_MR_MULTI);
//
//	// CAN data 
//	setSn_DIPR(SOCK_CAN,GROUP_IP);				// addrDIPR);
//	setSn_DHAR(SOCK_CAN,addrDHAR);
//	setSn_DPORT(SOCK_CAN,DEST_CAN_PORT);
//	socket(SOCK_CAN,Sn_MR_UDP,DEST_CAN_PORT,SF_IGMP_VER2 | Sn_MR_MULTI);

}

void W5500_Send_UDP(void)
{
//    uint8_t dest_ip[4] = {192, 168, 0, 4};  //
    uint8_t dest_ip[4] = {192, 168, 0, 26};  // 
    uint8_t data[] = "Hello! TechWins !!!";    //
    uint16_t len = sizeof(data);

//    socket(UDP_SOCKET, Sn_MR_UDP, DEST_PORT, 0);
	sendto(UDP_SOCKET, data, len, dest_ip, DEST_DOWN_PORT);

}

/* USER CODE END 1 */
