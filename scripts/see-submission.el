;;;
;;; opens with compile-logs.txt
(find-file "compile-logs.txt")
(evil-window-vsplit)
(evil-window-split)
(find-file "compile-errors.txt")
(evil-window-left 1)
(find-file "rsg.cc")
;; (magit-status)
(evil-window-right 1)
(evil-window-split)
(find-file "results.txt")
