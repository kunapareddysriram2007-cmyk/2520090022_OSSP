# Practical-10

Aim:
Study Linux inode structures, hard links, symbolic links, and memory-mapped file I/O using mmap().

Files:

- mmap_file.c
- sample.txt
- observations.txt

Compile:

gcc mmap_file.c -o mmap_file

Run:

./mmap_file

Commands:

ls -i sample.txt
stat sample.txt
find . -name "sample.txt"

ln sample.txt hardlink.txt
ln -s sample.txt softlink.txt
