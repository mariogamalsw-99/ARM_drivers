#include "unity.h"
#include "NVIC_driver/nvic.h"
 uint32_t NVIC_ISER_ARR_testVar[8];
 uint32_t NVIC_ISER_ARR_testVar[8];
 uint32_t NVIC_ICER_ARR_testVar[8];
 uint32_t NVIC_ISPR_ARR_testVar[8];
 uint32_t NVIC_ICPR_ARR_testVar[8];
 uint32_t NVIC_IABR_ARR_testVar[8];
 uint32_t NVIC_IPR_ARR_testVar[60];
 uint32_t NVIC_STIR_testVar;
void setUp() {}    // Nothing to do yet
void tearDown() {} // Nothing to do yet

void TEST_NVIC_EnableIRQ_should_Set_IRQ_enable()
{
  NVIC_enuErrCode_t ErrCd = NVIC_EnableIRQ(NVIC_IRQn_WWDG);
  TEST_ASSERT_EQUAL_INT16_MESSAGE(NVIC_OK, ErrCd, "test IRQ0 enable return status");
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(1, NVIC_ISER_ARR_testVar[0], "test IRQ0 enabled");
  ErrCd = NVIC_EnableIRQ(NVIC_IRQn_OTG_FS_WKUP);
  TEST_ASSERT_EQUAL_INT16_MESSAGE(NVIC_OK, ErrCd, "test IRQ42 enable return status");
  TEST_ASSERT_EQUAL_HEX32_MESSAGE((1<<10), NVIC_ISER_ARR_testVar[1], "test IRQ42 enabled");
}
void TEST_NVIC_DisableIRQ_should_Set_IRQ_disable()
{
  NVIC_enuErrCode_t ErrCd = NVIC_DisableIRQ(NVIC_IRQn_WWDG);
  TEST_ASSERT_EQUAL_INT16_MESSAGE(NVIC_OK, ErrCd, "test IRQ0 disable return status");
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(1, NVIC_ICER_ARR_testVar[0], "test IRQ0 disabled");
  ErrCd = NVIC_DisableIRQ(NVIC_IRQn_OTG_FS_WKUP);
  TEST_ASSERT_EQUAL_INT16_MESSAGE(NVIC_OK, ErrCd, "test IRQ42 disable return status");
  TEST_ASSERT_EQUAL_HEX32_MESSAGE((1<<10), NVIC_ICER_ARR_testVar[1], "test IRQ42 disabled");
}
int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(TEST_NVIC_EnableIRQ_should_Set_IRQ_enable);
  RUN_TEST(TEST_NVIC_DisableIRQ_should_Set_IRQ_disable);

  return UNITY_END();
}