#include "PlanAlpha.h"
#include <limits>
#include <stdlib.h>

decltype(PlanAlpha::speaker1) PlanAlpha::speaker1;
decltype(PlanAlpha::speaker2) PlanAlpha::speaker2;
//GCADJD                       PlanAlpha::leftColorSensor(I2CDevice::Pin::I2C2);
//GCADJD                       PlanAlpha::rightColorSensor(I2CDevice::Pin::I2C1);
//GC6050             PlanAlpha::gyroAcceleroSensor(I2CDevice::Pin::I2C2);
//PAL3G4200D         PlanAlpha::gyroSensor(I2CDevice::Pin::I2C2);
PALineSensor                 PlanAlpha::forwardLeftLineSensor(6, 1600);
PALineSensor                 PlanAlpha::forwardCenterLineSensor(5, 1400);
PALineSensor                 PlanAlpha::forwardRightLineSensor(3, 1400);
PALineSensor                 PlanAlpha::middleLeftLineSensor(7, 1000);
PALineSensor                 PlanAlpha::middleRightLineSensor(8, 1000);
PAThreeLineSensors           PlanAlpha::forwardLineSensors(
                                  &forwardLeftLineSensor, &forwardCenterLineSensor, &forwardRightLineSensor
                             );
GCMotor                      PlanAlpha::leftMotor(13, 14, 11);
GCMotor                      PlanAlpha::rightMotor(2, 12, 10);
decltype(PlanAlpha::powerSwitch) PlanAlpha::powerSwitch(28);

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262     // ド
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#ifdef __clang__
#   undef  __FLASH__
#   define __FLASH__
#endif

struct Note {
    int note;
    int duration;
};

static void __attribute__((constructor)) initializer()
{
    init();
}

#define duration 300
Note __FLASH__ kougen[] = {
    {NOTE_B4, duration * 2},
    {NOTE_B4, duration},
    {NOTE_D5, duration},
    {NOTE_G5, duration * 2},
    {NOTE_B4, duration * 2},
    
    {NOTE_C5, duration * 2},
    {NOTE_C5, duration},
    {NOTE_E5, duration},
    {NOTE_G5, duration * 2},
    {NOTE_C5, duration * 2},
    
    {NOTE_D5, duration * 2},
    {NOTE_D5, duration},
    {NOTE_FS5, duration},
    {NOTE_A5, duration * 2},
    {NOTE_FS5, duration * 2},
    {NOTE_G5, duration * 2},
};
#undef duration

#define duration 250
Note __FLASH__ water_crown[] = {
    {NOTE_C5, duration / 2},
    {NOTE_G4, duration / 2},
    {NOTE_C5, duration / 2},
    {NOTE_E5, duration / 2},
    {NOTE_A5, duration},
    {NOTE_G5, duration},
    {0, duration},
    {NOTE_C6, duration / 2},
    {NOTE_B6, duration / 2},
    {NOTE_A6, duration / 2},
    {NOTE_G5, duration / 2},
    {NOTE_F5, duration / 2},
    {NOTE_D5, duration / 2},
    
    {NOTE_C5, duration / 2},
    {NOTE_G4, duration / 2},
    {NOTE_C5, duration / 2},
    {NOTE_E5, duration / 2},
    {NOTE_A5, duration},
    {NOTE_G5, duration},
    {0, duration},
    {NOTE_C6, duration / 2},
    {NOTE_B6, duration / 2},
    {NOTE_A6, duration / 2},
    {NOTE_G5, duration / 2},
    {NOTE_F5, duration / 2},
    {NOTE_D5, duration / 2},
    
    {NOTE_C5, duration / 2},
    {NOTE_G4, duration / 2},
    {NOTE_C5, duration / 2},
    {NOTE_E5, duration / 2},
    {NOTE_A5, duration},
    {NOTE_G5, duration},
    {NOTE_D5, duration / 2},
    {NOTE_F5, duration / 2},
    {NOTE_A5, duration / 2},
    {NOTE_C6, duration / 2},
    {NOTE_B5, duration / 2},
    {NOTE_G5, duration / 2},
    {NOTE_B5, duration / 2},
    {NOTE_G6, duration / 2},
    
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
    {NOTE_A5, duration / 4},
    {NOTE_CS6, duration / 4},
};

