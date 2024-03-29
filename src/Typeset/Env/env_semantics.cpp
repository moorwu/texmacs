
/******************************************************************************
* MODULE     : env_semantics.cpp
* DESCRIPTION: attaching numerical values to the environment variables
* COPYRIGHT  : (C) 1999  Joris van der Hoeven
*******************************************************************************
* This software falls under the GNU general public license version 3 or later.
* It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
* in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
******************************************************************************/

#include "env.hpp"
#include "page_type.hpp"
#include "typesetter.hpp"
#include "Boxes/construct.hpp"
#include "analyze.hpp"

/******************************************************************************
* Retrieving the page size
******************************************************************************/

/*static*/ hashmap<string,int> default_var_type (Env_User);

/*static*/ void
initialize_default_var_type () {
  if (N(default_var_type) != 0) return;
  hashmap<string,int>& var_type= default_var_type;

  var_type (DPI)                = Env_Fixed;
  var_type (ZOOM_FACTOR)        = Env_Zoom;
  var_type (PREAMBLE)           = Env_Preamble;
  var_type (SAVE_AUX)           = Env_Fixed;
  var_type (MODE)               = Env_Mode;
  var_type (INFO_FLAG)          = Env_Info_Level;

  var_type (FONT)               = Env_Font;
  var_type (FONT_FAMILY)        = Env_Font;
  var_type (FONT_SERIES)        = Env_Font;
  var_type (FONT_SHAPE)         = Env_Font;
  var_type (FONT_SIZE)          = Env_Font_Size;
  var_type (FONT_BASE_SIZE)     = Env_Font_Size;
  var_type (MAGNIFICATION)      = Env_Magnification;
  var_type (MAGNIFY)            = Env_Magnify;
  var_type (COLOR)              = Env_Color;
  var_type (OPACITY)            = Env_Color;
  var_type (NO_PATTERNS)        = Env_Pattern_Mode;
  var_type (LANGUAGE)           = Env_Language;

  var_type (MATH_LANGUAGE)      = Env_Language;
  var_type (MATH_FONT)          = Env_Font;
  var_type (MATH_FONT_FAMILY)   = Env_Font;
  var_type (MATH_FONT_SERIES)   = Env_Font;
  var_type (MATH_FONT_SHAPE)    = Env_Font;
  var_type (MATH_LEVEL)         = Env_Index_Level;
  var_type (MATH_DISPLAY)       = Env_Display_Style;
  var_type (MATH_CONDENSED)     = Env_Math_Condensed;
  var_type (MATH_VPOS)          = Env_Vertical_Pos;

  var_type (PROG_LANGUAGE)      = Env_Language;
  var_type (PROG_FONT)          = Env_Font;
  var_type (PROG_FONT_FAMILY)   = Env_Font;
  var_type (PROG_FONT_SERIES)   = Env_Font;
  var_type (PROG_FONT_SHAPE)    = Env_Font;

  var_type (PAR_MODE)           = Env_Paragraph;
  var_type (PAR_FLEXIBILITY)    = Env_Paragraph;
  var_type (PAR_HYPHEN)         = Env_Paragraph;
  var_type (PAR_SPACING)        = Env_Paragraph;
  var_type (PAR_KERNING_STRETCH)= Env_Paragraph;
  var_type (PAR_KERNING_MARGIN) = Env_Paragraph;
  var_type (PAR_HYPHEN)         = Env_Paragraph;
  var_type (PAR_WIDTH)          = Env_Paragraph;
  var_type (PAR_LEFT)           = Env_Paragraph;
  var_type (PAR_RIGHT)          = Env_Paragraph;
  var_type (PAR_FIRST)          = Env_Paragraph;
  var_type (PAR_NO_FIRST)       = Env_Paragraph;
  var_type (PAR_SEP)            = Env_Paragraph;
  var_type (PAR_HOR_SEP)        = Env_Paragraph;
  var_type (PAR_VER_SEP)        = Env_Paragraph;
  var_type (PAR_LINE_SEP)       = Env_Paragraph;
  var_type (PAR_PAR_SEP)        = Env_Paragraph;

  var_type (PAGE_TYPE)          = Env_Fixed;
  var_type (PAGE_BREAKING)      = Env_Fixed;
  var_type (PAGE_FLEXIBILITY)   = Env_Fixed;
  var_type (PAGE_FIRST)         = Env_Fixed;
  var_type (PAGE_WIDTH)         = Env_Page_Extents;
  var_type (PAGE_HEIGHT)        = Env_Page_Extents;
  var_type (PAGE_WIDTH_MARGIN)  = Env_Page;
  var_type (PAGE_SCREEN_MARGIN) = Env_Page;
  var_type (PAGE_NR)            = Env_Page;
  var_type (PAGE_THE_PAGE)      = Env_Page;
  var_type (PAGE_ODD)           = Env_Page;
  var_type (PAGE_EVEN)          = Env_Page;
  var_type (PAGE_RIGHT)         = Env_Page;
  var_type (PAGE_TOP)           = Env_Page;
  var_type (PAGE_BOT)           = Env_Page;
  var_type (PAGE_USER_HEIGHT)   = Env_Page;
  var_type (PAGE_ODD_SHIFT)     = Env_Page;
  var_type (PAGE_EVEN_SHIFT)    = Env_Page;
  var_type (PAGE_SHRINK)        = Env_Page;
  var_type (PAGE_EXTEND)        = Env_Page;
  var_type (PAGE_HEAD_SEP)      = Env_Page;
  var_type (PAGE_FOOT_SEP)      = Env_Page;
  var_type (PAGE_ODD_HEADER)    = Env_Page;
  var_type (PAGE_ODD_FOOTER)    = Env_Page;
  var_type (PAGE_EVEN_HEADER)   = Env_Page;
  var_type (PAGE_EVEN_FOOTER)   = Env_Page;
  var_type (PAGE_THIS_HEADER)   = Env_Page;
  var_type (PAGE_THIS_FOOTER)   = Env_Page;
  var_type (PAGE_FNOTE_SEP)     = Env_Page;
  var_type (PAGE_FNOTE_BARLEN)  = Env_Page;
  var_type (PAGE_FLOAT_SEP)     = Env_Page;
  var_type (PAGE_MNOTE_SEP)     = Env_Page;
  var_type (PAGE_MNOTE_WIDTH)   = Env_Page;

  var_type (POINT_STYLE)        = Env_Point_Style;
  var_type (LINE_WIDTH)         = Env_Line_Width;
  var_type (DASH_STYLE)         = Env_Dash_Style;
  var_type (DASH_STYLE_UNIT)    = Env_Dash_Style_Unit;
  var_type (FILL_COLOR)         = Env_Fill_Color;
  var_type (ARROW_BEGIN)        = Env_Line_Arrows;
  var_type (ARROW_END)          = Env_Line_Arrows;
  var_type (ARROW_LENGTH)       = Env_Line_Arrows;
  var_type (ARROW_HEIGHT)       = Env_Line_Arrows;
  var_type (TEXT_AT_HALIGN)     = Env_Text_At_Halign;
  var_type (TEXT_AT_VALIGN)     = Env_Text_At_Valign;
  var_type (GR_FRAME)           = Env_Frame;
  var_type (GR_GEOMETRY)        = Env_Geometry;
  var_type (GR_GRID)            = Env_Grid;
  var_type (GR_GRID_ASPECT)     = Env_Grid_Aspect;
  var_type (GR_EDIT_GRID)       = Env_Grid;
  var_type (GR_EDIT_GRID_ASPECT)= Env_Grid_Aspect;

  var_type (SRC_STYLE)          = Env_Src_Style;
  var_type (SRC_SPECIAL)        = Env_Src_Special;
  var_type (SRC_COMPACT)        = Env_Src_Compact;
  var_type (SRC_CLOSE)          = Env_Src_Close;
}

