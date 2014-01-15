/******************************************************************************
 * MODULE     : qt_ui_element.cpp
 * DESCRIPTION: User interface proxies
 * COPYRIGHT  : (C) 2010  Massimiliano Gubinelli
 *******************************************************************************
 * This software falls under the GNU general public license version 3 or later.
 * It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
 * in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
 ******************************************************************************/

#include "qt_utilities.hpp"
#include "qt_renderer.hpp"
#include "qt_widget.hpp"
#include "qt_ui_element.hpp"
#include "qt_simple_widget.hpp"
#include "qt_window_widget.hpp"
#include "qt_menu.hpp"
#include "qt_gui.hpp"
#include "qt_picture.hpp"

#include "analyze.hpp"
#include "widget.hpp"
#include "message.hpp"
#include "promise.hpp"
#include "scheme.hpp"

#include "QTMWindow.hpp"
#include "QTMGuiHelper.hpp"
#include "QTMMenuHelper.hpp"
#include "QTMStyle.hpp"
#include "QTMApplication.hpp"
#include "QTMTreeModel.hpp"

#include <QCheckBox>
#include <QPushButton>
#include <QSplitter>
#include <QTreeView>

/******************************************************************************
 * Auxiliary classes
 ******************************************************************************/

QTMMenuButton::QTMMenuButton (QWidget* parent) : QToolButton(parent) {
  QTMAuxMenu m;
  m.myInitStyleOption (&option);
  setAttribute (Qt::WA_Hover);
}

void
QTMMenuButton::mousePressEvent (QMouseEvent* event) {
  // this one triggers the action and toggles the button
  QToolButton::mousePressEvent (event);
  // this one forwards the event to the parent
  // (which eventually is the menu)
  QWidget::mousePressEvent (event);
}

void
QTMMenuButton::mouseReleaseEvent (QMouseEvent* event) {
  // this one triggers the action and untoggles the button
  QToolButton::mouseReleaseEvent (event);
  // this one forwards the event to the parent
  // (which eventually is the menu which then closes itself)
  QWidget::mouseReleaseEvent (event);
}

void
QTMMenuButton::paintEvent (QPaintEvent* event) {
  (void) event;
  QPainter p (this);
  
  // initialize the options
  QStyleOptionToolButton buttonOpt;
  initStyleOption (&buttonOpt);
  QRect r = rect ();
  option.rect = r;
  option.state = QStyle::State_Enabled |
  ( buttonOpt.state & QStyle::State_MouseOver ? 
   QStyle::State_Selected : QStyle::State_None ); 
  // draw the control background as a menu item
  style () -> drawControl (QStyle::CE_MenuItem, &option, &p, this); 
  // draw the icon with a bit of inset.
  r.adjust (2,2,-2,-2);
  defaultAction ()-> icon ().paint (&p, r);
}

QTMMenuWidget::QTMMenuWidget (QWidget* parent): QWidget(parent) {
  QTMAuxMenu m;
  m.myInitStyleOption (&option);
}

void
QTMMenuWidget::paintEvent(QPaintEvent* event) {
  (void) event;
  QPainter p (this);
  option.rect = rect ();
  //QRect r = rect ();
  style()->drawControl (QStyle::CE_MenuEmptyArea, &option, &p, this);
  QWidget::paintEvent(event);
}


/*! A QToolButton which draws itself using its defaultAction()'s icon. */
class QTMUIButton: public QToolButton {
public:
  QTMUIButton (QWidget* parent = NULL): QToolButton(parent) {}
  void paintEvent(QPaintEvent *event);
};

void
QTMUIButton::paintEvent(QPaintEvent* event) {
  (void) event;
  QPainter p (this);
  defaultAction()->icon().paint (&p, rect ());
}

/******************************************************************************
 * Ad-hoc command_rep derivates for different UI elements in qt_ui_element_rep
 ******************************************************************************/

/*! Ad-hoc command to be used to simulate keypresses
 
 \sa qt_ui_element, , qt_ui_element_rep::as_qaction
 */

class qt_key_command_rep: public command_rep {
  string ks; 
  
public:
  qt_key_command_rep(string ks_) : ks(ks_) { }
  
  void apply () {
    if (N(ks)) { 
      QTMWidget *w = qobject_cast<QTMWidget*>(qApp->focusWidget());
      if (w && w->tm_widget()) {
        if (DEBUG_QT) debug_qt << "shortcut: " << ks << LF;
        the_gui->process_keypress (w->tm_widget(), ks, texmacs_time());
      }
    }
  }
  
  tm_ostream& print (tm_ostream& out) { return out << "qt_key_command_rep"; }
};