Note __FLASH__ farewell[] = {
    {NOTE_F5, duration},
    {NOTE_F4, duration},
    {NOTE_C5, duration},
    {NOTE_F4, duration},
    
    {NOTE_C5, duration},
    {NOTE_F5, duration},
    {NOTE_E5, duration},
    {NOTE_D5, duration},
    
    {NOTE_E5, duration},
    {NOTE_E4, duration},
    {NOTE_B4, duration},
    {NOTE_E4, duration},
    
    {NOTE_C5, duration},
    {NOTE_E5, duration},
    {NOTE_D5, duration},
    {NOTE_C5, duration},
    
    {NOTE_D5, duration},
    {NOTE_D4, duration},
    {NOTE_A4, duration},
    {NOTE_G4, duration},
    
    {NOTE_D5, duration},
    {NOTE_C5, duration},
    {NOTE_D4, duration},
    {NOTE_B4, duration},
    
    {NOTE_C5, duration},
    {0, duration},
    {NOTE_C4, duration},
    {0, duration},
    
    {NOTE_G3, duration / 4},
    {NOTE_C4, duration / 4},
    {NOTE_E4, duration / 4},
    {NOTE_G4, duration / 4},
    {NOTE_C5, duration / 4},
    {NOTE_E5, duration / 4},
    {NOTE_G5, duration / 4},
    {NOTE_C6, duration / 4},
};

Note __FLASH__ jr_sh1_1[] = {
    {NOTE_C4, duration},
    {NOTE_G4, duration},
    {NOTE_C5, duration},
    {NOTE_D5, duration},
    {NOTE_E5, duration},
    {NOTE_G4, duration},
    {NOTE_C5, duration},
    {NOTE_G4, duration},
    
    {NOTE_F5, duration},
    {NOTE_E5, duration},
    {NOTE_D5, duration},
    {NOTE_C5, duration},
    {NOTE_B4, duration},
    {NOTE_C5, duration},
    {NOTE_D5, duration},
    {NOTE_B4, duration},
    
    {NOTE_C5, duration},
    {NOTE_G4, duration},
    {NOTE_C5, duration},
    {NOTE_D5, duration},
    {NOTE_E5, duration},
    {NOTE_G4, duration},
    {NOTE_C5, duration},
    {NOTE_G4, duration},
    
    {NOTE_A5, duration},
    {NOTE_G5, duration},
    {NOTE_F5, duration},
    {NOTE_E5, duration},
    {NOTE_D4, duration},
    {NOTE_E5, duration},
    {NOTE_F5, duration},
    {NOTE_D4, duration},
    
    {NOTE_E5, duration * 2},
    {NOTE_G5, duration * 2},
    {NOTE_C6, duration * 4},
};

Note __FLASH__ jr_sh3_3[] = {
    {NOTE_E5, duration},
    {NOTE_DS5, duration},
    {NOTE_B4, duration},
    {NOTE_GS4, duration},
    {NOTE_FS4, duration},
    {NOTE_E4, duration},
    {NOTE_B3, duration},
    {NOTE_E4, duration},
    {NOTE_E3, duration},
    {NOTE_GS4, duration},
    {NOTE_B4, duration},
    {NOTE_DS5, duration},
    {NOTE_E5, duration},
    {NOTE_DS5, duration},
    {NOTE_B4, duration},
    {NOTE_GS4, duration},
    
    {NOTE_FS5, duration},
    {NOTE_D5, duration},
    {NOTE_B4, duration},
    {NOTE_A4, duration},
    {NOTE_A4, duration},
    {NOTE_G4, duration},
    {NOTE_D4, duration},
    {NOTE_G4, duration},
    {NOTE_G3, duration},
    {NOTE_FS5, duration},
    {NOTE_G5, duration},
    {NOTE_FS5, duration},
    {NOTE_G5, duration},
    {NOTE_FS5, duration},
    {NOTE_D5, duration},
    {NOTE_B4, duration},
    {NOTE_C5, duration / 4},
    {NOTE_A5, duration},
};

Note __FLASH__ toi_aozora[] {
    {NOTE_F5, duration},
    {NOTE_F5, duration},
    {NOTE_F5, duration},
    {NOTE_F5, duration},
    {NOTE_G5, duration},
    {NOTE_A5, duration * 2},
    {0, duration},
    
    {NOTE_E5, duration},
    {NOTE_E5, duration},
    {NOTE_E5, duration},
    {NOTE_E5, duration},
    {NOTE_F5, duration},
    {NOTE_G5, duration * 2},
    {0, duration},
    
    {NOTE_D5, duration},
    {NOTE_D5, duration},
    {NOTE_D5, duration},
    {NOTE_D5, duration},
    {NOTE_G5, duration},
    {NOTE_F5, duration},
    {NOTE_B5, duration * 2},
    
    {NOTE_C5, duration / 2},
    {NOTE_F5, duration / 2},
    {NOTE_G5, duration / 2},
    {NOTE_C6, duration * 2},
};

