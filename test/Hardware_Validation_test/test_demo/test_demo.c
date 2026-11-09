   #include "unity.h"
        //TODO::include your headers here

        void setUp() {}    // Nothing to do yet
        void tearDown() {} // Nothing to do yet
        //TODO:: add function for each test you want to add ex: 
        /*
            void Test_GPIO_Enable()
            {...}
            void Test_GPIO_Read()
            {...}
            void Test_GPIO_Write()
            {...}
        */
        void Test_Demo()
        {
            /*TODO:: call your function you want to test then use test_assert to tes teh return or result of your functiosn
            */
        TEST_ASSERT_EQUAL_MESSAGE(1,1, "Demo test");
        }
        int main(void)
        {
        UNITY_BEGIN();
        //TODO:: call run test on test functions you added ex: 
        /*
            RUN_TEST(Test_GPIO_Enable);
            RUN_TEST(Test_GPIO_Read);
            RUN_TEST(Test_GPIO_Write);
        */
        RUN_TEST(Test_Demo);
        
        return UNITY_END();
        }