/*! Ad-hoc command to be used with toggle widgets.
 
 The command associated with a qt_ui_element::toggle_widget has as a parameter the state
 of the QCheckBox. Since it is assumed everywhere else that commands injected into
 the gui's queue accept no parameters, and changes would be too big, we choose to
 encapsulate the original command in a new one which will execute the first with
 its argument.
 \sa qt_ui_element, , qt_ui_element_rep::as_qwidget, qt_ui_element_rep::toggle_widget
 */
class qt_toggle_command_rep: public command_rep {
  QPointer<QCheckBox> qwid;
  command cmd; 
  
public:
  qt_toggle_command_rep(QCheckBox* w, command c) : qwid(w), cmd(c) { }
  void apply () { if (qwid) cmd (list_object (object (qwid->isChecked()))); }

  tm_ostream& print (tm_ostream& out) { return out << "Toggle"; }
};

/*! Ad-hoc command to be used with enum widgets.
 
 The command associated with a qt_ui_element::enum_widget has one parameter. For the
 reason to be of this class, see \sa qt_toggle_command_rep .
 \sa qt_ui_element, , qt_ui_element_rep::as_qwidget, qt_ui_element_rep::enum_widget
 */
class qt_enum_command_rep: public command_rep {
  QPointer<QComboBox> qwid;
  command cmd; 
  
public:
  qt_enum_command_rep(QComboBox* w, command c) : qwid(w), cmd(c) {}
  void apply () { 
    if (qwid)
      cmd (list_object (object (from_qstring(qwid->currentText()))));
  }
  
  tm_ostream& print (tm_ostream& out) { return out << "Enum"; }
};


/******************************************************************************
 * glue widget
 ******************************************************************************/

QPixmap 
qt_glue_widget_rep::render () {
  QSize s = to_qsize (w, h);
  QPixmap pxm(s);
    //cout << "glue (" << s.width() << "," << s.height() << ")\n";
  pxm.fill (Qt::transparent);
  QPaintDevice *pd = static_cast<QPaintDevice*>(&pxm);
  
  if (pd && !pxm.isNull()) {
    qt_renderer_rep* ren = the_qt_renderer();
    ren->begin (pd);
    rectangle r = rectangle (0, 0, s.width(), s.height());
    ren->set_origin (0,0);
    ren->encode (r->x1, r->y1);
    ren->encode (r->x2, r->y2);
    ren->set_clipping (r->x1, r->y2, r->x2, r->y1);
    
    if (col == "") {
        // do nothing
    } else {
      if (is_atomic (col)) {
        color c = named_color (col->label);
        ren->set_background (c);
        ren->set_pencil (c);
        ren->fill (r->x1, r->y2, r->x2, r->y1);
      } else {
        ren->set_shrinking_factor (std_shrinkf);
        brush old_b = ren->get_background ();
        ren->set_background (col);
        ren->clear_pattern (5*r->x1, 5*r->y2, 5*r->x2, 5*r->y1);
        ren->set_background (old_b);
        ren->set_shrinking_factor (1);
      }
    }
    ren->end();
  }
  
  return pxm;  
}

QAction *
qt_glue_widget_rep::as_qaction() {
  QAction* a = new QTMAction();
  a->setText (to_qstring (as_string (col)));
  QIcon icon;
#if 0
  tree old_col = col;
  icon.addPixmap (render(), QIcon::Active, QIcon::On);
  col = "";
  icon.addPixmap (render(), QIcon::Normal, QIcon::On);
  col = old_col;
#else
  icon.addPixmap (render ());
#endif
  a->setIcon (icon);  
  a->setEnabled (false);
  return a;
}

QWidget *
qt_glue_widget_rep::as_qwidget() {
  QLabel* qw = new QLabel();
  qw->setText (to_qstring (as_string (col)));
  qw->setPixmap (render ());
  qw->setMinimumSize (to_qsize (w, h));
    //  w->setEnabled(false);
  qwid = qw;
  return qwid;
}


/******************************************************************************
 * qt_ui_element_rep
 ******************************************************************************/

qt_ui_element_rep::qt_ui_element_rep (types _type, blackbox _load)
: qt_widget_rep (_type), load (_load), cachedAction (NULL), cachedMenu (NULL) {}

/*!
 WARNING: Deleting here the cachedAction would contradict our memory policy
 in qt_menu_rep and lead to crashes
 
 HOWEVER: if we have a cachedMenu, it means somebody promoted us to managers
 of a root menu which we have to delete. But we MUST ensure nobody calls
 get_qmenu() when they shouldn't.
 */
qt_ui_element_rep::~qt_ui_element_rep() {
  if (cachedMenu)
    cachedMenu->deleteLater();
}

