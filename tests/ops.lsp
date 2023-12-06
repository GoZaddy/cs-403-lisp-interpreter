;; Test passes!
(SET a 5)
(set b 0)
(set c '"hey")

(> a b)
(< a b)
(eq? a b)
(symbol? a)
(symbol? 'a)
(list? a)
(list? '(1 2 3))
(nil? a)
(nil? ())
(number? c)
(number? a)

;; Expected output:
;; t
;; ()
;; ()
;; ()
;; t
;; ()
;; t
;; ()
;; t
;; ()
;; t