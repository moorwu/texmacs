
/******************************************************************************
* MODULE     : string.cpp
* DESCRIPTION: Fixed size strings with reference counting.
*              Zero characters can be part of string.
* COPYRIGHT  : (C) 1999  Joris van der Hoeven
*******************************************************************************
* This software falls under the GNU general public license and comes WITHOUT
* ANY WARRANTY WHATSOEVER. See the file $TEXMACS_PATH/LICENSE for more details.
* If you don't have this file, write to the Free Software Foundation, Inc.,
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
******************************************************************************/

#include "string.hpp"
#include <stdio.h>
#include <string.h>

static inline int
round_length (int n) {
  n=(n+3)&(0xfffffffc);
  if (n<24) return n;
  register int i=32;
  while (n>i) i<<=1;
  return i;
}

string_rep::string_rep (int n2):
  n(n2), a ((n==0)?((char*) NULL):new char[round_length(n)]) {}

void
string_rep::resize (register int m) {
  register int nn= round_length (n);
  register int mm= round_length (m);
  if (mm != nn) {
    if (mm != 0) {
      register int i, k= (m<n? m: n);
      char* b= new char[mm];
      for (i=0; i<k; i++) b[i]= a[i];
      if (nn != 0) delete[] a;
      a= b;
    }
    else if (nn != 0) delete[] a;
  }
  n= m;
}

string::string (char c) {
  rep= new string_rep(1);
  rep->a[0]=c;
}

string::string (char *a) {
  register int i, n=strlen(a);
  rep= new string_rep(n);
  for (i=0; i<n; i++)
    rep->a[i]=a[i];
}

string::string (char* a, int n) {
  register int i;
  rep= new string_rep(n);
  for (i=0; i<n; i++)
    rep->a[i]=a[i];
}

bool
string::operator == (char* s) {
  register int i, n= rep->n;
  register char* S= rep->a;
  for (i=0; i<n; i++) {
    if (s[i]!=S[i]) return false;
    if (s[i]=='\0') return false;
  }
  return (s[i]=='\0');
}

bool
string::operator != (char* s) {
  register int i, n= rep->n;
  register char* S= rep->a;
  for (i=0; i<n; i++) {
    if (s[i]!=S[i]) return true;
    if (s[i]=='\0') return true;
  }
  return (s[i]!='\0');
}

bool
string::operator == (string a) {
  register int i;
  if (rep->n!=a->n) return false;
  for (i=0; i<rep->n; i++)
    if (rep->a[i]!=a->a[i]) return false;
  return true;
}

bool
string::operator != (string a) {
  register int i;
  if (rep->n!=a->n) return true;
  for (i=0; i<rep->n; i++)
    if (rep->a[i]!=a->a[i]) return true;
  return false;
}

string
string::operator () (int begin, int end) {
  register int i;
  string r (end-begin);
  for (i=begin; i<end; i++) r[i-begin]=rep->a[i];
  return r;
}

string
copy (string s) {
  register int i, n=N(s);
  string r (n);
  for (i=0; i<n; i++) r[i]=s[i];
  return r;
}

string&
operator << (string& a, char x) {
  a->resize (N(a)+ 1);
  a [N(a)-1]=x;
  return a;
}

string&
operator << (string& a, string b) {
  register int i, k1= N(a), k2=N(b);
  a->resize (k1+k2);
  for (i=0; i<k2; i++) a[i+k1]= b[i];
  return a;
}

string
operator * (string a, string b) {
  register int i, n1=N(a), n2=N(b);
  string c(n1+n2);
  for (i=0; i<n1; i++) c[i]=a[i];
  for (i=0; i<n2; i++) c[i+n1]=b[i];
  return c;
}

string
operator * (char* a, string b) {
  return string (a) * b;
}

string
operator * (string a, char* b) {
  return a * string (b);
}

bool
operator <= (string s1, string s2) {
  register int i;
  for (i=0; i<N(s1); i++) {
    if (i>=N(s2)) return false;
    if (s1[i]<s2[i]) return true;
    if (s2[i]<s1[i]) return false;
  }
  return true;
}

ostream&
operator << (ostream& out, string a) {
  int i, n=N(a);
  if (n==0) return out;
  for (i=0; i<n; i++) out << a[i];
  return out;
}

int
hash (string s) {
  register int i, h=0, n=N(s);
  for (i=0; i<n; i++) {
    h=(h<<9)+(h>>23);
    h=h+((int) s[i]);
  }
  return h;
}

bool
as_bool (string s) {
  return (s == "true");
}

int
as_int (string s) {
  int i=0, n=N(s), val=0;
  if (n==0) return 0;
  if (s[0]=='-') i++;
  while (i<n) {
    if (s[i]<'0') break;
    if (s[i]>'9') break;
    val *= 10;
    val += (int) (s[i]-'0');
    i++;
  }
  if (s[0]=='-') val=-val;
  return val;
}