blackbox
qt_ui_element_rep::get_load (qt_widget qtw, types check_type) {
  ASSERT (check_type == none || qtw->type == check_type,
          c_string ("get_load: widget " * qtw->type_as_string() *
                    " was not of the expected type."));
  switch (qtw->type) {
    case horizontal_menu:   case vertical_menu:    case horizontal_list:
    case vertical_list:     case tile_menu:        case aligned_widget:
    case minibar_menu:      case menu_separator:   case menu_group:
    case pulldown_button:   case pullright_button: case menu_button:
    case text_widget:       case xpm_widget:       case toggle_widget:
    case enum_widget:       case choice_widget:    case filtered_choice_widget:
    case scrollable_widget: case hsplit_widget:    case vsplit_widget:
    case tabs_widget:       case icon_tabs_widget: case resize_widget:
    case refresh_widget:    case refreshable_widget:  case balloon_widget:
    case glue_widget:
    {
      qt_ui_element_rep* rep = static_cast<qt_ui_element_rep*> (qtw.rep);
      return rep->load;
    }
      break;
    default:
      return blackbox();
  }
}

/*! Returns the ui element as a popup widget.
 If the widget is of type vertical_menu, it is understood that the popup widget
 must be of the standard OS dependent type implemented by qt_menu_rep using
 QMenu.
 */
widget 
qt_ui_element_rep::make_popup_widget () {
  if (type == qt_widget_rep::vertical_menu)
    return tm_new<qt_menu_rep> (this);
  else
    return qt_widget_rep::make_popup_widget();
}

/*! Returns a QMenu* to be installed in the menu bar.
 This method *DOES NOT* transfer ownership to the caller. On the contrary, it
 "promotes" this qt_ui_element_rep to responsible for its deletion.
 */
QMenu*
qt_ui_element_rep::get_qmenu() {
  if (!cachedMenu) cachedMenu = as_qaction()->menu();
  return cachedMenu;
}

/*! For the refresh_widget
 * FIXME? Is this really used?
 */
qt_ui_element_rep::operator tree () {
  if (type == refresh_widget) {
    typedef pair<string, string> T;
    T x= open_box<T> (load);
    return tree (TUPLE, "refresh", x.x1, x.x2);
  }
  else if (type == refreshable_widget) {
    typedef pair<object, string> T;
    T x= open_box<T> (load);
    return tree (TUPLE, "refreshable", x.x2);
  }
  else {
    return tree();
  }
}

