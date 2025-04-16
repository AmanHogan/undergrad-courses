import math
from nltk.tokenize import RegexpTokenizer
from nltk.stem.porter import PorterStemmer
from nltk.corpus import stopwords

# Initialize tokenizer and stemmer
tokenizer = RegexpTokenizer(r'\b\w+\b')
stemmer = PorterStemmer()

def calculate_tf_query(token, query_tokens):
    """
    Calculates the the number of times a token appears in a document/query_tokens

    Args:
        token (str): term
        query_tokens (list[str]): document

    Returns: float: term frequency
    """
    return 1 + math.log10(query_tokens.count(token)) if query_tokens.count(token) > 0 else 0

def calculate_query_vector(query_tokens, all_paragraphs, df_dict):
    """
    Calculates the TF-IDF vector for each paragraph

    Args:
        query_tokens (list[str]): query token str
        all_paragraphs (list[list[str]]): all documents
        df_dict (dict{}): document freq for each token

    Returns:
        dict{}: normalized query vector
    """
    query_vector = {}

    # tf-idf = tf * idf
    for token in set(query_tokens):
        tf = calculate_tf_query(token, query_tokens)
        idf = math.log10(len(all_paragraphs) / df_dict.get(token, 1))
        query_vector[token] = tf * idf
    
    # tf-idf =  Normalize (tf-idf)
    vector_length = math.sqrt(sum(value ** 2 for value in query_vector.values()))
    query_vector = {token: value / vector_length for token, value in query_vector.items()}
    
    return query_vector

def cosine_similarity(vector1, vector2):
    """
    Calculates cosine simularity of two vectors

    Args:
        vector1 (dict{}): vector
        vector2 (dict{}): vector

    Returns:
        float: dot product of vectors / cosine simularity
    """

    dot_product = sum(vector1.get(token, 0) * vector2.get(token, 0) for token in set(vector1) | set(vector2))
    magnitude1 = math.sqrt(sum(value ** 2 for value in vector1.values()))
    magnitude2 = math.sqrt(sum(value ** 2 for value in vector2.values()))
    return dot_product / (magnitude1 * magnitude2) if magnitude1 != 0 and magnitude2 != 0 else 0

def getidf(token):
    """
    Gets the inverse document frequency of agiven token

    Args: token (str): token

    Returns: float: idf
    """

    # -1 if any upper case
    if any(char.isupper() for char in token):
        return -1
    
    # not in dictionary
    elif token not in df_dict:
        return -1
    
    else:
        return math.log10(len(paragraphs) / (df_dict[token]))

def getqvec(qstring):
    """
    Gets the query vector for a query string

    Args: qstring (str): query string

    Returns: dict{}: query vector
    """

    query_tokens = tokenizer.tokenize(qstring.lower())
    query_tokens = [stemmer.stem(token) for token in query_tokens if token not in stop_words]
    return calculate_query_vector(query_tokens, paragraphs, df_dict)

def query(qstring):
    """Returns the paragraph in the corpus with the highest cosine similarity

    Args:
        qstring (str): query string

    Returns:
        str, float: paragraph and similarity score
    """
    query_vector = getqvec(qstring)
    paragraph_similarity_scores = [(i, cosine_similarity(query_vector, tf_idf_vectors[i])) for i in range(len(tf_idf_vectors))]
    
    # if all similarities are 0 , return no match
    if all(score == 0 for _, score in paragraph_similarity_scores):
        return "No Match\n", 0.0
    
    else:
        max_similarity_paragraph = max(paragraph_similarity_scores, key=lambda x: x[1])
        max_similarity_paragraph_index = max_similarity_paragraph[0]
        max_similarity_score = max_similarity_paragraph[1]
        return paragraphs[max_similarity_paragraph_index] + '\n', max_similarity_score


if __name__ == '__main__':

    # Read file in cat.txt
    filename = './cat.txt'
    doc = None
    with open(filename, "r", encoding='UTF-8') as file:
        doc = file.read()

    # Split document into parapgrahs and tokenize paragraph
    paragraphs = doc.split('\n')
    paragraphs = [paragraph for paragraph in paragraphs if paragraph != '']
    paragraph_tokens_list = [tokenizer.tokenize(paragraph.lower()) for paragraph in paragraphs]

    # Remove stop words and stem tokens
    stop_words = set(stopwords.words('english'))
    paragraph_tokens_list = [[stemmer.stem(token) for token in tokens if token not in stop_words] for tokens in paragraph_tokens_list]

    # Compute document frequency for each token and store into dictionary
    df_dict = {}
    for paragraph_tokens in paragraph_tokens_list:
        for token in set(paragraph_tokens):  # Use set to count each token once per document
            df_dict[token] = df_dict.get(token, 0) + 1


    # Compute tf-idf vectors for each paragraph
    tf_idf_vectors = [calculate_query_vector(tokens, paragraph_tokens_list, df_dict) for tokens in paragraph_tokens_list]

    ###################### EXAMPLE USAGE #######################
    print("%.4f" % getidf(stemmer.stem("domesticated")))
    print("%.4f" % getidf(stemmer.stem("abandonment")))
    print("%.4f" % getidf(stemmer.stem("destruction")))
    print("%.4f" % getidf(stemmer.stem("the")))
    print("%.4f" % getidf(stemmer.stem("populations")))
    print("%.4f" % getidf(stemmer.stem("genetic")))
    print("%.4f" % getidf(stemmer.stem("eventually")))
    print("%.4f" % getidf(stemmer.stem("mammals")))
    print("%.4f" % getidf(stemmer.stem("relationships")))
    print("%.4f" % getidf(stemmer.stem("native")))
    print(getqvec("Cats have either a mutualistic or commensal relationship with humans."))
    print(getqvec("The cat skull is unusual among mammals in having very large eye sockets and a powerful and specialized jaw. Within the jaw, cats have teeth adapted for killing prey and tearing meat."))
    print(getqvec("query entropy"))
    print(getqvec("Cats are obligate carnivores"))
    print("%s%.4f" % query("Cats have either a mutualistic or commensal relationship with humans."))
    print("%s%.4f" % query("The cat skull is unusual among mammals in having very large eye sockets and a powerful and specialized jaw. Within the jaw, cats have teeth adapted for killing prey and tearing meat."))
    print("%s%.4f" % query("query entropy"))
    print("%s%.4f" % query("Cats are obligate carnivores"))