Note __FLASH__ ogawa_no_seseragi[] = {
    {NOTE_C6, duration},
    {NOTE_C5, duration},
    {NOTE_E5, duration},
    {NOTE_G5, duration},
    {NOTE_C5, duration},
    {NOTE_E5, duration},
    
    {NOTE_C6, duration},
    {NOTE_C5, duration},
    {NOTE_E5, duration},
    {NOTE_G5, duration},
    {NOTE_C5, duration},
    {NOTE_E5, duration},
    
    {NOTE_A4, duration},
    {NOTE_C5, duration},
    {NOTE_E5, duration},
    {NOTE_D5, duration},
    {NOTE_F5, duration},
    {NOTE_A5, duration},
    
    {NOTE_C5, duration / 2},
    {NOTE_E5, duration / 2},
    {NOTE_G5, duration / 2},
    {NOTE_C6, duration * 3},
};
#undef duration

#define duration 170
Note __FLASH__ harumachikaze[] = {
    {NOTE_G4, duration},
    {NOTE_C5, duration},
    {NOTE_F5, duration},
    {NOTE_G5, duration},
    {NOTE_G4, duration},
    {NOTE_C5, duration},
    {NOTE_F5, duration},
    {NOTE_G5, duration},
    
    {NOTE_C5, duration},
    {NOTE_E5, duration},
    {NOTE_G5, duration},
    {NOTE_B5, duration},
    {NOTE_C5, duration},
    {NOTE_E5, duration},
    {NOTE_G5, duration},
    {NOTE_B5, duration},
    
    {NOTE_D5, duration},
    {NOTE_G5, duration},
    {NOTE_B5, duration},
    {NOTE_C6, duration},
    {NOTE_D5, duration},
    {NOTE_G5, duration},
    {NOTE_B5, duration},
    {NOTE_C6, duration},
    
    {NOTE_A3, duration / 2},
    {NOTE_C4, duration / 2},
    {NOTE_E4, duration / 2},
    {NOTE_A4, duration / 2},
    {NOTE_C5, duration / 2},
    {NOTE_E5, duration / 2},
    {NOTE_A5, duration / 2},
    {NOTE_C6, duration / 2},
    {NOTE_E6, duration / 2},
};
#undef duration

#define duration 300
Note __FLASH__ springbox[] = {
    {NOTE_G4, duration},
    {NOTE_E5, duration},
    {NOTE_D5, duration},
    {NOTE_C5, duration},
    {NOTE_B4, duration},
    {NOTE_A4, duration},
    {NOTE_GS4, duration * 2},
    
    {NOTE_A4, duration},
    {NOTE_A5, duration},
    {NOTE_G5, duration},
    {NOTE_F5, duration},
    {NOTE_E5, duration},
    {NOTE_D5, duration},
    {NOTE_E5, duration * 2},
    
    {NOTE_F5, duration},
    {NOTE_C5, duration},
    {NOTE_C5, duration},
    {NOTE_F5, duration},
    {NOTE_E5, duration},
    {NOTE_D5, duration},
    {NOTE_C5, duration},
    {NOTE_B4, duration},
    {NOTE_C5, duration * 4},
};
#undef duration

#define duration 300
Note __FLASH__ mellow_time[] = {
    {NOTE_D5, duration},
    {NOTE_A4, duration / 2},
    {NOTE_CS5, duration},
    {NOTE_FS4, duration / 2},
    {NOTE_FS5, duration / 2},
    {NOTE_E5, duration},
    
    {NOTE_D5, duration},
    {NOTE_CS5, duration},
    {NOTE_A4, duration / 2},
    {NOTE_E5, duration / 2},
    {NOTE_D5, duration / 2},
    
    {NOTE_D5, duration},
    {NOTE_A4, duration / 2},
    {NOTE_G4, duration / 2},
    {NOTE_FS4, duration / 2},
    {NOTE_G4, duration / 2},
    {NOTE_A4, duration / 2},
    
    {NOTE_A4, duration},
    {NOTE_B4, duration},
    {NOTE_E5, duration / 2},
    {NOTE_D5, duration},
    {NOTE_CS5, duration / 2},
    {NOTE_D5, duration / 2},
    
    {NOTE_D5, duration},
    {NOTE_A4, duration / 2},
    {NOTE_CS5, duration},
    {NOTE_FS4, duration / 2},
    {NOTE_FS5, duration / 2},
    {NOTE_E5, duration},
    
    {NOTE_B4, duration},
    {NOTE_CS5, duration / 2},
    {NOTE_FS4, duration / 2},
    {NOTE_A4, duration / 2},
    {NOTE_CS5, duration},
    {NOTE_D5, duration * 2},
};

