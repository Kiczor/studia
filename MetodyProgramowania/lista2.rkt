#lang racket

(define (square x) (* x x))

(define (abs x y)
  (if (< (- x y) 0)
      (- y x)
      (- x y)))

(define (frac2 num den eps)
  (define (cnt a b c d i) (/ (+ (* (den i) a) (* (num i) b)) (+ (* (den i) c) (* (num i) d)))) 
    (define (iter A-1 A-2 B-1 B-2 pop i)
    (if (< (abs pop (cnt A-1 A-2 B-1 B-2 i)) eps)
        pop
        (iter (+ (* (den i) A-1) (* (num i) A-2)) A-1
              (+ (* (den i) B-1) (* (num i) B-2)) B-1
              (cnt A-1 A-2 B-1 B-2 i) (+ i 1))
        )
      )
  (iter 0.0 1.0 1.0 0.0 0 1)
  )

(frac2 (lambda (i) 1.0) (lambda (i) 1.0) 0.00001)
(+ 3 (frac2 (lambda (i) (square (- (* 2 i) 1))) (lambda (i) 6.0) 0.00001))