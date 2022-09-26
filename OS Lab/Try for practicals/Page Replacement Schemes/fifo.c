#include <stdio.h>

int main(int argc, char const *argv[])
{
    int no_pages, no_frames;
    printf("\nEnter no. of pages:");
    scanf(" %d", &no_pages);
    int refstr[no_pages];
    printf("\nEnter no. of frames:");
    scanf(" %d", &no_frames);
    int frames[no_frames];
    printf("\nEnter pages:");
    for (int i = 0; i < no_pages; i++)
    {
        scanf(" %d", &refstr[i]);
    }
    for (int i = 0; i < no_frames; i++)
    {
        frames[i] = -1;
    }
    int faults = 0;
    for (int i = 0; i < no_pages; i++)
    {
        int flag = 0;
        for (int j = 0; j < no_frames; j++)
        {
            if (refstr[i] == frames[j])
            {
                flag++;
                faults--;
            }
        }
        faults++;
        if (faults <= no_frames && flag == 0)
        {
            frames[i] = refstr[i];
        }
        else if (flag == 0)
        {
            frames[(faults - 1) % no_frames] = refstr[i];
        }
        printf("\n");
        for (int n = 0; n < no_frames; n++)
        {
            printf("%d\t", frames[n]);
        }
    }
    printf("\n\t%d", faults);
    return 0;
}