QAction* 
qt_ui_element_rep::as_qaction () {
  //if (DEBUG_QT_WIDGETS)
  //debug_widgets << "as_qaction: " << type_as_string() << LF;

  if (cachedAction)
    return cachedAction;

  switch (type) {
    case vertical_menu:
    case horizontal_menu:
    case vertical_list:
        // a vertical menu made up of the widgets in arr
    {
      typedef array<widget> T;
      array<widget> arr = open_box<T> (load);
      
      QAction* act = new QTMAction (NULL);
      act->setText (qt_translate ("Menu"));
      QMenu* m = new QMenu ();
      for (int i = 0; i < N(arr); i++) {
        if (is_nil (arr[i])) break;
        QAction* a = concrete (arr[i])->as_qaction ();
        m->addAction (a);
        a->setParent (m);
      }
      act->setMenu (m);
      cachedAction = act;
    }
      break;
    
    case horizontal_list:
        // an horizontal list made up of the widgets in arr
    {
      typedef array<widget> T;
      array<widget> arr = open_box<T> (load);
      cachedAction = new QTMMinibarAction (NULL, arr);
    }
      break;
      
    case aligned_widget:
        //  a table with two columns FIXME!!!!
    {
      typedef triple<array<widget>, array<widget>, coord4 > T;
      T x = open_box<T>(load);
      array<widget> lhs = x.x1;
      array<widget> rhs = x.x2;

      if (N(lhs) != N(rhs)) FAILED("aligned_widget: N(lhs) != N(rhs) ");
      
      array<widget> wids(N(lhs)*3);
      for (int i=0; i < N(lhs); ++i) {
        wids[3*i]   = lhs[i];
        wids[3*i+1] = rhs[i];
        wids[3*i+2] = ::glue_widget(false, true, 1, 1);
      }

      cachedAction = new QTMMinibarAction (NULL, wids);
    }
      break;

    case tile_menu:
        // a menu rendered as a table of "cols" columns & made up of the widgets
        // in array a
    {
      typedef pair<array<widget>, int> T;
      T             x = open_box<T>(load);
      array<widget> a = x.x1;
      int        cols = x.x2;

      cachedAction = new QTMTileAction (NULL, a, cols);
    }
      break;
      
    case minibar_menu: 
    {
      typedef array<widget> T;
      array<widget> arr = open_box<T> (load);

      cachedAction = new QTMMinibarAction (NULL, arr);
    }
      break;
      
    case menu_separator:
        // a horizontal or vertical menu separator
    {
      cachedAction = new QTMAction (NULL);
      cachedAction->setSeparator (true);
    }
      break;

    case glue_widget:
    {
      cachedAction = new QTMAction();
      cachedAction->setEnabled(false);
    }
      break;

    case menu_group:
        // a menu group; the name should be greyed and centered
    {
      typedef pair<string, int> T;
      T         x = open_box<T> (load);
      string name = x.x1;
      int   style = x.x2;  //FIXME: ignored. Use a QWidgeAction to use it?
      
      cachedAction = new QTMAction (NULL);
      cachedAction->setText (to_qstring (name));
      cachedAction->setEnabled (false);
      cachedAction->setFont (to_qfont (style, cachedAction->font())); 
    }
      break;
      
    case pulldown_button:
    case pullright_button:
        // a button w with a lazy pulldown menu pw
    {
      typedef pair<widget, promise<widget> > T;
      T                x = open_box<T> (load);
      qt_widget      qtw = concrete (x.x1);
      promise<widget> pw = x.x2;

      cachedAction    = qtw->as_qaction ();
      QTMLazyMenu* lm = new QTMLazyMenu (pw);
      lm->attachTo (cachedAction);  // lm deletes itself after cachedAction dies
      cachedAction->setEnabled (true);
    }
      break;
      
    case menu_button:
        // a command button with an optional prefix (o, * or v) and
        // keyboard shortcut; if ok does not hold, then the button is greyed
    {
      typedef quintuple<widget, command, string, string, int> T;
      T x = open_box<T> (load);

      qt_widget qtw = concrete (x.x1);
      command   cmd = x.x2;
      string   pre  = x.x3;
      string   ks   = x.x4;
      int   style   = x.x5;
      
      QTMCommand* c;
      cachedAction = qtw->as_qaction();
      const QKeySequence& qks = to_qkeysequence (ks);
      if (!qks.isEmpty()) {
        cachedAction->setShortcut (qks);
        command key_cmd = tm_new<qt_key_command_rep> (ks);
        c= new QTMCommand (cachedAction, key_cmd);
      } else {
        c= new QTMCommand (cachedAction, cmd);
      }
        
      // NOTE: this used to be a Qt::QueuedConnection, but the slot would not
      // be called if in a contextual menu
      QObject::connect (cachedAction, SIGNAL (triggered()), c, SLOT (apply()));    
  
      bool ok = (style & WIDGET_STYLE_INERT) == 0;
      cachedAction->setEnabled (ok? true: false);
      
        // FIXME: implement complete prefix handling
      bool check = (pre != "") || (style & WIDGET_STYLE_PRESSED);
      cachedAction->setCheckable (check? true: false);
      cachedAction->setChecked (check? true: false);
      if (pre == "v") {}
      else if (pre == "*") {}
      // [mi setOnStateImage:[NSImage imageNamed:@"TMStarMenuBullet"]];
      else if (pre == "o") {}
    }
      break;
      
    case balloon_widget:
        // Given a button widget w, specify a help balloon which should be
        // displayed when the user leaves the mouse pointer on the button for a
        // small while
    {
      typedef pair<widget, widget> T;
      T            x = open_box<T> (load);
      qt_widget  qtw = concrete (x.x1);
      qt_widget help = concrete (x.x2);

      cachedAction = qtw->as_qaction();
      {
        typedef quartet<string, int, color, bool> T1;
        T1 y = open_box<T1> (get_load (help, text_widget));
        cachedAction->setToolTip (to_qstring (y.x1));
        // HACK: force displaying of the tooltip (needed for items in the QMenuBar)
        QObject::connect (cachedAction, SIGNAL(hovered()),
                          cachedAction, SLOT(showToolTip()));
      }
    }
      break;
      
    case text_widget:
        // A text widget with a given color and transparency
    {
      typedef quartet<string, int, color, bool> T;
      T x = open_box<T>(load);
      string str = x.x1;
      int style  = x.x2;
      //color col  = x.x3;
      //bool tsp   = x.x4;

      QTMAction* a = new QTMAction (NULL);
      a->set_text (str);
      a->setFont (to_qfont (style, a->font()));
      cachedAction = a;
    }
      break;
      
    case xpm_widget:
        // a widget with an X pixmap icon
    {
      url    image = open_box<url>(load);
      cachedAction = new QTMAction (NULL);
      cachedAction->setIcon (QIcon (as_pixmap (*xpm_image (image))));
    }
      break;

    default:
      FAILED (c_string ("qt_ui_element: unknown type for as_qaction, "
                        * type_as_string()));
  }
  return cachedAction;
}


