
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; MODULE      : adobe-fonts.scm
;; DESCRIPTION : setup TeX adobe postscript fonts
;; COPYRIGHT   : (C) 1999  Joris van der Hoeven
;;
;; This software falls under the GNU general public license version 3 or later.
;; It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
;; in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(texmacs-module (fonts fonts-adobe))

(set-font-rules
  '(((avant-garde rm medium right $s $d) (ec avant-garde-rm $s $d))
    ((avant-garde rm medium slanted $s $d) (ec avant-garde-ti $s $d))
    ((avant-garde rm medium italic $s $d) (ec avant-garde-ti $s $d))
    ((avant-garde rm bold right $s $d) (ec avant-garde-bx $s $d))
    ((avant-garde rm bold slanted $s $d) (ec avant-garde-bi $s $d))
    ((avant-garde rm bold italic $s $d) (ec avant-garde-bi $s $d))

    ((bookman rm medium right $s $d) (ec bookman-rm $s $d))
    ((bookman rm medium slanted $s $d) (ec bookman-ti $s $d))
    ((bookman rm medium italic $s $d) (ec bookman-ti $s $d))
    ((bookman rm bold right $s $d) (ec bookman-bx $s $d))
    ((bookman rm bold slanted $s $d) (ec bookman-bx $s $d))
    ((bookman rm bold italic $s $d) (ec bookman-bi $s $d))
    ((bookman ss $series $shape $s $d) (avant-garde rm $series $shape $s $d))
    ((bookman tt $series $shape $s $d) (courier rm $series $shape $s $d))

    ((courier rm medium right $s $d) (ec courier-rm $s $d))
    ((courier rm medium slanted $s $d) (ec courier-ti $s $d))
    ((courier rm medium italic $s $d) (ec courier-ti $s $d))
    ((courier rm bold right $s $d) (ec courier-bx $s $d))
    ((courier rm bold slanted $s $d) (ec courier-bx $s $d))
    ((courier rm bold italic $s $d) (ec courier-bi $s $d))

    ((helvetica rm medium right $s $d) (ec helvetica-rm $s $d))
    ((helvetica rm medium slanted $s $d) (ec helvetica-ti $s $d))
    ((helvetica rm medium italic $s $d) (ec helvetica-ti $s $d))
    ((helvetica rm bold right $s $d) (ec helvetica-bx $s $d))
    ((helvetica rm bold slanted $s $d) (ec helvetica-bx $s $d))
    ((helvetica rm bold italic $s $d) (ec helvetica-bi $s $d))
    ((helvetica tt $series $shape $s $d) (courier rm $series $shape $s $d))

    ((new-century-schoolbook rm medium right $s $d) (ec nc-schoolbook-rm $s $d))
    ((new-century-schoolbook rm medium slanted $s $d) (ec nc-schoolbook-ti $s $d))
    ((new-century-schoolbook rm medium italic $s $d) (ec nc-schoolbook-ti $s $d))
    ((new-century-schoolbook rm bold right $s $d) (ec nc-schoolbook-bx $s $d))
    ((new-century-schoolbook rm bold slanted $s $d) (ec nc-schoolbook-bx $s $d))
    ((new-century-schoolbook rm bold italic $s $d) (ec nc-schoolbook-bi $s $d))

    ((palatino rm medium right $s $d) (ec palatino-rm $s $d))
    ((palatino rm medium slanted $s $d) (ec palatino-sl $s $d))
    ((palatino rm medium italic $s $d) (ec palatino-ti $s $d))
    ((palatino rm medium small-caps $s $d) (ec palatino-cc $s $d))
    ((palatino rm bold right $s $d) (ec palatino-bx $s $d))
    ((palatino rm bold slanted $s $d) (ec palatino-bl $s $d))
    ((palatino rm bold italic $s $d) (ec palatino-bi $s $d))
    ((palatino rm bold small-caps $s $d) (ec palatino-xc $s $d))
    ((palatino ss $series $shape $s $d) (helvetica rm $series $shape $s $d))
    ((palatino tt $series $shape $s $d) (courier rm $series $shape $s $d))

    ((times rm medium right $s $d) (ec times-rm $s $d))
    ((times rm medium slanted $s $d) (ec times-sl $s $d))
    ((times rm medium italic $s $d) (ec times-ti $s $d))
    ((times rm medium small-caps $s $d) (ec times-cc $s $d))
    ((times rm bold right $s $d) (ec times-bx $s $d))
    ((times rm bold slanted $s $d) (ec times-bl $s $d))
    ((times rm bold italic $s $d) (ec times-bi $s $d))
    ((times rm bold small-caps $s $d) (ec times-xc $s $d))
    ((times ss $series $shape $s $d) (helvetica rm $series $shape $s $d))
    ((times tt $series $shape $s $d) (courier rm $series $shape $s $d))

    ;; old style
    ((helvetica rm medium condensed $s $d) (adobe rphvrrn $s $d 0))
    ((helvetica rm medium slanted-condensed $s $d) (adobe rphvron $s $d 0))
    ((helvetica rm medium italic-condensed $s $d) (adobe rphvron $s $d 0))
    ((helvetica rm bold condensed $s $d) (adobe rphvbrn $s $d 0))
    ((helvetica rm bold slanted-condensed $s $d) (adobe rphvbon $s $d 0))
    ((helvetica rm bold italic-condensed $s $d) (adobe rphvbon $s $d 0))

    ((palatino rm medium italic-right $s $d) (adobe rpplru $s $d 0))
    ((palatino rm medium condensed $s $d) (adobe rpplrrn $s $d 0))
    ((palatino rm medium wide $s $d) (adobe rpplrre $s $d 0))
    ((palatino rm bold italic-right $s $d) (adobe rpplbu $s $d 0))

    ((times rm medium condensed $s $d) (adobe rptmrrn $s $d 0))
    ((times rm medium wide $s $d) (adobe rptmrre $s $d 0))

    ((chancery rm $a $b $s $d) (adobe rpzcmi $s $d 0))
    ((chancellary rm $a $b $s $d) (adobe rpzcmi $s $d 0))
    ((dingbat rm $a $b $s $d) (adobe rpzdr $s $d 0))))