/******************************************************************************
* Retrieving the page size
******************************************************************************/

#define get_page_par(which) \
  (get_string (which) == "auto"? \
   as_length (page_get_feature (page_type, which, page_landscape)): \
   get_length (which))

void
edit_env_rep::update_page_pars () {
  page_type         = get_string (PAGE_TYPE);
  page_landscape    = (get_string (PAGE_ORIENTATION) == "landscape");
  page_automatic    = (get_string (PAGE_MEDIUM) == "automatic");
  string width_flag = get_string (PAGE_WIDTH_MARGIN);
  string height_flag= get_string (PAGE_HEIGHT_MARGIN);
  bool   screen_flag= get_bool   (PAGE_SCREEN_MARGIN);

  if (page_automatic) {
    page_width        = get_length (PAGE_SCREEN_WIDTH);
    page_height       = get_length (PAGE_SCREEN_HEIGHT);
    page_odd_margin   = get_length (PAGE_SCREEN_LEFT);
    page_right_margin = get_length (PAGE_SCREEN_RIGHT);
    page_even_margin  = page_odd_margin;
    page_top_margin   = get_length (PAGE_SCREEN_TOP);
    page_bottom_margin= get_length (PAGE_SCREEN_BOT);
    page_user_width   = page_width - page_odd_margin - page_right_margin;
    page_user_height  = page_height - page_top_margin - page_bottom_margin;
  }
  else {
    page_width  = get_page_par (PAGE_WIDTH);
    page_height = get_page_par (PAGE_HEIGHT);

    if (width_flag == "false") {
      page_odd_margin   = get_page_par (PAGE_ODD);
      page_even_margin  = get_page_par (PAGE_EVEN);
      page_right_margin = get_page_par (PAGE_RIGHT);
      page_user_width   = page_width - page_odd_margin - page_right_margin;
    }
    else if (width_flag == "true") {
      page_user_width   = get_page_par (PAR_WIDTH);
      SI odd_sh         = get_length (PAGE_ODD_SHIFT);
      SI even_sh        = get_length (PAGE_EVEN_SHIFT);
      page_odd_margin   = ((page_width - page_user_width) >> 1) + odd_sh;
      page_even_margin  = ((page_width - page_user_width) >> 1) + even_sh;
      page_right_margin = page_width - page_odd_margin - page_user_width;
    }
    else {
      page_odd_margin   = get_page_par (PAGE_ODD);
      page_even_margin  = get_page_par (PAGE_EVEN);
      page_user_width   = get_page_par (PAR_WIDTH);
      page_right_margin = page_width - page_odd_margin - page_user_width;
    }

    if (height_flag == "false") {
      page_top_margin   = get_page_par (PAGE_TOP);
      page_bottom_margin= get_page_par (PAGE_BOT);
      page_user_height  = page_height - page_top_margin - page_bottom_margin;
    }
    else if (height_flag == "true") {
      page_user_height  = get_length (PAGE_USER_HEIGHT);
      page_top_margin   = (page_height - page_user_width) >> 1;
      page_bottom_margin= page_top_margin;
    }
    else {
      page_user_height  = get_length (PAGE_USER_HEIGHT);
      page_top_margin   = get_page_par (PAGE_TOP);
      page_bottom_margin= page_height - page_top_margin - page_user_height;
    }

    if (page_type == "user") {
      if (get_string (PAGE_EVEN) == "auto" &&
          get_string (PAGE_ODD ) != "auto")
        page_even_margin= page_odd_margin;
      if (get_string (PAGE_ODD ) == "auto" &&
          get_string (PAGE_EVEN) != "auto")
        page_odd_margin= page_even_margin;
    }

    if (screen_flag) {
      page_odd_margin   = get_length (PAGE_SCREEN_LEFT);
      page_right_margin = get_length (PAGE_SCREEN_RIGHT);
      page_top_margin   = get_length (PAGE_SCREEN_TOP);
      page_bottom_margin= get_length (PAGE_SCREEN_BOT);
      page_even_margin  = page_odd_margin;
      page_width = page_user_width + page_odd_margin + page_right_margin;
      page_height= page_user_height + page_top_margin + page_bottom_margin;
    }
  }
}

