
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; MODULE      : generic-kbd.scm
;; DESCRIPTION : general keyboard shortcuts for all modes
;; COPYRIGHT   : (C) 1999  Joris van der Hoeven
;;
;; This software falls under the GNU general public license version 3 or later.
;; It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
;; in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(texmacs-module (generic generic-kbd)
  (:use (texmacs keyboard prefix-kbd)
	(utils edit variants)
	(utils edit auto-close)
	(utils library cursor)
	(generic generic-edit)
	(source source-edit)
	(texmacs texmacs tm-files)
	(texmacs texmacs tm-print)
	(doc help-funcs)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; General shortcuts for all modes
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(kbd-map
  ("F1" (interactive docgrep-in-doc))
  ("S-F1" (load-help-buffer "about/welcome/welcome"))
  ("F2" (open-buffer))
  ("S-F2" (choose-file load-in-new-window "Load file" ""))
  ("C-F2" (revert-buffer))
  ("M-F2" (new-buffer))
  ("M-S-F2" (open-window))
  ("M-C-F2" (clone-window))
  ("F3" (save-buffer))
  ("S-F3" (choose-file save-buffer "Save TeXmacs file" "texmacs"))
  ("F4" (preview-with-ghostview))
  ("S-F4" (print-buffer))
  ("C-F4" (interactive print-to-file))
  ("M-F4" (interactive print-pages))
  ("M-S-F4" (interactive print-pages-to-file))
  ("C-F9" (toggle-full-screen-mode))

  ("space" (kbd-space))
  ("space var" (make 'nbsp))
  ("space var var" (make-space "0.2spc"))
  ("space var var var" (make-space "1em"))
  ("return" (kbd-return))
  ("backspace" (kbd-remove #f))
  ("delete" (kbd-remove #t))
  ("tab" (kbd-tab))
  ("left" (kbd-left))
  ("right" (kbd-right))
  ("up" (kbd-up))
  ("down" (kbd-down))
  ("home" (kbd-start-line))
  ("end" (kbd-end-line))
  ("pageup" (kbd-page-up))
  ("pagedown" (kbd-page-down))

  ("S-space" (kbd-shift-space))
  ("S-return" (kbd-shift-return))
  ("S-backspace" (kbd-remove #f))
  ("S-delete" (kbd-remove #t))
  ("S-left" (kbd-select kbd-left))
  ("S-right" (kbd-select kbd-right))
  ("S-up" (kbd-select kbd-up))
  ("S-down" (kbd-select kbd-down))
  ("S-home" (kbd-select kbd-start-line))
  ("S-end" (kbd-select kbd-end-line))
  ("S-pageup" (kbd-select kbd-page-up))
  ("S-pagedown" (kbd-select kbd-page-down))

  ("C-space" (kbd-select-enlarge))
  ("C-backspace" (remove-structure-upwards))
  ("C-delete" (remove-structure-upwards))
  ("C-tab" (variant-circulate #t))
  ("C-S-tab" (variant-circulate #f))
  ("C-*" (hidden-variant))
  ("C-left" (traverse-left))
  ("C-right" (traverse-right))
  ("C-up" (traverse-up))
  ("C-down" (traverse-down))
  ("C-home" (traverse-first))
  ("C-end" (traverse-last))
  ("C-pageup" (traverse-previous))
  ("C-pagedown" (traverse-next))
  ("C-section" (traverse-previous-section-title))
  ("C-S-left" (kbd-select traverse-left))
  ("C-S-right" (kbd-select traverse-right))
  ("C-S-up" (kbd-select traverse-up))
  ("C-S-down" (kbd-select traverse-down))
  ("C-S-home" (kbd-select traverse-first))
  ("C-S-end" (kbd-select traverse-last))
  ("C-S-pageup" (kbd-select traverse-previous))
  ("C-S-pagedown" (kbd-select traverse-next))

  ("A-*" (toggle-number))
  ("A-space" (make-space "0.2spc"))
  ("A-S-space" (make-space "-0.2spc"))
  ("A-backspace" (structured-remove #f))
  ("A-delete" (structured-remove #t))
  ("A-tab" (make-htab "5mm"))
  ("A-left" (structured-insert #f))
  ("A-right" (structured-insert #t))
  ("A-up" (structured-insert-up))
  ("A-down" (structured-insert-down))
  ("A-home" (structured-insert-start))
  ("A-end" (structured-insert-end))
  ("A-pageup" (structured-insert-top))
  ("A-pagedown" (structured-insert-bottom))

  ("M-space" (make-space "0.2spc"))
  ("M-S-space" (make-space "-0.2spc"))
  ("M-backspace" (positioning-default))
  ("M-delete" (positioning-default))
  ("M-tab" (make-htab "5mm"))
  ("M-left" (positioning-left))
  ("M-right" (positioning-right))
  ("M-up" (positioning-up))
  ("M-down" (positioning-down))
  ("M-home" (positioning-start))
  ("M-end" (positioning-end))
  ("M-pageup" (positioning-top))
  ("M-pagedown" (positioning-bottom))

  ("M-A-left" (structured-left))
  ("M-A-right" (structured-right))
  ("M-A-up" (structured-up))
  ("M-A-down" (structured-down))
  ("M-A-home" (structured-first))
  ("M-A-end" (structured-last))
  ("M-A-pageup" (structured-top))
  ("M-A-pagedown" (structured-bottom))
  ("M-A-(" (structured-exit-left))
  ("M-A-)" (structured-exit-right))
  ("M-A-S-left" (kbd-select structured-left))
  ("M-A-S-right" (kbd-select structured-right))
  ("M-A-S-up" (kbd-select structured-up))
  ("M-A-S-down" (kbd-select structured-down))
  ("M-A-S-home" (kbd-select structured-first))
  ("M-A-S-end" (kbd-select structured-last))
  ("M-A-S-pageup" (kbd-select structured-top))
  ("M-A-S-pagedown" (kbd-select structured-bottom))

  ("escape tab" (noop) (make-htab "5mm"))
  ("<" "<less>")
  (">" "<gtr>")
  ("C-<" (cursor-history-backward))
  ("C->" (cursor-history-forward))
  ("(" (make-bracket-open "(" ")"))
  (")" (make-bracket-close ")" "("))
  ("[" (make-bracket-open "[" "]"))
  ("]" (make-bracket-close "]" "["))
  ("{" (make-bracket-open "{" "}"))
  ("}" (make-bracket-close "}" "{"))
  ("\\" (if (or (inside? 'hybrid) (in-prog?)) (insert "\\") (make-hybrid)))
  ("cmd \\" (make-hybrid))

  ("accent:hat" "^")
  ("accent:deadhat" "^")
  ("accent:tilde" "~")
  ("accent:acute" "'")
  ("accent:grave" "`")

  ("symbol \\" "\\")
  ("symbol \"" "\"")
  ("symbol $" "$")
  ("symbol &" "&")
  ("symbol #" "#")
  ("symbol �" "�")
  ("symbol %" "%")
  ("symbol _" "_")
  ("symbol ^" "^")
  ("symbol \"" "\"")
  ("symbol |" "|")

  ("undo" (noop) (undo 0))
  ("redo" (noop) (redo 0))
  ("cancel" (noop) (clipboard-clear "primary"))
  ("cut" (noop) (clipboard-cut "primary"))
  ("paste" (noop) (clipboard-paste "primary"))
  ("copy" (noop) (clipboard-copy "primary"))
  ("find" (noop) (search-start #t))

  ("copyto 1" (noop) (clipboard-copy "primary"))
  ("copyto 2" (clipboard-copy "secondary"))
  ("copyto 3" (clipboard-copy "ternary"))
  ("copyto s" (clipboard-copy "search"))
  ("copyto r" (clipboard-copy "replace"))
  ("copyto *" (interactive clipboard-copy))
  ("cutto 1" (noop) (clipboard-cut "primary"))
  ("cutto 2" (clipboard-cut "secondary"))
  ("cutto 3" (clipboard-cut "ternary"))
  ("cutto s" (clipboard-cut "search"))
  ("cutto r" (clipboard-cut "replace"))
  ("cutto *" (interactive clipboard-cut))
  ("pastefrom 1" (noop) (clipboard-paste "primary"))
  ("pastefrom 2" (clipboard-paste "secondary"))
  ("pastefrom 3" (clipboard-paste "ternary"))
  ("pastefrom s" (clipboard-paste "search"))
  ("pastefrom r" (clipboard-paste "replace"))
  ("pastefrom *" (interactive clipboard-paste))

  ("table N t" (make 'tabular))
  ("table N T" (make 'tabular*))
  ("table N b" (make 'block))
  ("table N B" (make 'block*)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Emacs keymap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(kbd-map
  (:profile emacs)

  ;; standard Emacs shortcuts
  ("emacs a" (kbd-start-line))
  ("emacs b" (kbd-left))
  ("emacs d" (remove-text #t))
  ("emacs e" (kbd-end-line))
  ("emacs f" (kbd-right))
  ("emacs g" (selection-cancel))
  ("emacs j" (insert-return))
  ("emacs k" (kill-paragraph))
  ("emacs l" (recenter-window))
  ("emacs m" (insert-return))
  ("emacs n" (kbd-down))
  ("emacs o" (open-line))
  ("emacs p" (kbd-up))
  ("emacs q" (make 'symbol))
  ("emacs r" (search-start #f))
  ("emacs s" (search-start #t))
  ("emacs t" (transpose-chars))
  ("emacs v" (kbd-page-down))
  ("emacs w" (clipboard-cut "primary"))
  ("emacs y" (clipboard-paste "primary"))
  ("emacs insert" (clipboard-copy "primary"))
  ("emacs \\" (toggle-input-method))
  ("emacs ]" (abort-recursive-edit))
  ("emacs _" (undo 0))
  ("emacs /" (undo 0))

  ("cmd v" (kbd-page-up))
  ("cmd w" (clipboard-copy "primary"))
  ("cmd x" (interactive exec-interactive-command))
  ("cmd X" (interactive footer-eval))
  ("cmd <" (go-start))
  ("cmd >" (go-end))
  ("cmd $" (spell-start))

  ("emacs:prefix b" (interactive go-to-buffer))
  ("emacs:prefix k" (safely-kill-buffer))
  ("emacs:prefix C-c" (safely-quit-TeXmacs))
  ("emacs:prefix C-f" (interactive load-buffer))
  ("emacs:prefix C-s" (save-buffer))
  ("emacs:prefix C-w" (interactive save-buffer))

  ;; extra Emacs-ish shortcuts
  ("emacs =" (interactive replace-start-forward))

  ("cmd a" (make-tree))
  ("cmd g" (clipboard-clear "primary"))
  ("cmd R" (make-rigid))
  ("cmd [" (undo 0))
  ("cmd ]" (redo 0))
  ("cmd :" (make 'line-break))
  ("cmd ;" (make 'new-line))
  ("cmd return" (make 'next-line))
  ("cmd /" (make 'no-break))
  ("cmd !" (make-label))
  ("cmd ?" (make 'reference))
  ("cmd C-?" (make 'pageref)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Mac OS keymap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(kbd-map
  (:profile macos)

  ;; standard Mac OS keyboard shortcuts
  ("macos c" (clipboard-copy "primary"))
  ("macos f" (search-start #t))
  ("macos n" (new-buffer))
  ("macos o" (open-buffer))
  ("macos p" (preview-with-ghostview))
  ("macos q" (safely-quit-TeXmacs))
  ("macos r" (interactive replace-start-forward))
  ("macos s" (save-buffer))
  ("macos S" (choose-file save-buffer "Save TeXmacs file" "texmacs"))
  ("macos v" (clipboard-paste "primary"))
  ("macos w" (safely-kill-buffer))
  ("macos x" (clipboard-cut "primary"))
  ("macos z" (undo 0))
  ("macos Z" (redo 0))
  ("macos ;" (spell-start))

  ;; extra MacOS-like shortcuts
  ("macos F" (search-start #f))

  ("C-g" (selection-cancel))
  ("C-k" (kill-paragraph))
  ("C-q" (make 'symbol))

  ("cmd a" (make-tree))
  ("cmd R" (make-rigid))
  ("cmd x" (interactive exec-interactive-command))
  ("cmd X" (interactive footer-eval))
  ("cmd :" (make 'line-break))
  ("cmd ;" (make 'new-line))
  ("cmd return" (make 'next-line))
  ("cmd /" (make 'no-break))
  ("cmd !" (make-label))
  ("cmd ?" (make 'reference))
  ("cmd C-?" (make 'pageref))
  ("cmd <" (go-start))
  ("cmd >" (go-end)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Gnome and windows keymaps
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(kbd-map
  (:profile gnome windows)

  ;; standard Window shortcuts
  ("windows c" (clipboard-copy "primary"))
  ("windows f" (search-start #t))
  ("windows n" (new-buffer))
  ("windows o" (open-buffer))
  ("windows p" (preview-with-ghostview))
  ("windows q" (safely-quit-TeXmacs))
  ("windows r" (interactive replace-start-forward))
  ("windows s" (save-buffer))
  ("windows v" (clipboard-paste "primary"))
  ("windows w" (safely-kill-buffer))
  ("windows x" (clipboard-cut "primary"))
  ("windows z" (undo 0))

  ;; extra Window-ish shortcuts
  ("windows g" (selection-cancel))
  ("windows k" (kill-paragraph))
  ("windows F" (search-start #f))

  ("cmd a" (make-tree))
  ("cmd g" (clipboard-clear "primary"))
  ("cmd q" (make 'symbol))
  ("cmd x" (interactive footer-eval))
  ("cmd R" (make-rigid))
  ("cmd <" (go-start))
  ("cmd >" (go-end))
  ("cmd :" (make 'line-break))
  ("cmd ;" (make 'new-line))
  ("cmd return" (make 'next-line))
  ("cmd /" (make 'no-break))
  ("cmd !" (make-label))
  ("cmd ?" (make 'reference))
  ("cmd C-?" (make 'pageref))
  ("cmd $" (spell-start)))
