;; gets list[0]
(define first_value (listt) (
    cond (nil? listt) nil 't (car listt)
))

;; gets list[1]
(define second_value (listt) (
    cond (nil? listt) nil
        't (cond (nil? (cdr listt)) nil 't (car (cdr listt)))
))
;; equivalent of python's list[1:]
(define slice_from_second_value (listt) (
    cond (nil? listt) nil
        't (cdr listt)
))
;; equivalent of python's list[2:]
(define slice_from_third_value (listt) (
    cond (nil? listt)
        nil
        't (
            cond (nil? (cdr listt))
            nil
            't (cdr (cdr listt))
        )
))

(define greater_than_ten? (num) (  > num 10 ))

;; checks if first frame in list is a strike (knocked all pins in one shot)
(define is_strike? (listt) ( == (first_value listt) 10 ))

;; checks if second frame in list is a spare (knocked all pins in 2 bowls in a frame)
(define is_spare? (listt)(
    cond 
        (nil? (first_value listt)) ()
        (nil? (second_value listt)) ()
        't (== (+ (first_value listt) (second_value listt)) 10)
))


;; increment input by 1
(define increment (num) ( cond (nil? num) 1 't (+ num 1) ))


;; adds list[0] and list[1]
(define add_frame (listt) (
    cond 
        (nil? (first_value listt)) 0
        (nil? (second_value listt)) 0
        't (+ (first_value listt) (second_value listt))
))

(define wrap (n)(
    cond (nil? n) 0 't n
))


;; adds scores for strike/spare to a base value
(define get_score (base is_prev_strike is_prev_spare listt) (
    cond
        is_prev_strike (+ (+ (wrap (first_value listt)) (wrap (second_value listt))) (wrap base))
        is_prev_spare (+ (first_value listt) base)
        't base
))


;; a recursive function, contains main logic
(define process_frame (counter listt is_prev_strike is_prev_spare) (
    cond 
        (nil? listt) 0
        (greater_than_ten? counter) (
            + 
            (first_value listt)
            (process_frame counter (slice_from_second_value listt) () ())
        )
        't (
            cond
                (is_strike? listt) (
                    + 
                    (get_score 10 is_prev_strike is_prev_spare listt)
                    (process_frame (increment counter) (slice_from_second_value listt) 't ())
                    
                )
                (is_spare? listt) (
                    + 
                    (get_score 10 is_prev_strike is_prev_spare listt)
                    (process_frame (increment counter) (slice_from_third_value listt) () 't)  
                )

                't (
                    + 
                    (get_score (add_frame listt) is_prev_strike is_prev_spare listt)
                    (process_frame (increment counter) (slice_from_third_value listt) () ())
                )
        )
))

;; entry point
(define bowling (listt) ( process_frame 1 listt () () ))


;; (bowling '(0 0 0 0     0 0 0 0        0 0 0 0      0 0 0 0     0 0 0 0)) ;; 0, 20 gutter balls
;; (bowling '(10 10 10 10     10 10 10 10     10 10 10 10)) ;; 300, 12 strikes
(bowling '(5 3 5 3  3 5 5 3  3 5 3 5  6 2 2 6  7 1 1 7  ));; 80
;; (bowling '(0 0 0 0     0 0 0 0        0 0 0 0      0 0 0 0     0 0 10 5 4)) ;; 19, strike in 10 frame
;; (bowling '(0 0 0 0     0 0 0 0        0 0 0 0      0 0 0 0     10 5 4)) ;; 28, strike in 9th frame


;; (define fib (n) (
;;     cond (< n 0) 0 (<= n 1) n 't (+ (fib (- n 1)) (fib (- n 2)))
;; ))

;; (fib 19)