void
edit_env_rep::get_page_pars (SI& w, SI& h, SI& width, SI& height,
			     SI& odd, SI& even, SI& top, SI& bot)
{
  w     = page_user_width;
  h     = page_user_height;
  width = page_width;
  height= page_height;
  odd   = page_odd_margin;
  even  = page_even_margin;
  top   = page_top_margin;
  bot   = page_bottom_margin;

  int nr_cols= get_int (PAR_COLUMNS);
  if (nr_cols > 1) {
    SI col_sep= get_length (PAR_COLUMNS_SEP);
    w= ((w+col_sep) / nr_cols) - col_sep;
  }

  /*
  cout << "w     = " << (w/PIXEL) << "\n";
  cout << "h     = " << (h/PIXEL) << "\n";
  cout << "width = " << (width/PIXEL) << "\n";
  cout << "height= " << (height/PIXEL) << "\n";
  cout << "odd   = " << (odd/PIXEL) << "\n";
  cout << "even  = " << (even/PIXEL) << "\n";
  cout << "top   = " << (top/PIXEL) << "\n";
  cout << "bot   = " << (bot/PIXEL) << "\n";
  cout << "cols  = " << nr_cols << "\n";
  */
}

/******************************************************************************
* Retrieving ornament parameters
******************************************************************************/

