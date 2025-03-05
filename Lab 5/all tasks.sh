
# 1. Create a directory called project in your home directory
mkdir -p ~/project

# 2. Navigate to the project directory
cd ~/project

# 3. Create an empty file named task1.txt in the project directory
touch task1.txt

# 4. List all files in the current directory using the ls command. Create a file called file1.txt
ls
> file1.txt

# 5. Change the permissions of file1.txt so that only the owner has read and write permissions, and others have no permissions
chmod 600 file1.txt

# 6. Check the permissions of file1.txt using the ls -l command
ls -l file1.txt

# 7. Grant execute permissions to the owner of file1.txt
chmod u+x file1.txt

# 8. Display the current working directory using the pwd command
pwd

# 9. Show the current date and time using the date command
date

# 10. Display your system’s disk usage with the df -h command
df -h

# 11. Display system uptime using the uptime command
uptime

# 12. Show all users currently logged into the system using the who command
who

# 13-14. The script will take a filename as input, count, and display the number of lines in that file
echo -n "Enter filename: "
read filename
wc -l "$filename"
