#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h> 

read_header(const unsigned char *buffer) {

}

read_track(const unsigned char *buffer) {

}

void read_midi(const unsigned char *buffer) {
    unsigned char chunk_type[4];
    chunk_type[0] = buffer[0];
    chunk_type[1] = buffer[1];
    chunk_type[2] = buffer[2];
    chunk_type[3] = buffer[3];

    uint32_t length =
        (buffer[4] << 24) |
        (buffer[5] << 16) |
        (buffer[6] << 8)  |
        buffer[7];

    uint16_t format   = (buffer[8]  << 8) | buffer[9];
    uint16_t ntrks    = (buffer[10] << 8) | buffer[11];
    uint16_t division = (buffer[12] << 8) | buffer[13];

    if (
        chunk_type[0] != 'M' |
        chunk_type[1] != 'T' | 
        chunk_type[2] != 'h' | 
        chunk_type[3] != 'd' | 
        length != 6
    ) {
        fprintf(stderr, "Error: File must start with ASCII 'MThd' followed by 32-bit big-endian 6.\n");
        exit(1);
    }

    uint32_t ticks_per_second;
    if (division & 0x8000) {
        int8_t frames_per_second = (int8_t)((division >> 8) & 0x7F);
        if (frames_per_second & 0x40) frames_per_second |= 0x80;
        frames_per_second = -frames_per_second;
        uint8_t ticks_per_frame = division & 0xFF;
        ticks_per_second = frames_per_second * ticks_per_frame;
    } else {
        ticks_per_second = division * beats_per_minute / 60;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;

    FILE *f = fopen(argv[1], "rb");
    if (!f) return 1;

    unsigned char buffer[32];
    fread(buffer, 1, 32, f);
    fclose(f);

    read_midi(buffer);
    return 0;
}