QLayoutItem *
qt_ui_element_rep::as_qlayoutitem () {
  if (DEBUG_QT_WIDGETS)
    debug_widgets << "as_qlayoutitem: " << type_as_string() << LF;

  switch (type) {
    case horizontal_menu:
    case vertical_menu:
    case horizontal_list:
    case vertical_list:
    {
      typedef array<widget> T;
      T arr = open_box<T> (load);

      QLayout *l;
      if ((type == horizontal_list) || (type==horizontal_menu))
        l = new QHBoxLayout();
      else
        l = new QVBoxLayout();

      l->setSpacing(0);

      if (N(arr) > 0 && concrete(arr[0]).rep &&
          (concrete(arr[0]).rep->type == tabs_widget ||
           concrete(arr[0]).rep->type == icon_tabs_widget))  // HACK!
        l->setContentsMargins(0, 6, 0, 0);
      else
        l->setContentsMargins(0, 0, 0, 0);

      for (int i = 0; i < N(arr); i++) {
        if (is_nil (arr[i])) break;
        QLayoutItem* li = concrete (arr[i])->as_qlayoutitem ();
        if (li) l->addItem(li); // ownership transferred
      }

      return l;
    }

    case tile_menu:
    {
      typedef array<widget> T1;
      typedef pair<T1, int> T;
      T  x     = open_box<T> (load);
      T1 a     = x.x1;
      int cols = x.x2;
            
      QGridLayout* l = new QGridLayout ();
      l->setSizeConstraint (QLayout::SetFixedSize);
      l->setHorizontalSpacing (2);
      l->setVerticalSpacing (2);
      l->setContentsMargins (4, 0, 4, 0);
      int row= 0, col= 0;
      for (int i=0; i < N(a); i++) {
        QLayoutItem* li = concrete(a[i])->as_qlayoutitem();
        l->addItem(li, row, col);
        col++;
        if (col >= cols) { col = 0; row++; }
      }
      return l;
    }

    case aligned_widget:
        //  a table with two columns (FIXME!)
    {
      typedef array<widget> T2;
      typedef triple<T2, T2, coord4 > T;
      T      x = open_box<T>(load);
      T2   lhs = x.x1;
      T2   rhs = x.x2;
      coord4 y = x.x3;

      // FIXME: lpad and rpad ignored.
      SI hsep = y.x1; SI vsep = y.x2; SI lpad = y.x3; SI rpad = y.x4;
      (void) lpad; (void) rpad;
     
      if (N(lhs) != N(rhs)) FAILED("aligned_widget: N(lhs) != N(rhs) ");
      
        /* FIXME? From the docs:
         If the QGridLayout is not the top-level layout (i.e. does not manage 
         all of the widget's area and children), you must add it to its parent 
         layout when you create it, but before you do anything with it. 
         */
      QGridLayout* l = new QGridLayout ();
      l->setAlignment (Qt::AlignLeft);  // Don't center items automatically
      l->setSizeConstraint (QLayout::SetMinAndMaxSize);
      l->setHorizontalSpacing (6+hsep/PIXEL);
      l->setVerticalSpacing (6+vsep/PIXEL);
      for (int i=0; i < N(lhs); i++) {
        QLayoutItem* lli = concrete(lhs[i])->as_qlayoutitem();
        QLayoutItem* rli = concrete(rhs[i])->as_qlayoutitem();
        if (lli) l->addItem (lli, i, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
        if (rli) l->addItem (rli, i, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
      }
      return l;
    }
      
    case minibar_menu: 
    {
      typedef array<widget> T;
      array<widget> arr = open_box<T> (load);
      QBoxLayout* l= new QBoxLayout (QBoxLayout::LeftToRight);
      l->setContentsMargins (0, 0, 0, 0);
      l->setSpacing (0);
      for (int i = 0; i < N(arr); i++) {
        QLayoutItem* li = concrete(arr[i])->as_qlayoutitem();
        l->addItem(li);
      }
      return l;
    }
      
    case menu_separator: 
    {
      typedef bool T;
      T vertical = open_box<T> (load);
      QSizePolicy::Policy hpolicy = vertical ? QSizePolicy::Fixed 
                                             : QSizePolicy::Preferred;
      QSizePolicy::Policy vpolicy = vertical ? QSizePolicy::Preferred 
                                             : QSizePolicy::Fixed;
      return new QSpacerItem (1, 1, hpolicy, vpolicy);
    }
      
    case menu_group:
    {
      return NULL;
    }

    case pulldown_button:
    case pullright_button:
    case menu_button:
    case text_widget:
    case xpm_widget:
    case toggle_widget:
    case enum_widget:
    case choice_widget:
    case filtered_choice_widget:
    case tree_view_widget:
    case scrollable_widget:
    case hsplit_widget:
    case vsplit_widget:
    case tabs_widget:
    case icon_tabs_widget:
    case resize_widget:
    case refresh_widget:
    case refreshable_widget:
    case balloon_widget:
    {
      QWidgetItem* wi = new QWidgetItem (this->as_qwidget());
      return wi;
    }
      break;

    case glue_widget:
        // Used only for non-colored glue widgets (skips qt_glue_widget_rep)
    {
      typedef quartet<bool, bool, SI, SI> T;
      T x = open_box<T>(load);

      QSizePolicy::Policy hpolicy = x.x1 ? QSizePolicy::MinimumExpanding
                                         : QSizePolicy::Minimum;
      QSizePolicy::Policy vpolicy = x.x2 ? QSizePolicy::MinimumExpanding
                                         : QSizePolicy::Minimum;

      return new QSpacerItem (x.x3, x.x4, hpolicy, vpolicy);
    }
      break;
    default:
      ;
  }
  
  return NULL;
}

/*
 Because our policy is that the returned QWidget is owned by the caller, we
 must be careful and any QObjects we construct here must have the returned 
 QWidget as parent.
*/
QWidget *
qt_ui_element_rep::as_qwidget () {
  if (DEBUG_QT_WIDGETS)
    debug_widgets << "as_qwidget: " << type_as_string() << LF;

    // Don't return the cached widget, this only happens for refresh_widgets
    // and then we crash.
//  if (qwid) return qwid;
  
  switch (type) {
    case horizontal_menu:
    case vertical_menu:
    case horizontal_list:
    case vertical_list:
    case tile_menu: 
    case minibar_menu: 
    case aligned_widget: 
    {
        // note that the QLayout is the same object as the QLayoutItem 
        // so no need to free the layoutitem
      QLayout* l = this->as_qlayoutitem()->layout();
      QWidget* w = new QWidget();
      if (l)
        w->setLayout(l);
      else if (DEBUG_QT_WIDGETS)
          // should we create a default layout?
        debug_widgets << "qt_ui_element_rep::as_qwidget(): "
                      << "invalid situation" << LF;
      qwid = w;
    }
      break;
      
    case resize_widget:
    {
      typedef triple <string, string, string> T1;
      typedef quartet <widget, int, T1, T1 > T;
      T x = open_box<T>(load);

      qt_widget wid = concrete(x.x1);
      int     style = x.x2;
      T1     widths = x.x3;
      T1    heights = x.x4;
      
      qwid = wid->as_qwidget();
      qt_apply_tm_style (qwid, style);
      
      QSize minSize = qt_decode_length (widths.x1, heights.x1,
                                        qwid->minimumSizeHint(),
                                        qwid->fontMetrics());
      QSize defSize = qt_decode_length (widths.x2, heights.x2,
                                        qwid->minimumSizeHint(),
                                        qwid->fontMetrics());
      QSize maxSize = qt_decode_length (widths.x3, heights.x3,
                                        qwid->minimumSizeHint(),
                                        qwid->fontMetrics());

      if (minSize == defSize && defSize == maxSize) {        
        qwid->setFixedSize (defSize);
        qwid->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
      } else {
        qwid->setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Ignored);
        qwid->setMinimumSize (minSize);
        qwid->setMaximumSize (maxSize);
        qwid->resize (defSize);
      }
    }
      break;
      
    case menu_separator: 
    case menu_group:
    case glue_widget:
    {
      qwid = new QWidget();
    }
      break;
      
    case pulldown_button:
    case pullright_button:
    {
      typedef pair<widget, promise<widget> > T;
      T                x = open_box<T> (load);
      qt_widget      qtw = concrete (x.x1);
      promise<widget> pw = x.x2;
    
      QPushButton* b  = new QPushButton();
      QTMLazyMenu* lm = new QTMLazyMenu (pw, b);
      b->setMenu (lm);
      b->setAutoDefault (false);
      if (qtw->type == xpm_widget) {
        url image = open_box<url> (get_load (qtw));
        b->setIcon (QIcon (as_pixmap (*xpm_image (image))));
      } else if (qtw->type == text_widget) {
        typedef quartet<string, int, color, bool> T1;
        T1 y = open_box<T1> (get_load (qtw));
        b->setText (to_qstring (y.x1));
      }
      qwid = b;
    }
      break;
      
        // a command button with an optional prefix (o, * or v) and (sometimes) 
        // keyboard shortcut
    case menu_button:
    {
      typedef quintuple<widget, command, string, string, int> T;
      T x = open_box<T>(load);
      qt_widget qtw = concrete(x.x1); // contents: xpm_widget, text_widget, ...?
      command   cmd = x.x2;
      string    pre = x.x3;
      string     ks = x.x4;
      int     style = x.x5;
      
      if (qtw->type == xpm_widget) {  // Toolbar button
        QAction*     a = as_qaction();        // Create key shortcuts and actions
        QTMUIButton* b = new QTMUIButton();
        b->setDefaultAction (a);
        a->setParent (b);
        qwid = b;
      } else { // text_widget
        QPushButton*     b = new QPushButton();
        QTMCommand* qtmcmd = new QTMCommand (b, cmd);
        QObject::connect (b, SIGNAL (clicked ()), qtmcmd, SLOT (apply ()));
        if (qtw->type == text_widget) {
          typedef quartet<string, int, color, bool> T1;
          b->setText (to_qstring (open_box<T1> (get_load (qtw)).x1));
          qt_apply_tm_style (b, style);
        }
        b->setFlat (! (style & WIDGET_STYLE_BUTTON));
        qwid = b;
      }
      qwid->setEnabled (! (style & WIDGET_STYLE_INERT));
    }
      break;
      
      // given a button widget w, specify a help balloon which should be displayed
      // when the user leaves the mouse pointer on the button for a small while
    case balloon_widget:
    {
      typedef pair<widget, widget> T;
      T            x = open_box<T>(load);
      qt_widget  qtw = concrete (x.x1);
      qt_widget help = concrete (x.x2);
      
      typedef quartet<string, int, color, bool> T1;
      T1 y = open_box<T1>(get_load (help, text_widget));
      QWidget* w = qtw->as_qwidget();
      w->setToolTip (to_qstring (y.x1));
      qwid = w;
    }
      break;
      
      // a text widget with a given color and transparency
    case text_widget:
    {
      typedef quartet<string, int, color, bool> T;
      T        x = open_box<T>(load);
      string str = x.x1;
      int  style = x.x2;
      color    c = x.x3;
        //bool      tsp = x.x4;  // FIXME: add transparency support
      
      QLabel* w = new QLabel();
      /*
      //FIXME: implement refresh when changing language
      QTMAction* a= new QTMAction (NULL);
      a->set_text (str);
       */
      w->setText (to_qstring (str));
      w->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
      // Workaround too small sizeHint() when the text has letters with descent:
      w->setMinimumHeight (w->fontMetrics().height());
      
      qt_apply_tm_style (w, style, c);
      qwid = w;
    }
      break;
      
      // a widget with an X pixmap icon
    case xpm_widget:
    {
      url image = open_box<url>(load);
      QLabel* l = new QLabel (NULL);
      l->setPixmap (as_pixmap (*xpm_image (image)));
      qwid = l;
    }
      break;
      
    case toggle_widget:
    {
      typedef triple<command, bool, int > T;
      T         x = open_box<T>(load);
      command cmd = x.x1;
      bool  check = x.x2;
      int   style = x.x3;
      
      QCheckBox* w  = new QCheckBox (NULL);  
      w->setCheckState (check ? Qt::Checked : Qt::Unchecked);
      qt_apply_tm_style(w, style);
      
      command tcmd = tm_new<qt_toggle_command_rep> (w, cmd);
      QTMCommand* c = new QTMCommand (w, tcmd);
      QObject::connect (w, SIGNAL (stateChanged(int)), c, SLOT (apply()));

      qwid = w;
    }
      break;
      
    case enum_widget:
    {
      typedef quintuple<command, array<string>, string, int, string> T;
      T                x = open_box<T>(load);
      command        cmd = x.x1;
      QStringList values = to_qstringlist (x.x2);
      QString      value = to_qstring (x.x3);
      int          style = x.x4;
            
      QTMComboBox* w = new QTMComboBox (NULL);
      if (values.isEmpty())
        values << QString("");  // safeguard

      w->setEditable (value.isEmpty() || values.last().isEmpty());  // weird convention?!
      if (values.last().isEmpty())
        values.removeLast();
      
      w->addItemsAndResize (values, x.x5, "");
      int index = w->findText (value, Qt::MatchFixedString | Qt::MatchCaseSensitive);
      if (index != -1)
        w->setCurrentIndex (index);
   
      qt_apply_tm_style (w, style);
      
      command  ecmd = tm_new<qt_enum_command_rep> (w, cmd);
      QTMCommand* c = new QTMCommand (w, ecmd);
      // NOTE: with QueuedConnections, the slots are sometimes not invoked.
      QObject::connect (w, SIGNAL (currentIndexChanged(int)), c, SLOT (apply()));
      
      qwid = w;
    }
      break;
      
      // select one or multiple values from a list
    case choice_widget:
    {
      typedef quartet<command, array<string>, array<string>, bool> T;
      T  x = open_box<T>(load);
      qwid = new QTMListView (x.x1, to_qstringlist(x.x2), to_qstringlist(x.x3),
                              x.x4);
    }
      break;

    case filtered_choice_widget:
    {
      typedef quartet<command, array<string>, string, string> T;
      T           x = open_box<T>(load);
      string filter = x.x4;
      QTMListView* choiceWidget = new QTMListView (x.x1, to_qstringlist (x.x2),
                                                   QStringList (to_qstring (x.x3)),
                                                   false, true, true);

      QTMLineEdit* lineEdit = new QTMLineEdit (0, "1w");
      QObject::connect (lineEdit, SIGNAL (textChanged (const QString&)),
                        choiceWidget->filter(), SLOT (setFilterRegExp (const QString&)));
      lineEdit->setText (to_qstring (filter));
      lineEdit->setFocusPolicy (Qt::StrongFocus);

      QVBoxLayout* layout = new QVBoxLayout ();
      layout->addWidget (lineEdit);
      layout->addWidget (choiceWidget);
      layout->setSpacing (0);
      layout->setContentsMargins (0, 0, 0, 0);
      
      qwid = new QWidget();
      qwid->setLayout (layout);
    }
      break;
      
    case tree_view_widget:
    {
      typedef triple<command, tree, tree> T;
      T  x = open_box<T>(load);
      qwid = new QTMTreeView (x.x1, x.x2, x.x3);  // command, data, roles
    }
      break;
      
    case scrollable_widget:
    {
      typedef pair<widget, int> T;
      T           x = open_box<T> (load);
      qt_widget wid = concrete (x.x1);
      int     style = x.x2;
      
      QTMScrollArea* w = new QTMScrollArea();
      w->setWidgetAndConnect (wid->as_qwidget());
      w->setWidgetResizable (true);

      qt_apply_tm_style (w, style);
        // FIXME????
        // "Note that You must add the layout of widget before you call this function;
        //  if you add it later, the widget will not be visible - regardless of when
        //  you show() the scroll area. In this case, you can also not show() the widget
        //  later."
      qwid = w;

    }
      break;
      
    case hsplit_widget:
    case vsplit_widget:
    {
      typedef pair<widget, widget> T;
      T          x = open_box<T>(load);
      qt_widget w1 = concrete(x.x1);
      qt_widget w2 = concrete(x.x2);
      
      QWidget* qw1 = w1->as_qwidget();
      QWidget* qw2 = w2->as_qwidget();
      QSplitter* split = new QSplitter();
      split->setOrientation(type == hsplit_widget ? Qt::Horizontal 
                                                  : Qt::Vertical);
      split->addWidget (qw1);
      split->addWidget (qw2);
      
      qwid = split;
    }
      break;
      
    case tabs_widget:
    {
      typedef array<widget> T1;
      typedef pair<T1, T1> T;
      T       x = open_box<T>(load);
      T1   tabs = x.x1;
      T1 bodies = x.x2;
      
      QTMTabWidget* tw = new QTMTabWidget ();
      
      int i;
      for (i = 0; i < N(tabs); i++) {
        if (is_nil (tabs[i])) break;
        QWidget* prelabel = concrete (tabs[i])->as_qwidget();
        QLabel*     label = qobject_cast<QLabel*> (prelabel);
        QWidget*     body = concrete (bodies[i])->as_qwidget();
        tw->addTab (body, label ? label->text() : "");
        delete prelabel;
      }

      if (i>0) tw->resizeOthers(0);   // Force the automatic resizing

      qwid = tw;
    }
      break;
      
    case icon_tabs_widget:
    {
      typedef array<url> U1;
      typedef array<widget> T1;
      typedef triple<U1, T1, T1> T;
      T       x = open_box<T>(load);
      U1  icons = x.x1;
      T1   tabs = x.x2;
      T1 bodies = x.x3;

      QTMTabWidget* tw = new QTMTabWidget ();
      int i;
      for (i = 0; i < N(tabs); i++) {
        if (is_nil (tabs[i])) break;
        QImage*       img = xpm_image (icons[i]);
        QWidget* prelabel = concrete (tabs[i])->as_qwidget();
        QLabel*     label = qobject_cast<QLabel*> (prelabel);
        QWidget*     body = concrete (bodies[i])->as_qwidget();
        tw->addTab (body, QIcon (as_pixmap (*img)), label ? label->text() : "");
        delete prelabel;
      }

      if (i>0) tw->resizeOthers(0);   // Force the automatic resizing

      qwid = tw;
    }
      break;
      
    case refresh_widget:
    {
      typedef pair<string, string> T;
      T  x = open_box<T> (load);
      qwid = new QTMRefreshWidget (this, x.x1, x.x2);
    }
      break;
            
    case refreshable_widget:
    {
      typedef pair<object, string> T;
      T  x = open_box<T> (load);
      qwid = new QTMRefreshableWidget (this, x.x1, x.x2);
    }
      break;
      
    default:
      qwid = NULL;
  }
  
    //qwid->setFocusPolicy (Qt::StrongFocus); // Bad idea: containers get focus
  if (qwid->objectName().isEmpty())
    qwid->setObjectName (to_qstring (type_as_string()));
  return qwid;
}
