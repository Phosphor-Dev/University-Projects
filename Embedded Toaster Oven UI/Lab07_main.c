// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
//CSE13E Support Library
#include "Buttons.h"
#include "BOARD.h"
#include "Oled.h"
#include "Leds.h"
#include "Buttons.h"
// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>



// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)
#define BAKE 0
#define TOAST 1
#define BROIL 2
#define TIME 3
#define TEMP 4
#define LONG_PRESS 2
// **** Set any local typedefs here ****

typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING, COOKING_DONE
} OvenState;

typedef struct {
    OvenState state;
    //add more members to this struct
    int timeRemaining;
    int cookTime;
    int temp;
    int buttonPressLength3;
    int buttonPressLength4;
    int cookMode;
    int settingSelect;
} OvenData;

// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int clockTime;
};

// **** Define any module-level, global, or external variables here ****
OvenData Oven = {.state = SETUP, .timeRemaining = 0, .cookTime = 0, .temp = 300,
    .buttonPressLength3 = 0, .buttonPressLength4 = 0, .cookMode = BAKE,
    .settingSelect = TIME};

struct Timer ADC = {.event = FALSE, .clockTime = 0};
struct Timer Button = {.event = FALSE, .clockTime = 0};
struct Timer Timer = {.event = FALSE, .clockTime = 0};
struct Timer invTimer = {.event = FALSE, .clockTime = 0};

static int globalTimer = 0;
static uint32_t ADCpercent;
static uint8_t buttonsPressed;
static uint8_t led;
static int ledTime = 0;
static int ledTimeCounter = 0;
static int oledInvert = -1;


// **** Put any helper functions here ****

