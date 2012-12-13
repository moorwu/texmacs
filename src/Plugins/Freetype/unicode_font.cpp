
/******************************************************************************
* MODULE     : unicode_font.cpp
* DESCRIPTION: True Type fonts (using FreeType II)
* COPYRIGHT  : (C) 1999  Joris van der Hoeven
*******************************************************************************
* This software falls under the GNU general public license version 3 or later.
* It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
* in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
******************************************************************************/

#include "font.hpp"
#include "Freetype/free_type.hpp"
#include "Freetype/tt_file.hpp"
#include "Freetype/tt_face.hpp"
#include "analyze.hpp"
#include "converter.hpp"

#ifdef USE_FREETYPE

#define std_dpi 600
#define conv(l) ((l*dpi)/std_dpi)

/******************************************************************************
* True Type fonts
******************************************************************************/

struct unicode_font_rep: font_rep {
  string      family;
  int         dpi;
  font_metric fnm;
  font_glyphs fng;

  unicode_font_rep (string name, string family, int size, int dpi);

  void get_extents (string s, metric& ex);
  void get_xpositions (string s, SI* xpos);
  void draw_fixed (renderer ren, string s, SI x, SI y);
  font magnify (double zoom);
  glyph get_glyph (string s);
  SI get_left_correction  (string s);
  SI get_right_correction  (string s);
};

/******************************************************************************
* Initialization of main font parameters
******************************************************************************/

unicode_font_rep::unicode_font_rep (string name,
  string family2, int size2, int dpi2):
  font_rep (name), family (family2), dpi (dpi2)
{
  type= FONT_TYPE_UNICODE;
  size= size2;
  fnm = tt_font_metric (family, size, std_dpi);
  fng = tt_font_glyphs (family, size, dpi);
  if (fnm->bad_font_metric || fng->bad_font_glyphs) {
    fnm= std_font_metric (res_name, NULL, 0, -1);
    fng= std_font_glyphs (res_name, NULL, 0, -1);
    if (DEBUG_AUTO)
      cout << "TeXmacs] Font " << family << " " << size
	   << "pt at " << dpi << " dpi could not be loaded\n";
    
  }

  // get main font parameters
  metric ex;
  get_extents ("f", ex);
  y1= ex->y1;
  y2= ex->y2;
  get_extents ("p", ex);
  y1= min (y1, ex->y1);
  y2= max (y2, ex->y2);
  get_extents ("d", ex);
  y1= min (y1, ex->y1);
  y2= max (y2, ex->y2);
  display_size = y2-y1;
  design_size  = size << 8;

  // get character dimensions
  get_extents ("x", ex);
  yx           = ex->y2;
  get_extents ("M", ex);
  wquad        = ex->x2;

  // compute other heights
  yfrac        = yx >> 1;
  ysub_lo_base = -yx/3;
  ysub_hi_lim  = (5*yx)/6;
  ysup_lo_lim  = yx/2;
  ysup_lo_base = (5*yx)/6;
  ysup_hi_lim  = yx;
  yshift       = yx/6;

  // compute other widths
  wpt          = (dpi*PIXEL)/72;
  wfn          = (wpt*design_size) >> 8;
  wline        = wfn/20;

  // get fraction bar parameters
  get_extents ("-", ex);
  yfrac= (ex->y3 + ex->y4) >> 1;

  // get space length
  get_extents (" ", ex);
  spc  = space ((3*(ex->x2-ex->x1))>>2, ex->x2-ex->x1, (ex->x2-ex->x1)<<1);
  extra= spc;
  sep  = wfn/10;

  // get_italic space
  get_extents ("f", ex);
  SI italic_spc= (ex->x4-ex->x3)-(ex->x2-ex->x1);
  slope= ((double) italic_spc) / ((double) display_size);
  if (slope<0.15) slope= 0.0;
}

/******************************************************************************
* Routines for font
******************************************************************************/

static unsigned int
read_unicode_char (string s, int& i) {
  if (s[i] == '<') {
    i++;
    int start= i;
    while (s[i] != '>') i++;
    if (s[start] == '#') {
      start++;
      return (unsigned int) from_hexadecimal (s (start, i++));
    }
    else {
      string ss= s (start-1, ++i);
      string uu= cork_to_utf8 (ss);
      if (uu == ss) {
	cout << "TeXmacs] warning: invalid symbol " << ss
	     << " in unicode string\n";
	return '?';
      }
      int j= 0;
      return decode_from_utf8 (uu, j);
    }
  }
  else {
    unsigned int c= (unsigned int) s[i++];
    if (c >= 32 && c <= 127) return c;
    string ss= s (i-1, i);
    string uu= cork_to_utf8 (ss);
    int j= 0;
    return decode_from_utf8 (uu, j);
  }
}

