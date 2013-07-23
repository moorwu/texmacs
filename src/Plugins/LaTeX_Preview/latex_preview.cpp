
/******************************************************************************
* MODULE     : latex_preview.cpp
* DESCRIPTION: generating pictures using LaTeX with preview package
* COPYRIGHT  : (C) 2013  François Poulain, Joris van der Hoeven
*******************************************************************************
* This software falls under the GNU general public license version 3 or later.
* It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
* in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
******************************************************************************/

#include "LaTeX_Preview/latex_preview.hpp"
#include "Ghostscript/gs_utilities.hpp"
#include "Tex/convert_tex.hpp"
#include "analyze.hpp"
#include "file.hpp"
#include "sys_utils.hpp"

static string latex_command= "pdflatex";

void
set_latex_command (string cmd) {
  latex_command= cmd;
}

bool
latex_present () {
  return exists_in_path (latex_command);
}

array<string>
search_inclusions (tree t) {
  array<string> r;
  int i, n= N(t);
  if (is_atomic (t));
  else if (is_tuple (t, "\\textm.include"))
    for (i=1; i<n; i++)
      r << as_string (t[i]);
  else {
    for (i=0; i<n; i++)
      r << search_inclusions (t[i]);
  }
  return r;
}

array<string>
search_latex_previews (tree t) {
  array<string> r;
  if (is_atomic (t));
  else if (is_tuple (t, "\\latex_preview", 2))
    r << as_string (t[1]);
  else {
    int i, n= N(t);
    for (i=0; i<n; i++)
      r << search_latex_previews (t[i]);
  }
  return r;
}

void
latex_clean_tmp_directory () {
  string cmdln= "cd $TEXMACS_HOME_PATH/system/pic; rm -rf *";
  if (DEBUG_AUTO) cout << "TeXmacs] LaTeX cleaning: " << cmdln << "\n";
  system (cmdln);
}

void
latex_install_preview (string s, tree t) {
  array<string> macros= search_latex_previews (t);
  array<string> incls= search_inclusions (t);
  string preview= "%%%%%%%%%%%%%% ADDED BY TEXMACS %%%%%%%%%%%%%%%%%%\n";
  preview  << "\\usepackage[active,tightpage,delayed]{preview}\n";
  for (int i=0; i<N(macros); i++) {
    int arity= latex_arity (macros[i]);
    bool option= (arity<0);
    string arity_code;
    if (option) {
      arity_code << "[]";
      arity= -arity;
    }
    while (arity-- > 0) arity_code << "{}";
    string name= "\\" * macros[i];
    string cmd= "\\PreviewMacro";
    if (test (name, 0, "\\begin-")) {
      name= name(7, N(name));
      cmd= "\\PreviewEnvironment";
    }
    preview << cmd << "[{" * arity_code * "}]{" * name * "}\n";
  }
  preview << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";

  int i= 0;
  i= search_forwards ("\\documentclass", i, s);
  i= search_forwards ("{", i, s);
  i= search_forwards ("}", i, s);
  i= search_forwards ("\n", i, s);
  i++;
  s= s(0, i) * preview * s(i, N(s));
  latex_clean_tmp_directory ();
  save_string ("$TEXMACS_HOME_PATH/system/pic/temp.tex", s);
}

tree
latex_load_image (url image) {
  string s;
  tree t (IMAGE, 5);
  load_string (image, s, false);
  if (s == "") {
    if (DEBUG_AUTO) cout << "Could not load " * as_string (image) * "\n";
    return array<tree> ();
  }
  int width, height;
  gs_image_size (image, width, height);
  t[0]= tuple (tree (RAW_DATA, s), "eps");
  t[1]= as_string (width) * "pt";
  t[2]= as_string (height) * "pt";
  return (t);
}

array<tree>
latex_load_preview () {
  string cmdln= "cd  $TEXMACS_HOME_PATH/system/pic/ ;";
  cmdln << "gs -sDEVICE=epswrite -dSAFER -q -dNOPAUSE -dBATCH "
    << "-dLanguageLevel=3 -sOutputFile=temp%d.eps temp.pdf";
  if (DEBUG_AUTO) cout << "TeXmacs] LaTeX command: " << cmdln << "\n";
  if (system (cmdln)) {
    if (DEBUG_AUTO) cout << "Could not extract pictures from LaTeX document\n";
    return array<tree> ();
  }
  unsigned int cnt= 1;
  bool stop= false;
  array<tree> r;
  while (!stop) {
    url u= url ("$TEXMACS_HOME_PATH/system/pic/temp" *as_string (cnt)* ".eps");
    if (exists (u))
      r << latex_load_image (u);
    else
      stop= true;
    cnt++;
  }
  return r;
}

array<tree>
latex_preview (string s, tree t) {
  if (!latex_present ()) return array<tree>();
  // FIXME: ./Texmacs/Window/tm_frame.cpp:191 seems to crash here if we launch
  // system_wait ("LaTeX: compiling document, ", "please wait");
  latex_install_preview (s, t);
  string document_root= as_string (head (get_file_focus ()));
  string cmdln= "cd " * document_root;
  cmdln << "; " << "pdflatex"
        << " -interaction nonstopmode -halt-on-error -file-line-error "
        << " -output-directory $TEXMACS_HOME_PATH/system/pic/ "
        << " $TEXMACS_HOME_PATH/system/pic/temp.tex ";
  if (DEBUG_AUTO) cout << "TeXmacs] LaTeX command: " << cmdln << "\n";
  if (system (cmdln)) {
    if (DEBUG_AUTO) cout << "Could not compile LaTeX document\n";
    return array<tree> ();
  }
  array<tree> r= latex_load_preview ();
  if (N(r) != N(search_latex_previews (t))) {
    if (DEBUG_AUTO) cout << "Warning: LaTeX importation could have failed\n";
  }
  return r;
} 
