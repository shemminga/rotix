/*\
 *	Rotix - A program to generate rotational obfuscations
 *	Copyright (C) 2001  Sjoerd Hemminga
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

#include <stdio.h>

/*\
 * I18N
\*/

#include <libintl.h>
#define _(String) gettext (String)

/*\
 *  This function displays the help-information.
\*/

void display_help ()
{
	printf (_("Usage:\n"));
	printf (_("       rotix [ -f <file> ] [ -o <file> ] [ -r <value> ]\n"));
	printf (_("       rotix -t <text> [ -o <file> ] [ -r <value> ]\n\n"));

	printf (_("-f <file>  specify input-file\n"));
	printf (_("-o <file>  specify output-file\n"));
	printf (_("-r <value> specify the value to rotate with\n"));
	printf (_("-a         use all sane values to rotate with\n"));
	printf (_("-R         rotate right\n"));
	printf (_("-L         rotate left\n"));
	printf (_("-t <text>  specify the text to rotate\n\n"));
	
	printf (_("For complete documentation:\n"));
	printf ("man rotix\n\n");

	printf (_("Report bugs to: sjoerd@huiswerkservice.nl\n"));
}

void display_version ()
{
	printf (_("Rotix version 0.82\n\n"));

	printf ("Copyright (C) 2001 Sjoerd Hemminga <sjoerd@huiswerkservice.nl>\n\n");

	printf (_("Rotix is licensed under the GNU General Public License. See the file COPYING\n"
		  "for details.\n"));
}
