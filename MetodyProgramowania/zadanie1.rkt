#lang racket
(define (tagged-list? len sym x)
  (and (list? x)
       (= (length x) len)
       (eq? (first x) sym)))

(define leaf 'leaf)
(define (leaf? h) (eq? 'leaf h))
(define (hnode? h)
  (and (tagged-list? 5 'hnode h)
       (natural? (caddr h))))

(define (hnode-elem h) (second h))
(define (hnode-left h) (fourth h))
(define (hnode-right h) (fifth h))
(define (hnode-rank h) (third h))

(define (elem-priority x) (car x))

(define(hord? p h)
  (or (leaf? h)
      (<= p (elem-priority (hnode-elem h)))))

(define (rank h)
  (if (leaf? h)
      0
      (hnode-rank h)))

(define (heap? h)
  (or (leaf? h)
      (and (hnode? h)
           (heap? (hnode-left h))
           (heap? (hnode-right h))
           (<= (rank (hnode-right h))
               (rank (hnode-left h)))
           (= (rank h) (+ 1 (rank (hnode-right h))))
           (hord? (elem-priority (hnode-elem h))
                  (hnode-left h))
           (hord? (elem-priority (hnode-elem h))
                  (hnode-right h)))))

(define (make-hnode elem heap-a heap-b)
  (if (> (rank heap-a) (rank heap-b))
      (list 'hnode elem (+ 1 (rank heap-b)) heap-a heap-b)
      (list 'hnode elem (+ 1 (rank heap-a)) heap-a heap-b)
  )
 )

(make-hnode '(1 3) leaf leaf)
(make-hnode '(0 2) (make-hnode '(1 3) leaf leaf) (make-hnode '(2 3) leaf leaf))

(define empty-heap leaf)
(define (heap-empty? h)
  (leaf? h))

(define (heap-insert elt heap)
  (heap-merge heap (make-hnode elt leaf leaf)))

(define (heap-min heap)
  (hnode-elem heap))

(define (heap-pop heap)
  (heap-merge (hnode-left heap) (hnode-right heap)))

(define (heap-merge h1 h2)
  (cond
    [(leaf? h1) h2]
    [(leaf? h2) h1]
    [(let* ([najmhnode (if (< (elem-priority (hnode-elem h1)) (elem-priority (hnode-elem h2))) h1 h2)] 
            [e (hnode-elem najmhnode)]
            [HL (hnode-left najmhnode)]
            [HR (hnode-right najmhnode)]
            [h (if(< (elem-priority (hnode-elem h1)) (elem-priority (hnode-elem h2))) h2 h1) ])
       ((make-hnode e HL (heap-merge h HR)))
       )]
    )
  )

;;; heapsort. sorts a list of numbers.
(define (heapsort xs)
  (define (popAll h)
    (if (heap-empty? h)
        null
        (cons (elem-val (heap-min h)) (popAll (heap-pop h)))))
  (let ((h (foldl (lambda (x h)
                    (heap-insert (make-elem x x) h))
            empty-heap xs)))
    (popAll h)))

;;; check that a list is sorted (useful for longish lists)
(define (sorted? xs)
  (cond [(null? xs)              true]
        [(null? (cdr xs))        true]
        [(<= (car xs) (cadr xs)) (sorted? (cdr xs))]
        [else                    false]))

;;; generate a list of random numbers of a given length
(define (randlist len max)
  (define (aux len lst)
    (if (= len 0)
        lst
        (aux (- len 1) (cons (random max) lst))))
  (aux len null))