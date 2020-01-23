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


/*\
 *  Define the flags used.
 *
 *  This is upwards compatible. Programs using this interface will still be
 *  able to connect to later versions of this file. Other flags will be
 *  added when needed.
\*/

#define ROTATE_RIGHT_FLAG	1

/*\
 *  This function rotates rotar by rotor. NOTE that rotar contains the
 *  rotated contents after running this function.
\*/

void rotate (int rotor, char *rotar, char flags)
{
	int i;
	
	if (!(flags & ROTATE_RIGHT_FLAG)) {
		/* Instead of rotate right, rotate left. */
		rotor = -rotor;
	}
	
	/* Make sure that rotor-values over 127 don't cause problems. */
	rotor %= 26;
	
	/* Convert negative rotor values to a positive equivalent. */
	if (rotor < 0) {
		rotor += 26;
	}
	
	for (i = 0; rotar[i]; i++) {
		if ( (rotar[i] >= 65) && (rotar[i] <= 90) ) {
			rotar[i] -= 65;
			rotar[i] += rotor;
			rotar[i] %= 26;
			rotar[i] += 65;
		}
		
		if ( (rotar[i] >= 97) && (rotar[i] <= 122) ) {
			rotar[i] -= 97;
			rotar[i] += rotor;
			rotar[i] %= 26;
			rotar[i] += 97;
		}
	}
}
