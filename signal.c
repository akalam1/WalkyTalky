#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int numofctrlzs;
int numofctrlcs;
int thispid;

void ctrlc()
{
    if (numofctrlcs == 5)
    {
        raise(SIGHUP);
    }
    printf("OOOOOWWWWWWW!!!!  STOP hitting CTRL-C!!! %i %i \n\n", thispid, numofctrlcs);
    numofctrlcs++;
    sleep(1);
}

void ctrlz()
{
    if (numofctrlzs == 3)
    {
        printf("OK, I will wait until you need me again\n");
        numofctrlzs = 0;
        raise(SIGSTOP);
    }
    else
    {
        printf("I'm NOT waiting, I WON'T be put in the BACKGROUND %i %i\n\n", thispid, numofctrlzs);
        numofctrlzs++;
        sleep(1);
    }
}

void continueit()
{
    printf("thank you for waking me up, here we go again with process %i\n\n", thispid);
    sleep(1);
}

void simplekill()
{
    printf("Please try a Silver Bullet Next Time....I REFUSE TO DIE %i\n\n", thispid);
    sleep(1);
}

int main()
{
    numofctrlzs = 0;
    numofctrlcs = 0;
    thispid = getpid();
    signal(SIGINT, ctrlc);
    signal(SIGTSTP, ctrlz);
    signal(SIGCONT, continueit);
    signal(SIGTERM, simplekill);
    printf("hi class I\'m process %i....and I say Rich is a NERD!!!!!\n\n", thispid);

    while (1)
    {
        printf("Rich is a NERD, hahahahahahahahaha!!!\n\n");
        sleep(2);
    }
}