/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData) {
    OledClear(0);
    //update OLED here
    char initState[80], setting[10], clock[10], temp[10], timeCarrot[10] = ">",
            tempCarrot[10] = "", top[10], bottom[10];
    int minutes = 0, seconds = 0;

    if (Oven.state == COOKING) {
        minutes = Oven.timeRemaining / 60;
        seconds = Oven.timeRemaining - (minutes * 60);
        sprintf(clock, "%u:%.2u", minutes, seconds);
    } else {
        minutes = Oven.cookTime / 60;
        seconds = Oven.cookTime - (minutes * 60);
        sprintf(clock, "%u:%.2u", minutes, seconds);
    }

    sprintf(temp, "%u", Oven.temp);

    if ((Oven.state == COOKING) || (Oven.state == COOKING_DONE)) {
        sprintf(top, "%s%s%s%s%s", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON,
                OVEN_TOP_ON, OVEN_TOP_ON);
        sprintf(bottom, "%s%s%s%s%s", OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON,
                OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);

    } else {
        sprintf(top, "%s%s%s%s%s", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF,
                OVEN_TOP_OFF, OVEN_TOP_OFF);
        sprintf(bottom, "%s%s%s%s%s", OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF,
                OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
    }



    if (ovenData.cookMode == BAKE) {
        strcpy(setting, "BAKE");

        if ((Oven.state == COOKING) || (Oven.state == COOKING_DONE)) {
            sprintf(initState,
                    "|%s|  Mode: %s\n"
                    "|     |  Time: %s\n"
                    "|-----|  Temp: %s%s\n"
                    "|%s|",
                    top, setting,
                    clock, temp,
                    DEGREE_SYMBOL, bottom);
        } else if (ovenData.settingSelect == TIME) {
            sprintf(initState,
                    "|%s|  Mode: %s\n"
                    "|     | >Time: %s\n"
                    "|-----|  Temp: %s%s\n"
                    "|%s|",
                    top, setting,
                    clock, temp,
                    DEGREE_SYMBOL, bottom);
        } else if (ovenData.settingSelect == TEMP) {
            sprintf(initState,
                    "|%s|  Mode: %s\n"
                    "|     |  Time: %s\n"
                    "|-----| >Temp: %s%s\n"
                    "|%s|",
                    top, setting,
                    clock, temp,
                    DEGREE_SYMBOL, bottom);
        }
    } else if (ovenData.cookMode == TOAST) {
        strcpy(setting, "TOAST");
        sprintf(initState,
                "|%s|  Mode: %s\n"
                "|     |  Time: %s\n"
                "|-----|\n"
                "|%s|",
                top, setting,
                clock, bottom);

    } else if (ovenData.cookMode == BROIL) {
        Oven.temp = 500;
        strcpy(setting, "BROIL");
        sprintf(initState,
                "|%s|  Mode: %s\n"
                "|     |  Time: %s\n"
                "|-----|  Temp: 500%s\n"
                "|%s|",
                top, setting,
                clock, DEGREE_SYMBOL,
                bottom);

    }

    OledDrawString(initState);
    OledUpdate();
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void) {
    switch (Oven.state) {
        case SETUP:
            if (Oven.settingSelect == TIME) {
                ADCpercent = ((uint32_t) AdcRead() * 1000) / 1023;
                ADCpercent = (((ADCpercent * 255) / 1000) + 1);
                Oven.cookTime = ADCpercent;
            }
            if (Oven.settingSelect == TEMP) {
                ADCpercent = ((uint32_t) AdcRead() * 1000) / 1023;
                Oven.temp = (((ADCpercent * 255) / 1000) + 300);
            }
            updateOvenOLED(Oven);
            if (buttonsPressed & BUTTON_EVENT_3DOWN) {
                Oven.buttonPressLength3 = globalTimer;
                //printf("Pressed Time: %d\n", globalTimer);
                Oven.state = SELECTOR_CHANGE_PENDING;
            }

            if (buttonsPressed & BUTTON_EVENT_4DOWN) {
                //Oven.buttonPressLength4 = globalTimer;
                Oven.timeRemaining = Oven.cookTime;
                Oven.state = COOKING;
                ledTime = Oven.timeRemaining / 8;
                led = 0xFF;
                LEDS_SET(led);
            }
            break;
        case SELECTOR_CHANGE_PENDING:
            if (buttonsPressed & BUTTON_EVENT_3UP) {
                //printf("Released Time: %d\n", globalTimer);
                if (globalTimer - Oven.buttonPressLength3 < LONG_PRESS) {
                    if (Oven.cookMode == BAKE) {
                        Oven.cookMode = TOAST;
                        Oven.settingSelect = TIME;
                    } else if (Oven.cookMode == TOAST) {
                        Oven.cookMode = BROIL;
                        Oven.settingSelect = TIME;
                    } else if (Oven.cookMode == BROIL) {
                        Oven.cookMode = BAKE;
                        Oven.settingSelect = TIME;
                    }
                    //printf("Setting Selected: %d", Oven.settingSelect);
                    updateOvenOLED(Oven);
                } else if (globalTimer - Oven.buttonPressLength3 >= LONG_PRESS) {
                    if (Oven.settingSelect == TIME) {
                        if ((Oven.cookMode == TOAST) || (Oven.cookMode == BROIL)) {
                            Oven.settingSelect = TIME;
                        } else {
                            Oven.settingSelect = TEMP;
                        }
                    } else if (Oven.settingSelect == TEMP) {
                        if ((Oven.cookMode == TOAST) || (Oven.cookMode == BROIL)) {
                            Oven.settingSelect = TIME;
                        } else {
                            Oven.settingSelect = TIME;
                        }
                    }
                    updateOvenOLED(Oven);
                }
                Oven.state = SETUP;
            }
            break;
        case COOKING:
            if ((buttonsPressed & BUTTON_EVENT_3DOWN)
                    || (buttonsPressed & BUTTON_EVENT_3UP)
                    || (buttonsPressed & BUTTON_EVENT_4UP)) {
                break;
            } else if (buttonsPressed & BUTTON_EVENT_4DOWN) {
                Oven.buttonPressLength4 = globalTimer;
                Oven.state = RESET_PENDING;
                break;
            } else if (Oven.timeRemaining > 0) {
                //printf("%d", Oven.timeRemaining);
                led = LEDS_GET();
                Oven.timeRemaining--;
                ledTimeCounter++;
                if (ledTimeCounter == ledTime) {
                    //printf("sneet");
                    ledTimeCounter = 0;
                    led = led >> 1;
                }
                LEDS_SET(led);
                updateOvenOLED(Oven);

                break;
            } else if (Oven.timeRemaining <= 0) {
                Oven.timeRemaining = Oven.cookTime;
                Oven.state = COOKING_DONE;
                led = 0x00;
                LEDS_SET(led);
                updateOvenOLED(Oven);
                break;
            }
        case RESET_PENDING:
            if (globalTimer - Oven.buttonPressLength4 >= LONG_PRESS) {
                Oven.state = SETUP;
                led = 0x00;
                LEDS_SET(led);
                updateOvenOLED(Oven);
            } else if (buttonsPressed & BUTTON_EVENT_4UP) {
                Oven.state = COOKING;
            } else {
                if (Oven.timeRemaining > 0) {
                    //printf("%d", Oven.timeRemaining);
                    led = LEDS_GET();
                    Oven.timeRemaining--;
                    ledTimeCounter++;
                    if (ledTimeCounter == ledTime) {
                        //printf("sneet");
                        ledTimeCounter = 0;
                        led = led >> 1;
                    }
                    LEDS_SET(led);
                    updateOvenOLED(Oven);

                    break;
                } else if (Oven.timeRemaining <= 0) {
                    Oven.timeRemaining = Oven.cookTime;
                    Oven.state = COOKING_DONE;
                    OledSetDisplayInverted();
                    led = 0x00;
                    LEDS_SET(led);
                    updateOvenOLED(Oven);
                    break;
                }
            }
            break;
        case COOKING_DONE:
            if ((buttonsPressed & BUTTON_EVENT_3DOWN)
                    || (buttonsPressed & BUTTON_EVENT_3UP)) {
                break;
            }
            if (buttonsPressed & BUTTON_EVENT_4DOWN) {
                Oven.state = SETUP;
                OledSetDisplayNormal();
                break;
            } else {
                oledInvert = oledInvert * -1;
                if (oledInvert == -1) {
                    OledSetDisplayNormal();
                } else {
                    OledSetDisplayInverted();
                }
                break;
            }
    }
}

int main() {
    BOARD_Init();

    //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>

    printf("Welcome to CRUZID's Lab07 (Toaster Oven).  Compiled on %s %s.\n", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    OledInit();
    AdcInit();
    LEDS_INIT();
    ButtonsInit();
    while (1) {
        if ((ADC.event == TRUE)
                && (Oven.state != COOKING)
                && (Oven.state != COOKING_DONE)) {
            runOvenSM();
            //printf("Bruv\n");
            ADC.event = FALSE;
        }

        if (Button.event == TRUE) {
            //printf("Bruv 2\n");
            runOvenSM();
            Button.event = FALSE;
        }

        if (Timer.event == TRUE) {
            runOvenSM();
            //printf("Bruh");
            Timer.event = FALSE;
        }
        if (invTimer.event == TRUE) {
            runOvenSM();
            //printf("Bruh");
            invTimer.event = FALSE;
        }
        /*if (timer100hz.event == TRUE) {
        if (BUTTON_STATES() & BUTTON_STATE_3) {
            runOvenSM();
            //printf("Button 3");
            updateOvenOLED(Oven);
        }
        if (BUTTON_STATES() & BUTTON_STATE_4) {
            runOvenSM();
            //printf("Button 4");
            updateOvenOLED(Oven);
        }
        if (AdcChanged()) {
            runOvenSM();
            updateOvenOLED(Oven);
        }

    }*/
    }
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;
    //add event-checking code here
    if (Oven.state != COOKING_DONE) {
        Timer.clockTime++;
        if (Timer.clockTime == 5) {
            Timer.event = TRUE;
            Timer.clockTime = 0;
        }
        globalTimer++;
        if (globalTimer == 100000) {
            globalTimer = 0;
        }
    }
}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;
    //add event-checking code here
    buttonsPressed = ButtonsCheckEvents();
    if (AdcChanged()) {
        ADC.event = TRUE;
    }
    if (buttonsPressed & BUTTON_EVENT_3DOWN) {
        Button.event = TRUE;
    }
    if (buttonsPressed & BUTTON_EVENT_3UP) {
        Button.event = TRUE;
    }
    if (buttonsPressed & BUTTON_EVENT_4DOWN) {
        Button.event = TRUE;
    }
    if (buttonsPressed & BUTTON_EVENT_4UP) {
        Button.event = TRUE;
    }
    if (Oven.state == COOKING_DONE) {
        invTimer.clockTime++;
        if (invTimer.clockTime == 50) {
            invTimer.event = TRUE;
            invTimer.clockTime = 0;
        }
    }
}