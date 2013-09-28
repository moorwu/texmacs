
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; MODULE      : dynamic-drd.scm
;; DESCRIPTION : data relation definitions for dynamic tags
;; COPYRIGHT   : (C) 2005  Joris van der Hoeven
;;
;; This software falls under the GNU general public license version 3 or later.
;; It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
;; in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(texmacs-module (dynamic dynamic-drd)
  (:use (utils edit variants)))

;; fold <-> unfold toggles

(define-group toggle-tag (folded-tag) (unfolded-tag))
(define-group toggle-first-tag (folded-tag))
(define-group toggle-second-tag (unfolded-tag))
(define-group variant-tag (folded-tag) (unfolded-tag))
(define-group similar-tag (folded-tag) (unfolded-tag))

(tm-define-macro (define-toggle folded unfolded)
  `(begin
     (define-group toggle-first-tag ,folded)
     (define-group toggle-second-tag ,unfolded)
     (define-alternate ,folded ,unfolded)))

(tm-define-macro (define-fold folded unfolded)
  `(begin
     (define-group folded-tag ,folded)
     (define-group unfolded-tag ,unfolded)
     (define-alternate ,folded ,unfolded)))

(define-fold folded unfolded)
(define-fold folded-plain unfolded-plain)
(define-fold folded-std unfolded-std)
(define-fold folded-explain unfolded-explain)
(define-fold folded-env unfolded-env)
(define-fold folded-documentation unfolded-documentation)
(define-fold folded-grouped unfolded-grouped)
(define-fold picture-mixed source-mixed)

;; summarized <-> detailed toggles

(define-group toggle-tag (toggle-first-tag) (toggle-second-tag))
(define-group toggle-first-tag (summarized-tag) summarized-algorithm)
(define-group toggle-second-tag (detailed-tag) detailed-algorithm)
(define-group variant-tag (summarized-tag) (detailed-tag))
(define-group similar-tag (summarized-tag) (detailed-tag))

(tm-define-macro (define-summarize short long)
  `(begin
     (define-group summarized-tag ,short)
     (define-group detailed-tag ,long)
     (define-alternate ,short ,long)))

(define-summarize summarized detailed)
(define-summarize summarized-plain detailed-plain)
(define-summarize summarized-std detailed-std)
(define-summarize summarized-env detailed-env)
(define-summarize summarized-documentation detailed-documentation)
(define-summarize summarized-grouped detailed-grouped)
(define-summarize summarized-raw detailed-raw)
(define-summarize summarized-tiny detailed-tiny)

(define-alternate summarized-algorithm detailed-algorithm)

;; switches

(define-group variant-tag (unroll-tag))
(define-group similar-tag (unroll-tag))

(define-group switch-tag
  (alternative-tag) (unroll-tag) (expanded-tag))

(define-group big-switch-tag
  (big-alternative-tag) (unroll-tag) (expanded-tag))

(define-group alternative-tag
  (big-alternative-tag) tiny-switch)

(define-group big-alternative-tag
  switch screens)

(define-group unroll-tag
  unroll unroll-greyed unroll-phantoms)

(define-group expanded-tag
  expanded slides)

;; overlays

(define-group variant-tag (overlays-tag) (overlay-tag))
(define-group similar-tag (overlays-tag) (overlay-tag))

(define-group overlays-tag
  overlays overlays-compressed overlays-greyed)

(define-group overlay-tag
  overlay-from overlay-until overlay-this overlay-other)

;; hidden content

(define-group variant-tag (hidden-tag))
(define-group similar-tag (hidden-tag))

(define-group hidden-tag
  hidden-deleted hidden-invisible hidden-greyed)

;; ornaments

(define-group ornament-tag
  manila-paper rough-paper ridged-paper pine granite metal)

(define-group variant-tag (ornament-tag))
(define-group similar-tag (ornament-tag))
