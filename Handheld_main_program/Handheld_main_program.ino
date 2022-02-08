
/*
 Name:		Handheld_main_program.ino
 Created:	2/17/2021 4:13:36 PM
 Author:	Imam Syahrizal, Izzun Nafis I, Raihan Dhiazuhdi W

 Default setting:
 RTC using DS3231
 baud_rate is 9600 (can be changed easily by set param)
 update sensor frequency is 5 Hz (can be changed easily by set param)
 default record action duration 10 s (can be changed easily by set param)
 default maximum voltage for voltage sensor is 25 V (if your sensor have different max voltage please change in serial_print_data() function in source file)
*/

#include <LED_handheld_behaviour.h>


void HMI_state();

Led_handheld_behaviour hb;
int data;

void setup() {
	Serial.begin(9600);
    hb.rtc_init();
}

// the loop function runs over and over again until power down or reset
void loop() {
	HMI_state();
}




void HMI_state()
{
    if (Serial.available() > 0)
    {
        if (data == 2 || data == 3)
        {
            if (Serial.readString().toInt() != data)
            {
                hb.stop_record();
                if (data == 2)
                    hb.record(5);
                else
                    hb.record(5, 10);
            }
        }
        data = Serial.readString().toInt();
    }

    switch (data)
    {
    case 0:
        break;
    case 1:
        if (hb.serial_print(5))
            data = 1;
        else
            data = 0;
        break;
    case 2:
        if (!hb.record(5))
            data = 2;
        else
            data = 0;
        break;
    case 3:
        if (!hb.record(5, 10))
            data = 3;
        else
            data = 0;
        break;
    case 4:
        if (hb.remove_all_files())
            data = 0;
        else
            data = 4;
        break;
    case 5:
        if (hb.memory_info())
            data = 0;
        else
            data = 5;
        break;
    case 6:
        if (hb.import_all_files())
            data = 0;
        else
            data = 6;
    default:
        break;
    }

}
