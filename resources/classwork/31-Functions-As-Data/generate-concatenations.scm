;; it takes '("a" "b" "c") and generates ("a" "ab" "abc")
(define (generate-concatenations-helper strings collected)
  (if (null? strings) '()
	(let ((new-collected (string-append collected (car strings))))
	 (cons new-collected (generate-concatenations-helper (cdr strings)
					 new-collected)))
))
(define (generate-concatenations strings)
  (generate-concatenations-helper strings ""))



