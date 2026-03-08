( define (delete s k) 
   (cond 
      ((null? s) '())
      ((= k 1) (cdr s))
      (else (cons (car s)
         (delete (cdr s) (- k 1))
      ))
   )
) 

(display (delete '(1) 1))