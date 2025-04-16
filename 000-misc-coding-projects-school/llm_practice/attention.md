# Embeddings

Goal: taken in a tyring of text and predict the next word.

Mechanism: Tokenize each input and give each token an embedding which can be visualized as a vector in a higher dimensional space.
The meaning of a token is captured in the dimensions of this vector.

# Scaled Dot-Product Attention

Goal: we want the embeddings for  each word (dense vector) to take on different values or meanings depending on the context of a word.

### Example

american | shrew | mole |
--- | --- | --- |
5.5 | 3.5 | 5.5|
4.2 | 1.2 | 4.2|
2.1 | 12 | 2.1 |
... | ... | ...|
2.1 | 3 | 2.1|

mole | of | co2 |
--- | --- | --- |
5.5 | 3.5 | 3|
4.2 | 1.2 | 1|
2.1 | 12 | 3|
... | ... | ...|
2.1 | 3 | 1|

boisy | of | mole |
--- | --- | --- |
5.5 | 3.5 | 5.5|
4.2 | 1.2 | 4.2|
2.1 | 12 | 2.1 |
... | ... | ...|
2.1 | 3 | 2.1|

In this example, the embedding (meaning of the word) is the same in all 3 contexts even though they should be different.

An attenion block should fix this issue by having the embedding of a token being updated rountinuely.



You start with an intial embedding of a token that tells you the meaning of the token

a | fluffy | blue | creatue | ... | verdant |forest |
--- | --- | --- | --- | --- | --- | --- |
$E_1$ | $E_2$  | $E_3$  | $E_4$  | ... | $E_7$ |$E_8$ |

Have a certain matrix called $W_Q$ that maps the embedding to a smaller dimensional space called the Query/Key space. We do this by performing $W_Q * E_i$ to get the query vector $Q_i$

a | fluffy | blue | creatue | ... | verdant |forest |
--- | --- | --- | --- | --- | --- | --- |
$E_1$ | $E_2$  | $E_3$  | $E_4$  | ... | $E_7$ |$E_8$ |
$W_Q$ | $W_Q$   | $W_Q$   | $W_Q$  | ... | $W_Q$  | $W_Q$ |
$Q_1$ | $Q_2$  | $Q_3$  | $Q_4$  | ... | $Q_7$ |$Q_8$ |


Have another matrix called $W_K$ that maps the embeddings to a smaller dimensional space called the Query/Key space. We do this by performing $W_K * E_i$ to get the key vector $K_i$


a | fluffy | blue | creatue | ... | verdant |forest |
--- | --- | --- | --- | --- | --- | --- |
$E_1$ | $E_2$  | $E_3$  | $E_4$  | ... | $E_7$ |$E_8$ |
$W_K$ | $W_K$   | $W_K$   | $W_K$  | ... | $W_K$  | $W_K$ |
$K_1$ | $K_2$  | $K_3$  | $K_4$  | ... | $K_7$ |$K_8$ |


How well the key and query vectors line up denotes a relationship between the key and query. Another way of thinking of this as thinking of the key values as "answering" the queries by how well they line up in that lower dimensional space.


We can measure their similarity by performing a dot product after forming a key query table and picking the number with the largest products.


--- | a | fluffy | blue | creatue | ... | verdant |forest |
--- | --- | --- | --- | --- | --- | --- | --- |
a | $K_1 * Q_1$  | $K_1 * Q_2$  | . | ... | . |. | --- |
fluffy | .   | .  | .  | +100 | .  | . | --- |
blue | .  | .  | .  | +200 | . | .  | --- |
creatue | . | .  | . | ... | . | . | --- |
... | .  | .  | .  | ... | . | . | --- |
verdant | .  | .  | .  | ... | . | . | --- |
forest  | .  | .  | .  | ... | . | . | --- |


Since fluffy and blue have a high dot product, you would say that "fluffy and blue attend to creature"

This yields raw scores, but we want two things from these scores:
1. Normalize these scores for each column and get them in the range of 0 to 1. This is called an attention pattern (each column has a weight of how relevant the word on the right is to it)
2. Make sure that words in the future, in this table, do not affect words in the past.


How we can accomplish this is by performing softmax on each column. There is an equation that outlines the proccess we want to accomplish:

$Attention(Q,K,V) = softmax(\frac{QK^T}{\sqrt{d_k}})V$

We use key vectorcolumns Q and K vector row to get V vectors

Next we can tackle the issue of not having later tokens to influencing previous tokens is by setting values in the triangular matric to negative infinity. Then you apply softmax and get 0. THis is called masking.

One note is that the size of this increases by the size of the context window.

Next we have to update the embeddings with all this information

We do this by creating another matrix called the value matrix $W_K$. We multiply this value matrix by each embedding to get a sequence of value vectors. These value vectors are associated with their corresponsing keys

--- | a [$E_1$] | fluffy [$E_2$] | blue | creatue | ... | verdant |forest |
--- | --- | --- | --- | --- | --- | --- | --- |
a [$E_1 * W_V = V_1$] | $V_1 * value$| $V_1 * value$ | . | ... | . |. | --- |
fluffy [$E_2 * W_V = V_3$]| $V_2 * value$ | $V_2 * value$  | .  |  | .  | . | --- |
blue | .  | .  | .  |  | . | .  | --- |
creatue | . | .  | . | ... | . | . | --- |
... | .  | .  | .  | ... | . | . | --- |
verdant | .  | .  | .  | ... | . | . | --- |
forest  | .  | .  | .  | ... | . | . | --- |

Then you add together the values in each column to get the amoun of change. For example, you would get $\Delta E_1$ and addd this tp the original embedding. $\Delta E_1 +  E_1 = E_1'$

This process is called a single head of attention.


A full trnasformer runs several attention heads in parralel 

## Key Words
The $Q_i$ vector is essentially an encoding of the question: *are there any important words behind me that will modify my meaning and what is there position?*

The $W_Q$ is a bunch of weights and paramaters that map the embedding ($E_i$) to Query/Key space.

THe Embedding space is a higher dimensional space where each dimension is a *feature* of the vector that encodes some specific meaning.

The Query/Key space is  a lower dimensional space that encodes queryies and keys


```py
k = w_key(x) # here is waht i have
q = w_query(x) # here is what im interested in


wei = q @ k.transpose(-2,-1) # B T 16, @ B 16 T , B T T 
tril = torch.tril(torch.ones(T,T)) # with traingular matricies we can get a aggragate value of how much we car about
# previous information
wei = wei.masked_fill(tril == 0, float('-inf'))
wei = F.softmax(wei, dim=-1)

v = value(x) # here is what i give if yoiure interested in it
out = wei @ v
```



# Decoder only, encoder only
in decoder only, we  only care about the tokens before the current opne. Future tokesn cannot affect the past.

In encoder only, like sentiment analysis or language tranlation, future words can affect past onyes


# Self aattention vs Cross attention
We are using self attention becaause keys, wueies adn values are specififally from one source (x). 

cross attention, we pull information from a sperate source of nodes.

