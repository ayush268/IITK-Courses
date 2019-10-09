import os

mode = 'r'		# other modes: rb, r+, rb+, w, w+, wb, wb+, a, ab etc. 
filename = 'demofile.txt'
fo = open(filename, mode)
print "Name of the file: ", fo.name
print "Closed or not : ", fo.closed
print "Opening mode : ", fo.mode

file_content = ''
read_100_bytes = fo.read(100)
print read_100_bytes
file_content += read_100_bytes

read_100_bytes = fo.read(100)
print read_100_bytes
file_content += read_100_bytes

print file_content

file_pos = fo.tell()
print file_pos

fo.close()

fo = open(filename, mode)
fo.seek(file_pos, 0)
read_100_bytes = fo.read(100)
print read_100_bytes
file_content += read_100_bytes

print file_content
file_pos = fo.tell()
fo.close()

new_file_content = ''
fo = open(filename, mode)
line = fo.readline()
while line:
	new_file_content += line
	line = fo.readline()

print new_file_content
fo.close()

# mode = 'a'
# fo = open(filename, mode)
# fo.write(' some random string ')
# fo.close()
