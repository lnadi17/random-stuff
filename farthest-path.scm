(define (child-nodes node)
	(car (cdr node)))

(define (maximum-of-list mylist)
	(if (null? mylist) 0
		(if (> (car mylist) (maximum-of-list (cdr mylist))) (car mylist) (maximum-of-list (cdr mylist)))))

(define (farthest-path node) 
	(if (null? node) 0
		(+ (car node) (maximum-of-list (map farthest-path (child-nodes node))))))



