#!/bin/sh

# Generates version.c
#
# Copyright (c) 1990 Chelsea Dyerman
# University of California, Berkeley (XCF)

if[!-f version.c]
    then generation = 0
    else
    generation =
        `sed - n 's/^const char \*generation = \"\(.*\)\";/\1/p' <
        version.c ` if[!"$generation"] ;
then generation = 0;

fi fi
    generation = `expr $generation + 1 `
    creation =
    `date | awk
    '{if (NF == 6) { print $1 " "  $2 " " $3 " "  $6 " at " $4 " " $5 } else { print $1 " "  $2 " " $3 " " $7 " at " $4 " " $5 " " $6 }}'
    ` cat > version.c << EOF
/*
 * Copyright (c) 1990 Chelsea Dyerman
 * University of California, Berkeley (XCF)
 *
 * Some parts of this code -- in particular the dictionary based compression
 * code is Copyright 1995 by Dragon's Eye Productions
 *
 */
/*
 * This file is generated by mkversion.sh. Any changes made will go away.
 */
#include "patchlevel.h"
#include "params.h"
#include "interface.h"
#include "externs.h"
    const char *generation = "$generation";
const char *creation = "$creation";
const char *version = PATCHLEVEL;

const char *infotext[] = {

    CCYAN "ProtoMUCK " PROTOBASE " " CCRIMSON "-- " CCRIMSON VERSION,
    " ",
    CCYAN "Based on the original code written by these programmers:",
    "  " CAQUA
        "David Applegate    James Aspnes    Timothy Freeman    Bennet Yee",
    " ",
    CCYAN "Others who have done major coding work along the way:",
    "  " CAQUA "Lachesis, ChupChups, FireFoot, Russ 'Random' Smith, Dr. Cat,",
    "  " CAQUA "Revar, Points, Loki, PakRat, Nodaitsu",
    " ",
    CWHITE "ProtoMuck is derived from TinyMUCK, which was itself an extension",
    CWHITE
        "of TinyMUD.  Proto is an updated version of the NeonMUCK code base,",
    CWHITE
        "which originaly came from the FuzzBall distribution, by Foxen/Revar,",
    CWHITE "of TinyMUCK.",
    " ",
    CGREEN "And, here is the list of the programmers for ProtoMUCK:",
    CFOREST "  Moose and Akari: protomuck@bigfoot.com",
    " ",
    CWHITE "Thanks are also due towards the multiple people who had also",
    CWHITE
        "contributed ideas for the MUCK as we worked on it, and even tried to",
    CWHITE "help us out along the way.",
    CCYAN "Feel free to check ProtoMUCK's webpage at the following address:",
    CAQUA "http://protomuck.sourceforge.net/",
    " ",
    CBLUE "The recommended client by us for any mu* server is BeipMU*.",
    CBLUE "http://beipmu.nefastis.net for more information.",
    0,
};


void
do_credits(dbref player)
{
    int i;

    for (i = 0; infotext[i]; i++) {
        anotify_nolisten2(player, infotext[i]);
    }
}

EOF exit 0
