/*
 * Dillo web browser
 *
 * Copyright 2024 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include "djpeg.h"
#include "dpng.h"
#include "IO/tls.h"

#include <FL/Fl.H>
#include <zlib.h>

#include <stdio.h>

static void print_libs()
{
   char buf[256];

   printf("Libraries:");

   /* FLTK only offers a single number */
   {
      int fltkver = Fl::api_version();
      int fltk_maj = fltkver / 10000;
      int fltk_min = (fltkver / 100) % 100;
      int fltk_pat = fltkver % 100;
      printf(" fltk/%d.%d.%d", fltk_maj, fltk_min, fltk_pat);
   }

   printf(" zlib/%s", zlibVersion());

#ifdef ENABLE_JPEG
   printf(" jpeg/%s", a_Jpeg_version());
#endif

#ifdef ENABLE_PNG
   printf(" png/%s", a_Png_version());
#endif

#ifdef ENABLE_TLS
   /* TLS prints the name/version format, as it determines which SSL
    * library is in use */
   printf(" %s", a_Tls_version(buf, 256));
#endif

   printf("\n");
}

static void print_features()
{
   printf("Features:"
#ifdef ENABLE_GIF
         " +GIF"
#else
         " -GIF"
#endif
#ifdef ENABLE_JPEG
         " +JPEG"
#else
         " -JPEG"
#endif
#ifdef ENABLE_PNG
         " +PNG"
#else
         " -PNG"
#endif
#ifdef ENABLE_SVG
         " +SVG"
#else
         " -SVG"
#endif
#if !( defined(DISABLE_XEMBED) || defined(WIN32) || defined(__APPLE__) )
         " +XEMBED"
#else
         " -XEMBED"
#endif
#ifdef ENABLE_TLS
         " +TLS"
#else
         " -TLS"
#endif
         "\n");
}

void a_Version_print_info(void)
{
   printf("Dillo version " VERSION "\n");
   print_libs();
   print_features();
}
