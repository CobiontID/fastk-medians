/*********************************************************************************************\
 *
 *  Example code for opening and fetching compressed profiles produced by FastK
 *
 *  Author:  Gene Myers
 *  Date  :  October, 2020
 *
 *********************************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <math.h>

#include "libfastk.h"

static char *Usage = "<source_root>[.prof] ...";

/****************************************************************************************
 *
 *  Test Stub
 *
 *****************************************************************************************/

int main(int argc, char *argv[])
{ Profile_Index *P;

  { int    i, j, k;
    int    flags[128];

    (void) flags;

    ARG_INIT("ProfMedianAll");

    j = 1;
    for (i = 1; i < argc; i++)
      if (argv[i][0] == '-')
        switch (argv[i][1])
        { default:
            ARG_FLAGS("")
            break;
        }
      else
        argv[j++] = argv[i];
    argc = j;

    if (argc < 2)
      { fprintf(stderr,"Usage: %s %s\n",Prog_Name,Usage);
        exit (1);
      }
  }

  P = Open_Profiles(argv[1]);
  if (P == NULL)
    { fprintf(stderr,"%s: Cannot open %s\n",Prog_Name,argv[1]);
      exit (1);
    }

  { int     id, reads;
    uint16 *profile;
    int     pmax, plen;

    pmax    = 20000;
    profile = Malloc(pmax*sizeof(uint16),"Profile array");
    
    reads = P->nbase[P->nparts-1];
    for (id = 1; id < reads; id++)
      { 
        plen = Fetch_Profile(P,(int64) id-1,pmax,profile);
        if (plen > pmax)
          { pmax    = 1.2*plen + 1000;
            profile = Realloc(profile,pmax*sizeof(uint16),"Profile array");
            Fetch_Profile(P,(int64) id-1,pmax,profile);
          }
        //modified to print median value instead of iterating through all kmers
        if (plen % 2 == 0)
          { printf("%i\n", (profile[plen/2 - 1] + profile[plen/2]) / 2); }
        else
          { printf("%i\n", profile[plen / 2]); }
      }
    free(profile);
  }

  Free_Profiles(P);

  Catenate(NULL,NULL,NULL,NULL);
  Numbered_Suffix(NULL,0,NULL);
  free(Prog_Name);

  exit (0);
}