static tree
tuplify (tree t) {
  array<string> a= tokenize (t->label, ",");
  tree r (TUPLE, N(a));
  for (int i=0; i<N(a); i++)
    r[i]= a[i];
  return r;
}

ornament_parameters
edit_env_rep::get_ornament_parameters () {
  tree  shape = read (ORNAMENT_SHAPE);
  tree  tst   = read (ORNAMENT_TITLE_STYLE);
  tree  bg    = read (ORNAMENT_COLOR);
  tree  xc    = read (ORNAMENT_EXTRA_COLOR);
  tree  sunny = read (ORNAMENT_SUNNY_COLOR);
  tree  shadow= read (ORNAMENT_SHADOW_COLOR);
  int   a     = alpha;
  tree  w     = read (ORNAMENT_BORDER);
  tree  ext   = read (ORNAMENT_SWELL);
  tree  xpad  = read (ORNAMENT_HPADDING);
  tree  ypad  = read (ORNAMENT_VPADDING);

  array<brush> border;
  if (is_func (sunny, TUPLE)) {
    for (int i=0; i<N(sunny); i++)
      border << brush (sunny[i], a);
  }
  else {
    border << brush (sunny, a);
    border << brush (shadow, a);
  }
  if (N(border) == 1) border << border[0];
  if (N(border) == 2) border << border[1] << border[0];

  SI lw, bw, rw, tw;
  if (is_atomic (w) && occurs (",", w->label))
    w= tuplify (w);
  if (is_func (w, TUPLE, 4)) {
    lw= ((as_length (w[0]) >> 1) << 1);
    bw= ((as_length (w[1]) >> 1) << 1);
    rw= ((as_length (w[2]) >> 1) << 1);
    tw= ((as_length (w[3]) >> 1) << 1);
  }
  else lw= bw= rw= tw= ((as_length (w) >> 1) << 1);

  double lx, bx, rx, tx;
  if (is_atomic (ext) && occurs (",", ext->label))
    ext= tuplify (ext);
  if (is_func (ext, TUPLE, 4)) {
    lx= as_double (ext[0]);
    bx= as_double (ext[1]);
    rx= as_double (ext[2]);
    tx= as_double (ext[3]);
  }
  else lx= bx= rx= tx= as_double (ext);

  SI lpad, rpad;
  if (is_atomic (xpad) && occurs (",", xpad->label))
    xpad= tuplify (xpad);
  if (is_func (xpad, TUPLE, 2)) {
    lpad= as_length (xpad[0]);
    rpad= as_length (xpad[1]);
  }
  else lpad= rpad= as_length (xpad);

  SI bpad, tpad;
  if (is_atomic (ypad) && occurs (",", ypad->label))
    ypad= tuplify (ypad);
  if (is_func (ypad, TUPLE, 2)) {
    bpad= as_length (ypad[0]);
    tpad= as_length (ypad[1]);
  }
  else bpad= tpad= as_length (ypad);

  return ornament_parameters (shape, tst,
                              lw, bw, rw, tw,
			      lx, bx, rx, tx,
			      lpad, bpad, rpad, tpad,
                              brush (bg, a), brush (xc, a), border);
}

/******************************************************************************
* Updating the environment from the variables
******************************************************************************/

