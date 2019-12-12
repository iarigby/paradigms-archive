;; it takes '("a" "b" "c") and generates ("a" "ab" "abc")
(define (generate-concatenations-using strings collected)
  (if (null? strings) '()
  (let ((newcollected (string-append collected (car strings))))
	(cons newcollected (generate-concatenations-using (cdr strings)
				       newcollected)))))
;; '("a" "b" "c")
;; "a"
;; (generate-concatenations-using ("b" "c")
;;			       "a")



(define (generate-concatenations strings)
  (generate-concatenations-using strings ""))

