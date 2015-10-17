
#include "TMP36.h"
#include "uLCD_4DGL.h"
uLCD_4DGL uLCD(p28, p27, p29); // serial tx, serial rx, reset pin;
#include "math.h"
#include <iostream>
#include <sstream>
#include "PinDetect.h"
#include "SDFileSystem.h"
SDFileSystem sd(p5, p6, p7, p8, "sd");

void createPad();
void bye();
void store(string s);

int state;
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
    state = 1;
    myled1 = 1;
    wait(0.5);
    myled1 = 0;
}
void pb2_hit_callback (void)
{
    state = 2;
    myled2 = 1;
    wait(0.5);
    myled2 = 0;
}

void bye()
{

    uLCD.printf("\n Good Bye");

}
void generated()
{

    state = 0;
    uLCD.printf("\n Pad Created, Do you want to create another?");
    while (1) {

        if (state == 1) {
            createPad();
            break;
        };
        if (state == 2) {
            bye();
            break;
        };



        myled3 = !myled3;
        wait(0.2);
    }
}

int main()
{
    // Delay for initial pullup to take effect
    wait(.01);
// Setup Interrupt callback functions for a pb hit
    pb1.attach_deasserted(&pb1_hit_callback);
    pb2.attach_deasserted(&pb2_hit_callback);
// pb3.attach_deasserted(&pb3_hit_callback);
// Start sampling pb inputs using interrupts
    pb1.setSampleFrequency();
    pb2.setSampleFrequency();
//pb3.setSampleFrequency();
// pushbuttons now setup and running

    state = 0;
    uLCD.cls();
    uLCD.printf("Do you want to    create a one time pad?");
    while (1) {

        if (state == 1) {
            createPad();
            break;
        };
        if (state == 2) {
            bye();
            break;
        };



        myled4 = !myled4;
        wait(0.2);
    }
    return 0;
}

void createPad()
{

    float tempC, tempF , tempF2;
    TMP36 Temp(p20);
    tempC = Temp.read();


    tempF = (9.0*tempC)/5.0 + 32.0;
    // print current temp

//uLCD.printf("%5.2f F \n\r", tempF);
    wait(2.0);

    tempC = Temp.read();

    tempF2 = (9.0*tempC)/5.0 + 32.0;
    //print current temp
    //uLCD.printf("%5.2f F \n\r", tempF2);
//  wait(0.3);
    int Diff = ceil((abs(tempF2 - tempF) * 1000) - 0.5);
    // uLCD.printf("Diff int  is %d \n", Diff);
    // wait(0.3);
    // uLCD.cls();

    srand(time(NULL));
    char arr[1000];
    string thestring;
    for (int i = 0; i < 999; i ++) {
        arr[i] = char(((rand()+Diff)%26)+65);
        thestring = thestring + arr[i];
    }


    store(thestring);
    generated();

}
void store(string s)
{
    mkdir("/sd/Lab4", 0777);

    FILE *fp = fopen("/sd/Lab4/OTP.txt", "w");
    if(fp == NULL) {
        uLCD.printf("Error Open \n");
    }
    fprintf(fp, "%s", s.c_str());
    fclose(fp);

///////////////////////////////////////////////////
    fp = fopen("/sd/Lab4/positionCipherSender.txt", "w");
    if(fp == NULL) {
        uLCD.printf("Error Open \n");
    }
    fprintf(fp, "0");
    fclose(fp);
///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////
    fp = fopen("/sd/Lab4/positionCipherReceiver.txt", "w");
    if(fp == NULL) {
        uLCD.printf("Error Open \n");
    }
    fprintf(fp, "0");
    fclose(fp);
///////////////////////////////////////////////////////

}


