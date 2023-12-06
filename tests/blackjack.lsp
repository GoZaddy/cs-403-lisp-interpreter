;; CS 403 Blackjack project in Yisp
;; Test passes!


(define get_regular_card_value (card) (
    cond 
        (== card 11) 10
        (== card 12) 10
        (== card 13) 10
        (> card 1) card ;; assuming valid input (numbers are between 1-13)

))
(define choose_answer (num1 num2) (
    cond 
        (> num1 num2) (
            cond (> num1 21) num2 't num1
        )
        (== num1 num2) num1
        't (choose_answer num2 num1)
))
(define dfs (listt current) (
    cond (nil? listt) 
        current
        't (
            cond (== (car listt) 1)
                (choose_answer 
                    (dfs (cdr listt) (+ 1 current))
                    (dfs (cdr listt) (+ 11 current))
                )
                't (dfs (cdr listt) (+ (get_regular_card_value (car listt)) current))
        )
)) ;depth first search
(define blackjack (listt) (dfs listt 0)) ;entrypoint

(blackjack '(1 11)) ; 21
(blackjack '(1 1)) ; 12
(blackjack '(1 1 1 13)) ; 13



;; Expected output:
;; 21
;; 12
;; 13

