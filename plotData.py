# -*- coding: utf-8 -*-
"""
Created on Sat Dec 24 13:53:24 2016

@author: David
"""

import numpy as np
import matplotlib.pyplot as plt
plt.close('all')

data = np.loadtxt('winSeries.txt',dtype=float)
data[data==2.]=0.
data[data==-1.]=0.5

contractionNumber = 250

for i in range(7):
	contracted = data[0:len(data)+1-contractionNumber]
	for i in range(contractionNumber-1):
		contracted = contracted + data[i+1:len(data)+2+i-contractionNumber]
	contracted = contracted/contractionNumber

	plt.plot(np.arange(len(contracted))+contractionNumber/2, contracted, label=contractionNumber)

	contractionNumber *= 2

plt.legend(loc='upper left')