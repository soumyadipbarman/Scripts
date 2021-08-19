# Module for calculating fraction of negative weighted events & cross-section from log files
# USAGE : python GenXsecAnalyzer.py
# Only need to change file location

# Author : Soumyadip Barman
# Date : 24 Oct 2020

#####################################################################################

import os
import math

## File location ##
Path = "/home/sobarman/t3store3/Generator/Negative_weight/ttbar/MC@NLO-delta/441-v1/log/"    ## only need to change this line

filelist = os.listdir(Path)
myLines1 = []
myLines2 = []
myLines3 = []
myLines4 = []

print "\n"
print "########"
print "Starting Module GenXsecAnalyzer..."
print "########"
print "\n"

for i in filelist:
	if i.endswith(".log"):
        	with open(Path + i, 'r') as f:
			read_it = f.read()
			print "Reading file name :"+str(f)
            		for line in read_it.splitlines():
				if line.startswith("After filter: final fraction of events with negative weights"):
                			myLines1.append(line)
				if line.startswith("Before matching: total cross section"):
					myLines2.append(line) 
				if line.startswith("After matching: total cross section"):
					myLines3.append(line)
				if line.startswith("After filter: final cross section"):
                                        myLines4.append(line)

# Only for debugging
'''
print "\n"
print "#############################"
for i,x in enumerate(myLines1):
	i +=1
	print "File Number : "+str(i)+" : "+x

print "\n"
print "#############################"
for j,y in enumerate(myLines2):
	j +=1
	print "File Number : "+str(j)+" : "+y

print "\n"
print "#############################"
for k,z in enumerate(myLines3):
        k +=1
        print "File Number : "+str(k)+" : "+z

print "\n"
print "#############################"
for l,m in enumerate(myLines4):
        l +=1
        print "File Number : "+str(l)+" : "+m
'''

split_lines1 = [i.split() for i in myLines1]
split_lines2 = [j.split() for j in myLines2]
split_lines3 = [k.split() for k in myLines3]
split_lines4 = [l.split() for l in myLines4]

total1 = []
total2 = []
total3 = []
total4 = []

counter = 0
output1 = 0.0
output2 = 0.0
output3 = 0.0
output4 = 0.0

for avg1 in split_lines1:
	counter +=1
	total1.append(float(avg1[10]))
	#print (str(counter)+":"+avg[10])

for avg2 in split_lines2:
	total2.append(float(avg2[6]))

for avg3 in split_lines3:
        total3.append(float(avg3[6]))

for avg4 in split_lines4:
        total4.append(float(avg4[6]))

output1 = sum(total1)
results = ((output1/counter)*100)
output2 = sum(total2)
output3 = sum(total3)
output4 = sum(total4)

print "\n"
print "########"
print "Output"
print "########"
print "\n"

print "Number of Files : "+str(counter)
print "Before matching: total cross section : "+str(output2)+" pb"
print "After matching: total cross section : "+str(output3)+" pb"
print "After filter: final cross section : "+str(output4)+" pb"
print "Total fraction of Negative Weighted Events : "+str(output1)
print "After filter: final fraction of events with negative weights : "+str(results)+" %"
