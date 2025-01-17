#include <conio.h>
#include <string.h>
#include "ns_dpmi.h"
#include "ns_sb.h"
#include "ns_ctawe.h"
#include "ns_awe32.h"
#include "options.h"

/*  DSP defines  */
#define MPU_ACK_OK 0xfe
#define MPU_RESET_CMD 0xff
#define MPU_ENTER_UART 0x3f

static WORD wSBCBaseAddx; /* Sound Blaster base address */
static WORD wEMUBaseAddx; /* EMU8000 subsystem base address */
static WORD wMpuBaseAddx; /* MPU401 base address */

static unsigned short NoteFlags[128];

/*  macros  */
#define SBCPort(x) ((x) + wSBCBaseAddx)
#define MPUPort(x) ((x) + wMpuBaseAddx)

static SOUND_PACKET spSound =
    {
        0};

static LONG lBankSizes[MAXBANKS] =
    {
        0};

unsigned SetES(void);
#pragma aux SetES = \
    "xor eax, eax"  \
    "mov ax, es"    \
    "mov bx, ds"    \
    "mov es, bx" modify[eax ebx];

void RestoreES(unsigned num);
#pragma aux RestoreES = \
    "mov  es, ax" parm[eax];

/**********************************************************************

   Memory locked functions:

**********************************************************************/

void AWE32_NoteOff(
    int channel,
    int key,
    int velocity)

{
    unsigned temp;

    temp = SetES();
    awe32NoteOff(channel, key, velocity);
    RestoreES(temp);
    NoteFlags[key] ^= (1 << channel);
}

void AWE32_NoteOn(
    int channel,
    int key,
    int velocity)

{
    unsigned temp;

    temp = SetES();
    awe32NoteOn(channel, key, velocity);
    RestoreES(temp);
    NoteFlags[key] |= (1 << channel);
}

void AWE32_PolyAftertouch(
    int channel,
    int key,
    int pressure)

{
    unsigned temp;

    temp = SetES();
    awe32PolyKeyPressure(channel, key, pressure);
    RestoreES(temp);
}

void AWE32_ChannelAftertouch(
    int channel,
    int pressure)

{
    unsigned temp;

    temp = SetES();
    awe32ChannelPressure(channel, pressure);
    RestoreES(temp);
}

void AWE32_ControlChange(
    int channel,
    int number,
    int value)

{
    unsigned temp;
    int i;
    unsigned channelmask;

    temp = SetES();

    if (number == 0x7b)
    {
        channelmask = 1 << channel;
        for (i = 0; i < 128; i++)
        {
            if (NoteFlags[i] & channelmask)
            {
                awe32NoteOff(channel, i, 0);
                NoteFlags[i] ^= channelmask;
            }
        }
    }
    else
    {
        awe32Controller(channel, number, value);
    }
    RestoreES(temp);
}

void AWE32_ProgramChange(
    int channel,
    int program)

{
    unsigned temp;

    temp = SetES();
    awe32ProgramChange(channel, program);
    RestoreES(temp);
}

void AWE32_PitchBend(
    int channel,
    int lsb,
    int msb)

{
    unsigned temp;

    temp = SetES();
    awe32PitchBend(channel, lsb, msb);
    RestoreES(temp);
}

static void ShutdownMPU(
    void)

{
    volatile DWORD dwCount;

    for (dwCount = 0; dwCount < 0x2000; dwCount++)
        ;
    dwCount = 0x2000;
    while (dwCount && inp(MPUPort(1)) & 0x40)
        --dwCount;
    outp(MPUPort(1), MPU_RESET_CMD);
    for (dwCount = 0; dwCount < 0x2000; dwCount++)
        ;
    inp(MPUPort(0));

    for (dwCount = 0; dwCount < 0x2000; dwCount++)
        ;
    dwCount = 0x2000;
    while (dwCount && inp(MPUPort(1)) & 0x40)
        --dwCount;
    outp(MPUPort(1), MPU_RESET_CMD);
    for (dwCount = 0; dwCount < 0x2000; dwCount++)
        ;
    inp(MPUPort(0));
}

static void LoadSBK(
    void)
{
    /* use embeded preset objects */
    spSound.bank_no = 0;     /* load as Bank 0 */
    spSound.total_banks = 1; /* use 1 bank first */
    lBankSizes[0] = 0;       /* ram is not needed */

    spSound.banksizes = lBankSizes;
    awe32DefineBankSizes(&spSound);
    awe32SoundPad.SPad1 = awe32SPad1Obj;
    awe32SoundPad.SPad2 = awe32SPad2Obj;
    awe32SoundPad.SPad3 = awe32SPad3Obj;
    awe32SoundPad.SPad4 = awe32SPad4Obj;
    awe32SoundPad.SPad5 = awe32SPad5Obj;
    awe32SoundPad.SPad6 = awe32SPad6Obj;
    awe32SoundPad.SPad7 = awe32SPad7Obj;
}

int AWE32_Init(
    void)

{
    int status;
    BLASTER_CONFIG Blaster;

    wSBCBaseAddx = 0x220;
    wEMUBaseAddx = 0x620;
    wMpuBaseAddx = 0x330;

    status = BLASTER_GetCardSettings(&Blaster);
    if (status != BLASTER_Ok)
    {
        status = BLASTER_GetEnv(&Blaster);
        if (status != BLASTER_Ok)
        {
            return (AWE32_Error);
        }
    }

    wSBCBaseAddx = Blaster.Address;
    if (wSBCBaseAddx == UNDEFINED)
    {
        wSBCBaseAddx = 0x220;
    }

    wMpuBaseAddx = Blaster.Midi;
    if (wMpuBaseAddx == UNDEFINED)
    {
        wMpuBaseAddx = 0x330;
    }

    wEMUBaseAddx = Blaster.Emu;
    if (wEMUBaseAddx <= 0)
    {
        wEMUBaseAddx = wSBCBaseAddx + 0x400;
    }

    status = awe32Detect(wEMUBaseAddx);
    if (status)
    {
        return (AWE32_Error);
    }

    status = awe32InitHardware();
    if (status)
    {
        return (AWE32_Error);
    }

    status = awe32InitMIDI();
    if (status)
    {
        AWE32_Shutdown();
        return (AWE32_Error);
    }

    if (status != DPMI_Ok)
    {
        ShutdownMPU();
        awe32Terminate();
        return (AWE32_Error);
    }

    // Set the number of voices to use to 32
    awe32NumG = 32;

    awe32TotalPatchRam(&spSound);

    LoadSBK();
    awe32InitMIDI();
    awe32InitNRPN();

    memset(NoteFlags, 0, sizeof(NoteFlags));

    return (AWE32_Ok);
}

void AWE32_Shutdown(
    void)

{
    ShutdownMPU();
    awe32Terminate();
}
