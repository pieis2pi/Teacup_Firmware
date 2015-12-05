
/** \file
  \brief Analog subsystem, ARM specific part.

*/

#if defined TEACUP_C_INCLUDE && defined __ARM_STM32F411__

#include "cmsis-stm32f4xx.h"
#include "arduino.h"
#include "temp.h"

// DMA ADC-buffer
volatile uint32_t analog_buffer[NUM_TEMP_SENSORS];

// privat functions
void init_analog(void);
void init_analog_pins(void);
void dma_init(void); // main init of dma, used in analog_init()
void init_dma(DMA_Stream_TypeDef *DMA_Sx);
void deinit_dma(DMA_Stream_TypeDef *DMA_Sx);

/** Inititalise the analog subsystem.

  Initialise the ADC and start hardware scan loop for all used sensors.
*/
void analog_init() {

  if (NUM_TEMP_SENSORS) {                       // At least one channel in use.

    init_analog_pins();
    init_analog();
    dma_init();

  }
}

void init_analog_pins() {
  PIOC_2_PORT->MODER |= (GPIO_MODER_MODER0 << ((PIOC_2_PIN) << 1));         // analog mode
  PIOC_2_PORT->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((PIOC_2_PIN) << 1));        // no pullup
  PIOC_2_PORT->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR0 << ((PIOC_2_PIN) << 1));  // high speed
}

void init_analog() {

  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; //Enable clock

  /* Set ADC parameters */
  /* Set the ADC clock prescaler */
  /*  Datasheet says max. ADC-clock is 36MHz
      We don't need that much. 12MHz is slowest possible.
  */
  ADC->CCR |= (ADC_CCR_ADCPRE);
  
  /* Set ADC scan mode */
  // reset scan mode
  // reset resolution includes 12bit
  // discontinous mode disabled
  ADC1->CR1 &= ~( ADC_CR1_SCAN | 
                  ADC_CR1_RES |
                  ADC_CR1_DISCEN);
    
  /* Set ADC resolution */
  // resolution 12bit
  //ADC1->CR1 |=  ADC_CR1_xxx;
  
  /* Set ADC data alignment */
  // reset = right align
  // reset external trigger
  //
  // disable continous conversion mode
  // disable ADC DMA continuous request
  // disable ADC end of conversion selection
  ADC1->CR2 &= ~( ADC_CR2_ALIGN |
                  ADC_CR2_EXTSEL |
                  ADC_CR2_EXTEN |
                  ADC_CR2_CONT |
                  ADC_CR2_DDS |
                  ADC_CR2_EOCS);
  
  /* Set ADC number of conversion */
  // 1 conversion
  // ((NUM_TEMP_SENSORS) - 1) << 20
  ADC1->SQR1 &= ~(ADC_SQR1_L);

  // for loop over each channel (0..15) for sequence
  ADC1->SQR3 = PIOC_2_ADC << 0;
  // for PIO ## ADC >= 10 SRPR1 and ADC -10, else SMPR 2
  ADC1->SMPR1 = ADC_SMPR1_SMP10_1 << (4 << (PIOC_2_ADC - 10)); // 28 cycles

}

/** Init the DMA for ADC
*/

void dma_init() {
  
  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN; // Enable clock

  /**
    We have two DMA streams for ADC1. (DMA2_Stream0 and DMA2_Stream4)
    We take DMA2 Stream4.
    See reference manual 9.3.3 channel selection (p. 166)
  */
  // Disable DMA-Stream
  DMA2_Stream4->CR &= ~DMA_SxCR_EN;
  
  deinit_dma(DMA2_Stream4);
  init_dma(DMA2_Stream4);

  // Enable DMA-Stream
  DMA2_Stream4->CR |= DMA_SxCR_EN;

}

void init_dma(DMA_Stream_TypeDef *DMA_Sx) {
  
  uint32_t tmp = 0;

  /* Get the CR register value */
  tmp = DMA_Sx->CR;

  /* Clear CHSEL, MBURST, PBURST, PL, MSIZE, PSIZE, MINC, PINC, CIRC, DIR, CT and DBM bits */
  tmp &= ((uint32_t)~(DMA_SxCR_CHSEL | DMA_SxCR_MBURST | DMA_SxCR_PBURST | \
                      DMA_SxCR_PL    | DMA_SxCR_MSIZE  | DMA_SxCR_PSIZE  | \
                      DMA_SxCR_MINC  | DMA_SxCR_PINC   | DMA_SxCR_CIRC   | \
                      DMA_SxCR_DIR   | DMA_SxCR_CT     | DMA_SxCR_DBM));

  /* Prepare the DMA Stream configuration 
    - CHSEL = Channel 0             = 0x00
    - DIR   = Periphal to Memory    = 0x00
    - PINC  = fixed address pointer = 0x00
    - MINC  = fixed address pointer = 0x00
    - PSIZE = periphal size word    = DMA_SxCR_PSIZE_1
    - MSIZE = memory size word      = DMA_SxCR_MSIZE_1
    - CIRC  = circular mode enabled = DMA_SxCR_CIRC
    - PL    = priority high         = DMA_SxCR_PL
  */
  tmp |=  0x00 | 0x00 | 0x00 | 0x00 |
          DMA_SxCR_PSIZE_1 | DMA_SxCR_MSIZE_1 |
          DMA_SxCR_CIRC | DMA_SxCR_PL_1;
  // FIFO disabled...

  /* Write CR register values */
  DMA_Sx->CR = tmp;

  /* Reset value of FIFO control register 
    - FIFO error interrupt disabled
    - FIFO status empty
    - Direct mode disabled
    - 1/2 full FIFO
  */
  DMA_Sx->FCR = 0x00000021;

}

void deinit_dma(DMA_Stream_TypeDef *DMA_Sx) {

  // Deinit DMA
  DMA_Sx->CR   = 0;   /* Reset DMA Streamx control register */
  DMA_Sx->NDTR = 0;   /* Reset DMA Streamx number of data to transfer register */
  DMA_Sx->PAR  = 0;   /* Reset DMA Streamx peripheral address register */
  DMA_Sx->M0AR = 0;   /* Reset DMA Streamx memory 0 address register */
  DMA_Sx->M1AR = 0;   /* Reset DMA Streamx memory 1 address register */
  DMA_Sx->FCR  = (uint32_t)0x00000021;   /* Reset DMA Streamx FIFO control register */
  
}

/** Read analog value.

  \param channel Channel to be read.

  \return Analog reading, 10-bit right aligned.

  STM32F4 goes a different way. The ADC don't have a register for 
  each channel. We need a DMA soon to convert and hold all datas.
*/
//#include "delay.h"
uint16_t analog_read(uint8_t index) {
  // 11.8.2 Managing a sequence of conversions without using the DMA
  // page 220

  ADC1->SMPR1 &= ~(ADC_SMPR1_SMP12);  // PIOC_2_ADC 12
                                      // 3 CYCLES

  ADC1->SQR3 &= ~(ADC_SQR3_SQ1);      // rank 1
  ADC1->SQR3 |= PIOC_2_ADC;           // << (5 * (rank - 1))

  ADC1->CR2 |=  ADC_CR2_ADON          // A/D Converter ON / OFF
              | ADC_CR2_SWSTART;      // Start Conversion of regular channels

  while (!(ADC1->SR & ADC_SR_EOC) == ADC_SR_EOC);

  return ADC1->DR;
}

#endif /* defined TEACUP_C_INCLUDE && defined __ARMEL__ */
