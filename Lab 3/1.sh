# check if two arguments are provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <num1> <num2>"
    exit 1
fi

# read Command line arguments
num1=$1
num2=$2

result=$((num1 * num2))

echo "The multiplication of $num1 and $num2 is: $result"

