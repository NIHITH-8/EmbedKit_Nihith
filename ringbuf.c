#include <stdio.h>
#include <stdint.h>

#define SIZE 8

uint8_t buffer[SIZE];
uint8_t head = 0,tail = 0,count = 0;

int write_data(uint8_t data)
{
    if(count == SIZE)
    {
        printf("[WRITE] 0x%02X -> FAIL (buffer full)\n", data);
        return -1;
    }

    buffer[head] = data;

    /* SIZE is power of 2, so &7 works like %8 */
    head = (head + 1) & 7;

    count++;

    if(count == SIZE)
        printf("[WRITE] 0x%02X -> OK (count=%d) FULL\n", data, count);
    else
        printf("[WRITE] 0x%02X -> OK (count=%d)\n", data, count);

    return 0;
}

int read_data(uint8_t *data)
{
    if(count == 0)
    {
        printf("[READ] (empty) -> FAIL (buffer empty)\n");
        return -1;
    }

    *data = buffer[tail];

    tail = (tail + 1) & 7;

    count--;

    printf("[READ] -> 0x%02X (count=%d)\n", *data, count);

    return 0;
}

int main()
{
    uint8_t data;

    write_data(0x41);
    write_data(0x42);
    write_data(0x43);
    write_data(0x44);
    write_data(0x45);
    write_data(0x46);
    write_data(0x47);
    write_data(0x48);

    write_data(0x99);

    read_data(&data);
    read_data(&data);
    read_data(&data);

    write_data(0x49);
    write_data(0x4A);
    write_data(0x4B);

    while(count)
    {
        read_data(&data);
    }

    read_data(&data);

    return 0;
}
