#ifndef Hilly.h
char *timestamp()
{
    time_t t = time(NULL);
    // time_t msec = time(NULL) * 1000;
    // printf("%llu", msec);
    return ctime(&t);
}
unsigned long long timestamp_sec()
{
    time_t t = time(NULL);
    time_t msec = time(NULL) * 1000;
    return msec;
}
char *timestamp_msec(unsigned long long msec)
{
    time_t t = (time_t)(msec / 1000);
    return ctime(&t);
}
#define Hilly.h
#endif