#pragma once

bool waitForData(int fd, int timeSec, int timeMilis)
{
    bool isDataReady = false;
    struct timeval timeout;

    fd_set set;
    FD_ZERO(&set);

    timeout.tv_sec = timeSec;
    timeout.tv_usec = (timeMilis * 1000);

    FD_SET(fd, &set);

    int res = select(fd+1, &set, NULL, NULL, &timeout );

    if(res > 0)
    {

        if(FD_ISSET(fd, &set))
        {
            isDataReady = true;
        }
    }

    return isDataReady;
}
