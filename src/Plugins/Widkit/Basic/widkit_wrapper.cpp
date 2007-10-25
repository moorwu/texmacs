
/******************************************************************************
* MODULE     : widkit_wrapper.hpp
* DESCRIPTION: Conversions between widget and wk_widget
* COPYRIGHT  : (C) 2007  Joris van der Hoeven
*******************************************************************************
* This software falls under the GNU general public license and comes WITHOUT
* ANY WARRANTY WHATSOEVER. See the file $TEXMACS_PATH/LICENSE for more details.
* If you don't have this file, write to the Free Software Foundation, Inc.,
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
******************************************************************************/

#include "promise.hpp"
#include "url.hpp"
#include "Widkit/wk_widget.hpp"
#include "message.hpp"

#define THIS wk_widget (this)

/******************************************************************************
* Type conversions
******************************************************************************/

array<widget>
abstract (array<wk_widget> a) {
  int i, n= N(a);
  array<widget> b (n);
  for (i=0; i<n; i++) b[i]= abstract (a[i]);
  return b;
}

array<wk_widget>
concrete (array<widget> a) {
  int i, n= N(a);
  array<wk_widget> b (n);
  for (i=0; i<n; i++) b[i]= concrete (a[i]);
  return b;
}

class abstract_promise_rep: public promise_rep<widget> {
  promise<wk_widget> p;
public:
  abstract_promise_rep (promise<wk_widget> p2): p (p2) {}
  ostream& print (ostream& out) { return out << p; }
  widget eval () { return abstract (p ()); }
};

promise<widget>
abstract (promise<wk_widget> pw) {
  return new abstract_promise_rep (pw);
}

class concrete_promise_rep: public promise_rep<wk_widget> {
  promise<widget> p;
public:
  concrete_promise_rep (promise<widget> p2): p (p2) {}
  ostream& print (ostream& out) { return out << p; }
  wk_widget eval () { return concrete (p ()); }
};

promise<wk_widget>
concrete (promise<widget> pw) {
  return new concrete_promise_rep (pw);
}

/******************************************************************************
* Exported special widgets
******************************************************************************/

widget
horizontal_list (array<widget> a) {
  return abstract (horizontal_list (concrete (a)));
}

widget
horizontal_list (array<widget> a, array<string> name) {
  return abstract (horizontal_list (concrete (a), name));
}

widget
vertical_list (array<widget> a) {
  return abstract (vertical_list (concrete (a)));
}

widget
vertical_list (array<widget> a, array<string> name) {
  return abstract (vertical_list (concrete (a), name));
}

widget
vertical_menu (array<widget> a) {
  return abstract (vertical_menu (concrete (a)));
}

widget
tile (array<widget> a, int cols) {
  return abstract (tile (concrete (a), cols));
}

widget
tile (array<widget> a, int cols, array<string> name) {
  return abstract (tile (concrete (a), cols, name));
}

widget
horizontal_array (array<widget> a, int stretch_me) {
  return abstract (horizontal_array (concrete (a), stretch_me));
}

widget
horizontal_array (array<widget> a, array<string> s, int stretch_me) {
  return abstract (horizontal_array (concrete (a), s, stretch_me));
}

widget
switch_widget (array<widget> a, array<string> name, int init) {
  return abstract (switch_widget (concrete (a), name, init));
}

widget
optional_widget (widget w, bool on) {
  return abstract (optional_widget (concrete (w), on));
}

widget
glue_widget (bool hx, bool vx, SI w, SI h) {
  return abstract (glue_wk_widget (hx, vx, w, h));
}

widget
separator_widget (SI pre, SI post, bool vert) {
  return abstract (separator_wk_widget (pre, post, vert));
}

widget
text_widget (string s, bool tsp, string lan) {
  return abstract (text_wk_widget (s, tsp, lan));
}

widget
menu_text_widget (string s, color col, string lan, bool tt) {
  return abstract (menu_text_wk_widget (s, col, lan, tt));
}

widget
xpm_widget (url file_name, bool transp) {
  return abstract (xpm_wk_widget (file_name, transp));
}

widget
command_button (widget w, command cmd, bool button_flag) {
  return abstract (command_button (concrete (w), cmd, button_flag));
}

widget
command_button (widget lw, widget rw, command cmd) {
  return abstract (command_button (concrete (lw), concrete (rw), cmd));
}

widget
command_button (widget lw, widget cw, widget rw, command cmd, bool e, bool c) {
  return abstract (command_button (concrete (lw), concrete (cw),
				   concrete (rw), cmd, e, c));
}

