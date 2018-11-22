/** \file usage.c
 */
/*
 * Copyright 2018 Andy Alt<andy400-dev@yahoo.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <stdio.h>
#include "zank.h"
#include "usage.h"

void display_version (void)
{
  printf (PACKAGE " " VERSION "\n");
  return;
}

void display_help (void)
{
  printf ("\
  -c  --connect=<ip address>    (not yet implemented)\n\
  -s, --server                  (not yet implemented)\n\
  -h, --help\n\
  -v, --version\n\
\n");
  return;
}