void
unicode_font_rep::get_extents (string s, metric& ex) {
  if (N(s)==0) {
    ex->x1= ex->x3= ex->x2= ex->x4=0;
    ex->y3= ex->y1= 0; ex->y4= ex->y2= yx;
  }
  else {
    int i= 0, n= N(s);
    unsigned int uc= read_unicode_char (s, i);
    metric_struct* first= fnm->get (uc);
    ex->x1= conv (first->x1); ex->y1= conv (first->y1);
    ex->x2= conv (first->x2); ex->y2= conv (first->y2);
    ex->x3= conv (first->x3); ex->y3= conv (first->y3);
    ex->x4= conv (first->x4); ex->y4= conv (first->y4);
    SI x= conv (first->x2);

    while (i<n) {
      unsigned int pc= uc;
      uc= read_unicode_char (s, i);
      x += conv (fnm->kerning (pc, uc));
      metric_struct* next= fnm->get (uc);
      ex->x1= min (ex->x1, x+ conv (next->x1));
      ex->y1= min (ex->y1, conv (next->y1));
      ex->x2= max (ex->x2, x+ conv (next->x2));
      ex->y2= max (ex->y2, conv (next->y2));
      ex->x3= min (ex->x3, x+ conv (next->x3));
      ex->y3= min (ex->y3, conv (next->y3));
      ex->x4= max (ex->x4, x+ conv (next->x4));
      ex->y4= max (ex->y4, conv (next->y4));
      x += conv (next->x2);
      //if (fnm->kerning (pc, uc) != 0)
      //cout << "Kerning " << ((char) pc) << ((char) uc) << " " << conv (fnm->kerning (pc, uc)) << ", " << conv (next->x2) << "\n";
    }
  }
}

void
unicode_font_rep::get_xpositions (string s, SI* xpos) {
  int i= 0, n= N(s);
  if (n == 0) return;
  
  register SI x= 0;
  unsigned int uc= 0xffffffff;
  while (i<n) {
    int start= i;
    unsigned int pc= uc;
    uc= read_unicode_char (s, i);
    if (pc != 0xffffffff) x += conv (fnm->kerning (pc, uc));
    metric_struct* next= fnm->get (uc);
    for (int j= start; j<i; j++) xpos[j]= x;
    x += conv (next->x2);
    //if (fnm->kerning (pc, uc) != 0)
    //cout << "Kerning " << ((char) pc) << ((char) uc) << " " << conv (fnm->kerning (pc, uc)) << ", " << conv (next->x2) << "\n";
  }
  xpos[n]= x;
}

void
unicode_font_rep::draw_fixed (renderer ren, string s, SI x, SI y) {
  int i= 0, n= N(s);
  unsigned int uc= 0xffffffff;
  while (i<n) {
    unsigned int pc= uc;
    uc= read_unicode_char (s, i);
    if (pc != 0xffffffff) x += conv (fnm->kerning (pc, uc));
    ren->draw (uc, fng, x, y);
    metric_struct* ex= fnm->get (uc);
    x += conv (ex->x2);
    //if (fnm->kerning (pc, uc) != 0)
    //cout << "Kerning " << ((char) pc) << ((char) uc) << " " << conv (fnm->kerning (pc, uc)) << ", " << conv (ex->x2) << "\n";
  }
}

font
unicode_font_rep::magnify (double zoom) {
  return unicode_font (family, size, (int) round (dpi * zoom));
}

glyph
unicode_font_rep::get_glyph (string s) {
  int i= 0, n= N(s);
  unsigned int uc= read_unicode_char (s, i);
  if (i != n) return font_rep::get_glyph (s);
  glyph gl= fng->get (uc);
  if (is_nil (gl)) return font_rep::get_glyph (s);
  return gl;
}

SI
unicode_font_rep::get_left_correction  (string s) {
  metric ex;
  get_extents (s, ex);
  if (ex->x3 < ex->x1) return ex->x1 - ex->x3;
  return 0;
}

SI
unicode_font_rep::get_right_correction (string s) {
  metric ex;
  get_extents (s, ex);
  if (ex->x4 > ex->x2) return ex->x4 - ex->x2;
  return 0;
}

/******************************************************************************
* Interface
******************************************************************************/

font
unicode_font (string family, int size, int dpi) {
  string name= "unicode:" * family * as_string (size) * "@" * as_string(dpi);
  return make (font, name,
    tm_new<unicode_font_rep> (name, family, size, dpi));
}

#else

font
unicode_font (string family, int size, int dpi) {
  string name= "unicode:" * family * as_string (size) * "@" * as_string(dpi);
  cerr << "\n\nFont name= " << name << "\n";
  FAILED ("true type support was disabled");
  return font ();
}

#endif