Note __FLASH__ matataku_machinami[] = {
    {NOTE_C5, duration},
    {NOTE_F5, duration / 2},
    {NOTE_A5, duration / 2},
    {NOTE_C5, duration},
    {NOTE_F5, duration / 2},
    {NOTE_A5, duration / 2},
    {NOTE_C5, duration},
    {NOTE_F5, duration / 2},
    {NOTE_A5, duration / 2},
    {NOTE_C5, duration},
    {NOTE_F5, duration / 2},
    {NOTE_A5, duration / 2},
    
    {NOTE_F6, duration / 2},
    {NOTE_D6, duration / 2},
    {NOTE_B5, duration / 2},
    {NOTE_F5, duration / 2},
    {NOTE_F6, duration / 2},
    {NOTE_D6, duration / 2},
    {NOTE_B5, duration / 2},
    {NOTE_F5, duration / 2},
    {NOTE_E6, duration / 2},
    {NOTE_C6, duration / 2},
    {NOTE_G5, duration / 2},
    {NOTE_E5, duration / 2},
    {NOTE_C5, duration / 2},
    {NOTE_E5, duration / 2},
    {NOTE_G5, duration / 2},
    {NOTE_C6, duration / 2},
    
    {NOTE_C5, duration},
    {NOTE_F5, duration / 2},
    {NOTE_A5, duration / 2},
    {NOTE_C5, duration},
    {NOTE_F5, duration / 2},
    {NOTE_A5, duration / 2},
    {NOTE_C5, duration},
    {NOTE_F5, duration / 2},
    {NOTE_A5, duration / 2},
    {NOTE_C5, duration},
    {NOTE_F5, duration / 2},
    {NOTE_A5, duration / 2},
    
    {NOTE_A5, static_cast<int>(duration * 1.5)},
    {NOTE_G5, static_cast<int>(duration * 1.5)},
    {NOTE_F5, static_cast<int>(duration * 1.5)},
    {NOTE_E5, static_cast<int>(duration * 1.5)},
};
#undef duration

#define duration 200
Note __FLASH__ jr_sh2_2[] = {
    {NOTE_A4, duration},
    {NOTE_C5, duration},
    {NOTE_F5, duration},
    {NOTE_E5, duration},
    {NOTE_F5, duration * 2},
    {NOTE_C5, duration * 2},
    
    {NOTE_D5, duration},
    {NOTE_G5, duration},
    {NOTE_F5, duration},
    {NOTE_E5, duration},
    {NOTE_D5, duration},
    {NOTE_E5, duration},
    {NOTE_C5, duration},
    {NOTE_C5, duration},
    
    {NOTE_C5, duration},
    {NOTE_DS5, duration},
    {NOTE_GS5, duration},
    {NOTE_G5, duration},
    {NOTE_GS5, duration * 2},
    {NOTE_DS5, duration * 2},
    
    {NOTE_D5, duration},
    {NOTE_F5, duration},
    {NOTE_AS5, duration},
    {NOTE_GS5, duration},
    {NOTE_G5, duration},
    {NOTE_F5, duration},
    {NOTE_G5, duration},
    {NOTE_DS5, duration},
    
    {NOTE_GS5, duration},
    {NOTE_DS5, duration},
    {NOTE_CS5, duration},
    {NOTE_DS5, duration},
    {NOTE_C5, duration * 4},
};
#undef duration

Note __FLASH__ *songs[] = {
    kougen,
    water_crown,
    farewell,
    jr_sh1_1,
    jr_sh3_3,
    toi_aozora,
    ogawa_no_seseragi,
    harumachikaze,
    springbox,
    mellow_time,
    matataku_machinami,
    jr_sh2_2,
};

unsigned int __FLASH__ song_sizes[] = {
    sizeof(kougen) / sizeof(kougen[0]),
    sizeof(water_crown) / sizeof(water_crown[0]),
    sizeof(farewell) / sizeof(farewell[0]),
    sizeof(jr_sh1_1) / sizeof(jr_sh1_1[0]),
    sizeof(jr_sh3_3) / sizeof(jr_sh3_3[0]),
    sizeof(toi_aozora) / sizeof(toi_aozora[0]),
    sizeof(ogawa_no_seseragi) / sizeof(ogawa_no_seseragi[0]),
    sizeof(harumachikaze) / sizeof(harumachikaze[0]),
    sizeof(springbox) / sizeof(springbox[0]),
    sizeof(mellow_time) / sizeof(mellow_time[0]),
    sizeof(matataku_machinami) / sizeof(matataku_machinami[0]),
    sizeof(jr_sh2_2) / sizeof(jr_sh2_2[0]),
};

