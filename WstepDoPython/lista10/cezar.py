#-*- coding: utf-8 -*-

litery = 'aąbcćdeęfghijklłmnńoóprsśtuwyzźż'
lit_to_num = {}
num_to_lit = {}

for i in range( len( litery ) ):
	lit_to_num[ litery[i] ] = i
	num_to_lit[ i ] = litery[i]

def caesar( s, k ):
	szyfr = ''
	for x in s:
		szyfr += num_to_lit[ lit_to_num[ x ] + k ]

	return szyfr

print caesar( "fajnieś", 1 )
