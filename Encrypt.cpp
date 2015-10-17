
#include "TMP36.h"
#include "uLCD_4DGL.h"
uLCD_4DGL uLCD(p28, p27, p29); // serial tx, serial rx, reset pin;
#include "math.h"
#include <iostream>
#include <sstream>
#include "PinDetect.h"
#include "SDFileSystem.h"
SDFileSystem sd(p5, p6, p7, p8, "sd");


void store(string s);
char arrayCipher[1000];
int index;

int state;
int currLetter;
PinDetect pb1(p19); //you can use different pins
PinDetect pb2(p10); //you can use different pins
PinDetect pb3(p12); // you can use different pins
//////////////////
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

using namespace std;


void pb1_hit_callback (void)
{

    currLetter = currLetter - 1;
    if (currLetter == -1 ) {
        currLetter = 25;
    } else {
        currLetter = currLetter % 26;
    }
    //////////////////

    uLCD.locate(0,0);
    uLCD.text_width(5);
    uLCD.text_height(5);
    uLCD.printf("%c",char(currLetter + 65));
}
void pb2_hit_callback (void)
{
    /////////////////////////
    currLetter = currLetter + 1;
    currLetter = currLetter % 26;

    ///////////////

    uLCD.locate(0,0);
    uLCD.text_width(5);
    uLCD.text_height(5);
    uLCD.printf("%c",char(currLetter + 65));
}

void pb3_hit_callback (void)
{

    myled3 = !myled3;
    wait(0.5);
    myled3 = 0;

    FILE *fp2 = fopen("/sd/Lab4/positionCipherSender.txt", "r");

    if(fp2 == NULL) {
        uLCD.printf("Open Error!!!\n");
    } else {
        fscanf(fp2, "%i",&index);
        fclose(fp2);
        fclose(fp2);
        uLCD.locate(0,2);
        uLCD.text_width(5);
        uLCD.text_height(5);
        int cc = (arrayCipher[index] -65);
        cc = cc + currLetter;
        int dk = cc%26;
        uLCD.printf("%c",char(dk + 65));


        FILE  *fpC = fopen("/sd/Lab4/positionCipherSender.txt", "w");

        if(fpC == NULL) {
            uLCD.printf("Error Open \n");
        } else {
            fprintf(fpC, "%i", index + 1);
            fclose(fpC);
        }
    }


}



int main()
{
    // Delay for initial pullup to take effect
    wait(.01);
// Setup Interrupt callback functions for a pb hit
    pb1.attach_deasserted(&pb1_hit_callback);
    pb2.attach_deasserted(&pb2_hit_callback);
    pb3.attach_deasserted(&pb3_hit_callback);
// Start sampling pb inputs using interrupts
    pb1.setSampleFrequency();
    pb2.setSampleFrequency();
    pb3.setSampleFrequency();
// pushbuttons now setup and running
    FILE *fp = fopen("/sd/Lab4/OTP.txt", "r");
    if(fp == NULL) {
        uLCD.printf("Open Error!!!\n");
    } else {
        fscanf(fp, "%s",arrayCipher);
        fclose(fp);
        state = 0;
        currLetter = 0;
        uLCD.cls();
        uLCD.locate(0,0);
        uLCD.text_width(5);
        uLCD.text_height(5);
        uLCD.printf("%c",char(currLetter + 65));

        while (1) {


            myled4 = !myled4;
            wait(0.2);
        }
        return 0;
    }



}
