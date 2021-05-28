#include "hal.h"
bool stopFlag = false; // RESET - нажата

/* анимация */
void typeOne() {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
}

/* остановка анимации */
void typeTwo() {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
}

/* режимы sw переключателей*/
void typeThree() {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
}

void stopFunction() { // делаем через флаг для того что бы было два нажатия кнопки
    stopFlag = false;
    GPIO_PinState state_nBTN = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
    if (state_nBTN == GPIO_PIN_RESET) {
        stopFlag = true;
    }
    if (stopFlag) {
        typeTwo();
        while (state_nBTN == GPIO_PIN_RESET) {
            state_nBTN = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
            HAL_Delay(100);
        }
        while (state_nBTN == GPIO_PIN_SET) {
            state_nBTN = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
            HAL_Delay(100);
        }
    }
    typeOne();
    stopFlag = false;
}



bool checkNumber0x9() {
    GPIO_PinState state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);
    GPIO_PinState state2 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8);
    GPIO_PinState state3 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_10);
    GPIO_PinState state4 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
    if (state1 == GPIO_PIN_SET && state2 == GPIO_PIN_RESET && state3 == GPIO_PIN_RESET && state4 == GPIO_PIN_SET) {
        return true;
    }
    return false;
}


void animationFunction(int arrPinD[], int arrPinE[], int delay) {
    bool flag = false; // если тру то выходим и цикла
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
            if (!checkNumber0x9()) {
                flag = true;
                break;
            }
        }
        if (flag) { break; }

        for (int i = 6; i > 2; i--) {
            HAL_GPIO_WritePin(GPIOD, arrPinD[i], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i - 1], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i - 2], GPIO_PIN_SET);
            HAL_Delay(delay);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i], GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i - 1], GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i - 2], GPIO_PIN_RESET);
            stopFunction();
            if (!checkNumber0x9()) {
                flag = true;
                break;
            }
        }
        if (flag) { break; }
    }
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

    int arrPinE[] = {GPIO_PIN_4,
                     GPIO_PIN_8,
                     GPIO_PIN_10,
                     GPIO_PIN_12};

    while (1) {
        typeThree();
        for (int i = 0; i < 4; ++i) {
            GPIO_PinState stateE = HAL_GPIO_ReadPin(GPIOE, arrPinE[i]);
            HAL_GPIO_WritePin(GPIOD, arrPinD[i], stateE);
        }
        if(checkNumber0x9()) {
            typeOne();
            animationFunction(arrPinD, arrPinE, delay);
        }

    }

    return 0;
}