void
edit_env_rep::update_font () {
  fn_size= (int) (((double) get_int (FONT_BASE_SIZE)) *
		  get_double (FONT_SIZE) + 0.5);
  switch (mode) {
  case 0:
  case 1:
    fn= smart_font (get_string (FONT), get_string (FONT_FAMILY),
                    get_string (FONT_SERIES), get_string (FONT_SHAPE),
                    script (fn_size, index_level), (int) (magn*dpi));
    break;
  case 2:
    fn= smart_font (get_string (MATH_FONT), get_string (MATH_FONT_FAMILY),
                    get_string (MATH_FONT_SERIES), get_string (MATH_FONT_SHAPE),
                    get_string (FONT), get_string (FONT_FAMILY),
                    get_string (FONT_SERIES), "mathitalic",
                    script (fn_size, index_level), (int) (magn*dpi));
    break;
  case 3:
    fn= smart_font (get_string (PROG_FONT), get_string (PROG_FONT_FAMILY),
                    get_string (PROG_FONT_SERIES), get_string (PROG_FONT_SHAPE),
                    get_string (FONT), get_string (FONT_FAMILY) * "-tt",
                    get_string (FONT_SERIES), get_string (FONT_SHAPE),
                    script (fn_size, index_level), (int) (magn*dpi));
    break;
  }
}

int
decode_alpha (string s) {
  if (N(s) == 0) return 255;
  else if (s[N(s)-1] == '%') {
    // mg: be careful to avoid rounding problems for the conversion from double to int : (int)(2.55*100.0)=254
    double p = as_double (s (0, N(s)-1));
    if (p<0.0) p = 0.0;
    if (p>100.0) p = 100.0;
    return ((int) (255.0 * p))/100;
  }
  else {
    double p = as_double (s);
    if (p<0.0) p = 0.0;
    if (p>1.0) p = 1.0;
    return ((int) (255.0 * p));
  }
}

void
edit_env_rep::update_color () {
  alpha= decode_alpha (get_string (OPACITY));
  tree pc= env [COLOR];
  tree fc= env [FILL_COLOR];
  if (pc == "none") pen= pencil (false);
  else pen= pencil (pc, alpha, get_length (LINE_WIDTH));
  if (fc == "none") fill_brush= brush (false);
  else fill_brush= brush (fc, alpha);
}

void
edit_env_rep::update_pattern_mode () {
  no_patterns= (get_string (NO_PATTERNS) == "true");
  if (no_patterns) {
    tree c= env[COLOR];
    if (is_func (c, PATTERN, 4)) env (COLOR)= exec (c);
    c= env[BG_COLOR];
    if (is_func (c, PATTERN, 4)) env (BG_COLOR)= exec (c);
    c= env[FILL_COLOR];
    if (is_func (c, PATTERN, 4)) env (FILL_COLOR)= exec (c);
    c= env[ORNAMENT_COLOR];
    if (is_func (c, PATTERN, 4)) env (ORNAMENT_COLOR)= exec (c);
    c= env[ORNAMENT_EXTRA_COLOR];
    if (is_func (c, PATTERN, 4)) env (ORNAMENT_EXTRA_COLOR)= exec (c);
    update_color ();
  }
}

void
edit_env_rep::update_mode () {
  string s= get_string (MODE);
  if (s == "text") mode=1;
  else if (s == "math") mode=2;
  else if (s == "prog") mode=3;
  else mode=0;
  if (mode == 2) mode_op= OP_SYMBOL;
  else mode_op= OP_TEXT;
}

void
edit_env_rep::update_info_level () {
  string s= get_string (INFO_FLAG);
  if (s == "none") info_level= INFO_NONE;
  else if (s == "minimal") info_level= INFO_MINIMAL;
  else if (s == "short") info_level= INFO_SHORT;
  else if (s == "detailed") info_level= INFO_DETAILED;
  else if (s == "paper") info_level= INFO_PAPER;
  else if (s == "short-paper") info_level= INFO_SHORT_PAPER;
  else info_level= INFO_MINIMAL;
}

void
edit_env_rep::update_language () {
  switch (mode) {
  case 0:
  case 1:
    lan= text_language (get_string (LANGUAGE));
    break;
  case 2:
    lan= math_language (get_string (MATH_LANGUAGE));
    break;
  case 3:
    lan= prog_language (get_string (PROG_LANGUAGE));
    break;
  }
  hl_lan= lan->hl_lan;
}

