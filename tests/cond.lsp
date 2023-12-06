;; Test passes!

(set age 25)

(cond 
    (> age 39) '"You're old"
    (> age 29) '"You're getting there"
    (> age 19) '"You're perfectly aged"
    't '"Grow up"
)

;; Expected output:
;; "You're perfectly aged"