# Start with printing hello world
# print "hello world!"

# Variable
# No declaration required
# Dynamic Typing
# a = 5
# print a
# a = a + 5
# print a
# a += 5
# print a
# a = "hello world!"
# print a
# a += 10
# print a 	# Will throw type-mismatch error
# a += str(10)
# print a

# User input
# name = input("What is your name? ")
# print name
# name = raw_input("What is your name? ") 	# For string input
# print name
# age = raw_input("What is your age? ")
# print age
# print type(age)
# age = input("What is your age? ")		# For int/float input
# print age
# print type(age)

# String Manipulation
# st = "hello world !"
# print st
# st2 = st.strip(' !') + '!'
# print st2

# print st[0:5] + " everyone"
# print "orl" in st

# st3 = st.split('o w')
# print st3
# list
# a = [] 	# Empty list
# a = [ 5, 6 ]
# print a
# b = a
# print b
# b[0] = 11
# print b
# print a
# b = a[:] # To create seperate copy OR b = list(a)
# a.append(9)		#
# print a
# a.append('hello')
# print a
# print len(a)
# del a[1]		#
# print a
# a.append(100)
# a.append(5)
# print a
# print a.count(5)	#
# a = a*2 # Repeat a in place
# b = [ "world", "is", "beautiful"]
# a.extend(b)
# print a
# a.remove(5)
# print a
# a.remove(5)
# print a
# print a.pop(), a
# a.append(b)
# print a

'''
list.append(obj)			Appends object obj to list
list.count(obj)				Returns count of how many times obj occurs in list
list.extend(seq)			Appends the contents of seq to list
list.index(obj)				Returns the lowest index in list that obj appears
list.insert(index, obj)		Inserts object obj into list at offset index
list.pop(obj=list[-1])		Removes and returns last object or obj from list
list.remove(obj)			Removes object obj from list
list.reverse()				Reverses objects of list in place
list.sort([func])			Sorts objects of list, use compare func if given
'''

# dictionary 		# Key cannot be list/dictionary
# dictionary = {}
# dictionary['hello'] = 'world'
# dictionary[1] = 'wow'

# new_dict = {}
# new_dict[4] = 5

# dictionary['dict'] = new_dict

# print dictionary
# print dictionary['hello']
# print dictionary['dict'][4]

# lst = [1, 2]
# dictionary['list'] = lst

# print dictionary

# new_dict2 = {}
# new_dict2['1'] = 2

# dictionary.update(new_dict2)
# print dictionary 

# print len(dictionary)

# dictionary2 = dictionary 		# We can't copy dictionary like this
# dictionary2['new'] = 'element'
# print dictionary2
# print dictionary

# del dictionary2['new']
# print dictionary2
# print dictionary

# dictionary2 = dictionary.copy()
# dictionary2['new'] = 'element'
# print dictionary2
# print dictionary

