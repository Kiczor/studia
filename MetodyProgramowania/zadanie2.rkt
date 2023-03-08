#lang racket
(require rackunit/text-ui)
(require rackunit)

(define (inc n)
  (+ n 1))

;;; tagged lists
(define (tagged-list? len-xs tag xs)
  (and (list? xs)
       (= len-xs (length xs))
       (eq? (first xs) tag)))

;;; ordered elements
(define (make-elem pri val)
  (cons pri val))

(define (elem-priority x)
  (car x))

(define (elem-val x)
  (cdr x))

;;; leftist heaps (after Okasaki)

;; data representation
(define leaf 'leaf)

(define (leaf? h) (eq? 'leaf h))

(define (hnode? h)
  (and (tagged-list? 5 'hnode h)
       (natural? (caddr h))))

(define (make-hnode elem heap-a heap-b)
  (if (> (rank heap-a) (rank heap-b))
      (list 'hnode elem (+ 1 (rank heap-b)) heap-a heap-b)
      (list 'hnode elem (+ 1 (rank heap-a)) heap-a heap-b)
  )
 )

(define (hnode-elem h)
  (second h))

(define (hnode-left h)
  (fourth h))

(define (hnode-right h)
  (fifth h))

(define (hnode-rank h)
  (third h))

(define (hord? p h)
  (or (leaf? h)
      (<= p (elem-priority (hnode-elem h)))))

(define (heap? h)
  (or (leaf? h)
      (and (hnode? h)
           (heap? (hnode-left h))
           (heap? (hnode-right h))
           (<= (rank (hnode-right h))
               (rank (hnode-left h)))
           (= (rank h) (inc (rank (hnode-right h))))
           (hord? (elem-priority (hnode-elem h))
                  (hnode-left h))
           (hord? (elem-priority (hnode-elem h))
                  (hnode-right h)))))

(define (rank h)
  (if (leaf? h)
      0
      (hnode-rank h)))

;; operations

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
    [else (let* ([najmhnode (if (< (elem-priority (hnode-elem h1)) (elem-priority (hnode-elem h2))) h1 h2)] 
            [e (hnode-elem najmhnode)]
            [HL (hnode-left najmhnode)]
            [HR (hnode-right najmhnode)]
            [h (if(< (elem-priority (hnode-elem h1)) (elem-priority (hnode-elem h2))) h2 h1) ])
       (make-hnode e HL (heap-merge h HR)))
       ]
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

(heapsort (randlist 5 10))
(heapsort (randlist 10 20))

(define heapsort-testowanie
  (test-suite
   "Testy heapsorta"
   (test-case
    "Losowa lista"
    (check-equal? (sorted? (heapsort (randlist 5 10))) #t)
    )
   
   (test-case
    "Wieksza losowa lista"
    (check-equal? (sorted? (heapsort (randlist 10 100))) #t)
    )
   
    (test-case
    "Długa losowa lista"
    (check-equal? (sorted? (heapsort (randlist 100 1000))) #t)
    )
    
    (test-case
     "Bardzo długa lista"
     (check-equal? (sorted? (heapsort (randlist 10000 100000))) #t)
    )
   )
  )
(run-tests heapsort-testowanie)