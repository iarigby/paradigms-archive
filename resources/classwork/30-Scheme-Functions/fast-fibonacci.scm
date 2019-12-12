(define (fast-fibonacci n)
  (fast-fibonacci-helper n 0 1))

(define (fast-fibonacci-helper n base-0 base-1)
  (cond ((zero? n) base-0)
	((zero? (- n 1)) base 1)
	(else (fast-fibonacci-helper (- n 1) 
				     base-1  
				     (+ base-0 base-1)))))


