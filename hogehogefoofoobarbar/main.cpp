#include <limits>
#include <stdint.h>
#include "Speaker.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "AnalogIn.h"
#include "PwmOut.h"
#include "InterruptIn.h"
#include "DigitalInOut.h"
#include "GCSonicSensor.h"
#include <stdlib.h>
#include <algorithm>
#include <array>
#include <usb_serial.h>

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

struct Note {
    int note;
    int duration;
};

int random(int max)
{
    return static_cast<int>(rand() * (max + 1.0) / (1.0 + RAND_MAX));
//    return max;
}

void __attribute__((constructor)) initialize()
{
    init();
}

void toggler()
{
    toggleLED();
}

#define LAMBDA(arglist, arrow, retType, body)	\
({                                              \
    class Lambda                                \
    {                                           \
    public:                                     \
    static retType func arglist body            \
    };                                          \
    Lambda::func;                               \
})

#define DURATION 250

InterruptIn<17> powerInput;

int main(int __attribute__((unused)) argc, const char __attribute__((unused)) * argv[])
{
    DigitalOut led(BOARD_LED_PIN);
    led = 1;
    
    powerInput.attach(LAMBDA((), ->, void, {
        static unsigned long powerOffTime = 0;
        if (powerInput) {
            if (powerOffTime < millis()) {
                DigitalOut(18).write(0);
            }
        } else {
            powerOffTime = millis() + 500;
        }
    }), decltype(powerInput)::Mode::Changing);
    while (1) {
        
    }
    
    uint16_t level = std::numeric_limits<uint16_t>::max() / 2;
    int duration = DURATION;  // 8分音符
    Speaker<25> pin;
    //    DigitalIn button(22);
    pinMode(BOARD_LED_PIN, OUTPUT);
    InterruptIn<22> button;
    button.attach(toggler, decltype(button)::Mode::Falling);
    
    duration = 300;
    Note kougen[] = {
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
    
    duration = 250;
    Note water_crown[] = {
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
    
    Note farewell[] = {
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
    
    Note jr_sh1_1[] = {
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
    
    Note jr_sh3_3[] = {
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
    
    Note toi_aozora[] {
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
    
    Note ogawa_no_seseragi[] = {
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
    
    duration = 170;
    Note harumachikaze[] = {
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
    duration = DURATION;
    
    duration = 300;
    Note springbox[] = {
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
    duration = DURATION;
    
    Note mellow_time[] = {
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
    
    Note matataku_machinami[] = {
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
    
    duration = 200;
    Note jr_sh2_2[] = {
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
    duration = DURATION;
    
//    Note natsuirono_jikan[] = {
//        {NOTE_F5, duration},
//        {NOTE_C5, duration * 2},
//        {NOTE_E5, duration * 2},
//        {NOTE_F5, duration},
//        {NOTE_C5, duration * 2},
//
//        {NOTE_F5, duration},
//        {NOTE_C5, duration * 2},
//        {NOTE_E5, duration * 2},
//        {NOTE_F5, duration},
//        {NOTE_C5, duration * 2},
//
//        {NOTE_F5, duration},
//        {NOTE_C5, duration * 2},
//        {NOTE_E5, duration * 2},
//        {NOTE_F5, duration},
//        {NOTE_C5, duration * 2},
//
//        {NOTE_E4, duration / 2},
//        {NOTE_G4, duration / 2},
//        {NOTE_C5, duration / 2},
//        {NOTE_E5, duration / 2},
//        {NOTE_G5, duration * 2},
//    };

//    Note natsuirono_jikan[] = {
//        {NOTE_F5, duration},
//        {NOTE_D5, duration * 2},
//        {NOTE_E5, duration},
//        {NOTE_E5, duration},
//        {NOTE_F5, duration},
//        {NOTE_C5, duration * 2},
//        {NOTE_E5, duration},
//        {NOTE_C5, duration * 2},
//        {NOTE_E5, duration},
//        {NOTE_E5, duration},
//        {NOTE_F5, duration},
//        {NOTE_C5, duration * 2},
//        {NOTE_F5, duration},
//        {NOTE_C5, duration * 2},
//        {NOTE_E5, duration},
//        {NOTE_E5, duration},
//        {NOTE_F5, duration},
//        {NOTE_C5, duration * 2},
//
//        {NOTE_E4, duration / 2},
//        {NOTE_G4, duration / 2},
//        {NOTE_C5, duration / 2},
//        {NOTE_E5, duration / 2},
//        {NOTE_G5, duration * 2},
//    };

//    duration = 170;
//    Note ryokugan_no_jealousy[] = {
//        {NOTE_B3, duration * 8},
//
//        {NOTE_B3, duration * 2},
//        {NOTE_FS4, duration * 2},
//        {NOTE_G4, duration * 2},
//
//        {NOTE_A4, duration * 8},
//
//        {NOTE_A4, duration / 4},
//        {NOTE_B4, duration * 4},
//        {NOTE_FS4, duration * 2},
//
//        {NOTE_G4, duration * 8},
//
//        {NOTE_B4, duration * 4},
//        {NOTE_FS4, duration * 2},
//
//        {NOTE_G4, duration * 8},
//
//        {NOTE_B4, duration * 4},
//        {NOTE_E5, duration * 2},
//
//        {NOTE_E5, duration * 4},
//        {NOTE_C5, duration},
//        {NOTE_D5, duration},
//    };
    
    pin.play(duration, 0, 0);
    
    srand(AnalogIn(11));
    
    std::array<Note*, 12> songs = {
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
    const int numOfSongs = sizeof(songs) / sizeof(songs[0]);
    int song_sizes[] = {
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
    int indexes[numOfSongs];
    for (int i = 0; i < numOfSongs; i++) {
        indexes[i] = i;
    }
    
#define makeCase(num, notes)                                                    \
    case num:                                                                   \
        for (unsigned int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++) {   \
            if (notes[i].note) {                                                \
                pin.play(notes[i].note, level, notes[i].duration);              \
            }                                                                   \
            delay(notes[i].duration + 10);                                      \
        }                                                                       \
        break
    
    while (1) {
//        while (button) ;
//        switch (random(11)) {
//                makeCase(0, kougen);
//                makeCase(1, water_crown);
//                makeCase(2, farewell);
//                makeCase(3, jr_sh1_1);
//                makeCase(4, jr_sh3_3);
//                makeCase(5, toi_aozora);
//                makeCase(6, ogawa_no_seseragi);
//                makeCase(7, harumachikaze);
//                makeCase(8, springbox);
//                makeCase(9, mellow_time);
//                makeCase(10, matataku_machinami);
//                makeCase(11, jr_sh2_2);
//            default:
//                break;
//        }
        std::random_shuffle(indexes, indexes + sizeof(indexes) / sizeof(indexes[0] - 1));
        for (auto index : indexes) {
            while (button) ;
            for (int i = 0; i < song_sizes[index]; i++) {
                if (songs[index][i].note) {
                    pin.play(songs[index][i].note, level, songs[index][i].duration);
                }
                delay(songs[index][i].duration + 10);
            }
        }
        pin.play(duration, 0, 0);
    }
    
    return 0;
}
