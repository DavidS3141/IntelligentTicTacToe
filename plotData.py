# -*- coding: utf-8 -*-
"""
Created on Sat Dec 24 13:53:24 2016

@author: David
"""

import numpy as np
import matplotlib.pyplot as plt
plt.close('all')

colors=['b','r','y','k']

folder='longRun/'
folder=''

data = np.loadtxt(folder+'winSeries.txt',dtype=float)
error = np.loadtxt(folder+'errorSums.txt',dtype=float,delimiter=';')

contractionNumber = min(300,len(data)//2**4)
#contractionNumber = 1

for i in range(4):
	contracted = data[0:len(data)+1-contractionNumber]
	for j in range(contractionNumber-1):
		contracted = contracted + data[j+1:len(data)+2+j-contractionNumber]
	contracted = contracted/contractionNumber

	plt.plot(np.arange(len(contracted))+contractionNumber/2, contracted*100., color=colors[i], label=contractionNumber)

	contractionNumber *= 2

plt.xlabel('game nbr')
plt.ylabel('win rate [%]')
plt.legend(loc='upper left')

plt.figure()
#plt.plot(error[:,0],label='0')
#plt.plot(error[:,1],label='1')
#plt.plot(error[:,2],label='2')
#plt.plot(error[:,3],label='3')
#plt.plot(error[:,4],label='4')
plt.plot(error[:,5],label='5')
plt.plot(error[:,6],label='6')
plt.plot(error[:,7],label='7')
#plt.plot(error[:,8],label='8')

plt.legend()
