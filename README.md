# parametric-calculator

$param_name = $expr - declare parameter, ex: a = 5 + i

$function_name (x, ...) = $expr - declare function, ex: taylor_cos(x) = 1 - x^2 / 2! + x^4 / 4! - x^6 / 6!; f(x, y) = x + y^2

binary $op_name = $function_name - declare custom binary operator

unary_prefix , = $function_name - declare custom prefix unary operator

unary_postfix , = $function_name - declare custom postfix unary operator

pre-defined operators:

binary: +-/*^

unary_prefix: -+

unary_postfix: !

pre-defined functions: negative(), positive(), fact(), add(,), sub(,), mul(,), div(,) pow(,)
