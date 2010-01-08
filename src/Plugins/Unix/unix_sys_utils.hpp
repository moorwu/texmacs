
/******************************************************************************
* MODULE     : unix_sys_utils.hpp
* DESCRIPTION: external command handling
* COPYRIGHT  : (C) 2009  David MICHEL
*******************************************************************************
* This software falls under the GNU general public license version 3 or later.
* It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
* in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
******************************************************************************/

#ifndef UNIX_SYS_UTILS_H
#define UNIX_SYS_UTILS_H

#include "string.hpp"

int unix_system (string);
int unix_system (string, string&);

#endif // defined UNIX_SYS_UTILS_H

