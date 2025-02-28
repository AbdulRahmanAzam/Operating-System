
# checking for argument, if not then ask for the sentence
if [ $# -eq 0 ]; then
    echo "No sentence provided as an argument"
    echo "Pleaes enter a sentence"
    read sentence
else
    sentence="$*"
fi

# total times the vowel is used
vowel_count=$(echo "$sentence" | grep -o '[aeiou]' | wc -l)
echo -e "The no of vowels used among 5 in the sentence is $vowel_count\n"

# total times the each vowel is used
total_vowels=0
for vowel in a e i o u
do 
    count=$(echo "$sentence" | grep -o "$vowel" | wc -l)
    echo "Count of '$vowel' : '$count'"
    total_vowels=$((total_vowels + count))
done

