#lang racket

(define (cube x) (* x x x))

(define (square x) (* x x))

(define (abs x) (if (< x 0)
                    (- x)
                    x))

(define (dist x y) (abs (- x y)))

(define (cbrt x)
  (define (okej val) (< (dist x (cube val) ) 0.00000001))
  (define (funkcja y)
    (if (okej y)
        y
        (funkcja (/ (+ (/ x (square y)) y y) 3))
        ))
  (funkcja 1.0))

(cbrt 64)
(cbrt 512)
(cbrt -27)
(cbrt -8)
(cbrt 1)
(cbrt 11111)