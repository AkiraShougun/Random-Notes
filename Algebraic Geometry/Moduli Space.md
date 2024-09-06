$$
M_{0,n} \simeq  (\mathbb{P}^1 \ /\left\{ 1,0,\infty \right\})^{n-3} /\left\{ (t_1,\cdots,t_{n-3}) | t_i = t_j  \text{ for some }t_i \neq t_j\right\}
$$
$$[M_{0,n}] = \prod_{k=4}^{n}(\mathbb{L}-k+2)$$
Grothendieck class of $\overline{M_{0,n}}$

$[\overline{M_{0,3}}] = 1$
$[\overline{M_{0,4}}] = \mathbb{L}+1$
$[\overline{M_{0,5}}] = \mathbb{L}^2+5\mathbb{L}+1$ = L^2 +2L + (3L+1)
$[\overline{M_{0,6}}] = \mathbb{L}^3+16\mathbb{L}^2+16\mathbb{L}+1$ = L^3+6L^2+6L+1 + (10L^2+10L)
$[\overline{M_{0,7}}] = \mathbb{L}^4+42\mathbb{L}^3+127\mathbb{L}^2+42\mathbb{L}+1$ = L^4+17L^3+32L^2+17L+1 + (25L^3+95L^2+10L)
$[\overline{M_{0,8}}] = \mathbb{L}^5+99\mathbb{L}^4+715\mathbb{L}^3+715\mathbb{L}^2+99\mathbb{L}+1$

```python
from sympy import expand, symbols, binomial

L = symbols("L")

def Moduli_space(n):

    if n==3:

        return 1

    expr = 0

    for i in range(3,n-2+1):

        expr += binomial(n-2,i-1)*Moduli_space(i)*Moduli_space(n+1-i)

    return expand(Moduli_space(n-1)*(L+1) + L * expr)
```