widget
pulldown_button (widget w, widget m, bool button_flag) {
  return abstract (pulldown_button (concrete (w), concrete (m), button_flag));
}

widget
pullright_button (widget w, widget m, bool button_flag) {
  return abstract (pullright_button (concrete (w), concrete (m), button_flag));
}

widget
pulldown_button (widget w, promise<widget> pw) {
  return abstract (pulldown_button (concrete (w), concrete (pw)));
}

widget
pullright_button (widget w, promise<widget> pw) {
  return abstract (pullright_button (concrete (w), concrete (pw)));
}

widget
popup_widget (widget w, gravity quit) {
  return abstract (popup_widget (concrete (w), quit));
}

widget
canvas_widget (widget w, gravity grav) {
  return abstract (canvas_widget (concrete (w), grav));
}

widget
input_text_widget (command call_back) {
  return abstract (input_text_wk_widget (call_back));
}

widget
input_text_widget (command call_back, string type, array<string> def) {
  return abstract (input_text_wk_widget (call_back, type, def));
}

widget
inputs_list_widget (command call_back, array<string> prompts) {
  return abstract (inputs_list_wk_widget (call_back, prompts));
}

widget
file_chooser_widget (command cmd, string type, string mgn) {
  return abstract (file_chooser_wk_widget (cmd, type, mgn));
}

widget
balloon_widget (widget w, widget help) {
  return abstract (balloon_widget (concrete (w), concrete (help)));
}

widget
wait_widget (SI w, SI h, string message) {
  return abstract (wait_wk_widget (w, h, message));
}

widget
texmacs_widget (int mask, command quit) {
  return abstract (texmacs_wk_widget (mask, quit));
}

/******************************************************************************
* Helper routines for message passing
******************************************************************************/

void
send_bool (wk_widget w, string key, blackbox val) {
  if (type_box (val) != type_helper<bool>::id)
    fatal_error ("type mismatch", "send_bool");
  w << set_string (key, open_box<bool> (val)? string ("on"): string ("off"));
}

void
send_int (wk_widget w, string key, blackbox val) {
  if (type_box (val) != type_helper<int>::id)
    fatal_error ("type mismatch", "send_int");
  w << set_integer (key, open_box<int> (val));
}

void
send_string (wk_widget w, string key, blackbox val) {
  if (type_box (val) != type_helper<string>::id)
    fatal_error ("type mismatch", "send_string");
  w << set_string (key, open_box<string> (val));
}

void
send_widget (wk_widget w, string key, blackbox val) {
  if (type_box (val) != type_helper<widget>::id)
    fatal_error ("type mismatch", "send_widget");
  w << set_widget (key, concrete (open_box<widget> (val)));
}

void
send_coord2 (wk_widget w, string key, blackbox val) {
  typedef pair<SI,SI> coord2;
  if (type_box (val) != type_helper<coord2>::id)
    fatal_error ("type mismatch", "send_coord2");
  coord2 p= open_box<coord2> (val);
  w << set_coord2 (key, p.x1, p.x2);
}

void
send_coord4 (wk_widget w, string key, blackbox val) {
  typedef quadruple<SI,SI,SI,SI> coord4;
  if (type_box (val) != type_helper<coord4>::id)
    fatal_error ("type mismatch", "send_coord4");
  coord4 p= open_box<coord4> (val);
  w << set_coord4 (key, p.x1, p.x2, p.x3, p.x4);
}

blackbox
query_bool (wk_widget w, string key, int type_id) {
  if (type_id != type_helper<bool>::id)
    fatal_error ("type mismatch", "query_bool");
  string s;
  w << get_string (key, s);
  return close_box<bool> (s == "on");
}

blackbox
query_int (wk_widget w, string key, int type_id) {
  if (type_id != type_helper<int>::id)
    fatal_error ("type mismatch", "query_int");
  int i;
  w << get_integer (key, i);
  return close_box<int> (i);
}

blackbox
query_string (wk_widget w, string key, int type_id) {
  if (type_id != type_helper<string>::id)
    fatal_error ("type mismatch", "query_string");
  string s;
  w << get_string (key, s);
  return close_box<string> (s);
}

blackbox
query_widget (wk_widget w, string key, int type_id) {
  if (type_id != type_helper<widget>::id)
    fatal_error ("type mismatch", "query_widget");
  wk_widget wkw;
  w << get_widget (key, wkw);
  return close_box<widget> (abstract (wkw));
}

