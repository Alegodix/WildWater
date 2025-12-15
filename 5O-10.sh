FILE="data.csv"
FILE_TRIE="temp_sorted.csv"
FILE_MIN="min_50.dat"
FILE_MAX="max_10.dat"

tail -n +2 "$FILE" | sort -t';' -k2,2n > "$FILE_TRIE"

head -n 50 "$FILE_TRIE" > "$FILE_MIN"

tail -n 10 "$FILE_TRIE" > "$FILE_MAX"
