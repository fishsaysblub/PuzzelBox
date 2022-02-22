//
// Created by david on 21-5-19.
//

#ifndef MAIN_BOM_BIEM_H
#define MAIN_BOM_BIEM_H

extern const unsigned char biem_raw[];
extern const unsigned int biem_raw_len;

union BiemConvert
{
    const unsigned char *biem_char;
    float *biem_float;
};

#endif // MAIN_BOM_BIEM_H
