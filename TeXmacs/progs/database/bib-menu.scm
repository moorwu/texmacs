
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; MODULE      : bib-menu.scm
;; DESCRIPTION : menus for managing bibliographic databases
;; COPYRIGHT   : (C) 2015  Joris van der Hoeven
;;
;; This software falls under the GNU general public license version 3 or later.
;; It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
;; in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(texmacs-module (database bib-menu)
  (:use (database bib-widgets)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Menu for maintaining bibliographic databases
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(menu-bind bib-menu
  ("Import" (noop))
  ("Export" (noop))
  ---
  ("Search" (noop))
  ("Edit" (load-buffer "tmfs://db/bib"))
  ("Gathered" (noop))
  ("Conflicts" (noop))
  ---
  ("Preferences" (open-bib-preferences)))
