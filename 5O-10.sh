FICHIER_ENTREE="data.csv"
FICHIER_TRIE="temp_sorted.csv"
FICHIER_MIN="min_50.dat"
FICHIER_MAX="max_10.dat"

tail -n +2 "$FICHIER_ENTREE" | sort -t';' -k2,2n > "$FICHIER_TRIE"

head -n 50 "$FICHIER_TRIE" > "$FICHIER_MIN"

tail -n 10 "$FICHIER_TRIE" > "$FICHIER_MAX"
