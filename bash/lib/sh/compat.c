/* compat.c - functions for backwards compatibility with previous versions */

/* Copyright (C) 2023 Free Software Foundation, Inc.

   This file is part of GNU Bash, the Bourne Again SHell.

   Bash is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Bash is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Bash.  If not, see <http://www.gnu.org/licenses/>.
*/
   
#include <config.h>

#if defined (HAVE_UNISTD_H)
#  include <unistd.h>
#endif

#include <bashtypes.h>
#include <shell.h>

/* For backwards compatibility with existing loadable builtins. */
int
legal_number (const char *string, intmax_t *result)
{
  return (valid_number (string, result));
}

int
legal_identifier (const char *string)
{
  return (valid_identifier (string));
}

int
legal_alias_name (const char *string, int flags)
{
  return (valid_alias_name (string, flags));
}

int
compat_init (void)
{
  return 0;
}
