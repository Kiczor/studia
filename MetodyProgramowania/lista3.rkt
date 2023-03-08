#lang racket

(define (compose x y)
  (lambda (b) (x (y b)))
  )

(define (repeated p n)
  (if (> n 1)
      (compose p (repeated p (- n 1)))
      p
      )
  )

(define (average x y)
  (/ (+ x y) 2))

(define (good-enough? x y)
  (< (abs (- x y)) 0.00000001))

(define (fixed-point f s)
  (define (iter k)
    (let ((new-k (f k)))
      (if (good-enough? k new-k)
          k
          (iter new-k))))
  (iter s))

(define (average-damp f)
  (lambda (x) (average x (f x))))

(define (sqrt-ad x)
  (fixed-point (average-damp (lambda (y) (/ x y))) 1.0))

(define (sqrt-4 x) (fixed-point ((repeated average-damp 2) (lambda (y) (/ x (* y y y)))) 1.0))
(define (sqrt-5 x) (fixed-point ((repeated average-damp 2) (lambda (y) (/ x (* y y y y)))) 1.0))
(define (sqrt-6 x) (fixed-point ((repeated average-damp 3) (lambda (y) (/ x (* y y y y y)))) 1.0))

(sqrt-4 81)
(sqrt-5 32)
(sqrt-6 64)
(sqrt-6 729)

(define (rt- n x)
  (fixed-point ((repeated average-damp (- n 2) ) (lambda (y) (/ x (expt y (- n 1))))) 1.0))

;;poprawna funkcja liczaca n-ty pierwiastek x:
(define (rt n x)
  (fixed-point ((repeated average-damp (/ n 2) ) (lambda (y) (/ x (expt y (- n 1))))) 1.0))

;; tutaj widac ze dziala lepiej z usrednianiem w n/2
(rt- 10 1024)
(rt 10 1024)
(rt- 12 4096)
(rt 12 4096)
(rt- 13 8192)
(rt 13 8192)