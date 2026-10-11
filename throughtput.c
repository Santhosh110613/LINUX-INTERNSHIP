
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

    printf("====================================\n");
    printf("     BINDER THROUGHPUT TEST\n");
    printf("====================================\n");

    printf("Starting Emulator...\n");

    system("~/Android/Sdk/emulator/emulator -avd Pixel_6 > /dev/null 2>&1 &");

    printf("Waiting for Emulator...\n");

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

    printf("\nRunning Transactions...\n\n");

    int transactions = 5;

    clock_gettime(CLOCK_MONOTONIC, &start);

    double total = 0;

    for (int i = 1; i <= transactions; i++)
    {
        struct timespec ts1, ts2;

        clock_gettime(CLOCK_MONOTONIC, &ts1);

        system("adb shell service check activity > /dev/null");

        clock_gettime(CLOCK_MONOTONIC, &ts2);

        double t = diff_ms(ts1, ts2);

        total += t;

        printf("Transaction %2d : %.3f ms\n", i, t);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double total_ms = diff_ms(start, end);

    double throughput = (transactions * 1000.0) / total_ms;

    printf("\n------------------------------------\n");
    printf("Total Transactions : %d\n", transactions);
    printf("Total Time         : %.2f ms\n", total_ms);
    printf("Throughput         : %.2f Transactions/sec\n", throughput);
    printf("------------------------------------\n");

    return 0;
}
