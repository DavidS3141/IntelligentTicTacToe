# -*- coding: utf-8 -*-
"""
Created on Sat Dec 24 13:53:24 2016

@author: David
"""

import numpy as np
import matplotlib.pyplot as plt
plt.close('all')

colors=['b','r','y','k']

data = np.loadtxt('winSeries.txt',dtype=float)
data[data==2.]=0.
data[data==-1.]=0.5

contractionNumber = min(2500,len(data)//2**4)

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