(define (replace f x a)
  (cond 
    ((null? x) '())
    ((f (car x))
     (cons a (replace f (cdr x) a)))
    (else 
     (cons (car x) (replace f (cdr x) a)
     )
   )
  )
)
     
(replace (lambda (x) (not (pair? x))) '((A) B (C) D E (F)) 'Z)