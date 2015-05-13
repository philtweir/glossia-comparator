#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int s;

void clearerrno_()
{
    errno = 0;
}

int geterrno_()
{
    return errno;
}

void printerr_()
{
    printf("ERR: %s\n", strerror(errno));
}

int make_connection_()
{
    s = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un perc;
    perc.sun_family  = AF_UNIX;
    strcpy(perc.sun_path, "percentage.sock");
    connect(s, (struct sockaddr *)&perc, sizeof(perc));

    return errno;
}

int output_percentage_(double p)
{
    char percstr[100];

    sprintf(percstr, "%lf\n", p);
    clearerrno_();
    printf("STR: %s\n", percstr);
    send(s, percstr, strlen(percstr), 0);
    printerr_();
    return 0;
}