void
edit_env_rep::update_geometry () {
  tree t= env [GR_GEOMETRY];
  gw= as_length ("1par");
  gh= as_length ("0.6par");
  gvalign= as_string ("center");
  if (is_tuple (t, "geometry", 2) || is_tuple (t, "geometry", 3)) {
    if (is_length (as_string (t[1]))) gw= as_length (t[1]);
    if (is_length (as_string (t[2]))) gh= as_length (t[2]);
    if (is_tuple (t, "geometry", 3))
      gvalign= as_string (t[3]);
  }
  update_frame ();
}

void
edit_env_rep::update_frame () {
  tree t= env [GR_FRAME];
  SI yinc= gvalign == "top"    ? - gh
	 : gvalign == "bottom" ? 0
         : gvalign == "axis" ? - (gh/2) + as_length ("1yfrac")
	 : - gh / 2;
  if (is_tuple (t, "scale", 2) && is_func (t[2], TUPLE, 2)) {
    SI magn= as_length (t[1]);
    SI x   = as_length (t[2][0]);
    SI y   = as_length (t[2][1]);
    fr= scaling (magn, point (x, y + yinc));
  }
  else {
    SI cm   = as_length (string ("1cm"));
    SI par  = as_length (string ("1par"));
    SI yfrac= as_length (string ("1yfrac"));
    fr= scaling (cm, point (par >> 1, yfrac + yinc));
  }
  point p0= fr (as_point (tuple ("0par", "0par")));
  if (gvalign == "top") {
    clip_lim1= fr [point (p0[0], p0[1] - gh)];
    clip_lim2= fr [point (p0[0] + gw, p0[1])];
  }
  else if (gvalign == "bottom") {
    clip_lim1= fr [point (p0[0], p0[1])];
    clip_lim2= fr [point (p0[0] + gw, p0[1] + gh)];
  }
  else if (gvalign == "axis") {
    clip_lim1= fr [point (p0[0], p0[1] - (gh/2) + as_length ("1yfrac"))];
    clip_lim2= fr [point (p0[0] + gw, p0[1] + (gh/2) + as_length ("1yfrac"))];
  }
  else {
    clip_lim1= fr [point (p0[0], p0[1] - gh/2)];
    clip_lim2= fr [point (p0[0] + gw, p0[1] + gh/2)];
  }
}

void
edit_env_rep::update_src_style () {
  string s= as_string (env [SRC_STYLE]);
  if (s == "angular") src_style= STYLE_ANGULAR;
  else if (s == "scheme") src_style= STYLE_SCHEME;
  else if (s == "latex") src_style= STYLE_LATEX;
  else if (s == "functional") src_style= STYLE_FUNCTIONAL;
}

void
edit_env_rep::update_src_special () {
  string s= as_string (env [SRC_SPECIAL]);
  if (s == "raw") src_special= SPECIAL_RAW;
  else if (s == "format") src_special= SPECIAL_FORMAT;
  else if (s == "normal") src_special= SPECIAL_NORMAL;
  else if (s == "maximal") src_special= SPECIAL_MAXIMAL;
}

void
edit_env_rep::update_src_compact () {
  string s= as_string (env [SRC_COMPACT]);
  if (s == "all") src_compact= COMPACT_ALL;
  else if (s == "inline args") src_compact= COMPACT_INLINE_ARGS;
  else if (s == "normal") src_compact= COMPACT_INLINE_START;
  else if (s == "inline") src_compact= COMPACT_INLINE;
  else if (s == "none") src_compact= COMPACT_NONE;
}

void
edit_env_rep::update_src_close () {
  string s= as_string (env [SRC_CLOSE]);
  if (s == "minimal") src_close= CLOSE_MINIMAL;
  else if (s == "compact") src_close= CLOSE_COMPACT;
  else if (s == "long") src_close= CLOSE_LONG;
  else if (s == "repeat") src_close= CLOSE_REPEAT;
}

