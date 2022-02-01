#include <stdio.h>
#include <ctype.h>
#include <time.h>

main(ac, av) 
    int ac;
    char **av;
{
    FILE *fp;
    char c;
    char line[80];
    char word[80];
    char *lyric;
    char **lyrics;
    int i = 0;
    int len = 0;
    int lines = 0;
    int prob = 5;
    int width = 40;

    srand((unsigned)time(NULL));

    if (ac > 1)
    {
        if ((fp = fopen(av[1], "r")) == NULL)
        {
            printf("ogrify: can't open %s\n", *av);
        }
        else
        {
            lyrics = (char **)malloc(1);
            while (fgets(line, 80, fp) != NULL)
            {
                len = strlen(line);
                if (len)
                {
                    for (i = 0; i < len; i++)
                    {
                        line[i] = toupper(line[i]);
                    }
                    line[len - 1] = ' ';
                    lyric = (char *)malloc((len + 1) * sizeof(char));
                    strcpy(lyric, line);
                    lyrics = (char **)realloc(lyrics, ++lines * sizeof(char *));
                    lyrics[lines - 1] = lyric;
                }
            }
        }
    }

    if (ac > 2)
    {
        prob = atoi(av[2]);
    }

    i = len = 0;
    while ((c = getc(stdin)) != EOF)
    {
        if (isspace(c))
        {
            if (word[0] == '\0')
            {
                continue;
            }

            if (lines && rand() % 100 < prob)
            {
                lyric = lyrics[rand() % lines];
            }
            else
            {
                word[i++] = ' ';
                word[i++] = '\0';
                lyric = word;
            }

            len += strlen(lyric);

            if (len > width)
            {
                puts(NULL);
                len = strlen(lyric);
            }

            if (lyric[0] != ' ')
            {
                fputs(lyric, stdout);
            }

            i = 0;
            word[0] = '\0';
        }
        else if (ispunct(c))
        {
            continue;
        }
        else
        {
            word[i++] = toupper(c);
        }
    }

    puts(NULL);
}
