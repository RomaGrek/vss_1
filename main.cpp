#include "hal.h"
bool stopFlag = false; // RESET - нажата
void stopFunction() { // делаем через флаг для того что бы было два нажатия кнопки
    stopFlag = false;
    GPIO_PinState state_nBTN = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
    if (state_nBTN == GPIO_PIN_RESET) {
        stopFlag = true;
    }
    if (stopFlag) {
        while (state_nBTN == GPIO_PIN_RESET) {
            state_nBTN = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
            HAL_Delay(100);
        }
        while (state_nBTN == GPIO_PIN_SET) {
            state_nBTN = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
            HAL_Delay(100);
        }
    }
    stopFlag = false;
}


int umain() {
    int delay = 500;
    int arrPinD[] = {GPIO_PIN_3,
                     GPIO_PIN_4,
                     GPIO_PIN_5,
                     GPIO_PIN_6,
                     GPIO_PIN_8,
                     GPIO_PIN_9,
                     GPIO_PIN_11,
                     GPIO_PIN_12};

    while (1) {
        for (int i = 0; i < 6; ++i) {
            HAL_GPIO_WritePin(GPIOD, arrPinD[i], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i + 1], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i + 2], GPIO_PIN_SET);
            HAL_Delay(delay);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i], GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i + 1], GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i + 2], GPIO_PIN_RESET);
            stopFunction();
        }

        for (int i = 6; i > 2; i--) {
            HAL_GPIO_WritePin(GPIOD, arrPinD[i], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i - 1], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i - 2], GPIO_PIN_SET);
            HAL_Delay(delay);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i], GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i - 1], GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i - 2], GPIO_PIN_RESET);
            stopFunction();
        }
    }

    return 0;
}
