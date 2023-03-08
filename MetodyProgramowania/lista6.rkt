#lang racket

;'(+ 4 3 (* 5 8))
;(list '+ 4 3 (list '* 5 8))
;(list '+ '4 '3 '(* 5 8))
;'(+ 4 3 '(* 5 8))
;(list '+ '4 '3 ''(* 5 8))
;(list '+ '4 '3 '(quote (* 5 8)))
;(list '+ '4 '4 (list 'quote '(* 5 8)))

;(list '+ 4 3 (cons 5 8))
;
;`(+ 4 3 (5 . 8))
;`(+ 4 3 ,(* 5 8))
;(list `+ 4 3 `,(* 5 8))


(struct node (v l r) #:transparent)
(struct leaf () #:transparent)

;; predykat: czy dana wartość jest drzewem binarnym?

(define (tree? t)
  (match t
    [(leaf) true]
    ; wzorzec _ dopasowuje się do każdej wartości
    [(node _ l r) (and (tree? l) (tree? r))]
    ; inaczej niż w (cond ...), jeśli żaden wzorzec się nie dopasował, match kończy się błędem
    [_ false]))

;; przykładowe użycie dopasowania wzorca

(define (insert-bst v t)
  (match t
    [(leaf) (node v (leaf) (leaf))]
    [(node w l r)
     (if (< v w)
         (node w (insert-bst v l) r)
         (node w l (insert-bst v r)))]))

(define (add x lst)
  (if (null? lst)
      null
      (append (list (append (list x) (car lst)) ) (add x (cdr lst))))
  )

(add 3 (list (list 4 5) (list 5 6)))

(define (paths t)
  (match t
    [(leaf) (list (list '*))]
    [(node w l r) (add w (append (paths l) (paths r)))]
    )
  )

(define (paths2 t)
  (match t
    [(leaf) (list (list '*))]
    [(node w l r) (map (lambda (lista) (append (list w) lista)) (append (paths l) (paths r)))]
    )
  )

(paths2 (node 3
             (node 2
                   (leaf)
                   (node 6
                         (node 7 (leaf) (leaf))
                         (leaf)))
             (node 7 (leaf) (leaf))))



(struct const (val) #:transparent)
(struct op (symb l r) #:transparent)

(define (expr? e)
  (match e
    [(const n) (number? n)]
    [(op s l r) (and (member s '(+ *))
                     (expr? l)
                     (expr? r))]
    [_ false]))

;; przykładowe wyrażenie

(define e1 (op '* (op '+ (const 2) (const 2))
                  (const 2)))

;; ewaluator wyrażeń arytmetycznych

(define (eval e)
  (match e
    [(const n) n]
    [(op '+ l r) (+ (eval l) (eval r))]
    [(op '* l r) (* (eval l) (eval r))]))

;; kompilator wyrażeń arytmetycznych do odwrotnej notacji polskiej

(define (to-rpn e)
  (match e
    [(const n) (list n)]
    [(op s l r) (append (to-rpn l)
                        (to-rpn r)
                        (list s))]))

(define (mn-czy-dod e)
  (define (IT ex) ;; pierwsze dodawanie drugei mnozenie
    (match ex
      [(const n) (cons 0 0)]
      [(op '+ l r) (let ((pl (IT l)))
                     (let ((pr (IT r)))
                       (cons (+ (car pl) (car pr) 1) (+ (cdr pl) (cdr pr)))
                       )
                     )]
      [(op '* l r) (let ((pl (IT l)))
                     (let ((pr (IT r)))
                       (cons (+ (car pl) (car pr)) (+ 1 (cdr pl) (cdr pr)))
                       )
                     )]
      )
    )
  (let ((w (IT e)))
    (if (< (car w) (cdr w))
        true
        false
        )
    )
)

(define e2 (op '* (op '* (op '+ (const 2) (const 2))
                  (const 2)) (const 3)))
(mn-czy-dod e2)
(mn-czy-dod e1)
(mn-czy-dod (op '+ e1 e2))

(struct section (title cont) #:transparent)
(struct text (title autor sections) #:transparent)

(define (valid-text? t)
  (and (string? (text-title t))
       (string? (text-autor t))
       (list? text-sections)
       (andmap (lambda (el) (valid-section? el)) (text-sections))
       )
  )

(define (valid-section? s)
  (and (section? s)
       (string? (section-title s))
       (list? (section-cont s))
       (andmap (lambda (el)
                 (or (string? el)
                     (valid-section? el)))
               (section-cont s))
       )
  )

;;(define (text-html tx)