const int noteFrequencies[] = {
    0,  9,  9, 10,  10, 11,   12,  12, 13, 14, 15, 15,
    16,  17, 18, 19,  21, 22,  23,  25, 26, 28, 29, 31,
    33,  35, 37,  39,  41, 44,  46, 49, 52, 55, 58, 62,
    65, 69, 73, 78,  82, 87,  93, 98, 104,  110,  117,  124,
    131, 139, 147, 156, 165, 175, 185,  196,  208,  220,  233,  247,
    262, 277, 294, 311, 330, 349, 370,  392,  415,  440,  466,  494,
    523, 554, 587, 622, 659, 699, 740,  784,  831,  880,  932,  988,
    1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
    2093, 2218, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951,
    4186, 4435, 4699, 4978, 5274, 5587, 5920, 6272, 6645, 7040, 7459, 7902,
    8372, 8870, 9397, 9956, 10548,11175,  11840,  12544
};

static bool myDelay(unsigned long ms)
{
    if (PlanAlpha::powerSwitch.read() == false) {
        PlanAlpha::speaker1.pwm->write(0);
        PlanAlpha::speaker2.pwm->write(0);
        return true;
    }
    delay(ms);
    return false;
}

class Initializer {
public:
    Initializer() {
        srand(PlanAlpha::forwardCenterLineSensor.readRawValue());
        int num = static_cast<int>(rand() * (sizeof(song_sizes) / sizeof(song_sizes[0] + 1) + 1.0) / (1.0 + RAND_MAX));
		if (num == sizeof(song_sizes) / sizeof(song_sizes[0])) {
			// cielo estrellado
			using namespace PlanAlpha;
			const uint16_t level = std::numeric_limits<uint16_t>::max() / 2;
			
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[60]);
			speaker1.pwm->write(level);
			speaker2.pwm->write(0);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[60]);
			speaker1.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[60]);
			speaker1.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[60]);
			speaker1.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[60]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[79]);
			speaker2.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[84]);
			speaker2.pwm->write(level);
			if (myDelay(135)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[79]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[60]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker2.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[79]);
			speaker2.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[84]);
			speaker2.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[79]);
			speaker2.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[60]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[79]);
			speaker2.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[84]);
			speaker2.pwm->write(level);
			if (myDelay(135)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[79]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[60]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[79]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[84]);
			speaker2.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[79]);
			speaker2.pwm->write(level);
			if (myDelay(135)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[60]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[91]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[96]);
			speaker2.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[91]);
			speaker2.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[60]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker2.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[91]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[96]);
			speaker2.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[91]);
			speaker2.pwm->write(level);
			if (myDelay(135)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[60]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[91]);
			speaker2.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[96]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[91]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[60]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker2.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[91]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[96]);
			speaker2.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[91]);
			speaker2.pwm->write(level);
			//set_ch(ADDR_FREQ_C, 79);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[67]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[79]);
			speaker2.pwm->write(level);
			//set_ch(ADDR_FREQ_C, 0);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[68]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[80]);
			speaker2.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[72]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[84]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[75]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[87]);
			speaker2.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[82]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[94]);
			speaker2.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[80]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[92]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[84]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[96]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[75]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[87]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[70]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[82]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[70]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[82]);
			speaker2.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[74]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[86]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[77]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[89]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[84]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[96]);
			speaker2.pwm->write(level);
			if (myDelay(137)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[86]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[98]);
			speaker2.pwm->write(level);
			if (myDelay(138)) return;
			speaker1.pwm->setPeriod(1000000 / noteFrequencies[89]);
			speaker1.pwm->write(level);
			speaker2.pwm->setPeriod(1000000 / noteFrequencies[101]);
			speaker2.pwm->write(level);
			if (myDelay(136)) return;
			speaker1.play(noteFrequencies[96], level, 687);
			speaker2.play(noteFrequencies[108], level, 687);
			if (myDelay(687)) return;
		} else {
			const Note *song = songs[num];
			int size = song_sizes[num];
			for (int i = 0; i < size; i++) {
				if (song[i].note) {
					PlanAlpha::speaker.play(
											song[i].note, std::numeric_limits<uint16_t>::max() / 2, song[i].duration
											);
				}
				delay(song[i].duration + 10);
			}
		}
    }
};

static Initializer dummy;
