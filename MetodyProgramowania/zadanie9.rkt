#lang racket
(require rackunit)
(require rackunit/text-ui)

;; definicja wyrażeń arytmetycznych z jedną zmienną

(struct const (val) #:transparent)
(struct op (symb l r) #:transparent)
(struct variable () #:transparent)
(struct deriv (ex) #:transparent)

(define (expr? e)
  (match e
    [(variable) true]
    [(const n)  (number? n)]
    [(deriv x)  (expr? x)]
    [(op s l r) (and (member s '(+ *))
                     (expr? l)
                     (expr? r))]
    [_          false]))

;; przykładowe wyrażenie

(define f (op '* (op '* (variable) (variable))
                 (variable)))

;; pochodna funkcji

(define (∂ f)
  (match f
    [(const n)   (const 0)]
    [(variable)  (const 1)]
    [(deriv x)   (∂ (∂ x))]
    [(op '+ f g) (op '+ (∂ f) (∂ g))]
    [(op '* f g) (op '+ (op '* (∂ f) g)
                        (op '* f (∂ g)))]))

;; przykładowe użycie

(define df (∂ f))
(define ddf (∂ (∂ f)))
(define dddf (∂ (∂ (∂ f))))

;; zadanie (napisanie funkcji eval)

(define (eval ex value)
  (match ex
    [(const n) n]
    [(variable) value]
    [(op s l r) (if (eq? s '+)
                    (+ (eval l value) (eval r value))
                    (* (eval l value) (eval r value))
                    )
                ]
    [(deriv x) (eval (∂ x) value)]
    )
  )

;; testy funkcji eval

(define eval-testy
  (test-suite
   "testowanie dzialania funkcji eval:"
   (check-equal? (eval f 2) 8)
   (check-equal? (eval f 4) 64)
   (check-equal? (eval (op '+ (variable) (const 2)) 5) 7)
   (check-equal? (eval (op '+ (op '* (variable) (const 2)) (deriv (op '+ (op '* (variable) (variable)) (variable)))) 3) 13)
   (check-equal? (eval (op '* (const 1) (const 1) ) 23423) 1)
   (check-equal? (eval (deriv (op '* (variable) (op '+ (variable) (const 3)))) 10) 23)
   (check-equal? (eval (deriv (deriv (op '* (variable) (variable)))) 132) 2)
   (check-equal? (eval (deriv (deriv (deriv (op '* (variable) (op '* (variable) (variable)))))) 132) 6)
   (check-equal? (eval (deriv (deriv (deriv (op '* (variable) (variable))))) 132) 0)
   )
  )

(run-tests eval-testy)