void
edit_env_rep::update_dash_style () {
  tree t= env [DASH_STYLE];
  dash_style= array<bool> (0);
  if (is_string (t)) {
    string s= as_string (t);
    if (N(s) > 0 && (s[0] == '0' || s[0] == '1')) {
      int i, n= N(s);
      dash_style= array<bool> (n);
      for (i=0; i<n; i++)
        dash_style[i]= (s[i] != '0');
    }
  }
}

void
decompose_length (string s, double& x, string& un) {
  int i;
  for (i=0; i<N(s); i++)
    if ((s[i]>='a') && (s[i]<='z')) break;
  x = as_double (s (0, i));
  un= s (i, N(s));
}

tree
edit_env_rep::decode_arrow (tree t, string l, string h) {
  if (is_string (t)) {
    string s= t->label;
    if (s == "" || s == "none") return "";
    double lx, hx;
    string lun, hun;
    decompose_length (l, lx, lun);
    decompose_length (h, hx, hun);
    if (s == "<less>")
      return tree (LINE,
                   tree (_POINT, l, h),
                   tree (_POINT, "0" * lun, "0" * hun),
                   tree (_POINT, l, as_string (-hx) * hun));
    if (s == "<gtr>")
      return tree (LINE,
                   tree (_POINT, as_string (-lx) * lun, h),
                   tree (_POINT, "0" * lun, "0" * hun),
                   tree (_POINT, as_string (-lx) * lun,
                                 as_string (-hx) * hun));
    if (s == "<less>|")
      return tree (WITH, FILL_COLOR, tree (VALUE, COLOR),
                   LINE_WIDTH, "0ln",
                   tree (CLINE,
                         tree (_POINT, l, h),
                         tree (_POINT, "0" * lun, "0" * hun),
                         tree (_POINT, l, as_string (-hx) * hun)));
    if (s == "|<gtr>")
      return tree (WITH, FILL_COLOR, tree (VALUE, COLOR),
                   LINE_WIDTH, "0ln",
                   tree (CLINE,
                         tree (_POINT, as_string (-lx) * lun, h),
                         tree (_POINT, "0" * lun, "0" * hun),
                         tree (_POINT, as_string (-lx) * lun,
                               as_string (-hx) * hun)));
    if (s == "<gtr>")
      return tree (LINE,
                   tree (_POINT, as_string (-lx) * lun, h),
                   tree (_POINT, "0" * lun, "0" * hun),
                   tree (_POINT, as_string (-lx) * lun,
                                 as_string (-hx) * hun));
    if (s == "<less><less>")
      return tree (GR_GROUP,
                   tree (LINE,
                         tree (_POINT, l, h),
                         tree (_POINT, "0" * lun, "0" * hun),
                         tree (_POINT, l, as_string (-hx) * hun)),
                   tree (LINE,
                         tree (_POINT, as_string (0 * lx) * lun, h),
                         tree (_POINT, as_string (-lx) * lun, "0" * hun),
                         tree (_POINT, as_string (0 * lx) * lun,
                               as_string (-hx) * hun)));
    if (s == "<gtr><gtr>")
      return tree (GR_GROUP,
                   tree (LINE,
                         tree (_POINT, as_string (-lx) * lun, h),
                         tree (_POINT, "0" * lun, "0" * hun),
                         tree (_POINT, as_string (-lx) * lun,
                               as_string (-hx) * hun)),
                   tree (LINE,
                         tree (_POINT, as_string (0 * lx) * lun, h),
                         tree (_POINT, as_string (lx) * lun, "0" * hun),
                         tree (_POINT, as_string (0 * lx) * lun,
                               as_string (-hx) * hun)));                   
    if (s == "|")
      return tree (LINE,
                   tree (_POINT, "0" * lun, h),
                   tree (_POINT, "0" * lun, as_string (-hx) * hun));
    if (s == "o")
      return tree (WITH, FILL_COLOR, tree (VALUE, COLOR),
                   LINE_WIDTH, "0ln",
                   tree (CARC,
                         tree (_POINT, "0" * lun, h),
                         tree (_POINT, l, "0" * hun),
                         tree (_POINT, "0" * lun, as_string (-hx) * hun)));
    return "";
  }
  else return t;
}