(set-font-rules
  '(((adobe $f medium $a $s $d)
     (math
      (adobe-math (tex cmr $s $d)
		  (tex cmmi $s $d)
		  (tex cmsy $s $d)
		  (tex msam $s $d)
		  (tex msbm $s $d)
		  (tex stmary $s $d)
		  (tex wasy $s $d)
		  (tex line $s $d)
		  (tex cmsy $s $d)
		  (tex eufm $s $d)
		  (tex bbm $s $d)
		  (tex grmn $s $d)
		  (tex cmbsy $s $d)
		  (virtual long $s $d)
		  (virtual negate $s $d)
		  (virtual misc $s $d)
		  (tex rptmri $s $d 0)
		  (tex rpsyr $s $d 0)
		  (tex rpsyro $s $d 0)
		  (tex rptmbi $s $d 0)
		  (tex rpsyr $s $d 0)
		  (tex rpsyro $s $d 0))
      (rubber (tex-rubber rubber-cmex cmex $s $d)
	      (tex-rubber rubber-stmary stmary $s $d)
	      (tex-rubber rubber-wasy wasy $s $d)
	      (tex-dummy-rubber (tex-rubber rubber-cmex $cmex $s $d)))
      (adobe rptmr $s $d 0)
      (adobe rptmr $s $d 0)))

    ((adobe $f bold $a $s $d)
     (math
      (adobe-math (tex cmbx $s $d)
		  (tex cmmib $s $d)
		  (tex cmbsy $s $d)
		  (tex msam $s $d)
		  (tex msbm $s $d)
		  (tex stmaryb $s $d)
		  (tex wasyb $s $d)
		  (tex lineb $s $d)
		  (tex cmbsy $s $d)
		  (tex eufb $s $d)
		  (tex bbmbx $s $d)
		  (tex grxn $s $d)
		  (tex cmbsy $s $d)
		  (virtual long $s $d)
		  (virtual negate $s $d)
		  (virtual misc $s $d)
		  (tex rptmbi $s $d 0)
		  (tex rpsyr $s $d 0)
		  (tex rpsyro $s $d 0)
		  (tex rptmbi $s $d 0)
		  (tex rpsyr $s $d 0)
		  (tex rpsyro $s $d 0))
      (rubber (tex-rubber rubber-cmex cmexb $s $d)
	      (tex-rubber rubber-stmary stmaryb $s $d)
	      (tex-rubber rubber-wasy wasyb $s $d)
	      (tex-dummy-rubber (tex-rubber rubber-cmex $cmex $s $d)))
      (adobe rptmb $s $d 0)
      (adobe rptmb $s $d 0)))))
