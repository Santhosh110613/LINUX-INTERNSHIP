
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double diff_ms(struct timespec s, struct timespec e)
{
    return (e.tv_sec - s.tv_sec) * 1000.0 +
           (e.tv_nsec - s.tv_nsec) / 1000000.0;
}

int main()
{
    struct timespec start, end;
    double total = 0.0;

    printf("====================================\n");
    printf("    BINDER LATENCY TEST (Demo)\n");
    printf("====================================\n");

    printf("Starting Emulator...\n");
    system("~/Android/Sdk/emulator/emulator -avd Pixel_6 > /dev/null 2>&1 &");

    printf("Waiting for Emulator Boot...\n");
    system("adb wait-for-device");

    while (1)
    {
        FILE *fp = popen("adb shell getprop sys.boot_completed", "r");
        char out[16] = {0};

        if (fp)
        {
            fgets(out, sizeof(out), fp);
            pclose(fp);

            if (out[0] == '1')
                break;
        }

        system("sleep 1");
    }

    printf("\nEmulator Ready\n");

    printf("Checking Binder Service...\n");
    system("adb shell service check activity");

    printf("\nRunning 5 Transactions...\n\n");

    for (int i = 1; i <= 5; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);

        system("adb shell service check activity > /dev/null");

        clock_gettime(CLOCK_MONOTONIC, &end);

        double t = diff_ms(start, end);
        total += t;

        printf("Transaction %d : %.3f ms\n", i, t);
    }

    printf("\n------------------------------------\n");
    printf("Average Latency : %.3f ms\n", total / 5.0);
    printf("------------------------------------\n");

    return 0;
}