void
edit_env_rep::update_line_arrows () {
  line_arrows= array<tree> (2);
  string l= get_string (ARROW_LENGTH);
  string h= get_string (ARROW_HEIGHT);
  line_arrows[0]= decode_arrow (env [ARROW_BEGIN], l, h);
  line_arrows[1]= decode_arrow (env [ARROW_END], l, h);
}

void
edit_env_rep::update () {
  zoomf          = normal_zoom (get_double (ZOOM_FACTOR));
  pixel          = (SI) tm_round ((std_shrinkf * PIXEL) / zoomf);
  magn           = get_double (MAGNIFICATION);
  index_level    = get_int (MATH_LEVEL);
  display_style  = get_bool (MATH_DISPLAY);
  math_condensed = get_bool (MATH_CONDENSED);
  vert_pos       = get_int (MATH_VPOS);
  preamble       = get_bool (PREAMBLE);

  update_mode ();
  update_info_level ();
  update_language ();
  update_font ();

  update_geometry ();
  update_frame ();
  point_style= get_string (POINT_STYLE);
  update_color ();
  update_pattern_mode ();
  update_dash_style ();
  dash_style_unit= get_length (DASH_STYLE_UNIT);
  update_line_arrows ();
  text_at_halign= get_string (TEXT_AT_HALIGN);
  text_at_valign= get_string (TEXT_AT_VALIGN);

  update_src_style ();
  update_src_special ();
  update_src_compact ();
  update_src_close ();
}

/******************************************************************************
* Update a particular changed variable
******************************************************************************/

void
edit_env_rep::update (string s) {
  switch (var_type[s]) {
  case Env_User:
    break;
  case Env_Fixed:
    break;
  case Env_Zoom:
    zoomf= normal_zoom (get_double (ZOOM_FACTOR));
    pixel= (SI) tm_round ((std_shrinkf * PIXEL) / zoomf);
    break;
  case Env_Magnification:
    magn= get_double (MAGNIFICATION);
    update_font ();
    update_color ();
    break;
  case Env_Magnify:
    mgfy= get_double (MAGNIFY);
    break;
  case Env_Language:
    update_language ();
    break;
  case Env_Mode:
    update_mode ();
    update_language ();
    update_font ();
    break;
  case Env_Info_Level:
    update_info_level ();
    break;
  case Env_Font:
    update_font ();
    break;
  case Env_Font_Size:
    update_font ();
    break;
  case Env_Index_Level:
    index_level= get_int (MATH_LEVEL);
    update_font ();
    break;
  case Env_Display_Style:
    display_style= get_bool (MATH_DISPLAY);
    break;
  case Env_Math_Condensed:
    math_condensed= get_bool (MATH_CONDENSED);
    break;
  case Env_Vertical_Pos:
    vert_pos= get_int (MATH_VPOS);
    break;
  case Env_Color:
    update_color ();
    break;
  case Env_Pattern_Mode:
    update_pattern_mode ();
    break;
  case Env_Paragraph:
    break;
  case Env_Page:
    break;
  case Env_Page_Extents:
    update_page_pars ();
    break;
  case Env_Preamble:
    preamble= get_bool (PREAMBLE);
    break;
  case Env_Geometry:
    update_geometry ();
    break;
  case Env_Frame:
    update_frame ();
    break;
  case Env_Point_Style:
    point_style= get_string (POINT_STYLE);
    break;
  case Env_Line_Width:
    update_color ();
    break;
  case Env_Dash_Style:
    update_dash_style();
    break;
  case Env_Dash_Style_Unit:
    dash_style_unit= get_length (DASH_STYLE_UNIT);
    break;
  case Env_Fill_Color:
    update_color ();
    break;
  case Env_Line_Arrows:
    update_line_arrows();
    break;
  case Env_Text_At_Halign:
    text_at_halign= get_string (TEXT_AT_HALIGN);
    break;
  case Env_Text_At_Valign:
    text_at_valign= get_string (TEXT_AT_VALIGN);
    break;
  case Env_Src_Style:
    update_src_style ();
    break;
  case Env_Src_Special:
    update_src_special ();
    break;
  case Env_Src_Compact:
    update_src_compact ();
    break;
  case Env_Src_Close:
    update_src_close ();
    break;
  }
}
