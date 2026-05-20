#include "audio_recorder.h"
#include "stm32g4_sys.h"
#include <string.h>

static uint16_t audio_buffer[AUDIO_SAMPLE_COUNT];
static bool audio_finished = false;

static void AudioRecorder_DWT_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    DWT->CYCCNT = 0;
}

static void AudioRecorder_WaitCycles(uint32_t nb_cycles)
{
    uint32_t start = DWT->CYCCNT;
    while ((DWT->CYCCNT - start) < nb_cycles)
    {
    }
}

static uint8_t AudioRecorder_Convert12bTo8b(uint16_t sample)
{
    return (uint8_t)(sample >> 4);
}

void AudioRecorder_Init(void)
{
    memset(audio_buffer, 0, sizeof(audio_buffer));
    audio_finished = false;
    AudioRecorder_DWT_Init();
}

AudioStatus_t AudioRecorder_Record(adc_id_e channel)
{
    uint32_t i;
    uint32_t cycles_per_sample = SystemCoreClock / AUDIO_SAMPLE_RATE_HZ;

    audio_finished = false;

    for (i = 0; i < AUDIO_SAMPLE_COUNT; i++)
    {
        audio_buffer[i] = BSP_ADC_getValue(channel);
        AudioRecorder_WaitCycles(cycles_per_sample);
    }

    audio_finished = true;
    return AUDIO_OK;
}

AudioStatus_t AudioRecorder_SaveToFlash(void)
{
    uint32_t i;
    uint32_t flash_index = 0;
    uint64_t packed_data;
    uint8_t b0, b1, b2, b3, b4, b5, b6, b7;

    BSP_FLASH_erase_page();

    for (i = 0; i < AUDIO_SAMPLE_COUNT; i += 8)
    {
        b0 = AudioRecorder_Convert12bTo8b(audio_buffer[i + 0]);
        b1 = AudioRecorder_Convert12bTo8b(audio_buffer[i + 1]);
        b2 = AudioRecorder_Convert12bTo8b(audio_buffer[i + 2]);
        b3 = AudioRecorder_Convert12bTo8b(audio_buffer[i + 3]);
        b4 = AudioRecorder_Convert12bTo8b(audio_buffer[i + 4]);
        b5 = AudioRecorder_Convert12bTo8b(audio_buffer[i + 5]);
        b6 = AudioRecorder_Convert12bTo8b(audio_buffer[i + 6]);
        b7 = AudioRecorder_Convert12bTo8b(audio_buffer[i + 7]);

        packed_data =  //on doit écrire par bout de 64bits
              ((uint64_t)b0)
            | ((uint64_t)b1 << 8)
            | ((uint64_t)b2 << 16)
            | ((uint64_t)b3 << 24)
            | ((uint64_t)b4 << 32)
            | ((uint64_t)b5 << 40)
            | ((uint64_t)b6 << 48)
            | ((uint64_t)b7 << 56);

//        printf("Idx %lu : %u %u %u %u %u %u %u %u\r\n",
//               flash_index, b0,b1,b2,b3,b4,b5,b6,b7);

        BSP_FLASH_write_doubleword_fast(flash_index, packed_data);
        flash_index++;
    }

    return AUDIO_OK;
}

bool AudioRecorder_IsFinished(void)
{
    return audio_finished;
}

uint16_t AudioRecorder_GetSample(uint32_t index)
{
    if (index >= AUDIO_SAMPLE_COUNT)
    {
        return 0;
    }

    return audio_buffer[index];
}

uint32_t AudioRecorder_GetSampleCount(void)
{
    return AUDIO_SAMPLE_COUNT;
}

const uint16_t *AudioRecorder_GetBuffer(void)
{
    return audio_buffer;
}