blackbox
query_coord2 (wk_widget w, string key, int type_id) {
  typedef pair<SI,SI> coord2;
  if (type_id != type_helper<coord2>::id)
    fatal_error ("type mismatch", "query_coord2");
  SI c1, c2;
  w << get_coord2 (key, c1, c2);
  return close_box<coord2> (coord2 (c1, c2));
}

blackbox
query_coord4 (wk_widget w, string key, int type_id) {
  typedef quadruple<SI,SI,SI,SI> coord4;
  if (type_id != type_helper<coord4>::id)
    fatal_error ("type mismatch", "query_coord4");
  SI c1, c2, c3, c4;
  w << get_coord4 (key, c1, c2, c3, c4);
  return close_box<coord4> (coord4 (c1, c2, c3, c4));
}

/******************************************************************************
* Message passing
******************************************************************************/

void
wk_widget_rep::send (slot s, blackbox val) {
  switch (s) {
  case SLOT_NAME:
    send_string (THIS, "window name", val);
    break;

  case SLOT_SHRINKING_FACTOR:
    send_int (THIS, "shrinking factor", val);
    break;
  case SLOT_EXTENTS:
    send_coord4 (THIS, "extents", val);
    break;
  case SLOT_SCROLLBARS_VISIBILITY:
    send_int (THIS, "scrollbars", val);
    break;
  case SLOT_SCROLL_POSITION:
    send_coord2 (THIS, "scroll position", val);
    break;

  case SLOT_HEADER_VISIBILITY:
    send_bool (THIS, "header", val);
    break;
  case SLOT_MAIN_MENU:
    send_widget (THIS, "menu bar", val);
    break;
  case SLOT_MAIN_ICONS_VISIBILITY:
    send_bool (THIS, "main icons", val);
    break;
  case SLOT_MAIN_ICONS:
    send_widget (THIS, "main icons bar", val);
    break;
  case SLOT_CONTEXT_ICONS_VISIBILITY:
    send_bool (THIS, "context icons", val);
    break;
  case SLOT_CONTEXT_ICONS:
    send_widget (THIS, "context icons bar", val);
    break;
  case SLOT_USER_ICONS_VISIBILITY:
    send_bool (THIS, "user icons", val);
    break;
  case SLOT_USER_ICONS:
    send_widget (THIS, "user icons bar", val);
    break;
  case SLOT_FOOTER_VISIBILITY:
    send_bool (THIS, "footer flag", val);
    break;
  case SLOT_LEFT_FOOTER:
    send_string (THIS, "left footer", val);
    break;
  case SLOT_RIGHT_FOOTER:
    send_string (THIS, "right footer", val);
    break;
  case SLOT_INTERACTIVE_MODE:
    send_bool (THIS, "interactive mode", val);
    break;
  case SLOT_INTERACTIVE_PROMPT:
    send_widget (THIS, "interactive prompt", val);
    break;
  case SLOT_INTERACTIVE_INPUT:
    send_widget (THIS, "interactive input", val);
    break;
  default:
    fatal_error ("cannot handle message type",
		 "wk_widget_rep::set_blackbox");
  }
}

blackbox
wk_widget_rep::query (slot s, int type_id) {
  switch (s) {
  case SLOT_EXTENTS:
    return query_coord4 (THIS, "extents", type_id);
  case SLOT_VISIBLE_PART:
    return query_coord4 (THIS, "visible", type_id);
  case SLOT_SCROLLBARS_VISIBILITY:
    return query_int (THIS, "scrollbars", type_id);
  case SLOT_SCROLL_POSITION:
    return query_coord2 (THIS, "scroll position", type_id);

  case SLOT_HEADER_VISIBILITY:
    return query_bool (THIS, "header", type_id);
  case SLOT_MAIN_ICONS_VISIBILITY:
    return query_bool (THIS, "main icons", type_id);
  case SLOT_CONTEXT_ICONS_VISIBILITY:
    return query_bool (THIS, "context icons", type_id);
  case SLOT_USER_ICONS_VISIBILITY:
    return query_bool (THIS, "user icons", type_id);
  case SLOT_FOOTER_VISIBILITY:
    return query_bool (THIS, "footer flag", type_id);
  case SLOT_INTERACTIVE_MODE:
    return query_bool (THIS, "interactive mode", type_id);
  case SLOT_INTERACTIVE_INPUT:
    return query_string (THIS, "interactive input", type_id);
  default:
    fatal_error ("cannot handle message type",
		 "wk_widget_rep::set_blackbox");
    return blackbox ();
  }
}
