#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h> 

typedef struct {
    unsigned char chunk_type[4];
    uint32_t length;
    uint16_t format;
    uint16_t ntrks;
    uint16_t division;
} Header;

typedef struct {
    uint32_t midi_event; //not done
    uint32_t sysex_event; //not done
    uint32_t meta_event; //not done
} Event;

typedef struct
{
    uint32_t delta_time; //can possibly overflow
    Event event;
} MtrkEvent;

typedef struct
{
    unsigned char chunk_type;
    uint32_t length;
    MtrkEvent mtrk_event;
} Track;