double
as_double (string s) {
  double x= 0.0;
  {
    int i, n= N(s);
    STACK_NEW_ARRAY (buf, char, n+1);
    for (i=0; i<n; i++) buf[i]=s[i];
    buf[n]='\0';
    sscanf (buf, "%lf", &x);
    STACK_DELETE_ARRAY (buf);
  } // in order to avoid segmentation fault due to compiler bug
  return x;
}

char*
as_charp (string s) {
  int i, n=N(s);
  char *s2= new char[n+1];
  for (i=0; i<n; i++) s2[i]=s[i];
  s2[n]= '\0';
  return s2;
}

string
as_string_bool (bool f) {
    if (f) return string ("true");
    else return string ("false");
}

string
as_string (int i) {
  char buf[64];
  sprintf (buf, "%i", i);
  // sprintf (buf, "%i\0", i);
  return string(buf);
}

string
as_string (double x) {
  char buf[64];
  sprintf (buf, "%g", x);
  // sprintf (buf, "%g\0", x);
  return string(buf);
}

string
as_string (char* s) {
  return string (s);
}

bool
is_bool (string s) {
  return (s == "true") || (s == "false");
}

bool
is_int (string s) {
  int i=0, n=N(s);
  if (n==0) return false;
  if (s[i]=='+') i++;
  if (s[i]=='-') i++;
  if (i==n) return false;
  for (; i<n; i++)
    if ((s[i]<'0') || (s[i]>'9')) return false;
  return true;
}

bool
is_double (string s) {
  int i=0, n=N(s);
  if (n==0) return false;
  if (s[i]=='+') i++;
  if (s[i]=='-') i++;
  if (i==n) return false;
  for (; i< n; i++)
    if ((s[i]<'0') || (s[i]>'9')) break;
  if (i==n) return true;
  if (s[i]=='.') {
    i++;
    if (i==n) return false;
    for (; i< n; i++)
      if ((s[i]<'0') || (s[i]>'9')) break;
  }
  if (i==n) return true;
  if (s[i++]!='e') return false;
  if (s[i]=='+') i++;
  if (s[i]=='-') i++;
  if (i==n) return false;
  for (; i< n; i++)
    if ((s[i]<'0') || (s[i]>'9')) return false;
  return true;
}

bool
is_charp (string s) { (void) s;
  return true;
}

bool
is_quoted (string s) {
  return (N(s)>=2) && (s[0]=='\042') && (s[N(s)-1]=='\042');
}

bool
is_id (string s) {
  int i=0, n=N(s);
  if (n==0) return false;
  for (i=0; i< n; i++) {
    if ((i>0) && (s[i]>='0') && (s[i]<='9')) continue;
    if ((s[i]>='a') && (s[i]<='z')) continue;
    if ((s[i]>='A') && (s[i]<='Z')) continue;
    if (s[i]=='_') continue;
    return false;
  }
  return true;
}

/******************************************************************************
* Error messages
******************************************************************************/

static void (*the_info_handler) (string, string, int) = NULL;
static void (*the_wait_handler) (string, string, int) = NULL;
static void (*the_warning_handler) (string, string, int) = NULL;
static void (*the_error_handler) (string, string, int) = NULL;

void
fatal_error (string message, string routine, string file) {
  cerr << "\nFatal error: " << message << " in '" << routine << "'\n";
  if (N(file)!=0) cerr << "See file   : " << file << "\n";
  cout << 1/0 << "\n";
  exit (1);
}

void
set_info_handler (void (*routine) (string, string, int)) {
  the_info_handler= routine; }

void
system_info (string message, string argument, int level) {
  if (DEBUG_AUTO)
    cout << "TeXmacs] " << message << " " << argument << LF;
  if (the_info_handler != NULL)
    the_info_handler (message, argument, level);
}

void
set_wait_handler (void (*routine) (string, string, int)) {
  the_wait_handler= routine; }

void
system_wait (string message, string argument, int level) {
  if (the_wait_handler == NULL) {
    if (DEBUG_AUTO) {
      if (message == "") cout << "TeXmacs] Done" << LF;
      else {
	if (argument == "") cout << "TeXmacs] " << message << LF;
	else cout << "TeXmacs] " << message << " " << argument << LF;
	cout << "TeXmacs] Please wait..." << LF;
      }
    }
  }
  else the_wait_handler (message, argument, level);
}

void
set_warning_handler (void (*routine) (string, string, int)) {
  the_warning_handler= routine; }

void
system_warning (string message, string argument, int level) {
  if (DEBUG_AUTO)
    cout << "TeXmacs] Warning: " << message << " " << argument << LF;
  if (the_info_handler != NULL)
    the_info_handler ("Warning: " * message, argument, level);
}

void
set_error_handler (void (*routine) (string, string, int)) {
  the_error_handler= routine; }

void
system_error (string message, string argument, int level) {
  if (DEBUG_AUTO)
    cout << "TeXmacs] Error: " << message << " " << argument << LF;
  if (the_info_handler != NULL)
    the_info_handler ("Error: " * message, argument, level);
}
