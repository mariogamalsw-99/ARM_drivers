# Steps to add Unity to project
1. from paltformio interface in VScode open platforms serch for native and install it.
1. in platformio.ini add lines :
    ```
        [env:my_native_env]
        platform =native 
        test_framework = unity
        test_filter = native_pc*  ;here is filter for the paths to test files
        build_flags = -I "C:/Users/EVO_TECH/Desktop/repos/ARM_drivers/include"
                -D PC_UNIT_TEST ;To add the #define when run UNIT test on PC
    ```
1. add test file in folder *"test/"* __the name of folder contains your test suite _must_ start with "test\_"__ :    
    native_pc_test/test_GPIO.c

    ```C
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
    ```
1. in folder "include/" add  file unity_config.h with code:
  ```C
        #ifndef UNITY_CONFIG_H
        #define UNITY_CONFIG_H

        // Leave empty

        #endif

  ```    
1. from platformIO downbar **beside build and debug icon** choose the new env: my_native_env
1. from platformIO downbar **beside build and debug icon** click on test

     #### You should see soemething like this  
        ```
        Processing native_pc_test/test_GPIO in my_native_env environment
        ---------------------------------------------------------------------------------------------------------------------------
        Building...
        Testing...
        test\native_pc_test/test_GPIO.c:30: Test_Demo       [PASSED]
        ----------------------- my_native_env:Hardware_Validation_test/test_demo [PASSED] Took 2.68 seconds -----------------------

        ========================================================= SUMMARY =========================================================
        Environment    Test                                Status    Duration
        -------------  ----------------------------------  --------  ------------
        my_native_env  Hardware_Validation_test/test_demo  PASSED    00:00:02.677
        ======================================== 1 test cases: 1 succeeded in 00:00:02.677 ========================================
        *  Terminal will be reused by tasks, press any key to close it. 


        ```
