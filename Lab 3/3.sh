# if the filename is given in the arguement then continue, else ask for filename
if [ $# -eq 0 ]; then
    echo "No file name is provided"
    echo "Please enter a file name"
    read filename
else
    filename="$1"
fi

# if file exist then append else error msg
if [ -f "$filename" ]; then
    echo "File exists"
    timestamp=$(date +"%Y-%m-%d %H:%M:%S")

    echo "$timestamp" >> "$filename"

    echo "Date and Time appened to file: $filename"

else
    echo "File opening Failed"
fi
