/*
 * MIT License
 *
 * Copyright (c) 2020 ALİ GÜNGÖR
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "snow3g.h"

static thread_local uint32_t LFSR_S0 = 0x00;
static thread_local uint32_t LFSR_S1 = 0x00;
static thread_local uint32_t LFSR_S2 = 0x00;
static thread_local uint32_t LFSR_S3 = 0x00;
static thread_local uint32_t LFSR_S4 = 0x00;
static thread_local uint32_t LFSR_S5 = 0x00;
static thread_local uint32_t LFSR_S6 = 0x00;
static thread_local uint32_t LFSR_S7 = 0x00;
static thread_local uint32_t LFSR_S8 = 0x00;
static thread_local uint32_t LFSR_S9 = 0x00;
static thread_local uint32_t LFSR_S10 = 0x00;
static thread_local uint32_t LFSR_S11 = 0x00;
static thread_local uint32_t LFSR_S12 = 0x00;
static thread_local uint32_t LFSR_S13 = 0x00;
static thread_local uint32_t LFSR_S14 = 0x00;
static thread_local uint32_t LFSR_S15 = 0x00;

static thread_local uint32_t FSM_R1 = 0x00;
static thread_local uint32_t FSM_R2 = 0x00;
static thread_local uint32_t FSM_R3 = 0x00;

static thread_local uint8_t SR[256] =
    {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67,
     0x2B, 0xFE, 0xD7, 0xAB, 0x76, 0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59,
     0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0, 0xB7,
     0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1,
     0x71, 0xD8, 0x31, 0x15, 0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05,
     0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75, 0x09, 0x83,
     0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29,
     0xE3, 0x2F, 0x84, 0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B,
     0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF, 0xD0, 0xEF, 0xAA,
     0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C,
     0x9F, 0xA8, 0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC,
     0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2, 0xCD, 0x0C, 0x13, 0xEC,
     0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19,
     0x73, 0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE,
     0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB, 0xE0, 0x32, 0x3A, 0x0A, 0x49,
     0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
     0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4,
     0xEA, 0x65, 0x7A, 0xAE, 0x08, 0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6,
     0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A, 0x70,
     0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9,
     0x86, 0xC1, 0x1D, 0x9E, 0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E,
     0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF, 0x8C, 0xA1,
     0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0,
     0x54, 0xBB, 0x16};

static thread_local uint8_t SQ[256] =
    {0x25, 0x24, 0x73, 0x67, 0xD7, 0xAE, 0x5C, 0x30, 0xA4, 0xEE, 0x6E,
     0xCB, 0x7D, 0xB5, 0x82, 0xDB, 0xE4, 0x8E, 0x48, 0x49, 0x4F, 0x5D,
     0x6A, 0x78, 0x70, 0x88, 0xE8, 0x5F, 0x5E, 0x84, 0x65, 0xE2, 0xD8,
     0xE9, 0xCC, 0xED, 0x40, 0x2F, 0x11, 0x28, 0x57, 0xD2, 0xAC, 0xE3,
     0x4A, 0x15, 0x1B, 0xB9, 0xB2, 0x80, 0x85, 0xA6, 0x2E, 0x02, 0x47,
     0x29, 0x07, 0x4B, 0x0E, 0xC1, 0x51, 0xAA, 0x89, 0xD4, 0xCA, 0x01,
     0x46, 0xB3, 0xEF, 0xDD, 0x44, 0x7B, 0xC2, 0x7F, 0xBE, 0xC3, 0x9F,
     0x20, 0x4C, 0x64, 0x83, 0xA2, 0x68, 0x42, 0x13, 0xB4, 0x41, 0xCD,
     0xBA, 0xC6, 0xBB, 0x6D, 0x4D, 0x71, 0x21, 0xF4, 0x8D, 0xB0, 0xE5,
     0x93, 0xFE, 0x8F, 0xE6, 0xCF, 0x43, 0x45, 0x31, 0x22, 0x37, 0x36,
     0x96, 0xFA, 0xBC, 0x0F, 0x08, 0x52, 0x1D, 0x55, 0x1A, 0xC5, 0x4E,
     0x23, 0x69, 0x7A, 0x92, 0xFF, 0x5B, 0x5A, 0xEB, 0x9A, 0x1C, 0xA9,
     0xD1, 0x7E, 0x0D, 0xFC, 0x50, 0x8A, 0xB6, 0x62, 0xF5, 0x0A, 0xF8,
     0xDC, 0x03, 0x3C, 0x0C, 0x39, 0xF1, 0xB8, 0xF3, 0x3D, 0xF2, 0xD5,
     0x97, 0x66, 0x81, 0x32, 0xA0, 0x00, 0x06, 0xCE, 0xF6, 0xEA, 0xB7,
     0x17, 0xF7, 0x8C, 0x79, 0xD6, 0xA7, 0xBF, 0x8B, 0x3F, 0x1F, 0x53,
     0x63, 0x75, 0x35, 0x2C, 0x60, 0xFD, 0x27, 0xD3, 0x94, 0xA5, 0x7C,
     0xA1, 0x05, 0x58, 0x2D, 0xBD, 0xD9, 0xC7, 0xAF, 0x6B, 0x54, 0x0B,
     0xE0, 0x38, 0x04, 0xC8, 0x9D, 0xE7, 0x14, 0xB1, 0x87, 0x9C, 0xDF,
     0x6F, 0xF9, 0xDA, 0x2A, 0xC4, 0x59, 0x16, 0x74, 0x91, 0xAB, 0x26,
     0x61, 0x76, 0x34, 0x2B, 0xAD, 0x99, 0xFB, 0x72, 0xEC, 0x33, 0x12,
     0xDE, 0x98, 0x3B, 0xC0, 0x9B, 0x3E, 0x18, 0x10, 0x3A, 0x56, 0xE1,
     0x77, 0xC9, 0x1E, 0x9E, 0x95, 0xA3, 0x90, 0x19, 0xA8, 0x6C, 0x09,
     0xD0, 0xF0, 0x86};

static uint8_t MULx(uint8_t V, uint8_t c)
{
    if (V & 0x80)
        return ((V << 1) ^ c);
    else
        return (V << 1);
}

static uint8_t MULxPOW(uint8_t V, uint8_t i, uint8_t c)
{
    if (i == 0)
        return V;
    else
        return MULx(MULxPOW(V, i - 1, c), c);
}

static uint32_t MULalpha(uint8_t c)
{
    return ((((uint32_t)MULxPOW(c, 23, 0xa9)) << 24) | (((uint32_t)MULxPOW(c, 245, 0xa9)) << 16) | (((uint32_t)MULxPOW(c, 48, 0xa9)) << 8) | (((uint32_t)MULxPOW(c, 239, 0xa9))));
}

static uint32_t DIValpha(uint8_t c)
{
    return ((((uint32_t)MULxPOW(c, 16, 0xa9)) << 24) | (((uint32_t)MULxPOW(c, 39, 0xa9)) << 16) | (((uint32_t)MULxPOW(c, 6, 0xa9)) << 8) | (((uint32_t)MULxPOW(c, 64, 0xa9))));
}

static uint32_t S1(uint32_t w)
{
    uint8_t r0 = 0, r1 = 0, r2 = 0, r3 = 0;
    uint8_t srw0 = SR[(uint8_t)((w >> 24) & 0xff)];
    uint8_t srw1 = SR[(uint8_t)((w >> 16) & 0xff)];
    uint8_t srw2 = SR[(uint8_t)((w >> 8) & 0xff)];
    uint8_t srw3 = SR[(uint8_t)((w)&0xff)];
    r0 = ((MULx(srw0, 0x1b)) ^ (srw1) ^ (srw2) ^ ((MULx(srw3, 0x1b)) ^ srw3));
    r1 = (((MULx(srw0, 0x1b)) ^ srw0) ^ (MULx(srw1, 0x1b)) ^ (srw2) ^ (srw3));
    r2 = ((srw0) ^ ((MULx(srw1, 0x1b)) ^ srw1) ^ (MULx(srw2, 0x1b)) ^ (srw3));
    r3 = ((srw0) ^ (srw1) ^ ((MULx(srw2, 0x1b)) ^ srw2) ^ (MULx(srw3, 0x1b)));
    return ((((uint32_t)r0) << 24) | (((uint32_t)r1) << 16) | (((uint32_t)r2) << 8) | (((uint32_t)r3)));
}

static uint32_t S2(uint32_t w)
{
    uint8_t r0 = 0, r1 = 0, r2 = 0, r3 = 0;
    uint8_t sqw0 = SQ[(uint8_t)((w >> 24) & 0xff)];
    uint8_t sqw1 = SQ[(uint8_t)((w >> 16) & 0xff)];
    uint8_t sqw2 = SQ[(uint8_t)((w >> 8) & 0xff)];
    uint8_t sqw3 = SQ[(uint8_t)((w)&0xff)];
    r0 = ((MULx(sqw0, 0x69)) ^ (sqw1) ^ (sqw2) ^ ((MULx(sqw3, 0x69)) ^ sqw3));
    r1 = (((MULx(sqw0, 0x69)) ^ sqw0) ^ (MULx(sqw1, 0x69)) ^ (sqw2) ^ (sqw3));
    r2 = ((sqw0) ^ ((MULx(sqw1, 0x69)) ^ sqw1) ^ (MULx(sqw2, 0x69)) ^ (sqw3));
    r3 = ((sqw0) ^ (sqw1) ^ ((MULx(sqw2, 0x69)) ^ sqw2) ^ (MULx(sqw3, 0x69)));
    return ((((uint32_t)r0) << 24) | (((uint32_t)r1) << 16) | (((uint32_t)r2) << 8) | (((uint32_t)r3)));
}

static void ClockLFSRInitializationMode(uint32_t F)
{
    uint32_t v = (((LFSR_S0 << 8) & 0xffffff00) ^ (MULalpha((uint8_t)((LFSR_S0 >> 24) & 0xff))) ^ (LFSR_S2) ^ ((LFSR_S11 >> 8) & 0x00ffffff) ^ (DIValpha((uint8_t)((LFSR_S11)&0xff))) ^ (F));
    LFSR_S0 = LFSR_S1;
    LFSR_S1 = LFSR_S2;
    LFSR_S2 = LFSR_S3;
    LFSR_S3 = LFSR_S4;
    LFSR_S4 = LFSR_S5;
    LFSR_S5 = LFSR_S6;
    LFSR_S6 = LFSR_S7;
    LFSR_S7 = LFSR_S8;
    LFSR_S8 = LFSR_S9;
    LFSR_S9 = LFSR_S10;
    LFSR_S10 = LFSR_S11;
    LFSR_S11 = LFSR_S12;
    LFSR_S12 = LFSR_S13;
    LFSR_S13 = LFSR_S14;
    LFSR_S14 = LFSR_S15;
    LFSR_S15 = v;
}

static void ClockLFSRKeyStreamMode()
{
    uint32_t v = (((LFSR_S0 << 8) & 0xffffff00) ^ (MULalpha((uint8_t)((LFSR_S0 >> 24) & 0xff))) ^ (LFSR_S2) ^ ((LFSR_S11 >> 8) & 0x00ffffff) ^ (DIValpha((uint8_t)((LFSR_S11)&0xff))));
    LFSR_S0 = LFSR_S1;
    LFSR_S1 = LFSR_S2;
    LFSR_S2 = LFSR_S3;
    LFSR_S3 = LFSR_S4;
    LFSR_S4 = LFSR_S5;
    LFSR_S5 = LFSR_S6;
    LFSR_S6 = LFSR_S7;
    LFSR_S7 = LFSR_S8;
    LFSR_S8 = LFSR_S9;
    LFSR_S9 = LFSR_S10;
    LFSR_S10 = LFSR_S11;
    LFSR_S11 = LFSR_S12;
    LFSR_S12 = LFSR_S13;
    LFSR_S13 = LFSR_S14;
    LFSR_S14 = LFSR_S15;
    LFSR_S15 = v;
}

static uint32_t ClockFSM()
{
    uint32_t F = ((LFSR_S15 + FSM_R1) & 0xffffffff) ^ FSM_R2;
    uint32_t r = (FSM_R2 + (FSM_R3 ^ LFSR_S5)) & 0xffffffff;
    FSM_R3 = S2(FSM_R2);
    FSM_R2 = S1(FSM_R1);
    FSM_R1 = r;
    return F;
}

void Snow3G::Initialize(uint32_t *pKey, uint32_t* pIv)
{
    uint8_t i = 0;
    uint32_t F = 0x0;
    LFSR_S15 = pKey[3] ^ pIv[0];
    LFSR_S14 = pKey[2];
    LFSR_S13 = pKey[1];
    LFSR_S12 = pKey[0] ^ pIv[1];
    LFSR_S11 = pKey[3] ^ 0xffffffff;
    LFSR_S10 = pKey[2] ^ 0xffffffff ^ pIv[2];
    LFSR_S9 = pKey[1] ^ 0xffffffff ^ pIv[3];
    LFSR_S8 = pKey[0] ^ 0xffffffff;
    LFSR_S7 = pKey[3];
    LFSR_S6 = pKey[2];
    LFSR_S5 = pKey[1];
    LFSR_S4 = pKey[0];
    LFSR_S3 = pKey[3] ^ 0xffffffff;
    LFSR_S2 = pKey[2] ^ 0xffffffff;
    LFSR_S1 = pKey[1] ^ 0xffffffff;
    LFSR_S0 = pKey[0] ^ 0xffffffff;
    FSM_R1 = 0x0;
    FSM_R2 = 0x0;
    FSM_R3 = 0x0;
    for (i = 0; i < 32; i++)
    {
        F = ClockFSM();
        ClockLFSRInitializationMode(F);
    }
}

void Snow3G::GenerateKeyStream(uint32_t *pKeyStream, uint32_t nKeyStream)
{
    uint32_t t = 0;
    uint32_t F = 0x0;
    ClockFSM();
    ClockLFSRKeyStreamMode();
    for (t = 0; t < nKeyStream; t++)
    {
        F = ClockFSM();
        pKeyStream[t] = F ^ LFSR_S0;
        ClockLFSRKeyStreamMode();
    }
}