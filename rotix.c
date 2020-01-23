/*\
 *	Rotix - A program to generate rotational obfuscations
 *	Copyright (C) 2001  Sjoerd Hemminga <sjoerd@huiswerkservice.nl>
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful, but
 *	WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *	General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 *	USA
\*/


/* Rotix includes. */
#include "rot.h"
#include "help.h"

/* System includes. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef NO_GETOPT_LONG
#include <unistd.h>
#define getopt_long(a, b, c, d, e) getopt(a, b, c)
#else
#include <getopt.h>
#endif

/* I18N */
#ifdef I18N
#include <libintl.h>
#define _(String) gettext (String)
#else
#define _(String) String
#endif

/* Defining the flags. */
#define ROT_AUTO		1
#define ROT_INPUT_FILE		2
#define ROT_TEXT		4
#define ROT_OUTPUT_FILE		8
#define ROT_STDIN		16

int main (int argc, char **argv)
{
	int i = 1, rotor = 13, option = 0;
	char *arg = NULL, option_flags = 0, rotate_flags = 0;
	
#ifndef NO_GETOPT_LONG
	/* The struct used to determine which options are called. */
	static struct option rotix_options[] = {
		{ "file",	1,	NULL,	'f' },
		{ "rot",	1,	NULL,	'r' },
		{ "auto",	0,	NULL,	'a' },
		{ "output",	1,	NULL,	'o' },
		{ "text",	1,	NULL,	't' },
		{ "left",	0,	NULL,	'L' },
		{ "right",	0,	NULL,	'R' },
		{ "help",	0,	NULL,	'h' },
		{ "version",	0,	NULL,	'v' },
		{ NULL,		0,	NULL,	 0  }
	};
#endif


	/* A 2-bit character array, to obfuscate a character */
	char rotme[2];
	
	FILE *ifp = NULL;
	FILE *ofp = NULL;

#ifdef I18N
	/* Initialize I18n */
	setlocale (LC_MESSAGES, "");
	bindtextdomain (PACKAGE, LOCALEDIR);
	textdomain (PACKAGE);
#endif

	/* Initialization of some variables */	
	rotme[1] = '\0';
	rotate_flags |= ROTATE_RIGHT_FLAG;

/* Parsing options. */
	while (1) {
		option = getopt_long (argc, argv, "f:r:ao:t:LRhv", rotix_options, NULL);
		if (option == -1) break;
		
		switch (option) {
			case '?':
				display_help ();
				exit (1);
			case ':':

			/* Missing argument. */
				display_help ();
				exit (1);
			case 'v':
				display_version ();
				exit (0);
			case 'h':
				display_help ();
				exit (0);

			/* Options that affect the running of Rotix. */
			
			/* Direction right */
			case 'R':
				rotate_flags |= ROTATE_RIGHT_FLAG;
			break;
			
			case 'L':
				if (rotate_flags & ROTATE_RIGHT_FLAG) {
					rotate_flags -= 1;
				}
			break;

			/* Input file */
			case 'f':
				if (strcmp (optarg, "-") == 0) {
					ifp = stdin;
					option_flags |= ROT_STDIN;
					
					if (option_flags & ROT_TEXT) {
						fprintf (stderr, _("rotix: you cannot specify both an inputfile and a text\n"));
						exit (1);
					}
				} else {
					ifp = fopen (optarg, "r");
					option_flags |= ROT_INPUT_FILE;

					if (ifp == NULL) {
						fprintf (stderr, _("rotix: error opening file %s for reading\n"), optarg);
						exit (1);
					} else if (option_flags & ROT_TEXT) {
						fprintf (stderr, _("rotix: you cannot specify both an inputfile and a text\n"));
						exit (1);
					}
				}
			break;

			/* Rotate number */
			case 'r':
				if (strcmp (optarg, "auto") == 0) {
					option_flags |= ROT_AUTO;
				} else if ( !sscanf (optarg, "%9i", &rotor) ) {
					display_help ();
					exit (1);
				}
			break;
			
			/* Automated rotating */
			case 'a':
				option_flags |= ROT_AUTO;
			break;

			/* Output file */
			case 'o':
				if (strcmp (optarg, "-") == 0) {
					ofp = stdout;
				} else {
					ofp = fopen (optarg, "a");

					option_flags |= ROT_OUTPUT_FILE;
					
					if (ofp == NULL) {
						fprintf (stderr, _("rotix: error opening file %s for writing\n"), optarg);
						exit (1);
					}
				}
			break;

			/* Text */
			case 't':
				if ((option_flags & ROT_INPUT_FILE) || (option_flags & ROT_STDIN)) {
					fprintf (stderr, _("rotix: you cannot specify both an inputfile and a text\n"));
					exit (1);
				}
				
				arg = (char *)malloc (strlen (optarg) + 1);
				if (arg == NULL) {
					fprintf (stderr, _("rotix: not enough memory\n"));
					exit (1);
				}
				strcpy (arg, optarg);
				option_flags |= ROT_TEXT;
			break;
			
			/* Unrecognized option. NOTE: this should never happen, since case '?' should catch this one */
			default:
				fprintf (stderr, _("rotix: fixme\n"));
				exit (2);
		}
	}

	if (!(option_flags & ROT_INPUT_FILE) && !(option_flags & ROT_TEXT)) {
		option_flags |= ROT_STDIN;
		ifp = stdin;
	}
	
	if (ofp == NULL) {
		ofp = stdout;
	}
	
/*\
 *  End of option-parsing.
\*/
	if (option_flags & ROT_TEXT) {
		if (option_flags & ROT_AUTO) {
			for (i = 1; i < 26; i++) {
				rotate (1, arg, rotate_flags);
				fprintf (ofp, "ROT-%02i: %s\n", i, arg);
			}
			
			free (arg);
		} else {
			rotate (rotor, arg, rotate_flags);
			fprintf (ofp, "%s\n", arg);
		}
	} else if (option_flags & ROT_AUTO) {
		/* Goodie, goodie, automated (de-)obfuscation of a file! */
		
		if (ifp == stdin) {
			/* Very dirty hack to get this functioning without using any extra variables */
			ifp = tmpfile ();
			
			if (ifp == NULL) {
				fprintf (stderr, _("rotix: error creating temporary file\n"));
				exit (1);
			}
			
			arg = (char *)malloc (265);
			if (arg == NULL) {
				fprintf (stderr, _("rotix: not enough memory\n"));
				exit (1);
			}
			
			while ( !feof (stdin) ) {
				strcpy (arg, "");
				rotme[0] = '\0';
				
				fscanf (stdin, "%255[^\n]s", arg);
				fprintf (ifp, "%s", arg);
				
				if (feof (stdin)) break;
				
				rotme[0] = fgetc (stdin);
				fprintf (ifp, "%s", rotme);
			}
			rewind (ifp);
		}
		
		arg = (char *)malloc (256);
		if (arg == NULL) {
			fprintf (stderr, _("rotix: not enough memory\n"));
			exit (1);
		}

		for (i = 1; i < 26; i++) {
			fprintf (ofp, "\nROT-%02i:\n=======\n\n", i);
			
			while ( !feof (ifp) ) {
				strcpy (arg, "");
				rotme[0] = '\0';

				fscanf (ifp, "%255[^\n]s", arg);
				rotate (i, arg, rotate_flags);
				fprintf (ofp, "%s", arg);

				if (feof (ifp)) break;

				rotme[0] = fgetc (ifp);
				rotate (i, rotme, rotate_flags);
				fprintf (ofp, "%s", rotme);
			}
			rewind (ifp);
		}
		free (arg);
	} else {
		arg = (char *)malloc (256);
		if (arg == NULL) {
			fprintf (stderr, _("rotix: not enough memory\n"));
			exit (1);
		}

		while ( !feof (ifp) ) {
			strcpy (arg, "");
			rotme[0] = '\0';

			fscanf (ifp, "%255[^\n]s", arg);
			rotate (rotor, arg, rotate_flags);
			fprintf (ofp, "%s", arg);

			if (feof (ifp)) break;

			rotme[0] = fgetc (ifp);
			rotate (rotor, rotme, rotate_flags);
			fprintf (ofp, "%s", rotme);
		}

		free (arg);
	}

	fflush (NULL);

	if (option_flags & ROT_INPUT_FILE) {
		fclose (ifp);
	}
	
	if (option_flags & ROT_OUTPUT_FILE) {
		fclose (ofp);
	}		
	
	return (0);
}
