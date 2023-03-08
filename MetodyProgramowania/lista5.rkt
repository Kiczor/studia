#lang racket
(define (var? t)
  (symbol? t))

(define (neg? t)
  (and (list? t)
       (= 2 (length t))
       (eq? 'neg (car t))))

(define (conj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'conj (car t))))

(define (disj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'disj (car t))))

(define (prop? f)
  (or (var? f)
      (and (neg? f)
           (prop? (neg-subf f)))
      (and (disj? f)
           (prop? (disj-left f))
           (prop? (disj-rght f)))
      (and (conj? f)
           (prop? (conj-left f))
           (prop? (conj-rght f)))))

(define (make-neg val)
  (cons 'neg val))

(define (make-conj x y)
  (list 'conj x y))

(define (make-disj x y)
  (list 'disj x y))

(define (neg-subf x)
  (cdr x))

(define (disj-left x)
  (second x))

(define (disj-rght x)
  (third x))

(define (conj-left x)
  (second x))

(define (conj-rght x)
  (third x))

(define (free-vars f)
  (cond [(var? f) (list f)]
        [(disj? f) (append (free-vars (disj-left f)) (free-vars (disj-rght f)))]
        [(conj? f) (append (free-vars (conj-left f)) (free-vars (conj-rght f)))]
        )
  )