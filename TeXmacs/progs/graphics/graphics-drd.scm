
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; MODULE      : graphics-drd.scm
;; DESCRIPTION : properties of the graphical tags
;; COPYRIGHT   : (C) 2011  Joris van der Hoeven
;;
;; This software falls under the GNU general public license version 3 or later.
;; It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
;; in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(texmacs-module (graphics graphics-drd)
  (:use (utils library cursor)
        (utils library tree)
        (utils edit variants)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Properties of the graphical tags
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-group graphical-atomic-tag
  point)

(define-group graphical-curve-tag
  line cline spline cspline arc carc)

(define-group graphical-text-tag
  text-at math-at)

(define-group graphical-contains-curve-tag
  (graphical-curve-tag))

(define-group graphical-contains-text-tag
  (graphical-text-tag))

(define-group graphical-non-group-tag
  (graphical-curve-tag) (graphical-atomic-tag) (graphical-text-tag))

(define-group graphical-group-tag
  gr-group)

(define-group graphical-tag
  (graphical-non-group-tag) (graphical-group-tag))

(tm-define (graphical-text-context? t)
  (tm-in? t (graphical-text-tag-list)))

(tm-define (graphical-text-at-context? t)
  (and (graphical-text-context? t) (>= (tm-arity t) 2)))

(tm-define (graphical-text-arg-context? t)
  (and (graphical-text-context? t) (< (tm-arity t) 2)))

(tm-define (inside-graphical-text?)
  (tree-innermost graphical-text-context?))

(tm-define gr-tags-user      (list))
(tm-define gr-tags-all       (graphical-tag-list))
(tm-define gr-tags-curves    (graphical-curve-tag-list))
(tm-define gr-tags-noncurves (append (graphical-atomic-tag-list)
                                     (graphical-text-tag-list)
                                     (graphical-group-tag-list)))

(tm-define (graphical-user-tag? l)
  (in? l gr-tags-user))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; List of graphical attributes and their properties
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(tm-define (gr-prefixed? attr)
  (string-starts? attr "gr-"))

(tm-define (gr-prefix attr)
  (string-append "gr-" attr))

(tm-define (gr-unprefix attr)
  (substring attr 3 (string-length attr)))

(define-table attribute-default-table
  ("gid" . "default")
  ("magnify" . "1")
  ("color" . "black")
  ("opacity" . "100%")
  ("point-style" . "disk")
  ("line-width" . "1ln")
  ("line-join" . "normal")
  ("line-caps" . "normal")
  ("line-effects" . "normal")
  ("dash-style" . "none")
  ("dash-style-unit" . "5ln")
  ("arrow-begin" . "none")
  ("arrow-end" . "none")
  ("arrow-length" . "5ln")
  ("arrow-height" . "5ln")
  ("fill-color" . "none")
  ("fill-style" . "plain")
  ("text-at-halign" . "left")
  ("text-at-valign" . "base"))

(tm-define (graphics-attribute-default attr)
  (if (gr-prefixed? attr)
      (graphics-attribute-default (gr-unprefix attr))
      (ahash-ref attribute-default-table attr)))

(tm-define (decode-dash x)
  (cond ((== x "default") "---")
        ((== x "10") ". . . . .")
        ((== x "11100") "- - - - -")
        ((== x "1111010") "- . - . -")
        (else "other")))

(tm-define (decode-arrow x)
  (cond ((== x "default") "")
        ((== x "none") "")
        ((== x "") "")
        ((== x "<gtr>") ">")
        ((== x "|<gtr>") "|>")
        ((== x "<gtr><gtr>") ">>")
        ((== x "<less>") "<")
        ((== x "<less>|") "<|")
        ((== x "<less><less>") "<<")
        ((string? x) x)
        (else "other")))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Attributes of the graphical tags
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(tm-define (graphics-common-attributes)
  '("gid" "magnify" "color" "opacity"))

(tm-define (graphics-all-attributes)
  (map car (ahash-table->list attribute-default-table)))

(tm-define (graphics-attributes tag)
  (graphics-common-attributes))

(tm-define (graphics-attributes tag)
  (:require (== tag 'point))
  (append (graphics-common-attributes)
          '("fill-color"
            "point-style")))

(tm-define (graphics-attributes tag)
  (:require (or (graphical-curve-tag? tag) (graphical-user-tag? tag)))
  (append (graphics-common-attributes)
          '("fill-color"
            "line-width" "line-join" "line-caps" "line-effects"
            "dash-style" "dash-style-unit"
            "arrow-begin" "arrow-end" "arrow-length" "arrow-height")))
  
(tm-define (graphics-attributes tag)
  (:require (graphical-text-tag? tag))
  (append (graphics-common-attributes)
          '("text-at-halign" "text-at-valign")))

(tm-define (graphics-attributes tag)
  (:require (graphical-group-tag? tag))
  (graphics-all-attributes))

(tm-define (graphics-attribute? tag attr)
  (in? attr (graphics-attributes tag)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Attributes for editing modes
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(tm-define (graphics-mode-attributes mode)
  (cond ((func? mode 'edit 1) (graphics-attributes (cadr mode)))
        ((== mode '(group-edit props)) (graphics-all-attributes))
        (else '())))

(tm-define (graphics-mode-attribute? mode attr)
  (in? attr (graphics-mode-attributes mode)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Refined properties concerning arity and types of children
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(tm-define (graphics-minimal? obj)
  (or (tm-in? obj '(point text-at math-at))
      (== (tm-arity obj) (tag-minimal-arity (tm-car obj)))))

(tm-define (graphics-incomplete? obj)
  (< (tm-arity obj) (tag-minimal-arity (tm-car obj))))

(tm-define (graphics-complete? obj)
  (>= (tm-arity obj) (tag-maximal-arity (tm-car obj))))

(tm-define (graphics-complete obj)
  (list obj #f))
