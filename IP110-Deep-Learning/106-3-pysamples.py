a = "555.444"
print "a = ", a,  "type is", type(a)

f = float(a)
print "f = ", f,  "type is", type(f)

#i = int(a)  #you will have an error, but if a= "554" it is okay.
i = int(f)
print "i = ", i,  "type is", type(i)
#
#
# '''understand for & in '''
a = [2,3,4,5,6]
xyz = [0,12,4,6,242]
#
d=[]  #init a list d
for x in xyz:
	if x in a:
		d.append(x)
print "more human readable version", d

d2 = [x for x in xyz if x in a]
print "more concise version", d2

# it is an integer divide
a = 2/5
print "a =", a

a = 2.0/5
print "a =", a
#
# / is very speical char

filename1 = "M:\nickel_project\reactive.smi" # DANGER!
print "filename =", filename1

filename2 = "M:\\nickel_project\\reactive.smi" # Better!
print "filename =", filename2

filename3 = "M:/nickel_project/reactive.smi" # Usually works
print "filename =", filename3

filename4 = r"M:\nickel_project\reactive.smi"
print "filename =", filename4
#
#list
names = ["Ben", "Chen", "Tony"]
print len(names)

print names[0]
print names[1]
print names[2]
#print names[3]

print names[-1]
print names[-2]
print names[-3]
#
# ids = ["3pti", "2plv", "1crn"]
# print "list =", ids
#
# ids.append("0alm")
# print "append", ids
#
# del ids[0]
# print "delete", ids
#
# ids.sort()
# print "sort", ids
#
# ids.reverse()
# print "resvers", ids
#
# ids.insert(0, "3pti")
# print "insert", ids
#
# symbol_2_name = {
# 		"H": "hydrogen",
# 		"He": "helium",
# 		"Li": "lithium",
# 		"C": "carbon",
# 		"O": "oxygen",
# 		"N": "nitrogen"
# 	}
#
# print "dictionary:", symbol_2_name
#
# print "C->", symbol_2_name["C"]
#
# print symbol_2_name.get("P", "unknown")
#
# print symbol_2_name.get("C", "unknown")
#
# print "keys:", symbol_2_name.keys()
# print "values:", symbol_2_name.values()
#
#
# symbol_2_name.update( {"P": "phosphorous", "S": "sulfur"} )
# print symbol_2_name.items()
#
# del symbol_2_name['C']
# print symbol_2_name