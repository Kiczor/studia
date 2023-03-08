#lang racket

(define (tagged-list? len sym x)
  (and (list? x)
       (= (length x) len)
       (eq? (first x) sym)))

(define leaf 'leaf)

(define (leaf? x)
  (eq? x 'leaf))

(define (node e l r)
  (list 'node e l r))

(define (node? x)
  (tagged-list? 4 'node x))

(define (node-elem x)
  (second x))

(define (node-left x)
  (third x))

(define (node-right x)
  (fourth x))

(define (tree? x)
  (or (leaf? x)
      (and (node? x)
           (tree? (node-left  x))
           (tree? (node-right x)))))

(define (btree? t)
  (or (eq? t 'leaf)
      (and (tagged-list? 4 'node t)
           (btree? (third t))
           (btree? (fourth t)))))

(define (mirror t)
  (cond
    [(leaf? t) t]
    [else (node (node-elem t) (mirror (node-right t)) (mirror (node-left t)))]
    ))

(mirror '(node a (node b (node c leaf leaf) leaf) (node d leaf leaf)))

(define (flatten t)
    (cond
      [(leaf? t) null]
      [(append (append (flatten (node-left t)) (list (node-elem t))) (flatten (node-right t)))]))

(flatten '(node a (node b (node c leaf leaf) leaf) (node d leaf leaf)))

(define (insert x t)
  (cond
    [(leaf? t)            (node x leaf leaf)]
    [(= (node-elem t) x)  t]
    [(> (node-elem t) x)  (node (node-elem t)
                                (insert x (node-left t))
                                (node-right t))]
    [(< (node-elem t) x)  (node (node-elem t)
                                (node-left t)
                                (insert x (node-right t)))]))

(define (treesort x)
  (define (insertall lt t)
    (if (null? lt)
        t
        (insertall (cdr lt) (insert (car lt) t))
        )
    )
  (flatten (insertall x leaf)))

(treesort '(2 5 7 3 1 3 -1 23))